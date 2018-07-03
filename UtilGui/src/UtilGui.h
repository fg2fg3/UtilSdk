#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UtilGui.h"
#include "JoyStickDialog.h"

class MyClass;
class UtilGui : public QMainWindow
{
	Q_OBJECT

public:
	UtilGui(QWidget *parent = Q_NULLPTR);

private:
	Ui::UtilGuiClass ui;
	QSerialPort *serial; 
	std::vector<MyClass> vecMy;

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
	void OnBtQueueSize();
	void OnBtPrint();
	void OnBtJson2Db();

protected:
	void closeEvent(QCloseEvent *event);
};

class MyClass
{
public:
	MyClass();
	~MyClass();

private:

};
