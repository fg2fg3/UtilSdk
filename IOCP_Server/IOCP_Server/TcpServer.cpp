#include "StdAfx.h"
#include ".\tcpserver.h"

#include <stdio.h>
#include <process.h>

#pragma comment(lib,"Winmm.lib") //timeSetEvent()

#include <time.h>

CTcpServer::CTcpServer(void)
{
	m_hListenSocket = NULL;
	ZeroMemory(&m_struServerAdd,sizeof(m_struServerAdd)); //��������ַ
	m_hCompletionPort = NULL;
	m_hListenThread = NULL;

	for(int i=0;i<MAX_PROCESSOR_COUNTER;i++)
		m_hWorkerThread[i] = NULL;

	m_iMaxPostAcceptNumbs = 64;//һ�����Ͷ��64��accept
	m_hPostAcceptEvent[0] = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hPostAcceptEvent[1] = ::CreateSemaphore(NULL,0,m_iMaxPostAcceptNumbs,NULL);

	InitializeCriticalSection(&m_struCriSec);
	
	m_iWorkerThreadNumbers = 2;//����߳�������CPU������2��
	m_bServerRunning = false;

	m_pfAcceptEx = NULL;				//AcceptEx������ַ
	m_pfGetAddrs = NULL;	//GetAcceptExSockaddrs�����ĵ�ַ

	m_mapAcceptSockQueue.clear();

	//��ʼ��winsocket2��
	WSADATA wsData;
	int errorCode = WSAStartup(MAKEWORD(2, 2), &wsData);//��ʼ��ws2_32.lib��
}

