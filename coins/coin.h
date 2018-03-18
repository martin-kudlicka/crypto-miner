#ifndef COIN_H
#define COIN_H

#include <QtCore/QString>
#include <QtCore/QList>

namespace Coin
{
  enum Symbol
  {
    AEON,
    XMR
  };

  struct Info
  {
    Symbol  symbol;
    QString name;

    Info(Symbol symbol, const QString &name) : symbol(symbol), name(name)
    {
    }
  };

  using InfoList   = QList<Info>;
  using SymbolList = QList<Symbol>;
}

#endif