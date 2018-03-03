#include "miningunit.h"

#include "minerplugins.h"
#include "../miners/common/poolcredentials.h"
#include "log.h"

MiningUnit::MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins) : _minerPlugin(Q_NULLPTR), _options(id)
{
  for (auto &minerPlugin : minerPlugins->toList())
  {
    if (minerPlugin->name() == _options.miner())
    {
      _minerPlugin = minerPlugin;
      break;
    }
  }
  Q_ASSERT_X(_minerPlugin, "MiningUnit::MiningUnit", "_minerPlugin");
}

const MiningUnitOptions &MiningUnit::options() const
{
  return _options;
}

void MiningUnit::start()
{
  mCInfo(CryptoMiner) << "mining unit " << _options.id().toString() << " started";

  _worker = _minerPlugin->createWorker(_options.id());

  _worker->setPoolAddress(_options.poolAddress());
  _worker->setPoolCredentials(PoolCredentials(_options.poolUsername(), _options.poolPassword()));

  connect(&*_worker, SIGNAL(resultAccepted()), SLOT(on_worker_resultAccepted()));

  _worker->start();
}

void MiningUnit::stop()
{
  _worker.clear();

  mCInfo(CryptoMiner) << "mining unit " << _options.id().toString() << " stopped";
}

void MiningUnit::on_worker_resultAccepted()
{
  _options.setAcceptedResults(_options.acceptedResults() + 1);
}