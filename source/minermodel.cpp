#include "minermodel.h"

#include "minerplugins.h"

MinerModel::MinerModel(MinerPlugins *minerPlugins) : _minerPlugins(minerPlugins)
{
}

QVariant MinerModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto minerPlugin = _minerPlugins->toList().at(index.row());

  return minerPlugin->name();
}

int MinerModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _minerPlugins->toList().count();
}