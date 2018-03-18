#ifndef MINERWORKERXMRSTAKCPUNOTLS_H
#define MINERWORKERXMRSTAKCPUNOTLS_H

#include "../minerworkercommon.h"
#include <QtCore/QProcess>
#include <QtCore/QTextStream>

class MinerWorkerXmrStakWin64 : public MinerWorkerCommon
{
  Q_OBJECT

  public:
             MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakWin64() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    QProcess    _minerProcess;
    QString     _minerOutput;
    QString     _stdOutLastLine;
    QTextStream _stdOutStream;

    void    modifyConfig     (QString *config)       const;
    QString prepareConfigFile()                      const;
    QString readVanillaConfig()                      const;
    QString writeWorkerConfig(const QString &config) const;

    virtual const QString &consoleOutput() const Q_DECL_OVERRIDE;
    virtual       bool     isRunning    () const Q_DECL_OVERRIDE;
    virtual       void     start        ()       Q_DECL_OVERRIDE;
    virtual       void     stop         ()       Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
    void on_minerProcess_readyReadStandardOutput();
};

#endif