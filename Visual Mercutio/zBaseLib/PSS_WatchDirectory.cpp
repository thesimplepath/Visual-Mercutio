/****************************************************************************
 * ==> PSS_WatchDirectory --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a directory monitor                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WatchDirectory.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_WatchDirectory
//---------------------------------------------------------------------------
UINT WorkerThreadProc(LPVOID pParam)
{
    PSS_WatchDirectory* pObject = (PSS_WatchDirectory*)pParam;

    // if object is not valid
    if (!pObject || !pObject->IsKindOf(RUNTIME_CLASS(PSS_WatchDirectory)))
        return 1;

    HANDLE changeHandle[2];

    // find the first change notification
    changeHandle[0] = ::FindFirstChangeNotification(pObject->GetDirectory(),
                                                    pObject->MustWatchSubTree(),
                                                    pObject->GetNotifyFilter());

    if (changeHandle[0] == INVALID_HANDLE_VALUE)
        return 1;

    // assign the event kill
    changeHandle[1] = pObject->GetEventKillHandle();

    while (true)
    {
        // wait for notification
        switch (::WaitForMultipleObjects(2, changeHandle, FALSE, 100))
        {
            case WAIT_OBJECT_0:
            {
                pObject->RefreshFileList();

                if (pObject->FileHaveBeenAdded())
                    pObject->NotifyClientOnAdd();

                if (pObject->FileHaveBeenRemoved())
                    pObject->NotifyClientOnRemove();

                pObject->NotifyClient();

                if (!::FindNextChangeNotification(changeHandle[0]))
                    return 1;

                break;
            }

            case WAIT_OBJECT_0 + 1:
                // end requested
                return 0;

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
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_WatchDirectory, CObject)
//---------------------------------------------------------------------------
// PSS_WatchDirectory
//---------------------------------------------------------------------------
PSS_WatchDirectory::PSS_WatchDirectory() :
    CObject(),
    m_EventKill(NULL),
    m_pThread(NULL),
    m_Mutex(FALSE, NULL),
    m_WatchingStatus(IEWatchingStatus::IE_WS_Stopped),
    m_Directory(""),
    m_WatchingMode((UINT)IEWatchingMode::IE_WM_FileNameChange   |
                   (UINT)IEWatchingMode::IE_WM_LastWritesChange |
                   (UINT)IEWatchingMode::IE_WM_SizesChange),
    m_NotifyFilter(0),
    m_WatchSubTree(FALSE),
    m_FileHaveBeenAdded(FALSE),
    m_FileHaveBeenRemoved(FALSE)
{
    m_ChangeHandle[0] = INVALID_HANDLE_VALUE;
    m_EventKill       = ::CreateEvent(NULL, TRUE, FALSE, NULL);

    SetNotifyFilter();
}
//---------------------------------------------------------------------------
PSS_WatchDirectory::PSS_WatchDirectory(const CString& directory, UINT mode, BOOL subTree) :
    m_EventKill(NULL),
    m_pThread(NULL),
    m_Mutex(FALSE, NULL),
    m_WatchingStatus(IEWatchingStatus::IE_WS_Stopped),
    m_Directory(directory),
    m_WatchingMode(mode),
    m_NotifyFilter(0),
    m_WatchSubTree(subTree),
    m_FileHaveBeenAdded(FALSE),
    m_FileHaveBeenRemoved(FALSE)
{
    m_ChangeHandle[0] = INVALID_HANDLE_VALUE;
    m_EventKill       = ::CreateEvent(NULL, TRUE, FALSE, NULL);

    SetNotifyFilter();
}
//---------------------------------------------------------------------------
PSS_WatchDirectory::~PSS_WatchDirectory()
{
    SetWatchingStatus(IEWatchingStatus::IE_WS_Stopped);
    SetEvent(m_EventKill);
    CloseHandle(m_EventKill);

    // if the thread is running or exists, delete it
    if (m_pThread)
        delete m_pThread;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::Create(const CString& directory, UINT mode, BOOL subTree)
{
    m_ChangeHandle[0] = INVALID_HANDLE_VALUE;
    m_Directory       = directory;
    m_WatchingStatus  = IEWatchingStatus::IE_WS_Stopped;
    m_WatchingMode    = mode;
    m_WatchSubTree    = subTree;

    SetNotifyFilter();
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WatchDirectory::NotifyClient()
{}
//---------------------------------------------------------------------------
void PSS_WatchDirectory::NotifyClientOnAdd()
{}
//---------------------------------------------------------------------------
void PSS_WatchDirectory::NotifyClientOnRemove()
{}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::SetDirectory(const CString& directory)
{
    m_Directory = directory;
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::StartWatching(BOOL mustNotifyClient)
{
    if (m_pThread)
        return FALSE;

    ResetEvent(m_EventKill);
    m_pThread = AfxBeginThread(WorkerThreadProc, this);

    if (m_pThread)
        m_pThread->ResumeThread();

    SetWatchingStatus(IEWatchingStatus::IE_WS_Started);

    // when the service starts, refresh the list and notify the client
    if (RefreshFileList() > 0)
        if (mustNotifyClient)
            NotifyClient();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::PauseWatching()
{
    if (GetWatchingStatus() != IEWatchingStatus::IE_WS_Started)
        return FALSE;

    if (m_pThread)
        m_pThread->SuspendThread();

    SetWatchingStatus(IEWatchingStatus::IE_WS_Paused);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::ResumeWatching()
{
    if (GetWatchingStatus() != IEWatchingStatus::IE_WS_Paused)
        return FALSE;

    if (m_pThread)
        m_pThread->ResumeThread();

    SetWatchingStatus(IEWatchingStatus::IE_WS_Started);

    if (RefreshFileList() > 0)
        NotifyClient();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::StopWatching()
{
    if (GetWatchingStatus() != IEWatchingStatus::IE_WS_Started)
        return FALSE;

    SetWatchingStatus(IEWatchingStatus::IE_WS_Stopped);

    // set thread priority to close it
    m_pThread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
    SetEvent(m_EventKill);

    m_pThread = NULL;
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_WatchDirectory::RefreshFileList()
{
    // reset flags
    m_FileHaveBeenAdded   = FALSE;
    m_FileHaveBeenRemoved = FALSE;

    if (!CopyFilesArrayToTemporaryBuffer())
        return 0;

    if (!RemoveAllFiles())
        return 0;

    CFileFind finder;
    int       fileCount = 0;

    // build a string with wildcards
    CString wildcard(m_Directory);
    wildcard += _T("\\*.*");

    // start working for files
    BOOL working = finder.FindFile(wildcard);

    while (working)
    {
        working = finder.FindNextFile();

        // skip . and .. files otherwise to avoid infinite recurrences. Also skip directory because
        // only the current directory should be processed
        if (finder.IsDots() || finder.IsDirectory())
            continue;

        AddFile(finder.GetFilePath());
        ++fileCount;
    }

    finder.Close();

    const register INT_PTR fileAddCount = m_FileArray.GetSize();

    // check for add file
    for (register INT_PTR sourceIndex = 0; sourceIndex < fileAddCount; ++sourceIndex)
    {
        register INT_PTR index = 0;

        for (register INT_PTR i = 0; i < m_TemporaryFileArray.GetSize(); ++i)
            if (m_TemporaryFileArray.GetAt(i) == m_FileArray.GetAt(sourceIndex))
            {
                index = i;
                break;
            }

        // if the file has not been found, set the flag for add
        if (index >= m_TemporaryFileArray.GetSize())
        {
            m_FileHaveBeenAdded = TRUE;
            break;
        }
    }

    const register INT_PTR fileRemCount = m_TemporaryFileArray.GetSize();

    // check for remove file
    for (register INT_PTR sourceIndex = 0; sourceIndex < fileRemCount; ++sourceIndex)
    {
        register INT_PTR index = 0;

        for (register INT_PTR i = 0; i < m_FileArray.GetSize(); ++i)
            if (m_FileArray.GetAt(i) == m_TemporaryFileArray.GetAt(sourceIndex))
            {
                index = i;
                break;
            }

        // if the file has not been found, set the flag for remove
        if (index >= m_FileArray.GetSize())
        {
            m_FileHaveBeenRemoved = TRUE;
            break;
        }
    }

    return fileCount;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::AddFile(const CString& fileName)
{
    // check if the file name exists
    if (FileExists(fileName) == -1)
    {
        CSingleLock sLock(&m_Mutex);
        sLock.Lock();

        // resource has been locked
        if (sLock.IsLocked())
        {
            m_FileArray.Add(fileName);

            // unlock the resource
            sLock.Unlock();
        }
        else
            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::RemoveFile(const CString& fileName)
{
    // get the file index
    const int index = FileExists(fileName);

    // check if the file name exists
    if (index != -1)
    {
        CSingleLock sLock(&m_Mutex);
        sLock.Lock();

        // resource has been locked
        if (sLock.IsLocked())
        {
            m_FileArray.RemoveAt(index);

            // unlock the resource
            sLock.Unlock();
            return TRUE;
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::RemoveAllFiles()
{
    CSingleLock sLock(&m_Mutex);
    sLock.Lock();

    // resource has been locked
    if (sLock.IsLocked())
    {
        m_FileArray.RemoveAll();

        // unlock the resource
        sLock.Unlock();
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
int PSS_WatchDirectory::FileExists(const CString& fileName) const
{
    const register int fileCount = m_FileArray.GetSize();

    for (register int i = 0; i < fileCount; ++i)
        if (fileName == m_FileArray.GetAt(i))
            return i;

    return -1;
}
//---------------------------------------------------------------------------
void PSS_WatchDirectory::SetNotifyFilter()
{
    // initialize notify filter
    m_NotifyFilter = 0;

    if (m_WatchingMode & (UINT)IEWatchingMode::IE_WM_FileNameChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_FILE_NAME;

    if (m_WatchingMode & (UINT)IEWatchingMode::IE_WM_DirectoryNameChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_DIR_NAME;

    if (m_WatchingMode & (UINT)IEWatchingMode::IE_WM_AttributesChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_ATTRIBUTES;

    if (m_WatchingMode & (UINT)IEWatchingMode::IE_WM_SizesChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_SIZE;

    if (m_WatchingMode & (UINT)IEWatchingMode::IE_WM_LastWritesChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_LAST_WRITE;

    if (m_WatchingMode & (UINT)IEWatchingMode::IE_WM_SecurityChange)
        m_NotifyFilter |= FILE_NOTIFY_CHANGE_SECURITY;
}
//---------------------------------------------------------------------------
BOOL PSS_WatchDirectory::CopyFilesArrayToTemporaryBuffer()
{
    CSingleLock sLock(&m_Mutex);
    sLock.Lock();

    // resource has been locked
    if (sLock.IsLocked())
    {
        m_TemporaryFileArray.RemoveAll();

        const int fileCount = m_FileArray.GetSize();

        for (int i = 0; i < fileCount; ++i)
            m_TemporaryFileArray.Add(m_FileArray.GetAt(i));

        // unlock the resource
        sLock.Unlock();
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
