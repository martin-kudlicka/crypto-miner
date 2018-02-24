#include "miningmodel.h"

int MiningModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return static_cast<int>(Column::Count);
}

QVariant MiningModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  // TODO

  return QVariant();
}

QModelIndex MiningModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  if (_miningUnits.isEmpty())
  {
    return createIndex(row, column);
  }

  return createIndex(row, column, _miningUnits.id(row));
}

QModelIndex MiningModel::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

int MiningModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _miningUnits.count();
}