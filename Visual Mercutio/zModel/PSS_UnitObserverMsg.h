/****************************************************************************
 * ==> PSS_UnitObserverMsg -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an unit observer message                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitObserverMsgH
#define PSS_UnitObserverMsgH

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
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_Unit
    #define PSS_Unit ZBUnit
#endif
#ifndef PSS_UnitManager
    #define PSS_UnitManager ZBUnitManager
#endif

// forward class declarations
class PSS_Symbol;
class PSS_Unit;
class PSS_UnitManager;

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
* Unit observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UnitObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_UnitObserverMsg)

    public:
        /**
        * Action type
        */
        enum class IEActionType
        {
            IE_AT_None,
            IE_AT_OpenUnit,
            IE_AT_CloseUnit,
            IE_AT_ActivateUnit,
            IE_AT_AddElement,
            IE_AT_RemoveElement,
            IE_AT_ChangedElement
        };

        /**
        * Constructor
        *@param actionType - the action type
        *@param pUnitManager - the unit manager
        *@param pUnit - the unit
        *@param pElement - the owning symbol
        */
        PSS_UnitObserverMsg(IEActionType     actionType   = IEActionType::IE_AT_None,
                            PSS_UnitManager* pUnitManager = NULL,
                            PSS_Unit*        pUnit        = NULL,
                            PSS_Symbol*      pElement     = NULL);

        virtual ~PSS_UnitObserverMsg();

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
        * Gets the unit manager
        *@return the unit manager
        */
        virtual inline PSS_UnitManager* GetUnitManager() const;

        /**
        * Sets the unit manager
        *@param pManager - the unit manager
        */
        virtual inline void SetUnitManager(PSS_UnitManager* pManager);

        /**
        * Gets the unit
        *@return the unit
        */
        virtual inline PSS_Unit* GetUnit() const;

        /**
        * Sets the unit
        *@param pUnit - the unit
        */
        virtual inline void SetUnit(PSS_Unit* pUnit);

        /**
        * Gets the owning symbol element
        *@return the owning symbol element
        */
        virtual inline PSS_Symbol* GetElement() const;

        /**
        * Sets the owning symbol element
        *@param pSymbol - the owning symbol element
        */
        virtual inline void SetElement(PSS_Symbol* pSymbol);

    private:
        PSS_UnitManager* m_pUnitManager;
        PSS_Unit*        m_pUnit;
        PSS_Symbol*      m_pElement;
        IEActionType     m_ActionType;
};

//---------------------------------------------------------------------------
// PSS_UnitObserverMsg
//---------------------------------------------------------------------------
PSS_UnitObserverMsg::IEActionType PSS_UnitObserverMsg::GetActionType() const
{
    return m_ActionType;
}
//---------------------------------------------------------------------------
void PSS_UnitObserverMsg::SetActionType(IEActionType value)
{
    m_ActionType = value;
}
//---------------------------------------------------------------------------
PSS_UnitManager* PSS_UnitObserverMsg::GetUnitManager() const
{
    return m_pUnitManager;
}
//---------------------------------------------------------------------------
void PSS_UnitObserverMsg::SetUnitManager(PSS_UnitManager* pManager)
{
    m_pUnitManager = pManager;
}
//---------------------------------------------------------------------------
PSS_Unit* PSS_UnitObserverMsg::GetUnit() const
{
    return m_pUnit;
}
//---------------------------------------------------------------------------
void PSS_UnitObserverMsg::SetUnit(PSS_Unit* pUnit)
{
    m_pUnit = pUnit;
}
//---------------------------------------------------------------------------
PSS_Symbol* PSS_UnitObserverMsg::GetElement() const
{
    return m_pElement;
}
//---------------------------------------------------------------------------
void PSS_UnitObserverMsg::SetElement(PSS_Symbol* pSymbol)
{
    m_pElement = pSymbol;
}
//---------------------------------------------------------------------------

#endif
