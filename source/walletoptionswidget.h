#ifndef WALLETOPTIONSWIDGET_H
#define WALLETOPTIONSWIDGET_H

#include "ui_walletoptionswidget.h"
#include "walletoptions.h"
#include <MkWidgets/MWidgetSettings>

class Coin;

class WalletOptionsWidget : public QWidget
{
  public:
             WalletOptionsWidget(const Coin &coin, QWidget *parent);
    virtual ~WalletOptionsWidget() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    void accept() const;

  private:
    MWidgetSettings         _widgetSettings;
    WalletOptions           _options;
    Ui::WalletOptionsWidget _ui;

    void setupSettings(const Coin &coin);
};

#endif