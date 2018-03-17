#ifndef MINERMODEL_H
#define MINERMODEL_H

#include <QtCore/QAbstractListModel>

class MinerPlugins;

class MinerModel : public QAbstractListModel
{
  public:
             MinerModel(MinerPlugins *minerPlugins);
    virtual ~MinerModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    MinerPlugins *_minerPlugins;

    virtual QVariant data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual int      rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif