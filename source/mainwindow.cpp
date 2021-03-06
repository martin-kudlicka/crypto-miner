#include "mainwindow.h"

#include "miningunitdialog.h"
#include <MkWidgets/MAboutBox>
#include <MkSupport/MFeedback>
#include "optionsdialog.h"
#include "options.h"
#include "minerselectiondialog.h"
#include "walletoptionsdialog.h"

MainWindow::MainWindow() : _miningModel(&_minerPlugins)
{
  _ui.setupUi(this);

  setupWidgets();

  if (gOptions->mineOnStartup())
  {
    for (auto row = 0; row < _miningModel.rowCount(); ++row)
    {
      auto miningUnit = _miningModel.miningUnit(row);
      miningUnit->start();
    }
  }
}

void MainWindow::setupWidgets()
{
  _ui.miningView->setModel(&_miningModel);

  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::Status),      QHeaderView::ResizeToContents);
  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::Miner),       QHeaderView::Stretch);
  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::HwComponent), QHeaderView::ResizeToContents);
  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::Coin),        QHeaderView::ResizeToContents);
  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::HashRate),    QHeaderView::ResizeToContents);
  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::ResultETA),   QHeaderView::ResizeToContents);
  _ui.miningView->header()->setSectionResizeMode(static_cast<int>(MiningModel::Column::Results),     QHeaderView::ResizeToContents);

  connect(_ui.miningView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_miningView_selectionChanged);
}

void MainWindow::on_actionAbout_triggered(bool checked /* false */)
{
  MAboutBox(this).exec();
}

void MainWindow::on_actionOptions_triggered(bool checked /* false */)
{
  OptionsDialog optionsDialog(this);
  optionsDialog.exec();
}

void MainWindow::on_actionSendFeedback_triggered(bool checked /* false */) const
{
  MFeedback::createEmailForm();
}

void MainWindow::on_actionWallets_triggered(bool checked /* false */)
{
  WalletOptionsDialog walletOptionsDialog(&_minerPlugins, this);
  walletOptionsDialog.exec();
}

void MainWindow::on_miningUnit_finished()
{
  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);
  if (miningUnit)
  {
    _ui.miningUnitRemove->setEnabled(!miningUnit->isRunning());
    _ui.miningUnitStart->setEnabled(!miningUnit->isRunning());
    _ui.miningUnitStop->setEnabled(miningUnit->isRunning());
  }
}

void MainWindow::on_miningUnit_started()
{
  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);

  _ui.miningUnitRemove->setEnabled(!miningUnit->isRunning());
  _ui.miningUnitStart->setEnabled(!miningUnit->isRunning());
  _ui.miningUnitStop->setEnabled(miningUnit->isRunning());
}

void MainWindow::on_miningUnitAdd_clicked(bool checked /* false */)
{
  MinerSelectionDialog minerSelectionDialog(&_minerPlugins, this);
  if (minerSelectionDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  auto minerPlugin = minerSelectionDialog.selectedMiner();

  MiningUnitDialog miningUnitDialog(minerPlugin, minerSelectionDialog.selectedHwComponent(), minerSelectionDialog.selectedCoin(), this);
  if (miningUnitDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  _miningModel.insert(miningUnitDialog.options().id());
}

void MainWindow::on_miningUnitConsole_clicked(bool checked /* false */)
{
  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);

  miningUnit->showConsole();
}

void MainWindow::on_miningUnitEdit_clicked(bool checked /* false */)
{
  auto index       = _ui.miningView->currentIndex();
  auto id          = _miningModel.id(index);
  auto miningUnit  = _miningModel.miningUnit(index);
  auto minerPlugin = miningUnit->minerPlugin();

  MiningUnitDialog miningUnitDialog(id, minerPlugin, this);
  if (miningUnitDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  if (miningUnit->isRunning())
  {
    miningUnit->restart();
  }
}

void MainWindow::on_miningUnitRemove_clicked(bool checked /* false */)
{
  auto index = _ui.miningView->currentIndex();
  _miningModel.remove(index);
}

void MainWindow::on_miningUnitStart_clicked(bool checked /* false */)
{
  _ui.miningUnitStart->setEnabled(false);

  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);

  connect(&*miningUnit, &MiningUnit::started,  this, &MainWindow::on_miningUnit_started,  Qt::UniqueConnection);
  connect(&*miningUnit, &MiningUnit::finished, this, &MainWindow::on_miningUnit_finished, Qt::UniqueConnection);

  miningUnit->start();
}

void MainWindow::on_miningUnitStop_clicked(bool checked /* false */)
{
  _ui.miningUnitStop->setEnabled(false);

  auto index      = _ui.miningView->currentIndex();
  auto miningUnit = _miningModel.miningUnit(index);

  miningUnit->stop();
}

void MainWindow::on_miningView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  auto isSelected = !_ui.miningView->selectionModel()->selectedRows().isEmpty();

  _ui.miningUnitEdit->setEnabled(isSelected);
  _ui.miningUnitConsole->setEnabled(isSelected);

  if (isSelected)
  {
    auto index      = _ui.miningView->currentIndex();
    auto miningUnit = _miningModel.miningUnit(index);

    _ui.miningUnitRemove->setEnabled(!miningUnit->isRunning());
    _ui.miningUnitStart->setEnabled(!miningUnit->isRunning());
    _ui.miningUnitStop->setEnabled(miningUnit->isRunning());
  }
  else
  {
    _ui.miningUnitStart->setEnabled(false);
    _ui.miningUnitStop->setEnabled(false);
    _ui.miningUnitConsole->setEnabled(false);
  }
}