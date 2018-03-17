#include "hardwaremodel.h"

#include "companystrings.h"
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

  static CompanyStrings companyStrings;
  static HardwareStrings hardwareStrings;

  auto hwComponent = &_hwComponents->at(index.row());

  QString value;
  if (hwComponent->company != Company::Any)
  {
    value.append(companyStrings.toString(hwComponent->company));
    value.append(' ');
  }
  value.append(hardwareStrings.toString(hwComponent->hardware));

  return value;
}

int HardwareModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _hwComponents->count();
}