#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include "ui_consolewindow.h"

class ConsoleWindow : public QDialog
{
  Q_OBJECT

  public:
             ConsoleWindow(const QString &text);
    virtual ~ConsoleWindow() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    Ui::ConsoleWindow _ui;

  public Q_SLOTS:
    void on_minerWorker_outputLine(const QString &line) const;
};

#endif