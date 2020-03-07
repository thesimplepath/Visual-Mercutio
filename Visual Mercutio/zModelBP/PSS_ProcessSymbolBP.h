/****************************************************************************
 * ==> PSS_ProcessSymbolBP -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process symbol for banking process              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessSymbolBPH
#define PSS_ProcessSymbolBPH

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
#ifndef PSS_ProcessSymbolBP
    #define PSS_ProcessSymbolBP ZBBPProcessSymbol
#endif

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LogicalRulesEntity.h"
#include "PSS_SimPropertiesProcessBP.h"
#include "PSS_PrestationsPropertiesBP.h"
#include "PSS_ProcDeliveries.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_ProcRules.h"
#include "PSS_RulesPropertiesBP.h"
#include "PSS_ProcRisk.h"
#include "PSS_RiskPropertiesBP.h"
#include "PSS_RiskTypeContainer.h"
#include "PSS_RiskImpactContainer.h"
#include "PSS_RiskProbabilityContainer.h"

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
* Process symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_ProcessSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        */
        PSS_ProcessSymbolBP(const CString& name = _T(""));

        virtual ~PSS_ProcessSymbolBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessSymbolBP(const PSS_ProcessSymbolBP& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcessSymbolBP& operator = (const PSS_ProcessSymbolBP& other);

        /**
        * Adds a reference to this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE AddRef();

        /**
        * Releases a reference from this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE Release();

        /**
        * Creates the symbol component
        *@param name - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& name = _T(""));

        /**
        * Creates an empty child model
        *@param pParent - the parent
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateEmptyChildModel(CODModel* pParent);

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
        * Checks if this symbol is a process
        *@return TRUE if this symbol is a process, otherwise FALSE
        */
        virtual inline BOOL IsProcess() const;

        /**
        * Checks if the symbol can contain a child model
        *@return true if the symbol can contain a child model, otherwise false
        */
        virtual inline bool CanContainChildModel() const;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetSymbolName(const CString& value);

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
        * Creates the workflow activity
        *@param defaultProp - if true, the default property will be used
        *@return true on success, otherwise false
        */
        virtual bool CreateWorkflowActivity(bool defaultProp = true);

        /**
        * Sets the default property to the workflow activity
        *@return true on success, otherwise false
        */
        virtual bool SetDefaultPropertyToWorkflowActivity();

        /**
        * Gets the process workload forecast
        *@return the process workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcessWorkloadForecast();

        /**
        * Sets the process workload forecast
        *@param value - the process workload forecast value
        */
        virtual inline void SetProcessWorkloadForecast(const double value);

        /**
        * Sets the process workload forecast
        *@param prop - the property containing the process workload forecast value
        */
        virtual inline void SetProcessWorkloadForecast(PSS_AnnualNumberPropertiesBP& prop);

        /**
        * Gets the process cost forecast
        *@return the process cost forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcessCostForecast();

        /**
        * Sets the process cost forecast
        *@param value - the process cost forecast value
        */
        virtual inline void SetProcessCostForecast(const double value);

        /**
        * Sets the process cost forecast
        *@param prop - the property containing the process cost forecast value
        */
        virtual inline void SetProcessCostForecast(PSS_AnnualNumberPropertiesBP& prop);

        /**
        * Gets the HMO process cost
        *@return the HMO process cost
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcessCostHMO();

        /**
        * Sets the HMO process cost
        *@param value - the HMO process cost value
        */
        virtual inline void SetProcessCostHMO(const double value);

        /**
        * Sets the HMO process cost
        *@param value - the property containing the HMO process cost value
        */
        virtual inline void SetProcessCostHMO(PSS_AnnualNumberPropertiesBP& prop);

        /**
        * Checks if the process may contain prestations
        *@return true if the process may contain prestations, otherwise false
        */
        virtual inline bool HasPrestations() const;

        /**
        * Gets the prestations
        *@return the prestations
        */
        virtual PSS_Tokenizer GetPrestationsList();

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
        * Gets the deliveries
        *@return Gets the deliveries
        */
        virtual inline PSS_ProcDeliveries& GetDeliveries();

        /**
        * Gets the deliverie count
        *@return Gets the deliverie count
        */
        virtual inline int GetDeliveriesCount() const;

        /**
        * Gets the delivery at index
        *@param index - the index
        *@return the delivery, NULL if not found or on error
        */
        virtual inline PSS_DeliveriesPropertiesBP* GetDeliveryProperty(std::size_t index) const;

        /**
        * Gets the delivery name at index
        *@param index - the index
        *@return the delivery name, empty string if not found or on error
        */
        virtual inline CString GetDeliveryName(std::size_t index) const;

        /**
        * Sets the delivery name at index
        *@param index - the index
        *@param value - the delivery name
        */
        virtual inline void SetDeliveryName(std::size_t index, const CString& value);

        /**
        * Gets the delivery deliverables at index
        *@param index - the index
        *@return the delivery deliverables, empty string if not found or on error
        */
        virtual inline CString GetDeliveryDeliverables(std::size_t index) const;

        /**
        * Sets the delivery deliverables at index
        *@param index - the index
        *@param value - the delivery deliverables
        */
        virtual inline void SetDeliveryDeliverables(std::size_t index, const CString& value);

        /**
        * Adds a delivery deliverable at index
        *@param index - the index
        *@param value - the delivery deliverable to add
        *@return true on success, otherwise false
        */
        virtual inline bool AddDeliveryDeliverable(std::size_t index, const CString& value);

        /**
        * Removes a delivery deliverable at index
        *@param index - the index
        *@param value - the delivery deliverable to remove
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveDeliveryDeliverable(std::size_t index, const CString& value);

        /**
        * Removes all the delivery deliverables at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveAllDeliveryDeliverable(std::size_t index);

        /**
        * Gets the delivery quantity at index
        *@param index - the index
        *@return the delivery quantity
        */
        virtual inline float GetDeliveryQuantity(std::size_t index) const;

        /**
        * Sets the delivery quantity at index
        *@param index - the index
        *@param value - the delivery quantity
        */
        virtual inline void SetDeliveryQuantity(std::size_t index, const float value);

        /**
        * Gets the delivery percentage at index
        *@param index - the index
        *@return the delivery percentage
        */
        virtual inline float GetDeliveryPercentage(std::size_t index) const;

        /**
        * Sets the delivery percentage at index
        *@param index - the index
        *@param value - the delivery percentage
        */
        virtual inline void SetDeliveryPercentage(std::size_t index, const float value);

        /**
        * Gets the main delivery at index
        *@param index - the index
        *@return the main delivery, empty string if not found or on error
        */
        virtual inline CString GetDeliveryMain(std::size_t index) const;

        /**
        * Sets the main delivery at index
        *@param index - the index
        *@param value - the main delivery
        */
        virtual inline void SetDeliveryMain(std::size_t index, const CString& value);

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
        * Gets the unique object type identifier
        *@return the unique object type identifier
        */
        virtual inline int GetObjectTypeID() const;

        /**
        * Checks if a preview is shown
        *@return true if a preview is shown, otherwise false
        */
        virtual inline bool GetShowPreview() const;

        /**
        * Sets if a preview is shown
        *@param value - if true, a preview is shown
        */
        virtual inline void SetShowPreview(bool value);

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
        * Called after the symbol was created and before it's added on the model
        *@param pModel - the model containing the newly created symbol
        *@param pCtrl - the model controller
        *@return true if the symbol can be added on the model, false if the symbol should be destroyed immediatly
        */
        virtual bool OnPostCreation(CODModel* pModel = NULL, CODController* pCtrl = NULL);

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
        * Called when a deliverable name changed
        *@param oldName - the old name
        *@param newName - the new name
        */
        virtual void OnDeliverableNameChange(const CString& oldName, const CString& newName);

        /**
        * Called when a prestation is deleted
        *@param[in, out] prop - the property containing the prestation
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        virtual void OnDelCurrentPrestation(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when the symbol is double clicked
        *@return TRUE if the double click was performed, otherwise FALSE
        */
        virtual BOOL OnDoubleClick();

        /**
        * Called when the symbol is drawn
        *@param pDc - the device context to draw on
        */
        virtual void OnDraw(CDC* pDC);

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
        * Adjusts the element position
        */
        virtual void AdjustElementPosition();

    private:
        PSS_PrestationsPropertiesBP m_PrestProperties;
        PSS_SimPropertiesProcessBP  m_SimProperties;
        PSS_ProcDeliveries          m_Deliveries;
        PSS_ProcRules               m_Rules;
        PSS_ProcRisk                m_Risks;
        CRect                       m_CommentRect;
        bool                        m_IsUserModified;
        bool                        m_ShowPreview;

        /**
        * Gets the possible main deliverables list
        *@param propSet - the propertie set containing the deliverables
        *@param catID - the category identifier
        *@return the possible main deliverables list
        */
        CString GetPossibleListOfMainDeliverables(const ZBPropertySet& propSet, int catID) const;

        /**
        * Gets the available deliverables
        *@param propSet - the propertie set containing the deliverables
        *@return the avaliable deliverables
        */
        CString GetAvailableDeliverables(const ZBPropertySet& propSet) const;

        /**
        * Gets the deliverables in the children pages
        *@param[out] deliverableList - the deliverables found in children pages
        *@return the deliverables count
        */
        int GetDeliverablesInChildPages(CString& deliverableList) const;

        /**
        * Gets the main deliverable at index
        *@param index - the index
        *@return the main deliverable
        */
        CString CheckMainDeliverable(int index);

        /**
        * Checks the deliverables at index
        *@param index - the index
        *@return the main deliverable
        */
        CString CheckDeliverables(int index);

        /**
        * Updates the values for the delivery property at index
        *@param index - the index
        */
        void UpdateValuesForThisDeliveryProperty(std::size_t index);

        /**
        * Finds the quantity
        *@param main - the main deliverable name
        *@param pRootModel - the root model
        *@return the quantity
        */
        float FindQuantity(const CString& main, PSS_ProcessGraphModelMdlBP* pRootModel = NULL);

        /**
        * Calculates the delivery percentage
        *@param quantity - the quantity
        *@return the delivery percentage
        */
        inline float CalculateDeliveryPercentage(float quantity);

        /**
        * Calculates the sum of deliveries
        *@return the sum of deliveries
        */
        float CalculateSumOfDeliveries();

        /**
        * Gets the rule name by GUID
        *@param pRule - the rule for which the name should be get
        *@param ruleGUID - the rule GUID matching with the name to get
        *@return the rule name matching with the GUID
        */
        CString GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID);

        /**
        * Adds a new risk
        *@return the newly added risk index
        */
        inline int AddNewRisk();

        /**
        * Deletes the risk at index
        *@return true on success, otherwise false
        */
        inline bool DeleteRisk(std::size_t index);

        /**
        * Adds a new delivery
        *@return the newly added delivery index
        */
        inline int AddNewDelivery();

        /**
        * Deletes the delivery at index
        *@return true on success, otherwise false
        */
        inline bool DeleteDelivery(std::size_t index);

        /**
        * Called when a new risk is added
        *@param[in, out] prop - the property containing the risk
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        void OnAddNewRisk(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a risk is deleted
        *@param[in, out] prop - the property containing the risk
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        void OnDelCurrentRisk(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a new delivery is added
        *@param[in, out] prop - the property containing the delivery
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        void OnAddNewDelivery(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a delivery is deleted
        *@param[in, out] prop - the property containing the delivery
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        void OnDelCurrentDelivery(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);
};

//---------------------------------------------------------------------------
// PSS_ProcessSymbolBP
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_ProcessSymbolBP::AddRef()
{
    return CODSymbolComponent::AddRef();
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_ProcessSymbolBP::Release()
{
    return CODSymbolComponent::Release();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessSymbolBP::IsProcess() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::CanContainChildModel() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::IncludeDescriptionArea() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::IncludeAttributeArea() const
{
    return true;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcessSymbolBP::GetProcessWorkloadForecast()
{
    return m_SimProperties.GetProcessWorkloadForecast();
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetProcessWorkloadForecast(const double value)
{
    m_SimProperties.SetProcessWorkloadForecast(value);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetProcessWorkloadForecast(PSS_AnnualNumberPropertiesBP& prop)
{
    m_SimProperties.GetProcessWorkloadForecast() = prop;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcessSymbolBP::GetProcessCostForecast()
{
    return m_SimProperties.GetProcessCostForecast();
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetProcessCostForecast(const double value)
{
    m_SimProperties.SetProcessCostForecast(value);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetProcessCostForecast(PSS_AnnualNumberPropertiesBP& prop)
{
    m_SimProperties.GetProcessCostForecast() = prop;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcessSymbolBP::GetProcessCostHMO()
{
    return m_SimProperties.GetProcessCostHMO();
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetProcessCostHMO(const double value)
{
    m_SimProperties.SetProcessCostHMO(value);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetProcessCostHMO(PSS_AnnualNumberPropertiesBP& prop)
{
    m_SimProperties.GetProcessCostHMO() = prop;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::HasPrestations() const
{
    return true;
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetRiskCount() const
{
    return m_Risks.GetRiskCount();
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetRiskName(std::size_t index) const
{
    return m_Risks.GetRiskName(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskName(std::size_t index, const CString& value)
{
    m_Risks.SetRiskName(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetRiskDesc(std::size_t index) const
{
    return m_Risks.GetRiskDesc(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskDesc(std::size_t index, const CString& value)
{
    m_Risks.SetRiskDesc(index, value);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskType(std::size_t index, const CString& value)
{
    m_Risks.SetRiskType(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetRiskImpact(std::size_t index) const
{
    return m_Risks.GetRiskImpact(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskImpact(std::size_t index, int value)
{
    m_Risks.SetRiskImpact(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetRiskProbability(std::size_t index) const
{
    return m_Risks.GetRiskProbability(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskProbability(std::size_t index, int value)
{
    m_Risks.SetRiskProbability(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetRiskSeverity(std::size_t index) const
{
    return m_Risks.GetRiskSeverity(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskSeverity(std::size_t index, int value)
{
    m_Risks.SetRiskSeverity(index, value);
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::GetRiskUE(std::size_t index) const
{
    return m_Risks.GetRiskUE(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskUE(std::size_t index, float value)
{
    m_Risks.SetRiskUE(index, value);
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::GetRiskPOA(std::size_t index) const
{
    return m_Risks.GetRiskPOA(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskPOA(std::size_t index, float value)
{
    m_Risks.SetRiskPOA(index, value);
}
bool PSS_ProcessSymbolBP::GetRiskAction(std::size_t index) const
{
    return m_Risks.GetRiskAction(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetRiskAction(std::size_t index, bool value)
{
    m_Risks.SetRiskAction(index, value);
}
//---------------------------------------------------------------------------
PSS_ProcDeliveries& PSS_ProcessSymbolBP::GetDeliveries()
{
    return m_Deliveries;
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetDeliveriesCount() const
{
    return m_Deliveries.GetDeliveriesCount();
}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP* PSS_ProcessSymbolBP::GetDeliveryProperty(std::size_t index) const
{
    return m_Deliveries.GetProperty(index);
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetDeliveryName(std::size_t index) const
{
    return m_Deliveries.GetDeliveryName(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetDeliveryName(std::size_t index, const CString& value)
{
    m_Deliveries.SetDeliveryName(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetDeliveryDeliverables(std::size_t index) const
{
    return m_Deliveries.GetDeliveryDeliverables(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetDeliveryDeliverables(std::size_t index, const CString& value)
{
    m_Deliveries.SetDeliveryDeliverables(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::AddDeliveryDeliverable(std::size_t index, const CString& value)
{
    return m_Deliveries.AddDeliveryDeliverable(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::RemoveDeliveryDeliverable(std::size_t index, const CString& value)
{
    return m_Deliveries.RemoveDeliveryDeliverable(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::RemoveAllDeliveryDeliverable(std::size_t index)
{
    return m_Deliveries.RemoveAllDeliveryDeliverable(index);
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::GetDeliveryQuantity(std::size_t index) const
{
    return m_Deliveries.GetDeliveryQuantity(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetDeliveryQuantity(std::size_t index, const float value)
{
    m_Deliveries.SetDeliveryQuantity(index, value);
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::GetDeliveryPercentage(std::size_t index) const
{
    return m_Deliveries.GetDeliveryPercentage(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetDeliveryPercentage(std::size_t index, const float value)
{
    m_Deliveries.SetDeliveryPercentage(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetDeliveryMain(std::size_t index) const
{
    return m_Deliveries.GetDeliveryMain(index);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetDeliveryMain(std::size_t index, const CString& value)
{
    m_Deliveries.SetDeliveryMain(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetObjectTypeID() const
{
    return 3;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::GetShowPreview() const
{
    return m_ShowPreview;
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::SetShowPreview(bool value)
{
    m_ShowPreview = value;
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetRightSubMenu() const
{
    return 1;
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetIconIndex() const
{
    return (IsLocal() ? 5 : 13);
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::CalculateDeliveryPercentage(float quantity)
{
    const float sumOfDeliveries = CalculateSumOfDeliveries();

    if (!sumOfDeliveries)
        return 0.0f;

    return (quantity / sumOfDeliveries);
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::AddNewRisk()
{
    return m_Risks.AddNewRisk();
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::DeleteRisk(std::size_t index)
{
    return m_Risks.DeleteRisk(index);
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::AddNewDelivery()
{
    return m_Deliveries.AddNewDelivery();
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::DeleteDelivery(std::size_t index)
{
    return m_Deliveries.DeleteDelivery(index);
}
//---------------------------------------------------------------------------

#endif
