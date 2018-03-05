#include "minerworker-xmrstakcpu.h"

#include <QtCore/QStandardPaths>
#include <MkLib/MModuleInfo>
#include <QtCore/QThread>
#include "log.h"
#include <QtCore/QRegularExpression>

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId)
{
  _miningUnitId = miningUnitId;

  _fileInfo = MModuleInfo().fileInfo();

  auto baseName = _fileInfo.completeBaseName();
  auto dashPos  = baseName.indexOf('-');
  _minerName    = baseName.mid(dashPos + 1);

  _minerDir.setPath(_fileInfo.path());
  _minerDir.cd("miners");
  _minerDir.cd(_minerName);

  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak-cpu-notls.exe");
  _minerProcess.setWorkingDirectory(_minerDir.path());
}

MinerWorkerXmrStakCpu::~MinerWorkerXmrStakCpu()
{
  if (_minerProcess.state() != QProcess::NotRunning)
  {
    _minerProcess.kill();
  }
}

void MinerWorkerXmrStakCpu::modifyConfig(QString *config) const
{
  QString cpuThreadsConf = "\"cpu_threads_conf\" :\n[";
  for (auto cpu = 0; cpu < QThread::idealThreadCount(); ++cpu)
  {
    cpuThreadsConf += QString("\n     { \"low_power_mode\" : false, \"no_prefetch\" : true, \"affine_to_cpu\" : %1 },").arg(cpu);
#ifdef _DEBUG
    if (QThread::idealThreadCount() < 2 || cpu == QThread::idealThreadCount() - 2)
    {
      break;
    }
#endif
  }
  cpuThreadsConf += "\n],";

  config->replace("\"cpu_threads_conf\" : \nnull,",                 cpuThreadsConf);
  config->replace(R"("pool_address" : "pool.usxmrpool.com:3333",)", R"("pool_address" : ")"   + _poolAddress              + "\",");
  config->replace(R"("wallet_address" : "",)",                      R"("wallet_address" : ")" + _poolCredentials.username + "\",");
  config->replace(R"("pool_password" : "",)",                       R"("pool_password" : ")"  + _poolCredentials.password + "\",");
  config->replace(R"("verbose_level" : 3,)",                        R"("verbose_level" : 4,)");
  config->replace(R"("h_print_time" : 60,)",                        R"("h_print_time" : 1,)");
}

QString MinerWorkerXmrStakCpu::prepareConfigFile() const
{
  auto config = readVanillaConfig();

  modifyConfig(&config);

  auto filePath = writeWorkerConfig(config);

  return filePath;
}

QString MinerWorkerXmrStakCpu::readVanillaConfig() const
{
  auto configFileInfo = QFileInfo(_minerDir, "config.txt");

  QFile configFile(configFileInfo.filePath());
  configFile.open(QIODevice::ReadOnly | QIODevice::Text);

  QTextStream configStream(&configFile);
  return configStream.readAll();
}

QString MinerWorkerXmrStakCpu::writeWorkerConfig(const QString &config) const
{
  auto configFilePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  configFilePath.append(QDir::separator());
  configFilePath.append(_fileInfo.completeBaseName());

  QDir().mkpath(configFilePath);

  configFilePath.append(QDir::separator());
  configFilePath.append(_miningUnitId.toString());
  configFilePath.append(".txt");

  QFile configFile(configFilePath);
  configFile.open(QIODevice::WriteOnly | QIODevice::Text);

  QTextStream configStream(&configFile);
  configStream << config;

  return configFilePath;
}

bool MinerWorkerXmrStakCpu::isRunning() const
{
  return _minerProcess.state() != QProcess::NotRunning;
}

void MinerWorkerXmrStakCpu::setPoolAddress(const QString &address)
{
  _poolAddress = address;
}

void MinerWorkerXmrStakCpu::setPoolCredentials(const PoolCredentials &credentials)
{
  _poolCredentials = credentials;
}

void MinerWorkerXmrStakCpu::start()
{
  auto configFilePath = prepareConfigFile();
  _minerProcess.setArguments(QStringList() << configFilePath);

  _stdOutStream.setDevice(&_minerProcess);

  connect(&_minerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MinerWorkerXmrStakCpu::on_minerProcess_finished);
  connect(&_minerProcess, &QProcess::readyReadStandardOutput,                            this, &MinerWorkerXmrStakCpu::on_minerProcess_readyReadStandardOutput);

  _minerProcess.start(QIODevice::ReadOnly);

  if (_minerProcess.error() == QProcess::FailedToStart)
  {
    mCCritical(XmrStakCpu) << "failed to start miner for mining unit " << _miningUnitId.toString();

    emit finished();
  }
  else
  {
    mCInfo(XmrStakCpu) << "miner for mining unit " << _miningUnitId.toString() << " started";
  }
}

void MinerWorkerXmrStakCpu::on_minerProcess_finished(int exitCode, QProcess::ExitStatus exitStatus) const
{
  mCInfo(XmrStakCpu) << "miner for mining unit " << _miningUnitId.toString() << " stopped";

  emit finished();
}

void MinerWorkerXmrStakCpu::on_minerProcess_readyReadStandardOutput()
{
  forever
  {
    _stdOutLastLine += _stdOutStream.readLine();
    if (_stdOutStream.atEnd())
    {
      break;
    }

    _minerOutput.append(_stdOutLastLine + '\n');

    QRegularExpression regExp(R"(^\[.*\] : (.*))");
    auto regExpMatch = regExp.match(_stdOutLastLine);
    if (regExpMatch.hasMatch())
    {
      auto message = _miningUnitId.toString() + ' ' + regExpMatch.capturedRef(1);

      if (regExpMatch.capturedRef(1).contains("ERROR") || regExpMatch.capturedRef(1).contains("FAILED"))
      {
        mCCritical(XmrStakCpu) << message;
      }
      else if (regExpMatch.capturedRef(1).startsWith("Pool connection lost."))
      {
        mCWarning(XmrStakCpu) << message;
      }
      else
      {
        mCInfo(XmrStakCpu) << message;

        if (regExpMatch.capturedRef(1) == "Result accepted by the pool.")
        {
          emit resultAccepted();
        }
      }
    }
    else
    {
      regExp.setPattern(R"(^Totals:\D*(\d+\.\d))");
      regExpMatch = regExp.match(_stdOutLastLine);
      if (regExpMatch.hasMatch())
      {
        emit hashRate(regExpMatch.capturedRef(1).toFloat());
      }
    }

    _stdOutLastLine.clear();
  }
}