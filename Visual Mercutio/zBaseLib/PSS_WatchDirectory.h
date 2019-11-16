/****************************************************************************
 * ==> PSS_WatchDirectory --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a directory monitor                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WatchDirectoryH
#define PSS_WatchDirectoryH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Directory monitor, watches the changes done on a directory
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WatchDirectory : public CObject
{
    DECLARE_DYNAMIC(PSS_WatchDirectory)

    public:
        /**
        * Watching status
        */
        enum IEWatchingStatus
        {
            IE_WS_Stopped,
            IE_WS_Started,
            IE_WS_Paused
        };

        /**
        * Watching mode
        *@note These values may be combinated
        */
        enum IEWatchingMode
        {
            IE_WM_FileNameChange      = 0x0001,
            IE_WM_DirectoryNameChange = 0x0002,
            IE_WM_AttributesChange    = 0x0004,
            IE_WM_SizesChange         = 0x0008,
            IE_WM_LastWritesChange    = 0x0010,
            IE_WM_SecurityChange      = 0x0020
        };

        PSS_WatchDirectory();

        /**
        * Constructor
        *@param directory - directory to watch
        *@param mode - watch mode
        *@param subTree - if TRUE, the sub-trees will also be watched
        */
        PSS_WatchDirectory(const CString& directory,
                           UINT           mode    = IE_WM_FileNameChange | IE_WM_LastWritesChange | IE_WM_SizesChange,
                           BOOL           subTree = FALSE);

        virtual ~PSS_WatchDirectory();

        /**
        * Creates the watching dir
        *@param directory - directory to watch
        *@param mode - watch mode
        *@param subTree - if TRUE, the sub-trees will also be watched
        */
        virtual BOOL Create(const CString& directory,
                            UINT           mode    = IE_WM_FileNameChange | IE_WM_LastWritesChange | IE_WM_SizesChange,
                            BOOL           subTree = FALSE);

        /**
        * Called every time the directory changed
        */
        virtual void NotifyClient();

        /**
        * Called every time a file has been added 
        */
        virtual void NotifyClientOnAdd();

        /**
        * Called every time a file has been removed
        */
        virtual void NotifyClientOnRemove();

        /**
        * Sets the directory to watch
        *@param directory - directory to watch
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetDirectory(const CString& directory);

        /**
        * Starts to watch the directory
        *@param mustNotifyClient - if TRUE, client should be notified on change
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StartWatching(BOOL mustNotifyClient = TRUE);

        /**
        * Pauses the directory watching
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PauseWatching();

        /**
        * Resumes the directory watching
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ResumeWatching();

        /**
        * Stops the directory watching
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StopWatching();

        /**
        * Gets the watched directory
        *@return the watched directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Gets the watching status
        *@return the watching status
        */
        virtual inline IEWatchingStatus GetWatchingStatus() const;

        /**
        * Sets the watching status
        *@param value - the watching status
        */
        virtual inline void SetWatchingStatus(const IEWatchingStatus value);

        /**
        * Gets the watching mode
        *@return the watching mode
        */
        virtual inline UINT GetWatchingMode() const;

        /**
        * Gets if sub-trees should also be watched
        *@return TRUE if the sub-trees should also be watched, otherwise FALSE
        */
        virtual inline BOOL MustWatchSubTree() const;

        /**
        * Gets the notify filter
        *@return the notify filter
        */
        virtual inline DWORD GetNotifyFilter() const;

        /**
        * Refreshes the file list
        *@return file count
        */
        virtual int RefreshFileList();

        /**
        * Checks if files have been added
        *@return TRUE if files have been added, otherwise FALSE
        */
        virtual inline BOOL FileHaveBeenAdded() const;

        /**
        * Checks if files have been removed
        *@return TRUE if files have been removed, otherwise FALSE
        */
        virtual inline BOOL FileHaveBeenRemoved() const;

        /**
        * Adds a file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddFile(const CString& fileName);

        /**
        * Removes a file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFile(const CString& fileName);

        /**
        * Removes all the files
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveAllFiles();

        /**
        * Checks if a file exists
        *@param fileName - file name
        *@return the file index, -1 if not found or on error
        */
        virtual int FileExists(const CString& fileName) const;

        /**
        * Gets the file at index
        *@param index - index
        *@return the file at index, empty string if not found or on error
        */
        virtual inline CString GetFileAt(int index);

        /**
        * Gets the dir size
        *@return the dir size
        */
        virtual inline int GetSize();

        /**
        * Gets the mutex
        *@return the mutex
        */
        virtual inline CMutex& GetMutex();

        /**
        * Gets the event kill handle
        *@return the event kill handle
        */
        virtual inline HANDLE GetEventKillHandle() const;

    private:
        HANDLE           m_ChangeHandle[1];
        HANDLE           m_EventKill;
        CWinThread*      m_pThread;
        CMutex           m_Mutex;
        IEWatchingStatus m_WatchingStatus;
        CStringArray     m_FileArray;
        CStringArray     m_TemporaryFileArray;
        CString          m_Directory;
        UINT             m_WatchingMode;
        DWORD            m_NotifyFilter;
        BOOL             m_WatchSubTree;
        BOOL             m_FileHaveBeenAdded;
        BOOL             m_FileHaveBeenRemoved;

        /**
        * Sets the notify filter
        */
        void SetNotifyFilter();

        /**
        * Copy the file array to a temporary buffer
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CopyFilesArrayToTemporaryBuffer();
};

//---------------------------------------------------------------------------
// PSS_WatchDirectory
//---------------------------------------------------------------------------
CString PSS_WatchDirectory::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------
PSS_WatchDirectory::IEWatchingStatus PSS_WatchDirectory::GetWatchingStatus() const
{
    return m_WatchingStatus;
}
//---------------------------------------------------------------------------
void PSS_WatchDirectory::SetWatchingStatus(const IEWatchingStatus value)
{
    m_WatchingStatus = value;
}
//---------------------------------------------------------------------------
UINT PSS_WatchDirectory::GetWatchingMode() const
{
    return m_WatchingMode;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::MustWatchSubTree() const
{
    return m_WatchSubTree;
}
//---------------------------------------------------------------------------
DWORD PSS_WatchDirectory::GetNotifyFilter() const
{
    return m_NotifyFilter;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::FileHaveBeenAdded() const
{
    return m_FileHaveBeenAdded;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::FileHaveBeenRemoved() const
{
    return m_FileHaveBeenRemoved;
}
//---------------------------------------------------------------------------
CString PSS_WatchDirectory::GetFileAt(int index)
{
    if (index < m_FileArray.GetSize())
        return m_FileArray.GetAt(index);

    return "";
}
//---------------------------------------------------------------------------
int PSS_WatchDirectory::GetSize()
{
    return m_FileArray.GetSize();
}
//---------------------------------------------------------------------------
CMutex& PSS_WatchDirectory::GetMutex()
{
    return m_Mutex;
}
//---------------------------------------------------------------------------
HANDLE PSS_WatchDirectory::GetEventKillHandle() const
{
    return m_EventKill;
}
//---------------------------------------------------------------------------

#endif
