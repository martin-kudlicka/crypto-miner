#include "miningunitdialog.h"

#include "../miners/minerinterface.h"
#include "../coins/coins.h"

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
  for (const auto &coinInfo : gCoins->infoList())
  {
    _ui.parameterCoin->addItem(coinInfo.name, coinInfo.symbol);
  }
}

void MiningUnitDialog::accept()
{
  _options.setMiner(_minerPlugin->name());

  _widgetSettings.save();

  QDialog::accept();
}