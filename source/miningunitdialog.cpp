#include "miningunitdialog.h"

#include "../miners/minerinterface.h"
#include "hwcomponentstrings.h"
#include "coinsymbolstrings.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin::Symbol coinSymbol, QWidget *parent) : MiningUnitDialog(MUuidPtr::createUuid(), minerPlugin, hwComponent, coinSymbol, parent)
{
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin::Symbol coinSymbol, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

const MiningUnitOptions &MiningUnitDialog::options() const
{
  return _options;
}

void MiningUnitDialog::setupSettings()
{
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
    _ui.parameterHardware->addItem(value, value);
  }

  static CoinSymbolStrings coinSymbolStrings;

  for (auto coinSymbol : _minerPlugin->supportedCoins())
  {
    auto value = coinSymbolStrings.toString(coinSymbol);
    _ui.parameterCoin->addItem(value, value);
  }
}

void MiningUnitDialog::accept()
{
  _options.setMiner(_minerPlugin->name());

  _widgetSettings.save();

  QDialog::accept();
}