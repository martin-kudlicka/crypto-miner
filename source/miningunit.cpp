#include "miningunit.h"

#include "minerplugins.h"
#include "../miners/common/poolcredentials.h"
#include "log.h"
#include "miningmodel.h"
#include "consolewindow.h"
#include <MkAnalytics/MAnalytics>
#include "options.h"

MiningUnit::MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins, MiningModel *miningModel) : _miningModel(miningModel), _resultEtaTimer(0), _minerPlugin(Q_NULLPTR), _options(id)
{
  for (auto &minerPlugin : minerPlugins->toList())
  {
    if (minerPlugin->name() == _options.miner().name())
    {
      _minerPlugin = minerPlugin;
      break;
    }
  }
  Q_ASSERT_X(_minerPlugin, "MiningUnit::MiningUnit", "_minerPlugin");
}

void MiningUnit::closeConsole()
{
  if (_consoleWindow)
  {
    _consoleWindow.reset();
  }
}

bool MiningUnit::isRunning() const
{
  if (!_worker)
  {
    return false;
  }

  return _worker->isRunning();
}

const MinerInterface *MiningUnit::minerPlugin() const
{
  return _minerPlugin;
}

const MiningUnitOptions &MiningUnit::options() const
{
  return _options;
}

quintptr MiningUnit::resultEtaTimeSec() const
{
  return _resultEta.remainingTime() / 1000;
}

void MiningUnit::restart()
{
  stop();
  start();
}

const MiningUnit::Statistics &MiningUnit::sessionStatistics() const
{
  return _sessionStatistics;
}

void MiningUnit::showConsole()
{
  if (_consoleWindow)
  {
    _consoleWindow->activateWindow();
  }
  else
  {
    auto description = _options.miner().name() + tr(" mining ") + _options.miner().coin().toString();
    _consoleWindow.reset(new ConsoleWindow(description, _minerOutput));

    if (_worker)
    {
      connect(&*_worker, SIGNAL(outputLine(const QString &)), &*_consoleWindow, SLOT(on_minerWorker_outputLine(const QString &)));
    }

    _consoleWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(&*_consoleWindow, &ConsoleWindow::destroyed, this, &MiningUnit::on_consoleWindow_destroyed);

    _consoleWindow->show();
  }
}

void MiningUnit::start()
{
  mCInfo(CryptoMiner) << "mining unit " << _options.id().toString() << " started";

  _worker = _minerPlugin->createWorker(_options.id());

  _worker->setPoolAddress(_options.poolAddress());
  _worker->setPoolCredentials(PoolCredentials(_options.poolUsername(), _options.poolPassword()));

  connect(&*_worker, SIGNAL(finished(const QString &)),   SLOT(on_worker_finished(const QString &)));
  connect(&*_worker, SIGNAL(hashRate(float)),             SLOT(on_worker_hashRate(float)));
  connect(&*_worker, SIGNAL(outputLine(const QString &)), SLOT(on_worker_outputLine(const QString &)));
  connect(&*_worker, SIGNAL(resultAccepted()),            SLOT(on_worker_resultAccepted()));

  if (_consoleWindow)
  {
    connect(&*_worker, SIGNAL(outputLine(const QString &)), &*_consoleWindow, SLOT(on_minerWorker_outputLine(const QString &)));
  }

  _minerOutput.clear();
  _workerRunTime.start();
  _hashReportTime.invalidate();

  if (_sessionStatistics.results > 0)
  {
    _resultEta.setRemainingTime((_sessionStatistics.runTimeMSec + _workerRunTime.elapsed()) / _sessionStatistics.results, Qt::VeryCoarseTimer);
    _resultEtaTimer = startTimer(1000, Qt::VeryCoarseTimer);
  }

  _worker->start();

  _miningModel->setDataChanged(_options.id(), MiningModel::Column::Status);

  emit started();
}

void MiningUnit::stop()
{
  _worker->stop();
  _worker.clear();
}

void MiningUnit::timerEvent(QTimerEvent *event)
{
  if (_resultEta.hasExpired())
  {
    killTimer(_resultEtaTimer);
    _resultEtaTimer = 0;
  }

  _miningModel->setDataChanged(_options.id(), MiningModel::Column::ResultETA);
}

void MiningUnit::on_consoleWindow_destroyed(QObject *object /* Q_NULLPTR */)
{
  _consoleWindow.take();
}

void MiningUnit::on_worker_finished(const QString &workerName)
{
  _sessionStatistics.runTimeMSec += _workerRunTime.elapsed();
  auto miningTimeSec              = _workerRunTime.elapsed() / 1000;
  auto totalMiningTimeSec         = _options.miningTime() + miningTimeSec;
  _workerRunTime.invalidate();
  _options.setMiningTime(totalMiningTimeSec);

  mCInfo(CryptoMiner) << "mining unit " << _options.id().toString() << " stopped";

  _miningModel->setDataChanged(_options.id(), MiningModel::Column::Status);

  if (_resultEtaTimer != 0)
  {
    killTimer(_resultEtaTimer);
    _resultEtaTimer = 0;
  }

  emit finished();

  mAnalytics->sendTiming("miner", MAnalyticsTiming::Title::RunTime, miningTimeSec, workerName);
}

void MiningUnit::on_worker_hashRate(float value)
{
  _sessionStatistics.hashRate = value;
  _miningModel->setDataChanged(_options.id(), MiningModel::Column::HashRate);

  if (_hashReportTime.isValid())
  {
    auto hashCount = _options.hashCount();
    hashCount     += value * _hashReportTime.restart() / 1000;
    _options.setHashCount(hashCount);
  }
  else
  {
    _hashReportTime.start();
  }
}

void MiningUnit::on_worker_outputLine(const QString &line)
{
  while (!_minerOutput.isEmpty() && _minerOutput.count() >= gOptions->consoleOutputLinesInMemory())
  {
    _minerOutput.removeFirst();
  }

  _minerOutput.append(line);
}

void MiningUnit::on_worker_resultAccepted()
{
  _resultEta.setRemainingTime((_sessionStatistics.runTimeMSec + _workerRunTime.elapsed()) / ++_sessionStatistics.results, Qt::VeryCoarseTimer);
  _miningModel->setDataChanged(_options.id(), MiningModel::Column::Results);

  if (_resultEtaTimer == 0)
  {
    _resultEtaTimer = startTimer(1000, Qt::VeryCoarseTimer);
  }

  _options.setAcceptedResults(_options.acceptedResults() + 1);

  mAnalytics->sendEvent("miner", "resultFound", _worker->name(), 1);
}

MiningUnit::Statistics::Statistics() : hashRate(0.0), results(0), runTimeMSec(0)
{
}