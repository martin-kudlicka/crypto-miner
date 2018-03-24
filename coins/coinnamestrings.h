#ifndef COINNAMESTRINGS_H
#define COINNAMESTRINGS_H

#include "coins_global.h"
#include <MkCore/MStringizer>
#include "coin.h"

class COINS_EXPORT CoinNameStrings : public MStringizer<Coin::Name>
{
  public:
             CoinNameStrings();
    virtual ~CoinNameStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif