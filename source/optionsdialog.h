#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_optionsdialog.h"

class OptionsDialog : public QDialog
{
	public:
		         OptionsDialog(QWidget *parent);
		virtual ~OptionsDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

	private:
		Ui::OptionsDialog _ui;

    void setupSettings() const;

    virtual void accept() Q_DECL_OVERRIDE;
};

#endif