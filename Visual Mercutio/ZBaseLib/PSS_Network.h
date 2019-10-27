/****************************************************************************
 * ==> PSS_Network ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a network manager                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NetworkH
#define PSS_NetworkH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifndef _WIN32
    #include "winnet.h"
#endif

// processsoft
#include "PSS_NetResourceManager.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_MaxMNets = 5;
//---------------------------------------------------------------------------

/**
* Network manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Network
{
    public:
        PSS_Network();
        virtual ~PSS_Network();

        /**
        * Opens a network connection
        *@param path - network path
        *@param hWndOwner - owner window handle
        *@param temporarily - if true, the connection will be opened temporarily
        *@param interactive - if true, the connection will be interactive
        *@return true on success, otherwise false
        */
        virtual bool OpenConnection(const CString& path, HWND hWndOwner = NULL, bool temporarily = true, bool interactive = true);

        /**
        * Removes an existing connection
        *@param connection - the name of either the redirected local device or the remote network resource
        *                    to disconnect from. If specifies a redirected local resource, only the specified
        *                    redirection is broken. Otherwise, all connections to the remote network resource
        *                    are broken
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveConnection(const CString& connection);

        /**
        * Enumerates existing connections
        *@param resourceManager - resource manager
        *@return true on success, otherwise false
        */
        virtual bool EnumConnections(PSS_NetResourceManager& ResourceManager);

        /**
        * Gets all the free connections
        *@param freeConnectionArray - free connection array to populate with results
        *@return true on success, otherwise false
        */
        virtual bool GetFreeConnections(CStringArray& freeConnectionArray);

        /**
        * Gets the mapped or unmapped network drive. All local and floppy drives are not included
        *@param[out] driveArray - the drive array to populate with result
        *@return true on success, otherwise false
        */
        virtual bool GetNetworkDrives(CStringArray& driveArray) const;

        /**
        * Maps a connection
        *@param unc - unc drive name
        *@param local - local map name
        *@param canSpecifyUserName - if true, user name can be specified
        *@return true on success, otherwise false
        *@note If the local device is not specified, the function makes a connection to the network resource
        *      without redirecting a local device
        */
        virtual bool Map(const CString& unc, const CString& local = "", bool canSpecifyUserName = true);

        /**
        * Gets the unc (Universal Naming Conversion) name matching with a local map
        *@param local - local map name
        *@return matching unc name
        */
        virtual CString GetMap(const CString& local) const;

        /**
        * Gets the unc (Universal Naming Conversion) name
        *@param value - local map name
        *@return matching unc name
        */
        virtual CString GetUNC(const CString& value) const;

        /**
        * Gets the network error number
        *@return the network error number
        */
        virtual inline WORD GetNetworkErrorNo() const;

        /**
        * Gets the networks error message
        *@return the networks error message
        */
        virtual CString GetNetworkErrorMessage() const;

        /**
        * Gets the connected user name
        *@return the connected user name
        *@note If the user name is empty, check the error message
        */
        virtual CString GetUserName() const;

    private:
        static HANDLE m_Primary;
        static HANDLE m_hInstNetDriver;
        static HANDLE m_hInstWFWDriver;
        static HANDLE m_hInstMNet[g_MaxMNets];
        static int    m_MNets;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Network(const PSS_Network& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Network& operator = (const PSS_Network& other);

        /**
        * Checks if the window for multinet workgroups driver exists
        *@return TRUE if the window for multinet workgroups driver exists, otherwise FALSE
        */
        BOOL MNetDetect();

        /**
        * Checks if the window for workgroups multinet driver AND the windows for workgroups networking exist
        *@return TRUE if the window for workgroups multinet driver AND the windows for workgroups networking exist, otherwise FALSE
        */
        BOOL WFWDetect();

        /**
        * Gets the WFW Driver instance handle for MNet calls
        *@return the WFW Driver instance handle for MNet calls
        */
        HANDLE GetWFWNetDriverHandle() const;

        /**
        * Gets the MNet last target handle
        *@return the MNet last target handle
        */
        HANDLE GetLastTargetHandle() const;

        /**
        * Sets the MNet next target handle
        *@param hNetwork - network handle
        *@return the success or error code
        */
        WORD SetNextTargetHandle(HANDLE hNetwork);

        /**
        * Enumerates any multinet networks and fill in the MNet array instance handle
        *@return TRUE if some networks were found, FALSE if no networks was found
        */
        BOOL NetworkEnumAll();

        /**
        * Enumerates the existing connections
        *@param pNetResources - network resources
        *@param resourceManager - resource manager
        *@return true on success, otherwise false
        */
        bool EnumConnect(LPNETRESOURCE pNetResources, PSS_NetResourceManager& resourceManager);

        /**
        * Gets the MNets
        *@return the MNets
        */
        static inline const int GetMNets();

        /**
        * Sets the MNets
        *@param value - the MNets value
        */
        static inline void SetMNets(int value);

        /**
        * Gets the primary network handle
        *@return the primary network handle
        */
        static inline const HANDLE GetPrimary();

        /**
        * Sets the primary network handle
        *@param hHandle - the primary network handle
        */
        static inline void SetPrimary(HANDLE hHandle);

        /**
        * Gets the network driver instance
        *@return the network driver instance
        */
        static inline const HANDLE GethInstNetDriver();

        /**
        * Sets the network driver instance
        *@param hHandle - the network driver instance
        */
        static inline void SethInstNetDriver(HANDLE hHandle);

        /**
        * Gets the WFW network driver instance
        *@return the WFW network driver instance
        */
        static inline const HANDLE GethInstWFWDriver();

        /**
        * Sets the WFW network driver instance
        *@param hHandle - the WFW network driver instance
        */
        static inline void SethInstWFWDriver(HANDLE hHandle);
};

//---------------------------------------------------------------------------
// PSS_Network
//---------------------------------------------------------------------------
WORD PSS_Network::GetNetworkErrorNo() const
{
    INT error;

    #ifndef _WIN32
        // Calling WNetGetError at this point I am assuming that
        // a network error has indeed occured.
        WNetGetError(&error);
    #else
        DWORD errorCode;
        char  errorBuf[200];
        char  nameBuf[200];
        WNetGetLastError(&errorCode, errorBuf, sizeof(errorBuf), nameBuf, sizeof(nameBuf));

        // backward compatibility
        error = errorCode;
    #endif

    return error;
}
//---------------------------------------------------------------------------
const int PSS_Network::GetMNets()
{
    return m_MNets;
}
//---------------------------------------------------------------------------
void PSS_Network::SetMNets(int value)
{
    m_MNets = value;
}
//---------------------------------------------------------------------------
const HANDLE PSS_Network::GetPrimary()
{
    return m_Primary;
}
//---------------------------------------------------------------------------
void PSS_Network::SetPrimary(HANDLE hHandle)
{
    m_Primary = hHandle;
}
//---------------------------------------------------------------------------
const HANDLE PSS_Network::GethInstNetDriver()
{
    return m_hInstNetDriver;
}
//---------------------------------------------------------------------------
void PSS_Network::SethInstNetDriver(HANDLE hHandle)
{
    m_hInstNetDriver = hHandle;
}
//---------------------------------------------------------------------------
const HANDLE PSS_Network::GethInstWFWDriver()
{
    return m_hInstWFWDriver;
}
//---------------------------------------------------------------------------
inline void PSS_Network::SethInstWFWDriver(HANDLE hHandle)
{
    m_hInstWFWDriver = hHandle;
}
//---------------------------------------------------------------------------

#endif
