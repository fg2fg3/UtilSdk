#include "StdAfx.h"
#include ".\webserver.h"

CWebServer::CWebServer(void)
{
	m_mapWebSocketBuffer.clear();
	InitializeCriticalSection(&m_struCriSec);
}

CWebServer::~CWebServer(void)
{
	m_mapWebSocketBuffer.clear();
	DeleteCriticalSection(&m_struCriSec);
}
//�˺����ѵײ�ģ����յ����ֽڱ��浽�Լ��Ļ�������
const int Size = 1024*4;
static int currentLen = 0;
static char testBuf[Size];
void CWebServer::SaveReceivedData(SOCKET sock,char* pVoid,long dataLen)
{

	/*CMemoryBlock* pBuffer = NULL;
    SOCKET clientSockt = sock;
	::EnterCriticalSection(&m_struCriSec);
	int rc = 0;
	map<SOCKET,CMemoryBlock*>::iterator pos;
	pos = m_mapWebSocketBuffer.find(clientSockt);
	if(pos!=m_mapWebSocketBuffer.end())
	{
		pBuffer = pos->second;
		rc = 1;
	}
	else
	{
		pBuffer = new CMemoryBlock();
		pBuffer->m_iBufferSize = 0;
		if(m_mapWebSocketBuffer.insert(clientSockt,pBuffer))
		{
			rc = 1;
		}
		else
		{
			rc = 0;
		}
	}
	::LeaveCriticalSection(&m_struCriSec);*/

	this->SendData(sock,pVoid,dataLen);

}
