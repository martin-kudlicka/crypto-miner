#include "minerselectiondialog.h"

#include "minerplugins.h"

Q_DECL_CONSTEXPR QString MinerSelectionDialog::Property::OperatingSystemSupportedOnly = "operatingSystemSupportedOnly";

MinerSelectionDialog::MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _minerPlugins(minerPlugins), _coinsModel(&_allowedCoinMiners, minerPlugins), _hardwareModel(&_allowedHwComponentMiners, minerPlugins), _minersModel(&_allowedMinerMiners, minerPlugins), _minersMiner(Q_NULLPTR)
{
  _ui.setupUi(this);

  _settings.beginGroup("minerSelection");

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
  auto allowedMiners = _minerPlugins->toRawList().toSet();
  if (_ui.operatingSystemSupportedOnly->isChecked())
  {
    QMutableSetIterator<MinerInterface *> miner(allowedMiners);
    while (miner.hasNext())
    {
      miner.next();
      if (!MOperatingSystemVersion::isPlatformSupported(miner.value()->platform()))
      {
        miner.remove();
      }
    }
  }

  if (_minersMiner)
  {
    _allowedHwComponentMiners = { _minersMiner };
    _allowedCoinMiners        = { _minersMiner };
  }
  else
  {
    _allowedHwComponentMiners = allowedMiners;
    _allowedCoinMiners        = allowedMiners;
  }
  _allowedMinerMiners = allowedMiners;

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

  _ui.operatingSystemSupportedOnly->setChecked(_settings.value(Property::OperatingSystemSupportedOnly, true).toBool());
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

void MinerSelectionDialog::on_operatingSystemSupportedOnly_toggled(bool checked)
{
  _settings.setValue(Property::OperatingSystemSupportedOnly, checked);

  refreshAllowedMiners();

  emit _hardwareModel.layoutChanged();
  emit _coinsModel.layoutChanged();
  emit _minersModel.layoutChanged();

  refreshOkButton();
}