#include "minerworker-ethminer.h"

#include "log.h"
#include <QtCore/QRegularExpression>

MinerWorkerEthMiner::MinerWorkerEthMiner(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "ethminer.exe");
}

void MinerWorkerEthMiner::addPoolArguments()
{
  addArgument("--stratum", _poolAddress);

  auto userPass = _poolCredentials.username;
  if (!_poolCredentials.password.isEmpty())
  {
    userPass += ':' + _poolCredentials.password;
  }
  addArgument("--userpass", userPass);
}

QStringList MinerWorkerEthMiner::splitStdError(QString errLines) const
{
  QStringList lines;

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

void MinerWorkerEthMiner::addOptionArguments()
{
  addPoolArguments();

  auto hwComponent = _options.hwComponent();
  switch (hwComponent.type())
  {
    case HwComponent::Type::Gpu:
      switch (hwComponent.company())
      {
        case HwComponent::Company::Amd:
          addArgument("--opencl");
          break;
        case HwComponent::Company::Nvidia:
          addArgument("--cuda");
          break;
        default:
          Q_ASSERT_X(false, "MinerWorkerEthMiner::processArguments", "switch (hwComponent.company())");
      }
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerEthMiner::processArguments", "switch (hwComponent.type())");
  }
}

const QLoggingCategory &MinerWorkerEthMiner::logCategory() const
{
  return EthMiner();
}

void MinerWorkerEthMiner::parseStdErrLine(const QString &line) const
{
  auto errLines = splitStdError(line);
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
      QRegularExpression regExp(R"(^\s*(\S+))");
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

void MinerWorkerEthMiner::parseStdOutLine(const QString &line) const
{
}