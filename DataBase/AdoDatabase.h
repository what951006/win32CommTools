#pragma once
#include <windows.h>
#include <string>
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename( "EOF", "EndEOF" )


class CAdoDatabase  
{
public:
	CAdoDatabase();
	virtual ~CAdoDatabase();
	//打开mdb数据库
	BOOL OpenMDB(const std::string & strPath);
	BOOL OpenMSSQL(const std::string & strConn);
	//关闭数据库
	void Close();
	//执行sql语句
	BOOL OpenSql(const std::string &  strSql);
	//事务处理
	BOOL BeginTrans();
	BOOL EndTrans(BOOL bCommit=TRUE);
public:
	_ConnectionPtr m_pConn;
};