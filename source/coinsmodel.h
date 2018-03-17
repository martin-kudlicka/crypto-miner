#ifndef COINSMODEL_H
#define COINSMODEL_H

#include <QtCore/QAbstractListModel>
#include "../coins/coindefs.h"

class CoinsModel : public QAbstractListModel
{
  public:
             CoinsModel(const Coin::SymbolList *symbols);
    virtual ~CoinsModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const Coin::SymbolList *_symbols;

    virtual QVariant data    (const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual int      rowCount(const QModelIndex &parent = QModelIndex())            const Q_DECL_OVERRIDE;
};

#endif