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

    virtual void closeEvent(QCloseEvent *event);

  private Q_SLOTS:
    void on_actionAbout_triggered       (bool checked = false);
    void on_actionSendFeedback_triggered(bool checked = false) const;
    void on_miningUnitAdd_clicked       (bool checked = false);
    void on_miningUnitConsole_clicked   (bool checked = false);
    void on_miningUnitEdit_clicked      (bool checked = false);
    void on_miningUnitRemove_clicked    (bool checked = false);
    void on_miningUnitStart_clicked     (bool checked = false);
    void on_miningUnitStop_clicked      (bool checked = false);
    void on_miningView_selectionChanged (const QItemSelection &selected, const QItemSelection &deselected);
};

#endif