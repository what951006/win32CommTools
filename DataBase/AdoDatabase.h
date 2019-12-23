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
	//��mdb���ݿ�
	BOOL OpenMDB(const std::string & strPath);
	BOOL OpenMSSQL(const std::string & strConn);
	//�ر����ݿ�
	void Close();
	//ִ��sql���
	BOOL OpenSql(const std::string &  strSql);
	//������
	BOOL BeginTrans();
	BOOL EndTrans(BOOL bCommit=TRUE);
public:
	_ConnectionPtr m_pConn;

};

#endif // !defined(AFX_ADODATABASE_H__97BB3F74_FD4D_4C57_A7B9_A268F4118D3E__INCLUDED_)
