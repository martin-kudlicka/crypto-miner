#include "coinfullstrings.h"

#include "coinnamestrings.h"
#include "coinsymbolstrings.h"
#include "coin.h"

QString CoinFullStrings::toString(Coin::Name coinName)
{
  static CoinNameStrings coinNameStrings;

  QString text = coinNameStrings.toString(coinName);
  text.append(' ');

  static Coin coin;
  static CoinSymbolStrings coinSymbolStrings;

  auto coinSymbolStr = coinSymbolStrings.toString(coin.symbol(coinName));
  text.append(coinSymbolStr);

  return text;
}