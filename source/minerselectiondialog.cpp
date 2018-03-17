#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _hardwareModel(&_supportedHwComponents)
{
  _ui.setupUi(this);

  setupWidgets();
}

void MinerSelectionDialog::setupWidgets()
{
  for (auto &miner : _minerPlugins->toList())
  {
    for (const auto &hwComponent : miner->supportedHardware())
    {
      if (!_supportedHwComponents.contains(hwComponent))
      {
        _supportedHwComponents.append(hwComponent);
      }
    }
  }

  _ui.hwComponentsView->setModel(&_hardwareModel);
}