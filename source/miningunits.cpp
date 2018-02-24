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

MUuidPtr MiningUnits::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

bool MiningUnits::isEmpty() const
{
  return count() == 0;
}