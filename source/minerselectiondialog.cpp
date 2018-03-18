#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(&_supportedCoins, minerPlugins), _hardwareModel(&_supportedHwComponents, minerPlugins), _minerModel(minerPlugins)
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

void MinerSelectionDialog::on_hwComponentsView_clicked(const QModelIndex &index)
{
  if (_lastSelectedHwComponent == index)
  {
    _ui.hwComponentsView->clearSelection();
    _lastSelectedHwComponent = QModelIndex();
  }
  else
  {
    _lastSelectedHwComponent = index;
  }
}

void MinerSelectionDialog::on_coinsView_clicked(const QModelIndex &index)
{
  if (_lastSelectedCoin == index)
  {
    _ui.coinsView->clearSelection();
    _lastSelectedCoin = QModelIndex();
  }
  else
  {
    _lastSelectedCoin = index;
  }
}

void MinerSelectionDialog::on_minerView_clicked(const QModelIndex &index)
{
  if (_lastSelectedMiner == index)
  {
    _ui.minerView->clearSelection();
    _lastSelectedMiner = QModelIndex();
  }
  else
  {
    _lastSelectedMiner = index;
  }
}