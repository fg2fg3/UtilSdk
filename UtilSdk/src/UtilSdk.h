// UtilSdk.h : UtilSdk DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUtilSdkApp
// �йش���ʵ�ֵ���Ϣ������� UtilSdk.cpp
//

class CUtilSdkApp : public CWinApp
{
public:
	CUtilSdkApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
