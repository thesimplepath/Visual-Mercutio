/****************************************************************************
 * ==> PSS_WorkspaceObserverMsg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace observer message                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceObserverMsgH
#define PSS_WorkspaceObserverMsgH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Messages
//---------------------------------------------------------------------------
const int UM_INITWORKSPACE          = 100;
const int UM_REFRESHWORKSPACE       = 101;
const int UM_CLEARWORKSPACE         = 102;
const int UM_CLOSEWORKSPACE         = 103;
const int UM_ADDWORKSPACE_ENTITY    = 104;
const int UM_MODIFYWORKSPACE_ENTITY = 105;
const int UM_REMOVEWORKSPACE_ENTITY = 106;
//---------------------------------------------------------------------------

/**
* Workspace observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_WorkspaceObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - the message identifier
        *@param pEnv - the workspace environment, can be NULL
        */
        PSS_WorkspaceObserverMsg(UINT messageID = 0, PSS_WorkspaceEnv* pEnv = NULL);

        /**
        * Constructor
        *@param messageID - the message identifier
        *@param pEnv - the workspace environment, can be NULL
        *@param pEntity - the workspace entity, can be NULL
        */
        PSS_WorkspaceObserverMsg(UINT messageID, PSS_WorkspaceEnv* pEnv, PSS_WorkspaceEntity* pEntity);

        /**
        * Constructor
        *@param messageID - the message identifier
        *@param pEntity - the workspace entity, can be NULL
        */
        PSS_WorkspaceObserverMsg(UINT MessageID, PSS_WorkspaceEntity* pEntity);

        virtual ~PSS_WorkspaceObserverMsg();

        /**
        * Gets the message identifier
        *@return the message identifier
        */
        virtual inline UINT GetMessageID() const;

        /**
        * Sets the message identifier
        *@param value - the message identifier
        */
        virtual inline void SetMessageID(UINT value);

        /**
        * Gets the environment
        *@return the environment
        */
        virtual inline PSS_WorkspaceEnv* GetEnv() const;

        /**
        * Sets the environment
        *@param pEnv - the environment
        */
        virtual inline void SetEnv(PSS_WorkspaceEnv* pEnv);

        /**
        * Gets the entity
        *@return the entity
        */
        virtual inline PSS_WorkspaceEntity* GetEntity() const;

        /**
        * Sets the entity
        *@param pEntity - the entity
        */
        virtual inline void SetEntity(PSS_WorkspaceEntity* pEntity);

    private:
        PSS_WorkspaceEntity* m_pEntity;
        PSS_WorkspaceEnv*    m_pEnv;
        UINT                 m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceObserverMsg
//---------------------------------------------------------------------------
UINT PSS_WorkspaceObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
PSS_WorkspaceEnv* PSS_WorkspaceObserverMsg::GetEnv() const
{
    return m_pEnv;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceObserverMsg::SetEnv(PSS_WorkspaceEnv* pEnv)
{
    m_pEnv = pEnv;
}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceObserverMsg::GetEntity() const
{
    return m_pEntity;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceObserverMsg::SetEntity(PSS_WorkspaceEntity* pEntity)
{
    m_pEntity = pEntity;
}
//---------------------------------------------------------------------------

#endif
