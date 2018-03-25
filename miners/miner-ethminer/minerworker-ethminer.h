#ifndef MINERWORKERETHMINER_H
#define MINERWORKERETHMINER_H

#include "../minerworkercommon.h"

class MinerWorkerEthMiner : public MinerWorkerCommon
{
  Q_OBJECT

  public:
             MinerWorkerEthMiner(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerEthMiner() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    virtual const QLoggingCategory &logCategory() const Q_DECL_OVERRIDE;
    virtual       void              start      ()       Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_minerProcess_readyReadStandardOutput();
};

#endif