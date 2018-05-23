#pragma once

#include <QThread>

class JoystickThread : public QThread
{
	Q_OBJECT
public:
	explicit JoystickThread(QObject *parent = Q_NULLPTR);
	/**
	* @brief run 启动监听线程
	*/
	void run();
	/**
	* @brief stop 停止监听线程
	*/
	void stop();

signals:
	/// 手柄 XY 轴的输出信号
	/// 需 enableSignal(true), enableXYSignal(true) 才有效
	void Joy_MoveForward();
	void Joy_MoveBackward();
	void Joy_MoveForwardStop();
	void Joy_MoveBackwardStop();
	void Joy_MoveLeft();
	void Joy_MoveRight();
	void Joy_MoveLeftStop();
	void Joy_MoveRightStop();

	/// 手柄 Z 轴的输出信号
	/// 需 enableSignal(true), enableZSignal(true) 才有效
	void Joy_MoveClockWise();
	void Joy_MoveCCW();
	void Joy_MoveClockWiseStop();
	void Joy_MoveCCWStop();

	/// 手柄按键的输出信号
	/// 需 enableSignal(true), enableButtionSignal(true) 才有效
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
	* @brief setXYThreshold 设置 XY 手柄的开启阈值。
	* 由于手柄使用时间长了会由于机械问题在原点停不住。所以需要有个开启阈值。
	* @param x  x 阈值
	* @param y  y 阈值
	*/
	void setXYThreshold(int x, int y);
	/**
	* @brief setZThreshold 设置 Z 手柄的开启阈值。
	* @param z  z 阈值
	*/
	void setZThreshold(int z);
	/**
	* @brief enableSignal 可以用这个函数关闭所有的信号
	* @param on
	*/
	void enableSignal(bool on) { m_signal = on; }
	/**
	* @brief enableXYSignal XY 手柄的使能控制，只有enableSignal(true)时才有效。
	* 相当于对手柄的信号有两级控制，第一级是全局使能，第二级是这里的使能。
	* @param on
	*/
	void enableXYSignal(bool on) { m_xy_signal = on; }
	void enableZSignal(bool on) { m_z_signal = on; }
	void enableButtionSignal(bool on){ m_button_signal = on; }

	/**
	* @brief setMonitorInterval 设置内部轮询的时间间隔
	* @param interval 单位 ms，范围 20 - 10000。
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