#include "coins.h"

MLazySingleton<Coins> gCoins;

Coins::Coins()
{
  _infoList <<
    Coin::Info(Coin::Symbol::AEON, "Aeon") <<
    Coin::Info(Coin::Symbol::XMR,  "Monero");
}

const Coin::InfoList &Coins::infoList() const
{
  return _infoList;
}