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