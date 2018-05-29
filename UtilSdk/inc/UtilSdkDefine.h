#ifndef __MVOPEDEFINE_H
#define __MVOPEDEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

const string filedir = "files/";//can�������������Լ�g_setting.bin������ļ���
const string picdir = "pic/";

enum  INFOTYPE_E
{
	CUSTOMER_INFO = 0,//��Ӧ�ṹ��tagCustomerInfo
	VENDOR_INFO	=	1,//��Ӧ���Һͳ�����Ϣ
	UPLOAD_FILE =	2,//�ϴ��ļ�
	CANLIB_INFO	=	3,//canlib��Ϣ
	UPDATE_DBRECORD = 4,//���µ����ݿ�
};

typedef struct tagCustomerInfo//�û���Ϣ
{
	std::string		sCustomName;
	std::string		sCustomAddress;
}CustomerInfo,*pCustomerInfo;

typedef struct tagVencleInfo//������Ϣ
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

typedef struct tagVendorInfo//������Ϣ
{
	std::string	 sVendorName;
	std::string	 sAddress;
	std::string  sContract_person;
	std::string  sContract_type;
	std::string	 sId;
	std::string  sRemark;
	std::string  sState;
}VendorInfo,*pVendorInfo;

//˵������������һ��vendorid,�����vendorInfo�е�sId�Ƕ�Ӧ�ģ�ͨ����������������ͳ��͵Ķ�Ӧ��ϵ
typedef struct tagVenVec 
{
	std::string		sName;//name�����ֵ��û�ж������
	std::vector<VendorInfo>	vecVendors;
	std::vector<VencleInfo>  vecVencles;
}VenVec,*pVenVec;

typedef struct tagCanlibInfo//canlib���
{
	std::string		sDesc;
	std::string		sId;//�ļ���id����
	std::string		sFileUrl;//�ļ������ص�ַ
	std::string		sName;//�ļ�������
	std::string		sVencleId;//��Ӧ�ĳ����ͺ�
	std::string		sVendorId;//��Ӧ�ĳ���
}CanlibInfo,*pCanlibInfo;

typedef struct tagCanlibs
{
	std::vector<CanlibInfo>	 vecCanlib;//canlib�복����Ϣ���б�
}Canlibs,*pCanlibs;

typedef struct tagDBRecord//�ύ�����ݿ����Ϣ
{
	std::string  sSerialno;//���кţ��豸�����к�
	std::string  sCurVersion;//��ǰ�汾
	std::string	 sUsrCorp;//user_corp
	std::string	 sInstallLocation;//install_location
	std::string  sContract_type;//��ϵ����
	std::string	 sVencleId;//����id
	std::string  sPer_version;//per_version
	std::string	 sPhotoId;
	std::string  sUpgradeType;//��������
	std::string  sWiring_info;
	std::string  sVendorId;//����Id
}DBRecord,*pDBRecord;
#endif