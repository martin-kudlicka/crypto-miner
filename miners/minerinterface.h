#ifndef MINERINTERFACE_H
#define MINERINTERFACE_H

#include "minerworkerinterface.h"
#include "specification.h"
#include "../coins/coindefs.h"

class MUuidPtr;

#define IID_MINERINTERFACE "cz.martink.CryptoMiner.MinerInterface"

class MinerInterface : public QObject
{
  Q_OBJECT

  public:
    virtual MinerWorkerInterfaceSPtr createWorker     (const MUuidPtr &id) const = 0;
    virtual QString                  name             ()                   const = 0;
    virtual Coin::SymbolList         supportedCoins   ()                   const = 0;
    virtual HwComponentList          supportedHardware()                   const = 0;

  protected:
    virtual ~MinerInterface() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

Q_DECLARE_INTERFACE(MinerInterface, IID_MINERINTERFACE);

#endif