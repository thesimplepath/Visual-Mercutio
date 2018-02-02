// ZBRegisterSetup.cpp: implementation of the ZBRegisterSetup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBRegisterSetup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBRegisterSetup::ZBRegisterSetup()
{
}

ZBRegisterSetup::~ZBRegisterSetup()
{

}

bool ZBRegisterSetup::CreateEntry( const CString EntityName, const CString KeyName, const CString DefaultValue /*=""*/)
{
	HKEY	hkResult; 

	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, EntityName, 0, "", REG_OPTION_NON_VOLATILE,
						KEY_WRITE, NULL, &hkResult, NULL) != ERROR_SUCCESS)
	{
		AfxMessageBox ("Can not access Registers Base", MB_OK);
		return false;
	}
	RegCloseKey(hkResult);

	CHAR	szBuf[100]; 
	
	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE, EntityName,0, KEY_WRITE, &hkResult) != ERROR_SUCCESS)
	{
		return false;
	}
	strcpy(szBuf, DefaultValue);
	RegSetValueEx(hkResult, KeyName, 0, REG_EXPAND_SZ, (LPBYTE)szBuf, strlen(szBuf)+1);
	
	RegCloseKey(hkResult);
	return true;
}

bool ZBRegisterSetup::UpdateRegValue( const CString EntityName, const CString KeyName, const CString Value )
{
	HKEY	phkResult;
	CHAR	szBuf[100]; 
	
	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE, EntityName,0, KEY_WRITE, &phkResult) != ERROR_SUCCESS)
	{
		return false;
	}
	
	strcpy(szBuf, Value);
	RegSetValueEx(phkResult, KeyName, 0, REG_EXPAND_SZ, (LPBYTE)szBuf, strlen(szBuf)+1);
	
	RegCloseKey(phkResult);
	return true;
}

bool ZBRegisterSetup::GetRegValue( const CString EntityName, const CString KeyName, CString& Value, bool bCreateEntry /*= false*/ )
{
	char			szBuf[MAX_PATH];
	HKEY			phkResult;
	DWORD			dwRead;
	
	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE, EntityName,0, KEY_READ, &phkResult) != ERROR_SUCCESS)
	{
		if (bCreateEntry)
		{
			if (CreateEntry(EntityName, KeyName, Value) != 0)
			{
				AfxMessageBox ("Can not access Registers Base", MB_OK);
				return false;
			}
			else 
				return true;
		}
		else
			return false;
	}
	
	dwRead = DWORD(MAX_PATH);
	if (RegQueryValueEx(phkResult, KeyName, 0, NULL, (LPBYTE) &szBuf, &dwRead)==NO_ERROR)					
		if (szBuf) 
			Value = szBuf;

	return true;
}
