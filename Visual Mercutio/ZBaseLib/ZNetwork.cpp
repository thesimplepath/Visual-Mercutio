//## begin module%366D71A502F0.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%366D71A502F0.cm

//## begin module%366D71A502F0.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%366D71A502F0.cp

//## Module: ZNetWork%366D71A502F0; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZNetWork.cpp

//## begin module%366D71A502F0.additionalIncludes preserve=no
//## end module%366D71A502F0.additionalIncludes

//## begin module%366D71A502F0.includes preserve=yes
#include <StdAfx.h>
//## end module%366D71A502F0.includes

// ZNetWork
#include "ZNetWork.h"

//## begin module%366D71A502F0.declarations preserve=no
//## end module%366D71A502F0.declarations

// JMR-MODIF - Le 21 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## begin module%366D71A502F0.additionalDeclarations preserve=yes
HANDLE ZUNetwork::m_hInstMNet[MAX_MNETS] = { NULL };

#ifndef ORD_MNETNETWORKENUM
#define ORD_MNETNETWORKENUM        33
#endif

#ifndef ORD_MNETGETLASTTARGET
#define ORD_MNETGETLASTTARGET    35
#endif

#ifndef ORD_MNETGETNETINFO
#define ORD_MNETGETNETINFO        37
#endif

#ifndef ORD_MNETSETNEXTTARGET
#define ORD_MNETSETNEXTTARGET    38
#endif


#ifndef MNM_NET_PRIMARY                    // This resides in multinet.h from WFW SDK
#define MNM_NET_PRIMARY            0x0001    // Network is primary network (Windows network)
#endif

typedef HANDLE    (WINAPI *LPMNETGETLASTTARGET)    ();
typedef WORD    (WINAPI *LPMNETSETNEXTTARGET)    ( HANDLE        hNetwork );
typedef WORD    (WINAPI *LPMNETNETWORKENUM)        ( HANDLE FAR*    hNetwork );
typedef WORD    (WINAPI *LPMNETGETNETINFO)        ( HANDLE        hNetwork,
                                                  WORD*            lpwNetInfo,
                                                  LPSTR            lpszButton,
                                                  LPINT            lpcbButton,
                                                  HANDLE*        lphInstance );

//## end module%366D71A502F0.additionalDeclarations

// Class ZUNetwork

//## begin ZUNetwork::MNets%366D7A64020A.attr preserve=no  private: static int {V} 0
int ZUNetwork::m_MNets = 0;
//## end ZUNetwork::MNets%366D7A64020A.attr

//## begin ZUNetwork::Primary%366D7A870015.attr preserve=no  private: static HANDLE {V} 0
HANDLE ZUNetwork::m_Primary = 0;
//## end ZUNetwork::Primary%366D7A870015.attr

//## begin ZUNetwork::hInstNetDriver%366D7CF40249.attr preserve=no  private: static HANDLE {V} 0
HANDLE ZUNetwork::m_hInstNetDriver = 0;
//## end ZUNetwork::hInstNetDriver%366D7CF40249.attr

//## begin ZUNetwork::hInstWFWDriver%366D7D0C00DB.attr preserve=no  private: static HANDLE {V} 0
HANDLE ZUNetwork::m_hInstWFWDriver = 0;
//## end ZUNetwork::hInstWFWDriver%366D7D0C00DB.attr

ZUNetwork::ZUNetwork()
    //## begin ZUNetwork::ZUNetwork%.hasinit preserve=no
    //## end ZUNetwork::ZUNetwork%.hasinit
    //## begin ZUNetwork::ZUNetwork%.initialization preserve=yes
    //## end ZUNetwork::ZUNetwork%.initialization
{
    //## begin ZUNetwork::ZUNetwork%.body preserve=yes
    //## end ZUNetwork::ZUNetwork%.body
}

ZUNetwork::~ZUNetwork()
{
    //## begin ZUNetwork::~ZUNetwork%.body preserve=yes
    //## end ZUNetwork::~ZUNetwork%.body
}

//## Other Operations (implementation)
bool ZUNetwork::GetNetworkDrives( CStringArray& DriveArray )
{
    //## begin ZUNetwork::GetNetworkDrives%947664380.body preserve=yes
    char DriveLetter[5];

    for( int iDrive = 0 ; iDrive < 26 ; iDrive++ )
    {
        sprintf( DriveLetter, _T( "%c:" ), _T( 'A' ) + iDrive );

        UINT RetValue = GetDriveType( DriveLetter );

        if ( RetValue != DRIVE_REMOVABLE    &&
             RetValue != DRIVE_FIXED        &&
             RetValue != DRIVE_CDROM        &&
             RetValue != DRIVE_RAMDISK )
        {
            DriveArray.Add( DriveLetter );
        }
    }

    return DriveArray.GetSize() > 0;
    //## end ZUNetwork::GetNetworkDrives%947664380.body
}

bool ZUNetwork::Map( CString UNC, CString Local, bool CanSpecifyUsername )
{
    //## begin ZUNetwork::Map%947664376.body preserve=yes
    DWORD        Result;
    NETRESOURCE    NetResource;

    // Initialize the network resource structure
    NetResource.dwType            = RESOURCETYPE_DISK;
    NetResource.lpLocalName        = ( Local.IsEmpty() ) ? NULL : Local.GetBuffer( Local.GetLength() );
    NetResource.lpRemoteName    = UNC.GetBuffer( UNC.GetLength() );
    NetResource.lpProvider        = NULL;

    Result = WNetAddConnection2( &NetResource,    // pointer of the network resource structure
                                 NULL,            // password
                                 NULL,            // username
                                 0 );            // not remembered, otherwise, specify CONNECT_UPDATE_PROFILE

    UNC.ReleaseBuffer();
    Local.ReleaseBuffer();

    // Try again by asking the username and the password
    if ( Result != WN_SUCCESS && CanSpecifyUsername == true )
    {
        // Initialize the network resource structure
        NetResource.dwType            = RESOURCETYPE_DISK;
        NetResource.lpLocalName        = ( Local.IsEmpty() ) ? NULL : Local.GetBuffer( Local.GetLength() );
        NetResource.lpRemoteName    = UNC.GetBuffer( UNC.GetLength() );
        NetResource.lpProvider        = NULL;

        Result = WNetAddConnection3( ::GetDesktopWindow(),
                                     &NetResource,        // pointer of the network resource structure
                                     _T( "" ),            // empty string to let user enter a password
                                     _T( "" ),            // empty string to let user enter another username
                                     0 );                // not remembered, otherwise, specify CONNECT_UPDATE_PROFILE

        UNC.ReleaseBuffer();
        Local.ReleaseBuffer();
    }

    return Result == WN_SUCCESS;
    //## end ZUNetwork::Map%947664376.body
}

CString ZUNetwork::GetMap( CString Local )
{
    //## begin ZUNetwork::GetMap%947664377.body preserve=yes
    DWORD        Result;
    char        Buffer[500];
    DWORD        Size = 500;

    Result = WNetGetConnection( Local.GetBuffer( Local.GetLength() ),    // network device name
                                Buffer,                                    // buffer
                                &Size );                                // buffer size

    Local.ReleaseBuffer();

    if ( Result == WN_SUCCESS )
    {
        return Buffer;
    }

    return _T( "" );
    //## end ZUNetwork::GetMap%947664377.body
}

BOOL ZUNetwork::RemoveConnection( CString Connection )
{
    //## begin ZUNetwork::RemoveConnection%947664378.body preserve=yes
    DWORD Result;

    Result = WNetCancelConnection2 ( Connection.GetBuffer( Connection.GetLength() ),    // Network device name to disconnect either local or remote name
                                     CONNECT_UPDATE_PROFILE,                            // Should or not update the profile, 0 if not necessary to update the user profile
                                     TRUE );                                            // Force disconnection even if files are open

    Connection.ReleaseBuffer();

    return Result == WN_SUCCESS;
    //## end ZUNetwork::RemoveConnection%947664378.body
}

