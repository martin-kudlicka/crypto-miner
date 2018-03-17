#ifndef HARDWAREMODEL_H
#define HARDWAREMODEL_H

#include <QtCore/QAbstractListModel>
#include "../miners/specification.h"

class HardwareModel : public QAbstractListModel
{
  public:
             HardwareModel(const HwComponentList *hwComponents);
    virtual ~HardwareModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const HwComponentList *_hwComponents;

    virtual QVariant data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual int      rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif