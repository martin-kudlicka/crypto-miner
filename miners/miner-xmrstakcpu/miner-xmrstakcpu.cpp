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

CoinInfoList MinerXmrStakCpu::supportedCoins() const
{
  return { Coin::Monero };
}

HwComponentList MinerXmrStakCpu::supportedHardware() const
{
  return { HwComponent(Company::All, Hardware::Cpu) };
}