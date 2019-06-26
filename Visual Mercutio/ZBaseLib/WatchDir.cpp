// WatchDir.cpp : implementation file
//
#include "stdafx.h"
#include "WatchDir.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( ZUWatchDirectory, CObject )

UINT WorkerThreadProc( LPVOID pParam );


/////////////////////////////////////////////////////////////////////////////
// ZUWatchDirectory

ZUWatchDirectory::ZUWatchDirectory()
:     m_Directory( "" ),
    m_WatchingStatus( ZUWatchDirectory::Stopped ),
    m_WatchingMode( ZUWatchDirectory::FileNameChange | ZUWatchDirectory::LastWritesChange | ZUWatchDirectory::SizesChange ),
    m_WatchSubTree( FALSE ),
    m_pThread( NULL ),
    m_Mutex( FALSE, NULL ),
    m_FileHaveBeenAdded(FALSE),
    m_FileHaveBeenRemoved(FALSE)
{
    m_ChangeHandle[0] = INVALID_HANDLE_VALUE;
    m_EventKill = CreateEvent( NULL, TRUE, FALSE, NULL );
    SetNotifyFilter();
}

ZUWatchDirectory::ZUWatchDirectory( const CString Directory, UINT Mode, BOOL SubTree )
:     m_Directory( Directory ),
    m_WatchingStatus( ZUWatchDirectory::Stopped ),
    m_WatchingMode( Mode ),
    m_WatchSubTree( SubTree ),
    m_pThread( NULL ),
    m_Mutex( FALSE, NULL ),
    m_FileHaveBeenAdded(FALSE),
    m_FileHaveBeenRemoved(FALSE)
{
    m_ChangeHandle[0] = INVALID_HANDLE_VALUE;
    m_EventKill = CreateEvent( NULL, TRUE, FALSE, NULL );
    SetNotifyFilter();
}

ZUWatchDirectory::~ZUWatchDirectory()
{
    SetWatchingStatus( ZUWatchDirectory::Stopped );
    SetEvent( m_EventKill ); 
    CloseHandle( m_EventKill );
    // If the thread is running or exists, delete it
    if (m_pThread)
        delete m_pThread;
    m_pThread = NULL;
}

BOOL    ZUWatchDirectory::SetDirectory( const CString Directory )
{
    m_Directory = Directory;
    return TRUE;
}

BOOL    ZUWatchDirectory::Create( const CString Directory, UINT Mode, BOOL SubTree )
{
    m_Directory = Directory;
    m_WatchingStatus = ZUWatchDirectory::Stopped;
    m_WatchingMode = Mode;
    m_WatchSubTree = SubTree;
    m_ChangeHandle[0] = INVALID_HANDLE_VALUE;
    SetNotifyFilter();
    return TRUE;
}

BOOL    ZUWatchDirectory::StartWatching( BOOL MustNotifyClient )
{
    if (m_pThread)
        return FALSE;
    ResetEvent( m_EventKill );
    m_pThread = AfxBeginThread(WorkerThreadProc, this );
    if (m_pThread)
        m_pThread->ResumeThread();
    SetWatchingStatus( ZUWatchDirectory::Started );
    // When the service starts, refresh the list and notify the client
    if (RefreshFileList() > 0)
    {
        if (MustNotifyClient)
            NotifyClient();
    }
    return TRUE;
}

BOOL    ZUWatchDirectory::StopWatching()
{
    if (GetWatchingStatus() != ZUWatchDirectory::Started)
        return FALSE;
    SetWatchingStatus( ZUWatchDirectory::Stopped );
    // Set thread priority to close it.
    m_pThread->SetThreadPriority( THREAD_PRIORITY_ABOVE_NORMAL );
    SetEvent( m_EventKill ); 
    m_pThread = NULL;
    return TRUE;
}

BOOL    ZUWatchDirectory::PauseWatching()
{
    if (GetWatchingStatus() != ZUWatchDirectory::Started)
        return FALSE;
    if (m_pThread)
        m_pThread->SuspendThread();
    SetWatchingStatus( ZUWatchDirectory::Paused );
    return TRUE;
}

BOOL ZUWatchDirectory::ResumeWatching()
{
    if (GetWatchingStatus() != ZUWatchDirectory::Paused)
        return FALSE;
    if (m_pThread)
        m_pThread->ResumeThread();
    SetWatchingStatus( ZUWatchDirectory::Started );
    if (RefreshFileList() > 0)
        NotifyClient();
    return TRUE;
}

