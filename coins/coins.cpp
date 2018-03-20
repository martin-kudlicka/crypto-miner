#include "coins.h"

#include "coinnamestrings.h"
#include "coinsymbolstrings.h"

MLazySingleton<Coins> gCoins;

Coins::Coins()
{
  _coinsInfo =
  {
    { Coin::Name::Aeon,   Coin::Symbol::AEON },
    { Coin::Name::Monero, Coin::Symbol::XMR }
  };
}

Coin::Symbol Coins::symbol(Coin::Name coinName) const
{
  return _coinsInfo.value(coinName);
}