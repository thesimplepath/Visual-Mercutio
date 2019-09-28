// ZBWorkspaceObserverMsg.h: interface for the ZBWorkspaceObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWorkspaceObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBWorkspaceObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ObserverMsg.h"

// class name mapping
#ifndef PSS_WorkspaceEnv
    #define PSS_WorkspaceEnv ZBWorkspaceEnv
#endif
#ifndef PSS_WorkspaceEntity
    #define PSS_WorkspaceEntity ZBWorkspaceEntity
#endif

// forward declarations
class PSS_WorkspaceEnv;
class PSS_WorkspaceEntity;

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage de code inutile. (En commentaires)

const int UM_INITWORKSPACE = 100;
const int UM_REFRESHWORKSPACE = 101;
const int UM_CLEARWORKSPACE = 102;
const int UM_CLOSEWORKSPACE = 103;
const int UM_ADDWORKSPACE_ENTITY = 104;
const int UM_MODIFYWORKSPACE_ENTITY = 105;
const int UM_REMOVEWORKSPACE_ENTITY = 106;

class AFX_EXT_CLASS ZBWorkspaceObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBWorkspaceObserverMsg)

public:

    ZBWorkspaceObserverMsg(UINT MessageID = 0, PSS_WorkspaceEnv* pEnv = NULL);
    ZBWorkspaceObserverMsg(UINT MessageID, PSS_WorkspaceEnv* pEnv, PSS_WorkspaceEntity* pEntity);
    ZBWorkspaceObserverMsg(UINT MessageID, PSS_WorkspaceEntity* pEntity);
    virtual ~ZBWorkspaceObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID(UINT value)
    {
        m_MessageID = value;
    };

    PSS_WorkspaceEnv* GetpEnv() const
    {
        return m_pEnv;
    };

    void SetpEnv(PSS_WorkspaceEnv* value)
    {
        m_pEnv = value;
    };

    PSS_WorkspaceEntity* GetpEntity() const
    {
        return m_pEntity;
    };

    void SetpEntity(PSS_WorkspaceEntity* value)
    {
        m_pEntity = value;
    };

private:
    PSS_WorkspaceEntity* m_pEntity;
    PSS_WorkspaceEnv*   m_pEnv;
    UINT                m_MessageID;
};

#endif
