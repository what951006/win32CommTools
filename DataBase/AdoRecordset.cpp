// AdoRecordset.cpp: implementation of the CAdoRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "../DS0304.h" //当前工程头文件
#include "AdoRecordset.h"
#include <comutil.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoRecordset::CAdoRecordset()
{

}

CAdoRecordset::~CAdoRecordset()
{

}
BOOL CAdoRecordset::OpenTable(const std::string & strTable,
											CAdoDatabase* pDatabase)
{
	//创建Recordset对象
	HRESULT nRet=m_pRecordset.CreateInstance(__uuidof(Recordset));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	//打开表
	m_pRecordset->Open(_variant_t(strTable.c_str()),
		(IDispatch*)pDatabase->m_pConn,
		adOpenKeyset,adLockOptimistic,adCmdTable);
	if (FAILED(nRet))
	{
		m_pRecordset.Release();
		return FALSE;
	}
	return TRUE;
}
UINT CAdoRecordset::GetFieldsCount()
{
	if (m_pRecordset)
	{
		return m_pRecordset->Fields->GetCount();
	}
	return 0;
}
std::string CAdoRecordset::GetFieldName(LONG nIndex)
{
	if (m_pRecordset)
	{
		std::string strName="";
		strName=(_bstr_t)
			m_pRecordset->Fields->GetItem(_variant_t(nIndex))->GetName();
		return strName;
	}
	return "";
}
BOOL CAdoRecordset::SetValue(const char* nIndex, const std::string &  strValue)
{
	if(strValue.empty()) return FALSE;
	if (m_pRecordset)
	{
		m_pRecordset->Fields->GetItem(nIndex)->Value
			=_bstr_t(strValue.c_str());
		return TRUE;
	}
	return FALSE;
}
BOOL CAdoRecordset::SetValue(const char* nIndex,int intValue)
{
	_ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			m_pRecordset->put_Collect(_variant_t(nIndex), _variant_t(long(intValue)));
			return TRUE;
		}
	}
	catch (_com_error e)
	{
		return FALSE;
	} 
	return	FALSE;
}
BOOL CAdoRecordset::SetValue(LONG nIndex, const std::string &  strValue)
{
	if (m_pRecordset)
	{
    m_pRecordset->Fields->GetItem(nIndex)->Value
			=_bstr_t(strValue.c_str());
		return TRUE;
	}
	return FALSE;
}
BOOL CAdoRecordset::GetValue(LONG nIndex, std::string  & strValue)
{
  if(m_pRecordset)
	{
		//获取字段的值
		_variant_t varValue=
			m_pRecordset->Fields->GetItem(nIndex)->Value;
		
    if (varValue.vt!=VT_NULL)//判断是否为空
    {
			//该值不为空，将_variant_t转换成CString类型
			strValue=(_bstr_t)varValue;
			 return TRUE;
    }
	}
	return FALSE;
}
BOOL CAdoRecordset::GetValue(const std::string &  nIndex, std::string &  strValue)
{
	if(m_pRecordset)
	{
		//获取字段的值
		_variant_t varValue=
			m_pRecordset->Fields->GetItem(nIndex.c_str())->Value;
		
		if (varValue.vt!=VT_NULL)//判断是否为空
		{
			//该值不为空，将_variant_t转换成CString类型
			strValue=(_bstr_t)varValue;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAdoRecordset::GetValue(const std::string &  nIndex,int & intValue)
{
	if(m_pRecordset)
	{
		//获取字段的值
		_variant_t varValue=
			m_pRecordset->Fields->GetItem(nIndex.c_str())->Value;
		
		if (varValue.vt!=VT_NULL)//判断是否为空
		{
			//该值不为空，将_variant_t转换成CString类型
			intValue=(int)vartol(varValue);
			return TRUE;
		}
	}
	return FALSE;
}

void CAdoRecordset::Move(LONG nIndex)
{
	if (m_pRecordset)
	{
		m_pRecordset->Move(nIndex,
			_variant_t((LONG)adBookmarkFirst));
	}
}
void CAdoRecordset::MoveFirst()
{
	if (m_pRecordset)
	{
		if(!m_pRecordset->BOF)//数据库中存在数据
		{
	     m_pRecordset->MoveFirst();
		}
	
	}
}
void CAdoRecordset::MoveLast()
{
	if (m_pRecordset)
	{
		m_pRecordset->MoveLast();
	}
}
void CAdoRecordset::MoveNext()
{
	if (m_pRecordset)
	{
		m_pRecordset->MoveNext();
	}
}
void CAdoRecordset::MovePrevious()
{
	if (m_pRecordset)
	{
		m_pRecordset->MovePrevious();
	}
}
BOOL CAdoRecordset::IsEOF()
{
	if (m_pRecordset)
	{
		//return m_pRecordset->End3EOF;
		return m_pRecordset->EndEOF;
	}
	return FALSE;
}
void CAdoRecordset::AddNew()
{
	if (m_pRecordset)
	{
		m_pRecordset->AddNew();
	}
}
void CAdoRecordset::Update()
{
	if (m_pRecordset)
	{
		m_pRecordset->Update();
	}
}
void CAdoRecordset::Delete()
{
	if (m_pRecordset)
	{
		m_pRecordset->Delete(adAffectCurrent);
	}
}
BOOL CAdoRecordset::DeleteAll()
{
	_ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			return (m_pRecordset->Delete(adAffectGroup) == S_OK);
		}
	}
	catch (_com_error e)
	{
		return FALSE;
	} 
	return	FALSE;
}
BOOL CAdoRecordset::OpenSql(const std::string& strSql,CAdoDatabase* pDatabse)
{
	//创建Recordset对象
	HRESULT nRet=m_pRecordset.CreateInstance(__uuidof(Recordset));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	//打开表
	m_pRecordset->Open(_variant_t(strSql.c_str()),
		(IDispatch*)pDatabse->m_pConn,
		adOpenKeyset,adLockOptimistic,adCmdText);
	if (FAILED(nRet))
	{
		m_pRecordset.Release();
		return FALSE;
	}
	return TRUE;

}
BOOL CAdoRecordset::SetBinaryValue(LONG nIndex,BYTE* pData,ULONG nLen)
{
	//创建SAFEARRAY数组，接收需要保存的二进制数据
	SAFEARRAYBOUND bound={0};
	bound.cElements=nLen;
	bound.lLbound=0;
	SAFEARRAY* pArray=SafeArrayCreate(
		VT_UI1,1,&bound);
	//将数据首先保存到安全数据中
	for (LONG i=0;i<(LONG)nLen;i++)
	{
		SafeArrayPutElement(pArray,&i,pData+i);
	}
	//构造参数，将安全数组构造为VARIANT类型
  VARIANT varChunk={0};
	varChunk.vt=VT_ARRAY|VT_UI1;
	varChunk.parray=pArray;
	//把数据保存到数据库中
	m_pRecordset->Fields->GetItem(nIndex)->AppendChunk(&varChunk);
	//删除数组
	SafeArrayDestroy(pArray);
	return TRUE;
}
BOOL CAdoRecordset::SetBinaryValue(const char* nIndex,BYTE* pData,ULONG nLen)
{
	//创建SAFEARRAY数组，接收需要保存的二进制数据
	SAFEARRAYBOUND bound={0};
	bound.cElements=nLen;
	bound.lLbound=0;
	SAFEARRAY* pArray=SafeArrayCreate(
		VT_UI1,1,&bound);
	//将数据首先保存到安全数据中
	for (LONG i=0;i<(LONG)nLen;i++)
	{
		SafeArrayPutElement(pArray,&i,pData+i);
	}
	//构造参数，将安全数组构造为VARIANT类型
	VARIANT varChunk={0};
	varChunk.vt=VT_ARRAY|VT_UI1;
	varChunk.parray=pArray;
	//把数据保存到数据库中
	m_pRecordset->Fields->GetItem(nIndex)->AppendChunk(&varChunk);
	//删除数组
	SafeArrayDestroy(pArray);
	return TRUE;
}
BOOL CAdoRecordset::GetBinaryValue(LONG nIndex, BYTE* pData,ULONG & nLen)
{
   //获取字段的数据长度
	 ULONG nActualSize=
		 m_pRecordset->Fields->GetItem(nIndex)->ActualSize;
	 //如果pData为NULL，表示调用者要获取数据的长度
	 if (pData==NULL)
	 {
      nLen=nActualSize;
			return TRUE;
	 }
	 //第二次调用时，pData不为NULL
	 //BUFF空间不足
	 if (nLen<nActualSize)
	 {
        nLen=nActualSize;
				return FALSE;
	 }
	 //从数据库中获取数据保存到varValue变量中
	 _variant_t varValue=
		 m_pRecordset->Fields->GetItem(nIndex)->GetChunk(nActualSize);
   //从varValue变量中取出数据保存到pData指向的内存空间中
	 for (LONG i=0;i<(LONG)nLen;i++)
	 {
		 SafeArrayGetElement(varValue.parray,&i,pData+i);
	 }
	 return TRUE;
}
BOOL CAdoRecordset::GetBinaryValue(const char* nIndex, BYTE* pData,ULONG & nLen)
{
	//获取字段的数据长度
	ULONG nActualSize=
		m_pRecordset->Fields->GetItem(nIndex)->ActualSize;
	//如果pData为NULL，表示调用者要获取数据的长度
	if (pData==NULL)
	{
		nLen=nActualSize;
		return TRUE;
	}
	//第二次调用时，pData不为NULL
	//BUFF空间不足
	if (nLen<nActualSize)
	{
        nLen=nActualSize;
		return FALSE;
	}
	//从数据库中获取数据保存到varValue变量中
	_variant_t varValue=
		m_pRecordset->Fields->GetItem(nIndex)->GetChunk(nActualSize);
	//从varValue变量中取出数据保存到pData指向的内存空间中
	for (LONG i=0;i<(LONG)nLen;i++)
	{
		SafeArrayGetElement(varValue.parray,&i,pData+i);
	}
	return TRUE;
}

int CAdoRecordset::GetMaxID()
{
	long pos = GetAbsolutePosition();
	MoveLast();
	int id;
	GetValue("ID",id);
	SetAbsolutePosition(pos);
	return id;
}

long CAdoRecordset::GetRecordCount()
{
	_ASSERT(m_pRecordset != NULL);
	try
	{
		long count = m_pRecordset->GetRecordCount();
		
		// 如果ado不支持此属性，则手工计算记录数目 --------
		if (count < 0)
		{
			long pos = GetAbsolutePosition();
			MoveFirst();
			count = 0;
			while (!IsEOF()) 
			{
				count++;
				MoveNext();
			}
			SetAbsolutePosition(pos);
		}
		return count;
	}
	catch (_com_error e)
	{
		return -1;
	} 
}

long CAdoRecordset::GetAbsolutePosition()
{
	_ASSERT(m_pRecordset != NULL);
	
	try
	{
		return m_pRecordset->GetAbsolutePosition();
	}
	catch(...)
	{
		return -1;
	}
}

long CAdoRecordset::SetAbsolutePosition(int nPosition)
{
	_ASSERT(m_pRecordset != NULL);
	
	try
	{
		m_pRecordset->PutAbsolutePosition((enum PositionEnum)nPosition);		
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

long CAdoRecordset::vartol(const _variant_t &var)
{
	long value = 0;
	switch (var.vt)
	{
	case VT_BOOL:
		value = var.boolVal;
		break;
	case VT_UI1:
	case VT_I1:
		value = var.bVal;
		break;
	case VT_UI2:
	case VT_I2:
		value = var.iVal;
		break;
	case VT_I4:
	case VT_UI4:
		value = var.lVal;
		break;
	case VT_INT:
		value = var.intVal;
		break;
	case VT_R4:
		value = (long)(var.fltVal + 0.5);
		break;
	case VT_R8:
		value = (long)(var.dblVal + 0.5);
		break;
	case VT_DECIMAL:
		value = (long)var;
		break;
	case VT_CY:
		value = (long)var;
		break;
	case VT_BSTR://字符串
	case VT_LPSTR://字符串
	case VT_LPWSTR://字符串
		value = atol((_bstr_t)var);
		break;
	case VT_NULL:
	case VT_EMPTY:
		value = 0;
		break;
	default:
		//TRACE(_T("Warning: not done the  _variant_t type of value; file: %s; rows: %d\n"), __FILE__, __LINE__);
		;
	}
	return value;
}
