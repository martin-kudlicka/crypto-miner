#include "miner-xmrstakwin64.h"

#include "minerworker-xmrstakwin64.h"

MinerWorkerInterfaceSPtr MinerXmrStakWin64::createWorker(const MUuidPtr &id) const
{
  return QSharedPointer<MinerWorkerXmrStakWin64>::create(id);
}

QString MinerXmrStakWin64::name() const
{
  return "XMR-Stak Win64";
}

MOperatingSystemVersion::Platform MinerXmrStakWin64::platform() const
{
  return MOperatingSystemVersion::Platform::X64;
}

CoinList MinerXmrStakWin64::supportedCoins() const
{
  return { Coin::Name::Aeon, Coin::Name::Monero };
}

HwComponentList MinerXmrStakWin64::supportedHardware() const
{
  return { HwComponent(HwComponent::Company::Any, HwComponent::Type::Cpu), HwComponent(HwComponent::Company::Amd, HwComponent::Type::Gpu), HwComponent(HwComponent::Company::Nvidia, HwComponent::Type::Gpu) };
}