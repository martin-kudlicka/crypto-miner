#ifndef MINERWORKERCOMMON_H
#define MINERWORKERCOMMON_H

#include "../minerworkerinterface.h"
#include <MkCore/MUuidPtr>
#include "../common/poolcredentials.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include "../../common/mineroptions.h"

class MinerWorkerCommon : public MinerWorkerInterface
{
  Q_OBJECT

  public:
             MinerWorkerCommon(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerCommon() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    QString _minerName;

  protected:
    MinerOptions    _options;
    MUuidPtr        _miningUnitId;
    PoolCredentials _poolCredentials;
    QByteArray      _stdErrData;
    QByteArray      _stdOutData;
    QDir            _minerDir;
    QProcess        _minerProcess;
    QString         _poolAddress;
    QStringList     _arguments;

    void addArgument(const QString &name);
    void addArgument(const QString &name, const QString &value);

  private:
    void    addToCommandLine(const QString &argument, QString *commandLine) const;
    void    logCommandLine  ()                                              const;
    void    prepareArguments();
    QString readLine        (QByteArray *data)                              const;

    virtual       bool     isRunning         () const                             Q_DECL_OVERRIDE;
    virtual const QString &name              () const                             Q_DECL_OVERRIDE;
    virtual       void     setPoolAddress    (const QString &address)             Q_DECL_OVERRIDE;
    virtual       void     setPoolCredentials(const PoolCredentials &credentials) Q_DECL_OVERRIDE;
    virtual       void     start             ()                                   Q_DECL_OVERRIDE;
    virtual       void     stop              ()                                   Q_DECL_OVERRIDE;

    virtual       void              addOptionArguments()                          = 0;
    virtual const QLoggingCategory &logCategory       ()                    const = 0;
    virtual       void              parseStdErrLine   (const QString &line) const = 0;
    virtual       void              parseStdOutLine   (const QString &line) const = 0;

    private Q_SLOTS:
      void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
      void on_minerProcess_readyReadStandardError ();
      void on_minerProcess_readyReadStandardOutput();
};

#endif