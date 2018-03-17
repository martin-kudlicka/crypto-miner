#include "hardwaremodel.h"

#include "hardwarestrings.h"

HardwareModel::HardwareModel(const HwComponentList *hwComponents) : _hwComponents(hwComponents)
{
}

QVariant HardwareModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  static HardwareStrings hardwareStrings;

  auto hwComponent = &_hwComponents->at(index.row());

  auto value = hardwareStrings.toString(hwComponent->hardware);

  return value;
}

int HardwareModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _hwComponents->count();
}