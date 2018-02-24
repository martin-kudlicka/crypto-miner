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

  return QVariant();
}

QModelIndex MiningModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  return createIndex(row, column);
}

QModelIndex MiningModel::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

int MiningModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return 0;
}