/****************************************************************************
 * ==> PSS_ActivityToDoEventManager ----------------------------------------*
 ****************************************************************************
 * Description : Provides an activity todo event manager                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityToDoEventManager.h"

// processsoft
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"
#include "PSS_ActivityEventFile.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityToDoEventManager
//---------------------------------------------------------------------------
PSS_ActivityToDoEventManager::PSS_ActivityToDoEventManager()
{}
//---------------------------------------------------------------------------
PSS_ActivityToDoEventManager::PSS_ActivityToDoEventManager(const PSS_ActivityToDoEventManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityToDoEventManager::~PSS_ActivityToDoEventManager()
{}
//---------------------------------------------------------------------------
const PSS_ActivityToDoEventManager& PSS_ActivityToDoEventManager::operator = (const PSS_ActivityToDoEventManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Event* PSS_ActivityToDoEventManager::LoadEventFromFile(const CString& fileName)
{
    PSS_ActivityEventFile activityEventFile;
    PSS_Event*            pEvent         = activityEventFile.ImportActivityFromFile(fileName);
    PSS_ActivityEvent*    pActivityEvent = dynamic_cast<PSS_ActivityEvent*>(pEvent);

    if (pActivityEvent && pActivityEvent->GetActivityEventType() == PSS_ActivityEvent::IEType::IE_AT_ToDo)
    {
        const PSS_File file(fileName);
        const CString  path = PSS_Directory::NormalizeDirectory(file.GetFilePath());

        // if not in root directory
        if (path.CompareNoCase(GetRootDirectory()))
            // set the user queue name
            pEvent->SetUserQueue(PSS_Directory::GetShortDirectoryName(path));

        return pEvent;
    }

    return NULL;
}
//---------------------------------------------------------------------------
