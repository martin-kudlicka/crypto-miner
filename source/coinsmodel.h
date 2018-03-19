#ifndef COINSMODEL_H
#define COINSMODEL_H

#include <QtCore/QAbstractListModel>
#include "../coins/coin.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class CoinsModel : public QAbstractListModel
{
  public:
             CoinsModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins);
    virtual ~CoinsModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    Coin::Name           coinName(const QModelIndex &index) const;
    MinerInterfacePtrSet miners  (const QModelIndex &index) const;

  private:
          Coin::NameList                          _coins;
          QHash<Coin::Name, MinerInterfacePtrSet> _coinMiners;
    const MinerInterfacePtrSet                   *_allowedMiners;

    virtual QVariant      data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags   (const QModelIndex &index)                             const Q_DECL_OVERRIDE;
    virtual int           rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif