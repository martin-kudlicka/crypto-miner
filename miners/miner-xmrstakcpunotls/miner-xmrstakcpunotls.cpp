#include "miner-xmrstakcpunotls.h"

#include <QtCore/QSharedPointer>
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

Coin::SymbolList MinerXmrStakCpuNoTls::supportedCoins() const
{
  return { Coin::Symbol::XMR };
}

HwComponentList MinerXmrStakCpuNoTls::supportedHardware() const
{
  return { HwComponent(Company::Any, Hardware::Cpu) };
}