#ifndef COINSYMBOLSTRINGS_H
#define COINSYMBOLSTRINGS_H

#include "coins_global.h"
#include <MkCore/MStringizer>
#include "coin.h"

class COINS_EXPORT CoinSymbolStrings : public MStringizer<Coin::Symbol>
{
  public:
             CoinSymbolStrings();
    virtual ~CoinSymbolStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif