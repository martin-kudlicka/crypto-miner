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

QStringList MinerWorkerEthMiner::splitStdOutput() const
{
  QStringList lines;

  auto outLines = _stdOutLastLine;
  while (!outLines.isEmpty())
  {
    auto pipePos = outLines.indexOf('|');
    if (pipePos == -1)
    {
      lines.append(outLines);
      break;
    }
    else
    {
      auto nextPipePos = outLines.indexOf('|', pipePos + 1);
      if (nextPipePos == -1)
      {
        lines.append(outLines);
        break;
      }
      else
      {
        auto outLineLength = qMax(nextPipePos - 13, 1);
        lines.append(outLines.left(outLineLength));
        outLines.remove(0, outLineLength);
      }
    }
  }

  return lines;
}

const QLoggingCategory &MinerWorkerEthMiner::logCategory() const
{
  return EthMiner();
}

void MinerWorkerEthMiner::parseStdOutLine() const
{
  auto outLines = splitStdOutput();
  for (const auto &outLine : outLines)
  {
    QString message = _miningUnitId.toString() + ' ';

    auto pipePos = outLine.indexOf('|');
    if (pipePos == -1)
    {
      message.append(outLine);
    }
    else
    {
      message.append(outLine.mid(pipePos + 1));
    }

    if (outLine.contains("Error") || outLine.contains("failed"))
    {
      mCCritical(EthMiner) << message;
    }
    else
    {
      QRegularExpression regExp(R"(\s*(\S+))");
      auto regExpMatch = regExp.match(outLine);
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

    QRegularExpression regExp(R"(Speed\s+(\d+\.\d+))");
    auto regExpMatch = regExp.match(outLine);
    if (regExpMatch.hasMatch())
    {
      emit hashRate(regExpMatch.capturedRef(1).toFloat() * 1000000);
    }
  }
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