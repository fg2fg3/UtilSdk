﻿#include "UtilGui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>
#include "OpencvDemoDialog.h"
#include "UtilSdk.h"
#include <windows.h>
#include <tchar.h>
#include "zip.h"
#include "unzip.h"
#include <QsqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "ringbuffert.h"
#include "qringbuffer.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include "cJSON.h"

#define USE_QRINGBUFFER 0

std::string TCHAR2STRING(TCHAR *STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	delete chRtn;
	return str;
}

/************************************************************************
*   功能：将一个十六进制字节串转换成 ASCII 码表示的十六进制的字符串
*   输入参数：pHex    -- 十六进制数字节串首地址
*            pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            nLen    -- 要转换的十六进制数的长度（字节数）
*   输出参数：None
*   注：  转换后的结果全部是大写 ASCII 表示的十六进制数
************************************************************************/
void HexToAscii(unsigned char * pHex, unsigned char * pAscii, int nLen)
{
	unsigned char Nibble[2];

	for (int i = 0; i < nLen; i++)
	{
		Nibble[0] = (pHex[i] & 0xF0) >> 4;
		Nibble[1] = pHex[i] & 0x0F;
		for (int j = 0; j < 2; j++)
		{
			if (Nibble[j] < 10)
				Nibble[j] += 0x30;
			else
			{
				if (Nibble[j] < 16)
					Nibble[j] = Nibble[j] - 10 + 'A';
			}
			*pAscii++ = Nibble[j];
		}   // for (int j = ...)
	}   // for (int i = ...)
}

/****************************************************************************
*   功能：将一个 ASCII 码表示的十六进制字符串转换成十六进制的字节串
*   输入参数：pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            pHex   -- 十六进制数字节串首地址
*            nLen   -- 要转换的 ASCII 码表示的十六进制字符串的长度（字节数）
*   输出参数：None
*   注：  要求输入的 ASCII 码表示的十六进制数的字符个数必须为偶数，除了是1 - 9 和 A(a) - F(f) 以外没有别的字符
****************************************************************************/
void AsciiToHex(unsigned char * pAscii, unsigned char * pHex, int nLen)
{
	if (nLen % 2)
		return;
	int nHexLen = nLen / 2;

	for (int i = 0; i < nHexLen; i++)
	{
		unsigned char Nibble[2];
		Nibble[0] = *pAscii++;
		Nibble[1] = *pAscii++;
		for (int j = 0; j < 2; j++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble[j] = Nibble[j] - '0';
			else
				return;
		}   // for (int j = ...)
		pHex[i] = Nibble[0] << 4;   // Set the high nibble
		pHex[i] |= Nibble[1];   //Set the low nibble
	}   // for (int i = ...)
}

void string2tchar(std::string &src, TCHAR* buf)
{
#ifdef UNICODE  
	_stprintf_s(buf, MAX_PATH, _T("%S"), src.c_str());//%S宽字符  
#else  
	_stprintf_s(buf, MAX_PATH, _T("%s"), src.c_str());//%s单字符
#endif
}

UtilGui::UtilGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	SetupUI();
	InitVar();
	PrepareStyle();
	PrepareSlot();
}

void UtilGui::SetupUI()
{

}

void UtilGui::InitVar()
{

}

void UtilGui::PrepareStyle()
{
	serial = new QSerialPort;
}

void UtilGui::PrepareSlot()
{
	connect(ui.m_pBtChineseSupport, SIGNAL(clicked()), this, SLOT(OnBtChineseSupportClicked()));
	connect(ui.m_pBtCompare, SIGNAL(clicked()), this, SLOT(OnBtCompareClicked()));
	connect(ui.m_pBtJoyStick, SIGNAL(clicked()), this, SLOT(OnBtJoyStickClicked()));
	connect(ui.m_pBtOpencvDemo, SIGNAL(clicked()), this, SLOT(OnBtOpencvDemoClicked()));
	connect(ui.m_pBtZipFile, SIGNAL(clicked()), this, SLOT(OnBtZipFileClicked()));
	connect(ui.m_pBtUnzipFile, SIGNAL(clicked()), this, SLOT(OnBtUnzipFileClicked()));
	connect(ui.m_pBtSqlite, SIGNAL(clicked()), this, SLOT(OnBtSqliteClicked()));
	connect(ui.m_pBtHexString, SIGNAL(clicked()), this, SLOT(OnBtHexString()));
	connect(ui.m_pBtSerialPort, SIGNAL(clicked()), this, SLOT(OnBtSerialPort()));
	connect(ui.m_pBtCloseSerialPort, SIGNAL(clicked()), this, SLOT(OnBtCloseSerialPort()));
	connect(ui.m_pBtStartQueue, SIGNAL(clicked()), this, SLOT(OnBtStartQueue()));
	connect(ui.m_pBtStopQueue, SIGNAL(clicked()), this, SLOT(OnBtStopQueue()));
	connect(ui.m_pBtQueueSize, SIGNAL(clicked()), this, SLOT(OnBtQueueSize()));
	connect(ui.m_pBtPrint, SIGNAL(clicked()), this, SLOT(OnBtPrint()));
	connect(ui.m_pBtJson2Db, SIGNAL(clicked()), this, SLOT(OnBtJson2Db()));
}

