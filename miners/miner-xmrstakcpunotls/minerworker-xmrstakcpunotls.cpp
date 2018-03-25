#include "minerworker-xmrstakcpunotls.h"

#include <QtCore/QThread>
#include "log.h"
#include <QtCore/QRegularExpression>
#include <MkCore/MFile>

MinerWorkerXmrStakCpuNoTls::MinerWorkerXmrStakCpuNoTls(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak-cpu-notls.exe");
}

void MinerWorkerXmrStakCpuNoTls::modifyConfig(QString *config) const
{
  QString cpuThreadsConf = "\"cpu_threads_conf\" :\n[";
  for (auto threadNum = 0; threadNum < QThread::idealThreadCount(); ++threadNum)
  {
#ifdef _DEBUG
    if (QThread::idealThreadCount() < 2 || threadNum == QThread::idealThreadCount() - 2)
    {
      break;
    }
#endif
    cpuThreadsConf += QString("\n     { \"low_power_mode\" : false, \"no_prefetch\" : true, \"affine_to_cpu\" : %1 },").arg(threadNum);
  }
  cpuThreadsConf += "\n],";

  config->replace("\"cpu_threads_conf\" : \nnull,",                 cpuThreadsConf);
  config->replace(R"("pool_address" : "pool.usxmrpool.com:3333",)", R"("pool_address" : ")"   + _poolAddress              + "\",");
  config->replace(R"("wallet_address" : "",)",                      R"("wallet_address" : ")" + _poolCredentials.username + "\",");
  config->replace(R"("pool_password" : "",)",                       R"("pool_password" : ")"  + _poolCredentials.password + "\",");
  config->replace(R"("verbose_level" : 3,)",                        R"("verbose_level" : 4,)");
  config->replace(R"("h_print_time" : 60,)",                        R"("h_print_time" : 1,)");
}

QString MinerWorkerXmrStakCpuNoTls::prepareConfigFile() const
{
  auto config = readVanillaConfig();

  modifyConfig(&config);

  auto filePath = writeWorkerConfig(config);

  return filePath;
}

QString MinerWorkerXmrStakCpuNoTls::readVanillaConfig() const
{
  auto configFileInfo = QFileInfo(_minerDir, "config.txt");

  QFile configFile(configFileInfo.filePath());
  configFile.open(QIODevice::ReadOnly | QIODevice::Text);

  QTextStream configStream(&configFile);
  return configStream.readAll();
}

QString MinerWorkerXmrStakCpuNoTls::writeWorkerConfig(const QString &config) const
{
  auto configFilePath = _workDir.path();
  configFilePath.append(QDir::separator());
  configFilePath.append(_miningUnitId.toString());
  configFilePath.append(".txt");

  MFile::write(configFilePath, config);

  return configFilePath;
}

void MinerWorkerXmrStakCpuNoTls::start()
{
  auto configFilePath = prepareConfigFile();
  _minerProcess.setArguments(QStringList() << configFilePath);

  _stdOutStream.setDevice(&_minerProcess);

  connect(&_minerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MinerWorkerXmrStakCpuNoTls::on_minerProcess_finished);
  connect(&_minerProcess, &QProcess::readyReadStandardOutput,                            this, &MinerWorkerXmrStakCpuNoTls::on_minerProcess_readyReadStandardOutput);

  _minerProcess.start(QIODevice::ReadOnly);

  if (_minerProcess.error() == QProcess::FailedToStart)
  {
    mCCritical(XmrStakCpuNoTls) << "failed to start miner for mining unit " << _miningUnitId.toString();

    emit finished();
  }
  else
  {
    mCInfo(XmrStakCpuNoTls) << "miner for mining unit " << _miningUnitId.toString() << " started";
  }
}

void MinerWorkerXmrStakCpuNoTls::on_minerProcess_finished(int exitCode, QProcess::ExitStatus exitStatus) const
{
  mCInfo(XmrStakCpuNoTls) << "miner for mining unit " << _miningUnitId.toString() << " stopped";

  emit finished();
}

void MinerWorkerXmrStakCpuNoTls::on_minerProcess_readyReadStandardOutput()
{
  forever
  {
    _stdOutLastLine += _stdOutStream.readLine();
    if (_stdOutStream.atEnd())
    {
      break;
    }

    emit outputLine(_stdOutLastLine);
    appendOutput(_stdOutLastLine);

    auto outLines = _stdOutLastLine.split(QRegularExpression(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\])"), QString::SkipEmptyParts);
    for (auto outLine : outLines)
    {
      if (outLine.startsWith(" : "))
      {
        outLine.remove(0, 3);
      }
      auto message = _miningUnitId.toString() + ' ' + outLine;

      if (outLine.contains("ERROR") || outLine.contains("FAILED"))
      {
        mCCritical(XmrStakCpuNoTls) << message;
      }
      else if (outLine.contains("connection lost"))
      {
        mCWarning(XmrStakCpuNoTls) << message;
      }
      else
      {
        mCInfo(XmrStakCpuNoTls) << message;
      }

      if (outLine.contains("Result accepted"))
      {
        emit resultAccepted();
      }

      QRegularExpression regExp(R"(^Totals:\D*(\d+\.\d))");
      auto regExpMatch = regExp.match(outLine);
      if (regExpMatch.hasMatch())
      {
        emit hashRate(regExpMatch.capturedRef(1).toFloat());
      }
    }

    _stdOutLastLine.clear();
  }
}