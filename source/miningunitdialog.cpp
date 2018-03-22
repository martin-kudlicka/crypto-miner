#include "miningunitdialog.h"

#include "../miners/minerinterface.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent) : MiningUnitDialog(MUuidPtr::createUuid(), minerPlugin, hwComponent, coin, parent)
{
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent) : QDialog(parent), _options(id), _minerPlugin(minerPlugin), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets(hwComponent, coin);
  setupSettings();
}

const MiningUnitOptions &MiningUnitDialog::options() const
{
  return _options;
}

void MiningUnitDialog::setupSettings()
{
  // parameters
  _widgetSettings.setWidget(MinerOptions::Property::Parameters_HwComponent, _ui.parameterHwComponent, &_options.miner());
  _widgetSettings.setWidget(MinerOptions::Property::Parameters_Coin,        _ui.parameterCoin,        &_options.miner());

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
    auto value = hwComponent.toString();
    _ui.parameterHwComponent->addItem(value, value);
  }
  for (auto coin : _minerPlugin->supportedCoins())
  {
    _ui.parameterCoin->addItem(coin.toString(), coin.toString(Coin::Part::Name));
  }
}

void MiningUnitDialog::setupWidgets(const HwComponent &hwComponent, Coin coin) const
{
  setupWidgets();

  // parameters
  auto value = hwComponent.toString();
  auto index = _ui.parameterHwComponent->findData(value);
  _ui.parameterHwComponent->setCurrentIndex(index);

  value = coin.toString(Coin::Part::Name);
  index = _ui.parameterCoin->findData(value);
  _ui.parameterCoin->setCurrentIndex(index);
}

void MiningUnitDialog::accept()
{
  _options.miner().setName(_minerPlugin->name());

  _widgetSettings.save();

  QDialog::accept();
}