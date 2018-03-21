#include "coin.h"

#include <QtCore/QHash>
#include "coinnamestrings.h"
#include "coinsymbolstrings.h"

Coin::Coin(Name name) : _name(name)
{
  static QHash<Name, Symbol> coinsInfo =
  {
    { Name::Aeon,   Symbol::AEON },
    { Name::Monero, Symbol::XMR }
  };

  _symbol = coinsInfo.value(name);
}

Coin::Name Coin::name() const
{
  return _name;
}

Coin::Symbol Coin::symbol() const
{
  return _symbol;
}

QString Coin::toString(Parts parts /* Part::All */) const
{
  QString text;

  if (parts.testFlag(Part::Name))
  {
    static CoinNameStrings coinNameStrings;

    text = coinNameStrings.toString(_name);
  }

  if (parts.testFlag(Part::Symbol))
  {
    if (!text.isEmpty())
    {
      text.append(' ');
    }

    static CoinSymbolStrings coinSymbolStrings;

    text.append(coinSymbolStrings.toString(_symbol));
  }

  return text;
}

bool Coin::operator==(const Coin &other) const
{
  return other._name == _name && other._symbol == _symbol;
}

uint qHash(const Coin &key, uint seed /* 0 */)
{
  return qHash(static_cast<uchar>(key.name()), seed) ^ qHash(static_cast<uchar>(key.symbol()), seed);
}