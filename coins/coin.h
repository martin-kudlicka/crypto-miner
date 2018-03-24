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
      Ethereum,
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
      ETH,
      XMR
    };

    Coin(Name name);
    Coin(Symbol symbol);

    Name    name    ()                        const;
    Symbol  symbol  ()                        const;
    QString toString(Parts parts = Part::All) const;

    bool operator==(const Coin &other) const;

    static Coin fromString(const QString &text, Parts parts = Part::All);

  private:
    using CoinsInfo = QHash<Name, Symbol>;

    Name   _name;
    Symbol _symbol;

    static CoinsInfo _coinsInfo;
};

using CoinList = QList<Coin>;

uint COINS_EXPORT qHash(const Coin &key, uint seed = 0);

#endif