#include "hardwaremodel.h"

#include "minerplugins.h"

HardwareModel::HardwareModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins) : _allowedMiners(allowedMiners)
{
  for (auto &miner : minerPlugins->toList())
  {
    for (const auto &hwComponent : miner->supportedHardware())
    {
      if (!_hwComponents.contains(hwComponent))
      {
        _hwComponents.append(hwComponent);
      }

      _hwComponentMiners[hwComponent].insert(miner);
    }
  }
}

HwComponent HardwareModel::hwComponent(const QModelIndex &index) const
{
  return _hwComponents.at(index.row());
}

MinerInterfacePtrSet HardwareModel::miners(const QModelIndex &index) const
{
  auto hwComponent = &_hwComponents.at(index.row());

  return _hwComponentMiners.value(*hwComponent);
}

int HardwareModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return Column::Count;
}

QVariant HardwareModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto hwComponent = &_hwComponents.at(index.row());

  switch (index.column())
  {
    case Column::Name:
      return hwComponent->toString();
    default:
      Q_ASSERT_X(false, "HardwareModel::data", "switch (index.column())");
  }

  return QVariant();
}

Qt::ItemFlags HardwareModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractItemModel::flags(index);

  if (!_allowedMiners->isEmpty())
  {
    auto hwComponent       = &_hwComponents.at(index.row());
    auto hwComponentMiners = _hwComponentMiners.value(*hwComponent);
    if (!hwComponentMiners.intersects(*_allowedMiners))
    {
      itemFlags &= ~Qt::ItemIsEnabled;
    }
  }

  return itemFlags;
}

QVariant HardwareModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
  {
    return QVariant();
  }

  switch (section)
  {
    case Column::Name:
      return tr("Hardware");
    default:
      Q_ASSERT_X(false, "HardwareModel::headerData", "switch (section)");
  }

  return QVariant();
}

QModelIndex HardwareModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return QModelIndex();
  }

  return createIndex(row, column);
}

QModelIndex HardwareModel::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

int HardwareModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return _hwComponents.count();
}