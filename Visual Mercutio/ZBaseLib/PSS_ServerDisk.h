/****************************************************************************
 * ==> PSS_ServerDisk ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a server disk                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ServerDiskH
#define PSS_ServerDiskH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Server.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Server disk
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ServerDisk
{
    public:
        /**
        * Constructor
        *@param pServer - server
        *@param emptyImageServerIniFile - empty image server initialization file name
        */
        PSS_ServerDisk(PSS_Server* pServer = NULL, const CString& emptyImageServerIniFile = "");

        virtual ~PSS_ServerDisk();

        /**
        * Initializes the server disk
        *@param pServer - server
        *@param emptyImageServerIniFile - empty image server initialization file name
        */
        virtual void Initialize(PSS_Server* pServer, const CString& emptyImageServerIniFile = "");

        /**
        * Creates the server
        *@return true on success, otherwise false
        */
        virtual bool CreateServer();

        /**
        * Copies the server
        *@param sourceServer - source server to copy from
        *@return true on success, otherwise false
        */
        virtual bool CopyServer(PSS_Server& sourceServer);

        /**
        * Deletes the server
        *@param checkStructure - if true, the server structure will be checked
        *@return true on success, otherwise false
        */
        virtual bool DeleteServer(bool checkStructure = true);

        /**
        * Gets the server log
        *@return the server log
        */
        virtual inline CString GetLog();

    private:
        PSS_Server* m_pServer;
        PSS_Server  m_EmptyImageServer;
        CString     m_EmptyImageServerIniFile;
        CString     m_ServerCreationSuccess;
        CString     m_ServerCreationStart;
        CString     m_FailedToCreateServer;
        CString     m_FailedToCreateDir;
        CString     m_FailedToCopyFile;
        CString     m_FailedToInitializeParameters;
        CString     m_Log;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ServerDisk(const PSS_ServerDisk& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ServerDisk& operator = (const PSS_ServerDisk& other);

        /**
        * Creates the server directory structure
        *@return true on success, otherwise false
        */
        bool CreateServerDirectoryStructure();

        /**
        * Copies the server directory
        *@param sourceServer - source server to copy from
        *@return true on success, otherwise false
        */
        bool CopyServerDirectory(PSS_Server& SourceServer);
};

//---------------------------------------------------------------------------
// PSS_ServerDisk
//---------------------------------------------------------------------------
CString PSS_ServerDisk::GetLog()
{
    return m_Log;
}
//---------------------------------------------------------------------------

#endif
