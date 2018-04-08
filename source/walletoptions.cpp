#include "walletoptions.h"

#include "../coins/coin.h"

WalletOptions::WalletOptions()
{
  beginGroup("wallets");
}

QString WalletOptions::address(const Coin &coin) const
{
  return value(addressProperty(coin)).toString();
}

QString WalletOptions::addressProperty(const Coin &coin) const
{
  return coin.toString(Coin::Part::Name) + "/address";
}