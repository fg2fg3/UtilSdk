#pragma once

#include <QDialog>
#include "ui_JoyStickDialog.h"
#include "JoystickThread.h"
#include <QSettings>
#include <QSerialPort>

class JoyStickDialog : public QDialog
{
	Q_OBJECT

public:
	JoyStickDialog(QWidget *parent = Q_NULLPTR);
	~JoyStickDialog();

private:
	Ui::JoyStickDialog ui;

	JoystickThread*		m_pTrdJoy;

	QSerialPort m_serial;
private slots:
	void OnBtCaptureClicked();
	void OnBtOpenComClicked();
	void OnBtCloseComClicked();
};
