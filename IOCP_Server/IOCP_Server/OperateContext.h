#pragma once

#ifndef _OPERATE_CONTEXT_H
#define _OPERATE_CONTEXT_H

#include <winsock2.h>
#include "BaseDefine.h"

const int DESTROY_ALL_CONTEXT = 0xffffffff;

class COperateContext
{
public:
	COperateContext(void);
	~COperateContext(void);
//������������
public:
	WSAOVERLAPPED m_struOperateOl;//peer handle overlapped struct
	SOCKET m_hSocket; //client socket
	int m_iOperateMode ;//current context operation mode
    long m_iContextIndex;
//����Ĵ��붼������Դ�������������
public:
	virtual void ResetContext(){;}
	virtual void ReleaseContext(){;}
	//����ĺ����ڼ̳����ж���ʵ��
	//static void InitContextPool(long poolSize)
	//static COperateContext* GetContext();
	//static void DestroyContextPool();
	//static long GetContextCounter();
};

#endif
