/****************************************************************************
 * ==> PSS_ModuleVersion ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to works with file version information   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ModuleVersion.h"

//---------------------------------------------------------------------------
// Callbacks
//---------------------------------------------------------------------------
typedef HRESULT(CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO*);
//---------------------------------------------------------------------------
// PSS_ModuleVersion
//---------------------------------------------------------------------------
PSS_ModuleVersion::PSS_ModuleVersion() :
    VS_FIXEDFILEINFO(),
    m_pVersionInfo(NULL)
{}
//---------------------------------------------------------------------------
PSS_ModuleVersion::~PSS_ModuleVersion()
{
    if (m_pVersionInfo)
        delete[] m_pVersionInfo;
}
//---------------------------------------------------------------------------
bool PSS_ModuleVersion::GetFileVersionInfo(LPCTSTR pModuleName)
{
    // Default = ANSI code page
    m_Translation.m_Charset = 1252;
    std::memset((VS_FIXEDFILEINFO*)this, 0, sizeof(VS_FIXEDFILEINFO));

    TCHAR fileName[_MAX_PATH];

    // get module handle
    HMODULE hModule = ::GetModuleHandle(pModuleName);

    if (!hModule && pModuleName)
        return FALSE;

    // get module file name
    DWORD len = ::GetModuleFileName(hModule, fileName, sizeof(fileName) / sizeof(fileName[0]));

    if (len <= 0)
        return FALSE;

    // will always be set to zero
    DWORD dummyHandle;

    // read file version info
    len = ::GetFileVersionInfoSize(fileName, &dummyHandle);

    if (len <= 0)
        return FALSE;

    // allocate version info
    m_pVersionInfo = new BYTE[len];

    if (!::GetFileVersionInfo(fileName, 0, len, m_pVersionInfo))
        return FALSE;

    LPVOID pVersionInfo;
    UINT   infoLen;

    if (!::VerQueryValue(m_pVersionInfo, _T("\\"), &pVersionInfo, &infoLen))
        return FALSE;

    // copy fixed info to myself, which am derived from VS_FIXEDFILEINFO
    *(VS_FIXEDFILEINFO*)this = *(VS_FIXEDFILEINFO*)pVersionInfo;

    // get translation info
    if (::VerQueryValue(m_pVersionInfo, _T("\\VarFileInfo\\Translation"), &pVersionInfo, &infoLen ) && infoLen >= 4)
    {
        m_Translation = *(ITranslation*)pVersionInfo;
        TRACE("code page = %d\n", m_Translation.m_Charset);
    }

    return dwSignature == VS_FFI_SIGNATURE;
}
//---------------------------------------------------------------------------
CString PSS_ModuleVersion::GetValue(LPCTSTR pKeyName)
{
    CString value;

    if (m_pVersionInfo)
    {
        CString query;

        // to get a string value must pass query in the form: "\StringFileInfo\<langID><codepage>\keyname"
        // where <langID><codepage> is the languageID concatenated with the code page, in hex
        query.Format(_T("\\StringFileInfo\\%04x%04x\\%s"), m_Translation.m_LangID, m_Translation.m_Charset, pKeyName);

        LPCTSTR pVal;
        UINT    lenVal;

        if (::VerQueryValue(m_pVersionInfo, (LPTSTR)(LPCTSTR)query, (LPVOID*)&pVal, &lenVal))
            value = pVal;
    }

    return value;
}
//---------------------------------------------------------------------------
bool PSS_ModuleVersion::DllGetVersion(LPCTSTR pModulename, DLLVERSIONINFO& dvi)
{
    HINSTANCE hInst = ::LoadLibrary(pModulename);

    if (!hInst)
        return FALSE;

    // must use GetProcAddress because the DLL might not implement DllGetVersion. Depending upon the DLL, the lack
    // of implementation of the function may be a version marker in itself
    DLLGETVERSIONPROC pDllGetVersion = (DLLGETVERSIONPROC)::GetProcAddress(hInst, _T("DllGetVersion"));

    if (!pDllGetVersion)
        return FALSE;

    // clear and set size for Windows
    std::memset(&dvi, 0, sizeof(dvi));
    dvi.cbSize = sizeof(dvi);

    return SUCCEEDED((*pDllGetVersion)(&dvi));
}
//---------------------------------------------------------------------------
