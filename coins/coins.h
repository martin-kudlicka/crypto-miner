#ifndef COINS_H
#define COINS_H

#include "coins_global.h"
#include "coin.h"
#include <MkCore/MLazySingleton>
#include <QtCore/QHash>
#include "coinsymbolstrings.h"

class COINS_EXPORT Coins
{
  public:
    Coins();

    Coin::Symbol symbol        (Coin::Name coinName)     const;
    QString      toFullString  (Coin::Name coinName)     const;
    QString      toString      (Coin::Name coinName)     const;
    QString      toString      (Coin::Symbol coinSymbol) const;

  private:
    CoinSymbolStrings               _coinSymbolStrings;
    QHash<Coin::Name, Coin::Symbol> _coinsInfo;
};

extern MLazySingleton<Coins> gCoins;

#endif