/****************************************************************************
 * ==> PSS_StartSymbolBP ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a start symbol for banking process                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StartSymbolBPH
#define PSS_StartSymbolBPH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_StartSymbolBP
    #define PSS_StartSymbolBP ZBBPStartSymbol
#endif

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LogicalRulesEntity.h"
#include "PSS_UnitPropertiesBP.h"
#include "ZBProcRules.h"
#include "PSS_RulesPropertiesBP.h"
#include "ZBProcRisk.h"
#include "PSS_RiskPropertiesBP.h"
#include "ZVRiskTypeContainer.h"
#include "ZVRiskImpactContainer.h"
#include "ZVRiskProbabilityContainer.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Start symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StartSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_StartSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        */
        PSS_StartSymbolBP(const CString& name = _T(""));

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_StartSymbolBP(const PSS_StartSymbolBP& other);

        virtual ~PSS_StartSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_StartSymbolBP& operator = (const PSS_StartSymbolBP& other);

        /**
        * Creates the symbol component
        *@param name - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& name = _T(""));

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual CODComponent* Dup() const;

        /**
        * Copies the symbol definition only from another symbol
        *@param src - the source symbol to copy from
        */
        virtual void CopySymbolDefinitionFrom(const CODSymbolComponent& src);

        /**
        * Checks if this symbol is a start symbol
        *@return TRUE if this symbol is a start symbol, otherwise FALSE
        */
        virtual inline BOOL IsStart() const;

        /**
        * Checks if an item may be dropped on this symbol
        *@param pObj - the object to drop
        *@param point - the drop point in pixels
        *@return true if an item may be dropped on this symbol, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item on this symbol
        *@param pObj - the object to drop
        *@param point - the drop point in pixels
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Creates the symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

        /**
        * Fills an array with the symbol properties
        *@param[in, out] propSet - property set to fill with the symbol properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(ZBPropertySet& propSet, bool numericValues = false, bool groupValues = false);

        /**
        * Saves the changes to object properties
        *@param propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(ZBPropertySet& propSet);

        /**
        * Saves a symbol property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(ZBProperty& prop);

        /**
        * Checks the property value
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@return true on success, otherwise false
        */
        virtual bool CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int menuCmdID, ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Gets the attributes as a string
        *@param pAttributes - the attributes
        *@return the attributes as a string
        */
        virtual CString GetAttributeString(ZBPropertyAttributes* pAttributes) const;

        /**
        * Checks if the description area is included
        *@return true if the description area is included, otherwise false
        */
        virtual inline bool IncludeDescriptionArea() const;

        /**
        * Checks if the attribute area is included
        *@return true if the attribute area is included, otherwise false
        */
        virtual inline bool IncludeAttributeArea() const;

        /**
        * Checks if the symbol may contain units
        *@return true if the symbol may contain units, otherwise false
        */
        virtual inline bool HasUnit() const;

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetUnitName() const;

        /**
        * Sets the unit name
        *@param value - the unit name
        */
        virtual inline void SetUnitName(const CString& value);

        /**
        * Gets the unit cost
        *@return the unit cost
        */
        virtual inline float GetUnitCost() const;

        /**
        * Sets the unit cost
        *@param value - the unit cost
        */
        virtual inline void SetUnitCost(const float value);

        /**
        * Gets the unit GUID
        *@return the unit GUID
        */
        virtual inline CString GetUnitGUID() const;

        /**
        * Sets the unit GUID
        *@param value - the unit GUID
        */
        virtual inline void SetUnitGUID(const CString& value);

        /**
        * Checks if the process contains a rule
        *@param ruleName - the rule name to check
        *@return TRUE if the process contains the rule, otherwise FALSE
        */
        virtual BOOL ContainsRule(const CString& ruleName) const;

        /**
        * Gets the rules which are no longer synchronized with this process
        *@param[out] rulesList - the rules which are no longer synchronized with this process
        */
        virtual void CheckRulesSync(CStringArray& rulesList);

        /**
        * Gets the risk count
        *@return the risk count
        */
        virtual inline int GetRiskCount() const;

        /**
        * Gets the risk name at index
        *@param index - the index
        *@return the risk name, empty string if not found or on error
        */
        virtual inline CString GetRiskName(std::size_t index) const;

        /**
        * Sets the risk name at index
        *@param index - the index
        *@param value - the risk name
        */
        virtual inline void SetRiskName(std::size_t index, const CString& value);

        /**
        * Gets the risk description at index
        *@param index - the index
        *@return the risk description, empty string if not found or on error
        */
        virtual inline CString GetRiskDesc(std::size_t index) const;

        /**
        * Sets the risk description at index
        *@param index - the index
        *@param value - the risk description
        */
        virtual inline void SetRiskDesc(std::size_t index, const CString& value);

        /**
        * Gets the risk type at index
        *@param index - the index
        *@return the risk type, empty string if not found or on error
        */
        virtual CString GetRiskType(std::size_t index) const;

        /**
        * Sets the risk type at index
        *@param index - the index
        *@param value - the risk type
        */
        virtual inline void SetRiskType(std::size_t index, const CString& value);

        /**
        * Gets the risk impact at index
        *@param index - the index
        *@return the risk impact
        */
        virtual inline int GetRiskImpact(std::size_t index) const;

        /**
        * Sets the risk impact at index
        *@param index - the index
        *@param value - the risk impact
        */
        virtual inline void SetRiskImpact(std::size_t index, int value);

        /**
        * Gets the risk probability at index
        *@param index - the index
        *@return the risk probability
        */
        virtual inline int GetRiskProbability(std::size_t index) const;

        /**
        * Sets the risk probability at index
        *@param index - the index
        *@param value - the risk probability
        */
        virtual inline void SetRiskProbability(std::size_t index, int value);

        /**
        * Gets the risk severity at index
        *@param index - the index
        *@return the risk severity
        */
        virtual inline int GetRiskSeverity(std::size_t index) const;

        /**
        * Sets the risk severity at index
        *@param index - the index
        *@param value - the risk severity
        */
        virtual inline void SetRiskSeverity(std::size_t index, int value);

        /**
        * Gets the risk unitary estimation at index
        *@param index - the index
        *@return the risk unitary estimation
        */
        virtual inline float GetRiskUE(std::size_t index) const;

        /**
        * Sets the risk unitary estimation at index
        *@param index - the index
        *@param value - the risk unitary estimation
        */
        virtual inline void SetRiskUE(std::size_t index, float value);

        /**
        * Gets the risk annual operating loss (perte operationnelle annuelle in French) at index
        *@param index - the index
        *@return the risk annual operating loss
        */
        virtual inline float GetRiskPOA(std::size_t index) const;

        /**
        * Sets the risk annual operating loss (perte operationnelle annuelle in French) at index
        *@param index - the index
        *@param value - the risk annual operating loss
        */
        virtual inline void SetRiskPOA(std::size_t index, float value);

        /**
        * Gets the risk action at index
        *@param index - the index
        *@return the risk action
        */
        virtual inline bool GetRiskAction(std::size_t index) const;

        /**
        * Sets the risk action at index
        *@param index - the index
        *@param value - the risk action
        */
        virtual inline void SetRiskAction(std::size_t index, bool value);

        /**
        * Gets the unique object type identifier
        *@return the unique object type identifier
        */
        virtual inline int GetObjectTypeID() const;

        /**
        * Gets the right submenu resource index
        *@return the right submenu resource index
        */
        virtual inline int GetRightSubMenu() const;

        /**
        * Gets the icon resource index
        *@return the icon resource index
        */
        virtual inline int GetIconIndex() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Called after the property changed
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh);

        /**
        * Called when an internal property drag&drop occurred in the symbol
        *@param[in, out] srcProperty - the source property
        *@param[in, out] dstProperty - the destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param[in, out] props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(ZBProperty&    srcProperty,
                                                ZBProperty&    dstProperty,
                                                bool           top2Down,
                                                ZBPropertySet& props);

        /**
        * Called when the default attributes are filled
        *@param pAttributes - the attributes
        *@return true if the attributes were filled, otherwise false
        */
        virtual bool OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes);

        /**
        * Called when the attributes change
        *@param pAttributes - the attributes
        *@return true if the attributes changed, otherwise false
        */
        virtual bool OnChangeAttributes(ZBPropertyAttributes* pAttributes);

        /**
        * Called when the symbol is double clicked
        *@return TRUE if the double click was performed, otherwise FALSE
        */
        virtual BOOL OnDoubleClick();

        /**
        * Called when a tooltip is required
        *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
        *@param point - hit point
        *@param mode - tooltip mode
        *@return true if tooltip can be shown, otherwise false
        */
        virtual bool OnToolTip(CString&                   toolTipText,
                               const CPoint&              point,
                               PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

    protected:
        /**
        * Adds a new risk
        *@return the newly added risk index
        */
        virtual inline int AddNewRisk();

        /**
        * Deletes the risk at index
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteRisk(std::size_t index);

        /**
        * Called when a new risk is added
        *@param[in, out] prop - the property containing the risk
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        virtual void OnAddNewRisk(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a risk is deleted
        *@param[in, out] prop - the property containing the risk
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        virtual void OnDelCurrentRisk(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

    private:
        PSS_UnitPropertiesBP m_UnitProp;
        ZBProcRules          m_Rules;
        ZBProcRisk           m_Risks;

        /**
        * Gets the rule name by GUID
        *@param pRule - the rule for which the name should be get
        *@param ruleGUID - the rule GUID matching with the name to get
        *@return the rule name matching with the GUID
        */
        CString GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID);
};

