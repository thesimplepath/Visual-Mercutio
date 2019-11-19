/****************************************************************************
 * ==> PSS_ServerEventManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a server event manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ServerEventManager.h"

// std
#include <memory>

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ServerEventManager
//---------------------------------------------------------------------------
PSS_ServerEventManager::PSS_ServerEventManager()
{}
//---------------------------------------------------------------------------
PSS_ServerEventManager::PSS_ServerEventManager(const PSS_ServerEventManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ServerEventManager::~PSS_ServerEventManager()
{}
//---------------------------------------------------------------------------
const PSS_ServerEventManager& PSS_ServerEventManager::operator = (const PSS_ServerEventManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
ZBEventServer* PSS_ServerEventManager::AddEvent(const COleDateTime& dateTime,
                                                const CString&      fileName,
                                                EventResult         eventResult)
{
    std::unique_ptr<ZBEventServer> pEvent(new ZBEventServer(dateTime, fileName, eventResult));

    if (!PSS_EventManager::AddEvent(pEvent.get()))
        return NULL;

    return pEvent.release();
}
//---------------------------------------------------------------------------
