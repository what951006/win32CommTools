#pragma once
#include <windows.h>
#include <string>
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename( "EOF", "EndEOF" )

class CAdoDatabase;
class CAdoRecordset  
{
public:
	CAdoRecordset();
	virtual ~CAdoRecordset();
	//打开表
	BOOL OpenTable(const std::string &strTable,CAdoDatabase* pDatabase);
	//获取表中字段(列)的数量
	UINT GetFieldsCount();
	//获取表中字段的名称
	std::string  GetFieldName(LONG nIndex);
	//获取字段的值
	BOOL GetValue(LONG nIndex, std::string  & strValue);
	BOOL GetValue(const std::string & nIndex, std::string  & strValue);
	BOOL GetValue(LONG nIndex,int & intValue);
	BOOL GetValue(const std::string & nIndex,int & intValue);
	//设置字段的值
	BOOL SetValue(LONG nIndex, const std::string & strValue);
	BOOL SetValue(const char* nIndex, const std::string & strValue);
	BOOL SetValue(LONG nIndex,int intValue);
	BOOL SetValue(const char* nIndex,int intValue);
	//游标操作
	void Move(LONG nIndex);
	void MoveNext();
	void MovePrevious();
	void MoveFirst();
	void MoveLast();
	//判断是否到最后一条记录
	BOOL IsEOF();
	//添加新行
	void AddNew();
	//更新到数据库
	void Update();
	//删除记录
	void Delete();
	BOOL DeleteAll();
	//执行sql语句
	BOOL OpenSql(const std::string & strSql,CAdoDatabase* pDatabse);
//设置二进制数据
	BOOL SetBinaryValue(const char * nIndex,BYTE* pData,ULONG nLen);
	BOOL SetBinaryValue(LONG nIndex,BYTE* pData,ULONG nLen);
	//获取二进制数据
	BOOL GetBinaryValue(LONG nIndex,BYTE* pData,ULONG & nLen);
	BOOL GetBinaryValue(const char * nIndex,BYTE* pData,ULONG & nLen);
public:
	long vartol(const _variant_t& var);
	long SetAbsolutePosition(int nPosition);
	long GetAbsolutePosition();
	long GetRecordCount();
	int GetMaxID();
	_RecordsetPtr m_pRecordset;
};