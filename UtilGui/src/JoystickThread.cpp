#include "JoystickThread.h"

#include <Windows.h>
#include <QDebug>
#include "joystickapi.h"
#include "Mmsystem.h"

#define BASE_POS 32767
#define MIN_X_POS 0
#define MAX_X_POS 65535
#define MIN_Y_POS 0
#define MAX_Y_POS 65535
#define BASE_ANGLE 45 //X=Y 45度角


JoystickThread::JoystickThread(QObject *parent)
	:QThread(parent),
	m_valid(false),
	m_run(true),
	m_xThreshold(5000),
	m_yThreshold(5000),
	m_zThreshold(5000),
	old_xPos(0),
	old_yPos(0),
	old_zPos(0),
	m_signal(false),
	m_xy_signal(false),
	m_z_signal(false),
	m_button_signal(false),
	m_monitor_interval(50)
{
	JOYINFO joyinfo;
	if (joyGetNumDevs() > 0 && joyGetPos(JOYSTICKID1, &joyinfo) != JOYERR_UNPLUGGED)
	{
		m_valid = true;
		qDebug() << "m_valid = true";
	}

	for (int i = 0; i < 8; i++)
	{
		m_button[i] = 0;
	}
}

void JoystickThread::stop()
{
	m_run = 0;
	wait();
}

void JoystickThread::setXYThreshold(int x, int y)
{
	m_xThreshold = abs(x);
	m_yThreshold = abs(y);
}

void JoystickThread::setZThreshold(int z)
{
	m_zThreshold = abs(z);
}

void JoystickThread::Capture()
{
	m_run = true;
	JOYINFO joyinfo;
	if (joyGetNumDevs() > 0 && joyGetPos(JOYSTICKID1, &joyinfo) != JOYERR_UNPLUGGED)
	{
		m_valid = true;
		qDebug() << "m_valid = true";
	}

	for (int i = 0; i < 8; i++)
	{
		m_button[i] = 0;
	}
}



void JoystickThread::run()
{
	JOYINFOEX joyinfoex;
	joyinfoex.dwSize = sizeof(JOYINFOEX);
	joyinfoex.dwFlags = JOY_RETURNALL;
	while (m_valid && m_run)
	{
		int ret = joyGetPosEx(JOYSTICKID1, &joyinfoex);
		if (ret == JOYERR_NOERROR)
		{
			qDebug()<<joyinfoex.dwXpos<<","<<joyinfoex.dwYpos<<","<<joyinfoex.dwZpos<<",button:"<<joyinfoex.dwButtons<<",current"<<joyinfoex.dwButtonNumber;

			SendSerialCmd(joyinfoex.dwXpos, joyinfoex.dwYpos, joyinfoex.dwButtons);
		}
		else
		{
			qDebug() << "Error is " << ret;

		}

		msleep(1000);//2s更新一次
	}
}
void JoystickThread::SendSerialCmd(DWORD dwXpos, DWORD dwYpos, DWORD dwButtons)
{
	short int nAngle = 0;
	if ((dwXpos == BASE_POS && dwYpos == BASE_POS && dwButtons == 4) || (dwXpos == BASE_POS && dwYpos == MAX_Y_POS))
	{
		//发送尾视图
		qDebug() << " tail view" << nAngle;
	}

	else if ((dwXpos == BASE_POS && dwYpos == BASE_POS && dwButtons == 2) || (dwXpos == MAX_X_POS && dwYpos == BASE_POS))
	{
		//发送右视图
		qDebug() << " right view" << nAngle;
	}

	else if ((dwXpos == BASE_POS && dwYpos == BASE_POS && dwButtons == 1) || (dwXpos == BASE_POS && dwYpos == 0))
	{
		//发送前视图
		qDebug() << " head view" << nAngle;
	}

	else if ((dwXpos == BASE_POS && dwYpos == BASE_POS && dwButtons == 8) || (dwXpos == 0 && dwYpos == BASE_POS))
	{
		//发送左视图
		qDebug() << " left view" << nAngle;
	}

	else if (dwXpos == BASE_POS && dwYpos == BASE_POS && dwButtons == 32)
	{
		//发送顶视图
		qDebug() << " top view" << nAngle;
	}

	else if (dwXpos == BASE_POS && dwYpos == BASE_POS && dwButtons == 0)
	{
		//发送顶视图
		qDebug() << " No operaion" << nAngle;
	}

	//右上象限
	else if ((BASE_POS < dwXpos) && (dwXpos <= MAX_X_POS) && (dwYpos < BASE_POS))
	{
		nAngle = (long)(BASE_POS - dwYpos) * 45 / (dwXpos - BASE_POS);
		qDebug() << " Top right:nAngle" << nAngle;
	}

	//左上象限
	else if ((dwXpos < BASE_POS) && (dwYpos < BASE_POS))
	{
		nAngle = (long)(BASE_POS - dwYpos) * 45 / ( BASE_POS - dwXpos);
		nAngle += 90;
		qDebug() << "Top left:nAngle" << nAngle;
	}

	else if ((dwXpos < BASE_POS) && (BASE_POS < dwYpos ) && (dwYpos <= MAX_Y_POS))
	{
		nAngle = (long)(dwYpos - BASE_POS ) * 45 / (BASE_POS - dwXpos);
		nAngle += 180;
		qDebug() << "bottom left:nAngle" << nAngle;
	}

	else if ((BASE_POS < dwXpos ) && ( dwXpos < MAX_X_POS ) &&(BASE_POS < dwYpos) && (dwYpos <= MAX_Y_POS))
	{
		nAngle = (long)(dwXpos - BASE_POS) * 45 / ( dwYpos - BASE_POS);
		nAngle += 270;
		qDebug() << "bottom right:nAngle" << nAngle;
	}
	else
	{
		qDebug() << "Unknow section ";
	}

}

