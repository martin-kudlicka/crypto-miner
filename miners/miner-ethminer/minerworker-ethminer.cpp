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

void MinerWorkerEthMiner::start()
{
  // TODO

  _stdOutStream.setDevice(&_minerProcess);

  _minerProcess.start(QIODevice::ReadOnly);

  if (_minerProcess.error() == QProcess::FailedToStart)
  {
    mCCritical(EthMiner) << "failed to start miner for mining unit " << _miningUnitId.toString();

    emit finished();
  }
  else
  {
    mCInfo(EthMiner) << "miner for mining unit " << _miningUnitId.toString() << " started";
  }
}