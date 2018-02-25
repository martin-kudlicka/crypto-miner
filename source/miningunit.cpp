#include "miningunit.h"

#include "minerplugins.h"
#include "../miners/common/poolcredentials.h"

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
  _worker = _minerPlugin->createWorker();

  _worker->setPoolAddress(_options.poolAddress());
  _worker->setPoolCredentials(PoolCredentials(_options.poolUsername(), _options.poolPassword()));
}