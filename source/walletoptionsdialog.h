#ifndef WALLETOPTIONSDIALOG_H
#define WALLETOPTIONSDIALOG_H

#include "ui_walletoptionsdialog.h"
#include "coinsmodel.h"

class WalletOptionsDialog : public QDialog
{
  public:
             WalletOptionsDialog(MinerPlugins *minerPlugins, QWidget *parent);
    virtual ~WalletOptionsDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    CoinsModel              _coinsModel;
    QHash<Coin, int>        _walletWidgets;
    Ui::WalletOptionsDialog _ui;

    void setCurrentWalletWidget(const Coin &coin);

    virtual void accept() Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_coinsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif