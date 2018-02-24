#include "miningunitdialog.h"

#include "../miners/common/minerinterface.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *miner, QWidget *parent) : QDialog(parent), _miner(miner), _options(MUuidPtr::createUuid()), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

void MiningUnitDialog::setupSettings()
{
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Address,  _ui.poolAddress);
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Wallet,   _ui.poolWallet);
  _widgetSettings.setWidget(MiningUnitOptions::Property::Pool_Password, _ui.poolPassword);

  _widgetSettings.load();
}

void MiningUnitDialog::setupWidgets() const
{
  _ui.name->setText(_miner->name());
}

void MiningUnitDialog::accept()
{
  _options.setMiner(_miner->name());

  _widgetSettings.save();

  QDialog::accept();
}