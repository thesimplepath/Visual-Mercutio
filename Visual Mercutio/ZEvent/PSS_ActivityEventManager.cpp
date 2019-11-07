/****************************************************************************
 * ==> PSS_ActivityEventManager --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event manager                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityEventManager.h"

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
// PSS_ActivityEventManager
//---------------------------------------------------------------------------
PSS_ActivityEventManager::PSS_ActivityEventManager()
{}
//---------------------------------------------------------------------------
PSS_ActivityEventManager::PSS_ActivityEventManager(const PSS_ActivityEventManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityEventManager::~PSS_ActivityEventManager()
{}
//---------------------------------------------------------------------------
const PSS_ActivityEventManager& PSS_ActivityEventManager::operator = (const PSS_ActivityEventManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_ActivityEventManager::AddEvent(PSS_ActivityEvent::IEType eventType,
                                                      const CString&            fileName,
                                                      const COleDateTime&       time,
                                                      const CString&            folderName,
                                                      const CString&            processName,
                                                      const COleDateTime&       processCreationDate,
                                                      const COleDateTime&       processDueDate,
                                                      const CString&            activityType,
                                                      const CString&            activityName,
                                                      const COleDateTime&       activityCreationDate,
                                                      const COleDateTime&       activityDueDate,
                                                      const CString&            sender,
                                                      const CString&            receiver,
                                                      const CString&            processFileName,
                                                      const CString&            exchangeDataFileName,
                                                      const CString&            processExchangeDataFileName,
                                                      const CString&            activityStatus,
                                                      const CString&            comments)
{
    PSS_ActivityEvent* pEvent = new PSS_ActivityEvent(eventType,
                                                      fileName,
                                                      time,
                                                      folderName,
                                                      processName,
                                                      processCreationDate,
                                                      processDueDate,
                                                      activityType,
                                                      activityName,
                                                      activityCreationDate,
                                                      activityDueDate,
                                                      sender,
                                                      receiver,
                                                      processFileName,
                                                      exchangeDataFileName,
                                                      processExchangeDataFileName,
                                                      activityStatus,
                                                      comments);

    if (!ZBEventManager::AddEvent(pEvent))
    {
        delete pEvent;
        pEvent = NULL;
    }

    return pEvent;
}
//---------------------------------------------------------------------------
PSS_Event* PSS_ActivityEventManager::LoadEventFromFile(const CString& fileName)
{
    PSS_ActivityEventFile activityEventFile;
    PSS_Event*            pEvent = activityEventFile.ImportActivityFromFile(fileName);

    if (pEvent)
    {
        const PSS_File file(fileName);
        const CString  path = PSS_Directory::NormalizeDirectory(file.GetFilePath());

        // if not in root directory
        if (path.CompareNoCase(GetRootDirectory()))
            // set the user queue name
            pEvent->SetUserQueue(PSS_Directory::GetShortDirectoryName(path));
    }

    return pEvent;
}
//---------------------------------------------------------------------------
