#include "minerworker-xmrigwin32.h"

#include "log.h"
#include <QtCore/QRegularExpression>

MinerWorkerXmrigWin32::MinerWorkerXmrigWin32(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmrig.exe");
}

QStringList MinerWorkerXmrigWin32::poolArguments() const
{
  QStringList arguments;

  arguments << "--url=" + _poolAddress;
  arguments << "--user=" + _poolCredentials.username;
  if (!_poolCredentials.password.isEmpty())
  {
    arguments << "--pass=" + _poolCredentials.password;
  }

  return arguments;
}

const QLoggingCategory &MinerWorkerXmrigWin32::logCategory() const
{
  return XmrigWin32();
}

void MinerWorkerXmrigWin32::parseStdErrLine() const
{
}

void MinerWorkerXmrigWin32::parseStdOutLine() const
{
  auto outLines = _stdOutLastLine.split(QRegularExpression(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\])"), QString::SkipEmptyParts);
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
  }
}

QStringList MinerWorkerXmrigWin32::processArguments() const
{
  auto arguments = poolArguments();

  arguments << "--donate-level=1";
  arguments << "--max-cpu-usage=100";

  return arguments;
}