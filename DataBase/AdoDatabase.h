// AdoDatabase.h: interface for the CAdoDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADODATABASE_H__97BB3F74_FD4D_4C57_A7B9_A268F4118D3E__INCLUDED_)
#define AFX_ADODATABASE_H__97BB3F74_FD4D_4C57_A7B9_A268F4118D3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
#include <string>
#include <comutil.h>

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

#endif // !defined(AFX_ADODATABASE_H__97BB3F74_FD4D_4C57_A7B9_A268F4118D3E__INCLUDED_)
