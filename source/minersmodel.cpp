#include "minersmodel.h"

#include "minerplugins.h"

MinersModel::MinersModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins) : _allowedMiners(allowedMiners), _minerPlugins(minerPlugins)
{
}

int MinersModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return Column::Count;
}

QVariant MinersModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto minerPlugin = _minerPlugins->toList().at(index.row());

  switch (index.column())
  {
    case Column::Name:
      return minerPlugin->name();
    default:
      Q_ASSERT_X(false, "MinersModel::data", "switch (index.column())");
  }

  return QVariant();
}

Qt::ItemFlags MinersModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractItemModel::flags(index);

  if (!_allowedMiners->isEmpty())
  {
    auto minerPlugin = _minerPlugins->toList().at(index.row());
    if (!_allowedMiners->contains(minerPlugin))
    {
      itemFlags &= ~Qt::ItemIsEnabled;
    }
  }

  return itemFlags;
}

QVariant MinersModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
  {
    return QVariant();
  }

  switch (section)
  {
    case Column::Name:
      return tr("Miner");
    default:
      Q_ASSERT_X(false, "MinersModel::headerData", "switch (section)");
  }

  return QVariant();
}

QModelIndex MinersModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return QModelIndex();
  }

  return createIndex(row, column);
}

QModelIndex MinersModel::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

int MinersModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return _minerPlugins->toList().count();
}