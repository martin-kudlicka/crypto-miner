#include "miningunit.h"

#include "minerplugins.h"

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