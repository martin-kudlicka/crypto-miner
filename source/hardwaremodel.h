#ifndef HARDWAREMODEL_H
#define HARDWAREMODEL_H

#include <QtCore/QAbstractListModel>
#include "../miners/specification.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class HardwareModel : public QAbstractListModel
{
  public:
             HardwareModel(MinerPlugins *minerPlugins);
    virtual ~HardwareModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    MinerInterfacePtrSet miners(const QModelIndex &index) const;

  private:
    HwComponentList                          _hwComponents;
    QHash<HwComponent, MinerInterfacePtrSet> _hwComponentMiners;

    virtual QVariant      data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags   (const QModelIndex &index)                             const Q_DECL_OVERRIDE;
    virtual int           rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif