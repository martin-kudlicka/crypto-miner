#include "minerworker-ethminer.h"

#include "log.h"

MinerWorkerEthMiner::MinerWorkerEthMiner(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "ethminer.exe");
}

const QLoggingCategory &MinerWorkerEthMiner::logCategory() const
{
  return EthMiner();
}

void MinerWorkerEthMiner::parseStdOutLine() const
{
  // TODO
}

QStringList MinerWorkerEthMiner::processArguments() const
{
  // TODO
  return QStringList();
}