#include "coins.h"

#include "coinnamestrings.h"

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

QString Coins::toFullString(Coin::Name coinName) const
{
  static CoinNameStrings coinNameStrings;

  QString text = coinNameStrings.toString(coinName);
  text.append(' ');

  auto coinSymbolStr = _coinSymbolStrings.toString(symbol(coinName));
  text.append(coinSymbolStr);

  return text;
}

QString Coins::toString(Coin::Name coinName) const
{
  static CoinNameStrings coinNameStrings;

  return coinNameStrings.toString(coinName);
}

QString Coins::toString(Coin::Symbol coinSymbol) const
{
  return _coinSymbolStrings.toString(coinSymbol);
}