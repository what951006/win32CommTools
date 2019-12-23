// AdoCommand.cpp: implementation of the CAdoCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "../DS0304.h" //��ǰ����ͷ�ļ�
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
	//����Command����
	HRESULT nRet=m_pCmd.CreateInstance(__uuidof(Command));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	//��������
	m_pCmd->ActiveConnection=pSet->m_pConn;
	//����sql���
	m_pCmd->CommandText=_bstr_t(strSql.c_str());
	//ִ��sql���
	m_pCmd->Execute(NULL,NULL,adCmdText|adExecuteNoRecords);
	return TRUE;
}
