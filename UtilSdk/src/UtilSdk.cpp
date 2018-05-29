// UTILSDK.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "UtilSdk.h"
#include "UtilSdkProc.h"
#include "zlib/zlib.h"
#include <iostream>

using namespace std;

// ���ǵ���������һ��ʾ��
UTILSDK_API int nUtilSdk = 0;

// ���ǵ���������һ��ʾ����
UTILSDK_API int fnUtilSdk()
{
	return 42;
}

UTILSDK_API	void*	UTILSDK_Init()
{

	return nullptr;
}

UTILSDK_API	void	UTILSDK_Uninit(void* pHandle)
{

}

UTILSDK_API int		UTILSDK_ZipFile(char * DestName, const char *SrcName, int para)
{
	char SourceBuffer[102400] = { 0 };  //ѹ���ļ�ʱ��Դbuffer

	FILE* fp;  //����ѹ���ļ�ʱ�ļ���ָ��
	FILE* fp1;  //����ѹ���ļ�ʱ��ָ��
	errno_t err; //��������Ķ���
	err = fopen_s(&fp, SrcName, "r+b");
	//��ȡ�ļ�����
	long cur = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	long fileLength = ftell(fp);
	fseek(fp, cur, SEEK_SET);


	//��ȡ�ļ���buffer
	fread(SourceBuffer, fileLength, 1, fp);
	fclose(fp);

	//ѹ��buffer�е�����
	uLongf SourceBufferLen = 102400;
	char* DestBuffer = (char*)::calloc((uInt)SourceBufferLen, 1);
	err = compress((Bytef*)DestBuffer, (uLongf*)&SourceBufferLen, (const Bytef*)SourceBuffer, (uLongf)fileLength);
	if (err != Z_OK)
	{
		cout << "ѹ��ʧ�ܣ�" << err << endl;
		return 1;
	}

	//����һ���ļ�����д��ѹ���������
	err = fopen_s(&fp1, DestName, "w+b");
	if (!fp1)
	{
		printf("ѹ���ļ�����ʧ��! \n");
		return 1;
	}

	fwrite(DestBuffer, SourceBufferLen, 1, fp1);
	cout << "ѹ������" << endl;
	fclose(fp1);
	return 0;
}

UTILSDK_API int		UTILSDK_UnzipFile(char * DestName, const char *SrcName, int para)
{
	char uSorceBuffer[102400] = { 0 };  //��ѹ���ļ�ʱ��Դbuffer
	FILE* fp3;  //������ѹ�ļ����ļ�ָ��
	FILE* fp4;  //������ѹ�ļ����ļ�ָ��
	errno_t err; //��������Ķ���
	//������ѹ���ļ�
	err = fopen_s(&fp3, SrcName, "r+b");
	if (err)
	{
		printf("�ļ���ʧ��! \n");
		return 1;
	}

	//��ȡ����ѹ�ļ��Ĵ�С
	long ucur = ftell(fp3);
	fseek(fp3, 0L, SEEK_END);
	long ufileLength = ftell(fp3);
	fseek(fp3, ucur, SEEK_SET);


	//��ȡ�ļ���buffer
	fread(uSorceBuffer, ufileLength, 1, fp3);
	fclose(fp3);

	uLongf uDestBufferLen = 1024000;//�˴�������Ҫ�㹻�������ɽ�ѹ��������
	char* uDestBuffer = (char*)::calloc((uInt)uDestBufferLen, 1);
	//��ѹ��buffer�е�����
	/*
	int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
	uncompress ������ source �����������ݽ�ѹ���� dest ��������
	sourceLen �� source �������Ĵ�С(���ֽڼ�)��ע�⺯���ĵڶ�
	������ destLen �Ǵ�ַ���á������ú���ʱ��destLen ��ʾ dest
	�������Ĵ�С�� dest ������Ҫ�������½�ѹ������ݡ��ڽ��н�
	ѹ��ʱ����Ҫ��ǰ֪����ѹ�������ݽ�ѹ�������ж�����Ҫ��
	�ڽ���ѹ��֮ǰ������ԭʼ���ݵĴ�С(Ҳ���ǽ�ѹ������ݵĴ�
	С)���ⲻ�� zlib ������Ĺ��ܣ���Ҫ����������Ĺ�����������
	�˳��� destLen �ǽ�ѹ���������ݵ�ʵ�ʴ�С��
	*/
	err = uncompress((Bytef*)uDestBuffer, (uLongf*)&uDestBufferLen, (Bytef*)uSorceBuffer, (uLongf)ufileLength);

	if (err != Z_OK)
	{
		cout << "��ѹ��ʧ�ܣ�" << err << endl;
		return 1;
	}

	//����һ���ļ�����д���ѹ���������
	err = fopen_s(&fp4, DestName, "wb");
	if (err)
	{
		printf("��ѹ���ļ�����ʧ��! \n");
		return 1;
	}

	//printf("д������... \n");
	cout << "��ѹ���ݳɹ���" << endl;

	/*
	size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream );
	����fwrite��MSDN��׼����������buffer����Ҫ���ļ���д����������ڴ��е��׵�ַָ�룬
	size�Ǵ�д�����ݵ�ÿ��Ԫ�ص��ֽ�����count��Ҫд���ٸ�Ԫ�أ�stream ���ļ�ָ��
	*/
	fwrite(uDestBuffer, uDestBufferLen, 1, fp4);
	//cout << uDestBuffer << endl;
	fclose(fp4);
	return 0;
}