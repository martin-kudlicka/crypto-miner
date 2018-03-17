#include "miningunitdialog.h"

#include "../miners/minerinterface.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *minerPlugin, QWidget *parent) : MiningUnitDialog(MUuidPtr::createUuid(), minerPlugin, parent)
{
}

MiningUnitDialog::MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, QWidget *parent) : QDialog(parent), _minerPlugin(minerPlugin), _options(id), _widgetSettings(&_options)
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
}

void MiningUnitDialog::accept()
{
  _options.setMiner(_minerPlugin->name());

  _widgetSettings.save();

  QDialog::accept();
}