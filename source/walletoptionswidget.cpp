#include "walletoptionswidget.h"

WalletOptionsWidget::WalletOptionsWidget(const Coin &coin, QWidget *parent) : QWidget(parent), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupSettings(coin);
}

void WalletOptionsWidget::accept() const
{
  _widgetSettings.save();
}

void WalletOptionsWidget::setupSettings(const Coin &coin)
{
  _widgetSettings.setWidget(_options.addressProperty(coin), _ui.address);

  _widgetSettings.load();
}