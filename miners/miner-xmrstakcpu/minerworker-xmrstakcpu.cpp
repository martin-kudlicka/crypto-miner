#include "minerworker-xmrstakcpu.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <MkCore/MModuleInfo>

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId)
{
  _miningUnitId = miningUnitId;
}

QString MinerWorkerXmrStakCpu::prepareConfigFile() const
{
  auto moduleFileInfo = MModuleInfo().fileInfo();
  auto moduleBaseName = moduleFileInfo.baseName();
  auto dashPos        = moduleBaseName.indexOf('-');

  auto vanillaConfigFilePath = moduleFileInfo.path();
  vanillaConfigFilePath.append(QDir::separator());
  vanillaConfigFilePath.append("miners");
  vanillaConfigFilePath.append(QDir::separator());
  vanillaConfigFilePath.append(moduleBaseName.mid(dashPos + 1));
  vanillaConfigFilePath.append(QDir::separator());
  vanillaConfigFilePath.append("config.txt");

  auto workerConfigFilePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  workerConfigFilePath.append(QDir::separator());
  workerConfigFilePath.append("miners");
  workerConfigFilePath.append(QDir::separator());
  workerConfigFilePath.append(moduleBaseName.mid(dashPos + 1));

  QDir().mkpath(workerConfigFilePath);

  workerConfigFilePath.append(QDir::separator());
  workerConfigFilePath.append(_miningUnitId.toString());
  workerConfigFilePath.append(".txt");

  // TODO

  return workerConfigFilePath;
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
  auto configFilePath = prepareConfigFile();

  // TODO
}