void JoystickThread::setMonitorInterval(int interval)
{
	m_monitor_interval = qBound(20, interval, 10000);
}

int JoystickThread::Axis_stateMachine(int pos, int threshold, int &old_pos)
{
	pos = pos - 32767;
	if (abs(pos) <= threshold)
	{
		pos = 0;
	}
	else if (pos > threshold)
	{
		pos = 1;
	}
	else
	{
		pos = -1;
	}
	if (pos == old_pos) return 0;
	int ret;
	switch (pos)
	{
	case -1:
		ret = -1;
		break;
	case 0:
		if (old_pos == -1)
		{
			ret = -2;
		}
		else
		{
			ret = 2;
		}
		break;
	case 1:
		ret = 1;
		break;
	}
	//qDebug() << "o = " << old_pos << ", " << pos << ", ret =" << ret;
	old_pos = pos;
	return ret;
}

void JoystickThread::AxisX_StateMachine(int xPos)
{
	int ret = Axis_stateMachine(xPos, m_xThreshold, old_xPos);
	if (!m_signal || !m_xy_signal) return;
	switch (ret)
	{
	case -1:
		emit Joy_MoveLeft();
		break;
	case -2:
		emit Joy_MoveLeftStop();
		break;
	case 2:
		emit Joy_MoveRightStop();
		break;
	case 1:
		emit Joy_MoveRight();
		break;
	default:
		break;
	}
}

void JoystickThread::AxisY_StateMachine(int yPos)
{
	int ret = Axis_stateMachine(yPos, m_yThreshold, old_yPos);
	if (!m_signal || !m_xy_signal) return;
	switch (ret)
	{
	case -1:
		emit Joy_MoveForward();
		break;
	case -2:
		emit Joy_MoveForwardStop();
		break;
	case 2:
		emit Joy_MoveBackwardStop();
		break;
	case 1:
		emit Joy_MoveBackward();
		break;
	default:
		break;
	}
}

void JoystickThread::AxisZ_StateMachine(int zPos)
{
	int ret = Axis_stateMachine(zPos, m_zThreshold, old_zPos);
	if (ret == 0) return;
	//qDebug() << zPos - 32767 << ", " << ret;
	if (!m_signal || !m_z_signal) return;
	switch (ret)
	{
	case -1:
		emit Joy_MoveCCW();
		break;
	case -2:
		emit Joy_MoveCCWStop();
		break;
	case 2:
		emit Joy_MoveClockWiseStop();
		break;
	case 1:
		emit Joy_MoveClockWise();
		break;
	default:
		break;
	}
}

void JoystickThread::Button_StateMachine(int button)
{
	const int mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	for (int i = 0; i < 8; i++)
	{
		int n = button & mask[i];
		if (n ^ m_button[i]) // 如果当前 button 与以前的 button 不同
		{
			m_button[i] = n;
			if (!m_signal || !m_button_signal) continue;
			if (n)
			{
				qDebug() << "Joy_Button" << i + 1 << "Pressed()";
				switch (i + 1)
				{
				case 1:
					emit Joy_Button1Pressed();
					break;
				case 2:
					emit Joy_Button2Pressed();
					break;
				case 3:
					emit Joy_Button3Pressed();
					break;
				case 4:
					emit Joy_Button4Pressed();
					break;
				case 5:
					emit Joy_Button5Pressed();
					break;
				case 6:
					emit Joy_Button6Pressed();
					break;
				case 7:
					emit Joy_Button7Pressed();
					break;
				case 8:
					emit Joy_Button8Pressed();
					break;
				default:
					break;
				}
			}
			else
			{
				qDebug() << "Joy_Button" << i + 1 << "Released()";
				switch (i + 1)
				{
				case 1:
					emit Joy_Button1Released();
					break;
				case 2:
					emit Joy_Button2Released();
					break;
				case 3:
					emit Joy_Button3Released();
					break;
				case 4:
					emit Joy_Button4Released();
					break;
				case 5:
					emit Joy_Button5Released();
					break;
				case 6:
					emit Joy_Button6Released();
					break;
				case 7:
					emit Joy_Button7Released();
					break;
				case 8:
					emit Joy_Button8Released();
					break;
				default:
					break;
				}
			}
		}
	}
}

