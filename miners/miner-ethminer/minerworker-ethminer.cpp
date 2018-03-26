#include "minerworker-ethminer.h"

#include "log.h"
#include <QtCore/QRegularExpression>

MinerWorkerEthMiner::MinerWorkerEthMiner(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "ethminer.exe");
}

QStringList MinerWorkerEthMiner::poolArguments() const
{
  QStringList arguments;

  arguments << "--stratum"  << _poolAddress;

  auto userPass = _poolCredentials.username;
  if (!_poolCredentials.password.isEmpty())
  {
    userPass += ':' + _poolCredentials.password;
  }
  arguments << "--userpass" << userPass;

  return arguments;
}

QStringList MinerWorkerEthMiner::splitStdError() const
{
  QStringList lines;

  auto errLines = _stdErrLastLine;
  while (!errLines.isEmpty())
  {
    auto pipePos = errLines.indexOf('|');
    if (pipePos == -1)
    {
      lines.append(errLines);
      break;
    }
    else
    {
      auto nextPipePos = errLines.indexOf('|', pipePos + 1);
      if (nextPipePos == -1)
      {
        lines.append(errLines);
        break;
      }
      else
      {
        auto errLineLength = qMax(nextPipePos - 13, 1);
        lines.append(errLines.left(errLineLength));
        errLines.remove(0, errLineLength);
      }
    }
  }

  return lines;
}

const QLoggingCategory &MinerWorkerEthMiner::logCategory() const
{
  return EthMiner();
}

void MinerWorkerEthMiner::parseStdErrLine() const
{
  auto errLines = splitStdError();
  for (const auto &errLine : errLines)
  {
    QString message = _miningUnitId.toString() + ' ';

    auto pipePos = errLine.indexOf('|');
    if (pipePos == -1)
    {
      message.append(errLine);
    }
    else
    {
      message.append(errLine.mid(pipePos + 1));
    }

    if (errLine.contains("Error") || errLine.contains("failed"))
    {
      mCCritical(EthMiner) << message;
    }
    else
    {
      QRegularExpression regExp(R"(\s*(\S+))");
      auto regExpMatch = regExp.match(errLine);
      if (regExpMatch.hasMatch())
      {
        if (regExpMatch.capturedRef(1) == 'X')
        {
          mCCritical(EthMiner) << message;
        }
        else if (regExpMatch.capturedRef(1) == 'D')
        {
          mCDebug(EthMiner) << message;
        }
        else
        {
          mCInfo(EthMiner) << message;
        }
      }
    }

    if (errLine.contains("Accepted."))
    {
      emit resultAccepted();
    }

    QRegularExpression regExp(R"(Speed\s+(\d+\.\d+))");
    auto regExpMatch = regExp.match(errLine);
    if (regExpMatch.hasMatch())
    {
      emit hashRate(regExpMatch.capturedRef(1).toFloat() * 1000000);
    }
  }
}

void MinerWorkerEthMiner::parseStdOutLine() const
{
}

QStringList MinerWorkerEthMiner::processArguments() const
{
  auto arguments = poolArguments();

  auto hwComponent = _options.hwComponent();
  switch (hwComponent.type())
  {
    case HwComponent::Type::Gpu:
      switch (hwComponent.company())
      {
        case HwComponent::Company::Amd:
          arguments << "--opencl";
          break;
        case HwComponent::Company::Nvidia:
          arguments << "--cuda";
          break;
        default:
          Q_ASSERT_X(false, "MinerWorkerEthMiner::processArguments", "switch (hwComponent.company())");
      }
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerEthMiner::processArguments", "switch (hwComponent.type())");
  }

  return arguments;
}