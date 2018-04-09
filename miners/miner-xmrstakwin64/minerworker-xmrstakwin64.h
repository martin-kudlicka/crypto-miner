#ifndef MINERWORKERXMRSTAKWIN64_H
#define MINERWORKERXMRSTAKWIN64_H

#include "../minerworkercommon.h"

class MinerWorkerXmrStakWin64 : public MinerWorkerCommon
{
  public:
             MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakWin64() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    QStringList currencyArguments  () const;
    QStringList poolArguments      () const;
    QString     prepareCommonConfig() const;

    virtual const QLoggingCategory &logCategory     ()                    const Q_DECL_OVERRIDE;
    virtual       void              parseStdErrLine (const QString &line) const Q_DECL_OVERRIDE;
    virtual       void              parseStdOutLine (const QString &line) const Q_DECL_OVERRIDE;
    virtual       QStringList       processArguments()                    const Q_DECL_OVERRIDE;
};

#endif