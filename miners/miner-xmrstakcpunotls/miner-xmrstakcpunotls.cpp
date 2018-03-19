#include "miner-xmrstakcpunotls.h"

#include "minerworker-xmrstakcpunotls.h"

MinerWorkerInterfaceSPtr MinerXmrStakCpuNoTls::createWorker(const MUuidPtr &id) const
{
  return QSharedPointer<MinerWorkerXmrStakCpuNoTls>::create(id);
}

QString MinerXmrStakCpuNoTls::name() const
{
  return "XMR-Stak CPU (no TLS)";
}

MOperatingSystemVersion::Platform MinerXmrStakCpuNoTls::platform() const
{
  return MOperatingSystemVersion::Platform::X64;
}

Coin::NameList MinerXmrStakCpuNoTls::supportedCoins() const
{
  return { Coin::Name::Monero };
}

Hardware::HwComponentList MinerXmrStakCpuNoTls::supportedHardware() const
{
  return { Hardware::HwComponent(Hardware::Company::Any, Hardware::Type::Cpu) };
}