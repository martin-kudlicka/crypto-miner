#include "miner-xmrstakwin64.h"

#include <QtCore/QSharedPointer>
//#include "minerworker-xmrstakcpunotls.h"

MinerWorkerInterfaceSPtr MinerXmrStakWin64::createWorker(const MUuidPtr &id) const
{
  // TODO return QSharedPointer<MinerWorkerXmrStakCpuNoTls>::create(id);
  return Q_NULLPTR;
}

QString MinerXmrStakWin64::name() const
{
  return "XMR-Stak Win64";
}

MOperatingSystemVersion::Platform MinerXmrStakWin64::platform() const
{
  return MOperatingSystemVersion::Platform::X64;
}

Coin::SymbolList MinerXmrStakWin64::supportedCoins() const
{
  return { Coin::Symbol::AEON, Coin::Symbol::XMR };
}

HwComponentList MinerXmrStakWin64::supportedHardware() const
{
  return { HwComponent(Company::Any, Hardware::Cpu), HwComponent(Company::Amd, Hardware::Gpu), HwComponent(Company::Nvidia, Hardware::Gpu) };
}