#include "optionsdialog.h"

#include <MkCore/MCoreApplication>

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
  _ui.setupUi(this);

  setupSettings();
}

void OptionsDialog::setupSettings() const
{
  _ui.startWithLogon->setChecked(MCoreApplication::registeredOnStartup());
}

void OptionsDialog::accept()
{
  MCoreApplication::setRegisteredOnStartup(_ui.startWithLogon->isChecked());

  QDialog::accept();
}