void UtilGui::OnBtChineseSupportClicked()
{
	QString qslPath = QFileDialog::getOpenFileName(this, "D:/", "*.*");

	ui.m_pLbPath->setText(qslPath);

	QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题  
	std::string name = code->fromUnicode(qslPath).data();

	FILE* fp = fopen(name.c_str(), "r");
	if (fp == nullptr)
	{
		QMessageBox::warning(this, "提醒", qslPath);
	}
	fclose(fp);
}

void UtilGui::OnBtCompareClicked()
{
	//字符比较
	char a[] = "abc";
	char b[] = "bbc";
	if (a[1] == b[1])//字符比较
	{
		qDebug() << "Same";
	}
	else
	{
		qDebug() << "not same";
	}

	//另外的比较方式
	char c[] = { 0x00, 0x01, 0x03, 0x04 };
	char d[] = { 0x00, 0x01, 0x03, 0x05 };
	int t1 = 0, t2 = 0;
	memcpy((char*)&t1, c, 4);//4可以换为3等任意长度但是不可以超过t1的长度
	memcpy((char*)&t2, d, 4);
	if (t1 == t2)
	{
		qDebug() << "Same";
	}
	else
	{
		qDebug() << "Not Same";
	}
}

void UtilGui::OnBtJoyStickClicked()
{
	JoyStickDialog dlgJoy;
	dlgJoy.exec();
}

void UtilGui::closeEvent(QCloseEvent *event)
{
//	QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("关闭中!"));
	if (serial != nullptr)
	{
		serial->clear();
		serial->close();
		serial->deleteLater();
	}
}

void UtilGui::OnBtOpencvDemoClicked()
{
	OpencvDemoDialog dlgOpencv;
	dlgOpencv.exec();
}

void UtilGui::OnBtZipFileClicked()
{
	QString qsZipPath = qApp->applicationDirPath() + "/files/" + "2.zip";
	QString qsFile = qApp->applicationDirPath() + "/files/" + "1.flv";
	HZIP hz; DWORD writ;


	TCHAR zipPath[MAX_PATH] = { 0 };
	TCHAR fileAdd[MAX_PATH] = { 0 };
	string2tchar(qsZipPath.toStdString(), zipPath);
	string2tchar(qsFile.toStdString(), fileAdd);

	// EXAMPLE 1 - create a zipfile from existing files
	hz = CreateZip(zipPath, 0);
	ZipAdd(hz,fileAdd, fileAdd);
	//ZipAdd(hz, _T("znsimple.txt"), _T("\\simple.txt"));
	CloseZip(hz);
	//_tprintf(_T("Created '\\simple1.zip'\n"));
}

void UtilGui::OnBtUnzipFileClicked()
{
	QString qsSrc = qApp->applicationDirPath() + "/files/" + "1.zip";
	QString qsDestDir = qApp->applicationDirPath() + "/files/" ;
	//UTILSDK_UnzipFile(qsDest.toStdString().c_str(), qsSrc.toStdString().c_str());
	HZIP hz; DWORD writ;

	// EXAMPLE 1 - create a zipfile from existing files
	//hz = CreateZip(_T("\\simple1.zip"), 0);
	//ZipAdd(hz, _T("znsimple.bmp"), _T("\\simple.bmp"));
	//ZipAdd(hz, _T("znsimple.txt"), _T("\\simple.txt"));
	//CloseZip(hz);
	//_tprintf(_T("Created '\\simple1.zip'\n"));

	std::string res = qsSrc.toStdString();
	std::string sDstDir = qsDestDir.toStdString();

	TCHAR zipPath[MAX_PATH] = { 0 };
	TCHAR destDir[MAX_PATH] = { 0 };
	string2tchar(res, zipPath);
	string2tchar(sDstDir, destDir);
	hz = OpenZip(zipPath, 0);
	SetUnzipBaseDir(hz, destDir);
	ZIPENTRY ze; GetZipItem(hz, -1, &ze); int numitems = ze.index;
	for (int zi = 0; zi < numitems; zi++)
	{
		GetZipItem(hz, zi, &ze);
		UnzipItem(hz, zi, ze.name);
	}
	CloseZip(hz);
}

char* UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}

void UtilGui::OnBtSqliteClicked()
{
	//首先建立util.db数据库并用navicatmysql初始化
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	db.setDatabaseName("./testdatabase.db");

	if (!db.open())
	{
		qDebug() << db.lastError();
		qFatal("Failed to connect.");
	}

	qDebug("Connected!");

	QSqlQuery qry;

	qry.prepare("CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30))");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug() << "Table created!";

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (1, 'John', 'Doe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (2, 'Jane', 'Doe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (3, 'James', 'Doe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (4, 'Judy', 'Doe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (5, 'Richard', 'Roe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (6, 'Jane', 'Roe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (7, 'John', 'Noakes')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (8, 'Donna', 'Doe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (9, 'Ralph', 'Roe')");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Inserted!");

	qry.prepare("SELECT * FROM names");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
	{
		qDebug("Selected!");

		QSqlRecord rec = qry.record();

		int cols = rec.count();

		for (int c = 0; c < cols; c++)
			qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

		for (int r = 0; qry.next(); r++)
			for (int c = 0; c < cols; c++)
				qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
	}


	qry.prepare("SELECT firstname, lastname FROM names WHERE lastname = 'Roe'");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
	{
		qDebug("Selected!");

		QSqlRecord rec = qry.record();

		int cols = rec.count();

		for (int c = 0; c < cols; c++)
			qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

		for (int r = 0; qry.next(); r++)
			for (int c = 0; c < cols; c++)
				qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
	}


	qry.prepare("SELECT firstname, lastname FROM names WHERE lastname = 'Roe' ORDER BY firstname");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
	{
		qDebug("Selected!");

		QSqlRecord rec = qry.record();

		int cols = rec.count();

		for (int c = 0; c < cols; c++)
			qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

		for (int r = 0; qry.next(); r++)
			for (int c = 0; c < cols; c++)
				qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
	}


	qry.prepare("SELECT lastname, COUNT(*) as 'members' FROM names GROUP BY lastname ORDER BY lastname");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
	{
		qDebug("Selected!");

		QSqlRecord rec = qry.record();

		int cols = rec.count();

		for (int c = 0; c < cols; c++)
			qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

		for (int r = 0; qry.next(); r++)
			for (int c = 0; c < cols; c++)
				qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
	}

	qry.prepare("UPDATE names SET firstname = 'Nisse', lastname = 'Svensson' WHERE id = 7");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Updated!");

	qry.prepare("UPDATE names SET lastname = 'Johnson' WHERE firstname = 'Jane'");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Updated!");

	qry.prepare("DELETE FROM names WHERE id = 7");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Deleted!");

	qry.prepare("DELETE FROM names WHERE lastname = 'Johnson'");
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug("Deleted!");

	db.close();
}

void UtilGui::OnBtHexString()
{
	unsigned char hex[5] = { 0x23, 0x3A, 0x46, 0x4C, 0x52 };
	unsigned char hexString[10] = { 0 };
	HexToAscii(hex, hexString, 5);
	HexToAscii(hex, hexString, 10);
}

void UtilGui::OnBtSerialPort()
{

	//设置串口名
	serial->setPortName("COM1");
	//打开串口
	serial->open(QIODevice::ReadWrite);
	//设置波特率
	serial->setBaudRate(115200);
	//设置数据位
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	char cmd[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00 };
	serial->write("111111");
	serial->write("222222");
	serial->write("333333");
	serial->write(cmd);
	//write完毕不可以清除，否则啥也发不出去
	//serial->clear();
	//serial->close();
	//serial->deleteLater();

	//以下这种方式是发不出去的
	//QString qsCom = "COM1";
	//QSerialPort m_pSerial ;
	//m_pSerial.setPortName(qsCom);
	//以读写方式打开串口  
	//if (m_pSerial.open(QIODevice::ReadWrite))
	//{
	//	设置波特率  
	//	m_pSerial.setBaudRate(QSerialPort::Baud115200);
	//	设置数据位  
	//	m_pSerial.setDataBits(QSerialPort::Data8);
	//	设置校验位  
	//	m_pSerial.setParity(QSerialPort::NoParity);
	//	设置流控制  
	//	m_pSerial.setFlowControl(QSerialPort::NoFlowControl);
	//	设置停止位  
	//	m_pSerial.setStopBits(QSerialPort::OneStop);
	//	qWarning() << "Open " << qsCom << " OK!";
	//}
	//else
	//{
	//	qDebug() << "Could not open!" << qsCom;
	//}
	//qDebug() << "Thread start!";

	//int i = 5;
	//while (i--)
	//{
	//	m_pSerial.write("5555556666666");
	//	qDebug() << m_pSerial.error();
	//}
}

void UtilGui::OnBtCloseSerialPort()
{
	if (serial)
	{
		serial->clear();
		serial->close();
		serial->deleteLater();
		serial = nullptr;
	}
}

//高速无锁队列
void UtilGui::OnBtStartQueue()
{
#if USE_QRINGBUFFER
	QRingBuffer buffer;

	cout << "buffer size:" << buffer.size() << endl;

	char data1[48] = { 0x55 };
	char data2[8] = { 0 };
	cout << "buffer can read:" << buffer.canRead() << endl;
	cout << "buffer can write:" << buffer.canWrite() << endl;
	cout << "buffer writing..." << endl;
	buffer.write(data1, sizeof(data1));
	cout << "buffer can read:" << buffer.canRead() << endl;
	cout << "buffer can write:" << buffer.canWrite() << endl;
	cout << "buffer reading..." << endl;
	buffer.read(data2, 8);
	cout << "buffer can read:" << buffer.canRead() << endl;
	cout << "buffer can write:" << buffer.canWrite() << endl;

	cout << "HelloWorld!" << endl;
#else
	RingBuffer<int> q(5);
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);
	q.push_back(4);
	for (int i = 0; i < 4; i++)
		cout << q.pop_front() << endl;
	q.push_back(5);
	q.push_back(5);
	q.push_back(5);
	while (!q.isEmpty())//不判空就pop会崩
	{
		cout << q.pop_front() << endl;
	}
#endif

}

MyClass::MyClass()
{
	qDebug() << "Has inited!";
}

MyClass::~MyClass()
{
	qDebug() << "Ready to delete this!";
}



void UtilGui::OnBtStopQueue()
{
	MyClass my;	
	vecMy.push_back(my);
	vecMy.push_back(my);
	vecMy.push_back(my);
	qDebug() << "Vector size is " << vecMy.size();
	//vector等压入的时候是拷贝，之前的my结构体在出函数后就释放了
}

void UtilGui::OnBtQueueSize()
{
	qDebug() << "Vector size is " << vecMy.size();//此处得到是3，因为上个函数压入了3个数据
	vecMy.clear();
}

void UtilGui::OnBtPrint()
{
	QPrinter printer(QPrinter::HighResolution);
	printer.setPageSize(QPagedPaintDevice::A4);
	QPrintDialog printDialog(&printer, this);
	if (printDialog.exec()){
		QTextDocument textDocument;
		textDocument.print(&printer);
	}
}

void UtilGui::OnBtJson2Db()
{
	//首先建立util.db数据库并用navicatmysql初始化字段
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	db.setDatabaseName("./testdatabase.db");

	if (!db.open())
	{
		qDebug() << db.lastError();
		qFatal("Failed to connect.");
	}

	qDebug("Connected!");

	QSqlQuery qry;

	std::string sRet = QString::fromWCharArray(L"汉字").toStdString();

	//使用Cjson看看效果,如下方式写入数据库也是可以的,jsoncpp-1.8.4会把中文字符转为Unicode保存，在utf8的数据库里不可直接读出
	cJSON *base = cJSON_CreateObject();
	cJSON_AddStringToObject(base, "BS", "-1");
	cJSON_AddStringToObject(base, "Msg", UnicodeToUtf8(L"操作成功！"));
	char *str = cJSON_Print(base);

	char buf[1024] = "\0";
	memset(buf, 0, 1024);
	sprintf(buf, "INSERT INTO names (id,firstname) VALUES (10,'%s')", str);
	qry.prepare(QString(buf));
	if (!qry.exec())
		qDebug() << qry.lastError();
	else
		qDebug() << "Insert Ok! ";

	db.close();
}