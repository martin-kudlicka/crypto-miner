#include "minerworkercommon.h"

#include <MkLib/MModuleInfo>
#include <QtCore/QStandardPaths>
#include <MkCore/MMessageLogger>
#include <MkCore/MLoggingCategory>

MinerWorkerCommon::MinerWorkerCommon(const MUuidPtr &miningUnitId) : _options(miningUnitId), _miningUnitId(miningUnitId), _stdOutStream(&_minerProcess)
{
  auto fileInfo = MModuleInfo().fileInfo();

  auto baseName = fileInfo.completeBaseName();
  auto dashPos  = baseName.indexOf('-');
  _minerName    = baseName.mid(dashPos + 1);

  _minerDir.setPath(fileInfo.path());
  _minerDir.cd("miners");
  _minerDir.cd(_minerName);

  auto workPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  workPath.append(QDir::separator());
  workPath.append(fileInfo.completeBaseName());
  _workDir.setPath(workPath);
}

void MinerWorkerCommon::appendOutput(const QString &line)
{
  if (_minerOutput.count() >= 16)
  {
    _minerOutput.removeFirst();
  }

  _minerOutput.append(line);
}

const QStringList &MinerWorkerCommon::consoleOutput() const
{
  return _minerOutput;
}

bool MinerWorkerCommon::isRunning() const
{
  return _minerProcess.state() != QProcess::NotRunning;
}

const QString &MinerWorkerCommon::name() const
{
  return _minerName;
}

void MinerWorkerCommon::setPoolAddress(const QString &address)
{
  _poolAddress = address;
}

void MinerWorkerCommon::setPoolCredentials(const PoolCredentials &credentials)
{
  _poolCredentials = credentials;
}

void MinerWorkerCommon::start()
{
  _minerProcess.setArguments(processArguments());
  _minerProcess.setWorkingDirectory(_minerDir.path());

  connect(&_minerProcess,  QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MinerWorkerCommon::on_minerProcess_finished);
  connect(&_minerProcess, &QProcess::readyReadStandardOutput,                             this, &MinerWorkerCommon::on_minerProcess_readyReadStandardOutput);
  connect(&_minerProcess, &QProcess::readyReadStandardError,                              this, &MinerWorkerCommon::on_minerProcess_readyReadStandardError);

  _minerProcess.start(QIODevice::ReadOnly);

  if (_minerProcess.error() == QProcess::FailedToStart)
  {
    mCCritical(logCategory()) << "failed to start miner for mining unit " << _miningUnitId.toString();

    emit finished(_minerName);
  }
  else
  {
    mCInfo(logCategory()) << "miner for mining unit " << _miningUnitId.toString() << " started";
  }
}

void MinerWorkerCommon::stop()
{
  _minerProcess.kill();
}

void MinerWorkerCommon::on_minerProcess_finished(int exitCode, QProcess::ExitStatus exitStatus) const
{
  mCInfo(logCategory()) << "miner for mining unit " << _miningUnitId.toString() << " stopped";

  emit finished(_minerName);
}

void MinerWorkerCommon::on_minerProcess_readyReadStandardError()
{
  _stdErrData = _minerProcess.readAllStandardError();

  while (!_stdErrData.isEmpty())
  {
    auto lineEndPos = _stdErrData.indexOf('\n');
    if (lineEndPos == -1)
    {
      _stdErrLastLine = _stdErrData;
      _stdErrData.clear();
    }
    else
    {
      _stdErrLastLine = _stdErrData.left(lineEndPos - 1);
      _stdErrData.remove(0, lineEndPos + 1);
    }

    emit outputLine(_stdErrLastLine);
    appendOutput(_stdErrLastLine);

    parseStdErrLine();

    _stdErrLastLine.clear();
  }
}

void MinerWorkerCommon::on_minerProcess_readyReadStandardOutput()
{
  while (!_stdOutStream.atEnd())
  {
    _stdOutLastLine = _stdOutStream.readLine();

    emit outputLine(_stdOutLastLine);
    appendOutput(_stdOutLastLine);

    parseStdOutLine();

    _stdOutLastLine.clear();
  }
}