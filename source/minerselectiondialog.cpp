#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(minerPlugins), _hardwareModel(&_supportedHwComponents, minerPlugins), _minersModel(minerPlugins), _minersMiner(Q_NULLPTR)
{
  _ui.setupUi(this);

  setupWidgets();

  connect(_ui.hwComponentsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_hwComponentsView_selectionChanged);
  connect(_ui.coinsView->selectionModel(),        &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_coinsView_selectionChanged);
  connect(_ui.minersView->selectionModel(),       &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_minersView_selectionChanged);
}

void MinerSelectionDialog::refreshAllowedMiners()
{
  if (_minersMiner)
  {
    _allowedMiners = { _minersMiner };

    return;
  }
  else
  {
    _allowedMiners = _minerPlugins->toRawList().toSet();
  }

  if (!_hwComponentMiners.isEmpty())
  {
    _allowedMiners.intersect(_hwComponentMiners);
  }

  if (!_coinMiners.isEmpty())
  {
    _allowedMiners.intersect(_coinMiners);
  }
}

void MinerSelectionDialog::refreshOkButton() const
{
  _ui.okButton->setEnabled(!_ui.hwComponentsView->selectionModel()->selectedRows().isEmpty() && !_ui.coinsView->selectionModel()->selectedRows().isEmpty() && !_ui.minersView->selectionModel()->selectedRows().isEmpty());
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
  _ui.coinsView->setModel(&_coinsModel);
  _ui.minersView->setModel(&_minersModel);
}

void MinerSelectionDialog::on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = _ui.coinsView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index  = _ui.coinsView->selectionModel()->selectedIndexes().first();
    _coinMiners = _coinsModel.miners(index);
  }
  else
  {
    _coinMiners.clear();
  }
  refreshAllowedMiners();

  refreshOkButton();
}

void MinerSelectionDialog::on_hwComponentsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = _ui.hwComponentsView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index         = _ui.hwComponentsView->selectionModel()->selectedIndexes().first();
    _hwComponentMiners = _coinsModel.miners(index);
  }
  else
  {
    _hwComponentMiners.clear();
  }
  refreshAllowedMiners();

  refreshOkButton();
}

void MinerSelectionDialog::on_minersView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = _ui.minersView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index   = _ui.minersView->selectionModel()->selectedIndexes().first();
    _minersMiner = _minerPlugins->toList().operator[](index.row());
  }
  else
  {
    _minersMiner = Q_NULLPTR;
  }
  refreshAllowedMiners();

  refreshOkButton();
}