#ifndef MININGUNIT_H
#define MININGUNIT_H

#include <QtCore/QSharedPointer>
#include "miningunitoptions.h"
#include "../miners/minerworkerinterface.h"
#include <QtCore/QElapsedTimer>
#include <QtCore/QQueue>

class ConsoleWindow;
class MinerInterface;
class MinerPlugins;
class MiningModel;

class MiningUnit : public QObject
{
  Q_OBJECT

  public:
    struct Statistics
    {
      float    hashRate;
      quintptr results;

      Statistics();
    };

             MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins, MiningModel *miningModel);
    virtual ~MiningUnit() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

          void               closeConsole     ();
          bool               isRunning        () const;
    const MinerInterface    *minerPlugin      () const;
    const MiningUnitOptions &options          () const;
    const Statistics        &sessionStatistics() const;
          void               showConsole      ();
          void               start            ();
          void               stop             ();

  private:
          QScopedPointer<ConsoleWindow>    _consoleWindow;
    const MinerInterface                  *_minerPlugin;
          MiningModel                     *_miningModel;
          MiningUnitOptions                _options;
          QQueue<MinerWorkerInterfaceSPtr> _stoppingWorkers;
          MinerWorkerInterfaceSPtr         _worker;
          QElapsedTimer                    _miningTime;
          Statistics                       _sessionStatistics;

  Q_SIGNALS:
    void finished() const;
    void started () const;

  private Q_SLOTS:
    void on_consoleWindow_destroyed(QObject *obj = Q_NULLPTR);
    void on_worker_finished        ();
    void on_worker_hashRate        (float value);
    void on_worker_resultAccepted  ();
};

using MiningUnitSPtr = QSharedPointer<MiningUnit>;

#endif