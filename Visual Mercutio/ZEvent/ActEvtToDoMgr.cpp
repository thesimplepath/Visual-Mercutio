// Source file: ActEvtToDoMgr.cpp

#include <StdAfx.h>
#include "ActEvtToDoMgr.h"

// processsoft
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"
#include "PSS_ActivityEventFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBActivityEventToDoManager 


ZBActivityEventToDoManager::ZBActivityEventToDoManager()
{}

ZBActivityEventToDoManager::~ZBActivityEventToDoManager()
{}

PSS_Event* ZBActivityEventToDoManager::LoadEventFromFile(const CString Filename)
{
    PSS_ActivityEventFile activityEventFile;

    PSS_Event*    pEvent = activityEventFile.ImportActivityFromFile(Filename);
    if (pEvent &&
        pEvent->IsKindOf(RUNTIME_CLASS(PSS_ActivityEvent)) &&
        ((PSS_ActivityEvent*)pEvent)->GetActivityEventType() == PSS_ActivityEvent::IE_AT_ToDo)
    {
        PSS_File File(Filename);
        CString    Path = PSS_Directory::NormalizeDirectory(File.GetFilePath());
        // If are not in root directory
        if (Path.CompareNoCase(GetRootDirectory()) != 0)
        {
            // Set the user queue name
            pEvent->SetUserQueue(PSS_Directory::GetShortDirectoryName(Path));
        }
        return pEvent;
    }

    delete pEvent;
    return NULL;
}
