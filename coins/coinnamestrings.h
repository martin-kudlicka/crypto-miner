#ifndef COINNAMESTRINGS_H
#define COINNAMESTRINGS_H

#include <MkCore/MStringizer>
#include "coin.h"

class CoinNameStrings : public MStringizer<Coin::Name>
{
  public:
             CoinNameStrings();
    virtual ~CoinNameStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif