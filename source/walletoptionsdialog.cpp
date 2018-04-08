#include "walletoptionsdialog.h"

WalletOptionsDialog::WalletOptionsDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _coinsModel(minerPlugins)
{
  _ui.setupUi(this);

  _ui.coinsView->setModel(&_coinsModel);
  _ui.coinsView->setCurrentIndex(_coinsModel.index(0, CoinsModel::Column::Name));

  connect(_ui.coinsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &WalletOptionsDialog::on_coinsView_selectionChanged);
}

void WalletOptionsDialog::on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  if (selected.isEmpty())
  {
    return;
  }

  auto selectedCoin = _coinsModel.coin(selected.indexes().constFirst());
}