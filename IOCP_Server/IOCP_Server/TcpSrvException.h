#pragma once

#ifndef _TCPSRVEXCEPTION_H
#define _TCPSRVEXCEPTION_H

#pragma warning( disable : 4290 )  //vc++����������֧���쳣�淶�����Ժ��Դ˾���


class CSrvException
{
public:
	CSrvException(void);
	CSrvException(const char* expDescription,int expCode,long expLine = 0);
	~CSrvException(void);
public:
	char* GetExpDescription(){return this->m_strExpDescription;};
	int GetExpCode(){return this->m_iExpCode;};
	long GetExpLine(){return this->m_iExpLineNumber;};
private:
	char m_strExpDescription[512];//�쳣���ı�����
	int m_iExpCode;//�쳣����
	long m_iExpLineNumber;//�쳣Դ������������Ե��԰汾��Ч
};

#endif
