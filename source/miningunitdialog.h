#ifndef MININGUNITDIALOG_H
#define MININGUNITDIALOG_H

#include "ui_miningunitdialog.h"
#include "miningunitoptions.h"
#include <MkWidgets/MWidgetSettings>
#include "../coins/coin.h"
#include "../hardware/hwcomponent.h"

class MinerInterface;

class MiningUnitDialog : public QDialog
{
  Q_OBJECT

  public:
             MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent);
             MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, QWidget *parent);
             MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent);
    virtual ~MiningUnitDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    const MiningUnitOptions &options() const;

  private:
    enum class Tab
    {
      Parameters,
      Pool,
      Arguments
    };

    const MinerInterface      *_minerPlugin;
          Ui::MiningUnitDialog _ui;
          MiningUnitOptions    _options;
          MWidgetSettings      _widgetSettings;

    void setupSettings();
    void setupWidgets ()                                          const;
    void setupWidgets (const HwComponent &hwComponent, Coin coin) const;

    virtual void accept() Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_parameterCoin_currentIndexChanged(int index)            const;
    void on_walletAddress_clicked            (bool checked = false) const;
};

#endif