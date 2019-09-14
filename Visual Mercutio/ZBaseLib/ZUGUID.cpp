/****************************************************************************
 * ==> PSS_GUID ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a global unique identifier helper                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZUGUID.h"

// std
#include <string>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const char g_GUIDcheck[] = _T("_:[v0]");
//---------------------------------------------------------------------------
// PSS_GUID
//---------------------------------------------------------------------------
PSS_GUID::PSS_GUID()
{}
//---------------------------------------------------------------------------
PSS_GUID::~PSS_GUID()
{}
//---------------------------------------------------------------------------
CString PSS_GUID::CreateNewGUID()
{
    GUID    guid;
    CString str;
    HRESULT hResult = ::CoCreateGuid(&guid);

    if (hResult == S_OK)
        str.Format(_T("%s%d-%d"), g_GUIDcheck, guid.Data1, guid.Data2);
    else
        str.Empty();

    return str;
}
//---------------------------------------------------------------------------
bool PSS_GUID::GUIDIsValid(const CString& guid)
{
    return (guid.Left(std::strlen(g_GUIDcheck)) == g_GUIDcheck);
}
//---------------------------------------------------------------------------
