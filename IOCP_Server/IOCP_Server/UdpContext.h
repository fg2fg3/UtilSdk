#pragma once
#ifndef _UDP_CONTEXT_
#define _UDP_CONTEXT_

#include "operatecontext.h"
#include "BaseDefine.h"
#include "ContextStack.h"

const int MAX_UDP_CONTEXT_BUFSIZE = 4*1024; //4K
const int DEFAULT_UDP_POOL_SIZE = 256;

class CUdpContext :public COperateContext
{
private:
	CUdpContext();
	~CUdpContext(void);
public:
	long SetSendParameters(struct sockaddr_in& remoteAddr,char* dataAddr,unsigned long transferByte);
	virtual void ResetContext();
	LPWSABUF GetSendBuf(){return &m_struRevBuf;}
public:
	struct sockaddr_in m_struRemoteAddr;
	WSABUF m_struRevBuf;

public:
	static long GetContextCounter();
	static long GetIdleContextCounter();

public://����ĺ������ڽ���context pool�Ĺ���
	static void InitContextPool(long poolSize = DEFAULT_UDP_POOL_SIZE);
	static CUdpContext* GetContext(SOCKET socket,int operateMode); //���new����
	void ReleaseContext();//���delete����
	static void DestroyContextPool();
	static void ShowContextIndex();
private:
	static bool m_bInitialized;
	static CContextStack* m_pUdpContextStack; //ʵ�ʸ�������
	static CContextStack* m_pUdpManageContextStack;//������Դ����
	static CRITICAL_SECTION m_struCriSec;	
};
#endif