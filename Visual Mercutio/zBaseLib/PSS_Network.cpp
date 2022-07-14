/****************************************************************************
 * ==> PSS_Network ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a network manager                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Network.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#ifndef ORD_MNETNETWORKENUM
    #define ORD_MNETNETWORKENUM 33
#endif

#ifndef ORD_MNETGETLASTTARGET
    #define ORD_MNETGETLASTTARGET 35
#endif

#ifndef ORD_MNETGETNETINFO
    #define ORD_MNETGETNETINFO 37
#endif

#ifndef ORD_MNETSETNEXTTARGET
    #define ORD_MNETSETNEXTTARGET 38
#endif

// This resides in multinet.h from WFW SDK. Network is primary network (Windows network)
#ifndef MNM_NET_PRIMARY
    #define MNM_NET_PRIMARY 0x0001
#endif
//---------------------------------------------------------------------------
// Global typedefs
//---------------------------------------------------------------------------
typedef HANDLE(WINAPI *LPMNETGETLASTTARGET) ();
typedef WORD  (WINAPI *LPMNETSETNEXTTARGET) (HANDLE      hNetwork);
typedef WORD  (WINAPI *LPMNETNETWORKENUM)   (HANDLE FAR* hNetwork);
typedef WORD  (WINAPI *LPMNETGETNETINFO)    (HANDLE      hNetwork,
                                             WORD*       lpwNetInfo,
                                             LPSTR       lpszButton,
                                             LPINT       lpcbButton,
                                             HANDLE*     lphInstance);
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
HANDLE PSS_Network::m_Primary               = 0;
HANDLE PSS_Network::m_hInstNetDriver        = 0;
HANDLE PSS_Network::m_hInstWFWDriver        = 0;
HANDLE PSS_Network::m_hInstMNet[g_MaxMNets] = {NULL};
int    PSS_Network::m_MNets                 = 0;
//---------------------------------------------------------------------------
// PSS_Network
//---------------------------------------------------------------------------
PSS_Network::PSS_Network()
{}
//---------------------------------------------------------------------------
PSS_Network::PSS_Network(const PSS_Network& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Network::~PSS_Network()
{}
//---------------------------------------------------------------------------
const PSS_Network& PSS_Network::operator = (const PSS_Network& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
bool PSS_Network::OpenConnection(const CString& path, HWND hWndOwner, bool temporarily, bool interactive) const
{
    CString     netPath     = path;
    NETRESOURCE netResource = {0};

    // initialize the network resource structure
    netResource.dwScope       = RESOURCE_GLOBALNET;
    netResource.dwType        = RESOURCETYPE_DISK;
    netResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    netResource.dwUsage       = RESOURCEUSAGE_NOLOCALDEVICE;
    netResource.lpLocalName   = NULL;
    netResource.lpRemoteName  = netPath.GetBuffer(netPath.GetLength());
    netResource.lpComment     = _T("");
    netResource.lpProvider    = NULL;

    // if no owner, assign the desktop window handle
    if (!hWndOwner)
        hWndOwner = ::GetDesktopWindow();

    char  accessName[200];
    DWORD accessNameBufferSize = 200;
    DWORD connectionResult;

    const DWORD result = ::WNetUseConnection(hWndOwner,
                                             &netResource,
                                             NULL,
                                             NULL,
                                             CONNECT_TEMPORARY | CONNECT_INTERACTIVE,
                                             accessName,
                                             &accessNameBufferSize,
                                             &connectionResult);

    netPath.ReleaseBuffer();

    return (result == WN_SUCCESS);
}
//---------------------------------------------------------------------------
BOOL PSS_Network::RemoveConnection(const CString& connection) const
{
    CString     connName = connection;
    const DWORD result   = ::WNetCancelConnection2(connName.GetBuffer(connName.GetLength()), CONNECT_UPDATE_PROFILE, TRUE);

    connName.ReleaseBuffer();

    return (result == WN_SUCCESS);
}
//---------------------------------------------------------------------------
bool PSS_Network::EnumConnections(PSS_NetResourceManager& resourceManager) const
{
    return EnumConnect(NULL, resourceManager);
}
//---------------------------------------------------------------------------
bool PSS_Network::GetFreeConnections(CStringArray& freeConnectionArray) const
{
    PSS_NetResourceManager resourceManager;

    if (!EnumConnections(resourceManager))
        return false;

    CStringArray driveArray;

    if (!GetNetworkDrives(driveArray))
        return false;

    const std::size_t driveArraySize = driveArray.GetSize();

    // iterate through drives letter and try to locate if already mapped
    for (std::size_t i = 0; i < driveArraySize; ++i)
    {
        bool found = false;

        const std::size_t resCount = resourceManager.GetNetResourceCount();

        for (std::size_t resIndex = 0; resIndex < resCount; ++resIndex)
            if (!driveArray.GetAt(i).CompareNoCase(resourceManager.GetNetResourceAt(resIndex)->GetLocalName()))
            {
                found = true;
                break;
            }

        if (!found)
            freeConnectionArray.Add(driveArray.GetAt(i));
    }

    return (driveArray.GetSize() > 0);
}
//---------------------------------------------------------------------------
bool PSS_Network::GetNetworkDrives(CStringArray& driveArray) const
{
    char driveLetter[5];

    for (int drive = 0; drive < 26; ++drive)
    {
        std::sprintf(driveLetter, _T("%c:"), _T('A') + drive);

        const UINT result = ::GetDriveType(driveLetter);

        if (result != DRIVE_REMOVABLE &&
            result != DRIVE_FIXED     &&
            result != DRIVE_CDROM     &&
            result != DRIVE_RAMDISK)
            driveArray.Add(driveLetter);
    }

    return (driveArray.GetSize() > 0);
}
//---------------------------------------------------------------------------
bool PSS_Network::Map(const CString& unc, const CString& local, bool canSpecifyUserName) const
{
    CString     uncName     = unc;
    CString     localName   = local;
    NETRESOURCE netResource = {0};

    // initialize the network resource structure
    netResource.dwType       = RESOURCETYPE_DISK;
    netResource.lpLocalName  = (localName.IsEmpty() ? NULL : localName.GetBuffer(localName.GetLength()));
    netResource.lpRemoteName = uncName.GetBuffer(uncName.GetLength());
    netResource.lpProvider   = NULL;

    DWORD result = ::WNetAddConnection2(&netResource, NULL, NULL, 0);

    uncName.ReleaseBuffer();
    localName.ReleaseBuffer();

    // try again by asking the user name and the password
    if (result != WN_SUCCESS && canSpecifyUserName)
    {
        // initialize the network resource structure
        netResource.dwType       = RESOURCETYPE_DISK;
        netResource.lpLocalName  = (localName.IsEmpty() ? NULL : localName.GetBuffer(localName.GetLength()));
        netResource.lpRemoteName = uncName.GetBuffer(uncName.GetLength());
        netResource.lpProvider   = NULL;

        result = ::WNetAddConnection3(::GetDesktopWindow(), &netResource, _T(""), _T(""), 0);

        uncName.ReleaseBuffer();
        localName.ReleaseBuffer();
    }

    return (result == WN_SUCCESS);
}
//---------------------------------------------------------------------------
CString PSS_Network::GetMap(const CString& local) const
{
    char    buffer[500];
    DWORD   size      = 500;
    CString localName = local;

    const DWORD result = ::WNetGetConnection(localName.GetBuffer(localName.GetLength()), buffer, &size);

    localName.ReleaseBuffer();

    if (result == WN_SUCCESS)
        return buffer;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Network::GetUNC(const CString& value) const
{
    TCHAR                buffer[1000]    = {0};
    DWORD                bufferSize      = 1000;
    REMOTE_NAME_INFO*    pRemoteNameInfo = (REMOTE_NAME_INFO*)&buffer;
    UNIVERSAL_NAME_INFO* pUniNameInfo    = (UNIVERSAL_NAME_INFO*)&buffer;
    DWORD                result;

    if ((result = ::WNetGetUniversalName(LPTSTR((const char*)value),
                                         UNIVERSAL_NAME_INFO_LEVEL,
                                         LPVOID(&buffer),
                                         &bufferSize)) != NO_ERROR)
    {
        char msgBuffer[100];

        // on failure, print the error
        std::sprintf(msgBuffer, _T("Error: %ld\n\n"), result);

        return _T("");
    }

    return pUniNameInfo->lpUniversalName;
}
//---------------------------------------------------------------------------
CString PSS_Network::GetNetworkErrorMessage() const
{
    INT     bufferSize = 100;
    WORD    errorNb;
    CString error;

    // GetNetworkErrorNo() is called by assuming that a network error has indeed occurred
    switch (errorNb = GetNetworkErrorNo())
    {
        // success
        case WN_SUCCESS:       return _T("");
        case WN_NOT_SUPPORTED: error.LoadString(IDS_NOT_SUPPORTED); break;

        default:
        {
            DWORD retCode;

            #ifndef _WIN32
                // check if this is a driver specific error, then use Winnet.h
                retCode = ::WNetGetErrorText(errorNb, error.GetBufferSetLength(bufferSize), &bufferSize);
            #else
                char nameBuffer[200];

                ::WNetGetLastError(&retCode,
                                   error.GetBufferSetLength(bufferSize),
                                   bufferSize,
                                   nameBuffer,
                                   sizeof(nameBuffer));
            #endif

            error.ReleaseBuffer();

            if (retCode != WN_SUCCESS)
            {
                switch (errorNb)
                {
                    case WN_SUCCESS:             error.LoadString(IDS_SUCCESS);            break;
                    case WN_NOT_SUPPORTED:       error.LoadString(IDS_NOT_SUPPORTED);      break;
                    case WN_NET_ERROR:           error.LoadString(IDS_NET_ERROR);          break;
                    case WN_MORE_DATA:           error.LoadString(IDS_MORE_DATA);          break;
                    case WN_BAD_POINTER:         error.LoadString(IDS_BAD_POINTER);        break;
                    case WN_BAD_VALUE:           error.LoadString(IDS_BAD_VALUE);          break;
                    case WN_BAD_PASSWORD:        error.LoadString(IDS_BAD_PASSWORD);       break;
                    case WN_ACCESS_DENIED:       error.LoadString(IDS_ACCESS_DENIED);      break;
                    case WN_FUNCTION_BUSY:       error.LoadString(IDS_FUNCTION_BUSY);      break;
                    #ifndef _WIN32
                        case WN_WINDOWS_ERROR:   error.LoadString(IDS_WINDOWS_ERROR);      break;
                    #endif
                    case WN_BAD_USER:            error.LoadString(IDS_BAD_USER);           break;
                    case WN_OUT_OF_MEMORY:       error.LoadString(IDS_OUT_OF_MEMORY);      break;
                    case WN_CANCEL:              error.LoadString(IDS_CANCEL);             break;
                    case WN_NOT_CONNECTED:       error.LoadString(IDS_NOT_CONNECTED);      break;
                    case WN_OPEN_FILES:          error.LoadString(IDS_OPEN_FILES);         break;
                    case WN_BAD_NETNAME:         error.LoadString(IDS_BAD_NETNAME);        break;
                    case WN_BAD_LOCALNAME:       error.LoadString(IDS_BAD_LOCALNAME);      break;
                    #ifndef _WIN32
                        case WN_BAD_JOBID:       error.LoadString(IDS_BAD_JOBID);          break;
                        case WN_JOB_NOT_FOUND:   error.LoadString(IDS_JOB_NOT_FOUND);      break;
                        case WN_JOB_NOT_HELD:    error.LoadString(IDS_JOB_NOT_HELD);       break;
                        case WN_BAD_QUEUE:       error.LoadString(IDS_BAD_QUEUE);          break;
                        case WN_BAD_FILE_HANDLE: error.LoadString(IDS_BAD_FILE_HANDLE);    break;
                        case WN_CANT_SET_COPIES: error.LoadString(IDS_CANT_SET_COPIES);    break;
                        case WN_ALREADY_LOCKED:  error.LoadString(IDS_ALREADY_LOCKED);     break;
                    #endif
                    case WN_ALREADY_CONNECTED:   error.LoadString(IDS_ALREADY_CONNECTED);  break;
                    default:                     error.LoadString(IDS_UNKNOWN_ERROR_CODE); break;
                }
            }

            break;
        }
    }

    return error;
}
//---------------------------------------------------------------------------
CString PSS_Network::GetUserName() const
{
    // user name string
    char userName[200];
    userName[0] = 0;

    BOOL retValue = FALSE;

    #ifndef _WIN32
        static BOOL notFirst   = FALSE;
        HANDLE      hNetwork   = 0;
        const INT   bufferSize = sizeof(userName);

        // deal with windows for multinet workgroups
        if (::MNetDetect())
        {
            // write message to the window debugger
            TRACE("Multinet detected in GetUser\n");

            if (hNetwork != 0)
            {
                // write message to the window debugger
                TRACE("MNetGetlastTarget returned with handle %u\n", LPINT(hNetwork));

                if (notFirst)
                {
                    hNetwork = ::GetLastTargetHandle();
                    ::SetNextTargetHandle(hNetwork);
                }
                else
                {
                    // write message to the window debugger
                    TRACE0("First time through -- don't believe WFW\n");

                    if (::NetworkEnumAll())
                    {
                        // write message to the window debugger
                        TRACE1("MNetNetworkEnum returned %d Multinets, setting first as target\n", m_MNets);

                        notFirst = TRUE;

                        if (m_Primary != 0)
                            ::SetNextTargetHandle(m_Primary);
                        else
                            ::SetNextTargetHandle(m_hInstMNet[0]);
                    }
                    else
                        TRACE0("MNetNetworkEnum returned No Multinets--strange response\n");
                }
            }
            else
            {
                // write message to the window debugger
                TRACE0("MNetGetLastTarget returned a NULL handle\n");

                if (::NetworkEnumAll())
                {
                    // write message to the window debugger
                    TRACE0("MNetNetworkEnum returned Multinets, setting first as target\n");

                    if (m_Primary != 0)
                        ::SetNextTargetHandle(m_Primary);
                    else
                        ::SetNextTargetHandle(m_hInstMNet[0]);
                }
                else
                    // write message to the window debugger
                    TRACE0("MNetNetworkEnum returned No Multinets--strange response\n");
            }
        }

        switch (::WNetGetUser(LPSTR(userName), LPINT(&bufferSize)))
        {
            case WN_SUCCESS:       retValue = TRUE; break;
            case WN_NOT_SUPPORTED:
            case WN_NET_ERROR:
            case WN_BAD_POINTER:
            case WN_BAD_USER:
            case WN_MORE_DATA:     break;
        }
    #else
        DWORD bufferSize = sizeof(userName);

        switch (::WNetGetUser(NULL, LPSTR(userName), &bufferSize))
        {
            case NO_ERROR:                 retValue = TRUE; break;
            case ERROR_NOT_CONNECTED:
            case ERROR_MORE_DATA:
            case ERROR_NO_NETWORK:
            case ERROR_EXTENDED_ERROR:
            case ERROR_NO_NET_OR_BAD_PATH: break;
        }
    #endif

    return (retValue ? userName : _T(""));
}
//---------------------------------------------------------------------------
BOOL PSS_Network::MNetDetect() const
{
    BOOL retValue = FALSE;

    // not in _WIN32
    #ifndef _WIN32
        static int multinet = -1;
        WORD       index;

        // first time, so must determine
        if (multinet == -1)
        {
            // query the net version type
            index = ::WNetGetCaps(WNNC_NET_TYPE);

            // is multi net bit set?
            if (index & WNNC_NET_MultiNet)
                multinet = 1;
            else
                multinet = 0;
        }

        if (multinet == 1)
            retValue = TRUE;
    #endif

    return retValue;
}
//---------------------------------------------------------------------------
BOOL PSS_Network::WFWDetect() const
{
    BOOL retValue = FALSE;

    // not in _WIN32
    #ifndef _WIN32
        static int wfwNet = -1;
        WORD       index;

        // first time, so must determine
        if (wfwNet == -1)
        {
            wfwNet = 0;

            // query net version type
            index = ::WNetGetCaps(WNNC_NET_TYPE);

            // is multi net bit set ??
            if (index & WNNC_NET_MultiNet)
                if (index & WNNC_SUBNET_WinWorkgroups)
                    wfwNet = 1;
        }

        if (wfwNet == 1)
            retValue = TRUE;
    #endif

    return retValue;
}
//---------------------------------------------------------------------------
HANDLE PSS_Network::GetWFWNetDriverHandle() const
{
    #ifndef _WIN32
        HANDLE hInst = HINSTANCE(::WNetGetCaps(WORD(0xffff)));

        if (hInst != 0)
            m_hInstWFWDriver = hinst;

        return m_hInstWFWDriver;
    #else
        return 0;
    #endif
}
//---------------------------------------------------------------------------
HANDLE PSS_Network::GetLastTargetHandle() const
{
    LPMNETGETLASTTARGET pMNetGetLastTarget;
    HANDLE              hLast = NULL;

    if (!m_hInstWFWDriver)
        m_hInstWFWDriver = GetWFWNetDriverHandle();

    if (m_hInstWFWDriver)
    {
        pMNetGetLastTarget = LPMNETGETLASTTARGET(::GetProcAddress(HINSTANCE(m_hInstWFWDriver),
                                                                  LPCSTR(MAKEINTRESOURCE(ORD_MNETGETLASTTARGET))));

        if (pMNetGetLastTarget)
            hLast = (*pMNetGetLastTarget)();
    }

    return hLast;
}
//---------------------------------------------------------------------------
WORD PSS_Network::SetNextTargetHandle(HANDLE hNetwork) const
{
    LPMNETSETNEXTTARGET pMNetSetNextTarget;
    WORD                retValue = WN_BAD_VALUE;

    if (!m_hInstWFWDriver)
        m_hInstWFWDriver = GetWFWNetDriverHandle();

    if (m_hInstWFWDriver)
    {
        pMNetSetNextTarget = LPMNETSETNEXTTARGET(::GetProcAddress(HINSTANCE(m_hInstWFWDriver),
                                                                  LPCSTR(MAKEINTRESOURCE(ORD_MNETSETNEXTTARGET))));

        if (pMNetSetNextTarget)
            retValue = (*pMNetSetNextTarget)(hNetwork);
    }

    return retValue;
}
//---------------------------------------------------------------------------
BOOL PSS_Network::NetworkEnumAll() const
{
    LPMNETNETWORKENUM pMNetNetworkEnum;
    HANDLE            hNetwork   = 0;
    LPMNETGETNETINFO  pMNetGetNetInfo;
    WORD              netInfo    = 0;
    char              button[80] = _T("empty");
    char              buffer[100];
    int               cbButton   = 80;
    HANDLE            hInstance  = NULL;
    WORD              errInfo;
    BOOL              result     = FALSE;
    int               i;

    // initialize the MNet array
    for (i = 0; i < g_MaxMNets; ++i)
    {
        m_hInstMNet[i] = NULL;
        ++i;
    }

    i = 0;

    if (!m_hInstWFWDriver)
        m_hInstWFWDriver = GetWFWNetDriverHandle();

    if (m_hInstWFWDriver)
    {
        pMNetNetworkEnum = LPMNETNETWORKENUM(::GetProcAddress(HINSTANCE(m_hInstWFWDriver),
                                                              LPCSTR(MAKEINTRESOURCE(ORD_MNETNETWORKENUM))));

        if (pMNetNetworkEnum)
        {
            WORD error = (*pMNetNetworkEnum)(&hNetwork);

            if (hNetwork != 0)
            {
                m_hInstMNet[i] = hNetwork;
                ++i;

                pMNetGetNetInfo = LPMNETGETNETINFO(::GetProcAddress(HINSTANCE(m_hInstWFWDriver),
                                                                    LPCSTR(MAKEINTRESOURCE(ORD_MNETGETNETINFO))));

                if (pMNetGetNetInfo)
                {
                    // write message to the window debugger
                    ::wsprintf(LPSTR(buffer),
                               LPSTR(_T("Debug: values before call Handle: %p, NetInfo: %p, Text: %s, Button Text length: %u, DLL handle: %u")),
                               LPINT(&hNetwork),
                               LPINT(&netInfo),
                               LPSTR(button),
                               LPINT(&cbButton),
                               LPINT(&hInstance));

                    TRACE1("%s\n", buffer);

                    errInfo = (*pMNetGetNetInfo)(HANDLE(hNetwork),
                                                 (WORD*)&netInfo,
                                                 LPSTR(button),
                                                 LPINT(&cbButton),
                                                 (HANDLE*)&hInstance);

                    if (errInfo == WN_SUCCESS)
                    {
                        // write message to the window debugger
                        TRACE0("MNetGetInfo returned valid information\n");

                        ::wsprintf(LPSTR(buffer),
                                   LPSTR(_T("Handle: %p, NetInfo: %p, Text: %s, Button Text length: %u, DLL handle: %u")),
                                   LPINT(&hNetwork),
                                   LPINT(&netInfo),
                                   LPSTR(button),
                                   LPINT(&cbButton),
                                   LPINT(&hInstance));

                        TRACE1("%s\n", buffer);

                        if (netInfo == MNM_NET_PRIMARY)
                            m_Primary = hNetwork;
                    }
                    else
                        // write message to the window debugger
                        TRACE0("MNetGetInfo returned invalid information");
                }

                while (error != WN_BAD_VALUE && i < g_MaxMNets)
                {
                    error = (*pMNetNetworkEnum)(&hNetwork);

                    if (hNetwork != 0)
                    {
                        m_hInstMNet[i++] = hNetwork;

                        if (pMNetGetNetInfo)
                        {
                            // write message to the window debugger
                            ::wsprintf(LPSTR(buffer),
                                       LPSTR(_T("Debug: values before call Handle: %p, NetInfo: %p, Text: %s, Button Text length: %u, DLL handle: %u")),
                                       LPINT(&hNetwork),
                                       LPINT(&netInfo),
                                       LPSTR(button),
                                       LPINT(&cbButton),
                                       LPINT(&hInstance));

                            TRACE1("%s\n", buffer);

                            errInfo = (*pMNetGetNetInfo)(HANDLE(hNetwork),
                                                         (WORD*)&netInfo,
                                                         LPSTR(button),
                                                         LPINT(&cbButton),
                                                         (HANDLE*)&hInstance);

                            if (errInfo == WN_SUCCESS)
                            {
                                // write message to the window debugger
                                TRACE0("MNetGetInfo returned valid information");

                                ::wsprintf(LPSTR(buffer),
                                           LPSTR(_T("Handle: %p, NetInfo: %p, Text: %s, Button Text length: %u, DLL handle: %u")),
                                           LPINT(&hNetwork),
                                           LPINT(&netInfo),
                                           LPSTR(button),
                                           LPINT(&cbButton),
                                           LPINT(&hInstance));

                                TRACE1("%s\n", buffer);

                                if (netInfo == MNM_NET_PRIMARY)
                                    m_Primary = hNetwork;
                            }
                        }
                    }
                }
            }
        }

        // found some networks?
        for (i = 0; i < g_MaxMNets; ++i)
            if (m_hInstMNet[i])
            {
                ++m_MNets;
                result = TRUE;
            }
    }

    return result;
}
//---------------------------------------------------------------------------
bool PSS_Network::EnumConnect(LPNETRESOURCE pNetResources, PSS_NetResourceManager& resourceManager) const
{
    HANDLE hEnum;

    // call the WNetOpenEnum function to begin the enumeration.
    DWORD result = ::WNetOpenEnum(RESOURCE_CONNECTED, RESOURCETYPE_ANY, 0, pNetResources, &hEnum);

    // process errors with an application-defined error handler
    if (result != NO_ERROR)
        return false;

    LPNETRESOURCE pNRLocal = NULL;

    try
    {
        DWORD buffer  = 16384; // 16K is a good size
        DWORD entries = -1;    // enumerate all possible entries

        // call the GlobalAlloc() function to allocate resources
        pNRLocal = LPNETRESOURCE(::GlobalAlloc(GPTR, buffer));

        if (!pNRLocal)
            return false;

        DWORD resultEnum = 0;

        do
        {
            // initialize the buffer
            ZeroMemory(pNRLocal, buffer);

            // call the WNetEnumResource() function to continue the enumeration
            resultEnum = ::WNetEnumResource(hEnum, &entries, pNRLocal, &buffer);

           // if the call succeeds, iterate through the structures
            if (resultEnum == NO_ERROR)
            {
                for (DWORD i = 0; i < entries; ++i)
                {
                    resourceManager.AddNetResource(&pNRLocal[i]);

                    // if the net resource structure is a container resource, call the EnumerateFunc function recursively
                    if (RESOURCEUSAGE_CONTAINER == (pNRLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER))
                        if (!EnumConnect(&pNRLocal[i], resourceManager))
                            TRACE("EnumerateFunc returned FALSE.");
                }
            }
            // process errors
            else
            if (resultEnum != ERROR_NO_MORE_ITEMS)
                break;
        }
        while (resultEnum != ERROR_NO_MORE_ITEMS);
    }
    catch (...)
    {
        // call the GlobalFree() function to free the memory
        if (pNRLocal)
            ::GlobalFree((HGLOBAL)pNRLocal);

        throw;
    }

    // call the GlobalFree function to free the memory
    ::GlobalFree((HGLOBAL)pNRLocal);

    // call WNetCloseEnum to end the enumeration.
    result = ::WNetCloseEnum(hEnum);

    return (result == NO_ERROR);
}
//---------------------------------------------------------------------------
