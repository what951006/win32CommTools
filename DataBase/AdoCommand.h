// AdoCommand.h: interface for the CAdoCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCOMMAND_H__517741FF_24B7_472F_BECA_0D968A1FC7FF__INCLUDED_)
#define AFX_ADOCOMMAND_H__517741FF_24B7_472F_BECA_0D968A1FC7FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
#include <string>


class CAdoCommand  
{
public:
	CAdoCommand();
	virtual ~CAdoCommand();
	BOOL OpenSql(const std::string &strSql,
	CAdoDatabase* pSet);
public:
	_CommandPtr m_pCmd;

};

#endif // !defined(AFX_ADOCOMMAND_H__517741FF_24B7_472F_BECA_0D968A1FC7FF__INCLUDED_)
