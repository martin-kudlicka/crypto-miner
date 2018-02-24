#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "minerplugins.h"
#include "miningmodel.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
             MainWindow();
    virtual ~MainWindow() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    Ui::MainWindow _ui;
    MinerPlugins   _minerPlugins;
    MiningModel    _miningModel;

    void setupWidgets();

  private Q_SLOTS:
    void on_miningUnitAdd_clicked      (bool checked = false);
    void on_miningView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
};

#endif