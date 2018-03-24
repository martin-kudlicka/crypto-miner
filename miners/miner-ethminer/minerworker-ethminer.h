#ifndef MINERWORKERETHMINER_H
#define MINERWORKERETHMINER_H

#include "../minerworkercommon.h"
#include <QtCore/QProcess>
#include <QtCore/QTextStream>

class MinerWorkerEthMiner : public MinerWorkerCommon
{
  Q_OBJECT

  public:
             MinerWorkerEthMiner(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerEthMiner() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    QProcess     _minerProcess;
    QString      _stdOutLastLine;
    QTextStream  _stdOutStream;

    virtual bool isRunning() const Q_DECL_OVERRIDE;
    virtual void start    ()       Q_DECL_OVERRIDE;
    virtual void stop     ()       Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
    void on_minerProcess_readyReadStandardOutput();
};

#endif