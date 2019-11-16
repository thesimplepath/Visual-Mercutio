/****************************************************************************
 * ==> PSS_EventManager ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event manager                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventManager.h"

// std
#include <memory>

// processsoft
#include "zBaseLib\PSS_Directory.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_EventManager
//---------------------------------------------------------------------------
PSS_EventManager::PSS_EventManager() :
    m_IncludeSubDirectory(FALSE)
{}
//---------------------------------------------------------------------------
PSS_EventManager::~PSS_EventManager()
{
    RemoveAllEvents();
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::Initialize(const CString& directory)
{
    m_RootDirectory = PSS_Directory::NormalizeDirectory(directory);
    return PSS_Directory::Exist(m_RootDirectory);
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::AddEvent(PSS_Event* pEvent)
{
    m_Events.Add(pEvent);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::RemoveEvent(PSS_Event* pEvent)
{
    const int eventCount = m_Events.GetSize();

    for (int i = 0; i < eventCount; ++i)
        if (pEvent == m_Events[i])
        {
            delete pEvent;
            m_Events.RemoveAt(i);
            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::RemoveEventAt(int index)
{
    if (index < m_Events.GetSize())
        return FALSE;

    delete m_Events[index];
    m_Events.RemoveAt(index);
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::RemoveAllEvents()
{
    const int eventCount = m_Events.GetSize();

    // delete all events
    for (int i = 0; i < eventCount; ++i)
    {
        delete m_Events[i];
        m_Events[i] = NULL;
    }

    m_Events.RemoveAll();
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::LoadFromDirectory(BOOL clearAllFirst, BOOL includeSubDirectory)
{
    m_IncludeSubDirectory = includeSubDirectory;

    if (clearAllFirst)
        RemoveAllEvents();

    LoadFromSubDirectory(m_RootDirectory);
    return GetEventCount() > 0;
}
//---------------------------------------------------------------------------
BOOL PSS_EventManager::LoadFromDirectory(const CString& directory, BOOL clearAllFirst, BOOL includeSubDirectory)
{
    m_RootDirectory = PSS_Directory::NormalizeDirectory(directory);
    return LoadFromDirectory(clearAllFirst, includeSubDirectory);
}
//---------------------------------------------------------------------------
void PSS_EventManager::LoadFromSubDirectory(const CString& directory)
{
    // build a string with wildcards
    CString wildcards(directory);
    wildcards += _T("\\*.*");

    CFileFind finder;

    // start working for files
    BOOL working = finder.FindFile(wildcards);

    // iterate through the file list
    while (working)
    {
        working = finder.FindNextFile();

        // skip . and .. files to avoid infinite recursion
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

        std::unique_ptr<PSS_Event> pEvent(LoadEventFromFile(finder.GetFilePath()));

        if (pEvent.get())
        {
            AddEvent(pEvent.get());
            pEvent.release();
        }
    }

    finder.Close();
}
//---------------------------------------------------------------------------
