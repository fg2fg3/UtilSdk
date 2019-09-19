#include "OpencvDemoDialog.h"
#include <QFileDialog>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QTextCodec>
using namespace std;
using namespace cv;

OpencvDemoDialog::OpencvDemoDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_pBtPic1, SIGNAL(clicked()), this, SLOT(OnBtPic1Clicked()));
	connect(ui.m_pBtPic2, SIGNAL(clicked()), this, SLOT(OnBtPic2Clicked()));
	connect(ui.m_pBtMergePic, SIGNAL(clicked()), this, SLOT(OnBtMergePic()));
	connect(ui.m_pBtSaveBin, SIGNAL(clicked()), this, SLOT(OnBtSaveBin()));

	//OnBtPic1Clicked();
	//OnBtPic2Clicked();
}

OpencvDemoDialog::~OpencvDemoDialog()
{
}

void OpencvDemoDialog::OnBtPic1Clicked()
{
//	QString path = QFileDialog::getOpenFileName(this, "打开图片", "D:/", "*.*");
	QString path = qApp->applicationDirPath() + "/pic/bmw71.jpg";
	ui.m_pLbPic1Path->setText(path);

	m_mat1 = cv::imread(path.toLatin1().data());

	cv::cvtColor(m_mat1, m_mat1, CV_BGR2RGB);
	QImage img = QImage((const unsigned char*)(m_mat1.data), m_mat1.cols, m_mat1.rows, QImage::Format_RGB888);
	QPixmap mp = mp.fromImage(img);
	ui.m_pLbPic1->setPixmap(mp);
}

void OpencvDemoDialog::OnBtPic2Clicked()
{
	QString path = qApp->applicationDirPath() + "/pic/huidu.jpg";//为何显示灰度的歪斜图
	ui.m_pLbPic1Path->setText(path);

	m_mat2 = cv::imread(path.toLatin1().data());

	//cv::cvtColor(m_mat1, m_mat1, CV_BGR2RGB);
	QImage img = QImage((const unsigned char*)(m_mat2.data), m_mat2.cols, m_mat2.rows, QImage::Format_RGB888);
	QPixmap mp = mp.fromImage(img);
	ui.m_pLbPic2->setPixmap(mp);

	//用graphicsView显示，图片会带缩放条显示，效果更好
	//ui->graphicsView->resize(img.width(), img.height());
	//QGraphicsScene *scene = new QGraphicsScene;
	////scene->setSceneRect(0,0,img.width(),img.height());  
	//scene->addPixmap(QPixmap::fromImage(img));
	//ui->graphicsView->setScene(scene);
	//ui->graphicsView->adjustSize();
	//ui->label->hide();
	//ui->graphicsView->show();
}

void OpencvDemoDialog::OnBtMergePic()
{
	cv::Mat ROI = m_mat1(cv::Rect(300, 300, m_mat2.cols, m_mat2.rows));

	QString path = qApp->applicationDirPath() + "/pic/huidu.jpg";
	cv::Mat mask = cv::imread(path.toLatin1().data(), 0);

	m_mat2.copyTo(ROI, mask);//roi区域和mask掩膜
	QImage img = QImage((const unsigned char*)(m_mat1.data), m_mat1.cols, m_mat1.rows, QImage::Format_RGB888);
	QPixmap mp = mp.fromImage(img);
	ui.m_pLbPicMerge->setPixmap(mp);
}

void OpencvDemoDialog::OnBtSaveBin()
{
	//save the image data to bin,BGR format
	QStringList paths = QFileDialog::getOpenFileNames(this, tr("selc"), qApp->applicationDirPath(), "*.*");
	QTextCodec *code = QTextCodec::codecForName("gb2312");

	for (int i = 0; i < paths.length(); i++)
	{
		std::string name = code->fromUnicode(paths.at(i)).data();
		std::string dstName = name;
		dstName = dstName.replace(dstName.end() - 3, dstName.end(), "bgra");
		FILE *fpw = fopen(dstName.c_str(), "wb");
		if (fpw == NULL)
		{
			cout << "Open error!" << endl;
			fclose(fpw);
			return;
		}

		Mat image = imread(name);
		int nCh = image.channels();
		if (!image.data || image.channels() != 3)
		{
			cout << "Image read failed or image channels isn't equal to 3."
				<< endl;
			return;
		}

		// write image to binary format file
		int labelw = 1;
		int rows = image.rows;
		int cols = image.cols;

		//fwrite(&labelw, sizeof(char), 1, fpw);
		char alpha = 0xFF;
		char* dp = (char*)image.data;
		for (int i = 0; i<rows*cols; i++)
		{
			//opencv按照BGRA读取
			fwrite(&dp[i * 3], sizeof(char), 1, fpw);
			fwrite(&dp[i * 3 + 1], sizeof(char), 1, fpw);
			fwrite(&dp[i * 3 + 2], sizeof(char), 1, fpw);
			fwrite(&alpha, sizeof(char), 1, fpw);
			//printf("%d,%d,%d", dp[i * 3], dp[i * 3 + 1], dp[i * 3 +2]);
		}
		fclose(fpw);
	}

}