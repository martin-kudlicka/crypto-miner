#ifndef MININGUNITDIALOG_H
#define MININGUNITDIALOG_H

#include "ui_miningunitdialog.h"
#include "miningunitoptions.h"
#include <MkWidgets/MWidgetSettings>

class MinerInterface;

class MiningUnitDialog : public QDialog
{
  public:
             MiningUnitDialog(const MinerInterface *miner, QWidget *parent);
    virtual ~MiningUnitDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const MinerInterface *_miner;
    Ui::MiningUnitDialog  _ui;
    MiningUnitOptions     _options;
    MWidgetSettings       _widgetSettings;

    void setupSettings();
    void setupWidgets () const;

    virtual void accept() Q_DECL_OVERRIDE;
};

#endif