int ZUWatchDirectory::RefreshFileList()
{
    // Reset flags
    m_FileHaveBeenAdded = FALSE;
    m_FileHaveBeenRemoved = FALSE;

    if (!CopyFilesArrayToTemporaryBuffer())
        return 0;
    if (!RemoveAllFiles())
        return 0;

    CFileFind    finder;
    int            FileCounter = 0;

    // build a string with wildcards
    CString strWildcard(m_Directory);
    strWildcard += _T("\\*.*");

    // start working for files
    BOOL bWorking = finder.FindFile(strWildcard);

    while (bWorking)
    {
        bWorking = finder.FindNextFile();

        // skip . and .. files; otherwise, we'd
        // recur infinitely!
        // Skip directory because only the current directory
        if (finder.IsDots() ||
            finder.IsDirectory())
         continue;

        AddFile( finder.GetFilePath() );
        ++FileCounter;
    }

    finder.Close();

    // check for add file
    for (register INT_PTR sourceIndex = 0; sourceIndex < m_FileArray.GetSize(); ++sourceIndex)
    {
        register INT_PTR index = 0;

        for (register INT_PTR i = 0; i < m_TemporaryFileArray.GetSize(); ++i)
            if (m_TemporaryFileArray.GetAt(i) == m_FileArray.GetAt(sourceIndex))
            {
                index = i;
                break;
            }

        // if the file has not been found, Set the flag for add
        if (index >= m_TemporaryFileArray.GetSize())
        {
            m_FileHaveBeenAdded = TRUE;
            break;
        }
    }

    // check for remove file
    for (register INT_PTR sourceIndex = 0; sourceIndex < m_TemporaryFileArray.GetSize(); ++sourceIndex)
    {
        register INT_PTR index = 0;

        for (register INT_PTR i = 0; i < m_FileArray.GetSize(); ++i)
            if (m_FileArray.GetAt(i) == m_TemporaryFileArray.GetAt(sourceIndex))
            {
                index = i;
                break;
            }

        // if the file has not been found, Set the flag for add
        if (index >= m_FileArray.GetSize())
        {
            m_FileHaveBeenRemoved = TRUE;
            break;
        }
    }

    return FileCounter;
}

void ZUWatchDirectory::SetNotifyFilter()
{
    // Initialize notify filter
    m_NotifyFilter = 0;
    if (m_WatchingMode & FileNameChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_FILE_NAME;
    if (m_WatchingMode & DirectoryNameChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_DIR_NAME;
    if (m_WatchingMode & AttributesChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_ATTRIBUTES;
    if (m_WatchingMode & SizesChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_SIZE;
    if (m_WatchingMode & LastWritesChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_LAST_WRITE;
    if (m_WatchingMode & SecurityChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_SECURITY;
}


BOOL    ZUWatchDirectory::AddFile( const CString Filename )
{
    // Checks if the filename not already exists
    if (FileExists( Filename ) == -1)
    {
        CSingleLock sLock(&m_Mutex);
        sLock.Lock();
        if (sLock.IsLocked())  // Resource has been locked
        {
            m_FileArray.Add( Filename );
            // Unlock the resource
            sLock.Unlock();
        }
        else
            return FALSE;
    }
    return TRUE;
}
BOOL    ZUWatchDirectory::RemoveFile( const CString Filename )
{
    // Checks if the filename not already exists
    int        Index = FileExists( Filename );
    if (Index != -1)
    {
        CSingleLock sLock(&m_Mutex);
        sLock.Lock();
        if (sLock.IsLocked())  // Resource has been locked
        {
            m_FileArray.RemoveAt(Index);
            // Unlock the resource
            sLock.Unlock();
            return TRUE;
        }
    }
    return FALSE;
}

BOOL    ZUWatchDirectory::RemoveAllFiles()
{
    CSingleLock sLock(&m_Mutex);
    sLock.Lock();
    if (sLock.IsLocked())  // Resource has been locked
    {
        m_FileArray.RemoveAll();
        // Unlock the resource
        sLock.Unlock();
        return TRUE;
    }
    return FALSE;
}

int        ZUWatchDirectory::FileExists( const CString Filename )
{
    for (register int i = 0; i < m_FileArray.GetSize(); ++i)
        if (Filename == m_FileArray.GetAt(i))
            return i;
    return -1;
}

BOOL    ZUWatchDirectory::CopyFilesArrayToTemporaryBuffer()
{
    CSingleLock sLock(&m_Mutex);
    sLock.Lock();
    if (sLock.IsLocked())  // Resource has been locked
    {
        m_TemporaryFileArray.RemoveAll();
        for (int i = 0; i < m_FileArray.GetSize(); ++i)
            m_TemporaryFileArray.Add( m_FileArray.GetAt(i) );
        // Unlock the resource
        sLock.Unlock();
        return TRUE;
    }
    return FALSE;
}


UINT WorkerThreadProc( LPVOID pParam )
{
    ZUWatchDirectory* pObject = (ZUWatchDirectory*)pParam;    
    if (pObject == NULL || !pObject->IsKindOf(RUNTIME_CLASS(ZUWatchDirectory)))
        return 1;   // if pObject is not valid
    
    HANDLE    ChangeHandle[2];

    // Find the first change notification
    ChangeHandle[0] = FindFirstChangeNotification( pObject->GetDirectory(), pObject->MustWatchSubTree(), pObject->GetNotifyFilter() );
    if (ChangeHandle[0] == INVALID_HANDLE_VALUE)
        return 1;
    // Assigns the event kill
    ChangeHandle[1] = pObject->m_EventKill;

    DWORD    dwWaitStatus;
    while (true)
    {
        // Wait for notification. 
        dwWaitStatus = WaitForMultipleObjects(2, ChangeHandle, FALSE, 100);
        switch (dwWaitStatus)     
        {         
            case WAIT_OBJECT_0:
            {
                pObject->RefreshFileList();
                if (pObject->FileHaveBeenAdded())
                    pObject->NotifyClientOnAdd();
                if (pObject->FileHaveBeenRemoved())
                    pObject->NotifyClientOnRemove();
                pObject->NotifyClient();
                if (FindNextChangeNotification( ChangeHandle[0]) == FALSE) 
                    return 1;
                break;
            }
            case WAIT_OBJECT_0 + 1:
            {
                return 0;    // End requested
            }
            case WAIT_TIMEOUT:
                TRACE("NOTHING\n");
                break;
            default:             
                return 1;     
        }
    }
    TRACE("REQUEST TO STOP\n");
    return 0;
}
