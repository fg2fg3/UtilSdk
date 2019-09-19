#pragma once

#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

#include "TcpSrvException.h"

#include "BaseDefine.h"
#include "tcpreceivecontext.h"
#include "TcpSendContext.h"
#include "AcceptContext.h"


#include <map>
using namespace std;

const int ACCEPT_EVENT_CNT = 2;

class CTcpServer
{
public:
	CTcpServer(void);
	~CTcpServer(void);
public:
	int InitServer(char* ipAddress,unsigned short port) throw(CSrvException);//��ʼ��������
	int StartServer(void) throw(CSrvException);//����������
	int StopServer(void) throw(CSrvException);//ֹͣ������
	int PauseServer(void);
protected:
	int SendFile(SOCKET sock,char* fileName);//ͨ���˺�����Զ�˷����ļ�
	int SendData(SOCKET sock,char* pVoid,long dataSize);//ͨ���˺���������ͨ����
	virtual void SaveReceivedData(SOCKET sock,char* pVoid,long dataLen){;}//��CTcpServer�̳е��඼��Ҫʵ�ִ˺���
private:
	SOCKET m_hListenSocket;//�����׽��־��
	SA m_struServerAdd; //��������ַ
	HANDLE m_hCompletionPort;
	HANDLE m_hListenThread;
	HANDLE m_hWorkerThread[MAX_PROCESSOR_COUNTER];
	HANDLE m_hPostAcceptEvent[ACCEPT_EVENT_CNT];	
	CRITICAL_SECTION m_struCriSec;
private:
	LPFN_ACCEPTEX m_pfAcceptEx;				//AcceptEx������ַ
	LPFN_GETACCEPTEXSOCKADDRS m_pfGetAddrs;	//GetAcceptExSockaddrs�����ĵ�ַ
private:
	int m_iMaxPostAcceptNumbs;
	int m_iWorkerThreadNumbers;
	bool m_bServerRunning;
	unsigned long m_iTimerID;
private:
	static UINT WINAPI ListenThread(LPVOID lpParam);//����client connet�¼�
	static UINT WINAPI WorkThread(LPVOID lpParma);//������work��
	static void PASCAL TimerProc(UINT wTimerID,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2);
private:
	int PushClientSocket(SOCKET clientSocket);//�������ӵ�socket�������������й���
	int CloseClientSocket(SOCKET clientSocket);//�ر��쳣����
	bool IsValidSocket(SOCKET socket);//�жϴ����socket�Ƿ����ĺϷ���connect
	map<SOCKET,long> m_mapAcceptSockQueue;
	SOCKET m_struTestSockt;
private:	
	void ConnectTimeOutCheck();
	int PostAcceptOperation(int postNumbs);
	int CteateThread();
	int ReleaseResource(void);
	int SetHeartBeatCheck(SOCKET clientSock);
	void ShowNewConnectInf(LPWSAOVERLAPPED pOverlapped);
private:
	  int IssueReceiveOperation(SOCKET socket);
	  int IssueAcceptOperation();
	  int IssueSendOperation(SOCKET cliSock,char* pData,unsigned long dwTransferBytes);

	  int CompleteReceive(LPWSAOVERLAPPED pOverlapped,unsigned long dwTransferBytes);
	  int CompleteAccept(LPWSAOVERLAPPED pOverlapped,unsigned long dwTransferBytes);
	  int CompleteSend(LPWSAOVERLAPPED pOverlapped,unsigned long dwTransferBytes);

private: 
	void ErrorReport(unsigned long errorCode,char* description);
	void DebugPrintf(char* szFormat,...);
};
#endif