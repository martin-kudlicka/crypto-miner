#include "miner-xmrigwin32.h"

MinerWorkerInterfaceSPtr MinerXmrigWin32::createWorker(const MUuidPtr &id) const
{
  // TODO
  return Q_NULLPTR;
}

QString MinerXmrigWin32::name() const
{
  return "XMRig Win32";
}

MOperatingSystemVersion::Platform MinerXmrigWin32::platform() const
{
  return MOperatingSystemVersion::Platform::X86;
}

CoinList MinerXmrigWin32::supportedCoins() const
{
  return { Coin::Name::Monero };
}

HwComponentList MinerXmrigWin32::supportedHardware() const
{
  return { HwComponent(HwComponent::Company::Any, HwComponent::Type::Cpu) };
}