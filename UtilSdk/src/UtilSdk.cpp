// UTILSDK.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <windows.h>
#include "UtilSdk.h"
#include "UtilSdkProc.h"
#include <iostream>
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>/*
#include "zlib.h"
#include "zconf.h"
#include "contrib/minizip/zip.h"
#include "contrib/minizip/unzip.h"
#include "contrib/minizip/ioapi.h"*/
#include <vector>

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

UTILSDK_API int		UTILSDK_ZipFile(const char * DestName, const char *SrcName, int para)
{
	return true;
}


UTILSDK_API int UTILSDK_UnzipFile(const char * DestName, const char *zip_file, int para/* =0 */)
{
	//unzFile zFile;
	//zFile = unzOpen64(zip_file);
	//if (zFile == NULL)
	//{
	//	cout << zip_file << "�ļ���ʧ��" << endl;
	//	return -1;
	//}

	//unz_global_info64 zGlobalInfo;

	//if (UNZ_OK != unzGetGlobalInfo64(zFile, &zGlobalInfo))
	//{
	//	// ������  
	//	cout << __FILE__ << "��" << __LINE__ << "�д��󣻵õ�ȫ����Ϣ����" << endl;
	//	return -1;
	//}

	//unz_file_info64 zFileInfo;
	//unsigned int num = 512;
	//char *fileName = new char[num];

	//for (int i = 0; i < zGlobalInfo.number_entry; i++)
	//{
	//	// ���������ļ�  
	//	if (UNZ_OK != unzGetCurrentFileInfo64(zFile, &zFileInfo, fileName, num, NULL, 0, NULL, 0))
	//	{
	//		//��������Ϣ  
	//		cout << __FILE__ << "��" << __LINE__ << "�д��󣻵õ���ǰ�ļ���Ϣ����" << endl;
	//	}
	//	unzGoToNextFile(zFile);
	//}
	//if (UNZ_OK != unzOpenCurrentFile(zFile))
	//{
	//	//��������Ϣ  
	//	cout << __FILE__ << "��" << __LINE__ << "�д��󣻴�ѹ������" << fileName << "�ļ�ʧ�ܣ�" << endl;
	//}
	//cout << "ѹ���ļ�" << fileName << "����Ϊ��" << endl;
	//int fileLength = zFileInfo.uncompressed_size;
	//char *fileData = new char[fileLength];
	////std::vector<char*> file;
	//int len = 1;
	//while (len)
	//{
	//	//��ѹ���ļ�  
	//	len = unzReadCurrentFile(zFile, (voidp)fileData, fileLength - 1);
	//	fileData[len] = '\0';
	//	for (int j = 0; j < len; j++)
	//	{
	//		//file.push_back(fileData[j]);
	//	}
	//}
	////for (int j = 0; j < file.size(); j++)
	////{
	////	cout << file[j];
	////}
	//unzCloseCurrentFile(zFile);
	//free(fileData);
	//unzClose(zFile);
	return 0;
}
//
//UTILSDK_API int UTILSDK_UnzipFile3(const char * DestName, const char *zip_file, int para/* =0 */)
//{
//	struct data zip;
//	FILE *fp, *out;
//	void *buf, *source, *name, *tmp;
//	unsigned short s = 0x9c78;
//	unsigned long blen;
//
//	if ((fp = fopen(zip_file, "rb")) == NULL)
//		error_quit("Open File");
//
//	while (!feof(fp))
//	{
//		fread(&zip, sizeof(struct data), 1, fp);
//		if (zip.f_len <= 0)
//			break;
//		name = malloc(zip.f_len + 1);
//		memset(name, 0,zip.f_len + 1);
//		fread(name, zip.f_len, 1, fp);
//
//		if (zip.e_len > 0)
//			fseek(fp, zip.e_len, SEEK_CUR);
//
//		//if (zip.d_len == 0)
//		//	mkdir(name, 0777);
//		/*else */if (zip.d_len == zip.len)
//		{
//			if ((out = fopen((char*)name, "w")) == NULL)
//				error_quit("Create File");
//
//			printf("Unzip %s . . .\n", name);
//
//			buf = malloc(zip.d_len + 1);
//			memset(buf, 0,zip.d_len + 1);
//
//			fread(buf, zip.d_len, 1, fp);
//			fwrite(buf, zip.d_len, 1, out);
//
//			fclose(out);
//			free(buf);
//
//			printf("Unzip %s Successed . . .\n", name);
//		}
//		else
//		{
//			buf = malloc(zip.d_len + 1);
//			memset(buf,0, zip.d_len + 1);
//			fread(buf, zip.d_len, 1, fp);
//
//			source = malloc(zip.len + 1);
//			memset(source, 0,zip.len + 1);
//
//			tmp = malloc(zip.d_len + 3);
//			memset(tmp, 0,zip.d_len + 3);
//			memcpy(tmp, &s, sizeof(s));
//			memcat((char*)tmp, (char*)buf, zip.d_len);
//
//			if ((out = fopen((char*)name, "w")) == NULL)
//				error_quit("Create File");
//
//			printf("Unzip %s . . .\n", name);
//
//			blen = compressBound(zip.len);
//			uncompress((Bytef*)source, &blen, (Bytef*)tmp, zip.len);
//
//			fwrite(source, zip.len, 1, out);
//
//			fclose(out);
//			free(source);
//			free(tmp);
//			free(buf);
//
//			printf("Unzip %s Successed . . .\n", name);
//		}
//
//		free(name);
//	}
//
//	fclose(fp);
//	return true;
//}
//
//
//UTILSDK_API int		UTILSDK_UnzipFile2(const char * DestName, const char *SrcName, int para)
//{
//	char uSorceBuffer[102400] = { 0 };  //��ѹ���ļ�ʱ��Դbuffer
//	FILE* fp3;  //������ѹ�ļ����ļ�ָ��
//	FILE* fp4;  //������ѹ�ļ����ļ�ָ��
//	errno_t err; //��������Ķ���
//	//������ѹ���ļ�
//	err = fopen_s(&fp3, SrcName, "r+b");
//	if (err)
//	{
//		printf("�ļ���ʧ��! \n");
//		return 1;
//	}
//
//	//��ȡ����ѹ�ļ��Ĵ�С
//	long ucur = ftell(fp3);
//	fseek(fp3, 0L, SEEK_END);
//	long ufileLength = ftell(fp3);
//	fseek(fp3, ucur, SEEK_SET);
//
//
//	//��ȡ�ļ���buffer
//	fread(uSorceBuffer, ufileLength, 1, fp3);
//	fclose(fp3);
//
//	uLongf uDestBufferLen = 1024000;//�˴�������Ҫ�㹻�������ɽ�ѹ��������
//	char* uDestBuffer = (char*)::calloc((uInt)uDestBufferLen, 1);
//	//��ѹ��buffer�е�����
//	/*
//	int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
//	uncompress ������ source �����������ݽ�ѹ���� dest ��������
//	sourceLen �� source �������Ĵ�С(���ֽڼ�)��ע�⺯���ĵڶ�
//	������ destLen �Ǵ�ַ���á������ú���ʱ��destLen ��ʾ dest
//	�������Ĵ�С�� dest ������Ҫ�������½�ѹ������ݡ��ڽ��н�
//	ѹ��ʱ����Ҫ��ǰ֪����ѹ�������ݽ�ѹ�������ж�����Ҫ��
//	�ڽ���ѹ��֮ǰ������ԭʼ���ݵĴ�С(Ҳ���ǽ�ѹ������ݵĴ�
//	С)���ⲻ�� zlib ������Ĺ��ܣ���Ҫ����������Ĺ�����������
//	�˳��� destLen �ǽ�ѹ���������ݵ�ʵ�ʴ�С��
//	*/
//	err = uncompress((Bytef*)uDestBuffer, (uLongf*)&uDestBufferLen, (Bytef*)uSorceBuffer, (uLongf)ufileLength);
//
//	if (err != Z_OK)
//	{
//		cout << "��ѹ��ʧ�ܣ�" << err << endl;
//		return 1;
//	}
//
//	//����һ���ļ�����д���ѹ���������
//	err = fopen_s(&fp4, DestName, "wb");
//	if (err)
//	{
//		printf("��ѹ���ļ�����ʧ��! \n");
//		return 1;
//	}
//
//	//printf("д������... \n");
//	cout << "��ѹ���ݳɹ���" << endl;
//
//	/*
//	size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream );
//	����fwrite��MSDN��׼����������buffer����Ҫ���ļ���д����������ڴ��е��׵�ַָ�룬
//	size�Ǵ�д�����ݵ�ÿ��Ԫ�ص��ֽ�����count��Ҫд���ٸ�Ԫ�أ�stream ���ļ�ָ��
//	*/
//	fwrite(uDestBuffer, uDestBufferLen, 1, fp4);
//	//cout << uDestBuffer << endl;
//	fclose(fp4);
//	return 0;
//}

