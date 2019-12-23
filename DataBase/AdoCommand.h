#pragma once
#include <windows.h>
#include <string>
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename( "EOF", "EndEOF" )

class CAdoDatabase;
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
