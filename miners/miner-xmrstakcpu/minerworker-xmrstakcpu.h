#ifndef MINERWORKER_H
#define MINERWORKER_H

#include "../common/minerworkerinterface.h"
#include "../common/poolcredentials.h"

class MinerWorkerXmrStakCpu : public MinerWorkerInterface
{
  public:
    virtual ~MinerWorkerXmrStakCpu() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    virtual void setPoolAddress    (const QString &address)             Q_DECL_OVERRIDE;
    virtual void setPoolCredentials(const PoolCredentials &credentials) Q_DECL_OVERRIDE;

    PoolCredentials _poolCredentials;
    QString         _poolAddress;
};

#endif