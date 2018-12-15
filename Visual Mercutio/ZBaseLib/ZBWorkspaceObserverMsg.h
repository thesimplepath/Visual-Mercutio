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

#include "ZIObserverMsg.h"

// forward declarations
class ZBWorkspaceEnv;
class ZBWorkspaceEntity;

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

const int UM_INITWORKSPACE            = 100;
const int UM_REFRESHWORKSPACE        = 101;
const int UM_CLEARWORKSPACE            = 102;
const int UM_CLOSEWORKSPACE            = 103;
const int UM_ADDWORKSPACE_ENTITY    = 104;
const int UM_MODIFYWORKSPACE_ENTITY = 105;
const int UM_REMOVEWORKSPACE_ENTITY = 106;

class AFX_EXT_CLASS ZBWorkspaceObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC( ZBWorkspaceObserverMsg )

public:

    ZBWorkspaceObserverMsg( UINT MessageID = 0, ZBWorkspaceEnv* pEnv = NULL );
    ZBWorkspaceObserverMsg( UINT MessageID, ZBWorkspaceEnv* pEnv, ZBWorkspaceEntity* pEntity );
    ZBWorkspaceObserverMsg( UINT MessageID, ZBWorkspaceEntity* pEntity );
    virtual ~ZBWorkspaceObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID( UINT value )
    {
        m_MessageID = value;
    };

    ZBWorkspaceEnv* GetpEnv() const
    {
        return m_pEnv;
    };

    void SetpEnv( ZBWorkspaceEnv* value )
    {
        m_pEnv = value;
    };

    ZBWorkspaceEntity* GetpEntity() const
    {
        return m_pEntity;
    };

    void SetpEntity( ZBWorkspaceEntity* value )
    {
        m_pEntity = value;
    };

private:

    UINT                m_MessageID;
    ZBWorkspaceEnv*        m_pEnv;
    ZBWorkspaceEntity*    m_pEntity;
};

#endif // !defined(AFX_ZBWorkspaceObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)