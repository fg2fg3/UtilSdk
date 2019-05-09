#pragma once

#include "zmq.h"
#include "zmq_utils.h"
#include <QtWidgets/QMainWindow>
#include "ui_UtilGui.h"
#include "JoyStickDialog.h"
#include <string.h>
#include <stdio.h>
//#include <unistd.h>

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
	HANDLE hThreadClient;
	HANDLE hThreadServer;
	DWORD  dwClientTrdId;
	DWORD  dwServerTrdId;
	MyClass* m_pServer;
	MyClass* m_pClient;

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
	void OnBtWeb();
	void OnBtStartThreadClicked();
	void OnBtStopThreadClicked();
	void OnBtRapidJsonReadClicked();
	void OnBtRapidJsonWriteClicked();

protected:
	void closeEvent(QCloseEvent *event);
};

class MyClass
{
public:
	MyClass();
	~MyClass();
	bool isClose(){
		return m_bClose;
	}

	void Stop(){ m_bClose = true; }

	void ProcClient();
	void ProcServer();


	void* m_hSvrContext;
	void* m_hResponser;

	void* m_hClientContext;
	void* m_hRequest;
private:
	bool m_bClose;
};
