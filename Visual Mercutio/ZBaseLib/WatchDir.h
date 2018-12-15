#if !defined(AFX_WATCHDIR_H__INCLUDED_)
#define AFX_WATCHDIR_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WatchDir.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZUWatchDirectory utility class


class AFX_EXT_CLASS ZUWatchDirectory : public CObject
{
public:
    enum    WatchingStatus {Stopped, 
                            Started, 
                            Paused
                            };
    enum    WatchingMode   {FileNameChange        = 0x0001, 
                            DirectoryNameChange = 0x0002, 
                            AttributesChange    = 0x0004,
                            SizesChange            = 0x0008,
                            LastWritesChange    = 0x0010,
                            SecurityChange        = 0x0020
                            };
    HANDLE    m_EventKill;

public:
    ZUWatchDirectory();
    ~ZUWatchDirectory();
    ZUWatchDirectory( const CString Directory, 
                      UINT Mode  = ZUWatchDirectory::FileNameChange | ZUWatchDirectory::LastWritesChange | ZUWatchDirectory::SizesChange,
                      BOOL SubTree = FALSE );
    BOOL Create( const CString Directory, 
                 UINT Mode  = ZUWatchDirectory::FileNameChange | ZUWatchDirectory::LastWritesChange | ZUWatchDirectory::SizesChange,
                 BOOL SubTree = FALSE );
    // NotifyClient is called every time the directory changed
    virtual    void    NotifyClient(){};
    // NotifyClient is called every time a file has been added 
    virtual    void    NotifyClientOnAdd(){};
    // NotifyClient is called every time a file has been removed 
    virtual    void    NotifyClientOnRemove(){};

    BOOL    SetDirectory( const CString Directory );

    BOOL    StartWatching( BOOL MustNotifyClient = TRUE );
    BOOL    PauseWatching();
    BOOL    ResumeWatching();
    BOOL    StopWatching();

    CString            GetDirectory() const { return m_Directory; };
    WatchingStatus    GetWatchingStatus() const { return m_WatchingStatus; };
    void            SetWatchingStatus(const WatchingStatus value ) { m_WatchingStatus = value; };
    UINT            GetWatchingMode() const { return m_WatchingMode; }
    BOOL            MustWatchSubTree() const { return m_WatchSubTree; };
    DWORD            GetNotifyFilter() const { return m_NotifyFilter; };
    int                RefreshFileList();

    BOOL            FileHaveBeenAdded() const { return m_FileHaveBeenAdded; };
    BOOL            FileHaveBeenRemoved() const { return m_FileHaveBeenRemoved; };
    // File Array functions
    BOOL            AddFile( const CString Filename );
    BOOL            RemoveFile( const CString Filename );
    BOOL            RemoveAllFiles();
    int                FileExists( const CString Filename );
    CString            GetFileAt( int Index  );
    int                GetSize();

    CMutex&            GetMutex() { return m_Mutex; };

    DECLARE_DYNAMIC( ZUWatchDirectory )


private:
    void    SetNotifyFilter();
    BOOL    CopyFilesArrayToTemporaryBuffer();

private:
    CString            m_Directory;
    WatchingStatus    m_WatchingStatus;
    UINT            m_WatchingMode;
    BOOL            m_WatchSubTree;
    HANDLE            m_ChangeHandle[1];
    DWORD            m_NotifyFilter;
    CWinThread*        m_pThread;
    CMutex            m_Mutex;
    CStringArray    m_FileArray;
    CStringArray    m_TemporaryFileArray;

    BOOL            m_FileHaveBeenAdded;
    BOOL            m_FileHaveBeenRemoved;

};

inline     CString        ZUWatchDirectory::GetFileAt( int Index  )
{
    if (Index < m_FileArray.GetSize())
        return m_FileArray.GetAt(Index);
    return "";
}

inline     int            ZUWatchDirectory::GetSize()
{
    return m_FileArray.GetSize();
}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATCHDIR_H__INCLUDED_)
