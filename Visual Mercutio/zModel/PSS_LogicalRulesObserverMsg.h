/****************************************************************************
 * ==> PSS_LogicalRulesObserverMsg -----------------------------------------*
 ****************************************************************************
 * Description : Provides a logical rules observer message                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalRulesObserverMsgH
#define PSS_LogicalRulesObserverMsgH

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

// forward class declarations
class ZBRulesEntity;

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
const int g_InitRules    = 450;
const int g_RefreshRules = 451;
const int g_ClearRules   = 452;
const int g_CloseRules   = 453;
//---------------------------------------------------------------------------

/**
* Logical rules observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalRulesObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_LogicalRulesObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - the message identifier
        *@param pEntity - the entity
        *@param rootName - the root name
        */
        PSS_LogicalRulesObserverMsg(UINT           messageID = 0,
                                    ZBRulesEntity* pEntity   = NULL,
                                    const CString& rootName  = _T(""));

        virtual ~PSS_LogicalRulesObserverMsg();

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
        virtual inline ZBRulesEntity* GetEntity() const;

        /**
        * Sets the entity
        *@param pEntity - the entity
        */
        virtual inline void SetEntity(ZBRulesEntity* pEntity);

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
        ZBRulesEntity* m_pEntity;
        CString        m_RootName;
        UINT           m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_LogicalRulesObserverMsg
//---------------------------------------------------------------------------
UINT PSS_LogicalRulesObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
ZBRulesEntity* PSS_LogicalRulesObserverMsg::GetEntity() const
{
    return m_pEntity;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesObserverMsg::SetEntity(ZBRulesEntity* pEntity)
{
    m_pEntity = pEntity;
}
//---------------------------------------------------------------------------
CString PSS_LogicalRulesObserverMsg::GetRootName() const
{
    return m_RootName;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesObserverMsg::SetRootName(const CString& value)
{
    m_RootName = value;
}
//---------------------------------------------------------------------------

#endif
