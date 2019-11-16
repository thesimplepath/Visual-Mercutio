/****************************************************************************
 * ==> PSS_ActivityMessageEventManager -------------------------------------*
 ****************************************************************************
 * Description : Provides an activity message event manager                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityMessageEventManager.h"

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
// PSS_ActivityMessageEventManager
//---------------------------------------------------------------------------
PSS_ActivityMessageEventManager::PSS_ActivityMessageEventManager()
{}
//---------------------------------------------------------------------------
PSS_ActivityMessageEventManager::PSS_ActivityMessageEventManager(const PSS_ActivityMessageEventManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityMessageEventManager::~PSS_ActivityMessageEventManager()
{}
//---------------------------------------------------------------------------
const PSS_ActivityMessageEventManager& PSS_ActivityMessageEventManager::operator = (const PSS_ActivityMessageEventManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Event* PSS_ActivityMessageEventManager::LoadEventFromFile(const CString& fileName)
{
    PSS_ActivityEventFile activityEventFile;
    PSS_Event*            pEvent(activityEventFile.ImportActivityFromFile(fileName));
    PSS_ActivityEvent*    pActivityEvent = dynamic_cast<PSS_ActivityEvent*>(pEvent);

    if (pActivityEvent && pActivityEvent->GetActivityEventType() == PSS_ActivityEvent::IE_AT_Message)
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
