#ifndef MINERXMRSTAKWIN64_H
#define MINERXMRSTAKWIN64_H

#include "../minerinterface.h"

class MinerXmrStakWin64 : public MinerInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_MINERINTERFACE)
  Q_INTERFACES(MinerInterface)

  private:
    virtual ~MinerXmrStakWin64() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    virtual MinerWorkerInterfaceSPtr          createWorker     (const MUuidPtr &id) const Q_DECL_OVERRIDE;
    virtual QString                           name             ()                   const Q_DECL_OVERRIDE;
    virtual MOperatingSystemVersion::Platform platform         ()                   const Q_DECL_OVERRIDE;
    virtual Coin::NameList                    supportedCoins   ()                   const Q_DECL_OVERRIDE;
    virtual Hardware::ComponentList           supportedHardware()                   const Q_DECL_OVERRIDE;
};


#endif