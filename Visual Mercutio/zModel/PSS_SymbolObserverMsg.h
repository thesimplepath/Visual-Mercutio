/****************************************************************************
 * ==> PSS_SymbolObserverMsg -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol observer message                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolObserverMsgH
#define PSS_SymbolObserverMsgH

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

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_SymbolObserverMsg)

    public:
        /**
        * Action type
        */
        enum IEActionType
        {
            IE_AT_None,
            IE_AT_ElementHasChanged,
            IE_AT_NameHasChanged,
            IE_AT_DescriptionHasChanged,
            IE_AT_ElementSelected
        };

        /**
        * Constructor
        *@param actionType - the action type
        *@param pElement - the element
        */
        PSS_SymbolObserverMsg(IEActionType actionType = IE_AT_None, CODComponent* pElement = NULL);

        /**
        * Constructor
        *@param symbolRef - the symbol reference number
        *@param actionType - the action type
        */
        PSS_SymbolObserverMsg(int symbolRef, IEActionType actionType = IE_AT_None);

        virtual ~PSS_SymbolObserverMsg();

        /**
        * Gets the action type
        *@return the action type
        */
        virtual inline IEActionType GetActionType() const;

        /**
        * Sets the action type
        *@param value - the action type
        */
        virtual inline void SetActionType(IEActionType value);

        /**
        * Gets the element
        *@return the element
        */
        virtual inline CODComponent* GetElement() const;

        /**
        * Sets the element
        *@param value - the element
        */
        virtual inline void SetElement(CODComponent* value);

        /**
        * Gets the symbol reference
        *@return the symbol reference
        */
        virtual inline int GetSymbolRef() const;

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        */
        virtual inline void SetSymbolRef(int value);

    private:
        CODComponent* m_pElement;
        IEActionType  m_ActionType;
        int           m_SymbolRef;
};

//---------------------------------------------------------------------------
// PSS_SymbolObserverMsg
//---------------------------------------------------------------------------
PSS_SymbolObserverMsg::IEActionType PSS_SymbolObserverMsg::GetActionType() const
{
    return m_ActionType;
}
//---------------------------------------------------------------------------
void PSS_SymbolObserverMsg::SetActionType(IEActionType value)
{
    m_ActionType = value;
}
//---------------------------------------------------------------------------
CODComponent* PSS_SymbolObserverMsg::GetElement() const
{
    return m_pElement;
}
//---------------------------------------------------------------------------
void PSS_SymbolObserverMsg::SetElement(CODComponent* pElement)
{
    m_pElement = pElement;
}
//---------------------------------------------------------------------------
int PSS_SymbolObserverMsg::GetSymbolRef() const
{
    return m_SymbolRef;
}
//---------------------------------------------------------------------------
void PSS_SymbolObserverMsg::SetSymbolRef(int value)
{
    m_SymbolRef = value;
}
//---------------------------------------------------------------------------

#endif
