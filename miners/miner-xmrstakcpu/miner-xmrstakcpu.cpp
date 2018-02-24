#include "miner-xmrstakcpu.h"

#include <QtCore/QSharedPointer>

MinerWorkerInterfaceSPtr MinerXmrStakCpu::createWorker() const
{
  // TODO
  return MinerWorkerInterfaceSPtr::create();
}

QString MinerXmrStakCpu::name() const
{
  return "XMR-Stak CPU";
}