#include "miner-xmrstakcpu.h"

#include <QtCore/QSharedPointer>
#include "minerworker-xmrstakcpu.h"

MinerWorkerInterfaceSPtr MinerXmrStakCpu::createWorker(const MUuidPtr &id) const
{
  return QSharedPointer<MinerWorkerXmrStakCpu>::create(id);
}

QString MinerXmrStakCpu::name() const
{
  return "XMR-Stak CPU";
}

Coin::SymbolList MinerXmrStakCpu::supportedCoins() const
{
  return { Coin::Symbol::XMR };
}

HwComponentList MinerXmrStakCpu::supportedHardware() const
{
  return { HwComponent(Company::Any, Hardware::Cpu) };
}