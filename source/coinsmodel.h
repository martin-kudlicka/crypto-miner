#ifndef COINSMODEL_H
#define COINSMODEL_H

#include <QtCore/QAbstractItemModel>
#include "../coins/coin.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class CoinsModel : public QAbstractItemModel
{
  public:
             CoinsModel(const MinerInterfacePtrSet *allowedMiners, MinerPlugins *minerPlugins);
    virtual ~CoinsModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    Coin                 coin  (const QModelIndex &index) const;
    MinerInterfacePtrSet miners(const QModelIndex &index) const;

  private:
    enum Column
    {
      Name,
      Count
    };

          CoinList                          _coins;
          QHash<Coin, MinerInterfacePtrSet> _coinMiners;
    const MinerInterfacePtrSet             *_allowedMiners;

    virtual int           columnCount(const QModelIndex &parent = QModelIndex())                      const Q_DECL_OVERRIDE;
    virtual QVariant      data       (const QModelIndex &index, int role = Qt::DisplayRole)           const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags      (const QModelIndex &index)                                       const Q_DECL_OVERRIDE;
    virtual QModelIndex   index      (int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QModelIndex   parent     (const QModelIndex &child)                                       const Q_DECL_OVERRIDE;
    virtual int           rowCount   (const QModelIndex &parent = QModelIndex())                      const Q_DECL_OVERRIDE;
};

#endif