bool ZUNetwork::OpenConnection( CString Path, HWND hwndOwner, bool Temporarily, bool Interactive )
{
    //## begin ZUNetwork::OpenConnection%945889219.body preserve=yes
    NETRESOURCE    NetResource;
    DWORD        AccessNameBufferSize = 200;
    char        AccessName[200];
    DWORD        Result;

    // Initialize the network resource structure
    NetResource.dwScope            = RESOURCE_GLOBALNET;
    NetResource.dwType            = RESOURCETYPE_DISK;
    NetResource.dwDisplayType    = RESOURCEDISPLAYTYPE_GENERIC;
    NetResource.dwUsage            = RESOURCEUSAGE_NOLOCALDEVICE;
    NetResource.lpLocalName        = NULL;
    NetResource.lpRemoteName    = Path.GetBuffer( Path.GetLength() );
    NetResource.lpComment        = _T( "" );
    NetResource.lpProvider        = NULL;

    // If no owner, assigns the desktop window handle
    if ( hwndOwner == NULL )
    {
        hwndOwner = ::GetDesktopWindow();
    }

    DWORD dwRet = WNetUseConnection( hwndOwner,                                    // hwndOwner
                                     &NetResource,                                // lpNetResource,
                                     NULL,                                        // lpPassword
                                     NULL,                                        // lpUserID
                                     CONNECT_TEMPORARY | CONNECT_INTERACTIVE,    // dwFlags,
                                     AccessName,                                // lpAccessName
                                     &AccessNameBufferSize,                        // lpBufferSize
                                     &Result );                                    // lpResult

    Path.ReleaseBuffer();

    return dwRet == WN_SUCCESS;
    //## end ZUNetwork::OpenConnection%945889219.body
}

bool ZUNetwork::EnumConnections( ZNetResourceManager& ResourceManager )
{
    //## begin ZUNetwork::EnumConnections%947664379.body preserve=yes
    return EnumConnect( NULL, ResourceManager );
    //## end ZUNetwork::EnumConnections%947664379.body
}

bool ZUNetwork::GetFreeConnections( CStringArray& FreeConnectionArray )
{
    //## begin ZUNetwork::GetFreeConnections%947664375.body preserve=yes
    ZNetResourceManager ResourceManager;

    if ( !EnumConnections( ResourceManager ) )
    {
        return false;
    }

    CStringArray DriveArray;

    if ( !GetNetworkDrives( DriveArray ) )
    {
        return false;
    }

    // Now run through drives letter and try to locate
    // if already mapped
    for ( size_t i = 0; i < DriveArray.GetSize(); ++i )
    {
        bool Found = false;

        for ( size_t ri = 0; ri < ResourceManager.GetNetResourceCount(); ++ri )
        {
            if ( DriveArray.GetAt( i ).CompareNoCase( ResourceManager.GetNetResourceAt( ri )->GetLocalName() ) == 0 )
            {
                Found = true;
                break;
            }
        }

        if ( Found == false )
        {
            FreeConnectionArray.Add( DriveArray.GetAt( i ) );
        }
    }

    return DriveArray.GetSize() > 0;
    //## end ZUNetwork::GetFreeConnections%947664375.body
}

CString ZUNetwork::GetUNC( const CString value )
{
    //## begin ZUNetwork::GetUNC%945619906.body preserve=yes
    // Size of Buffer
    DWORD                    cbBuff    = 1000;

    // Buffer to receive information
    TCHAR                    szBuff[1000];
    REMOTE_NAME_INFO*        prni    = (REMOTE_NAME_INFO*)&szBuff;

    // Pointers to head of buffer
    UNIVERSAL_NAME_INFO*    puni    = (UNIVERSAL_NAME_INFO*)&szBuff;
    DWORD                    res;

    if ( ( res = WNetGetUniversalName( (LPTSTR)( (const char*)value ),
                                       UNIVERSAL_NAME_INFO_LEVEL,
                                       (LPVOID)&szBuff,                    // Structure is written to this block of memory
                                       &cbBuff ) ) != NO_ERROR )
    {
        char Buffer[100];

        // If it fails print the error
        sprintf( Buffer, _T( "Error: %ld\n\n" ), res );

        return _T( "" );
    }

    // Using the pointer to the REMOTE_NAME_INFO_LEVEL structure
    return puni->lpUniversalName;
    //## end ZUNetwork::GetUNC%945619906.body
}

