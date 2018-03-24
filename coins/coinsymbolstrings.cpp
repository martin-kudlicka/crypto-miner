#include "coinsymbolstrings.h"

CoinSymbolStrings::CoinSymbolStrings()
{
  insert(Coin::Symbol::AEON, "AEON");
  insert(Coin::Symbol::ETH,  "ETH");
  insert(Coin::Symbol::XMR,  "XMR");
}