//struct data
	//{
	//	unsigned long head;
	//	unsigned short pk;
	//	unsigned short q;
	//	unsigned short type;
	//	unsigned short time;
	//	unsigned short date;
	//	unsigned long crc;
	//	unsigned long d_len;
	//	unsigned long len;
	//	unsigned short f_len;
	//	unsigned short e_len;
	//}__attribute__;
	//
	//void error_quit(const char *msg)
	//{
	//	perror(msg);
	//	exit(-1);
	//}
	//
	//void memcat(char *tmp, char *buf, unsigned long len)
	//{
	//	int i = 2, j = 0;
	//
	//	while (len)
	//	{
	//		tmp[i] = buf[j];
	//
	//		++i;
	//		++j;
	//		--len;
	//	}
	//}
	//
	//int get_zip_file_num(char *zip_file)
	//{
	//	int i = 0;
	//	FILE *fp;
	//	struct data zip;
	//
	//	if ((fp = fopen(zip_file, "rb")) == NULL)
	//		return -1;
	//
	//	while (!feof(fp))
	//	{
	//		fread(&zip, sizeof(struct data), 1, fp);
	//		if (zip.f_len <= 0)
	//			break;
	//		fseek(fp, zip.f_len, SEEK_CUR);
	//
	//		if (zip.e_len > 0)
	//			fseek(fp, zip.e_len, SEEK_CUR);
	//
	//		if (zip.d_len > 0)
	//			fseek(fp, zip.d_len, SEEK_CUR);
	//
	//		++i;
	//	}
	//
	//	fclose(fp);
	//
	//	return i;
	//}

