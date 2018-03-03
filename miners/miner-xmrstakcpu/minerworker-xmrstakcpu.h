#ifndef MINERWORKER_H
#define MINERWORKER_H

#include "../common/minerworkerinterface.h"
#include "../common/poolcredentials.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcess>

class MinerWorkerXmrStakCpu : public MinerWorkerInterface
{
  public:
             MinerWorkerXmrStakCpu(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerXmrStakCpu() Q_DECL_OVERRIDE;

  private:
    PoolCredentials _poolCredentials;
    QDir            _vanillaDir;
    QFileInfo       _fileInfo;
    QProcess        _minerProcess;
    QString         _minerName;
    QString         _poolAddress;

    void    modifyConfig     (QString *config)       const;
    QString prepareConfigFile()                      const;
    QString readVanillaConfig()                      const;
    QString writeWorkerConfig(const QString &config) const;

    virtual void setPoolAddress    (const QString &address)             Q_DECL_OVERRIDE;
    virtual void setPoolCredentials(const PoolCredentials &credentials) Q_DECL_OVERRIDE;
    virtual void start             ()                                   Q_DECL_OVERRIDE;
};

#endif