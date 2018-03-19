#ifndef MINERXMRSTAKCPUNOTLS_H
#define MINERXMRSTAKCPUNOTLS_H

#include "../minerinterface.h"

class MinerXmrStakCpuNoTls : public MinerInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_MINERINTERFACE)
  Q_INTERFACES(MinerInterface)

  private:
    virtual ~MinerXmrStakCpuNoTls() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    virtual MinerWorkerInterfaceSPtr          createWorker     (const MUuidPtr &id) const Q_DECL_OVERRIDE;
    virtual QString                           name             ()                   const Q_DECL_OVERRIDE;
    virtual MOperatingSystemVersion::Platform platform         ()                   const Q_DECL_OVERRIDE;
    virtual Coin::NameList                    supportedCoins   ()                   const Q_DECL_OVERRIDE;
    virtual HwComponentList                   supportedHardware()                   const Q_DECL_OVERRIDE;
};

#endif