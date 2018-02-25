#include "minerworker-xmrstakcpu.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <MkCore/MModuleInfo>

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId)
{
  _miningUnitId = miningUnitId;

  _configFilePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  _configFilePath.append(QDir::separator());
  _configFilePath.append("miners");
  _configFilePath.append(QDir::separator());

  auto moduleBaseName = MModuleInfo().fileInfo().baseName();
  auto dashPos        = moduleBaseName.indexOf('-');
  _configFilePath.append(moduleBaseName.mid(dashPos + 1));

  QDir().mkpath(_configFilePath);

  _configFilePath.append(QDir::separator());
  _configFilePath.append(miningUnitId.toString());
  _configFilePath.append(".txt");
}

void MinerWorkerXmrStakCpu::prepareConfigFile() const
{
  
}

void MinerWorkerXmrStakCpu::setPoolAddress(const QString &address)
{
  _poolAddress = address;
}

void MinerWorkerXmrStakCpu::setPoolCredentials(const PoolCredentials &credentials)
{
  _poolCredentials = credentials;
}

void MinerWorkerXmrStakCpu::start()
{
  // TODO
}