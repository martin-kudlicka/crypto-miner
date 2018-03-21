#include "coin.h"

#include <QtCore/QHash>
#include "coinnamestrings.h"
#include "coinsymbolstrings.h"

Coin::CoinsInfo Coin::_coinsInfo =
{
  { Name::Aeon,   Symbol::AEON },
  { Name::Monero, Symbol::XMR }
};

Coin::Coin(Name name) : _name(name)
{
  _symbol = _coinsInfo.value(name);
}

Coin::Coin(Symbol symbol) : _symbol(symbol)
{
  _name = _coinsInfo.key(symbol);
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

Coin Coin::fromString(const QString &text, Parts parts /* Part::All */)
{
  auto partsStr = text.split(' ');

  if (parts.testFlag(Part::Name))
  {
    static CoinNameStrings coinNameStrings;

    auto name = coinNameStrings.fromString(partsStr.takeFirst());

    return Coin(name);
  }

  if (parts.testFlag(Part::Symbol))
  {
    static CoinSymbolStrings coinSymbolStrings;

    auto symbol = coinSymbolStrings.fromString(partsStr.takeFirst());

    return Coin(symbol);
  }

  Q_UNREACHABLE();
}

uint qHash(const Coin &key, uint seed /* 0 */)
{
  return qHash(static_cast<uchar>(key.name()), seed) ^ qHash(static_cast<uchar>(key.symbol()), seed);
}