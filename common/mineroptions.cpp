#include "mineroptions.h"

#include <MkCore/MUuidPtr>

Q_DECL_CONSTEXPR QString MinerOptions::Property::Name                   = "name";
Q_DECL_CONSTEXPR QString MinerOptions::Property::Parameters_CoinName    = "parameters/coinName";
Q_DECL_CONSTEXPR QString MinerOptions::Property::Parameters_HwComponent = "parameters/hwComponent";

MinerOptions::MinerOptions(const MUuidPtr &id)
{
  beginGroup("miningUnits");
  beginGroup(id.toString());
  beginGroup("miner");
}

QString MinerOptions::coinName() const
{
  return value(Property::Parameters_CoinName).toString();
}

QString MinerOptions::name() const
{
  return value(Property::Name).toString();
}

void MinerOptions::setName(const QString &name)
{
  setValue(Property::Name, name);
}