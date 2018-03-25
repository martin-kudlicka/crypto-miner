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

void MinerWorkerEthMiner::start()
{
  // TODO

  _stdOutStream.setDevice(&_minerProcess);

  connect(&_minerProcess, &QProcess::readyReadStandardOutput, this, &MinerWorkerEthMiner::on_minerProcess_readyReadStandardOutput);

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

void MinerWorkerEthMiner::on_minerProcess_readyReadStandardOutput()
{
  forever
  {
    _stdOutLastLine += _stdOutStream.readLine();
    if (_stdOutStream.atEnd())
    {
      break;
    }

    emit outputLine(_stdOutLastLine);
    appendOutput(_stdOutLastLine);

    // TODO

    _stdOutLastLine.clear();
  }
}