CString ZUNetwork::GetNetworkErrorMessage()
{
    //## begin ZUNetwork::GetNetworkErrorMessage%913142850.body preserve=yes
    INT         nBuffSize = 100;
    WORD        nError;
    CString        Error;
    
    // Calling GetNetworkErrorNo at this point I am assuming that
    // a network error has indeed occured.
    switch ( nError = GetNetworkErrorNo() )
    {
        // Success!
        case WN_SUCCESS:
        {
            return _T( "" );
        }

        case WN_NOT_SUPPORTED:
        {
            Error.LoadString( IDS_NOT_SUPPORTED );
            break;
        }

        default:
        {
            DWORD wRetCode;

#ifndef _WIN32
            // First see if this is a driver specific error.  Then use Winnet.h
            wRetCode = WNetGetErrorText( nError, Error.GetBufferSetLength( nBuffSize ), &nBuffSize );
#else
            char szNameBuf[200];
            WNetGetLastError( &wRetCode,
                              Error.GetBufferSetLength( nBuffSize ),
                              nBuffSize,
                              szNameBuf,
                              sizeof( szNameBuf ) );
#endif

            Error.ReleaseBuffer();

            if ( wRetCode != WN_SUCCESS )
            {
                switch ( nError )
                {
                    case WN_SUCCESS:
                    {
                        Error.LoadString( IDS_SUCCESS );
                        break;
                    }

                    case WN_NOT_SUPPORTED:
                    {
                        Error.LoadString( IDS_NOT_SUPPORTED );
                        break;
                    }

                    case WN_NET_ERROR:
                    {
                        Error.LoadString( IDS_NET_ERROR );
                        break;
                    }

                    case WN_MORE_DATA:
                    {
                        Error.LoadString( IDS_MORE_DATA );
                        break;
                    }

                    case WN_BAD_POINTER:
                    {
                        Error.LoadString( IDS_BAD_POINTER );
                        break;
                    }

                    case WN_BAD_VALUE:
                    {
                        Error.LoadString( IDS_BAD_VALUE );
                        break;
                    }

                    case WN_BAD_PASSWORD:
                    {
                        Error.LoadString( IDS_BAD_PASSWORD );
                        break;
                    }

                    case WN_ACCESS_DENIED:
                    {
                        Error.LoadString( IDS_ACCESS_DENIED );
                        break;
                    }

                    case WN_FUNCTION_BUSY:
                    {
                        Error.LoadString( IDS_FUNCTION_BUSY );
                        break;
                    }

#ifndef _WIN32
                    case WN_WINDOWS_ERROR:
                    {
                        Error.LoadString( IDS_WINDOWS_ERROR );
                        break;
                    }
#endif

                    case WN_BAD_USER:
                    {
                        Error.LoadString( IDS_BAD_USER );
                        break;
                    }

                    case WN_OUT_OF_MEMORY:
                    {
                        Error.LoadString( IDS_OUT_OF_MEMORY );
                        break;
                    }

                    case WN_CANCEL:
                    {
                        Error.LoadString( IDS_CANCEL );
                        break;
                    }

                    case WN_NOT_CONNECTED:
                    {
                        Error.LoadString( IDS_NOT_CONNECTED );
                        break;
                    }

                    case WN_OPEN_FILES:
                    {
                        Error.LoadString( IDS_OPEN_FILES );
                        break;
                    }

                    case WN_BAD_NETNAME:
                    {
                        Error.LoadString( IDS_BAD_NETNAME );
                        break;
                    }

                    case WN_BAD_LOCALNAME:
                    {
                        Error.LoadString( IDS_BAD_LOCALNAME );
                        break;
                    }

#ifndef _WIN32
                    case WN_BAD_JOBID:
                    {
                        Error.LoadString( IDS_BAD_JOBID );
                        break;
                    }

                    case WN_JOB_NOT_FOUND:
                    {
                        Error.LoadString( IDS_JOB_NOT_FOUND );
                        break;
                    }

                    case WN_JOB_NOT_HELD:
                    {
                        Error.LoadString( IDS_JOB_NOT_HELD );
                        break;
                    }

                    case WN_BAD_QUEUE:
                    {
                        Error.LoadString( IDS_BAD_QUEUE );
                        break;
                    }

                    case WN_BAD_FILE_HANDLE:
                    {
                        Error.LoadString( IDS_BAD_FILE_HANDLE );
                        break;
                    }

                    case WN_CANT_SET_COPIES:
                    {
                        Error.LoadString( IDS_CANT_SET_COPIES );
                        break;
                    }

                    case WN_ALREADY_LOCKED:
                    {
                        Error.LoadString( IDS_ALREADY_LOCKED );
                        break;
                    }
#endif

                    case WN_ALREADY_CONNECTED:
                    {
                        Error.LoadString( IDS_ALREADY_CONNECTED );
                        break;
                    }

                    default:
                    {
                        Error.LoadString( IDS_UNKNOWN_ERROR_CODE );
                        break;
                    }
                } // switch (nError)
            }

            break;
        }// default
    }// switch WNetGetError

    return Error;
    //## end ZUNetwork::GetNetworkErrorMessage%913142850.body
}

