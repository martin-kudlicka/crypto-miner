#ifndef COINS_H
#define COINS_H

#include "coins_global.h"
#include "coin.h"
#include <MkCore/MLazySingleton>
#include <QtCore/QHash>

class COINS_EXPORT Coins
{
  public:
    Coins();

    Coin::Symbol symbol      (Coin::Name coinName) const;
    QString      toFullString(Coin::Name coinName) const;

  private:
    QHash<Coin::Name, Coin::Symbol> _coinsInfo;
};

extern MLazySingleton<Coins> gCoins;

#endif