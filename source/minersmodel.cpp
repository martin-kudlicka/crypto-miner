#include "minersmodel.h"

#include "minerplugins.h"

MinersModel::MinersModel(MinerPlugins *minerPlugins) : _minerPlugins(minerPlugins)
{
}

QVariant MinersModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto minerPlugin = _minerPlugins->toList().at(index.row());

  return minerPlugin->name();
}

int MinersModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _minerPlugins->toList().count();
}