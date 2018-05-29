#ifndef __MVOPEDEFINE_H
#define __MVOPEDEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

const string filedir = "files/";//can包和升级包，以及g_setting.bin包存放文件夹
const string picdir = "pic/";

enum  INFOTYPE_E
{
	CUSTOMER_INFO = 0,//对应结构体tagCustomerInfo
	VENDOR_INFO	=	1,//对应厂家和车型信息
	UPLOAD_FILE =	2,//上传文件
	CANLIB_INFO	=	3,//canlib信息
	UPDATE_DBRECORD = 4,//更新到数据库
};

typedef struct tagCustomerInfo//用户信息
{
	std::string		sCustomName;
	std::string		sCustomAddress;
}CustomerInfo,*pCustomerInfo;

typedef struct tagVencleInfo//车辆信息
{
	std::string	 sDesc;
	std::string  sId;
	std::string  sName;
	std::string  sOpt_time;
	std::string  sOpt_user;
	std::string  sRemarks;
	std::string  sState;
	std::string  sVendorId;
	std::string	 sVendorName;
}VencleInfo,*pVencleInfo;

typedef struct tagVendorInfo//车厂信息
{
	std::string	 sVendorName;
	std::string	 sAddress;
	std::string  sContract_person;
	std::string  sContract_type;
	std::string	 sId;
	std::string  sRemark;
	std::string  sState;
}VendorInfo,*pVendorInfo;

//说明：车型中有一个vendorid,这个和vendorInfo中的sId是对应的，通过这个来做到车厂和车型的对应关系
typedef struct tagVenVec 
{
	std::string		sName;//name随便填值，没有多大意义
	std::vector<VendorInfo>	vecVendors;
	std::vector<VencleInfo>  vecVencles;
}VenVec,*pVenVec;

typedef struct tagCanlibInfo//canlib库和
{
	std::string		sDesc;
	std::string		sId;//文件的id号码
	std::string		sFileUrl;//文件的下载地址
	std::string		sName;//文件的名字
	std::string		sVencleId;//适应的车辆型号
	std::string		sVendorId;//适应的车厂
}CanlibInfo,*pCanlibInfo;

typedef struct tagCanlibs
{
	std::vector<CanlibInfo>	 vecCanlib;//canlib与车型信息的列表
}Canlibs,*pCanlibs;

typedef struct tagDBRecord//提交到数据库的信息
{
	std::string  sSerialno;//序列号，设备的序列号
	std::string  sCurVersion;//当前版本
	std::string	 sUsrCorp;//user_corp
	std::string	 sInstallLocation;//install_location
	std::string  sContract_type;//联系类型
	std::string	 sVencleId;//车型id
	std::string  sPer_version;//per_version
	std::string	 sPhotoId;
	std::string  sUpgradeType;//升级类型
	std::string  sWiring_info;
	std::string  sVendorId;//车辆Id
}DBRecord,*pDBRecord;
#endif