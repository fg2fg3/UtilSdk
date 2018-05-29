// UTILSDK.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "UtilSdk.h"
#include "UtilSdkProc.h"
#include "zlib/zlib.h"
#include <iostream>

using namespace std;

// 这是导出变量的一个示例
UTILSDK_API int nUtilSdk = 0;

// 这是导出函数的一个示例。
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
	char SourceBuffer[102400] = { 0 };  //压缩文件时的源buffer

	FILE* fp;  //打开欲压缩文件时文件的指针
	FILE* fp1;  //创建压缩文件时的指针
	errno_t err; //错误变量的定义
	err = fopen_s(&fp, SrcName, "r+b");
	//获取文件长度
	long cur = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	long fileLength = ftell(fp);
	fseek(fp, cur, SEEK_SET);


	//读取文件到buffer
	fread(SourceBuffer, fileLength, 1, fp);
	fclose(fp);

	//压缩buffer中的数据
	uLongf SourceBufferLen = 102400;
	char* DestBuffer = (char*)::calloc((uInt)SourceBufferLen, 1);
	err = compress((Bytef*)DestBuffer, (uLongf*)&SourceBufferLen, (const Bytef*)SourceBuffer, (uLongf)fileLength);
	if (err != Z_OK)
	{
		cout << "压缩失败：" << err << endl;
		return 1;
	}

	//创建一个文件用来写入压缩后的数据
	err = fopen_s(&fp1, DestName, "w+b");
	if (!fp1)
	{
		printf("压缩文件创建失败! \n");
		return 1;
	}

	fwrite(DestBuffer, SourceBufferLen, 1, fp1);
	cout << "压缩结束" << endl;
	fclose(fp1);
	return 0;
}

UTILSDK_API int		UTILSDK_UnzipFile(char * DestName, const char *SrcName, int para)
{
	char uSorceBuffer[102400] = { 0 };  //解压缩文件时的源buffer
	FILE* fp3;  //打开欲解压文件的文件指针
	FILE* fp4;  //创建解压文件的文件指针
	errno_t err; //错误变量的定义
	//打开欲解压的文件
	err = fopen_s(&fp3, SrcName, "r+b");
	if (err)
	{
		printf("文件打开失败! \n");
		return 1;
	}

	//获取欲解压文件的大小
	long ucur = ftell(fp3);
	fseek(fp3, 0L, SEEK_END);
	long ufileLength = ftell(fp3);
	fseek(fp3, ucur, SEEK_SET);


	//读取文件到buffer
	fread(uSorceBuffer, ufileLength, 1, fp3);
	fclose(fp3);

	uLongf uDestBufferLen = 1024000;//此处长度需要足够大以容纳解压缩后数据
	char* uDestBuffer = (char*)::calloc((uInt)uDestBufferLen, 1);
	//解压缩buffer中的数据
	/*
	int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
	uncompress 函数将 source 缓冲区的内容解压缩到 dest 缓冲区。
	sourceLen 是 source 缓冲区的大小(以字节计)。注意函数的第二
	个参数 destLen 是传址调用。当调用函数时，destLen 表示 dest
	缓冲区的大小， dest 缓冲区要足以容下解压后的数据。在进行解
	压缩时，需要提前知道被压缩的数据解压出来会有多大。这就要求
	在进行压缩之前，保存原始数据的大小(也就是解压后的数据的大
	小)。这不是 zlib 函数库的功能，需要我们做额外的工作。当函数
	退出后， destLen 是解压出来的数据的实际大小。
	*/
	err = uncompress((Bytef*)uDestBuffer, (uLongf*)&uDestBufferLen, (Bytef*)uSorceBuffer, (uLongf)ufileLength);

	if (err != Z_OK)
	{
		cout << "解压缩失败：" << err << endl;
		return 1;
	}

	//创建一个文件用来写入解压缩后的数据
	err = fopen_s(&fp4, DestName, "wb");
	if (err)
	{
		printf("解压缩文件创建失败! \n");
		return 1;
	}

	//printf("写入数据... \n");
	cout << "解压数据成功！" << endl;

	/*
	size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream );
	这是fwrite的MSDN标准参数表，其中buffer是需要向文件中写入的内容在内存中的首地址指针，
	size是待写入内容的每个元素的字节数，count是要写多少个元素，stream 是文件指针
	*/
	fwrite(uDestBuffer, uDestBufferLen, 1, fp4);
	//cout << uDestBuffer << endl;
	fclose(fp4);
	return 0;
}