#ifndef MINERSELECTIONDIALOG_H
#define MINERSELECTIONDIALOG_H

#include "ui_minerselectiondialog.h"
#include "hardwaremodel.h"
#include "coinsmodel.h"
#include "minersmodel.h"
#include <QtCore/QSettings>

class MinerPlugins;

class MinerSelectionDialog : public QDialog
{
  Q_OBJECT

  public:
             MinerSelectionDialog(MinerPlugins *minerPlugins, QWidget *parent);
    virtual ~MinerSelectionDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    Coin            selectedCoin       () const;
    HwComponent     selectedHwComponent() const;
    MinerInterface *selectedMiner      () const;

  private:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString OperatingSystemSupportedOnly;
    };

    MinerInterfacePtrSet     _allowedCoinMiners;
    MinerInterfacePtrSet     _allowedHwComponentMiners;
    MinerInterfacePtrSet     _allowedMinerMiners;
    CoinsModel               _coinsModel;
    HardwareModel            _hardwareModel;
    MinerPlugins            *_minerPlugins;
    MinersModel              _minersModel;
    MinerInterfacePtrSet     _coinMiners;
    MinerInterfacePtrSet     _hwComponentMiners;
    MinerInterface          *_minersMiner;
    Ui::MinerSelectionDialog _ui;
    QSettings                _settings;

    void refreshAllowedMiners();
    void refreshOkButton     () const;
    void setupWidgets        ();

  private Q_SLOTS:
    void on_coinsView_selectionChanged          (const QItemSelection &selected, const QItemSelection &deselected);
    void on_hwComponentsView_selectionChanged   (const QItemSelection &selected, const QItemSelection &deselected);
    void on_minersView_selectionChanged         (const QItemSelection &selected, const QItemSelection &deselected);
    void on_operatingSystemSupportedOnly_toggled(bool checked);
};

#endif