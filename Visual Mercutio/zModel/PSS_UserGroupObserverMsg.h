/****************************************************************************
 * ==> PSS_UserGroupObserverMsg --------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group observer message                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserGroupObserverMsgH
#define PSS_UserGroupObserverMsgH

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
#include "zBaseLib\PSS_ObserverMsg.h"

// class name mapping
#ifndef PSS_UserEntity
    #define PSS_UserEntity ZBUserEntity
#endif

// forward class declarations
class PSS_UserEntity;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
const int g_InitUserGroup    = 100;
const int g_RefreshUserGroup = 101;
const int g_ClearUserGroup   = 102;
const int g_CloseUserGroup   = 103;
//---------------------------------------------------------------------------

/**
* User group observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserGroupObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_UserGroupObserverMsg)

    public:
        /**
        * Constructor
        *@param message - the message identifier
        *@param pEntity - the entity
        *@param rootName - the root name
        */
        PSS_UserGroupObserverMsg(UINT messageID = 0, PSS_UserEntity* pEntity = NULL, const CString& rootName = _T(""));

        virtual ~PSS_UserGroupObserverMsg();

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
        * Gets the identity
        *@return the identity
        */
        virtual inline PSS_UserEntity* GetEntity() const;

        /**
        * Sets the identity
        *@param value - the identity
        */
        virtual inline void SetEntity(ZBUserEntity* value);

        /**
        * Gets the root name
        *@return the root name
        */
        virtual inline CString GetRootName() const;

        /**
        * Sets the root name
        *@param value - the root name
        */
        virtual inline void SetRootName(const CString& value);

    private:
        PSS_UserEntity* m_pEntity;
        CString         m_RootName;
        UINT            m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_UserGroupObserverMsg
//---------------------------------------------------------------------------
UINT PSS_UserGroupObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_UserGroupObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupObserverMsg::GetEntity() const
{
    return m_pEntity;
}
//---------------------------------------------------------------------------
void PSS_UserGroupObserverMsg::SetEntity(ZBUserEntity* value)
{
    m_pEntity = value;
}
//---------------------------------------------------------------------------
CString PSS_UserGroupObserverMsg::GetRootName() const
{
    return m_RootName;
}
//---------------------------------------------------------------------------
void PSS_UserGroupObserverMsg::SetRootName(const CString& value)
{
    m_RootName = value;
}
//---------------------------------------------------------------------------

#endif
