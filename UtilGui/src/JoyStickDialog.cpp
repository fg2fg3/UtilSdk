#include "JoyStickDialog.h"

JoyStickDialog::JoyStickDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);



	connect(ui.m_pBtCapture, SIGNAL(clicked()), this, SLOT(OnBtCaptureClicked()));
	m_pTrdJoy = new JoystickThread;
	m_pTrdJoy->start();
}

JoyStickDialog::~JoyStickDialog()
{
}

void JoyStickDialog::OnBtCaptureClicked()
{
	m_pTrdJoy->stop();
	m_pTrdJoy->Capture();
	m_pTrdJoy->start();
}