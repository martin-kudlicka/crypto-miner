#include "minerworker-xmrstakwin64.h"

#include "log.h"
#include <QtCore/QResource>
#include <MkCore/MFile>
#include <QtCore/QRegularExpression>
#include <MkCore/MThread>

MinerWorkerXmrStakWin64::MinerWorkerXmrStakWin64(const MUuidPtr &miningUnitId) : MinerWorkerCommon(miningUnitId)
{
  _minerProcess.setProgram(_minerDir.path() + QDir::separator() + "xmr-stak.exe");
}

void MinerWorkerXmrStakWin64::addCurrencyArguments()
{
  QString currencyValue;
  auto coin = _options.coin();
  switch (coin.name())
  {
    case Coin::Name::Aeon:
      currencyValue = "aeon7";
      break;
    case Coin::Name::Monero:
      currencyValue = "monero7";
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::currencyArguments", "switch (coin.name())");
  }
  addArgument("--currency", currencyValue);
}

void MinerWorkerXmrStakWin64::addPoolArguments()
{
  addArgument("--url",  _poolAddress);
  addArgument("--user", _poolCredentials.username);
  addArgument("--rigid", QString());

  QString passwordValue;
  if (_poolCredentials.password.isEmpty())
  {
    passwordValue = R"("")";
  }
  else
  {
    passwordValue = _poolCredentials.password;
  }
  addArgument("--pass", passwordValue);
}

QString MinerWorkerXmrStakWin64::prepareCommonConfig() const
{
  QResource configResource(":/resources/files/config.txt");
  QByteArray configData = reinterpret_cast<const char *>(configResource.data());

  if (!MThread::runningAsAdministrator())
  {
    configData.replace(R"("use_slow_memory" : "warn",)", R"("use_slow_memory" : "always",)");
  }

  auto configFilePath = _minerProcess.workingDirectory();
  configFilePath.append(QDir::separator());
  configFilePath.append("config.txt");

  MFile::write(configFilePath, configData);

  return configFilePath;
}

void MinerWorkerXmrStakWin64::addOptionArguments()
{
  addPoolArguments();

  addArgument("--config", prepareCommonConfig());

  if (!MThread::runningAsAdministrator())
  {
    addArgument("--noUAC");
  }

  addCurrencyArguments();

  auto hwComponent = _options.hwComponent();
  switch (hwComponent.type())
  {
    case HwComponent::Type::Cpu:
      addArgument("--noAMD");
      addArgument("--noNVIDIA");
      break;
    case HwComponent::Type::Gpu:
      addArgument("--noCPU");

      switch (hwComponent.company())
      {
        case HwComponent::Company::Amd:
          addArgument("--noNVIDIA");
          break;
        case HwComponent::Company::Nvidia:
          addArgument("--noAMD");
          break;
        default:
          Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::processArguments", "switch (hwComponent.company())");
      }
      break;
    default:
      Q_ASSERT_X(false, "MinerWorkerXmrStakWin64::processArguments", "switch (hwComponent.type())");
  }
}

const QLoggingCategory &MinerWorkerXmrStakWin64::logCategory() const
{
  return XmrStakWin64();
}

void MinerWorkerXmrStakWin64::parseStdErrLine(const QString &line) const
{
}

void MinerWorkerXmrStakWin64::parseStdOutLine(const QString &line) const
{
  auto outLines = line.split(QRegularExpression(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\])"), QString::SkipEmptyParts);
  for (auto outLine : outLines)
  {
    if (outLine.startsWith(" : "))
    {
      outLine.remove(0, 3);
    }
    auto message = _miningUnitId.toString() + ' ' + outLine;

    if (outLine.contains("ERROR") || outLine.contains("FAILED"))
    {
      mCCritical(XmrStakWin64) << message;
    }
    else
    {
      mCInfo(XmrStakWin64) << message;
    }

    if (outLine.contains("Result accepted by the pool."))
    {
      emit resultAccepted();
    }

    QRegularExpression regExp(R"(^Totals \(ALL\):\D*(\d+\.\d))");
    auto regExpMatch = regExp.match(outLine);
    if (regExpMatch.hasMatch())
    {
      emit hashRate(regExpMatch.capturedRef(1).toFloat());
    }
  }
}