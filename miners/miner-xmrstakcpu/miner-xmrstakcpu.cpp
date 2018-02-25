#include "miner-xmrstakcpu.h"

#include <QtCore/QSharedPointer>
#include "minerworker-xmrstakcpu.h"

MinerWorkerInterfaceSPtr MinerXmrStakCpu::createWorker() const
{
  return QSharedPointer<MinerWorkerXmrStakCpu>::create();
}

QString MinerXmrStakCpu::name() const
{
  return "XMR-Stak CPU";
}