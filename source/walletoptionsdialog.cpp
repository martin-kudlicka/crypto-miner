#include "walletoptionsdialog.h"

#include "walletoptionswidget.h"

WalletOptionsDialog::WalletOptionsDialog(MinerPlugins *minerPlugins, QWidget *parent) : QDialog(parent), _coinsModel(minerPlugins)
{
  _ui.setupUi(this);

  _ui.coinsView->setModel(&_coinsModel);

  connect(_ui.coinsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &WalletOptionsDialog::on_coinsView_selectionChanged);

  _ui.coinsView->setCurrentIndex(_coinsModel.index(0, CoinsModel::Column::Name));
}

void WalletOptionsDialog::setCurrentWalletWidget(const Coin &coin)
{
  if (_walletWidgets.contains(coin))
  {
    _ui.walletOptonsStack->setCurrentIndex(_walletWidgets.value(coin));
  }
  else
  {
    auto index = _ui.walletOptonsStack->addWidget(new WalletOptionsWidget(coin, _ui.walletOptonsStack));
    _walletWidgets.insert(coin, index);
    _ui.walletOptonsStack->setCurrentIndex(index);
  }
}

void WalletOptionsDialog::accept()
{
  for (auto index : _walletWidgets)
  {
    auto widget = static_cast<const WalletOptionsWidget *>(_ui.walletOptonsStack->widget(index));
    widget->accept();
  }

  QDialog::accept();
}

void WalletOptionsDialog::on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  if (selected.isEmpty())
  {
    return;
  }

  auto selectedCoin = _coinsModel.coin(selected.indexes().constFirst());
  setCurrentWalletWidget(selectedCoin);
}