#ifndef MINERWORKER_H
#define MINERWORKER_H

#include "../common/minerworkerinterface.h"
#include "../common/poolcredentials.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QTextStream>

class MinerWorkerXmrStakCpu : public MinerWorkerInterface
{
  Q_OBJECT

  public:
             MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakCpu() Q_DECL_OVERRIDE;

  private:
    PoolCredentials _poolCredentials;
    QDir            _minerDir;
    QFileInfo       _fileInfo;
    QProcess        _minerProcess;
    QString         _minerName;
    QString         _minerOutput;
    QString         _poolAddress;
    QString         _stdOutLastLine;
    QTextStream     _stdOutStream;

    void    modifyConfig     (QString *config)       const;
    QString prepareConfigFile()                      const;
    QString readVanillaConfig()                      const;
    QString writeWorkerConfig(const QString &config) const;

    virtual const QString &consoleOutput     () const                             Q_DECL_OVERRIDE;
    virtual       bool     isRunning         () const                             Q_DECL_OVERRIDE;
    virtual       void     setPoolAddress    (const QString &address)             Q_DECL_OVERRIDE;
    virtual       void     setPoolCredentials(const PoolCredentials &credentials) Q_DECL_OVERRIDE;
    virtual       void     start             ()                                   Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_minerProcess_finished               (int exitCode, QProcess::ExitStatus exitStatus) const;
    void on_minerProcess_readyReadStandardOutput();
};

#endif