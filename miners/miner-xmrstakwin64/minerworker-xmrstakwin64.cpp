#include "minerworker-xmrstakwin64.h"

#include "log.h"
#include <QtCore/QResource>
#include <MkCore/MFile>
#include <QtCore/QRegularExpression>

MinerWorkerXmrStakWin64::MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId), _options(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak.exe");
  _minerProcess.setWorkingDirectory(_minerDir.path());
}

QStringList MinerWorkerXmrStakWin64::prepareArguments() const
{
  QStringList arguments;

  arguments << "--config";
  arguments << prepareCommonConfig();

  arguments << "--noUAC";

  auto hwComponent = _options.hwComponent();
  switch (hwComponent.type())
  {
    case HwComponent::Type::Cpu:
      arguments << "--noAMD";
      arguments << "--noNVIDIA";
      break;
    case HwComponent::Type::Gpu:
      arguments << "--noCPU";

      switch (hwComponent.company())
      {
        case HwComponent::Company::Amd:
          arguments << "--noNVIDIA";
          break;
        case HwComponent::Company::Nvidia:
          arguments << "--noAMD";
          break;
        default:
          Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::prepareArguments", "switch (hwComponent.company())");
      }
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::prepareArguments", "switch (hwComponent.type())");
  }

  return arguments;
}

QString MinerWorkerXmrStakWin64::prepareCommonConfig() const
{
  QResource configResource(":/resources/files/config.txt");
  QByteArray configData = reinterpret_cast<const char *>(configResource.data());

  configData.replace("%pool_address%",   _poolAddress.toLocal8Bit());
  configData.replace("%wallet_address%", _poolCredentials.username.toLocal8Bit());
  configData.replace("%pool_password%",  _poolCredentials.password.toLocal8Bit());

  QString currency;
  auto coin = _options.coin();
  switch (coin.name())
  {
    case Coin::Name::Aeon:
      currency = "aeon";
      break;
    case Coin::Name::Monero:
      currency = "monero";
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::prepareCommonConfig", "switch (coinName)");
  }
  configData.replace("%currency%", currency.toLocal8Bit());

  auto configFilePath = _workDir.path();
  configFilePath.append(QDir::separator());
  configFilePath.append(_miningUnitId.toString());
  configFilePath.append("-config.txt");

  MFile::write(configFilePath, configData);

  return configFilePath;
}
const QString &MinerWorkerXmrStakWin64::consoleOutput() const
{
  return _minerOutput;
}

bool MinerWorkerXmrStakWin64::isRunning() const
{
  return _minerProcess.state() != QProcess::NotRunning;
}

void MinerWorkerXmrStakWin64::start()
{
  auto arguments = prepareArguments();
  _minerProcess.setArguments(arguments);

  _stdOutStream.setDevice(&_minerProcess);

  connect(&_minerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MinerWorkerXmrStakWin64::on_minerProcess_finished);
  connect(&_minerProcess, &QProcess::readyReadStandardOutput,                            this, &MinerWorkerXmrStakWin64::on_minerProcess_readyReadStandardOutput);

  _minerProcess.start(QIODevice::ReadOnly);

  if (_minerProcess.error() == QProcess::FailedToStart)
  {
    mCCritical(XmrStakWin64) << "failed to start miner for mining unit " << _miningUnitId.toString();

    emit finished();
  }
  else
  {
    mCInfo(XmrStakWin64) << "miner for mining unit " << _miningUnitId.toString() << " started";
  }
}

void MinerWorkerXmrStakWin64::stop()
{
  _minerProcess.kill();
}

void MinerWorkerXmrStakWin64::on_minerProcess_finished(int exitCode, QProcess::ExitStatus exitStatus) const
{
  mCInfo(XmrStakWin64) << "miner for mining unit " << _miningUnitId.toString() << " stopped";

  emit finished();
}

void MinerWorkerXmrStakWin64::on_minerProcess_readyReadStandardOutput()
{
  forever
  {
    _stdOutLastLine += _stdOutStream.readLine();
    if (_stdOutStream.atEnd())
    {
      break;
    }

    emit outputLine(_stdOutLastLine);
    _minerOutput.append(_stdOutLastLine + '\n');

    QRegularExpression regExp(R"(^\[.*\] : (.*))");
    auto regExpMatch = regExp.match(_stdOutLastLine);
    if (regExpMatch.hasMatch())
    {
      auto message = _miningUnitId.toString() + ' ' + regExpMatch.capturedRef(1);

      if (regExpMatch.capturedRef(1).contains("ERROR") || regExpMatch.capturedRef(1).contains("FAILED"))
      {
        mCCritical(XmrStakWin64) << message;
      }
    }

    _stdOutLastLine.clear();
  }
}