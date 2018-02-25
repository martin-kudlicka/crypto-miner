#include "miner-xmrstakcpu.h"

#include <QtCore/QSharedPointer>
#include "minerworker.h"

MinerWorkerInterfaceSPtr MinerXmrStakCpu::createWorker() const
{
  return QSharedPointer<MinerWorker>::create();
}

QString MinerXmrStakCpu::name() const
{
  return "XMR-Stak CPU";
}