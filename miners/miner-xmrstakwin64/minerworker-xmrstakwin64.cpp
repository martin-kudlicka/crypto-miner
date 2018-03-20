#include "minerworker-xmrstakwin64.h"

#include "log.h"
#include <QtCore/QResource>
#include "../../coins/coinnamestrings.h"
#include <QtCore/QStandardPaths>
#include <MkCore/MFile>

MinerWorkerXmrStakWin64::MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId), _options(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak.exe");
  _minerProcess.setWorkingDirectory(_minerDir.path());
}

QStringList MinerWorkerXmrStakWin64::prepareArguments() const
{
  QStringList arguments;

  //arguments << "--noUAC";

  auto commonConfigFilePath = prepareCommonConfig();

  // TODO

  return QStringList();
}

QString MinerWorkerXmrStakWin64::prepareCommonConfig() const
{
  QResource configResource(":/resources/files/config.txt");
  QByteArray configData = reinterpret_cast<const char *>(configResource.data());

  configData.replace("%pool_address%",   _poolAddress.toLocal8Bit());
  configData.replace("%wallet_address%", _poolCredentials.username.toLocal8Bit());
  configData.replace("%pool_password%",  _poolCredentials.password.toLocal8Bit());

  static CoinNameStrings coinNameStrings;

  QString currency;
  auto coinName = coinNameStrings.fromString(_options.coinName());
  switch (coinName)
  {
    case Coin::Name::Aeon:
      currency = "aeon";
      break;
    case Coin::Name::Monero:
      currency = "monero";
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::prepareCommonConfig", "switch (coinName)");
  }
  configData.replace("%currency%", currency.toLocal8Bit());

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