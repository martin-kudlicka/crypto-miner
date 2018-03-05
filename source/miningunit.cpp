#include "miningunit.h"

#include "minerplugins.h"
#include "../miners/common/poolcredentials.h"
#include "log.h"
#include "miningmodel.h"
#include "consolewindow.h"

MiningUnit::MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins, MiningModel *miningModel) : _miningModel(miningModel), _minerPlugin(Q_NULLPTR), _options(id)
{
  for (auto &minerPlugin : minerPlugins->toList())
  {
    if (minerPlugin->name() == _options.miner())
    {
      _minerPlugin = minerPlugin;
      break;
    }
  }
  Q_ASSERT_X(_minerPlugin, "MiningUnit::MiningUnit", "_minerPlugin");
}

bool MiningUnit::isRunning() const
{
  if (!_worker)
  {
    return false;
  }

  return _worker->isRunning();
}

const MiningUnitOptions &MiningUnit::options() const
{
  return _options;
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
    _consoleWindow.reset(new ConsoleWindow(_worker->consoleOutput()));
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

  connect(&*_worker, SIGNAL(finished()),       SLOT(on_worker_finished()));
  connect(&*_worker, SIGNAL(hashRate(float)),  SLOT(on_worker_hashRate(float)));
  connect(&*_worker, SIGNAL(resultAccepted()), SLOT(on_worker_resultAccepted()));

  _miningTime.start();

  _worker->start();

  _miningModel->setDataChanged(_options.id(), MiningModel::Column::Status);
}

void MiningUnit::stop()
{
  _worker.clear();
}

void MiningUnit::on_consoleWindow_destroyed(QObject *obj /* Q_NULLPTR */)
{
  _consoleWindow.take();
}

void MiningUnit::on_worker_finished()
{
  auto miningTime = _options.miningTime() + _miningTime.elapsed() / 1000;
  _miningTime.invalidate();
  _options.setMiningTime(miningTime);

  // worker will be destroyed when mining unit is destroyed or new one is created

  _miningModel->setDataChanged(_options.id(), MiningModel::Column::Status);

  mCInfo(CryptoMiner) << "mining unit " << _options.id().toString() << " stopped";
}

void MiningUnit::on_worker_hashRate(float value)
{
  _sessionStatistics.hashRate = value;
  _miningModel->setDataChanged(_options.id(), MiningModel::Column::HashRate);
}

void MiningUnit::on_worker_resultAccepted()
{
  ++_sessionStatistics.results;
  _miningModel->setDataChanged(_options.id(), MiningModel::Column::Results);

  _options.setAcceptedResults(_options.acceptedResults() + 1);
}

MiningUnit::Statistics::Statistics() : hashRate(0.0), results(0)
{
}