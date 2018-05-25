#include "UtilGui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>

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
}

void UtilGui::OnBtChineseSupportClicked()
{
	QString qslPath = QFileDialog::getOpenFileName(this, "D:/", "*.*");

	ui.m_pLbPath->setText(qslPath);

	QTextCodec *code = QTextCodec::codecForName("GB2312");//�������·������  
	std::string name = code->fromUnicode(qslPath).data();

	FILE* fp = fopen(name.c_str(), "r");
	if (fp == nullptr)
	{
		QMessageBox::warning(this, "����", qslPath);
	}
	fclose(fp);
}

void UtilGui::OnBtCompareClicked()
{
	//�ַ��Ƚ�
	char a[] = "abc";
	char b[] = "bbc";
	if (a[1] == b[1])//�ַ��Ƚ�
	{
		qDebug() << "Same";
	}
	else
	{
		qDebug() << "not same";
	}

	//����ıȽϷ�ʽ
	char c[] = { 0x00, 0x01, 0x03, 0x04 };
	char d[] = { 0x00, 0x01, 0x03, 0x05 };
	int t1 = 0, t2 = 0;
	memcpy((char*)&t1, c, 4);//4���Ի�Ϊ3�����ⳤ�ȵ��ǲ����Գ���t1�ĳ���
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
	QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ر���!"));
}