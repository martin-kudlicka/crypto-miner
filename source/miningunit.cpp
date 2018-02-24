#include "miningunit.h"

MiningUnit::MiningUnit(const MUuidPtr &id) : _options(id)
{
}

const MiningUnitOptions &MiningUnit::options() const
{
  return _options;
}