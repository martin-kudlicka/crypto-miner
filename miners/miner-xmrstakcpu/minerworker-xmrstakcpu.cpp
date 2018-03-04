#include "minerworker-xmrstakcpu.h"

#include <QtCore/QStandardPaths>
#include <MkLib/MModuleInfo>
#include <QtCore/QThread>
#include "log.h"

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId)
{
  _miningUnitId = miningUnitId;

  _fileInfo = MModuleInfo().fileInfo();

  auto baseName = _fileInfo.baseName();
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

    mCInfo(XmrStakCpu) << "miner for mining unit " << _miningUnitId.toString() << " stopped";
  }
}

void MinerWorkerXmrStakCpu::modifyConfig(QString *config) const
{
  QString cpuThreadsConf = "\"cpu_threads_conf\" :\n[";
  for (auto cpu = 0; cpu < QThread::idealThreadCount(); ++cpu)
  {
    cpuThreadsConf += QString("\n     { \"low_power_mode\" : false, \"no_prefetch\" : true, \"affine_to_cpu\" : %1 },").arg(cpu);
#ifdef _DEBUG
    if (cpu == 2)
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
  auto moduleBaseName = _fileInfo.baseName();
  auto dashPos        = moduleBaseName.indexOf('-');

  auto configFilePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  configFilePath.append(QDir::separator());
  configFilePath.append("miners");
  configFilePath.append(QDir::separator());
  configFilePath.append(moduleBaseName.mid(dashPos + 1));

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

  connect(&_minerProcess, &QProcess::readyReadStandardOutput, this, &MinerWorkerXmrStakCpu::on_minerProcess_readyReadStandardOutput);

  _minerProcess.start(QIODevice::ReadOnly);

  mCInfo(XmrStakCpu) << "miner for mining unit " << _miningUnitId.toString() << " started";
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

    if (_stdOutLastLine.startsWith('['))
    {
      auto message = _miningUnitId.toString() + ' ';
      auto linePos = _stdOutLastLine.indexOf(": ");
      message.append(_stdOutLastLine.mid(linePos + 2));

      if (message.contains("ERROR") || message.contains("FAILED"))
      {
        mCCritical(XmrStakCpu) << message;
      }
      else if (message.contains("Pool connection lost."))
      {
        mCWarning(XmrStakCpu) << message;
      }
      else
      {
        mCInfo(XmrStakCpu) << message;

        if (message.contains("Result accepted by the pool."))
        {
          emit resultAccepted();
        }
      }
    }

    _stdOutLastLine.clear();
  }
}