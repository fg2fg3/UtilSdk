#pragma once

#include <QDialog>
#include "ui_OpencvDemoDialog.h"
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  


class OpencvDemoDialog : public QDialog
{
	Q_OBJECT

public:
	OpencvDemoDialog(QWidget *parent = Q_NULLPTR);
	~OpencvDemoDialog();

private:
	Ui::OpencvDemoDialog ui;
	cv::Mat		m_mat1;
	cv::Mat		m_mat2;
	cv::Mat		m_matMerge;

private slots:
	void OnBtPic1Clicked();
	void OnBtPic2Clicked();
	void OnBtMergePic();
	void OnBtSaveBin();
};
