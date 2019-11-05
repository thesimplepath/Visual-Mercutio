// Source file: ActEvtMsgMgr.cpp

#include <StdAfx.h>
#include "ActEvtMsgMgr.h"

// processsoft
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"
#include "ActEvtFl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBActivityEventMessageManager 

ZBActivityEventMessageManager::ZBActivityEventMessageManager()
{}

ZBActivityEventMessageManager::~ZBActivityEventMessageManager()
{}

ZBEvent* ZBActivityEventMessageManager::LoadEventFromFile(const CString Filename)
{
    ZBEventActivityFile    EventActivityFile;
    ZBEvent*    pEvent = EventActivityFile.ImportActivityFromFile(Filename);
    if (pEvent &&
        pEvent->IsKindOf(RUNTIME_CLASS(PSS_ActivityEvent)) &&
        ((PSS_ActivityEvent*)pEvent)->GetActivityEventType() == PSS_ActivityEvent::IE_AT_Message)
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
