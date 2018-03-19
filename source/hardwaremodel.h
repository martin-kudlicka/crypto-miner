#ifndef HARDWAREMODEL_H
#define HARDWAREMODEL_H

#include <QtCore/QAbstractListModel>
#include "../hardware/hardware.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class HardwareModel : public QAbstractListModel
{
  public:
             HardwareModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins);
    virtual ~HardwareModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    Hardware::Component  hwComponent(const QModelIndex &index) const;
    MinerInterfacePtrSet miners     (const QModelIndex &index) const;

  private:
          Hardware::ComponentList                          _hwComponents;
          QHash<Hardware::Component, MinerInterfacePtrSet> _hwComponentMiners;
    const MinerInterfacePtrSet                            *_allowedMiners;

    virtual QVariant      data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags   (const QModelIndex &index)                             const Q_DECL_OVERRIDE;
    virtual int           rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif