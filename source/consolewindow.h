#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include "ui_consolewindow.h"

class ConsoleWindow : public QDialog
{
  public:
             ConsoleWindow();
    virtual ~ConsoleWindow() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    Ui::ConsoleWindow _ui;
};

#endif