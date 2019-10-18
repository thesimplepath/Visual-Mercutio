// Source file: EventManager.cpp

#include <StdAfx.h>
#include "EventManager.h"

// processsoft
#include "zBaseLib\PSS_Directory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBEventManager 


ZBEventManager::ZBEventManager()
: m_IncludeSubDirectory(FALSE)
{
}

ZBEventManager::~ZBEventManager()
{
    RemoveAllEvents();
}

BOOL    ZBEventManager::Initialize( const CString Directory )
{
    m_RootDirectory = PSS_Directory::NormalizeDirectory( Directory );
    return PSS_Directory::Exist( m_RootDirectory );
}

BOOL    ZBEventManager::LoadFromDirectory( BOOL ClearAllFirst, BOOL IncludeSubDirectory )
{
    m_IncludeSubDirectory = IncludeSubDirectory;
    if (ClearAllFirst)
        RemoveAllEvents();
    LoadFromSubDirectory( m_RootDirectory );
    return GetEventCount() > 0;
}

BOOL    ZBEventManager::LoadFromDirectory( const CString Directory, BOOL ClearAllFirst, BOOL IncludeSubDirectory )
{
    m_RootDirectory = PSS_Directory::NormalizeDirectory( Directory );
    return LoadFromDirectory( ClearAllFirst, IncludeSubDirectory );
}

void    ZBEventManager::LoadFromSubDirectory( const CString Directory )
{
    // Run through the file list
    CFileFind finder;

    // build a string with wildcards
    CString strWildcard(Directory);
    strWildcard += _T("\\*.*");

    // start working for files
    BOOL bWorking = finder.FindFile(strWildcard);

    while (bWorking)
    {
        bWorking = finder.FindNextFile();

        // skip . and .. files; otherwise, we'd
        // recur infinitely!
        // Skip directory because only the current directory
        if (finder.IsDots())
         continue;


        // if it's a directory, recursively search it
        if (finder.IsDirectory())
        {
            if (!m_IncludeSubDirectory)
                continue;
            LoadFromSubDirectory(finder.GetFilePath());
            continue;
        }
   
        ZBEvent* pEvent = LoadEventFromFile( finder.GetFilePath() );
        if (pEvent)
            AddEvent( pEvent );
    }
    finder.Close();
}


BOOL    ZBEventManager::AddEvent( ZBEvent* pEvent )
{
    m_Events.Add( pEvent );
    return TRUE;
}

BOOL    ZBEventManager::RemoveEvent( ZBEvent* pEvent )
{
    for (int i = 0; i < m_Events.GetSize(); ++i)
    {
        if (pEvent == m_Events[i])
        {
            delete pEvent;
            pEvent = NULL;
            m_Events.RemoveAt(i);
            return TRUE;
        }
    }
    return FALSE;
}
BOOL    ZBEventManager::RemoveEventAt( int Index )
{
    if (Index < m_Events.GetSize())
        return FALSE;
    delete m_Events[Index];
    m_Events.RemoveAt(Index);
    return FALSE;
}
BOOL    ZBEventManager::RemoveAllEvents()
{
    // Deletes all events
    for (int i = 0; i < m_Events.GetSize(); ++i)
    {
        delete m_Events[i];
        m_Events[i] = NULL;
    }
    m_Events.RemoveAll();
    return TRUE;
}


