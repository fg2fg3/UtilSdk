#pragma once

#include <QThread>

class JoystickThread : public QThread
{
	Q_OBJECT
public:
	explicit JoystickThread(QObject *parent = Q_NULLPTR);
	/**
	* @brief run ���������߳�
	*/
	void run();
	/**
	* @brief stop ֹͣ�����߳�
	*/
	void stop();

signals:
	/// �ֱ� XY �������ź�
	/// �� enableSignal(true), enableXYSignal(true) ����Ч
	void Joy_MoveForward();
	void Joy_MoveBackward();
	void Joy_MoveForwardStop();
	void Joy_MoveBackwardStop();
	void Joy_MoveLeft();
	void Joy_MoveRight();
	void Joy_MoveLeftStop();
	void Joy_MoveRightStop();

	/// �ֱ� Z �������ź�
	/// �� enableSignal(true), enableZSignal(true) ����Ч
	void Joy_MoveClockWise();
	void Joy_MoveCCW();
	void Joy_MoveClockWiseStop();
	void Joy_MoveCCWStop();

	/// �ֱ�����������ź�
	/// �� enableSignal(true), enableButtionSignal(true) ����Ч
	void Joy_Button1Pressed();
	void Joy_Button2Pressed();
	void Joy_Button3Pressed();
	void Joy_Button4Pressed();
	void Joy_Button5Pressed();
	void Joy_Button6Pressed();
	void Joy_Button7Pressed();
	void Joy_Button8Pressed();
	void Joy_Button1Released();
	void Joy_Button2Released();
	void Joy_Button3Released();
	void Joy_Button4Released();
	void Joy_Button5Released();
	void Joy_Button6Released();
	void Joy_Button7Released();
	void Joy_Button8Released();
	public slots:
	/**
	* @brief setXYThreshold ���� XY �ֱ��Ŀ�����ֵ��
	* �����ֱ�ʹ��ʱ�䳤�˻����ڻ�е������ԭ��ͣ��ס��������Ҫ�и�������ֵ��
	* @param x  x ��ֵ
	* @param y  y ��ֵ
	*/
	void setXYThreshold(int x, int y);
	/**
	* @brief setZThreshold ���� Z �ֱ��Ŀ�����ֵ��
	* @param z  z ��ֵ
	*/
	void setZThreshold(int z);
	/**
	* @brief enableSignal ��������������ر����е��ź�
	* @param on
	*/
	void enableSignal(bool on) { m_signal = on; }
	/**
	* @brief enableXYSignal XY �ֱ���ʹ�ܿ��ƣ�ֻ��enableSignal(true)ʱ����Ч��
	* �൱�ڶ��ֱ����ź����������ƣ���һ����ȫ��ʹ�ܣ��ڶ����������ʹ�ܡ�
	* @param on
	*/
	void enableXYSignal(bool on) { m_xy_signal = on; }
	void enableZSignal(bool on) { m_z_signal = on; }
	void enableButtionSignal(bool on){ m_button_signal = on; }

	/**
	* @brief setMonitorInterval �����ڲ���ѯ��ʱ����
	* @param interval ��λ ms����Χ 20 - 10000��
	*/
	void setMonitorInterval(int interval);
private:
	int Axis_stateMachine(int pos, int threshold, int &old_pos);
	void AxisX_StateMachine(int xPos);
	void AxisY_StateMachine(int yPos);
	void AxisZ_StateMachine(int zPos);
	void Button_StateMachine(int button);

	int m_xThreshold;
	int m_yThreshold;
	int m_zThreshold;

	int old_xPos;
	int old_yPos;
	int old_zPos;
	int m_button[8];

	bool m_run;
	bool m_valid;

	bool m_signal;
	bool m_xy_signal;
	bool m_z_signal;
	bool m_button_signal;

	int m_monitor_interval;
};