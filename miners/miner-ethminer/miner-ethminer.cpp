#include "miner-ethminer.h"

#include "minerworker-ethminer.h"

MinerWorkerInterfaceSPtr MinerEthMiner::createWorker(const MUuidPtr &id) const
{
  return QSharedPointer<MinerWorkerEthMiner>::create(id);
}

QString MinerEthMiner::name() const
{
  return "ethminer";
}

MOperatingSystemVersion::Platform MinerEthMiner::platform() const
{
  return MOperatingSystemVersion::Platform::X64;
}

CoinList MinerEthMiner::supportedCoins() const
{
  return { Coin::Name::Ethereum };
}

HwComponentList MinerEthMiner::supportedHardware() const
{
  return { HwComponent(HwComponent::Company::Amd, HwComponent::Type::Gpu), HwComponent(HwComponent::Company::Nvidia, HwComponent::Type::Gpu) };
}