/****************************************************************************
 * ==> PSS_InternetStatus --------------------------------------------------*
 ****************************************************************************
 * Description : Internet status helper class                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_InternetStatus.h"

// mfc
#include <AfxSock.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_InternetStatus
//---------------------------------------------------------------------------
PSS_InternetStatus::PSS_InternetStatus()
{}
//---------------------------------------------------------------------------
PSS_InternetStatus::~PSS_InternetStatus()
{}
//---------------------------------------------------------------------------
bool PSS_InternetStatus::IsConnected() const
{
    CSocket server;
    HKEY    hKey;
    DWORD   dial;
    DWORD   dialType   = REG_DWORD;
    DWORD   dialSize   = 4;
    DWORD   newVal     = 0;
    bool    result     = true;
    int     checkCount = AfxSocketInit();

    if (::RegOpenKeyEx(HKEY_CURRENT_USER,
                       _T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"),
                       0,
                       KEY_SET_VALUE,
                       &hKey) != ERROR_SUCCESS)
    {
        // cannot find the key. Handle this situation or just continue
    }

    if (::RegQueryValueEx(hKey,
                          _T("EnableAutodial"),
                          NULL,
                          &dialType,
                          (BYTE*)&dial,
                          &dialSize) != ERROR_SUCCESS)
    {
        // cannot find the value. Handle it
    }

    if (dial)
    {
        // need to change the value, in order to make a dialup window not to show up

        if ((checkCount = ::RegSetValueEx(hKey,
                                          _T("EnableAutodial"),
                                          NULL,
                                          dialType,
                                          (BYTE*)&newVal,
                                          dialSize)) != ERROR_SUCCESS)
        {
            // failed? Shouldn't get here, needs to decide how to handle it
        }
    }

    if (!server.Create()) 
        result = false;
    // can use www.microsoft.com in order to check whether DNS is available, or numeric IP 207.46.130.150 otherwise
    else
    if (!server.Connect(_T("www.microsoft.com"), 80))
    {
        server.Close();
        result = false;
    }

    if (dial)
        if ((checkCount = ::RegSetValueEx(hKey,
                                          _T("EnableAutodial"),
                                          NULL,
                                          dialType,
                                          (BYTE*)&dial,
                                          dialSize)) != ERROR_SUCCESS)
        {
            // failed? Shouldn't get it, needs to decide how to handle this
        }

    RegCloseKey(hKey);

    return result;
}
//---------------------------------------------------------------------------
