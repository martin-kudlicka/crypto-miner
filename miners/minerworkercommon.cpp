#include "minerworkercommon.h"

#include <MkLib/MModuleInfo>
#include <QtCore/QStandardPaths>

MinerWorkerCommon::MinerWorkerCommon(const MUuidPtr &miningUnitId) : _miningUnitId(miningUnitId)
{
  auto fileInfo = MModuleInfo().fileInfo();

  auto baseName = fileInfo.completeBaseName();
  auto dashPos  = baseName.indexOf('-');
  _minerName    = baseName.mid(dashPos + 1);

  _minerDir.setPath(fileInfo.path());
  _minerDir.cd("miners");
  _minerDir.cd(_minerName);

  auto workPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  workPath.append(QDir::separator());
  workPath.append(fileInfo.completeBaseName());
  _workDir.setPath(workPath);
}

void MinerWorkerCommon::appendOutput(const QString &line)
{
  if (_minerOutput.count() >= 16)
  {
    _minerOutput.removeFirst();
  }

  _minerOutput.append(line);
}

const QStringList &MinerWorkerCommon::consoleOutput() const
{
  return _minerOutput;
}

const QString &MinerWorkerCommon::name() const
{
  return _minerName;
}

void MinerWorkerCommon::setPoolAddress(const QString &address)
{
  _poolAddress = address;
}

void MinerWorkerCommon::setPoolCredentials(const PoolCredentials &credentials)
{
  _poolCredentials = credentials;
}