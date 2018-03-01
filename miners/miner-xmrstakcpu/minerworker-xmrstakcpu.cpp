#include "minerworker-xmrstakcpu.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <MkLib/MModuleInfo>
#include <QtCore/QTextStream>

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId)
{
  _miningUnitId = miningUnitId;
}

QString MinerWorkerXmrStakCpu::prepareConfigFile() const
{
  auto vanillaConfig = readVanillaConfig();

  // TODO

  writeWorkerConfig(vanillaConfig);

  return vanillaConfig;
}

QString MinerWorkerXmrStakCpu::readVanillaConfig() const
{
  auto moduleFileInfo = MModuleInfo().fileInfo();
  auto moduleBaseName = moduleFileInfo.baseName();
  auto dashPos        = moduleBaseName.indexOf('-');

  auto configFilePath = moduleFileInfo.path();
  configFilePath.append(QDir::separator());
  configFilePath.append("miners");
  configFilePath.append(QDir::separator());
  configFilePath.append(moduleBaseName.mid(dashPos + 1));
  configFilePath.append(QDir::separator());
  configFilePath.append("config.txt");

  QFile configFile(configFilePath);
  configFile.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream configStream(&configFile);

  return configStream.readAll();
}

void MinerWorkerXmrStakCpu::writeWorkerConfig(const QString &config) const
{
  auto moduleFileInfo = MModuleInfo().fileInfo();
  auto moduleBaseName = moduleFileInfo.baseName();
  auto dashPos        = moduleBaseName.indexOf('-');

  auto configFilePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  configFilePath.append(QDir::separator());
  configFilePath.append("miners");
  configFilePath.append(QDir::separator());
  configFilePath.append(moduleBaseName.mid(dashPos + 1));

  QDir().mkpath(configFilePath);

  configFilePath.append(QDir::separator());
  configFilePath.append(_miningUnitId.toString());
  configFilePath.append(".txt");

  QFile configFile(configFilePath);
  configFile.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream configStream(&configFile);
  configStream << config;
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