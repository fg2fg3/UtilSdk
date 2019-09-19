#pragma once
#ifndef _BASE_DEFINE_H_
#define _BASE_DEFINE_H_

#include <winsock2.h>
#include <MSWSock.h>
#pragma comment(lib,"ws2_32")   // Standard socket API.
#pragma comment(lib,"mswsock")  // AcceptEx, TransmitFile, etc,.
#pragma comment(lib,"shlwapi")  // UrlUnescape.

using namespace std;
#include <iostream>

//#include <MSTcpIP.h> //���ļ����������define���弰struct����,����socketʵ��heartbeat���.�����ļ���win2000�Ͽ���û�У������Լ�����


#define  SIO_KEEPALIVE_VALS  IOC_IN | IOC_VENDOR | 4
//�Զ���Ľṹ��,����TCP������
typedef struct tcp_keepalive
{
	unsigned long onoff;
	unsigned long keepalivetime;
	unsigned long keepaliveinterval;
}TCP_KEEPALIVE,*PTCP_KEEPALIVE;


//#define NULL 0
#define SA struct sockaddr_in

const int MAX_PROCESSOR_COUNTER = 10;//��ඨ��10��������

enum SERVER_COMPLETE_KEY
{
    COMPLETION_KEY_IO = 0,
	COMPLETION_KEY_SHUTDOWN = 1,
};

enum SOCKET_CONTEXT_STATE
{
	SC_WAIT_ACCEPT   =   0,
	SC_WAIT_RECEIVE  =   1,
	SC_WAIT_TRANSMIT =   2,
	SC_WAIT_RESET    =   3,
};












#endif