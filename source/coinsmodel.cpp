#include "coinsmodel.h"

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

Coin CoinsModel::coin(const QModelIndex &index) const
{
  return _coins.at(index.row());
}

MinerInterfacePtrSet CoinsModel::miners(const QModelIndex &index) const
{
  auto coin = _coins.at(index.row());

  return _coinMiners.value(coin);
}

int CoinsModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return Column::Count;
}

QVariant CoinsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto coin = _coins.at(index.row());

  switch (index.column())
  {
    case Column::Name:
      return coin.toString();
    default:
      Q_ASSERT_X(false, "CoinsModel::data", "switch (index.column())");
  }

  return QVariant();
}

Qt::ItemFlags CoinsModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractItemModel::flags(index);

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

QModelIndex CoinsModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return QModelIndex();
  }

  return createIndex(row, column);
}

QModelIndex CoinsModel::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

int CoinsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return _coins.count();
}