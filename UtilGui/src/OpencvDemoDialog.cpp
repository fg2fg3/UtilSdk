#include "OpencvDemoDialog.h"
#include <QFileDialog>
#include <QApplication>

OpencvDemoDialog::OpencvDemoDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_pBtPic1, SIGNAL(clicked()), this, SLOT(OnBtPic1Clicked()));
	connect(ui.m_pBtPic2, SIGNAL(clicked()), this, SLOT(OnBtPic2Clicked()));
	connect(ui.m_pBtMergePic, SIGNAL(clicked()), this, SLOT(OnBtMergePic()));

	OnBtPic1Clicked();
	OnBtPic2Clicked();
}

OpencvDemoDialog::~OpencvDemoDialog()
{
}

void OpencvDemoDialog::OnBtPic1Clicked()
{
//	QString path = QFileDialog::getOpenFileName(this, "��ͼƬ", "D:/", "*.*");
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
	QString path = qApp->applicationDirPath() + "/pic/benci.jpg";//Ϊ����ʾ�Ҷȵ���бͼ
	ui.m_pLbPic1Path->setText(path);

	m_mat2 = cv::imread(path.toLatin1().data());

	//cv::cvtColor(m_mat1, m_mat1, CV_BGR2RGB);
	QImage img = QImage((const unsigned char*)(m_mat2.data), m_mat2.cols, m_mat2.rows, QImage::Format_RGB888);
	QPixmap mp = mp.fromImage(img);
	ui.m_pLbPic2->setPixmap(mp);

	//��graphicsView��ʾ��ͼƬ�����������ʾ��Ч������
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
	cv::Mat ROI = m_mat2(cv::Rect(0, 0, 100, 100));
	m_mat2.copyTo(ROI, m_mat1);
	//������m_matMTI.copyTo(ROI),MTI�ĺڱ���Ҳ�ử��m_matSAR����.  
	QImage img = QImage((const unsigned char*)(m_mat1.data), m_mat1.cols, m_mat1.rows, QImage::Format_RGB888);
	QPixmap mp = mp.fromImage(img);
	ui.m_pLbPicMerge->setPixmap(mp);
}