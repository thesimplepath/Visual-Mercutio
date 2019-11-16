/****************************************************************************
 * ==> PSS_RegisterSetup ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to create, modify or get a value from a  *
 *               key in the registry                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RegisterSetup.h"

// processsoft
#include "PSS_MsgBox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_RegisterSetup
//---------------------------------------------------------------------------
PSS_RegisterSetup::PSS_RegisterSetup()
{}
//---------------------------------------------------------------------------
PSS_RegisterSetup::~PSS_RegisterSetup()
{}
//---------------------------------------------------------------------------
bool PSS_RegisterSetup::CreateEntry(HKEY           hRoot,
                                    const CString& entityName,
                                    const CString& keyName,
                                    const CString& defaultValue,
                                    bool           silent) const
{
    if (!hRoot)
        hRoot = HKEY_LOCAL_MACHINE;

    HKEY hKey;

    try
    {
        // create a new key in the registry
        const DWORD result = ::RegCreateKeyEx(hRoot,
                                              entityName,
                                              0,
                                              "",
                                              REG_OPTION_NON_VOLATILE,
                                              KEY_WRITE,
                                              NULL,
                                              &hKey,
                                              NULL);

        if (result != ERROR_SUCCESS)
        {
            if (!silent)
                ShowError(result, false);

            return false;
        }
    }
    catch (...)
    {
        if (!silent)
            ShowGenericError();

        return false;
    }

    ::RegCloseKey(hKey);

    // set the default value in the newly created key
    return UpdateRegValue(hRoot, entityName, keyName, defaultValue, silent);
}
//---------------------------------------------------------------------------
bool PSS_RegisterSetup::UpdateRegValue(HKEY           hRoot,
                                       const CString& entityName,
                                       const CString& keyName,
                                       const CString& value,
                                       bool           silent) const
{
    if (!hRoot)
        hRoot = HKEY_LOCAL_MACHINE;

    HKEY hKey = NULL;
    CHAR buffer[100];

    try
    {
        // open the registry key
        DWORD result = ::RegOpenKeyEx(hRoot, entityName, 0, KEY_WRITE, &hKey);

        if (result != ERROR_SUCCESS)
        {
            if (!silent)
                ShowError(result, false);

            return false;
        }

        // copy the value to set
        std::strcpy(buffer, value);

        // set the value in the registry key
        result = ::RegSetValueEx(hKey, keyName, 0, REG_EXPAND_SZ, LPBYTE(buffer), std::strlen(buffer) + 1);

        // the key will no longer be used, close it
        ::RegCloseKey(hKey);
        hKey = NULL;

        if (result != ERROR_SUCCESS)
        {
            if (!silent)
                ShowError(result, false);

            return false;
        }
    }
    catch (...)
    {
        if (hKey)
            ::RegCloseKey(hKey);

        if (!silent)
            ShowGenericError();

        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_RegisterSetup::GetRegValue(HKEY           hRoot,
                                    const CString& entityName,
                                    const CString& keyName,
                                    CString&       value,
                                    bool           createEntry,
                                    bool           silent) const
{
    if (!hRoot)
        hRoot = HKEY_LOCAL_MACHINE;

    HKEY hKey = NULL;

    try
    {
        // open the registry key
        DWORD result = ::RegOpenKeyEx(hRoot, entityName, 0, KEY_READ, &hKey);

        if (result != ERROR_SUCCESS)
            // do create a new entry if not exists?
            if (createEntry && (result == ERROR_FILE_NOT_FOUND || result == ERROR_PATH_NOT_FOUND))
                // create a new key entry
                return CreateEntry(hRoot, entityName, keyName, value, silent);
            else
            {
                if (!silent)
                    ShowError(result, false);

                return false;
            }

        char  buffer[MAX_PATH];
        DWORD read = DWORD(MAX_PATH);

        // get the value
        result = ::RegQueryValueEx(hKey, keyName, 0, NULL, LPBYTE(&buffer), &read);

        // the key will no longer be used, close it
        ::RegCloseKey(hKey);
        hKey = NULL;

        if (result != NO_ERROR)
        {
            if (!silent)
                ShowError(result, false);

            return false;
        }

        value = buffer;
    }
    catch (...)
    {
        if (hKey)
            ::RegCloseKey(hKey);

        if (!silent)
            ShowGenericError();

        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_RegisterSetup::ShowGenericError() const
{
    PSS_MsgBox mBox;
    mBox.Show(_T("Cannot access the Windows registry.\r\n\r\nReceived error:\r\nInternal error."), MB_OK);
}
//---------------------------------------------------------------------------
void PSS_RegisterSetup::ShowError(DWORD errorCode, bool useLocale) const
{
    // select the error message locale to use
    const WORD langID = MAKELANGID(LANG_NEUTRAL, useLocale ? SUBLANG_DEFAULT : SUBLANG_NEUTRAL);

    char* pBuffer = NULL;

    // get the error
    const DWORD count = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                         NULL,
                                         errorCode,
                                         langID,
                                         (char*)&pBuffer,
                                         0,
                                         NULL);

    std::string errMsg;

    if (count > 0)
    {
        if ((count > 2) && pBuffer[count - 2] == L'\r' && pBuffer[count - 1] == L'\n')
            pBuffer[count - 2] = L'\0';

        errMsg = pBuffer;
        ::LocalFree(pBuffer);
    }

    PSS_MsgBox mBox;
    mBox.Show(_T(("Cannot access the Windows registry.\r\n\r\nReceived error:\r\n" + errMsg).c_str()), MB_OK);
}
//---------------------------------------------------------------------------
