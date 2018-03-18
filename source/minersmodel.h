#ifndef MINERMODEL_H
#define MINERMODEL_H

#include <QtCore/QAbstractListModel>
#include "../miners/minerinterface.h"

class MinerPlugins;

class MinersModel : public QAbstractListModel
{
  public:
             MinersModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins);
    virtual ~MinersModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const MinerInterfacePtrSet *_allowedMiners;
          MinerPlugins         *_minerPlugins;

    virtual QVariant      data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags   (const QModelIndex &index)                             const Q_DECL_OVERRIDE;
    virtual int           rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif