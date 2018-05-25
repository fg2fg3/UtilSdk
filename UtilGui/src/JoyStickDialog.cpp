#include "JoyStickDialog.h"

JoyStickDialog::JoyStickDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pTrdJoy = new JoystickThread;
}

JoyStickDialog::~JoyStickDialog()
{
}
