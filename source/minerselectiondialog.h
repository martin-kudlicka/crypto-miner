#ifndef MINERSELECTIONDIALOG_H
#define MINERSELECTIONDIALOG_H

#include "ui_minerselectiondialog.h"
#include "hardwaremodel.h"
#include "coinsmodel.h"
#include "minermodel.h"

class MinerPlugins;

class MinerSelectionDialog : public QDialog
{
  Q_OBJECT

  public:
             MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent);
    virtual ~MinerSelectionDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    Ui::MinerSelectionDialog _ui;
    Coin::SymbolList         _supportedCoins;
    CoinsModel               _coinsModel;
    HwComponentList          _supportedHwComponents;
    HardwareModel            _hardwareModel;
    MinerPlugins            *_minerPlugins;
    MinerModel               _minerModel;
    QModelIndex              _lastSelectedHwComponent;
    QModelIndex              _lastSelectedCoin;
    QModelIndex              _lastSelectedMiner;

    void setupWidgets();

  private Q_SLOTS:
    void on_hwComponentsView_clicked(const QModelIndex &index);
    void on_coinsView_clicked       (const QModelIndex &index);
    void on_minerView_clicked       (const QModelIndex &index);
};

#endif