CTcpServer::~CTcpServer(void)
{
	m_hListenSocket = NULL;
	ZeroMemory(&m_struServerAdd,sizeof(m_struServerAdd)); //��������ַ
	m_hCompletionPort = NULL;
	m_hListenThread = NULL;

	for(int i=0;i<MAX_PROCESSOR_COUNTER;i++)
		m_hWorkerThread[i] = NULL;

	for(int i=0;i<ACCEPT_EVENT_CNT;i++)
	    m_hPostAcceptEvent[i] = NULL;

	m_iWorkerThreadNumbers = 2;//����߳�������CPU������2��
	m_bServerRunning = false;

    m_pfAcceptEx = NULL;				//AcceptEx������ַ
	m_pfGetAddrs = NULL;	//GetAcceptExSockaddrs�����ĵ�ַ

	DeleteCriticalSection(&m_struCriSec);

	WSACleanup();
}
int CTcpServer::InitServer(char* ipAddress,unsigned short port)
{
	try
	{
		int errorCode = 1;
		if(!ipAddress)
		{
			throw CSrvException("Invalid Ip address.",-1,(long)(__LINE__));
		}
		//�����׽���
		m_hListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if(m_hListenSocket == INVALID_SOCKET)
		{
			throw CSrvException("Invalid socket handle.",-1,(long)(__LINE__));
		}
		//��accetpex����Ϊ�첽������ģʽ
		ULONG ul = 1;
		errorCode = ioctlsocket(m_hListenSocket, FIONBIO, &ul);
		if(SOCKET_ERROR == errorCode)
		{
			throw CSrvException("Set listen socket to FIONBIO mode error.",-1,(long)(__LINE__));
		}

		//����Ϊsocket����,��ֹ������������˿��ܹ������ٴ�ʹ�û������Ľ���ʹ��
		int nOpt = 1;
		errorCode = setsockopt(m_hListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nOpt, sizeof(nOpt));
		if(SOCKET_ERROR == errorCode)
		{
			throw CSrvException("Set listen socket to SO_REUSEADDR mode error.",-1,(long)(__LINE__));
		}
        
		//�ر�ϵͳ�Ľ����뷢�ͻ�����
		int nBufferSize = 0;
		setsockopt(m_hListenSocket,SOL_SOCKET,SO_SNDBUF,(char*)&nBufferSize,sizeof(int));
		setsockopt(m_hListenSocket,SOL_SOCKET,SO_RCVBUF,(char*)&nBufferSize,sizeof(int)); 

		unsigned long dwBytes = 0;
		GUID guidAcceptEx = WSAID_ACCEPTEX;
		if (NULL == m_pfAcceptEx)
		{
			errorCode = WSAIoctl(m_hListenSocket,SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx,sizeof(guidAcceptEx)
				, &m_pfAcceptEx, sizeof(m_pfAcceptEx), &dwBytes, NULL, NULL);
		}
		if (NULL == m_pfAcceptEx || SOCKET_ERROR == errorCode)
		{
			throw CSrvException("Invalid fuction pointer.",-1,(long)(__LINE__));
		}

		//����GetAcceptExSockaddrs����
		GUID guidGetAddr = WSAID_GETACCEPTEXSOCKADDRS;
		if (NULL == m_pfGetAddrs)
		{
			errorCode = WSAIoctl(m_hListenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidGetAddr, sizeof(guidGetAddr)
				, &m_pfGetAddrs, sizeof(m_pfGetAddrs), &dwBytes, NULL, NULL);
		}
		if (NULL == m_pfGetAddrs || SOCKET_ERROR == errorCode)
		{
			throw CSrvException("Invalid fuction pointer.",-1,(long)(__LINE__));
		}

		//����������ַ��Ϣ
		m_struServerAdd.sin_family = AF_INET;
		m_struServerAdd.sin_addr.s_addr = inet_addr(ipAddress);
		m_struServerAdd.sin_port = htons(port);

		//������ɶ˿�
		m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
		if(m_hCompletionPort == NULL)
		{
			throw CSrvException("Invalid completion port handle.",-1,(long)(__LINE__));
		}
		//��׽��ֺͷ�������ַ
		errorCode = bind(m_hListenSocket,(struct sockaddr*)&m_struServerAdd,sizeof(m_struServerAdd));
		if(errorCode == SOCKET_ERROR)
		{
			throw CSrvException("Error socket bind operation.",WSAGetLastError(),(long)(__LINE__));
		}

		//�������̺߳͹����߳�
		if(!this->CteateThread())
		{
			throw CSrvException("Create worker thread error.",-1,(long)(__LINE__));
		}
        //�Ѽ����̺߳���ɶ˿ڰ
		CreateIoCompletionPort((HANDLE)m_hListenSocket,m_hCompletionPort,SC_WAIT_ACCEPT,0);
		//������������ʱ��os���������¼�
		WSAEventSelect(m_hListenSocket,m_hPostAcceptEvent[0],FD_ACCEPT);
		//���ü����ȴ����
		errorCode = listen(m_hListenSocket,m_iMaxPostAcceptNumbs);//�ڶ����������������Ӷ�������ĵȴ������Ŀ.���������server��Ҫ�����ֵ
		if(errorCode)
		{
			throw CSrvException("Error socket lister operation.",-1,(long)(__LINE__));
		}
        
		CAcceptContext::InitContextPool(m_iMaxPostAcceptNumbs);//Ĭ�����ӳ�����64������context����
		CTcpReceiveContext::InitContextPool(m_iMaxPostAcceptNumbs);
		CTcpSendContext::InitContextPool(m_iMaxPostAcceptNumbs*10);
		PostAcceptOperation(m_iMaxPostAcceptNumbs/2);//Ͷ�����Ӳ�������ɶ˿�,Ӧ���߲�����
	
		m_iTimerID = timeSetEvent(1000,0,TimerProc,(DWORD)this,TIME_PERIODIC);//1���Ӷ�ʱ��
		
		return 1;
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d, errorCode: %d\n",e.GetExpDescription(),e.GetExpLine(),e.GetExpCode());
		this->ReleaseResource();//�ͷŷ����˵���Դ
		return e.GetExpCode();
	}	
}
int CTcpServer::StartServer(void)
{
	try
	{
		if(m_bServerRunning)
		{
			throw CSrvException("Server is running..",-1,(long)(__LINE__));
		}
		m_bServerRunning = true; //�����������߳�
		if(m_hListenThread)
		{
			ResumeThread(m_hListenThread);
		}

		for (int i=0; i<m_iWorkerThreadNumbers; i++)
		{
			if(m_hWorkerThread[i])
			{
				SetThreadPriority(m_hWorkerThread[i],THREAD_PRIORITY_TIME_CRITICAL);
				ResumeThread(m_hWorkerThread[i]);
			}
		}
		return 1;
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return e.GetExpCode();
	}
	catch(...)
	{
		return 0;
	}
}

