#ifndef MININGUNITDIALOG_H
#define MININGUNITDIALOG_H

#include "ui_miningunitdialog.h"

class MiningUnitDialog : public QDialog
{
  public:
             MiningUnitDialog(QWidget *parent);
    virtual ~MiningUnitDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif