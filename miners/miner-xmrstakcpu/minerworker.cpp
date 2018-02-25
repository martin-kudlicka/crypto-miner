#include "minerworker.h"

void MinerWorker::setPoolAddress(const QString &address)
{
  _poolAddress = address;
}

void MinerWorker::setPoolCredentials(const PoolCredentials &credentials)
{
  _poolCredentials = credentials;
}