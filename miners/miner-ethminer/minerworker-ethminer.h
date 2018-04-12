#ifndef MINERWORKERETHMINER_H
#define MINERWORKERETHMINER_H

#include "../minerworkercommon.h"

class MinerWorkerEthMiner : public MinerWorkerCommon
{
  public:
             MinerWorkerEthMiner(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerEthMiner() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    void        addPoolArguments();
    QStringList splitStdError   (QString errLines) const;

    virtual       void              addOptionArguments()                          Q_DECL_OVERRIDE;
    virtual const QLoggingCategory &logCategory       ()                    const Q_DECL_OVERRIDE;
    virtual       void              parseStdErrLine   (const QString &line) const Q_DECL_OVERRIDE;
    virtual       void              parseStdOutLine   (const QString &line) const Q_DECL_OVERRIDE;
};

#endif