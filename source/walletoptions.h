#ifndef WALLETOPTIONS_H
#define WALLETOPTIONS_H

#include <MkCore/MSettings>

class Coin;

class WalletOptions : public MSettings
{
  public:
             WalletOptions();
    virtual ~WalletOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    QString addressProperty(const Coin &coin) const;
};

#endif