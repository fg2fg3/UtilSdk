#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>

class CMvOpeProc {
public:
	CMvOpeProc(void);
	~CMvOpeProc();


	void SetWebServer(std::string sWebAddr, std::string sWebPort, std::string sCaPath, std::string sKeyPath);
	std::string  GetWebAddr(){ return m_sWebAddr; }
	std::string	 GetWebPort(){ return m_sWebPort; }
	std::string	 GetCertPath(){ return m_sCaPath; }
	std::string	 GetKeyPath(){ return m_sKeyPath; }

	std::string  GetUrlHead(){ return m_sUrlHead; }

	std::string	 GetSessionId(){ return m_sSessionId; }
	void	SetSessionId(std::string &session){ m_sSessionId = session; }

	//std::string	 GetUsrName(){ return m_sUsrName; }
	//void	SetUsrName(std::string &userName){ m_sUsrName = userName; }

	//std::string	 GetPwd(){ return m_sPwd; }
	//void	SetPwd(std::string &)

	//重要
	//获取回复
	int	HttpsGet(std::string &url, std::string &responce, const char* pCaPath = nullptr, const char* pKeyPath = nullptr);
	//分析回复并获取结果
	int	GetParseResult(int  nInfoType, std::string &src, void*	dest);
	//上传文件
	int UploadFile(std::string &url, std::string &filename, std::string &filepath, std::string &sFileId);
	int DownloadFile(std::string &url, std::string &filepath);
	int PostsData(std::string &url, std::string &sPost, std::string &response);
private:
	std::string		m_sWebAddr;
	std::string		m_sWebPort;
	std::string		m_sCaPath;
	std::string		m_sKeyPath;
	std::string		m_sUrlHead;
	std::string		m_sSessionId;
	//std::string		m_sUsrName;
	//std::string		m_sPwd;

};