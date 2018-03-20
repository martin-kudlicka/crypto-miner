#include "mineroptions.h"

#include <MkCore/MUuidPtr>
#include "../coins/coinnamestrings.h"

Q_DECL_CONSTEXPR QString MinerOptions::Property::Name                   = "name";
Q_DECL_CONSTEXPR QString MinerOptions::Property::Parameters_CoinName    = "parameters/coinName";
Q_DECL_CONSTEXPR QString MinerOptions::Property::Parameters_HwComponent = "parameters/hwComponent";

MinerOptions::MinerOptions(const MUuidPtr &id)
{
  beginGroup("miningUnits");
  beginGroup(id.toString());
  beginGroup("miner");
}

Coin::Name MinerOptions::coinName() const
{
  static CoinNameStrings coinNameStrings;

  auto coinNameStr = value(Property::Parameters_CoinName).toString();

  return coinNameStrings.fromString(coinNameStr);
}

QString MinerOptions::name() const
{
  return value(Property::Name).toString();
}

void MinerOptions::setName(const QString &name)
{
  setValue(Property::Name, name);
}