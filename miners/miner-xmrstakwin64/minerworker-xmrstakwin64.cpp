#include "minerworker-xmrstakwin64.h"

#include "log.h"
#include <QtCore/QResource>
#include <MkCore/MFile>
#include <QtCore/QRegularExpression>

MinerWorkerXmrStakWin64::MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak.exe");
}

QStringList MinerWorkerXmrStakWin64::currencyArguments() const
{
  QStringList arguments;

  arguments << "--currency";

  auto coin = _options.coin();
  switch (coin.name())
  {
    case Coin::Name::Aeon:
      arguments << "aeon";
      break;
    case Coin::Name::Monero:
      arguments << "monero";
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::currencyArguments", "switch (coin.name())");
  }

  return arguments;
}

QStringList MinerWorkerXmrStakWin64::poolArguments() const
{
  QStringList arguments;

  arguments << "--url"  << _poolAddress;
  arguments << "--user" << _poolCredentials.username;
  arguments << "--pass";
  if (_poolCredentials.password.isEmpty())
  {
    arguments << R"("")";
  }
  else
  {
    arguments << _poolCredentials.password;
  }

  return arguments;
}

QStringList MinerWorkerXmrStakWin64::prepareArguments() const
{
  auto arguments = poolArguments();

  arguments << "--config";
  arguments << prepareCommonConfig();

  arguments << "--noUAC";

  arguments << currencyArguments();

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

  auto configFilePath = _workDir.path();
  configFilePath.append(QDir::separator());
  configFilePath.append(_miningUnitId.toString());
  configFilePath.append("-config.txt");

  MFile::write(configFilePath, configData);

  return configFilePath;
}

const QLoggingCategory &MinerWorkerXmrStakWin64::logCategory() const
{
  return XmrStakWin64();
}

void MinerWorkerXmrStakWin64::start()
{
  auto arguments = prepareArguments();
  _minerProcess.setArguments(arguments);

  _stdOutStream.setDevice(&_minerProcess);

  connect(&_minerProcess, &QProcess::readyReadStandardOutput, this, &MinerWorkerXmrStakWin64::on_minerProcess_readyReadStandardOutput);

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
        mCCritical(XmrStakWin64) << message;
      }
      else
      {
        mCInfo(XmrStakWin64) << message;
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