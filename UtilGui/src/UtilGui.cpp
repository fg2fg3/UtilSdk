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