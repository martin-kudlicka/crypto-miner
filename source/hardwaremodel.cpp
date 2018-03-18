#include "hardwaremodel.h"

#include "companystrings.h"
#include "hardwarestrings.h"
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

  static CompanyStrings companyStrings;
  static HardwareStrings hardwareStrings;

  auto hwComponent = &_hwComponents.at(index.row());

  QString value;
  if (hwComponent->company != Company::Any)
  {
    value.append(companyStrings.toString(hwComponent->company));
    value.append(' ');
  }
  value.append(hardwareStrings.toString(hwComponent->hardware));

  return value;
}

Qt::ItemFlags HardwareModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractListModel::flags(index);

  if (!_allowedMiners->isEmpty())
  {
    auto hwComponent       = &_hwComponents.at(index.row());
    auto hwComponentMiners = _hwComponentMiners.value(*hwComponent);
    if (hwComponentMiners.intersect(*_allowedMiners).isEmpty())
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