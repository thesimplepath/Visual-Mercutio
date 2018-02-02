// ZBCriptedFileApplicationTypeInfo.cpp: implementation of the ZBCriptedFileApplicationTypeInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBCriptedFileApplicationTypeInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const size_t ApplicationTypeIndexFile = 5;
const size_t ProductKeyIndexFile = 7;

const char	 InvalidNoProductKey[] = "xp0?ws5";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBCriptedFileApplicationTypeInfo::ZBCriptedFileApplicationTypeInfo(const CString Filename /*= ""*/)
: ZBCriptedFileInfo(Filename), m_ApplicationType(Unknown)
{

}

ZBCriptedFileApplicationTypeInfo::~ZBCriptedFileApplicationTypeInfo()
{

}


BOOL	ZBCriptedFileApplicationTypeInfo::Initialize( const CString Filename )
{
	ZBCriptedFileInfo::SetFilename( Filename );
	return TRUE;
}

BOOL	ZBCriptedFileApplicationTypeInfo::CreateEmpty( const CString Filename )
{
	ZBCriptedFileInfo::CreateEmptyFile( Filename );
	ZBCriptedFileApplicationTypeInfo::WriteApplicationType( ZBCriptedFileApplicationTypeInfo::Unknown );
	ZBCriptedFileApplicationTypeInfo::WriteProductKey( InvalidNoProductKey );
	return !ZBCriptedFileInfo::GetErrorStatus();
}

BOOL	ZBCriptedFileApplicationTypeInfo::CheckProductKey( CString ProductKey )
{
	CString Key = LoadProductKey();
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
		return FALSE;
	return Key == ProductKey;
}


BOOL	ZBCriptedFileApplicationTypeInfo::ReadFileInfo()
{
	ZBCriptedFileInfo::LoadEntityTable();
	return !ZBCriptedFileInfo::GetErrorStatus();
}

BOOL	ZBCriptedFileApplicationTypeInfo::WriteFileInfo()
{
	ZBCriptedFileInfo::WriteEntityTable();
	return !ZBCriptedFileInfo::GetErrorStatus();
}



ZBCriptedFileApplicationTypeInfo::ApplicationInfoType	ZBCriptedFileApplicationTypeInfo::LoadApplicationType()
{
	if (!ReadFileInfo())
		return ZBCriptedFileApplicationTypeInfo::Unknown;
	m_ApplicationType = (ApplicationInfoType)ZBCriptedFileInfo::GetInt( ApplicationTypeIndexFile );
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
		m_ApplicationType = ZBCriptedFileApplicationTypeInfo::Unknown;
	return m_ApplicationType;
}

BOOL ZBCriptedFileApplicationTypeInfo::WriteApplicationType( ZBCriptedFileApplicationTypeInfo::ApplicationInfoType value )
{
	ZBCriptedFileInfo::LoadEntityTable();
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
		return FALSE;
	ZBCriptedFileInfo::SetInt( (int)value, ApplicationTypeIndexFile );
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
		return FALSE;
	if (!WriteFileInfo())
	{
		m_ApplicationType = ZBCriptedFileApplicationTypeInfo::Unknown;
		return FALSE;
	}
	// finally assign the value
	m_ApplicationType = value;
	return TRUE;
}


CString	ZBCriptedFileApplicationTypeInfo::LoadProductKey()
{
	if (!ReadFileInfo())
		return m_ProductKey = InvalidNoProductKey;
	m_ProductKey = ZBCriptedFileInfo::GetString( ProductKeyIndexFile );
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
		m_ProductKey = InvalidNoProductKey;
	return m_ProductKey;
}

BOOL	ZBCriptedFileApplicationTypeInfo::WriteProductKey( CString value )
{
	ZBCriptedFileInfo::LoadEntityTable();
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
	{
		m_ProductKey = InvalidNoProductKey;
		return FALSE;
	}
	ZBCriptedFileInfo::SetString( value, ProductKeyIndexFile );
	if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
		return FALSE;
	if (!WriteFileInfo())
	{
		m_ProductKey = InvalidNoProductKey;
		return FALSE;
	}
	// finally assign the value
	m_ProductKey = value;
	return TRUE;
}