CString ZUNetwork::GetUserName()
{
    //## begin ZUNetwork::GetUserName%913142851.body preserve=yes
    BOOL bRetValue = FALSE;

    // User name string
    char szUser[200];
    szUser[0] = 0;

#ifndef _WIN32
    static BOOL    notfirst    = FALSE;
    HANDLE         hNetwork    = 0;
    INT            nBuffSize;

    nBuffSize = sizeof( szUser );

    // Deal with windows for workgroups multinet
    if ( MNetDetect() )
    {
        // Write message to the windebug
        TRACE( _T( " Multinet detected in GetUser" ) );

        if ( hNetwork != 0 )
        {
            // Write message to the windebug
            TRACE( _T( " MNetGetlastTarget returned with handle %u" ), (LPINT)hNetwork );

            if ( notfirst )
            {
                hNetwork = GetLastTargetHandle();
                SetNextTargetHandle( hNetwork );
            }
            else
            {
                // Write message to the windebug
                TRACE0( _T( " First time through -- don't believe WFW" ) );

                if ( NetworkEnumAll() )
                {
                    // Write message to the windebug
                    TRACE1( _T( " MNetNetworkEnum returned %d Multinets, setting first as target" ), m_MNets );
    
                    notfirst = TRUE;

                    if ( m_Primary != 0 )
                    {
                        SetNextTargetHandle( m_Primary );
                    }
                    else
                    {
                        SetNextTargetHandle( m_hInstMNet[0] );
                    }
                }
                else
                {
                    TRACE0( _T( " MNetNetworkEnum returned No Multinets--strange response" ) );
                }
            }
        }
        else
        {
            // Write message to the windebug
            TRACE0( _T( " MNetGetLastTarget returned a NULL handle" ) );

            if ( NetworkEnumAll() )
            {
                // Write message to the windebug
                TRACE0( _T( " MNetNetworkEnum returned Multinets, setting first as target" ) );

                if ( m_Primary != 0 )
                {
                    SetNextTargetHandle( m_Primary );
                }
                else
                {
                    SetNextTargetHandle( m_hInstMNet[0] );
                }
            }
            else
            {
                // Write message to the windebug
                TRACE0( _T( " MNetNetworkEnum returned No Multinets--strange response" ) );
            }
        }
    }        // end of Multinet detect code

    switch ( WNetGetUser( (LPSTR) szUser, (LPINT) &nBuffSize ) )
    {
        case WN_SUCCESS:
        {
            bRetValue = TRUE;
            break;
        }

        case WN_NOT_SUPPORTED:
        {
            break;
        }

        case WN_NET_ERROR:
        {
            break;
        }

        case WN_BAD_POINTER:
        {
            break;
        }

        case WN_BAD_USER:
        {
            break;
        }

        case WN_MORE_DATA:
        {
            break;
        }
    }
#else
    DWORD SizeBuffer = sizeof( szUser );

    switch ( WNetGetUser( NULL, (LPSTR)szUser, &SizeBuffer ) )
    {
        case NO_ERROR:
        {
            bRetValue = TRUE;
            break;
        }

        case ERROR_NOT_CONNECTED:
        {
            break;
        }

        case ERROR_MORE_DATA:
        {
            break;
        }

        case ERROR_NO_NETWORK:
        {
            break;
        }

        case ERROR_EXTENDED_ERROR:
        {
            break;
        }

        case ERROR_NO_NET_OR_BAD_PATH:
        {
            break;
        }
    }
#endif

    return ( bRetValue ) ? szUser : _T( "" );
    //## end ZUNetwork::GetUserName%913142851.body
}

