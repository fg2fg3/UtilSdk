#pragma once
#ifndef _ACCEP_CONTEXT_H
#define _ACCEP_CONTEXT_H

#include "ContextStack.h"

#include "OperateContext.h"

const long DEFAULT_ACCEPT_CONTEXT_POOL = 256;

//tcp accept operation context
const int ACCEPT_ADDRESS_LENGTH = ((sizeof( struct sockaddr_in) + 16));

class CAcceptContext :public COperateContext
{
private:
	CAcceptContext(int opMode,SOCKET listenSocket,SOCKET clientSocket);
	~CAcceptContext(void);
public:
	SOCKET m_struListenSocket;
	unsigned char m_ucAddressbuf[ACCEPT_ADDRESS_LENGTH*2];

public:
	void SetAcceptParameters(SOCKET listenSocket,SOCKET clientSocket);
	void ResetContext();
	static long GetContextCounter();
	static long GetIdleContextCounter();

public://����ĺ������ڽ���context pool�Ĺ���
	static void InitContextPool(long poolSize = DEFAULT_ACCEPT_CONTEXT_POOL);
	static CAcceptContext* GetContext(); //���new����
	void ReleaseContext();//���delete����
	static void DestroyContextPool();
	static void ShowContextIndex();
private:
	static bool m_bInitialized;
	static CContextStack* m_pAcceptContextStack; //ʵ�ʸ�������
	static CContextStack* m_pAcceptContextManageStack;//������Դ����
	static CRITICAL_SECTION m_struCriSec;	

};

#endif
