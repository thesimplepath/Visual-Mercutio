// Source file: ActEvtMsgMgr.cpp

#include <StdAfx.h>

#include "ActEvtMsgMgr.h"
#include "ActEvtFl.h"
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBActivityEventMessageManager 


ZBActivityEventMessageManager::ZBActivityEventMessageManager()
{
}

ZBActivityEventMessageManager::~ZBActivityEventMessageManager()
{
}


ZBEvent*    ZBActivityEventMessageManager::LoadEventFromFile( const CString Filename )
{
    ZBEventActivityFile    EventActivityFile;
    ZBEvent*    pEvent = EventActivityFile.ImportActivityFromFile( Filename );
    if (pEvent && 
        pEvent->IsKindOf(RUNTIME_CLASS(ZBEventActivity)) && 
        ((ZBEventActivity*)pEvent)->GetActivityEventType() == MessageActivity)
    {
        ZFile    File(Filename);
        CString    Path = ZDirectory::NormalizeDirectory( File.GetFilePath() );
        // If are not in root directory
        if (Path.CompareNoCase( GetRootDirectory() ) != 0)
        {
            // Set the user queue name
            pEvent->SetUserQueue( ZDirectory::GetShortDirectoryName( Path ) );
        }
        return pEvent;
    }
    delete pEvent;
    return NULL;
}


