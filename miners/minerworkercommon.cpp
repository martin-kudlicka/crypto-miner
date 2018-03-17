#include "minerworkercommon.h"

#include <MkLib/MModuleInfo>

MinerWorkerCommon::MinerWorkerCommon(const MUuidPtr &miningUnitId) : _miningUnitId(miningUnitId)
{
  _fileInfo = MModuleInfo().fileInfo();

  auto baseName = _fileInfo.completeBaseName();
  auto dashPos  = baseName.indexOf('-');
  _minerName    = baseName.mid(dashPos + 1);

  _minerDir.setPath(_fileInfo.path());
  _minerDir.cd("miners");
  _minerDir.cd(_minerName);
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