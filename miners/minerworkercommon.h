#ifndef MINERWORKERCOMMON_H
#define MINERWORKERCOMMON_H

#include "../minerworkerinterface.h"
#include <MkCore/MUuidPtr>
#include "../common/poolcredentials.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QTextStream>
#include "../../common/mineroptions.h"

class MinerWorkerCommon : public MinerWorkerInterface
{
  Q_OBJECT

  public:
             MinerWorkerCommon(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerCommon() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  protected:
    MinerOptions    _options;
    MUuidPtr        _miningUnitId;
    PoolCredentials _poolCredentials;
    QStringList     _minerOutput;
    QDir            _minerDir;
    QDir            _workDir;
    QProcess        _minerProcess;
    QString         _poolAddress;
    QString         _stdOutLastLine;
    QTextStream     _stdOutStream;

    void appendOutput(const QString &line);

  private:
    QString _minerName;

    virtual const QStringList &consoleOutput     () const                             Q_DECL_OVERRIDE;
    virtual       bool         isRunning         () const                             Q_DECL_OVERRIDE;
    virtual const QString     &name              () const                             Q_DECL_OVERRIDE;
    virtual       void         setPoolAddress    (const QString &address)             Q_DECL_OVERRIDE;
    virtual       void         setPoolCredentials(const PoolCredentials &credentials) Q_DECL_OVERRIDE;
    virtual       void         stop              ()                                   Q_DECL_OVERRIDE;

    virtual const QLoggingCategory &logCategory    () const = 0;
    virtual       void              parseStdOutLine() const = 0;

    private Q_SLOTS:
      void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
      void on_minerProcess_readyReadStandardOutput();
};

#endif