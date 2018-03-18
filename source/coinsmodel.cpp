#include "coinsmodel.h"

#include "coinsymbolstrings.h"
#include "minerplugins.h"

CoinsModel::CoinsModel(MinerPlugins *minerPlugins)
{
  for (auto &miner : minerPlugins->toList())
  {
    for (auto symbol : miner->supportedCoins())
    {
      if (!_symbols.contains(symbol))
      {
        _symbols.append(symbol);
      }

      _symbolMiners[symbol].insert(miner);
    }
  }
}

MinerInterfacePtrSet CoinsModel::miners(const QModelIndex &index) const
{
  auto symbol = _symbols.at(index.row());

  return _symbolMiners.value(symbol);
}

QVariant CoinsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  static CoinSymbolStrings coinSymbolStrings;

  auto symbol = _symbols.at(index.row());

  auto value = coinSymbolStrings.toString(symbol);

  return value;
}

Qt::ItemFlags CoinsModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractListModel::flags(index);

  // TODO

  return itemFlags;
}

int CoinsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _symbols.count();
}