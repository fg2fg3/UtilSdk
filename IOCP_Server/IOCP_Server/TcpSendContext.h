#pragma once

#include "operatecontext.h"
#include "MemoryBlock.h"
#include "ContextStack.h"

const long DEFAULT_TCPSEND_CONTEXT_POOL_SIZE = 256;//Ĭ�Ϸ���context pool����������Ӳ��������������ܵ����β���
const long DEFAULT_TCP_SEND_CONTEXT_SIZE = 1024*4;//Ĭ�ϵ�ÿһ�δ�������ֽ���

class CTcpSendContext :public COperateContext
{
private:
	CTcpSendContext(SOCKET cliSock,int operateMode = SC_WAIT_TRANSMIT);
	~CTcpSendContext(void);
private:
	CMemoryBlock* m_pSendDataBuf;
public:
//	TRANSMIT_FILE_BUFFERS m_struTransmitFileBuf;
	WSABUF m_struSendBuf;
public:
	long SetSendParameters(SOCKET cliScok,char* dataAddr,unsigned long transferByte);
	void ResetContext();
	static long GetContextCounter();
	static long GetIdleContextCounter();
	long GetContextSize(){return DEFAULT_TCP_SEND_CONTEXT_SIZE;}

public://����ĺ������ڽ���context pool�Ĺ���
	static void InitContextPool(long poolSize = DEFAULT_TCPSEND_CONTEXT_POOL_SIZE);
	static CTcpSendContext* GetContext(); 
	void ReleaseContext();
	static void DestroyContextPool();
private:
	static bool m_bInitialized;
	static CContextStack* m_pTcpSendContextStack;
	static CContextStack* m_pTcpSendContextManageStack;
	static CRITICAL_SECTION m_struCriSec;	
};
