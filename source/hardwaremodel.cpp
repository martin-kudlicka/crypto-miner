#include "hardwaremodel.h"

#include "../hardware/hwcomponentstrings.h"
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

Hardware::Component HardwareModel::hwComponent(const QModelIndex &index) const
{
  return _hwComponents.at(index.row());
}

MinerInterfacePtrSet HardwareModel::miners(const QModelIndex &index) const
{
  auto hwComponent = &_hwComponents.at(index.row());

  return _hwComponentMiners.value(*hwComponent);
}

QVariant HardwareModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto hwComponent = &_hwComponents.at(index.row());

  return HwComponentStrings::toString(*hwComponent);
}

Qt::ItemFlags HardwareModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractListModel::flags(index);

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

int HardwareModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _hwComponents.count();
}