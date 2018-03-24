#ifndef MINERWORKERXMRSTAKCPUNOTLS_H
#define MINERWORKERXMRSTAKCPUNOTLS_H

#include "../minerworkercommon.h"

class MinerWorkerXmrStakCpuNoTls : public MinerWorkerCommon
{
  Q_OBJECT

  public:
             MinerWorkerXmrStakCpuNoTls(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakCpuNoTls() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    void    modifyConfig     (QString *config)       const;
    QString prepareConfigFile()                      const;
    QString readVanillaConfig()                      const;
    QString writeWorkerConfig(const QString &config) const;

    virtual void start() Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
    void on_minerProcess_readyReadStandardOutput();
};

#endif