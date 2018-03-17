#ifndef MINERSELECTIONDIALOG_H
#define MINERSELECTIONDIALOG_H

#include "ui_minerselectiondialog.h"
#include "hardwaremodel.h"

class MinerPlugins;

class MinerSelectionDialog : public QDialog
{
  public:
             MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent);
    virtual ~MinerSelectionDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    HwComponentList          _supportedHwComponents;
    HardwareModel            _hardwareModel;
    MinerPlugins            *_minerPlugins;
    Ui::MinerSelectionDialog _ui;

    void setupWidgets();
};

#endif