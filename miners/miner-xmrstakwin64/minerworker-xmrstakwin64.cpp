#include "minerworker-xmrstakwin64.h"

#include "log.h"
#include <QtCore/QResource>
#include "../../common/coinsymbolstrings.h"
#include <QtCore/QStandardPaths>
#include <MkCore/MFile>

MinerWorkerXmrStakWin64::MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId), _options(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak.exe");
  _minerProcess.setWorkingDirectory(_minerDir.path());
}

QStringList MinerWorkerXmrStakWin64::prepareArguments() const
{
  auto commonConfigFilePath = prepareCommonConfig();

  // TODO

  return QStringList();
}

QString MinerWorkerXmrStakWin64::prepareCommonConfig() const
{
  QResource configResource(":/resources/files/config.txt");
  QString configData = reinterpret_cast<const char *>(configResource.data());

  configData.replace("%pool_address%",   _poolAddress);
  configData.replace("%wallet_address%", _poolCredentials.username);
  configData.replace("%pool_password%",  _poolCredentials.password);

  QString currency;
  auto coinSymbol = gCoinSymbolStrings->fromString(_options.coinSymbol());
  switch (coinSymbol)
  {
    case Coin::Symbol::AEON:
      currency = "aeon";
      break;
    case Coin::Symbol::XMR:
      currency = "monero";
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::prepareCommonConfig", "switch (coinSymbol)");
  }
  configData.replace("%currency%", currency);

  auto configFilePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  configFilePath.append(QDir::separator());
  configFilePath.append(_fileInfo.completeBaseName());
  configFilePath.append(QDir::separator());
  configFilePath.append(_miningUnitId.toString());
  configFilePath.append("-config.txt");

  MFile::write(configFilePath, configData);

  return configFilePath;
}

const QString &MinerWorkerXmrStakWin64::consoleOutput() const
{
  return _minerOutput;
}

bool MinerWorkerXmrStakWin64::isRunning() const
{
  return _minerProcess.state() != QProcess::NotRunning;
}

void MinerWorkerXmrStakWin64::start()
{
  auto arguments = prepareArguments();
  _minerProcess.setArguments(arguments);

  _stdOutStream.setDevice(&_minerProcess);

  connect(&_minerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MinerWorkerXmrStakWin64::on_minerProcess_finished);
  connect(&_minerProcess, &QProcess::readyReadStandardOutput,                            this, &MinerWorkerXmrStakWin64::on_minerProcess_readyReadStandardOutput);

  _minerProcess.start(QIODevice::ReadOnly);

  if (_minerProcess.error() == QProcess::FailedToStart)
  {
    mCCritical(XmrStakWin64) << "failed to start miner for mining unit " << _miningUnitId.toString();

    emit finished();
  }
  else
  {
    mCInfo(XmrStakWin64) << "miner for mining unit " << _miningUnitId.toString() << " started";
  }
}

void MinerWorkerXmrStakWin64::stop()
{
  _minerProcess.kill();
}

void MinerWorkerXmrStakWin64::on_minerProcess_finished(int exitCode, QProcess::ExitStatus exitStatus) const
{
  mCInfo(XmrStakWin64) << "miner for mining unit " << _miningUnitId.toString() << " stopped";

  emit finished();
}

void MinerWorkerXmrStakWin64::on_minerProcess_readyReadStandardOutput()
{
  forever
  {
    _stdOutLastLine += _stdOutStream.readLine();
    if (_stdOutStream.atEnd())
    {
      break;
    }

    emit outputLine(_stdOutLastLine);
    _minerOutput.append(_stdOutLastLine + '\n');

    // TODO

    _stdOutLastLine.clear();
  }
}