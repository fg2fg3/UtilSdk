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
	//�Զ�д��ʽ�򿪴���  
	if (m_serial.open(QIODevice::ReadWrite))
	{
		//���ò�����  
		m_serial.setBaudRate(115200);
		//��������λ  
		m_serial.setDataBits(QSerialPort::Data8);
		//����У��λ  
		m_serial.setParity(QSerialPort::NoParity);
		//����������  
		m_serial.setFlowControl(QSerialPort::NoFlowControl);
		//����ֹͣλ  
		m_serial.setStopBits(QSerialPort::OneStop);
		ui.m_pLbStatu->setText(QString::fromLocal8Bit("���ڴ򿪳ɹ���"));
	}
	else
	{
		ui.m_pLbStatu->setText(QString::fromLocal8Bit("���ڴ�ʧ�ܣ�"));
	}
}

void JoyStickDialog::OnBtCloseComClicked()
{
	m_serial.close();
	ui.m_pLbStatu->setText(QString::fromLocal8Bit("�����Ѿ��رգ�"));
}