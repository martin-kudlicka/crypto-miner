#include "optionsdialog.h"

#include <MkCore/MCoreApplication>
#include "options.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent), _widgetSettings(&*gOptions)
{
  _ui.setupUi(this);

  setupSettings();
}

void OptionsDialog::setupSettings()
{
  _ui.startWithLogon->setChecked(MCoreApplication::registeredOnStartup());

  _widgetSettings.setWidget(Options::Property::Startup_MineOnStartup, _ui.mineOnStartup);

  _widgetSettings.load();
}

void OptionsDialog::accept()
{
  MCoreApplication::setRegisteredOnStartup(_ui.startWithLogon->isChecked());

  _widgetSettings.save();

  QDialog::accept();
}