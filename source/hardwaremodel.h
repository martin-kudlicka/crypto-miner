#ifndef HARDWAREMODEL_H
#define HARDWAREMODEL_H

#include <QtCore/QAbstractItemModel>
#include "../hardware/hwcomponent.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class HardwareModel : public QAbstractItemModel
{
  public:
             HardwareModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins);
    virtual ~HardwareModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    HwComponent          hwComponent(const QModelIndex &index) const;
    MinerInterfacePtrSet miners     (const QModelIndex &index) const;

  private:
    enum Column
    {
      Name,
      Count
    };

          HwComponentList                          _hwComponents;
          QHash<HwComponent, MinerInterfacePtrSet> _hwComponentMiners;
    const MinerInterfacePtrSet                    *_allowedMiners;

    virtual int           columnCount(const QModelIndex &parent = QModelIndex())                      const Q_DECL_OVERRIDE;
    virtual QVariant      data       (const QModelIndex &index, int role = Qt::DisplayRole)           const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags      (const QModelIndex &index)                                       const Q_DECL_OVERRIDE;
    virtual QModelIndex   index      (int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QModelIndex   parent     (const QModelIndex &child)                                       const Q_DECL_OVERRIDE;
    virtual int           rowCount   (const QModelIndex &parent = QModelIndex())                      const Q_DECL_OVERRIDE;
};

#endif