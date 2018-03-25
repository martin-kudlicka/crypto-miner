#include "miningmodel.h"

#include <QtGui/QIcon>

MiningModel::MiningModel(MinerPlugins *minerPlugins) : _miningUnits(minerPlugins, this)
{
}

MUuidPtr MiningModel::id(const QModelIndex &index) const
{
  return index.internalId();
}

void MiningModel::insert(const MUuidPtr &id)
{
  auto row = _miningUnits.index(id);

  insertRow(row);
}

MiningUnitSPtr MiningModel::miningUnit(int row)
{
  auto index2 = index(row, 0);

  return miningUnit(index2);
}

MiningUnitSPtr MiningModel::miningUnit(const MUuidPtr &id)
{
  return _miningUnits.get(id);
}

MiningUnitSPtr MiningModel::miningUnit(const QModelIndex &index)
{
  return _miningUnits.get(index.internalId());
}

void MiningModel::remove(const QModelIndex &index)
{
  removeRow(index.row());
}

void MiningModel::setDataChanged(const MUuidPtr &id, Column column)
{
  auto row    = _miningUnits.index(id);
  auto index2 = index(row, static_cast<int>(column));
  emit dataChanged(index2, index2);
}

int MiningModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _miningUnits.count();
}

int MiningModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return static_cast<int>(Column::Count);
}

QVariant MiningModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole && role != Qt::DecorationRole)
  {
    return QVariant();
  }

  auto miningUnit = const_cast<MiningUnits *>(&_miningUnits)->get(index.internalId());
  if (!miningUnit)
  {
    return QVariant();
  }

  switch (role)
  {
    case Qt::DisplayRole:
      switch (index.column())
      {
        case Column::Miner:
          return miningUnit->options().miner().name();
        case Column::HwComponent:
          return miningUnit->options().miner().hwComponent().toString();
        case Column::HashRate:
          {
            auto hashRate = miningUnit->sessionStatistics().hashRate;
            QString suffix;
            auto precision = 1;
            if (hashRate > 1000000)
            {
              hashRate /= 1000000;
              suffix    = " M";
              precision = 2;
            }
            else if (hashRate > 1000)
            {
              hashRate /= 1000;
              suffix    = " K";
              precision = 2;
            }

            return QString::number(hashRate, 'f', precision) + suffix;
          }
        case Column::Results:
          return miningUnit->sessionStatistics().results;
      }
      break;
    case Qt::DecorationRole:
      switch (index.column())
      {
        case Column::Status:
          return miningUnit->isRunning() ? QIcon(":/resources/images/status/running.png") : QIcon(":/resources/images/status/stopped.png");
      }
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
    case Column::HwComponent:
      return tr("HW");
    case Column::HashRate:
      return "H/s";
    case Column::Results:
      return tr("Results");
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

bool MiningModel::removeRows(int row, int count, const QModelIndex &parent /* QModelIndex() */)
{
  beginRemoveRows(parent, row, row + count - 1);

  _miningUnits.removeIndex(row);

  endRemoveRows();

  return true;
}