#ifndef MININGUNITDIALOG_H
#define MININGUNITDIALOG_H

#include "ui_miningunitdialog.h"
#include "miningunitoptions.h"
#include <MkWidgets/MWidgetSettings>
#include "../coins/coin.h"

class MinerInterface;

struct HwComponent;

class MiningUnitDialog : public QDialog
{
  public:
             MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin::Symbol coinSymbol, QWidget *parent);
             MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin::Symbol coinSymbol, QWidget *parent);
    virtual ~MiningUnitDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    const MiningUnitOptions &options() const;

  private:
    const MinerInterface       *_minerPlugin;
          Ui::MiningUnitDialog  _ui;
          MiningUnitOptions     _options;
          MWidgetSettings       _widgetSettings;

    void setupSettings();
    void setupWidgets () const;

    virtual void accept() Q_DECL_OVERRIDE;
};

#endif