#include "mainwindow.h"

#include "miningunitdialog.h"

MainWindow::MainWindow()
{
  _ui.setupUi(this);
}

void MainWindow::on_miningUnitAdd_clicked(bool checked /* false */)
{
  // for now take first and only plugin
  auto minerPlugin = _minerPlugins.plugins().front();

  MiningUnitDialog minerDialog(*minerPlugin, this);
  if (minerDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  // TODO
}