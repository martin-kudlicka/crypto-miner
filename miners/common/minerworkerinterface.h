#ifndef MINERWORKERINTERFACE_H
#define MINERWORKERINTERFACE_H

#include <QtCore/QObject>
#include <MkCore/MUuidPtr>

struct PoolCredentials;

class MinerWorkerInterface : public QObject
{
  Q_OBJECT

  public:
    virtual void setPoolAddress    (const QString &address)             = 0;
    virtual void setPoolCredentials(const PoolCredentials &credentials) = 0;
    virtual void start             ()                                   = 0;

  protected:
    virtual ~MinerWorkerInterface() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    MUuidPtr _miningUnitId;

  Q_SIGNALS:
    void resultAccepted() const;
};

using MinerWorkerInterfaceSPtr = QSharedPointer<MinerWorkerInterface>;

#endif