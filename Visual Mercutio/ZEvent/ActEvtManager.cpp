// Source file: ActEvtManager.cpp

#include <StdAfx.h>
#include "ActEvtManager.h"

// processsoft
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"
#include "PSS_ActivityEventFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBActivityEventManager 


ZBActivityEventManager::ZBActivityEventManager()
{}

ZBActivityEventManager::~ZBActivityEventManager()
{}

PSS_ActivityEvent* ZBActivityEventManager::AddEvent(PSS_ActivityEvent::IEType EventType,
                                                    CString Filename,
                                                    COleDateTime Time,
                                                    CString FolderName,
                                                    CString ProcessName,
                                                    COleDateTime ProcessCreationDate,
                                                    COleDateTime ProcessDueDate,
                                                    CString ActivityType,
                                                    CString ActivityName,
                                                    COleDateTime ActivityCreationDate,
                                                    COleDateTime ActivityDueDate,
                                                    CString Sender,
                                                    CString Receiver,
                                                    CString ProcessFilename,
                                                    CString ExchangeDataFilename,
                                                    CString ProcessExchangeDataFilename,
                                                    CString ActivityStatus,
                                                    CString Comments)
{
    PSS_ActivityEvent* pEvent = new PSS_ActivityEvent(EventType,
                                                      Filename,
                                                      Time,
                                                      FolderName,
                                                      ProcessName,
                                                      ProcessCreationDate,
                                                      ProcessDueDate,
                                                      ActivityType,
                                                      ActivityName,
                                                      ActivityCreationDate,
                                                      ActivityDueDate,
                                                      Sender,
                                                      Receiver,
                                                      ProcessFilename,
                                                      ExchangeDataFilename,
                                                      ProcessExchangeDataFilename,
                                                      ActivityStatus,
                                                      Comments);
    if (!ZBEventManager::AddEvent(pEvent))
    {
        delete pEvent;
        pEvent = NULL;
    }
    return pEvent;
}

ZBEvent* ZBActivityEventManager::LoadEventFromFile(const CString fileName)
{
    PSS_ActivityEventFile activityEventFile;
    ZBEvent*              pEvent = activityEventFile.ImportActivityFromFile(fileName);

    if (pEvent)
    {
        PSS_File File(fileName);
        CString    Path = PSS_Directory::NormalizeDirectory(File.GetFilePath());
        // If are not in root directory
        if (Path.CompareNoCase(GetRootDirectory()) != 0)
        {
            // Set the user queue name
            pEvent->SetUserQueue(PSS_Directory::GetShortDirectoryName(Path));
        }
    }
    return pEvent;
}
