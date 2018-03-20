#ifndef MINEROPTIONS_H
#define MINEROPTIONS_H

#include <MkCore/MSettings>
#include "../coins/coin.h"

class MUuidPtr;

class MinerOptions : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Name;
      static Q_DECL_CONSTEXPR QString Parameters_CoinName;
      static Q_DECL_CONSTEXPR QString Parameters_HwComponent;
    };

             MinerOptions(const MUuidPtr &id);
    virtual ~MinerOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    Coin::Name coinName() const;
    QString    name    () const;
    void       setName (const QString &name);
};

#endif