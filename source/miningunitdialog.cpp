#include "miningunitdialog.h"

#include "../miners/common/minerinterface.h"

MiningUnitDialog::MiningUnitDialog(const MinerInterface *miner, QWidget *parent) : QDialog(parent), _miner(miner)
{
  _ui.setupUi(this);

  setupWidgets();
}

void MiningUnitDialog::setupWidgets() const
{
  _ui.name->setText(_miner->name());
}