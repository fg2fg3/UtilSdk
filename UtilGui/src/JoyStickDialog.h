#pragma once

#include <QDialog>
#include "ui_JoyStickDialog.h"

class JoyStickDialog : public QDialog
{
	Q_OBJECT

public:
	JoyStickDialog(QWidget *parent = Q_NULLPTR);
	~JoyStickDialog();

private:
	Ui::JoyStickDialog ui;
};