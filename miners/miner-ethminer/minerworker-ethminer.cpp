#include "minerworker-ethminer.h"

#include "log.h"

MinerWorkerEthMiner::MinerWorkerEthMiner(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "ethminer.exe");
}

QStringList MinerWorkerEthMiner::poolArguments() const
{
  QStringList arguments;

  arguments << "--stratum"  << _poolAddress;

  auto userPass = _poolCredentials.username;
  if (!_poolCredentials.password.isEmpty())
  {
    userPass += ':' + _poolCredentials.password;
  }
  arguments << "--userpass" << userPass;

  return arguments;
}

const QLoggingCategory &MinerWorkerEthMiner::logCategory() const
{
  return EthMiner();
}

void MinerWorkerEthMiner::parseStdOutLine() const
{
  // TODO
}

QStringList MinerWorkerEthMiner::processArguments() const
{
  auto arguments = poolArguments();

  auto hwComponent = _options.hwComponent();
  switch (hwComponent.type())
  {
    case HwComponent::Type::Gpu:
      switch (hwComponent.company())
      {
        case HwComponent::Company::Amd:
          arguments << "--opencl";
          break;
        case HwComponent::Company::Nvidia:
          arguments << "--cuda";
          break;
        default:
          Q_ASSERT_X(false, "MinerWorkerEthMiner::processArguments", "switch (hwComponent.company())");
      }
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerEthMiner::processArguments", "switch (hwComponent.type())");
  }

  return arguments;
}