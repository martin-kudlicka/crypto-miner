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

Coin MinerOptions::coin() const
{
  auto coinNameStr = value(Property::Parameters_CoinName).toString();

  return Coin::fromString(coinNameStr, Coin::Part::Name);
}

HwComponent MinerOptions::hwComponent() const
{
  auto hwComponentStr = value(Property::Parameters_HwComponent).toString();

  // TODO

  return HwComponent(HwComponent::Company::Any, HwComponent::Type::Cpu);
}

QString MinerOptions::name() const
{
  return value(Property::Name).toString();
}

void MinerOptions::setName(const QString &name)
{
  setValue(Property::Name, name);
}