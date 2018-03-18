#include "miningunitdialog.h"

#include "../miners/minerinterface.h"
#include "hwcomponentstrings.h"
#include "coinsymbolstrings.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin::Symbol coinSymbol, QWidget *parent) : MiningUnitDialog(MUuidPtr::createUuid(), minerPlugin, hwComponent, coinSymbol, parent)
{
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin::Symbol coinSymbol, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets(hwComponent, coinSymbol);
  setupSettings();
}

const MiningUnitOptions &MiningUnitDialog::options() const
{
  return _options;
}

void MiningUnitDialog::setupSettings()
{
  // parameters
  _widgetSettings.setWidget(MinerOptions::Property::Parameters_HwComponent, _ui.parameterHwComponent);
  _widgetSettings.setWidget(MinerOptions::Property::Parameters_Coin,        _ui.parameterCoin);

  // pool
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Address,  _ui.poolAddress);
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Username, _ui.poolUsername);
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Password, _ui.poolPassword);

  _widgetSettings.load();
}

void MiningUnitDialog::setupWidgets() const
{
  _ui.name->setText(_minerPlugin->name());

  // parameters
  for (const auto &hwComponent : _minerPlugin->supportedHardware())
  {
    auto value = HwComponentStrings::toString(hwComponent);
    _ui.parameterHwComponent->addItem(value, value);
  }

  for (auto coinSymbol : _minerPlugin->supportedCoins())
  {
    auto value = gCoinSymbolStrings->toString(coinSymbol);
    _ui.parameterCoin->addItem(value, value);
  }
}

void MiningUnitDialog::setupWidgets(const HwComponent &hwComponent, Coin::Symbol coinSymbol) const
{
  setupWidgets();

  // parameters
  auto value = HwComponentStrings::toString(hwComponent);
  auto index = _ui.parameterHwComponent->findData(value);
  _ui.parameterHwComponent->setCurrentIndex(index);

  value = gCoinSymbolStrings->toString(coinSymbol);
  index = _ui.parameterCoin->findData(value);
  _ui.parameterCoin->setCurrentIndex(index);
}

void MiningUnitDialog::accept()
{
  _options.miner().setName(_minerPlugin->name());

  _widgetSettings.save();

  QDialog::accept();
}