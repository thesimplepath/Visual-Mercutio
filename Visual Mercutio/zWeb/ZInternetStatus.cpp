// ZInternetStatus.cpp: implementation of the ZInternetStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZInternetStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZInternetStatus::ZInternetStatus()
{
}

ZInternetStatus::~ZInternetStatus()
{
}

// JMR-MODIF - Le 26 janvier 2006 - TEMPORAIRE : Erreur inexpliquée avec afxsock, lié à une fonction apparamment
// inutilisée, temporairement désactivée le temps de trouver une réponse.
/*
bool ZInternetStatus::IsConnected()
{
    CSocket    m_Server;
    HKEY    hKey;
    DWORD    dwDial;
    DWORD    dwDialType    = REG_DWORD;
    DWORD    dwDialSize    = 4;
    DWORD    dwNew        = 0;
    bool    bResult        = true;
    int        nCheck        = AfxSocketInit();

    if ( RegOpenKeyEx ( HKEY_CURRENT_USER,
                        _T( "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings" ),
                        0,
                        KEY_SET_VALUE,
                        &hKey ) != ERROR_SUCCESS )
    {
        // We cannot find the key. Handle this situation or just continue
    }

    if ( RegQueryValueEx( hKey,
                          _T( "EnableAutodial" ),
                          NULL,
                          &dwDialType,
                          (BYTE *) &dwDial,
                          &dwDialSize ) != ERROR_SUCCESS )
    {
        // We cannot find the value. Handle it.
    }

    if ( dwDial )
    {
        // We need to change the value, in order to make
        // a dialup window not to show up.

        if ( ( nCheck = RegSetValueEx( hKey,
                                       _T( "EnableAutodial" ),
                                       NULL,
                                       dwDialType,
                                       (BYTE *) &dwNew,
                                       dwDialSize ) ) != ERROR_SUCCESS )
        {
            // Failed? We shouldn't get here. You decide how to handle it
        }
    }

    if ( !m_Server.Create() ) 
    {
        bResult = false;
    }
    // You can use www.microsoft.com in order to check whether DNS is available or numeric IP 207.46.130.150 otherwise.
    else if ( !m_Server.Connect( _T( "www.microsoft.com" ), 80 ) ) 
    {
        m_Server.Close();
        bResult = false;
    }

    if ( dwDial )
    {
        if ( ( nCheck = RegSetValueEx( hKey,
                                       _T( "EnableAutodial" ),
                                       NULL,
                                       dwDialType,
                                       (BYTE *) &dwDial,
                                       dwDialSize ) ) != ERROR_SUCCESS )
        {
            // Failed? We shouldn't get it. You decide how to handle this.
        }
    }

    RegCloseKey( hKey );
    return bResult;
}
*/
