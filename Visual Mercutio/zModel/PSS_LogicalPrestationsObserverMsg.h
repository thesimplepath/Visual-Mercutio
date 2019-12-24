/****************************************************************************
 * ==> PSS_LogicalPrestationsObserverMsg -----------------------------------*
 ****************************************************************************
 * Description : Provides a logical prestation observer message             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalPrestationsObserverMsgH
#define PSS_LogicalPrestationsObserverMsgH

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

// forward class declaration
class ZBPrestationsEntity;

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
const int g_InitPrestations    = 400;
const int g_RrefrshPrestations = 401;
const int g_ClearPrestations   = 402;
const int g_ClosePrestations   = 403;
//---------------------------------------------------------------------------

/**
* Logical prestation observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalPrestationsObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_LogicalPrestationsObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - the message identifier
        *@param pEntity - the entity
        *@param rootName - the root name
        */
        PSS_LogicalPrestationsObserverMsg(UINT                 messageID = 0,
                                          ZBPrestationsEntity* pEntity   = NULL,
                                          const CString&       rootName  = _T(""));

        virtual ~PSS_LogicalPrestationsObserverMsg();

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
        virtual inline ZBPrestationsEntity* GetEntity() const;

        /**
        * Sets the entity
        *@param pEntity - the entity
        */
        virtual inline void SetEntity(ZBPrestationsEntity* pEntity);

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
        ZBPrestationsEntity* m_pEntity;
        CString              m_RootName;
        UINT                 m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_LogicalPrestationsObserverMsg
//---------------------------------------------------------------------------
UINT PSS_LogicalPrestationsObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
ZBPrestationsEntity* PSS_LogicalPrestationsObserverMsg::GetEntity() const
{
    return m_pEntity;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsObserverMsg::SetEntity(ZBPrestationsEntity* pEntity)
{
    m_pEntity = pEntity;
}
//---------------------------------------------------------------------------
CString PSS_LogicalPrestationsObserverMsg::GetRootName() const
{
    return m_RootName;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsObserverMsg::SetRootName(const CString& value)
{
    m_RootName = value;
}
//---------------------------------------------------------------------------

#endif
