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

    virtual const QLoggingCategory &logCategory     () const Q_DECL_OVERRIDE;
    virtual       void              parseStdErrLine () const Q_DECL_OVERRIDE;
    virtual       void              parseStdOutLine () const Q_DECL_OVERRIDE;
    virtual       QStringList       processArguments() const Q_DECL_OVERRIDE;
};

#endif