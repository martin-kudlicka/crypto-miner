#ifndef MININGUNITDIALOG_H
#define MININGUNITDIALOG_H

#include "ui_miningunitdialog.h"
#include "miningunitoptions.h"
#include "../coins/coin.h"
#include "../hardware/hwcomponent.h"

class MinerInterface;

class MiningUnitDialog : public MOptionsDialog<Ui::MiningUnitDialog, MiningUnitOptions>
{
  Q_OBJECT

  public:
             MiningUnitDialog(const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent);
             MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, QWidget *parent);
             MiningUnitDialog(const MUuidPtr &id, const MinerInterface *minerPlugin, const HwComponent &hwComponent, Coin coin, QWidget *parent);
    virtual ~MiningUnitDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    enum class Tab
    {
      Parameters,
      Pool,
      Arguments
    };

    const MinerInterface *_minerPlugin;

    void setupWidgets(const HwComponent &hwComponent, Coin coin) const;

    virtual void accept       ()       Q_DECL_OVERRIDE;
    virtual void setupSettings()       Q_DECL_OVERRIDE;
    virtual void setupWidgets () const Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_parameterCoin_currentIndexChanged(int index)            const;
    void on_walletAddress_clicked            (bool checked = false) const;
};

#endif