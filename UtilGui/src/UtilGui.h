#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UtilGui.h"
#include "JoyStickDialog.h"

class UtilGui : public QMainWindow
{
	Q_OBJECT

public:
	UtilGui(QWidget *parent = Q_NULLPTR);

private:
	Ui::UtilGuiClass ui;
	QSerialPort *serial;

	void PrepareSlot();
	void PrepareStyle();
	void SetupUI();
	void InitVar();

private slots:
	void OnBtChineseSupportClicked();
	void OnBtCompareClicked();
	void OnBtJoyStickClicked();
	void OnBtOpencvDemoClicked();
	void OnBtZipFileClicked();
	void OnBtUnzipFileClicked();
	void OnBtSqliteClicked();
	void OnBtHexString();
	void OnBtSerialPort();
	void OnBtCloseSerialPort();
	void OnBtStartQueue();
	void OnBtStopQueue();

protected:
	void closeEvent(QCloseEvent *event);
};
