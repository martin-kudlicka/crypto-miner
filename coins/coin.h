#ifndef COIN_H
#define COIN_H

#include <QtCore/QString>
#include <QtCore/QList>

namespace Coin
{
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
}

#endif