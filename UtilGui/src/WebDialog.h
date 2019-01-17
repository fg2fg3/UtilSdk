#pragma once

#include <QDialog>
#include "ui_WebDialog.h"
#include <QtWebKit/QtWebKit>


class WebDialog : public QDialog
{
	Q_OBJECT

public:
	WebDialog(QWidget *parent = Q_NULLPTR);
	~WebDialog();

private:
	Ui::WebDialog ui;
};
