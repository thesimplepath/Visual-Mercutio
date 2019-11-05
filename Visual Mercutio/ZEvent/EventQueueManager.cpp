// Source file: EventQueueManager.cpp

#include <StdAfx.h>

#include "EventQueueManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBEventQueueManager 


ZBEventQueueManager::ZBEventQueueManager()
{}

ZBEventQueueManager::~ZBEventQueueManager()
{}

BOOL ZBEventQueueManager::Create(const CString Directory)
{
    if (Directory.GetAt(Directory.GetLength() - 1) == '\\')
        m_Directory = Directory.Left(Directory.GetLength() - 1);
    else
        m_Directory = Directory;

    // Make the queue directory lower case.
    m_Directory.MakeLower();

    return TRUE;
}

BOOL    ZBEventQueueManager::DispatchToEventQueue(PSS_ActivityEvent& EventActivity)
{
    CString    Filename = BuildActivityEventFilename(EventActivity);
    m_EventActivityFile.ExportActivityToFile(Filename, &EventActivity);
    return TRUE;
}
//---------------------------------------------------------------------------
CString ZBEventQueueManager::BuildActivityEventFilename(PSS_ActivityEvent& EventActivity)
{
    CString file = m_Directory + "\\" + EventActivity.GetFileName() + EventActivity.GetFileExtension();
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

    // if the filename already exists, choose another name
    ::GetTempFileName(m_Directory, // pointer to directory name for temporary file
                      "Exp",       // pointer to file name prefix
                      0,           // number used to create temporary file name
                      fileBuffer); // pointer to buffer that receives the new file name
    TRACE("TEMPORARY FILE CREATED");

    return fileBuffer;
}
//---------------------------------------------------------------------------
