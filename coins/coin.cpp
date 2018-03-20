#include "coin.h"

Coin::Coin()
{
  _coinsInfo =
  {
    { Coin::Name::Aeon,   Coin::Symbol::AEON },
    { Coin::Name::Monero, Coin::Symbol::XMR }
  };
}

Coin::Symbol Coin::symbol(Name coinName) const
{
  return _coinsInfo.value(coinName);
}