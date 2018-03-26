#ifndef MINERWORKERINTERFACE_H
#define MINERWORKERINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>

struct PoolCredentials;

class MinerWorkerInterface : public QObject
{
  Q_OBJECT

  public:
    virtual const QStringList &consoleOutput     () const                             = 0;
    virtual       bool         isRunning         () const                             = 0;
    virtual const QString     &name              () const                             = 0;
    virtual       void         setPoolAddress    (const QString &address)             = 0;
    virtual       void         setPoolCredentials(const PoolCredentials &credentials) = 0;
    virtual       void         start             ()                                   = 0;
    virtual       void         stop              ()                                   = 0;

  protected:
    virtual ~MinerWorkerInterface() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  Q_SIGNALS:
    void finished      (const QString &name) const;
    void hashRate      (float value)         const;
    void outputLine    (const QString &line) const;
    void resultAccepted()                    const;
};

using MinerWorkerInterfaceSPtr = QSharedPointer<MinerWorkerInterface>;

#endif