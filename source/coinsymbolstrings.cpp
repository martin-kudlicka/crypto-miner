#include "coinsymbolstrings.h"

MLazySingleton<CoinSymbolStrings> gCoinSymbolStrings;

CoinSymbolStrings::CoinSymbolStrings()
{
  insert(Coin::Symbol::AEON, "AEON");
  insert(Coin::Symbol::XMR,  "XMR");
}