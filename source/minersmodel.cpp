#include "minersmodel.h"

#include "minerplugins.h"

MinersModel::MinersModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins) : _allowedMiners(allowedMiners), _minerPlugins(minerPlugins)
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

Qt::ItemFlags MinersModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractListModel::flags(index);

  if (!_allowedMiners->isEmpty())
  {
    auto minerPlugin = _minerPlugins->toList().at(index.row());
    if (!_allowedMiners->contains(minerPlugin))
    {
      itemFlags &= ~Qt::ItemIsEnabled;
    }
  }

  return itemFlags;
}

int MinersModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _minerPlugins->toList().count();
}