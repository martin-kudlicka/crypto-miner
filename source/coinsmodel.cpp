#include "coinsmodel.h"

#include "../common/coinsymbolstrings.h"
#include "minerplugins.h"

CoinsModel::CoinsModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins) : _allowedMiners(allowedMiners)
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

Coin::Symbol CoinsModel::coinSymbol(const QModelIndex &index) const
{
  return _symbols.at(index.row());
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

  auto symbol = _symbols.at(index.row());

  return gCoinSymbolStrings->toString(symbol);
}

Qt::ItemFlags CoinsModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractListModel::flags(index);

  if (!_allowedMiners->isEmpty())
  {
    auto symbol       = _symbols.at(index.row());
    auto symbolMiners = _symbolMiners.value(symbol);
    if (!symbolMiners.intersects(*_allowedMiners))
    {
      itemFlags &= ~Qt::ItemIsEnabled;
    }
  }

  return itemFlags;
}

int CoinsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _symbols.count();
}