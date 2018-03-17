#ifndef MINERSELECTIONDIALOG_H
#define MINERSELECTIONDIALOG_H

#include "ui_minerselectiondialog.h"
#include "hardwaremodel.h"
#include "coinsmodel.h"
#include "minermodel.h"

class MinerPlugins;

class MinerSelectionDialog : public QDialog
{
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

    void setupWidgets();
};

#endif