#ifndef MINERWORKERXMRIGWIN32_H
#define MINERWORKERXMRIGWIN32_H

#include "../minerworkercommon.h"

class MinerWorkerXmrigWin32 : public MinerWorkerCommon
{
  public:
             MinerWorkerXmrigWin32(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrigWin32() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    virtual const QLoggingCategory &logCategory     () const Q_DECL_OVERRIDE;
    virtual       void              parseStdErrLine () const Q_DECL_OVERRIDE;
    virtual       void              parseStdOutLine () const Q_DECL_OVERRIDE;
    virtual       QStringList       processArguments() const Q_DECL_OVERRIDE;
};

#endif