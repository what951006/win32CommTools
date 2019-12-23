// AdoRecordset.h: interface for the CAdoRecordset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADORECORDSET_H__CC43A2BE_A414_47A0_93B3_FB963C38DABA__INCLUDED_)
#define AFX_ADORECORDSET_H__CC43A2BE_A414_47A0_93B3_FB963C38DABA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAdoRecordset  
{
public:
	CAdoRecordset();
	virtual ~CAdoRecordset();
	//�򿪱�
	BOOL OpenTable(const std::string &strTable,CAdoDatabase* pDatabase);
	//��ȡ�����ֶ�(��)������
	UINT GetFieldsCount();
	//��ȡ�����ֶε�����
	std::string  GetFieldName(LONG nIndex);
	//��ȡ�ֶε�ֵ
	BOOL GetValue(LONG nIndex, std::string  & strValue);
	BOOL GetValue(const std::string & nIndex, std::string  & strValue);
	BOOL GetValue(LONG nIndex,int & intValue);
	BOOL GetValue(const std::string & nIndex,int & intValue);
	//�����ֶε�ֵ
	BOOL SetValue(LONG nIndex, const std::string & strValue);
	BOOL SetValue(const char* nIndex, const std::string & strValue);
	BOOL SetValue(LONG nIndex,int intValue);
	BOOL SetValue(const char* nIndex,int intValue);
	//�α����
	void Move(LONG nIndex);
	void MoveNext();
	void MovePrevious();
	void MoveFirst();
	void MoveLast();
	//�ж��Ƿ����һ����¼
	BOOL IsEOF();
	//�������
	void AddNew();
	//���µ����ݿ�
	void Update();
	//ɾ����¼
	void Delete();
	BOOL DeleteAll();
	//ִ��sql���
	BOOL OpenSql(const std::string & strSql,CAdoDatabase* pDatabse);
//���ö���������
	BOOL SetBinaryValue(const char * nIndex,BYTE* pData,ULONG nLen);
	BOOL SetBinaryValue(LONG nIndex,BYTE* pData,ULONG nLen);
	//��ȡ����������
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

#endif // !defined(AFX_ADORECORDSET_H__CC43A2BE_A414_47A0_93B3_FB963C38DABA__INCLUDED_)
