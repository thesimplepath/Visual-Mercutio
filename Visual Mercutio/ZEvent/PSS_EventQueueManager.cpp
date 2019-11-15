/****************************************************************************
 * ==> PSS_EventQueueManager -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an event queue manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventQueueManager.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
PSS_EventQueueManager::PSS_EventQueueManager()
{}
//---------------------------------------------------------------------------
PSS_EventQueueManager::~PSS_EventQueueManager()
{}
//---------------------------------------------------------------------------
BOOL PSS_EventQueueManager::Create(const CString& directory)
{
    if (directory.GetAt(directory.GetLength() - 1) == '\\')
        m_Directory = directory.Left(directory.GetLength() - 1);
    else
        m_Directory = directory;

    // make the queue directory lower case
    m_Directory.MakeLower();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventQueueManager::DispatchToEventQueue(const PSS_ActivityEvent& activityEvent)
{
    const CString fileName = BuildActivityEventFilename(activityEvent);
    m_ActivityEventFile.ExportActivityToFile(fileName, const_cast<PSS_ActivityEvent*>(&activityEvent));
    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_EventQueueManager::BuildActivityEventFilename(const PSS_ActivityEvent& activityEvent)
{
    CString file = m_Directory + "\\" + activityEvent.GetFileName() + activityEvent.GetFileExtension();
    int     index = 0;

    for (int i = 0; i < 20; ++i)
    {
        index = i;

        CFileStatus status;

        // check if the file exists
        if (CFile::GetStatus(file, status))
        {
            TRACE("SLEEP IN DISPATCH TO EVENT QUEUE");
            ::Sleep(100);
            continue;
        }

        break;
    }

    if (index < 20)
        return file;

    char fileBuffer[MAX_PATH];

    // if the file name already exists, select another one
    ::GetTempFileName(m_Directory, "Exp",  0,  fileBuffer);
    TRACE("TEMPORARY FILE CREATED");

    return fileBuffer;
}
//---------------------------------------------------------------------------
