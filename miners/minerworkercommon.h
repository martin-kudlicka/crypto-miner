#ifndef MINERWORKERCOMMON_H
#define MINERWORKERCOMMON_H

#include "../minerworkerinterface.h"
#include <MkCore/MUuidPtr>
#include "../common/poolcredentials.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>

class MinerWorkerCommon : public MinerWorkerInterface
{
  public:
             MinerWorkerCommon(const MUuidPtr &miningUnitId);
    virtual ~MinerWorkerCommon() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  protected:
    MUuidPtr        _miningUnitId;
    PoolCredentials _poolCredentials;
    QDir            _minerDir;
    QFileInfo       _fileInfo;
    QString         _poolAddress;

  private:
    QString _minerName;

    virtual const QString &name              () const                             Q_DECL_OVERRIDE;
    virtual       void     setPoolAddress    (const QString &address)             Q_DECL_OVERRIDE;
    virtual       void     setPoolCredentials(const PoolCredentials &credentials) Q_DECL_OVERRIDE;
};

#endif