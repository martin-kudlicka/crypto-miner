#include "miningunits.h"

MiningUnits::MiningUnits(MinerPlugins *minerPlugins, MiningModel *miningModel) : _minerPlugins(minerPlugins), _miningModel(miningModel)
{
  _settings.beginGroup("miningUnits");
}

MiningUnits::~MiningUnits()
{
  for (auto &miningUnit : _miningUnits)
  {
    if (miningUnit->isRunning())
    {
      miningUnit.clear();
    }
  }
}

quintptr MiningUnits::count() const
{
  return _settings.childGroups().count();
}

MiningUnitSPtr MiningUnits::get(const MUuidPtr &id)
{
  if (_miningUnits.contains(id))
  {
    if (!_miningUnits[id].toWeakRef().toStrongRef())
    {
      // under destruction
      return Q_NULLPTR;
    }

    return _miningUnits[id];
  }

  auto rule = _miningUnits.insert(id, MiningUnitSPtr(new MiningUnit(id, _minerPlugins, _miningModel)));

  return *rule;
}

MUuidPtr MiningUnits::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

quintptr MiningUnits::index(const MUuidPtr &id) const
{
  quintptr index2 = 0;

  for (const auto &id2 : _settings.childGroups())
  {
    if (id2 == id.toString())
    {
      return index2;
    }

    ++index2;
  }

  Q_UNREACHABLE();
  return -1;
}

bool MiningUnits::isEmpty() const
{
  return count() == 0;
}

void MiningUnits::removeIndex(quintptr index)
{
  auto id2 = id(index);

  _miningUnits.remove(id2);
  _settings.remove(id2.toString());
}