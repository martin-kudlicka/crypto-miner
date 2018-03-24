#ifndef MINERWORKERXMRSTAKCPUNOTLS_H
#define MINERWORKERXMRSTAKCPUNOTLS_H

#include "../minerworkercommon.h"
#include "../../common/mineroptions.h"

class MinerWorkerXmrStakWin64 : public MinerWorkerCommon
{
  Q_OBJECT

  public:
             MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakWin64() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    MinerOptions _options;

    QStringList currencyArguments  () const;
    QStringList poolArguments      () const;
    QStringList prepareArguments   () const;
    QString     prepareCommonConfig() const;

    virtual void start() Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
    void on_minerProcess_readyReadStandardOutput();
};

#endif