BOOL ZUNetwork::MNetDetect()
{
    //## begin ZUNetwork::MNetDetect%913142852.body preserve=yes
    BOOL bRetVal = FALSE;

#ifndef _WIN32
    static int    iMultinet = -1;
    WORD        nIndex;

    // First time, so we must determine
    if ( iMultinet == -1 )
    {
        /* Query net version type */
        nIndex = WNetGetCaps (WNNC_NET_TYPE);

        // Is MultiNet bit set ??
        if ( nIndex & WNNC_NET_MultiNet )
        {
            iMultinet = 1;
        }
        else
        {
            iMultinet = 0;
        }
    }

    if ( iMultinet == 1 )
    {
        bRetVal = TRUE;
    }
#endif // not in _WIN32

    return bRetVal;
    //## end ZUNetwork::MNetDetect%913142852.body
}

BOOL ZUNetwork::WFWDetect()
{
    //## begin ZUNetwork::WFWDetect%913142853.body preserve=yes
    BOOL bRetVal = FALSE;

#ifndef _WIN32
    static int    WFWnet = -1;
    WORD        nIndex;

    // First time, so we must determine
    if ( WFWnet == -1 )
    {
        WFWnet = 0;

        // Query net version type
        nIndex = WNetGetCaps( WNNC_NET_TYPE );

        // Is MultiNet bit set ??
        if ( nIndex & WNNC_NET_MultiNet )
        {
            if ( nIndex & WNNC_SUBNET_WinWorkgroups )
            {
                WFWnet = 1;
            }
        }
    }

    if ( WFWnet == 1 )
    {
        bRetVal = TRUE;
    }
#endif // not in _WIN32

    return bRetVal;
    //## end ZUNetwork::WFWDetect%913142853.body
}

HANDLE ZUNetwork::GetWFWNetDriverHandle()
{
    //## begin ZUNetwork::GetWFWNetDriverHandle%913142854.body preserve=yes

#ifndef _WIN32
    HANDLE hinst    = 0;
    hinst            = (HINSTANCE)WNetGetCaps( (WORD)0xffff );

    if ( hinst != 0 )
    {
        m_hInstWFWDriver = hinst;
    }

    return m_hInstWFWDriver;
#else
    return 0;
#endif
    //## end ZUNetwork::GetWFWNetDriverHandle%913142854.body
}

HANDLE ZUNetwork::GetLastTargetHandle()
{
    //## begin ZUNetwork::GetLastTargetHandle%913142855.body preserve=yes
    // Pointer to MNet function
    LPMNETGETLASTTARGET lpMNetGetLastTarget;
    HANDLE hlast = NULL;

    if ( m_hInstWFWDriver == 0 )
    {
        m_hInstWFWDriver = GetWFWNetDriverHandle();
    }

    if ( m_hInstWFWDriver != 0 )
    {
        lpMNetGetLastTarget = (LPMNETGETLASTTARGET)GetProcAddress( (HINSTANCE)m_hInstWFWDriver,
                                                                   (LPCSTR)MAKEINTRESOURCE( ORD_MNETGETLASTTARGET ) );

        if ( lpMNetGetLastTarget != NULL )
        {
            hlast = (*lpMNetGetLastTarget)();
        }
    }

    return hlast;
    //## end ZUNetwork::GetLastTargetHandle%913142855.body
}

WORD ZUNetwork::SetNextTargetHandle( HANDLE hNetwork )
{
    //## begin ZUNetwork::SetNextTargetHandle%913142856.body preserve=yes
    // Pointer to MNet function
    LPMNETSETNEXTTARGET lpMNetSetNextTarget;
    WORD retval = WN_BAD_VALUE;

    if ( m_hInstWFWDriver == 0 )
    {
        m_hInstWFWDriver = GetWFWNetDriverHandle();
    }

    if ( m_hInstWFWDriver != 0 )
    {
        lpMNetSetNextTarget = (LPMNETSETNEXTTARGET)GetProcAddress( (HINSTANCE)m_hInstWFWDriver,
                                                                   (LPCSTR)MAKEINTRESOURCE( ORD_MNETSETNEXTTARGET ) );

        if ( lpMNetSetNextTarget != NULL )
        {
            retval = (*lpMNetSetNextTarget)(hNetwork);
        }
    }

    return retval;
    //## end ZUNetwork::SetNextTargetHandle%913142856.body
}

