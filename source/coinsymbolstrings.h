#ifndef COINSYMBOLSTRINGS_H
#define COINSYMBOLSTRINGS_H

#include <MkCore/MStringizer>
#include "../coins/coin.h"
#include <MkCore/MLazySingleton>

class CoinSymbolStrings : public MStringizer<Coin::Symbol>
{
  public:
             CoinSymbolStrings();
    virtual ~CoinSymbolStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

extern MLazySingleton<CoinSymbolStrings> gCoinSymbolStrings;

#endif