//---------------------------------------------------------------------------
// PSS_StartSymbolBP
//---------------------------------------------------------------------------
BOOL PSS_StartSymbolBP::IsStart() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
bool PSS_StartSymbolBP::IncludeDescriptionArea() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_StartSymbolBP::IncludeAttributeArea() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_StartSymbolBP::HasUnit() const
{
    return true;
}
//---------------------------------------------------------------------------
CString PSS_StartSymbolBP::GetUnitName() const
{
    return m_UnitProp.GetUnitName();
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetUnitName(const CString& value)
{
    m_UnitProp.SetUnitName(value);
}
//---------------------------------------------------------------------------
float PSS_StartSymbolBP::GetUnitCost() const
{
    return m_UnitProp.GetUnitCost();
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetUnitCost(const float value)
{
    m_UnitProp.SetUnitCost(value);
}
//---------------------------------------------------------------------------
CString PSS_StartSymbolBP::GetUnitGUID() const
{
    return m_UnitProp.GetUnitGUID();
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetUnitGUID(const CString& value)
{
    m_UnitProp.SetUnitGUID(value);
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetRiskCount() const
{
    return m_Risks.GetRiskCount();
}
//---------------------------------------------------------------------------
CString PSS_StartSymbolBP::GetRiskName(std::size_t index) const
{
    return m_Risks.GetRiskName(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskName(std::size_t index, const CString& value)
{
    m_Risks.SetRiskName(index, value);
}
//---------------------------------------------------------------------------
CString PSS_StartSymbolBP::GetRiskDesc(std::size_t index) const
{
    return m_Risks.GetRiskDesc(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskDesc(std::size_t index, const CString& value)
{
    m_Risks.SetRiskDesc(index, value);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskType(std::size_t index, const CString& value)
{
    m_Risks.SetRiskType(index, value);
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetRiskImpact(std::size_t index) const
{
    return m_Risks.GetRiskImpact(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskImpact(std::size_t index, int value)
{
    m_Risks.SetRiskImpact(index, value);
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetRiskProbability(std::size_t index) const
{
    return m_Risks.GetRiskProbability(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskProbability(std::size_t index, int value)
{
    m_Risks.SetRiskProbability(index, value);
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetRiskSeverity(std::size_t index) const
{
    return m_Risks.GetRiskSeverity(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskSeverity(std::size_t index, int value)
{
    m_Risks.SetRiskSeverity(index, value);
}
//---------------------------------------------------------------------------
float PSS_StartSymbolBP::GetRiskUE(std::size_t index) const
{
    return m_Risks.GetRiskUE(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskUE(std::size_t index, float value)
{
    m_Risks.SetRiskUE(index, value);
}
//---------------------------------------------------------------------------
float PSS_StartSymbolBP::GetRiskPOA(std::size_t index) const
{
    return m_Risks.GetRiskPOA(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskPOA(std::size_t index, float value)
{
    m_Risks.SetRiskPOA(index, value);
}
//---------------------------------------------------------------------------
bool PSS_StartSymbolBP::GetRiskAction(std::size_t index) const
{
    return m_Risks.GetRiskAction(index);
}
//---------------------------------------------------------------------------
void PSS_StartSymbolBP::SetRiskAction(std::size_t index, bool value)
{
    m_Risks.SetRiskAction(index, value);
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetObjectTypeID() const
{
    return 0;
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetRightSubMenu() const
{
    return 4;
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::GetIconIndex() const
{
    return (IsLocal()) ? 10 : 18;
}
//---------------------------------------------------------------------------
int PSS_StartSymbolBP::AddNewRisk()
{
    return m_Risks.AddNewRisk();
}
//---------------------------------------------------------------------------
bool PSS_StartSymbolBP::DeleteRisk(std::size_t index)
{
    return m_Risks.DeleteRisk(index);
}
//---------------------------------------------------------------------------

#endif