int CTcpServer::StopServer(void)
{
	if(!m_bServerRunning)
	{
		StartServer();
	}
    
	//�������������Ŀ���ǰ�socke���������޸�Ϊ������ģʽ
	unsigned long ul = 1;//Ҫ��Ϊ������ģʽ����ֵ�������
	ioctlsocket(m_hListenSocket, FIONBIO, &ul);//����socket ��I/Oģʽ��Ϊͬ�������첽

	m_bServerRunning = false;//�����������߳�
	if(m_hListenThread)
	{
		WaitForSingleObject(m_hListenThread,INFINITE);
	}
	for(int i=0;i<m_iWorkerThreadNumbers;i++)
		PostQueuedCompletionStatus(m_hCompletionPort, COMPLETION_KEY_SHUTDOWN, 0, NULL);
	for(int i=0;i<m_iWorkerThreadNumbers;i++)
	{
		if(m_hWorkerThread[i])
		{
			WaitForSingleObject(m_hWorkerThread[i],INFINITE);
		}
	}
	this->ReleaseResource();
	return 0;
}
//ͨ���˺�����client�����ļ�
//fileName������Ǿ���·��
int CTcpServer::SendFile(SOCKET sock,char* fileName)//ͨ���˺�����Զ�˷����ļ�
{
	if(IsValidSocket(sock) && fileName)
	{
		HANDLE file = CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING, 
			                     FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,0);
		if(INVALID_HANDLE_VALUE != file)
		{
			BY_HANDLE_FILE_INFORMATION Info={0};
			GetFileInformationByHandle( file, &Info );//ͨ���ļ�����õ��ļ���Ϣ

			CTcpSendContext* pContext = CTcpSendContext::GetContext();
			if(pContext)
			{
				pContext->SetSendParameters(sock,NULL,0);
				int errorCode = TransmitFile(sock, file, Info.nFileSizeLow, 0,&pContext->m_struOperateOl,NULL, 0 );
				if(errorCode || (!errorCode && WSAGetLastError() == ERROR_IO_PENDING))
				{
					return 1;
				}
				else
				{
					pContext->ReleaseContext();
				}
			}
		}
		CloseHandle(file);
	}
}
//ͨ���˺���server���������������
int CTcpServer::SendData(SOCKET sock,char* pVoid,long dataSize)
{
	if(IsValidSocket(sock))
	{
		if(pVoid)
		{
			return IssueSendOperation(sock,pVoid,dataSize);
		}
	}
	return 0;
}
int CTcpServer::PushClientSocket(SOCKET clientSock)
{
	int rc = 0;
	::EnterCriticalSection(&m_struCriSec);

	rc = (int)m_mapAcceptSockQueue.size();
	if(m_mapAcceptSockQueue.insert(std::make_pair(clientSock,rc++)).second)
		rc = 1;
	else
		rc = 0;
	LeaveCriticalSection(&m_struCriSec);
	return rc;
}
//�˺�����Ҫ���ڹر�client��������ӣ������й����г����쳣�����ɷ����������ر�
//�κ�����Ҫ�����߳�ͬ������
int CTcpServer::CloseClientSocket(SOCKET clientSocket)
{ 
	::EnterCriticalSection(&this->m_struCriSec);
	SOCKET sock = NULL;
	map<SOCKET,long>::iterator pos;
	pos = m_mapAcceptSockQueue.find(clientSocket);
	if(pos!=m_mapAcceptSockQueue.end())
	{
		sock = pos->first;
		m_mapAcceptSockQueue.erase(pos);
	}
	::LeaveCriticalSection(&this->m_struCriSec);
	if(sock)
	{
		shutdown(sock,SD_SEND); 
		closesocket(sock);//SO_UPDATE_ACCEPT_CONTEXT �����ᵼ�³���TIME_WAIT,��ʹ������DONT
	}
	return 1;
}
bool CTcpServer::IsValidSocket(SOCKET socket)
{
	bool validSocket = false;
	::EnterCriticalSection(&this->m_struCriSec);
	SOCKET sock = NULL;
	map<SOCKET,long>::iterator pos;
	pos = m_mapAcceptSockQueue.find(socket);
	if(pos!=m_mapAcceptSockQueue.end())
	{
		validSocket = true;
	}
	::LeaveCriticalSection(&this->m_struCriSec);
	return validSocket;
}
void CTcpServer::ConnectTimeOutCheck()
{
	EnterCriticalSection(&m_struCriSec);

	map<SOCKET,long>::iterator pos;
	int iIdleTime = 0;
	int nTimeLen = 0;
	for(pos = m_mapAcceptSockQueue.begin();pos!=m_mapAcceptSockQueue.end();)
	{
		nTimeLen = sizeof(iIdleTime);
		//getsockopt(pos->first,SOL_SOCKET,SO_CONNECT_TIME,(char *)&iConnectTime, &nTimeLen);//��ֻ�ܼ��ӿ�ʼ���ӵ����ڵ�ʱ�䣬�����socket���м������ݽ��ջ��ͣ���Ȼ��Ͽ�����
		getsockopt(pos->first,SOL_SOCKET, SO_GROUP_PRIORITY, (char *)&iIdleTime, &nTimeLen);
						
		if((int)time(NULL) - iIdleTime >120) //timeout value is 2 minutes.
		{
			cout<<"�ͻ���: "<<pos->first<<"��ʱ,ϵͳ���رմ�����."<<endl;
			shutdown(pos->first,SD_SEND); 
			closesocket(pos->first);
			m_mapAcceptSockQueue.erase(pos++);
		}
		else
		{
           ++pos;
		}
	}
	LeaveCriticalSection(&m_struCriSec);
}
int CTcpServer::PostAcceptOperation(int postNumbs)
{
	unsigned long dwAcceptNumbs = 0;
	for(int i=0;i<postNumbs;i++)
	{
		if(IssueAcceptOperation())
		{
			dwAcceptNumbs++;
		}
	}
	return dwAcceptNumbs;
}
// ���������̺߳ͼ����߳�
int CTcpServer::CteateThread()
{
	SYSTEM_INFO  sysinfo;
	GetSystemInfo(&sysinfo);
    m_iWorkerThreadNumbers = sysinfo.dwNumberOfProcessors*2+2;//����߳�������CPU������2��
	if(m_iWorkerThreadNumbers>=MAX_PROCESSOR_COUNTER) //ע��˴��ܿ��ܻ��������ܵľ����½�
		m_iWorkerThreadNumbers = MAX_PROCESSOR_COUNTER-1;


	m_hListenThread = (HANDLE)_beginthreadex(NULL,0,ListenThread,this,CREATE_SUSPENDED,NULL);
	if(!m_hListenThread)
		return 0;

    int counter = 0;
	for (int i=0; i<m_iWorkerThreadNumbers; i++)
	{
		m_hWorkerThread[i] = (HANDLE)_beginthreadex(NULL,0,WorkThread,this,CREATE_SUSPENDED,NULL);
		if(!m_hWorkerThread[i]) //���ٴ���һ���߳�
		{
			m_hWorkerThread[i] = NULL;
			continue;
		}	
		counter++;
	}
    return counter;
}
//�ͷ���Դ
int CTcpServer::ReleaseResource(void)
{
	if(m_hListenSocket)
	{
		closesocket(m_hListenSocket);
		m_hListenSocket = NULL;
	}
	map<SOCKET,long>::iterator pos;
	for(pos = m_mapAcceptSockQueue.begin();pos!=m_mapAcceptSockQueue.end();++pos)
	{
		shutdown(pos->first,SD_SEND);
		closesocket(pos->first);
	}
	m_mapAcceptSockQueue.clear();

	timeKillEvent(m_iTimerID);
	CAcceptContext::DestroyContextPool();//�������е�AcceptContext����
	CTcpReceiveContext::DestroyContextPool();
	CTcpSendContext::DestroyContextPool();

	ZeroMemory(&m_struServerAdd,sizeof(m_struServerAdd)); //��������ַ
	if(m_hCompletionPort)
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}
	if(m_hListenThread)
	{
		CloseHandle(m_hListenThread);
		m_hListenThread = NULL;
	}
	for(int i=0;i<m_iWorkerThreadNumbers;i++)
	{
		if(m_hWorkerThread[i])
		{
			CloseHandle(m_hWorkerThread[i]);
			m_hWorkerThread[i] = NULL;
		}
	}
    for(int i=0;i<ACCEPT_EVENT_CNT;i++)
	{
		if(m_hPostAcceptEvent[i])
		{
			CloseHandle(m_hPostAcceptEvent[i]);
			m_hPostAcceptEvent[i] = NULL;
		}

	}
	return 1;
}
//���ڼ��ͻȻ����,ֻ������windows 2000��ƽ̨
//���ͻ���Ҳ��Ҫwin2000����ƽ̨
int CTcpServer::SetHeartBeatCheck(SOCKET clientSock)
{
	DWORD dwError = 0L,dwBytes = 0;
	TCP_KEEPALIVE sKA_Settings = {0},sReturned = {0};
	sKA_Settings.onoff = 1 ;
	sKA_Settings.keepalivetime = 5000 ; // Keep Alive in 5.5 sec.
	sKA_Settings.keepaliveinterval = 1000 ; // Resend if No-Reply

	dwError = WSAIoctl(clientSock, SIO_KEEPALIVE_VALS, &sKA_Settings,sizeof(sKA_Settings), &sReturned, sizeof(sReturned),&dwBytes,NULL, NULL);
	if(dwError == SOCKET_ERROR )
	{
		dwError = WSAGetLastError();
		DebugPrintf("SetHeartBeatCheck->WSAIoctl()��������,�������: %ld",dwError);	
		return 0;
	}
    return 1;
}
//��ʾ�����ӵĿͻ�����Ϣ
void CTcpServer::ShowNewConnectInf(LPWSAOVERLAPPED pOverlapped)
{
	if(pOverlapped)
	{
		CAcceptContext* pContext = CONTAINING_RECORD(pOverlapped,CAcceptContext,m_struOperateOl);

		sockaddr_in* pClientAddr = NULL;
		sockaddr_in* pLocalAddr = NULL;
		int nClientAddrLen = 0;
		int nLocalAddrLen = 0;

		m_pfGetAddrs(pContext->m_ucAddressbuf, 0,ACCEPT_ADDRESS_LENGTH,ACCEPT_ADDRESS_LENGTH,
			(LPSOCKADDR*)&pLocalAddr, &nLocalAddrLen, (LPSOCKADDR*)&pClientAddr, &nClientAddrLen);

		DebugPrintf("�ͻ���:%s :%u ���ӷ������ɹ�.socket:%d\n",inet_ntoa(pClientAddr->sin_addr),ntohs(pClientAddr->sin_port),pContext->m_hSocket);
	}
}
//��������ͣ��ᵼ�µĺ����δ����
int CTcpServer::PauseServer(void)
{
try
	{
		if(m_bServerRunning)
		{
			throw CSrvException("Server have paused",-1);
		}
		if(m_hListenThread)
		{
			SuspendThread(m_hListenThread);
		}

		for (int i=0; i<m_iWorkerThreadNumbers; i++)
		{
			if(!m_hWorkerThread[i])
			{
				SuspendThread(m_hWorkerThread[i]);
			}
		}
		return 1;
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return 0;
	}
	catch(...)
	{
		return 0;
	}
}
UINT WINAPI CTcpServer::ListenThread(LPVOID lpParam)
{
	CTcpServer* pThis = (CTcpServer*)lpParam;
	if(!pThis)
		return 0; 

	unsigned long rc = 0;
	unsigned long postAcceptCnt = 1;
	while(pThis->m_bServerRunning)
	{

		rc = WSAWaitForMultipleEvents(ACCEPT_EVENT_CNT, pThis->m_hPostAcceptEvent, FALSE,1000, FALSE);		
		if(!pThis->m_bServerRunning)
			break;

		if(WSA_WAIT_FAILED == rc)
		{
			pThis->ErrorReport(WSAGetLastError(),"WSAWaitForMultipleEvents");
			continue;
		}
		else if(rc ==WSA_WAIT_TIMEOUT)//��ʱ
		{
			continue;
		}
		else  
		{
			rc = rc - WSA_WAIT_EVENT_0;
			if(rc == 0)
				postAcceptCnt = pThis->m_iMaxPostAcceptNumbs;
			else
				postAcceptCnt = 1;

			pThis->PostAcceptOperation(postAcceptCnt);
		}
	}
	return 0;
}
UINT WINAPI CTcpServer::WorkThread(LPVOID lpParam)
{
	CTcpServer* pThis = (CTcpServer*)lpParam;
	if(!pThis)
		return 0;	

	static long byteCount = 0;
	BOOL    bResult;
	unsigned long   NumTransferred;
	ULONG_PTR contextKey = COMPLETION_KEY_SHUTDOWN ;
	LPOVERLAPPED pOverlapped = NULL;

	while(pThis->m_bServerRunning)
	{
		bResult = GetQueuedCompletionStatus(pThis->m_hCompletionPort,&NumTransferred,&contextKey,&pOverlapped,INFINITE);
		COperateContext* pContext = CONTAINING_RECORD(pOverlapped,COperateContext,m_struOperateOl);
		if ((bResult == FALSE) && (pOverlapped != NULL))//�ͻ��˷������˳�(������������)���ڴ˼�⵽����I/Oϵͳ�ŶӵĲ����᷵��,ֻ��������heartbeat���ƲŻ��д�����
		{
			pThis->DebugPrintf("��⵽�ͻ���:%d �������˳�,�������:%d,������: %d\n",pContext->m_hSocket,GetLastError(),pContext->m_iOperateMode);
			pThis->CloseClientSocket(pContext->m_hSocket);
			pContext->ReleaseContext();
			continue;
		}
		else if((bResult == TRUE) && (pOverlapped == NULL))
		{
          pThis->DebugPrintf("�û����������������˳�\n");	
		  break;
		}
		else if((bResult == TRUE)&& (pOverlapped != NULL))//��������
		{
			if(contextKey == COMPLETION_KEY_IO)
			{
				switch(pContext->m_iOperateMode)
				{
				case SC_WAIT_ACCEPT:
					{
						pThis->CompleteAccept(pOverlapped,NumTransferred);
						break;
					}
				case SC_WAIT_RECEIVE://client gracefulclose handle here �����˳�Ҳ�ڴ������д���
					{
						if(NumTransferred == 0)
						{
							pThis->DebugPrintf("�ͻ���:%d �����˳�\n",pContext->m_hSocket);
							pThis->CloseClientSocket(pContext->m_hSocket);
							pContext->ReleaseContext();
						}
						else
						   pThis->CompleteReceive(pOverlapped,NumTransferred);
						break;
					}
				case SC_WAIT_TRANSMIT:
					{
						pThis->CompleteSend(pOverlapped,NumTransferred);
						break;
					}
				default:
					break;
				}
			}
			else if(contextKey == COMPLETION_KEY_SHUTDOWN)
			{
				pContext->ReleaseContext();
				break;
			}
		}
	}
	return 0;
}
//��ʱ���ص�����,����ͬ�̺߳�����ȫ��ͬ

