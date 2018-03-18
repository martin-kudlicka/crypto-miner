#ifndef MINERSELECTIONDIALOG_H
#define MINERSELECTIONDIALOG_H

#include "ui_minerselectiondialog.h"
#include "hardwaremodel.h"
#include "coinsmodel.h"
#include "minersmodel.h"

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
    MinersModel              _minersModel;

    void setupWidgets  ();
    void updateOkButton() const;

  private Q_SLOTS:
    void on_coinsView_selectionChanged       (const QItemSelection &selected, const QItemSelection &deselected) const;
    void on_hwComponentsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
    void on_minersView_selectionChanged      (const QItemSelection &selected, const QItemSelection &deselected) const;
};

#endif