#ifndef __UTILSDK_H
#define __UTILSDK_H

#ifdef UTILSDK_EXPORTS
#define UTILSDK_API __declspec(dllexport)
#else
#define UTILSDK_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>
#define CALLBACK	__stdcall
extern "C"
{
	extern UTILSDK_API int nUtilSdk;

	UTILSDK_API int fnUtilSdk(void);

	UTILSDK_API	void*	UTILSDK_Init(void);
	UTILSDK_API	void	UTILSDK_Uninit(void* pHandle);
	UTILSDK_API int		UTILSDK_ZipFile(const char * DestName, const char *SrcName, int para=0);
	UTILSDK_API int		UTILSDK_UnzipFile(const char * DestName, const char *SrcName, int para=0);
}
#endif // !__UTILSDK_H