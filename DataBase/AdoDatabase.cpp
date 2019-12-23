// AdoDatabase.cpp: implementation of the CAdoDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "../DS0304.h" //当前工程头文件
#include "AdoDatabase.h"
#include <comutil.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoDatabase::CAdoDatabase()
{

}

CAdoDatabase::~CAdoDatabase()
{
    Close();
}
BOOL CAdoDatabase::OpenMDB(const std::string & strPath)
{
	////创建Connection对象
	//HRESULT nRet=m_pConn.CreateInstance(__uuidof(Connection));
 // if (FAILED(nRet))
 // {
	//	return FALSE;
 // }
	////构造连接字符串
 // CString strConn;
 // strConn.Format("Provider=Microsoft.Jet.OLEDB.4.0;"
	//  "Data Source=%s;User ID=;Password=;", strPath);
	////连接数据库
	//nRet=m_pConn->Open(_bstr_t(strConn),"","",0);
	//if (FAILED(nRet))
	//{
 //     m_pConn.Release();
	//		return FALSE;
	//}
	return TRUE;
}
BOOL CAdoDatabase::OpenMSSQL(const std::string &  strConn)
{
	HRESULT hr;	
	try
	{
		hr=m_pConn.CreateInstance("ADODB.Connection");
		if(SUCCEEDED(hr))
		{
			m_pConn->ConnectionTimeout=3;
			m_pConn->Open(_bstr_t(strConn.c_str()),"","",adModeUnknown);
		}
	}	
	catch(_com_error e)
	{
		::MessageBox(NULL, e.ErrorMessage(),L"Error",NULL);
		return false;
	}
	return TRUE;
}

void CAdoDatabase::Close()
{
	if (m_pConn)
	{
		m_pConn->Close();
	}
}
BOOL CAdoDatabase::OpenSql(const std::string &   strSql)
{
	if (m_pConn)
	{
		HRESULT nRet=m_pConn->Execute(_bstr_t(strSql.c_str()),
			NULL,adCmdText|adExecuteNoRecords);
		if (SUCCEEDED(nRet))
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CAdoDatabase::BeginTrans()
{
	if (m_pConn)
	{
		if (SUCCEEDED(m_pConn->BeginTrans()))
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CAdoDatabase::EndTrans(BOOL bCommit/* =TRUE */)
{
	if (m_pConn)
	{
		HRESULT nRet=S_OK;
		if (bCommit)
		{
			nRet=m_pConn->CommitTrans();
		}
		else
		{
			nRet=m_pConn->RollbackTrans();
		}
		if (SUCCEEDED(nRet))
		{
			return TRUE;
		}
	}
	return FALSE;
}