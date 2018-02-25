#include "minerworker-xmrstakcpu.h"

MinerWorkerXmrStakCpu::MinerWorkerXmrStakCpu(const MUuidPtr &id)
{
  _id = id;
}

void MinerWorkerXmrStakCpu::setPoolAddress(const QString &address)
{
  _poolAddress = address;
}

void MinerWorkerXmrStakCpu::setPoolCredentials(const PoolCredentials &credentials)
{
  _poolCredentials = credentials;
}

void MinerWorkerXmrStakCpu::start()
{
  // TODO
}