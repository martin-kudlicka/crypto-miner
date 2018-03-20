#ifndef COINFULLSTRINGS_H
#define COINFULLSTRINGS_H

#include "coins_global.h"
#include "coin.h"

class COINS_EXPORT CoinFullStrings
{
  public:
    static QString toString(Coin::Name coinName);
};

#endif