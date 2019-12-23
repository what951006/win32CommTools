#include "AdoCommand.h"
#include "AdoDatabase.h"


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
