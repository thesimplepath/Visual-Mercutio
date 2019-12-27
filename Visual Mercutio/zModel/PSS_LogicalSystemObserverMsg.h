/****************************************************************************
 * ==> PSS_LogicalSystemObserverMsg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system observer message                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalSystemObserverMsgH
#define PSS_LogicalSystemObserverMsgH

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
#ifndef PSS_SystemEntity
    #define PSS_SystemEntity ZBSystemEntity
#endif

// forward class declarations
class PSS_SystemEntity;

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
// Global constants
//---------------------------------------------------------------------------
const int g_InitLogicalSystem    = 200;
const int g_RefreshLogicalSystem = 201;
const int g_ClearLogicalSystem   = 202;
const int g_CloseLogicalSystem   = 203;
//---------------------------------------------------------------------------

/**
* Logical system observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalSystemObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_LogicalSystemObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - the message identifier
        *@param pEntity - the entity
        *@param rootName - the root name
        */
        PSS_LogicalSystemObserverMsg(UINT              messageID = 0,
                                     PSS_SystemEntity* pEntity   = NULL,
                                     const CString&    rootName  = _T(""));

        virtual ~PSS_LogicalSystemObserverMsg();

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
        * Gets the entity
        *@return the entity
        */
        virtual inline PSS_SystemEntity* GetEntity() const;

        /**
        * Sets the entity
        *@param pEntity - the entity
        */
        virtual inline void SetEntity(PSS_SystemEntity* value);

        /**
        * Gets the root name
        *@return the root name
        */
        virtual inline CString GetRootName() const;

        /**
        * Sets the root name
        *@param value - the root name
        */
        virtual inline void SetRootName(const CString value);

    private:
        PSS_SystemEntity* m_pEntity;
        CString           m_RootName;
        UINT              m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_LogicalSystemObserverMsg
//---------------------------------------------------------------------------
UINT PSS_LogicalSystemObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_LogicalSystemObserverMsg::GetEntity() const
{
    return m_pEntity;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemObserverMsg::SetEntity(PSS_SystemEntity* value)
{
    m_pEntity = value;
}
//---------------------------------------------------------------------------
CString PSS_LogicalSystemObserverMsg::GetRootName() const
{
    return m_RootName;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemObserverMsg::SetRootName(const CString value)
{
    m_RootName = value;
}
//---------------------------------------------------------------------------

#endif
