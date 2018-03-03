#include "minerworker-xmrstakcpu.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <MkLib/MModuleInfo>
#include <QtCore/QTextStream>
#include <QtCore/QThread>
#include "log.h"

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId)
{
  _miningUnitId = miningUnitId;

  _fileInfo     = MModuleInfo().fileInfo();

  auto baseName = _fileInfo.baseName();
  auto dashPos  = baseName.indexOf('-');
  _minerName    = baseName.mid(dashPos + 1);

  _vanillaDir.setPath(_fileInfo.path());
  _vanillaDir.cd("miners");
  _vanillaDir.cd(_minerName);

  _minerProcess.setProgram(_vanillaDir.path() + QDir::separator() + "xmr-stak-cpu-notls.exe");
  _minerProcess.setWorkingDirectory(_vanillaDir.path());
}

MinerWorkerXmrStakCpu::~MinerWorkerXmrStakCpu()
{
  if (_minerProcess.state() != QProcess::NotRunning)
  {
    stop();
  }
}

void MinerWorkerXmrStakCpu::modifyConfig(QString *config) const
{
  QString cpuThreadsConf = "\"cpu_threads_conf\" :\n[";
  for (auto cpu = 0; cpu < QThread::idealThreadCount(); cpu++)
  {
    cpuThreadsConf += QString("\n     { \"low_power_mode\" : false, \"no_prefetch\" : true, \"affine_to_cpu\" : %1 },").arg(cpu);
#ifdef _DEBUG
    break;
#endif
  }
  cpuThreadsConf    += "\n],";
  auto poolAddress   = R"("pool_address" : ")"   + _poolAddress              + "\",";
  auto walletAddress = R"("wallet_address" : ")" + _poolCredentials.username + "\",";
  auto poolPassword  = R"("pool_password" : ")"  + _poolCredentials.password + "\",";
  auto verboseLevel  = R"("verbose_level" : 4,)";

  config->replace("\"cpu_threads_conf\" : \nnull,",                 cpuThreadsConf);
  config->replace(R"("pool_address" : "pool.usxmrpool.com:3333",)", poolAddress);
  config->replace(R"("wallet_address" : "",)",                      walletAddress);
  config->replace(R"("pool_password" : "",)",                       poolPassword);
  config->replace(R"("verbose_level" : 3,)",                        verboseLevel);
}

QString MinerWorkerXmrStakCpu::prepareConfigFile() const
{
  auto config = readVanillaConfig();

  modifyConfig(&config);

  auto filePath = writeWorkerConfig(config);

  return filePath;
}

QString MinerWorkerXmrStakCpu::readVanillaConfig() const
{
  auto configFileInfo = QFileInfo(_vanillaDir, "config.txt");

  QFile configFile(configFileInfo.filePath());
  configFile.open(QIODevice::ReadOnly | QIODevice::Text);

  QTextStream configStream(&configFile);
  return configStream.readAll();
}

void MinerWorkerXmrStakCpu::stop()
{
  _minerProcess.terminate();

  mCInfo(XmrStakCpu) << "miner for mining unit " << _miningUnitId.toString() << " stopped";
}

QString MinerWorkerXmrStakCpu::writeWorkerConfig(const QString &config) const
{
  auto moduleBaseName = _fileInfo.baseName();
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

  return configFilePath;
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

  _minerProcess.setArguments(QStringList() << configFilePath);
  _minerProcess.start();

  mCInfo(XmrStakCpu) << "miner for mining unit " << _miningUnitId.toString() << " started";
}