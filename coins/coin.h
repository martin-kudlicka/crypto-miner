#ifndef COIN_H
#define COIN_H

#include "coins_global.h"
#include <QtCore/QList>
#include <QtCore/QHash>

class COINS_EXPORT Coin
{
  public:
    enum Name
    {
      Aeon,
      Monero
    };
    enum Symbol
    {
      AEON,
      XMR
    };

    using NameList = QList<Name>;

    Coin();

    Symbol symbol(Name coinName) const;

  private:
    QHash<Name, Symbol> _coinsInfo;
};

#endif