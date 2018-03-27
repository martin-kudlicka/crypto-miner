#include "minerworkercommon.h"

#include <MkLib/MModuleInfo>
#include <QtCore/QStandardPaths>
#include <MkCore/MMessageLogger>
#include <MkCore/MLoggingCategory>

MinerWorkerCommon::MinerWorkerCommon(const MUuidPtr &miningUnitId) : _options(miningUnitId), _miningUnitId(miningUnitId)
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
  workPath.append(QDir::separator());
  workPath.append(_miningUnitId.toString());
  QDir().mkpath(workPath);
  _minerProcess.setWorkingDirectory(workPath);
}

void MinerWorkerCommon::appendOutput(const QString &line)
{
  if (_minerOutput.count() >= 262144)
  {
    _minerOutput.removeFirst();
  }

  _minerOutput.append(line);
}

void MinerWorkerCommon::addToCommandLine(const QString &argument, QString *commandLine) const
{
  if (!commandLine->isEmpty())
  {
    commandLine->append(' ');
  }

  auto hasSpace = argument.contains(' ');
  if (hasSpace)
  {
    commandLine->append('"');
  }
  commandLine->append(argument);
  if (hasSpace)
  {
    commandLine->append('"');
  }
}

void MinerWorkerCommon::logCommandLine() const
{
  QString commandLine;
  addToCommandLine(_minerProcess.program(), &commandLine);

  for (const auto &argument : _minerProcess.arguments())
  {
    addToCommandLine(argument, &commandLine);
  }

  mCDebug(logCategory()) << "executing " << commandLine;
}

QString MinerWorkerCommon::readLine(QByteArray *data) const
{
  auto lineEndPos = data->indexOf('\n');
  if (lineEndPos == -1)
  {
    return QString();
  }
  else
  {
    auto line = data->left(lineEndPos - 1);
    data->remove(0, lineEndPos + 1);

    return line;
  }
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

  connect(&_minerProcess,  QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MinerWorkerCommon::on_minerProcess_finished);
  connect(&_minerProcess, &QProcess::readyReadStandardOutput,                             this, &MinerWorkerCommon::on_minerProcess_readyReadStandardOutput);
  connect(&_minerProcess, &QProcess::readyReadStandardError,                              this, &MinerWorkerCommon::on_minerProcess_readyReadStandardError);

  logCommandLine();

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

  QDir(_minerProcess.workingDirectory()).removeRecursively();

  emit finished(_minerName);
}

void MinerWorkerCommon::on_minerProcess_readyReadStandardError()
{
  _stdErrData += _minerProcess.readAllStandardError();

  forever
  {
    _stdErrLastLine = readLine(&_stdErrData);
    if (_stdErrLastLine.isNull())
    {
      break;
    }

    emit outputLine(_stdErrLastLine);
    appendOutput(_stdErrLastLine);

    parseStdErrLine();
  }
}

void MinerWorkerCommon::on_minerProcess_readyReadStandardOutput()
{
  _stdOutData += _minerProcess.readAllStandardOutput();

  forever
  {
    _stdOutLastLine = readLine(&_stdOutData);
    if (_stdOutLastLine.isNull())
    {
      break;
    }

    emit outputLine(_stdOutLastLine);
    appendOutput(_stdOutLastLine);

    parseStdOutLine();
  }
}