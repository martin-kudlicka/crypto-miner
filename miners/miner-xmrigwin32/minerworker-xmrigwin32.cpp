#include "minerworker-xmrigwin32.h"

#include "log.h"
#include <QtCore/QRegularExpression>

MinerWorkerXmrigWin32::MinerWorkerXmrigWin32(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmrig.exe");
}

void MinerWorkerXmrigWin32::addPoolArguments()
{
  addArgument("--url=" + _poolAddress);
  addArgument("--user=" + _poolCredentials.username);
  if (!_poolCredentials.password.isEmpty())
  {
    addArgument("--pass=" + _poolCredentials.password);
  }
}

const QLoggingCategory &MinerWorkerXmrigWin32::logCategory() const
{
  return XmrigWin32();
}

void MinerWorkerXmrigWin32::addOptionArguments()
{
  addPoolArguments();

  addArgument("--donate-level=1");
  addArgument("--max-cpu-usage=100");
}

void MinerWorkerXmrigWin32::parseStdErrLine(const QString &line) const
{
}

void MinerWorkerXmrigWin32::parseStdOutLine(const QString &line) const
{
  auto outLines = line.split(QRegularExpression(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\])"), QString::SkipEmptyParts);
  for (auto outLine : outLines)
  {
    outLine      = outLine.trimmed();
    auto message = _miningUnitId.toString() + ' ' + outLine;

    if (outLine.contains("error:"))
    {
      mCCritical(XmrigWin32) << message;
    }
    else
    {
      mCInfo(XmrigWin32) << message;
    }

    if (outLine.contains("accepted "))
    {
      emit resultAccepted();
    }

    QRegularExpression regExp(R"(^speed\s\S+\s\D*(\d+\.\d+))");
    auto regExpMatch = regExp.match(outLine);
    if (regExpMatch.hasMatch())
    {
      emit hashRate(regExpMatch.capturedRef(1).toFloat());
    }
  }
}