#ifndef MININGUNIT_H
#define MININGUNIT_H

#include <QtCore/QSharedPointer>
#include "miningunitoptions.h"
#include "../miners/minerworkerinterface.h"
#include <QtCore/QElapsedTimer>
#include <QtCore/QDeadlineTimer>

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
      quintptr runTimeMSec;

      Statistics();
    };

             MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins, MiningModel *miningModel);
    virtual ~MiningUnit() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

          void               closeConsole     ();
          bool               isRunning        () const;
    const MinerInterface    *minerPlugin      () const;
    const MiningUnitOptions &options          () const;
          void               restart          ();
          quintptr           resultEtaTimeSec () const;
    const Statistics        &sessionStatistics() const;
          void               showConsole      ();
          void               start            ();
          void               stop             ();

  private:
          QScopedPointer<ConsoleWindow> _consoleWindow;
          int                           _resultEtaTimer;
    const MinerInterface               *_minerPlugin;
          MiningModel                  *_miningModel;
          MiningUnitOptions             _options;
          MinerWorkerInterfaceSPtr      _worker;
          QDeadlineTimer                _resultEta;
          QElapsedTimer                 _hashReportTime;
          QElapsedTimer                 _workerRunTime;
          QStringList                   _minerOutput;
          Statistics                    _sessionStatistics;

    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

  Q_SIGNALS:
    void finished() const;
    void started () const;

  private Q_SLOTS:
    void on_consoleWindow_destroyed(QObject *object = Q_NULLPTR);
    void on_worker_finished        (const QString &workerName);
    void on_worker_hashRate        (float value);
    void on_worker_outputLine      (const QString &line);
    void on_worker_resultAccepted  ();
};

using MiningUnitSPtr = QSharedPointer<MiningUnit>;

#endif