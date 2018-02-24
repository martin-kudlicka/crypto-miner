#ifndef MINERXMRSTAKCPU_H
#define MINERXMRSTAKCPU_H

#include "../common/minerinterface.h"

class MinerXmrStakCpu : public MinerInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_MINERINTERFACE)
  Q_INTERFACES(MinerInterface)

  private:
    virtual ~MinerXmrStakCpu() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    virtual MinerWorkerInterfaceSPtr createWorker() const Q_DECL_OVERRIDE;
    virtual QString                  name        () const Q_DECL_OVERRIDE;
};

#endif