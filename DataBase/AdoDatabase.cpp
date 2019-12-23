#include "AdoDatabase.h"
#include <comutil.h>



CAdoDatabase::CAdoDatabase()
{

}

CAdoDatabase::~CAdoDatabase()
{
    Close();
}
BOOL CAdoDatabase::OpenMDB(const std::string & strPath)
{
	HRESULT nRet=m_pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	std::string strConn(1024, 0);
	sprintf_s((char*)strConn.c_str(), strConn.size(), "Provider = Microsoft.Jet.OLEDB.4.0; "
		"Data Source=%s;User ID=;Password=;", strPath.c_str());

	nRet = m_pConn->Open(_bstr_t(strConn.c_str()), "", "", 0);
	if (FAILED(nRet))
	{
		m_pConn.Release();
		return FALSE;
	}
	return TRUE;
}
BOOL CAdoDatabase::OpenMSSQL(const std::string &  strConn)
{
	BOOL result = false;
	HRESULT hr;	
	try
	{
		hr=m_pConn.CreateInstance("ADODB.Connection");
		if(SUCCEEDED(hr))
		{
			m_pConn->ConnectionTimeout=3;
			hr =m_pConn->Open(_bstr_t(strConn.c_str()),"","",adModeUnknown);
			if (SUCCEEDED(hr))
			{
				result = true;
			}
		}
	}	
	catch(_com_error &e)
	{
		// e.ErrorMessage();
		result = false;
	}
	return result;
}

void CAdoDatabase::Close()
{
	if (m_pConn)
	{
		if (m_pConn->GetState() != adStateClosed)
		{
			m_pConn->Close();
		}
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