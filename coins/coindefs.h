#ifndef COINDEFS_H
#define COINDEFS_H

namespace Coin
{
  struct Info
  {
    QString symbol;
    QString name;
  };

  static Q_DECL_CONSTEXPR Info Monero = { "XMR", "Monero" };
}

using CoinInfoList = QList<Coin::Info>;

#endif