BOOL ZUNetwork::NetworkEnumAll()
{
    //## begin ZUNetwork::NetworkEnumAll%913142857.body preserve=yes
    // Pointer to MNet function
    LPMNETNETWORKENUM    lpMNetNetworkEnum;
    WORD                err;
    HANDLE                hNetwork = 0;

    // Pointer to MNet function
    LPMNETGETNETINFO    lpMNetGetNetInfo;
    WORD                NetInfo            = 0;
    char                szButton[80]    = _T( "empty" );
    char                szBuffer2[100];
    int                    cbButton        = 80;
    HANDLE                hInstance        = NULL;
    WORD                errinfo;
    BOOL                retval            = FALSE;
    int                    i;

    // Initialize our MNet array
    for ( i = 0; i < MAX_MNETS; i++ )
    {
        m_hInstMNet[i++] = NULL;
    }

    i = 0;

    if ( m_hInstWFWDriver == 0 )
    {
        m_hInstWFWDriver = GetWFWNetDriverHandle();
    }

    if ( m_hInstWFWDriver != 0 )
    {
        lpMNetNetworkEnum = (LPMNETNETWORKENUM)GetProcAddress( (HINSTANCE)m_hInstWFWDriver,
                                                               (LPCSTR)MAKEINTRESOURCE( ORD_MNETNETWORKENUM ) );

        if ( lpMNetNetworkEnum != NULL )
        {
            err = (*lpMNetNetworkEnum)( &hNetwork );

            if ( hNetwork != 0 )
            {
                m_hInstMNet[i++] = hNetwork;
                lpMNetGetNetInfo = (LPMNETGETNETINFO)GetProcAddress( (HINSTANCE)m_hInstWFWDriver,
                                                                     (LPCSTR) MAKEINTRESOURCE( ORD_MNETGETNETINFO ) );

                if ( lpMNetGetNetInfo != NULL )
                {
                    // Write message to the windebug
                    wsprintf( (LPSTR)szBuffer2,
                              (LPSTR)_T( " Debug: values before call Handle: %u, NetInfo: %u, Text: %s, Button Text length: %u, DLL handle: %u" ),
                              (LPINT)&hNetwork,
                              (LPINT)&NetInfo,
                              (LPSTR)szButton,
                              (LPINT)&cbButton,
                              (LPINT)&hInstance );

                    TRACE1( _T( "%s" ), szBuffer2 );

                    errinfo = (*lpMNetGetNetInfo)( (HANDLE)hNetwork,
                                                   (WORD *)&NetInfo,
                                                   (LPSTR)szButton,
                                                   (LPINT)&cbButton,
                                                   (HANDLE*)&hInstance );

                    if ( errinfo == WN_SUCCESS )
                    {
                        // Write message to the windebug
                        TRACE0( _T( " MNetGetInfo returned valid information" ) );

                        wsprintf( (LPSTR)szBuffer2,
                                  (LPSTR)_T( " Handle: %u, NetInfo: %u, Text: %s, Button Text length: %u, DLL handle: %u" ),
                                  (LPINT)&hNetwork,
                                  (LPINT)&NetInfo,
                                  (LPSTR)szButton,
                                  (LPINT)&cbButton,
                                  (LPINT)&hInstance );

                        TRACE1( _T( "%s" ),szBuffer2 );

                        if ( NetInfo == MNM_NET_PRIMARY )
                        {
                            m_Primary = hNetwork;
                        }
                    }
                    else
                    {
                        // Write message to the windebug
                        TRACE0( _T( " MNetGetInfo returned invalid information" ) );
                    }
                }

                while ( err != WN_BAD_VALUE && i < MAX_MNETS )
                {
                    err = (*lpMNetNetworkEnum)( &hNetwork );

                    if ( hNetwork != 0 )
                    {
                        m_hInstMNet[i++] = hNetwork;

                        if ( lpMNetGetNetInfo != NULL )
                        {
                            // Write message to the windebug
                            wsprintf( (LPSTR)szBuffer2,
                                      (LPSTR)_T( " Debug: values before call Handle: %u, NetInfo: %u, Text: %s, Button Text length: %u, DLL handle: %u" ),
                                      (LPINT)&hNetwork,
                                      (LPINT)&NetInfo,
                                      (LPSTR)szButton,
                                      (LPINT)&cbButton,
                                      (LPINT)&hInstance );

                            TRACE1( _T( "%s" ), szBuffer2 );

                            errinfo = (*lpMNetGetNetInfo)( (HANDLE)hNetwork,
                                                           (WORD *)&NetInfo,
                                                           (LPSTR)szButton,
                                                           (LPINT)&cbButton,
                                                           (HANDLE *)&hInstance );

                            if ( errinfo == WN_SUCCESS )
                            {
                                // Write message to the windebug
                                TRACE0( _T( " MNetGetInfo returned valid information" ) );

                                wsprintf( (LPSTR)szBuffer2,
                                          (LPSTR)_T( " Handle: %u, NetInfo: %u, Text: %s, Button Text length: %u, DLL handle: %u" ),
                                          (LPINT)&hNetwork,
                                          (LPINT)&NetInfo,
                                          (LPSTR)szButton,
                                          (LPINT)&cbButton,
                                          (LPINT)&hInstance );

                                TRACE1( _T( "%s" ), szBuffer2 );

                                if ( NetInfo == MNM_NET_PRIMARY )
                                {
                                    m_Primary = hNetwork;
                                }
                            }
                        }
                    }
                }        /* while err != WN_BAD_VALUE etc */
            }
        }

        /* Did we find some networks ? */
        for ( i = 0; i < MAX_MNETS; i++ )
        {
            if ( m_hInstMNet[i] != 0 )
            {
                m_MNets++;
                retval = TRUE;
            }
        }
    }

    return retval;
    //## end ZUNetwork::NetworkEnumAll%913142857.body
}

