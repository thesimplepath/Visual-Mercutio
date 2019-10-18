// Source file: ActEvtToDoMgr.cpp

#include <StdAfx.h>
#include "ActEvtToDoMgr.h"

// processsoft
#include "ActEvtFl.h"
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBActivityEventToDoManager 


ZBActivityEventToDoManager::ZBActivityEventToDoManager()
{
}

ZBActivityEventToDoManager::~ZBActivityEventToDoManager()
{
}


ZBEvent*    ZBActivityEventToDoManager::LoadEventFromFile( const CString Filename )
{
    ZBEventActivityFile    EventActivityFile;
    ZBEvent*    pEvent = EventActivityFile.ImportActivityFromFile( Filename );
    if (pEvent && 
        pEvent->IsKindOf(RUNTIME_CLASS(ZBEventActivity)) && 
        ((ZBEventActivity*)pEvent)->GetActivityEventType() == ToDoActivity)
    {
        PSS_File File(Filename);
        CString    Path = PSS_Directory::NormalizeDirectory( File.GetFilePath() );
        // If are not in root directory
        if (Path.CompareNoCase( GetRootDirectory() ) != 0)
        {
            // Set the user queue name
            pEvent->SetUserQueue(PSS_Directory::GetShortDirectoryName( Path ) );
        }
        return pEvent;
    }
    delete pEvent;
    return NULL;
}


