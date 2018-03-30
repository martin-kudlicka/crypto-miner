#include "minerworker-xmrigwin32.h"

#include "log.h"

MinerWorkerXmrigWin32::MinerWorkerXmrigWin32(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmrig.exe");
}

QStringList MinerWorkerXmrigWin32::poolArguments() const
{
  QStringList arguments;

  arguments << "--url" << _poolAddress;
  arguments << "--user" << _poolCredentials.username;
  if (!_poolCredentials.password.isEmpty())
  {
    arguments << "--pass" << _poolCredentials.password;
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
  // TODO
}

QStringList MinerWorkerXmrigWin32::processArguments() const
{
  auto arguments = poolArguments();

  // TODO

  return arguments;
}