#include "UtilGui.h"
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
#include "WebDialog.h"
#include <stdlib.h> 
#include <stdio.h> 
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"  
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
//#include "BoostCS.h"
#include <winsock2.h> 

#pragma comment(lib,"ws2_32.lib")  
using namespace rapidjson;
using namespace std;

#define USE_QRINGBUFFER 0

#define ENABLE_ZMQ 1

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

#include <stdio.h>
#include <string.h>

//字符转换成整形
int hex2int(char c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		return c - 'A' + 10;
	}
	else if ((c >= 'a') && (c <= 'z'))
	{
		return c - 'a' + 10;
	}
	else if ((c >= '0') && (c <= '9'))
	{
		return c - '0';
	}
	return false;
}

int HexString2int(QString qsHex)
{
	//十六进制字符串转换成整形
	const char* hexStr = qsHex.toStdString().c_str();
	int data[32] = { 0 };
	int count = 0;
	for (int i = 0; i<strlen(hexStr); i += 2)
	{
		int high = hex2int(hexStr[i]);   //高四位
		int low = hex2int(hexStr[i + 1]); //低四位
		data[count++] = (high << 4) + low;
	}
	//打印输出
	for (int i = 0; i<strlen(hexStr) / 2; i++)
	{
		printf("%d ", data[i]);
	}
	return 1;
}
//void convertStringToHex(const QString &str, QByteArray &byteData) 
//{
//	int hexdata, lowhexdata; 
//	int hexdatalen = 0; 
//	int len = str.length(); 
//	byteData.resize(len / 2); 
//	char lstr, hstr;
//	for (int i = 0; i<len;) 
//	{ //char lstr, 
//		hstr=str[i].toLatin1(); 
//		if(hstr == ' ') 
//		{ 
//			i++; 
//			continue; 
//		} 
//		i++; 
//		if(i >= len) break; 
//		lstr = str[i].toLatin1(); 
//		hexdata = convertCharToHex(hstr); 
//		lowhexdata = convertCharToHex(lstr); 
//		if((hexdata == 16) || (lowhexdata == 16)) 
//			break; 
//		else hexdata = hexdata*16+lowhexdata; 
//		i++; 
//		byteData[hexdatalen] = (char)hexdata; 
//		hexdatalen++; 
//	} byteData.resize(hexdatalen); 
//}



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
	connect(ui.m_pBtWeb, SIGNAL(clicked()), this, SLOT(OnBtWeb()));
	connect(ui.m_pBtStartThread, SIGNAL(clicked()), this, SLOT(OnBtStartThreadClicked()));
	connect(ui.m_pBtStopThread, SIGNAL(clicked()), this, SLOT(OnBtStopThreadClicked()));
	connect(ui.m_pBtRapidJsonRead, SIGNAL(clicked()), this, SLOT(OnBtRapidJsonReadClicked()));
	connect(ui.m_pBtRapidJsonWrite, SIGNAL(clicked()), this, SLOT(OnBtRapidJsonWriteClicked()));
	connect(ui.m_pBtBoostServer, SIGNAL(clicked()), this, SLOT(OnBtBoostServerClicked()));
	connect(ui.m_pBtBoostClient, SIGNAL(clicked()), this, SLOT(OnBtBoostClientClicked()));
	connect(ui.m_pBtStopBoostCS, SIGNAL(clicked()), this, SLOT(OnBtBoostStopCSClicked()));
	connect(ui.m_pBtCharTest, SIGNAL(clicked()), this, SLOT(OnBtCharTestClicked()));
	connect(ui.m_pBtConIOCPServer, SIGNAL(clicked()), this, SLOT(OnBtConIOCPServerClicked()));
	connect(ui.m_pBtDisConIOCPServer, SIGNAL(clicked()), this, SLOT(OnBtDisConIOCPServerClicked()));
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
	unsigned char hex[8] = { 0x02, 0x01, 0x27, 0x77, 0x13, 0x01, 0x10, 0x01 };
	//目标是转化成1.01.03.19.01.16.01(头两个数据不转化）
	unsigned char hex2String[16] = { 0 };
	HexToAscii(hex, hex2String, 8);
	QString qsHex = QString((char*)hex2String);
	int nHead = qsHex.mid(4, 4).toInt(0, 16);//请注意16进制转10进制可以修改toInt()中的第二个参数base
	QString qsVer = QString::number(nHead / 10000) + "." + QString::number((nHead % 10000) / 100) + "." + QString::number(nHead % 100);
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

void UtilGui::OnBtWeb()
{
	WebDialog dlg;//其实是一个widget
	dlg.exec();
}

//
//MyClass定义
//
MyClass::MyClass()
{
	m_bClose = false;
	qDebug() << "Has inited!";
}

MyClass::~MyClass()
{
	qDebug() << "Ready to delete this!";
}

