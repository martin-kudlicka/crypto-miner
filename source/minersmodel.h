#ifndef MINERMODEL_H
#define MINERMODEL_H

#include <QtCore/QAbstractItemModel>
#include "../miners/minerinterface.h"

class MinerPlugins;

class MinersModel : public QAbstractItemModel
{
  public:
             MinersModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins);
    virtual ~MinersModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    enum Column
    {
      Name,
      Count
    };

    const MinerInterfacePtrSet *_allowedMiners;
          MinerPlugins         *_minerPlugins;

    virtual int           columnCount(const QModelIndex &parent = QModelIndex())                      const Q_DECL_OVERRIDE;
    virtual QVariant      data       (const QModelIndex &index, int role = Qt::DisplayRole)           const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags      (const QModelIndex &index)                                       const Q_DECL_OVERRIDE;
    virtual QModelIndex   index      (int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QModelIndex   parent     (const QModelIndex &child)                                       const Q_DECL_OVERRIDE;
    virtual int           rowCount   (const QModelIndex &parent = QModelIndex())                      const Q_DECL_OVERRIDE;
};

#endif