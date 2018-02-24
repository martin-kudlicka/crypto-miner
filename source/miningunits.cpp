#include "miningunits.h"

Q_DECL_CONSTEXPR QString MiningUnits::Property::Group = "miningUnits";

MiningUnits::MiningUnits()
{
  _settings.beginGroup(Property::Group);
}

quintptr MiningUnits::count() const
{
  return _settings.childGroups().count();
}

const MiningUnitSPtr &MiningUnits::get(const MUuidPtr &id)
{
  if (_miningUnits.contains(id))
  {
    return _miningUnits[id];
  }

  auto rule = _miningUnits.insert(id, MiningUnitSPtr(new MiningUnit(id)));

  return *rule;
}

MUuidPtr MiningUnits::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

bool MiningUnits::isEmpty() const
{
  return count() == 0;
}