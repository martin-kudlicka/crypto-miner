#include "coinfullstrings.h"

#include "coinnamestrings.h"
#include "coinsymbolstrings.h"
#include "coins.h"

QString CoinFullStrings::toString(Coin::Name coinName)
{
  static CoinNameStrings coinNameStrings;

  QString text = coinNameStrings.toString(coinName);
  text.append(' ');

  static CoinSymbolStrings coinSymbolStrings;

  auto coinSymbolStr = coinSymbolStrings.toString(gCoins->symbol(coinName));
  text.append(coinSymbolStr);

  return text;
}