bool ZUNetwork::EnumConnect( LPNETRESOURCE lpnr, ZNetResourceManager& ResourceManager )
{
    //## begin ZUNetwork::EnumConnect%947664374.body preserve=yes
    DWORD dwResult, dwResultEnum;
    HANDLE hEnum;
    DWORD cbBuffer = 16384;        // 16K is a good size
    DWORD cEntries = -1;        // Enumerate all possible entries
    LPNETRESOURCE lpnrLocal;    // Pointer to enumerated structures
    DWORD i;

    // Call the WNetOpenEnum function to begin the enumeration.
    dwResult = WNetOpenEnum( RESOURCE_CONNECTED,    // All network resources
                             RESOURCETYPE_ANY,        // All resources
                             0,                        // Enumerate all resources
                             lpnr,                    // NULL first time the function is called
                             &hEnum );                // Handle to the resource

    if ( dwResult != NO_ERROR )
    {
        // Process errors with an application-defined error handler.
        return false;
    }

    // Call the GlobalAlloc function to allocate resources.
    lpnrLocal = (LPNETRESOURCE)GlobalAlloc( GPTR, cbBuffer );

    do
    {
        // Initialize the buffer.
        ZeroMemory( lpnrLocal, cbBuffer );

        // Call the WNetEnumResource function to continue the enumeration.
        dwResultEnum = WNetEnumResource( hEnum,            // Resource handle
                                         &cEntries,        // Defined locally as -1
                                         lpnrLocal,        // LPNETRESOURCE
                                         &cbBuffer );    // Buffer size

        // If the call succeeds, loop through the structures.
        if ( dwResultEnum == NO_ERROR )
        {
            for( i = 0; i < cEntries; i++ )
            {
                ResourceManager.AddNetResource( &lpnrLocal[i] );

                // If the NETRESOURCE structure represents a container resource,
                // call the EnumerateFunc function recursively.
                if ( RESOURCEUSAGE_CONTAINER == ( lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER ) )
                {
                    if( !EnumConnect( &lpnrLocal[i], ResourceManager ) )
                    {
                        TRACE( _T( "EnumerateFunc returned FALSE." ) );
                    }
                }
            }
        }
        // Process errors.
        else if ( dwResultEnum != ERROR_NO_MORE_ITEMS )
        {
            break;
        }
    }
    while( dwResultEnum != ERROR_NO_MORE_ITEMS );

    // Call the GlobalFree function to free the memory.
    GlobalFree( (HGLOBAL)lpnrLocal );

    // Call WNetCloseEnum to end the enumeration.
    dwResult = WNetCloseEnum( hEnum );

    if( dwResult != NO_ERROR )
    {
        // Process errors.
        return false;
    }

    return true;
    //## end ZUNetwork::EnumConnect%947664374.body
}

// Additional Declarations
//## begin ZUNetwork%366D71D50245.declarations preserve=yes
//## end ZUNetwork%366D71D50245.declarations

//## begin module%366D71A502F0.epilog preserve=yes
//## end module%366D71A502F0.epilog
