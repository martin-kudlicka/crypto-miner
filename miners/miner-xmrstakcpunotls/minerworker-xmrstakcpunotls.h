#ifndef MINERWORKERXMRSTAKCPUNOTLS_H
#define MINERWORKERXMRSTAKCPUNOTLS_H

#include "../minerworkercommon.h"

class MinerWorkerXmrStakCpuNoTls : public MinerWorkerCommon
{
  public:
             MinerWorkerXmrStakCpuNoTls(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakCpuNoTls() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    void    modifyConfig     (QString *config)       const;
    QString readVanillaConfig()                      const;
    QString writeWorkerConfig(const QString &config) const;

    virtual       void              addOptionArguments()                          Q_DECL_OVERRIDE;
    virtual const QLoggingCategory &logCategory       ()                    const Q_DECL_OVERRIDE;
    virtual       void              parseStdErrLine   (const QString &line) const Q_DECL_OVERRIDE;
    virtual       void              parseStdOutLine (  const QString &line) const Q_DECL_OVERRIDE;
};

#endif