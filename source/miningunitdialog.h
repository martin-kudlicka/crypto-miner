#ifndef MININGUNITDIALOG_H
#define MININGUNITDIALOG_H

#include "ui_miningunitdialog.h"

class MinerInterface;

class MiningUnitDialog : public QDialog
{
  public:
             MiningUnitDialog(const MinerInterface *miner, QWidget *parent);
    virtual ~MiningUnitDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    const MinerInterface *_miner;
    Ui::MiningUnitDialog  _ui;

    void setupWidgets() const;
};

#endif