// AdoCommand.cpp: implementation of the CAdoCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "../DS0304.h" //当前工程头文件
#include "AdoCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoCommand::CAdoCommand()
{

}

CAdoCommand::~CAdoCommand()
{

}
BOOL CAdoCommand::OpenSql(const std::string & strSql, CAdoDatabase* pSet)
{
	//创建Command对象
	HRESULT nRet=m_pCmd.CreateInstance(__uuidof(Command));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	//设置连接
	m_pCmd->ActiveConnection=pSet->m_pConn;
	//设置sql语句
	m_pCmd->CommandText=_bstr_t(strSql.c_str());
	//执行sql语句
	m_pCmd->Execute(NULL,NULL,adCmdText|adExecuteNoRecords);
	return TRUE;
}
