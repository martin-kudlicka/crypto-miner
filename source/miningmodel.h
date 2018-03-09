#ifndef MININGMODEL_H
#define MININGMODEL_H

#include <QtCore/QAbstractItemModel>
#include "miningunits.h"

class MiningModel : public QAbstractItemModel
{
  public:
    enum class Column
    {
      Status,
      Miner,
      HashRate,
      Results,
      Count
    };

             MiningModel(MinerPlugins *minerPlugins);
    virtual ~MiningModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    MUuidPtr       id            (const QModelIndex &index) const;
    void           insert        (const MUuidPtr &id);
    MiningUnitSPtr miningUnit    (int row);
    MiningUnitSPtr miningUnit    (const MUuidPtr &id);
    MiningUnitSPtr miningUnit    (const QModelIndex &index);
    void           remove        (const QModelIndex &index);
    void           setDataChanged(const MUuidPtr &id, Column column);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

  private:
    MiningUnits _miningUnits;

    virtual int         columnCount(const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
    virtual QVariant    data       (const QModelIndex &index, int role = Qt::DisplayRole)                 const Q_DECL_OVERRIDE;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent = QModelIndex())       const Q_DECL_OVERRIDE;
    virtual bool        insertRows (int row, int count, const QModelIndex &parent = QModelIndex())              Q_DECL_OVERRIDE;
    virtual QModelIndex parent     (const QModelIndex &child)                                             const Q_DECL_OVERRIDE;
    virtual bool        removeRows (int row, int count, const QModelIndex &parent = QModelIndex())              Q_DECL_OVERRIDE;
};

#endif