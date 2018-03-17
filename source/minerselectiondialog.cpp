#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(&_supportedCoins), _hardwareModel(&_supportedHwComponents), _minerModel(minerPlugins)
{
  _ui.setupUi(this);

  setupWidgets();
}

void MinerSelectionDialog::setupWidgets()
{
  for (auto &miner : _minerPlugins->toList())
  {
    for (auto symbol : miner->supportedCoins())
    {
      if (!_supportedCoins.contains(symbol))
      {
        _supportedCoins.append(symbol);
      }
    }

    for (const auto &hwComponent : miner->supportedHardware())
    {
      if (!_supportedHwComponents.contains(hwComponent))
      {
        _supportedHwComponents.append(hwComponent);
      }
    }
  }

  _ui.hwComponentsView->setModel(&_hardwareModel);
  _ui.coinsView->setModel(&_coinsModel);
  _ui.minerView->setModel(&_minerModel);
}