#include "coinsmodel.h"

#include "coinsymbolstrings.h"

CoinsModel::CoinsModel(const Coin::SymbolList *symbols) : _symbols(symbols)
{
}

QVariant CoinsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  static CoinSymbolStrings coinSymbolStrings;

  auto symbol = _symbols->at(index.row());

  auto value = coinSymbolStrings.toString(symbol);

  return value;
}

int CoinsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _symbols->count();
}