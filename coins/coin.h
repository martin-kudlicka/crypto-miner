#ifndef COIN_H
#define COIN_H

#include "coins_global.h"
#include <QtCore/QList>

class COINS_EXPORT Coin
{
  public:
    enum Name
    {
      Aeon,
      Monero
    };
    enum class Part
    {
      None,
      Name,
      Symbol,
      All = Name | Symbol
    };
    Q_DECLARE_FLAGS(Parts, Part)
    enum Symbol
    {
      AEON,
      XMR
    };

    Coin(Name name);

    Name    name    ()                        const;
    Symbol  symbol  ()                        const;
    QString toString(Parts parts = Part::All) const;

    bool operator==(const Coin &other) const;

  private:
    Name   _name;
    Symbol _symbol;
};

using CoinList = QList<Coin>;

uint COINS_EXPORT qHash(const Coin &key, uint seed = 0);

#endif