void PASCAL CTcpServer::TimerProc(UINT wTimerID,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
	CTcpServer* pThis = (CTcpServer*)dwUser;
	pThis->DebugPrintf("RevPool:%ld,Idle:%ld,AccPool: %d,Idle:%ld,SendPool: %ld,Idle: %ld. connect:%ld \n",CTcpReceiveContext::GetContextCounter(),CTcpReceiveContext::GetIdleContextCounter(),CAcceptContext::GetContextCounter(),CAcceptContext::GetIdleContextCounter(),CTcpSendContext::GetContextCounter(),CTcpSendContext::GetIdleContextCounter(),pThis->m_mapAcceptSockQueue.size());
    
	pThis->ConnectTimeOutCheck();

	//CTcpReceiveContext::ShowContextIndex();

			
}
int CTcpServer::IssueAcceptOperation()
{
	try
	{
		int errorCode = 1;
		unsigned long dwBytes = 0;
		unsigned long dwAcceptNumbs = 0;

		SOCKET hClientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET == hClientSocket)
		{
			CloseClientSocket(hClientSocket);
			throw CSrvException("PostAcceptOperation()->WSASocket(),Invalid socket handle.",-1,(long)(__LINE__));
		}
		//����Ϊ�첽ģʽ
		ULONG ul = 1;
		errorCode =ioctlsocket(hClientSocket, FIONBIO, &ul);
		if(SOCKET_ERROR == errorCode)
		{
			CloseClientSocket(hClientSocket);
			throw CSrvException("PostAcceptOperation()->ioctlsocket(),incorrect ioctlsocket operation.",-1,(long)(__LINE__));
		}
		CAcceptContext* pAccContext = CAcceptContext::GetContext();
		if (NULL == pAccContext)
		{
			CloseClientSocket(hClientSocket);
			throw CSrvException("PostAcceptOperation()->CAcceptContext::GetContext(),Invalid AcceptContext handle.",-1,(long)(__LINE__));
		}
		pAccContext->SetAcceptParameters(this->m_hListenSocket,hClientSocket);

		errorCode = m_pfAcceptEx(pAccContext->m_struListenSocket,pAccContext->m_hSocket, pAccContext->m_ucAddressbuf,0,ACCEPT_ADDRESS_LENGTH, ACCEPT_ADDRESS_LENGTH, &dwBytes, &(pAccContext->m_struOperateOl));
		if(FALSE == errorCode && ERROR_IO_PENDING != WSAGetLastError())
		{
			CloseClientSocket(hClientSocket);
			pAccContext->ReleaseContext();
			throw CSrvException("PostAcceptOperation()->AcceptEx,incorrect AcceptEx operation.",-1,(long)(__LINE__));
		}
		return 1;
	}
	catch(CSrvException& e)
	{	
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return 0;
	}
}
//���������������
//�ڴ˺�������Ҫ����net conncet sockt�Ĳ���
//Ͷ����һ��accept��������socket��Ͷ��receive����
int CTcpServer::CompleteAccept(LPWSAOVERLAPPED pOverlapped,unsigned long dwTransferBytes)
{
	try
	{
		if(pOverlapped)
		{
			CAcceptContext* pContext = CONTAINING_RECORD(pOverlapped,CAcceptContext,m_struOperateOl);

			m_struTestSockt = pContext->m_hSocket;  //������
			PushClientSocket(pContext->m_hSocket);//���������socket��ջ,���й���

			int errorCode = 0;
			//int nZero=1024*1000;//�رշ��ͻ�����
			//errorCode = setsockopt(pContext->m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(nZero));
			//errorCode = setsockopt(pContext->m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(nZero));

			int nOpt = 1;//socket���ã���ֹ�����ִ���TIME_WAIT״̬��ʱ������socket
			errorCode = setsockopt(pContext->m_hSocket,SOL_SOCKET ,SO_REUSEADDR,(const char*)&nOpt,sizeof(nOpt));
			if(errorCode == SOCKET_ERROR)
			{
				CloseClientSocket(pContext->m_hSocket);
				pContext->ReleaseContext();
				throw CSrvException("CompleteAccept->setsockopt() error..",-1,(long)(__LINE__));
			}
			int dontLinget = 1;//�������ر�socket��ʱ��,��ִ���������Ĳ����ֹرգ�����ִ��RESET
			errorCode = setsockopt(pContext->m_hSocket,SOL_SOCKET,SO_DONTLINGER,(char *)&dontLinget,sizeof(dontLinget)); 
			if(errorCode == SOCKET_ERROR)
			{
				CloseClientSocket(pContext->m_hSocket);
				pContext->ReleaseContext();
				throw CSrvException("CompleteAccept->setsockopt() error..",-1,(long)(__LINE__));
			}
			//char chOpt=1; //���͵�ʱ��ر�Nagle�㷨,�ر�nagel�㷨�п��ܻ��������
			//errorCode = setsockopt(pContext->m_hSocket,IPPROTO_TCP,TCP_NODELAY,&chOpt,sizeof(char));   
			//if(errorCode == SOCKET_ERROR)
			//{
			//	CloseClientSocket(pContext->m_hSocket);
			//	pContext->ReleaseContext();
			//	throw CSrvException("CompleteAccept->setsockopt() error..",-1,(long)(__LINE__));
			//}
			int accTime = (int)time(NULL);//���µ�ǰsocket���ʱ��,���ڳ�ʱ���
			errorCode = setsockopt(pContext->m_hSocket, SOL_SOCKET, SO_GROUP_PRIORITY, (char *)&accTime, sizeof(accTime));
			if(errorCode == SOCKET_ERROR)
			{
				CloseClientSocket(pContext->m_hSocket);
				pContext->ReleaseContext();
				throw CSrvException("CompleteAccept->setsockopt() error..",-1,(long)(__LINE__));
			}
			if(!this->SetHeartBeatCheck(pContext->m_hSocket))//��������������
			{
				CloseClientSocket(pContext->m_hSocket);
				pContext->ReleaseContext();
				throw CSrvException("CompleteAccept->setsockopt() error..",-1,(long)(__LINE__));
			}

			//�ڿͻ��˷����������ʱ��,��������ù��ܣ�����ֺ����IssueReceiveOperation�б�10057����,���˺�������ɿ���û����ȷ�������ͻ�����Ϣ
			//this->ShowNewConnectInf(pOverlapped);

			if(NULL == CreateIoCompletionPort((HANDLE)pContext->m_hSocket,this->m_hCompletionPort,(ULONG_PTR)0,0))
			{
				CloseClientSocket(pContext->m_hSocket);
				pContext->ReleaseContext();
				throw CSrvException("CompleteAccept->setsockopt() error..",-1,(long)(__LINE__));
			}
			else
			{   
				if(!IssueReceiveOperation(pContext->m_hSocket))//���ͽ�����������
				{
					CloseClientSocket(pContext->m_hSocket);
					pContext->ReleaseContext();
					throw CSrvException("CompleteAccept->IssueReceiveOperation() occured an error.",-1,(long)(__LINE__));
				}
			}
			if(!IssueAcceptOperation())
			{
				ReleaseSemaphore(m_hPostAcceptEvent[1],1,NULL);
			}
			pContext->ReleaseContext();
			return 1;
		}
		else
		{
			throw CSrvException("CompleteAccept->pOverlapped is null..",-1,(long)(__LINE__));
		}
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return 0;
	}
}
//�����첽��������
int CTcpServer::IssueReceiveOperation(SOCKET socket)
{
	try
	{
		CTcpReceiveContext* pContext = CTcpReceiveContext::GetContext(socket);
		if(pContext)
		{
			//�������ӵ�socket��Ͷ��receive�������ȴ�remote client�������ݹ���.
			unsigned long bytes = 0;
			unsigned long flag = 0;
			int err = WSARecv(pContext->m_hSocket,pContext->GetBufAddr(),1,&bytes,&flag, &(pContext->m_struOperateOl), NULL);
			if (SOCKET_ERROR == err && WSA_IO_PENDING != WSAGetLastError())
			{
				pContext->ReleaseContext();
				ErrorReport(WSAGetLastError(),"IssueReceiveOperation()->WSARecv()");
				throw CSrvException("IssueReceiveOperation->WSARecv() error.",-1,(long)(__LINE__));
			}
			return 1;
		}
		else
		{
			throw CSrvException("IssueReceiveOperation->CTcpReceiveContext::GetContext() occured an error.",-1,(long)(__LINE__));
		}
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return 0;
	}
}
////�����������
//Ҫ��ɵĹ�����
//1  ��������
//2  Ͷ����һ��Receive����
//3  ��2�Ļ�����������һ��receive��context
int CTcpServer::CompleteReceive(LPWSAOVERLAPPED pOverlapped,unsigned long dwTransferBytes)
{
	try
	{
		if(pOverlapped)
		{
			CTcpReceiveContext* pContext = CONTAINING_RECORD(pOverlapped,CTcpReceiveContext,m_struOperateOl);
			if(dwTransferBytes && pContext)
			{
				//���µ�ǰsocket���ʱ��,���ڳ�ʱ���
				//�˹��ܷŵ�complete�п���ʹϵͳ�����ܸ���
				int revTime = (int)time(NULL);
				int errorCode = setsockopt(pContext->m_hSocket, SOL_SOCKET, SO_GROUP_PRIORITY, (char *)&revTime, sizeof(revTime));
				if(SOCKET_ERROR == errorCode)
				{
					pContext->ReleaseContext();
					CloseClientSocket(pContext->m_hSocket);
					throw CSrvException("CompleteReceive->setsockopt() error..",-1,(long)(__LINE__));
				}
				//�ڴ˴���Ҫ�жϽ��������Ƿ���ɼ���������
			    SaveReceivedData(pContext->m_hSocket,pContext->GetBufAddr()->buf,dwTransferBytes);
				
				//IssueSendOperation(pContext->m_hSocket,pContext->GetBufAddr()->buf,dwTransferBytes);//�ѽ��յ�������ԭ�ⲻ���ط��ظ�client
				
				if(!IssueReceiveOperation(pContext->m_hSocket))
				{
					pContext->ReleaseContext();
					CloseClientSocket(pContext->m_hSocket);
					throw CSrvException("CompleteReceive->IssueReceiveOperation() error..",-1,(long)(__LINE__));
				}
			}	
			else if(dwTransferBytes==0)//client �����Ͽ�������
			{
				CloseClientSocket(pContext->m_hSocket);
			}
			pContext->ReleaseContext();
			return 1;
		}
		else
		{
			throw CSrvException("CompleteReceive->pOverlapped is null.",-1,(long)(__LINE__));
		}
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return 0;
	}
}
////�����첽�ļ���������
int CTcpServer::IssueSendOperation(SOCKET cliSock,char* pData,unsigned long dwTransferBytes)
{
	try
	{
		unsigned long dwBytes = 0,err = 0;
		unsigned long leavingBytes = dwTransferBytes; 
		if(leavingBytes!=0)
		{		
			CTcpSendContext* pContext = NULL;
			do
			{
				pContext = CTcpSendContext::GetContext();
				leavingBytes = pContext->SetSendParameters(cliSock,pData,leavingBytes);
				err = WSASend(pContext->m_hSocket,&pContext->m_struSendBuf,1,&dwBytes,0,&pContext->m_struOperateOl,NULL);
				if(SOCKET_ERROR == err && WSA_IO_PENDING != WSAGetLastError())
				{
					pContext->ReleaseContext();
					DebugPrintf("IssueSendOperation->WSASend() occured a error.�������:%ld.",WSAGetLastError());
				    throw CSrvException("IssueSendOperation->WSASend occured an error.",-1,(long)(__LINE__));
				}
			}while(leavingBytes!=0);
			return 1;
		}
		else
		{
			throw CSrvException("IssueSendOperation->WSASend occured an error.",-1,(long)(__LINE__));
		}
	}
	catch(CSrvException& e)
	{
		DebugPrintf("%s at line:%d\n",e.GetExpDescription(),e.GetExpLine());
		return 0;
	}
}
////�ļ����������������
int CTcpServer::CompleteSend(LPWSAOVERLAPPED pOverlapped,unsigned long dwTransferBytes)
{
	if(pOverlapped)
	{
		CTcpSendContext* pContext = CONTAINING_RECORD(pOverlapped,CTcpSendContext,m_struOperateOl);
		if(pContext->m_struSendBuf.len != dwTransferBytes)
			DebugPrintf("Ͷ�ݵ�send ��������û�з������.\n");

		char buf[512] = "test\n";
		IssueSendOperation(pContext->m_hSocket,buf,512);	
		pContext->ReleaseContext();	
		//DebugPrintf("�ɹ������ֽ���Ϊ:%ld\n",dwTransferBytes);
		return 1;
	}
	return 0;
}

void CTcpServer::ErrorReport(unsigned long errorCode,char* description)
{
	DebugPrintf("����: %s ��������,�������Ϊ: %d\n",description,errorCode);
}
void CTcpServer::DebugPrintf(char* szFormat,...)
{
	 EnterCriticalSection(&m_struCriSec);
     
     va_list args;
     va_start(args, szFormat);
     
     vprintf(szFormat, args );
     
     va_end(args);
     
     LeaveCriticalSection(&m_struCriSec);
}