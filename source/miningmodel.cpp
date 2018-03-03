#include "miningmodel.h"

MiningModel::MiningModel(MinerPlugins *minerPlugins) : _miningUnits(minerPlugins)
{
}

void MiningModel::insert(const MUuidPtr &id)
{
  auto row = _miningUnits.index(id);

  insertRow(row);
}

MiningUnitSPtr MiningModel::miningUnit(const QModelIndex &index)
{
  return _miningUnits.get(index.internalId());
}

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

  auto miningUnit = const_cast<MiningUnits *>(&_miningUnits)->get(index.internalId());

  switch (index.column())
  {
    case Column::Miner:
      return miningUnit->options().miner();
    case Column::TotalResults:
      return miningUnit->options().acceptedResults();
  }

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

bool MiningModel::insertRows(int row, int count, const QModelIndex &parent /* QModelIndex() */)
{
  beginInsertRows(parent, row, row + count - 1);
  // already added
  endInsertRows();

  return true;
}

QModelIndex MiningModel::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

int MiningModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _miningUnits.count();
}