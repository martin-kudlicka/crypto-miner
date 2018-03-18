#include "coinsmodel.h"

#include "coinsymbolstrings.h"
#include "minerplugins.h"

CoinsModel::CoinsModel(const Coin::SymbolList *symbols, MinerPlugins *minerPlugins) : _symbols(symbols)
{
  for (auto &miner : minerPlugins->toList())
  {
    for (auto symbol : miner->supportedCoins())
    {
      _symbolMiners[symbol].insert(miner);
    }
  }
}

MinerInterfacePtrSet CoinsModel::miners(const QModelIndex &index) const
{
  auto symbol = _symbols->at(index.row());

  return _symbolMiners.value(symbol);
}

QVariant CoinsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  static CoinSymbolStrings coinSymbolStrings;

  auto symbol = _symbols->at(index.row());

  auto value = coinSymbolStrings.toString(symbol);

  return value;
}

int CoinsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return _symbols->count();
}