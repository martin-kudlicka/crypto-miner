#ifndef MINERXMRSTAKCPU_H
#define MINERXMRSTAKCPU_H

#include "../common/minerinterface.h"

class MinerXmrStakCpu : public MinerInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_MINERINTERFACE FILE "miner-xmrstakcpu.json")
  Q_INTERFACES(MinerInterface)

  private:
    virtual ~MinerXmrStakCpu() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    virtual QString name() const Q_DECL_OVERRIDE;
};

#endif