DWORD WINAPI ClientThread(LPVOID lpParam)
{
	MyClass* pObject = (MyClass*)lpParam;
	if(ENABLE_ZMQ)
	{
		printf("Use zmq");//包含zmq的头文件 

		void * pCtx = NULL;
		void * pSock = NULL;
		//使用tcp协议进行通信，需要连接的目标机器IP地址为192.168.1.2
		//通信使用的网络端口 为7766 
		const char * pAddr = "tcp://127.0.0.1:7766";

		//创建context 
		if ((pCtx = zmq_ctx_new()) == NULL)
		{
			return 0;
		}
		//创建socket 
		if ((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
		{
			zmq_ctx_destroy(pCtx);
			return 0;
		}
		int iSndTimeout = 5000;// millsecond
		//设置接收超时 
		if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
		{
			zmq_close(pSock);
			zmq_ctx_destroy(pCtx);
			return 0;
		}
		//连接目标IP192.168.1.2，端口7766 
		if (zmq_connect(pSock, pAddr) < 0)
		{
			zmq_close(pSock);
			zmq_ctx_destroy(pCtx);
			return 0;
		}
		//循环发送消息 
		while (1)
		{
			static int i = 0;
			char szMsg[1024] = { 0 };
			sprintf(szMsg, "hello world : %3d", i++);
			printf("Enter to send...\n");
			if (zmq_send(pSock, szMsg, sizeof(szMsg), 0) < 0)
			{
				fprintf(stderr, "send message faild\n");
				continue;
			}
			printf("send message : [%s] succeed\n", szMsg);
			//getchar();用于获取界面输入，输入enter发送一次消息
			Sleep(1000);
		}

		return 0;
	}
	else
	{
		while (pObject != nullptr && pObject->isClose() != true)
		{
			pObject->ProcClient();
			Sleep(1000);
		}
	}
	return true;
}

DWORD WINAPI ServerThread(LPVOID lpParam)
{
	MyClass* pObject = (MyClass*)lpParam;
	if(ENABLE_ZMQ)
	{
		printf("Use zmq");
	
		void * pCtx = NULL;
		void * pSock = NULL;
		const char * pAddr = "tcp://*:7766";

		//创建context，zmq的socket 需要在context上进行创建 
		if ((pCtx = zmq_ctx_new()) == NULL)
		{
			return 0;
		}
		//创建zmq socket ，socket目前有6中属性 ，这里使用dealer方式
		//具体使用方式请参考zmq官方文档（zmq手册） 
		if ((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
		{
			zmq_ctx_destroy(pCtx);
			return 0;
		}
		int iRcvTimeout = 5000;// millsecond
		//设置zmq的接收超时时间为5秒 
		if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
		{
			zmq_close(pSock);
			zmq_ctx_destroy(pCtx);
			return 0;
		}
		//绑定地址 tcp://*:7766 
		//也就是使用tcp协议进行通信，使用网络端口 7766
		if (zmq_bind(pSock, pAddr) < 0)
		{
			zmq_close(pSock);
			zmq_ctx_destroy(pCtx);
			return 0;
		}
		printf("bind at : %s\n", pAddr);
		while (1)
		{
			char szMsg[1024] = { 0 };
			printf("waitting...\n");
			errno = 0;
			//循环等待接收到来的消息，当超过5秒没有接到消息时，
			//zmq_recv函数返回错误信息 ，并使用zmq_strerror函数进行错误定位 
			if (zmq_recv(pSock, szMsg, sizeof(szMsg), 0) < 0)
			{
				printf("error = %s\n", zmq_strerror(errno));
				continue;
			}
			printf("received message : %s\n", szMsg);
		}

		return 0;
	}
	else
	{
		while (pObject != nullptr && pObject->isClose() != true)
		{
			pObject->ProcServer();
			Sleep(1000);
		}
	}
	return true;
}

void MyClass::ProcClient()
{
	printf("Client is running...\n");
}

void MyClass::ProcServer()
{
	printf("Server is running...\n");
}

void UtilGui::OnBtStartThreadClicked()
{
	m_pServer = new MyClass();
	hThreadServer = CreateThread(NULL, 0, ServerThread, m_pServer, 0, &dwServerTrdId);
	printf("Thread server start:%d!\n",dwServerTrdId);
	Sleep(2);

	m_pClient = new MyClass();
	hThreadClient = CreateThread(NULL, 0,ClientThread, m_pClient, 0, &dwClientTrdId);
	printf("Thread client start:%d!\n", dwClientTrdId);
}

void UtilGui::OnBtStopThreadClicked()
{
	printf("Thread end!");
	std::cout << "Thread end!" << std::endl;

	if(hThreadServer != nullptr)
	{
		m_pServer->Stop();
		CloseHandle(hThreadServer);
		hThreadServer = nullptr;
	}
	if (hThreadClient != nullptr)
	{
		m_pClient->Stop();
		CloseHandle(hThreadClient);
		hThreadClient = nullptr;
	}
}

void UtilGui::OnBtRapidJsonWriteClicked()
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType &allocator = doc.GetAllocator(); //获取分配器  
	//1.添加字符串对象  
	doc.AddMember("author", "tashaxing", allocator);
	//2.添加数组对象  
	Value array1(kArrayType);
	for (int i = 0; i<3; i++)
	{
		Value int_object(kObjectType);
		int_object.SetInt(i);
		array1.PushBack(int_object, allocator);
	}
	doc.AddMember("number", array1, allocator);
	//3.添加复合对象  
	Value object(kObjectType);
	object.AddMember("language1", "C++", allocator);
	object.AddMember("language2", "java", allocator);
	doc.AddMember("language", object, allocator);
	//4.添加对象数组和复合对象的组合  
	Value array2(kArrayType);
	Value object1(kObjectType);
	object1.AddMember("hobby", "drawing", allocator);
	array2.PushBack(object1, allocator);
	Value object2(kObjectType);
	object2.AddMember("height", 1.71, allocator);
	array2.PushBack(object2, allocator);
	doc.AddMember("information", array2, allocator);
	StringBuffer buffer;
	PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json  
	doc.Accept(pretty_writer);
	//打印到屏幕  
	cout << "the json output:" << endl;
	cout << buffer.GetString() << endl;
	//输出到文件  
	ofstream fout;
	fout.open("test.txt");    //可以使绝对和相对路径，用\\隔开目录，test, test.json, test.txt 都行，不局限于文件格式后缀，只要是文本文档  
	fout << buffer.GetString();
	fout.close();
}

void UtilGui::OnBtRapidJsonReadClicked()
{
	cout << "the json read:" << endl;
	ifstream fin;
	fin.open("test.txt");
	string str;
	string str_in = "";
	while (getline(fin, str))    //一行一行地读到字符串str_in中  
	{
		str_in = str_in + str + '\n';
	}
	//解析并打印出来  
	Document document;
	document.Parse<0>(str_in.c_str());

	Value &node1 = document["author"];
	cout << "author: " << node1.GetString() << endl;

	Value &node2 = document["number"];
	cout << "number: " << endl;
	if (node2.IsArray())
	{
		for (int i = 0; i<node2.Size(); i++)
			cout << '\t' << node2[i].GetInt() << endl;
	}

	Value &node3 = document["language"];
	cout << "language: " << endl;
	Value &tmp = node3["language1"];
	cout << '\t' << "language1: " << tmp.GetString() << endl;
	tmp = node3["language2"];
	cout << '\t' << "language2: " << tmp.GetString() << endl;

	Value &node4 = document["information"];
	cout << "information: " << endl;
	if (node4.IsArray())
	{
		int i = 0;
		Value &data = node4[i];   //注意，此处下表索引只能用变量，不能用常量，例如node[0]编译错误  
		cout << '\t' << "hobby: " << data["hobby"].GetString() << endl;
		i = 1;
		data = node4[i];
		cout << '\t' << "height: " << data["height"].GetDouble() << endl;
	}
}

void UtilGui::OnBtBoostServerClicked()
{
	//talk_to_client::ptr client = talk_to_client::new_();
	//acceptor.async_accept(client->sock(), boost::bind(handle_accept, client, _1));
	//service.run();
}

void UtilGui::OnBtBoostClientClicked()
{
	//ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);
	//char* names[] = { "John", "James", "Lucy", "Tracy", "Frank", "Abby", 0 };
	//for (char ** name = names; *name; ++name) {
	//	talk_to_svr::start(ep, *name);
	//	boost::this_thread::sleep(boost::posix_time::millisec(100));
	//}
	//
	//service.run();
}

void UtilGui::OnBtBoostStopCSClicked()
{

}

void UtilGui::OnBtCharTestClicked()
{
	int ft1 = 0x89abcdef;
	char buf[8] = { 0 };

	buf[0] = ((ft1 >> 24) & 0x3f) << 4;
	buf[1] = (ft1 >> 24);


	//将ft1的最高6位放到buf2中
	//ft1>>24 将最高位移到最低位，高六位继续>>2高2位补11变成e2,再&0x3f取低六位
	buf[2] = (ft1 >> 26) & 0x3f;

	buf[3] = ft1;//结果是ef

}

void UtilGui::OnBtConIOCPServerClicked()
{
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		return ;
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int len = sizeof(sin);

	const char * sendData = "来自客户端的数据包.\n";
	sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);

	char recvData[255];
	int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);
	if (ret > 0)
	{
		recvData[ret] = 0x00;
		printf(recvData);
	}

	closesocket(sclient);
	WSACleanup();
}

void UtilGui::OnBtDisConIOCPServerClicked()
{
}