//char SourceBuffer[102400] = { 0 };  //ѹ���ļ�ʱ��Դbuffer

//FILE* fp;  //����ѹ���ļ�ʱ�ļ���ָ��
//FILE* fp1;  //����ѹ���ļ�ʱ��ָ��
//errno_t err; //��������Ķ���
//err = fopen_s(&fp, SrcName, "r+b");
////��ȡ�ļ�����
//long cur = ftell(fp);
//fseek(fp, 0L, SEEK_END);
//long fileLength = ftell(fp);
//fseek(fp, cur, SEEK_SET);


////��ȡ�ļ���buffer
//fread(SourceBuffer, fileLength, 1, fp);
//fclose(fp);

////ѹ��buffer�е�����
//uLongf SourceBufferLen = 102400;
//char* DestBuffer = (char*)::calloc((uInt)SourceBufferLen, 1);
//err = compress((Bytef*)DestBuffer, (uLongf*)&SourceBufferLen, (const Bytef*)SourceBuffer, (uLongf)fileLength);
//if (err != Z_OK)
//{
//	cout << "ѹ��ʧ�ܣ�" << err << endl;
//	return 1;
//}

////����һ���ļ�����д��ѹ���������
//err = fopen_s(&fp1, DestName, "w+b");
//if (!fp1)
//{
//	printf("ѹ���ļ�����ʧ��! \n");
//	return 1;
//}

//fwrite(DestBuffer, SourceBufferLen, 1, fp1);
//cout << "ѹ������" << endl;
//fclose(fp1);
//return 0;