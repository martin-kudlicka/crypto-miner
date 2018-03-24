#ifndef MINERETHMINER_H
#define MINERETHMINER_H

#include "../minerinterface.h"

class MinerEthMiner : public MinerInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_MINERINTERFACE)
  Q_INTERFACES(MinerInterface)

  private:
    virtual ~MinerEthMiner() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    virtual MinerWorkerInterfaceSPtr          createWorker     (const MUuidPtr &id) const Q_DECL_OVERRIDE;
    virtual QString                           name             ()                   const Q_DECL_OVERRIDE;
    virtual MOperatingSystemVersion::Platform platform         ()                   const Q_DECL_OVERRIDE;
    virtual CoinList                          supportedCoins   ()                   const Q_DECL_OVERRIDE;
    virtual HwComponentList                   supportedHardware()                   const Q_DECL_OVERRIDE;
};

#endif