#ifndef HARDWAREMODEL_H
#define HARDWAREMODEL_H

#include <QtCore/QAbstractListModel>
#include "../miners/specification.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class HardwareModel : public QAbstractListModel
{
  public:
             HardwareModel(const HwComponentList *hwComponents, MinerPlugins *minerPlugins);
    virtual ~HardwareModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const HwComponentList                         *_hwComponents;
          QHash<HwComponent, MinerInterfacePtrSet> _hwComponentMiners;

    virtual QVariant data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual int      rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif