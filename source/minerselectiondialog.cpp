#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(&_allowedCoinMiners, minerPlugins), _hardwareModel(&_allowedHwComponentMiners, minerPlugins), _minersModel(&_allowedMinerMiners, minerPlugins), _minersMiner(Q_NULLPTR)
{
  _ui.setupUi(this);

  setupWidgets();

  connect(_ui.hwComponentsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_hwComponentsView_selectionChanged);
  connect(_ui.coinsView->selectionModel(),        &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_coinsView_selectionChanged);
  connect(_ui.minersView->selectionModel(),       &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_minersView_selectionChanged);
}

Coin MinerSelectionDialog::selectedCoin() const
{
  return _coinsModel.coin(_ui.coinsView->currentIndex());
}

HwComponent MinerSelectionDialog::selectedHwComponent() const
{
  return _hardwareModel.hwComponent(_ui.hwComponentsView->currentIndex());
}

MinerInterface *MinerSelectionDialog::selectedMiner() const
{
  return _minersMiner;
}

void MinerSelectionDialog::refreshAllowedMiners()
{
  if (_minersMiner)
  {
    _allowedHwComponentMiners = { _minersMiner };
    _allowedCoinMiners        = { _minersMiner };
  }
  else
  {
    _allowedHwComponentMiners = _minerPlugins->toRawList().toSet();
    _allowedCoinMiners        = _minerPlugins->toRawList().toSet();
  }
  _allowedMinerMiners = _minerPlugins->toRawList().toSet();

  if (!_hwComponentMiners.isEmpty())
  {
    _allowedCoinMiners.intersect(_hwComponentMiners);
    _allowedMinerMiners.intersect(_hwComponentMiners);
  }

  if (!_coinMiners.isEmpty())
  {
    _allowedHwComponentMiners.intersect(_coinMiners);
    _allowedMinerMiners.intersect(_coinMiners);
  }
}

void MinerSelectionDialog::refreshOkButton() const
{
  _ui.okButton->setEnabled(!_ui.hwComponentsView->selectionModel()->selectedRows().isEmpty() && !_ui.coinsView->selectionModel()->selectedRows().isEmpty() && !_ui.minersView->selectionModel()->selectedRows().isEmpty());
}

void MinerSelectionDialog::setupWidgets()
{
  _ui.hwComponentsView->setModel(&_hardwareModel);
  _ui.coinsView->setModel(&_coinsModel);
  _ui.minersView->setModel(&_minersModel);
}

void MinerSelectionDialog::on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.coinsView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index  = _ui.coinsView->selectionModel()->selectedIndexes().constFirst();
    _coinMiners = _coinsModel.miners(index);
  }
  else
  {
    _coinMiners.clear();
  }
  refreshAllowedMiners();

  emit _hardwareModel.layoutChanged();
  emit _minersModel.layoutChanged();

  refreshOkButton();
}

void MinerSelectionDialog::on_hwComponentsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.hwComponentsView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index         = _ui.hwComponentsView->selectionModel()->selectedIndexes().constFirst();
    _hwComponentMiners = _hardwareModel.miners(index);
  }
  else
  {
    _hwComponentMiners.clear();
  }
  refreshAllowedMiners();

  emit _coinsModel.layoutChanged();
  emit _minersModel.layoutChanged();

  refreshOkButton();
}

void MinerSelectionDialog::on_minersView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.minersView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index   = _ui.minersView->selectionModel()->selectedIndexes().constFirst();
    _minersMiner = _minerPlugins->toList().operator[](index.row());
  }
  else
  {
    _minersMiner = Q_NULLPTR;
  }
  refreshAllowedMiners();

  emit _hardwareModel.layoutChanged();
  emit _coinsModel.layoutChanged();

  refreshOkButton();
}