#include "mainwindow.h"

#include "miningunitdialog.h"
#include <MkWidgets/MAboutBox>
#include <MkSupport/MFeedback>

MainWindow::MainWindow() : _miningModel(&_minerPlugins)
{
  _ui.setupUi(this);

  setupWidgets();
}

void MainWindow::setupWidgets()
{
  _ui.miningView->setModel(&_miningModel);

  connect(_ui.miningView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_miningView_selectionChanged);
}

void MainWindow::on_actionAbout_triggered(bool checked /* false */)
{
  MAboutBox(this).exec();
}

void MainWindow::on_actionSendFeedback_triggered(bool checked /* false */) const
{
  MFeedback::createEmailForm();
}

void MainWindow::on_miningUnitAdd_clicked(bool checked /* false */)
{
  // for now take first and only plugin
  auto minerPlugin = _minerPlugins.toList().front();

  MiningUnitDialog minerDialog(minerPlugin, this);
  if (minerDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  _miningModel.insert(minerDialog.options().id());
}

void MainWindow::on_miningUnitStart_clicked(bool checked /* false */)
{
  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);

  miningUnit->start();
}

void MainWindow::on_miningUnitStop_clicked(bool checked /* false */)
{
  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);

  miningUnit->stop();
}

void MainWindow::on_miningView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.miningView->selectionModel()->selectedRows().isEmpty();
  if (isSelected)
  {
    auto index      = _ui.miningView->currentIndex();
    auto miningUnit = _miningModel.miningUnit(index);

    _ui.miningUnitStart->setEnabled(!miningUnit->isRunning());
    _ui.miningUnitStop->setEnabled(miningUnit->isRunning());
  }
  else
  {
    _ui.miningUnitStart->setEnabled(false);
    _ui.miningUnitStop->setEnabled(false);
  }
}