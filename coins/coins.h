#pragma once

#include "coins_global.h"
#include "coin.h"

class COINS_EXPORT Coins
{
  public:
    Coins();

    const Coin::InfoList &infoList() const;

  private:
    Coin::InfoList _infoList;
};
