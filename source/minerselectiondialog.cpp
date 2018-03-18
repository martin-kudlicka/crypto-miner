#include "minerselectiondialog.h"

#include "minerplugins.h"

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(&_allowedMiners, minerPlugins), _hardwareModel(&_allowedMiners, minerPlugins), _minersModel(&_allowedMiners, minerPlugins), _minersMiner(Q_NULLPTR)
{
  _ui.setupUi(this);

  setupWidgets();

  connect(_ui.hwComponentsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_hwComponentsView_selectionChanged);
  connect(_ui.coinsView->selectionModel(),        &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_coinsView_selectionChanged);
  connect(_ui.minersView->selectionModel(),       &QItemSelectionModel::selectionChanged, this, &MinerSelectionDialog::on_minersView_selectionChanged);
}

void MinerSelectionDialog::refreshAllowedMiners()
{
  _allowedMiners = _minerPlugins->toRawList().toSet();

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
  _ui.hwComponentsView->setModel(&_hardwareModel);
  _ui.coinsView->setModel(&_coinsModel);
  _ui.minersView->setModel(&_minersModel);
}

void MinerSelectionDialog::on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.coinsView->selectionModel()->selectedRows().isEmpty();
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

  emit _hardwareModel.layoutChanged();
  emit _minersModel.layoutChanged();

  refreshOkButton();
}

void MinerSelectionDialog::on_hwComponentsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.hwComponentsView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index         = _ui.hwComponentsView->selectionModel()->selectedIndexes().first();
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
    auto index   = _ui.minersView->selectionModel()->selectedIndexes().first();
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