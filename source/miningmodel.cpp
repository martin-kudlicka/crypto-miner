#include "miningmodel.h"

MiningModel::MiningModel(MinerPlugins *minerPlugins) : _miningUnits(minerPlugins, this)
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

void MiningModel::setDataChanged(const MUuidPtr &id, Column column)
{
  auto row    = _miningUnits.index(id);
  auto index2 = index(row, static_cast<int>(column));
  emit dataChanged(index2, index2);
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
    case Column::HashRate:
      return QString::number(miningUnit->sessionStatistics().hashRate, 'f', 1) + " H/s";
    case Column::Results:
      return miningUnit->sessionStatistics().results;
  }

  return QVariant();
}

QVariant MiningModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
  {
    return QVariant();
  }

  switch (section)
  {
    case Column::Miner:
      return tr("Miner");
    case Column::HashRate:
      return "H/s";
    case Column::Results:
      return tr("Results");
  }

  Q_UNREACHABLE();
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