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

Coin::NameList MinerXmrStakWin64::supportedCoins() const
{
  return { Coin::Name::Aeon, Coin::Name::Monero };
}

Hardware::ComponentList MinerXmrStakWin64::supportedHardware() const
{
  return { Hardware::Component(Hardware::Company::Any, Hardware::Type::Cpu), Hardware::Component(Hardware::Company::Amd, Hardware::Type::Gpu), Hardware::Component(Hardware::Company::Nvidia, Hardware::Type::Gpu) };
}