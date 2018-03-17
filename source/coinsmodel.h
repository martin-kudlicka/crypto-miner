#ifndef COINSMODEL_H
#define COINSMODEL_H

#include <QtCore/QAbstractListModel>
#include "../coins/coindefs.h"
#include "../miners/minerinterface.h"

class MinerPlugins;

class CoinsModel : public QAbstractListModel
{
  public:
             CoinsModel(const Coin::SymbolList *symbols, MinerPlugins *minerPlugins);
    virtual ~CoinsModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const Coin::SymbolList                         *_symbols;
          QHash<Coin::Symbol, MinerInterfacePtrSet> _symbolMiners;

    virtual QVariant data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual int      rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif