#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UtilGui.h"

class UtilGui : public QMainWindow
{
	Q_OBJECT

public:
	UtilGui(QWidget *parent = Q_NULLPTR);

private:
	Ui::UtilGuiClass ui;

	void PrepareSlot();
	void PrepareStyle();
	void SetupUI();
	void InitVar();

private slots:
	void OnBtChineseSupportClicked();
	void OnBtCompareClicked();
	void OnBtJoyStickClicked();
};