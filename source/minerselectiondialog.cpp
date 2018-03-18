#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(&_supportedCoins, minerPlugins), _hardwareModel(&_supportedHwComponents, minerPlugins), _minersModel(minerPlugins)
{
  _ui.setupUi(this);

  setupWidgets();

  connect(_ui.hwComponentsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_hwComponentsView_selectionChanged);
  connect(_ui.coinsView->selectionModel(),        &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_coinsView_selectionChanged);
  connect(_ui.minersView->selectionModel(),       &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_minersView_selectionChanged);
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
  _ui.minersView->setModel(&_minersModel);
}

void MinerSelectionDialog::updateOkButton() const
{
  _ui.okButton->setEnabled(!_ui.hwComponentsView->selectionModel()->selectedRows().isEmpty() && !_ui.coinsView->selectionModel()->selectedRows().isEmpty() && !_ui.minersView->selectionModel()->selectedRows().isEmpty());
}

void MinerSelectionDialog::on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  updateOkButton();
}

void MinerSelectionDialog::on_hwComponentsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  updateOkButton();
}

void MinerSelectionDialog::on_minersView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  updateOkButton();
}