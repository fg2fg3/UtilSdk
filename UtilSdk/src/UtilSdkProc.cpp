#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const	std::string  httpHead = "http://";
const	std::string	 httpsHead = "https://";

CMvOpeProc::CMvOpeProc()
{
	m_sSessionId = "";
	m_sWebAddr = "";
	m_sWebPort = "";
	m_sCaPath = "";
	m_sKeyPath = "";
	m_pHttpClient = new HttpClient;
	return;
}

CMvOpeProc::~CMvOpeProc()
{
	if (m_pHttpClient != NULL)
	{
		delete m_pHttpClient;
		m_pHttpClient = nullptr;
	}
}

void CMvOpeProc::SetWebServer(std::string sWebAddr, std::string sWebPort, std::string sCaPath, std::string sKeyPath)
{
	m_sWebAddr = sWebAddr;
	m_sWebPort = sWebPort;
	m_sCaPath = sCaPath;
	m_sKeyPath = sKeyPath;
	m_sUrlHead = httpsHead + m_sWebAddr + ":" + m_sWebPort + "/";
}

int	CMvOpeProc::HttpsGet(std::string &url, std::string &responce, const char* pCaPath, const char* pKeyPath)
{
	if (m_pHttpClient != nullptr)
	{
		return m_pHttpClient->Gets(url, responce,pCaPath,pKeyPath);
	}
	return -1;
}


int	CMvOpeProc::GetParseResult(int  nInfoType, std::string &src, void*	dest)
{
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value root;

	int ret = 0;
	//从字符串中读取数据
	string result = "";
	JSONCPP_STRING errs;
	if (reader->parse(src.c_str(), src.c_str() + src.size(), &root, &errs))
	{
		switch (nInfoType)
		{
		case CUSTOMER_INFO:
		{
			CustomerInfo*	cus = (CustomerInfo*)dest;
			cus->sCustomName = root["customname"].asString();
			cus->sCustomAddress = root["customaddress"].asString();
			break;
		}
		case VENDOR_INFO:
		{
			VenVec*	v = (VenVec*)dest;
			std::vector<VendorInfo> vecVendor;
			v->vecVendors = vecVendor;
			std::vector<VencleInfo> vecVencle;
			v->vecVencles = vecVencle;

			Json::Value res = root["response"];
			//std::cout << res << std::endl;
			Json::Value::Members resMem = res.getMemberNames();
			for (auto it2 = resMem.begin(); it2 != resMem.end();it2++)
			{
				std::cout << *it2 << std::endl;
				VendorInfo vi;
				std::string name = *it2;
				vi.sVendorName = name;
				//std::cout << vi.sVendorName << std::endl;
				Json::Value vvi = res[name];
				Json::Value vvvi = vvi["ve"];
				std::cout << vvvi << std::endl;
				vi.sAddress = vvvi["address"].asString();
				vi.sContract_person = vvvi["contract_person"].asString();
				vi.sContract_type = vvvi["contract_type"].asString();
				vi.sId = vvvi["id"].asString();
				vi.sRemark = vvvi["remark"].asString();
				vi.sState = vvvi["state"].asString();
				v->vecVendors.push_back(vi);

				Json::Value ven = vvi["vehs"];
				std::cout << ven << std::endl;
				int size = ven.size();
				for (int i = 0; i < size;i++)
				{
					Json::Value temp = ven[i];
					//cout << temp << endl;
					VencleInfo  venc;
					venc.sVendorName = name;
					venc.sDesc = temp["desc"].asString();
					venc.sId = temp["id"].asString();
					venc.sName = temp["name"].asString();
					venc.sOpt_time = temp["opt_time"].asString();
					venc.sOpt_user = temp["opt_user"].asString();
					venc.sRemarks = temp["remarks"].asString();
					venc.sState = temp["state"].asString();
					venc.sVendorId = temp["vendorid"].asString();
					v->vecVencles.push_back(venc);
				}
			}
			break;
		}
		case CANLIB_INFO:
		{
			Canlibs* cbs = (Canlibs*)dest;
			std::vector<CanlibInfo> vecCanlib;
			cbs->vecCanlib = vecCanlib;

			ret = root["code"].asInt();
			Json::Value res = root["response"];
			std::cout << res << std::endl;
			for (int i = 0; i < res.size();i++)
			{
				Json::Value v = res[i];
				CanlibInfo ci;
				ci.sDesc = v["desc"].asString();
				ci.sFileUrl = v["sofile"].asString();
				ci.sId = v["id"].asString();
				ci.sName = v["name"].asString();
				ci.sVencleId = v["vehicle_id"].asString();
				ci.sVendorId = v["vendor_id"].asString();
				cbs->vecCanlib.push_back(ci);
			}
			break;
		}
		case UPDATE_DBRECORD:
		{
			ret = root["code"].asInt();
			break;
		}
		default:
			break;
		}
	}
	return ret;
}

//上传文件
int CMvOpeProc::UploadFile(std::string &url, std::string &filename, std::string &filepath,std::string &sFileId)
{
	if (m_pHttpClient != nullptr)
	{	
		std::string sRes = "";
		int ret = m_pHttpClient->UploadFile(url, filename, filepath, sRes);
		if (ret == 0)
		{
			Json::CharReaderBuilder b;
			Json::CharReader* reader(b.newCharReader());
			Json::Value root;

			//从字符串中读取数据
			string result = "";
			JSONCPP_STRING errs;
			if (reader->parse(sRes.c_str(), sRes.c_str() + sRes.size(), &root, &errs))
			{
				int iCode = root["code"].asInt();
				if (iCode == 1)
				{
					sFileId = root["id"].asString();
				}
			}
		}
		return 0;
	}
	return -1;
}

int  CMvOpeProc::DownloadFile(std::string &url, std::string &filepath)
{
	if (m_pHttpClient != nullptr)
	{
		return m_pHttpClient->DownloadFile(url, filepath);
	}
	return -1;
}

int  CMvOpeProc::PostsData(std::string &url, std::string &sPost, std::string &response)
{
	if (m_pHttpClient != nullptr)
	{
		return m_pHttpClient->PostsData(url, sPost, response);
	}
	return -1;
}