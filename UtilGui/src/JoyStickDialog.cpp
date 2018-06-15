#include "JoyStickDialog.h"

JoyStickDialog::JoyStickDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_pBtCapture, SIGNAL(clicked()), this, SLOT(OnBtCaptureClicked()));
	connect(ui.m_pBtOpenCom, SIGNAL(clicked()), this, SLOT(OnBtOpenComClicked()));
	connect(ui.m_pBtCloseCom, SIGNAL(clicked()), this, SLOT(OnBtCloseComClicked()));

}

JoyStickDialog::~JoyStickDialog()
{
}

void JoyStickDialog::OnBtCaptureClicked()
{
	m_pTrdJoy = new JoystickThread;
	m_pTrdJoy->SetCom(&m_serial);
	m_pTrdJoy->start();
}

void JoyStickDialog::OnBtOpenComClicked()
{

	m_serial.setPortName("COM4");
	//以读写方式打开串口  
	if (m_serial.open(QIODevice::ReadWrite))
	{
		//设置波特率  
		m_serial.setBaudRate(115200);
		//设置数据位  
		m_serial.setDataBits(QSerialPort::Data8);
		//设置校验位  
		m_serial.setParity(QSerialPort::NoParity);
		//设置流控制  
		m_serial.setFlowControl(QSerialPort::NoFlowControl);
		//设置停止位  
		m_serial.setStopBits(QSerialPort::OneStop);
		ui.m_pLbStatu->setText(QString::fromLocal8Bit("串口打开成功！"));
	}
	else
	{
		ui.m_pLbStatu->setText(QString::fromLocal8Bit("串口打开失败！"));
	}
}

void JoyStickDialog::OnBtCloseComClicked()
{
	m_serial.close();
	ui.m_pLbStatu->setText(QString::fromLocal8Bit("串口已经关闭！"));
}