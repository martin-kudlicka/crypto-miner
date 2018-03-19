#include "coinsmodel.h"

#include "../coins/coins.h"
#include "minerplugins.h"

CoinsModel::CoinsModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins) : _allowedMiners(allowedMiners)
{
  for (auto &miner : minerPlugins->toList())
  {
    for (auto coin : miner->supportedCoins())
    {
      if (!_coins.contains(coin))
      {
        _coins.append(coin);
      }

      _coinMiners[coin].insert(miner);
    }
  }
}

Coin::Name CoinsModel::coinName(const QModelIndex &index) const
{
  return _coins.at(index.row());
}

MinerInterfacePtrSet CoinsModel::miners(const QModelIndex &index) const
{
  auto coin = _coins.at(index.row());

  return _coinMiners.value(coin);
}

QVariant CoinsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto coin = _coins.at(index.row());

  return gCoins->toFullString(coin);
}

Qt::ItemFlags CoinsModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractListModel::flags(index);

  if (!_allowedMiners->isEmpty())
  {
    auto coin       = _coins.at(index.row());
    auto coinMiners = _coinMiners.value(coin);
    if (!coinMiners.intersects(*_allowedMiners))
    {
      itemFlags &= ~Qt::ItemIsEnabled;
    }
  }

  return itemFlags;
}

int CoinsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _coins.count();
}