// ZBBPProcedureSymbol.h: interface for the ZBBPProcedureSymbol class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPProcedureSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPProcedureSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LogicalRulesEntity.h"
#include "ZBProcCombinations.h"
#include "ZBBPSimPropProcedure.h"
#include "ZBBPUnitProp2.h"
#include "ZBBPCostPropProcedure2.h"
#include "ZBProcRules.h"
#include "ZBBPRulesProp.h"
#include "ZBProcRisk.h"
#include "ZBBPRiskProp.h"
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

// JMR-MODIF - Le 6 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBBPProcedureSymbol : public PSS_Symbol
{
    DECLARE_SERIAL(ZBBPProcedureSymbol)

public:

    ZBBPProcedureSymbol(const CString Name = _T(""));
    virtual ~ZBBPProcedureSymbol();

    /* Copy constructor. */
    ZBBPProcedureSymbol(const ZBBPProcedureSymbol& src);

    /* Assignment operator. */
    ZBBPProcedureSymbol& operator=(const ZBBPProcedureSymbol& src);

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Return the unique object type ID
    virtual int GetObjectTypeID() const
    {
        return 2;
    }

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom(CODSymbolComponent& src);

    // Overloaded to be able to modify the activity name
    // and description
    virtual BOOL SetSymbolName(const CString value);

    // Return true if the symbol can contain a child model
    virtual bool CanContainChildModel() const
    {
        return false;
    }

    // External file and external application methods
    virtual bool AcceptExtApp() const;

    // Let do the base class implementation
    //virtual bool DoInsertExtApp();
    virtual bool AcceptExtFile() const;

    // Let do the base class implementation
    //virtual bool DoInsertExtFile();

    ///////////////////////////////////////////////////////
    // Properties methods

    // Call when a new symbol is created
    virtual bool CreateSymbolProperties();

    // Call to retreive properties for the object
    virtual bool FillProperties(ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false);

    // Call to save new changes to object's properties
    virtual bool SaveProperties(ZBPropertySet& PropSet);

    // Called to save a property for the object
    virtual bool SaveProperty(ZBProperty& Property);

    // Called to check the property value
    virtual bool CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties);

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput(ZBProperty&        Property,
                                      CString&            value,
                                      ZBPropertySet&    Properties,
                                      bool&            Refresh);

    // Called to process the a menu command for the property value
    virtual bool ProcessMenuCommand(int            MenuCommand,
                                    ZBProperty&    Property,
                                    CString&        value,
                                    ZBPropertySet&    Properties,
                                    bool&            Refresh);

    // Called after the property changed
    virtual bool OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh);

    // Called when an internal drag&drop of property occured
    virtual bool OnDropInternalPropertyItem(ZBProperty&    SrcProperty,
                                            ZBProperty&    DstProperty,
                                            bool            Top2Down,
                                            ZBPropertySet&    Properties);

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes);
    virtual bool OnChangeAttributes(ZBPropertyAttributes* pAttributes);
    virtual CString GetAttributeString(ZBPropertyAttributes* pAttributes) const;

    /**
    * Called when a tooltip is required
    *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
    *@param point - hit point
    *@param mode - tooltip mode
    *@return true if tooltip can be shown, otherwise false
    */
    virtual bool OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

    // Drag and drop methods
    virtual bool AcceptDropItem(CObject* pObj, const CPoint& pt);
    virtual bool DropItem(CObject* pObj, const CPoint& pt);

    /* Creates the symbol component. */
    BOOL Create(const CString Name = _T(""));

    //////////////////////////////////////////////////////////////////////
    // Area state methods
    virtual bool IncludeDescriptionArea() const
    {
        // We would like to offer the description area
        return true;
    }

    virtual bool IncludeAttributeArea() const
    {
        // We would like to offer the attribute area
        return true;
    }

    //////////////////////////////////////////////////////////////////////
    // Call-back on symbols
    virtual void OnSymbolNameChanged(CODComponent& Comp, const CString OldName);

    virtual void OnDraw(CDC* pDC);

    ULONG STDMETHODCALLTYPE AddRef()
    {
        return CODSymbolComponent::AddRef();
    }

    ULONG STDMETHODCALLTYPE Release()
    {
        return CODSymbolComponent::Release();
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est une procédure.
    virtual BOOL IsProcedure()
    {
        return TRUE;
    }

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    virtual BOOL OnDoubleClick();

    // Update mecanism for symbol change
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    /* Called by the framework when a connection is created. */
    virtual void OnConnect(CODConnection* pConnection);

    //@cmember
    /* Called by the framework before a connection is destroyed. */
    virtual void OnDisconnect(CODConnection* pConnection);

    //@cmember
    /* Called by the framework when a connection moves. */
    virtual BOOL OnConnectionMove(CODConnection* pConnection);

    // Called by the link itself when disconnected
    virtual void OnLinkDisconnect(CODLinkComponent* pLink);

    // Get all entering up deliverables and store them in the parameter
    int     GetEnteringUpDeliverable(CString& EnteringDeliverables);
    int     GetEnteringUpDeliverable(CODEdgeArray& Edges);

    // Get all leaving down deliverables and store them in the parameter
    int     GetLeavingDownDeliverable(CString& LeavingDeliverables);
    int     GetLeavingDownDeliverable(CODEdgeArray& Edges);

    // Get all leaving right deliverables and store them in the parameter
    int     GetLeavingRightDeliverable(CString& LeavingDeliverables);
    int     GetLeavingRightDeliverable(CODEdgeArray& Edges);

    // Get all leaving left deliverables and store them in the parameter
    int     GetLeavingLeftDeliverable(CString& LeavingDeliverables);
    int     GetLeavingLeftDeliverable(CODEdgeArray& Edges);

    // Returns the combinations reference
    ZBProcCombinations& GetCombinations()
    {
        return m_Combinations;
    }

    // Add a new combination,
    // and return the index of the new added combination
    // Return -1 if the function fails
    int AddNewCombination()
    {
        return m_Combinations.AddNewCombination();
    }

    // Return the counter of combinations
    int GetCombinationCount() const
    {
        return m_Combinations.GetCombinationCount();
    }

    // Return the combination property at a specific index
    PSS_CombinationPropertiesBP* GetCombinationProperty(size_t Index) const
    {
        return m_Combinations.GetProperty(Index);
    }

    // Delete a combination
    bool DeleteCombination(size_t Index)
    {
        return m_Combinations.DeleteCombination(Index);
    }

    bool DeleteCombination(PSS_CombinationPropertiesBP* pProp)
    {
        return m_Combinations.DeleteCombination(pProp);
    }

    // Return true if the combination name already exists
    bool CombinationNameExist(const CString Name) const
    {
        return m_Combinations.CombinationNameExist(Name);
    }

    // Return the next valid name
    CString GetNextCombinationValidName() const
    {
        return m_Combinations.GetNextCombinationValidName();
    }

    // Build the string with all available deliverables
    CString GetAvailableDeliverables(const CString AllDeliverables) const
    {
        return m_Combinations.GetAvailableDeliverables(AllDeliverables);
    }

    // Build the string with all allocated deliverables
    CString GetAllocatedDeliverables() const
    {
        return m_Combinations.GetAllocatedDeliverables();
    }

    // Return true if a specific deliverable is in the specified string
    bool IsDeliverableInString(const CString Deliverables, const CString Value) const
    {
        return m_Combinations.IsDeliverableInString(Deliverables, Value);
    }

    // Return the right combination prop of a specific deliverable
    PSS_CombinationPropertiesBP* LocateCombinationOfDeliverable(const CString DeliverableName) const
    {
        return m_Combinations.LocateCombinationOfDeliverable(DeliverableName);
    }

    // Retrieve the right combination properties index containing a specific deliverable
    // if not found, return -1
    int LocateCombinationIndexOfDeliverable(const CString DeliverableName) const
    {
        return m_Combinations.LocateCombinationIndexOfDeliverable(DeliverableName);
    }

    // Replace an old deliverable by a new one
    // return true if done
    bool ReplaceDeliverable(const CString OldDeliverableName, const CString NewDeliverableName)
    {
        return m_Combinations.ReplaceDeliverable(OldDeliverableName, NewDeliverableName);
    }

    // Delete a deliverable from all combinations, including the master
    // return true if done
    bool DeleteDeliverableFromAllCombinations(const CString DeliverableName)
    {
        return m_Combinations.DeleteDeliverableFromAllCombinations(DeliverableName);
    }

    /* Gets the combination name at the specific Index. */
    CString GetCombinationName(size_t Index) const
    {
        return m_Combinations.GetCombinationName(Index);
    }

    //@cmember
    /* Sets the combination name at the specific Index. */
    void SetCombinationName(size_t Index, CString Value)
    {
        m_Combinations.SetCombinationName(Index, Value);
    }

    //@cmember
    /* Gets the list of deliberables at the specific Index. */
    CString GetCombinationDeliverables(size_t Index) const
    {
        return m_Combinations.GetCombinationDeliverables(Index);
    }

    //@cmember
    /* Sets the list of deliberables at the specific Index. */
    void SetCombinationDeliverables(size_t Index, CString Value)
    {
        m_Combinations.SetCombinationDeliverables(Index, Value);
    }

    //@cmember
    /* Add a deliverable to the list of deliberables at the specific Index. */
    bool AddCombinationDeliverable(size_t Index, CString Value)
    {
        return m_Combinations.AddCombinationDeliverable(Index, Value);
    }

    //@cmember
    /* Remove a deliverable to the list of deliberables at the specific Index. */
    bool RemoveCombinationDeliverable(size_t Index, CString Value)
    {
        return m_Combinations.RemoveCombinationDeliverable(Index, Value);
    }

    //@cmember
    /* Remove all deliverables to the list of deliberables at the specific Index. */
    bool RemoveAllCombinationDeliverable(size_t Index)
    {
        return m_Combinations.RemoveAllCombinationDeliverable(Index);
    }

    //@cmember
    /* Gets the combination percentage at the specific Index. */
    float GetCombinationActivationPerc(size_t Index) const
    {
        return m_Combinations.GetCombinationActivationPerc(Index);
    }

    //@cmember
    /* Sets the combination percentage at the specific Index. */
    void SetCombinationActivationPerc(size_t Index, const float value)
    {
        m_Combinations.SetCombinationActivationPerc(Index, value);
    }

    /* Gets the combination master name at the specific Index. */
    CString GetCombinationMaster(size_t Index) const
    {
        return m_Combinations.GetCombinationMaster(Index);
    }

    //@cmember
    /* Sets the combination master name at the specific Index. */
    void SetCombinationMaster(size_t Index, CString Value)
    {
        m_Combinations.SetCombinationMaster(Index, Value);
    }

    // Calculate the procedure activation based on combinations
    PSS_AnnualNumberPropertiesBP CalculateProcedureActivation();

    // Attributes
    //@cmember
    /* Gets and Sets the cost multiplier factor. */
    float GetMultiplier() const
    {
        return m_CostProcedureProp.GetMultiplier();
    }

    void SetMultiplier(const float value)
    {
        m_CostProcedureProp.SetMultiplier(value);
    }

    //@cmember
    /* Gets and Sets the processing time. */
    double GetProcessingTime() const
    {
        return m_CostProcedureProp.GetProcessingTime();
    }

    void SetProcessingTime(const double value)
    {
        m_CostProcedureProp.SetProcessingTime(value);
    }

    //@cmember
    /* Gets and Sets the unitary cost. */
    float GetUnitaryCost() const
    {
        return m_CostProcedureProp.GetUnitaryCost();
    }

    void SetUnitaryCost(const float value)
    {
        m_CostProcedureProp.SetUnitaryCost(value);
    }

    //@cmember
    /* Gets and Sets the processing duration. */
    double GetProcessingDuration() const
    {
        return m_CostProcedureProp.GetProcessingDuration();
    }

    void SetProcessingDuration(const double value)
    {
        m_CostProcedureProp.SetProcessingDuration(value);
    }

    //@cmember
    /* Gets and Sets the processing duration maximum. */
    double GetProcessingDurationMax() const
    {
        return m_CostProcedureProp.GetProcessingDurationMax();
    }

    void SetProcessingDurationMax(const double value)
    {
        m_CostProcedureProp.SetProcessingDurationMax(value);
    }

    //////////////////////////////////////////////////////////////////////
    // Unit methods
    virtual bool HasUnit() const
    {
        return true;
    }

    virtual CString GetUnitName() const
    {
        return m_UnitProp.GetUnitName();
    }

    void SetUnitName(const CString value)
    {
        m_UnitProp.SetUnitName(value);
    }

    float GetUnitCost() const
    {
        return m_UnitProp.GetUnitCost();
    }

    void SetUnitCost(const float value)
    {
        m_UnitProp.SetUnitCost(value);
    }

    virtual CString GetUnitGUID() const
    {
        return m_UnitProp.GetUnitGUID();
    }

    void SetUnitGUID(const CString value)
    {
        m_UnitProp.SetUnitGUID(value);
    }

    int GetUnitDoubleValidationType() const
    {
        return m_UnitProp.GetUnitDoubleValidationType();
    }

    void SetUnitDoubleValidationType(const int value)
    {
        m_UnitProp.SetUnitDoubleValidationType(value);
    }

    void GetUnitDoubleValidationTypeStringArray(CStringArray& sar) const
    {
        m_UnitProp.GetUnitDoubleValidationTypeStringArray(sar);
    }

    int ConvertUnitDoubleValidationString2Type(const CString Type) const
    {
        return m_UnitProp.ConvertUnitDoubleValidationString2Type(Type);
    }

    CString GetUnitDoubleValidationTypeString(const int Value) const
    {
        return m_UnitProp.GetUnitDoubleValidationTypeString(Value);
    }

    // Rule list methods
    CString GetRuleList() const;
    void SetRuleList(const CString Value);
    bool RuleExist(const CString Value);
    void AddRule(const CString Value);
    void RemoveRule(const CString Value);
    CString GetRuleAt(size_t Index);
    size_t GetRuleCount() const;

    void RemoveAllRules()
    {
        SetRuleList(_T(""));
    }

    // Task list methods
    CString GetTaskList() const;
    void SetTaskList(const CString Value);
    bool TaskExist(const CString Value);
    void AddTask(const CString Value);
    void RemoveTask(const CString Value);
    CString GetTaskAt(size_t Index);
    size_t GetTaskCount() const;

    void RemoveAllTasks()
    {
        SetTaskList(_T(""));
    }

    // Decision list methods
    CString GetDecisionList() const;
    void SetDecisionList(const CString Value);
    bool DecisionExist(const CString Value);
    void AddDecision(const CString Value);
    void RemoveDecision(const CString Value);
    CString GetDecisionAt(size_t Index);
    size_t GetDecisionCount() const;

    void RemoveAllDecisions()
    {
        SetDecisionList(_T(""));
    }

    //@cmember
    /* Gets the procedure activation. */
    PSS_AnnualNumberPropertiesBP& GetProcedureActivation();

    //@cmember
    /* Sets the procedure activation. */
    void SetProcedureActivation(const double value);
    void SetProcedureActivation(PSS_AnnualNumberPropertiesBP& AnnualNumberProp);

    //@cmember
    /* Gets the standard procedure time. */
    PSS_AnnualNumberPropertiesBP& GetProcedureCost();

    //@cmember
    /* Sets the standard procedure time. */
    void SetProcedureCost(const double value);
    void SetProcedureCost(PSS_AnnualNumberPropertiesBP& AnnualNumberProp);

    //@cmember
    /* Gets the procedure workload forecast. */
    PSS_AnnualNumberPropertiesBP& GetProcedureWorkloadForecast();

    //@cmember
    /* Sets the procedure workload forecast. */
    void SetProcedureWorkloadForecast(const double value);
    void SetProcedureWorkloadForecast(PSS_AnnualNumberPropertiesBP& AnnualNumberProp);

    //@cmember
    /* Gets the procedure cost forecast. */
    PSS_AnnualNumberPropertiesBP& GetProcedureCostForecast();

    //@cmember
    /* Sets the procedure cost forecast. */
    void SetProcedureCostForecast(const double value);
    void SetProcedureCostForecast(PSS_AnnualNumberPropertiesBP& AnnualNumberProp);

    //@cmember
    /* Gets the procedure workload per activity forecast. */
    double GetProcedureWorkloadPerActivity() const;

    //@cmember
    /* Sets the procedure workload per activity forecast. */
    void SetProcedureWorkloadPerActivity(const double value);

    //@cmember
    /* Gets the procedure cost per activity forecast. */
    double GetProcedureCostPerActivity() const;

    //@cmember
    /* Sets the procedure cost per activity forecast. */
    void SetProcedureCostPerActivity(const double value);

    // JMR-MODIF - Le 26 avril 2007 - Ajout de la fonction ContainsRule.
    BOOL ContainsRule(CString RuleName);

    // JMR-MODIF - Le 9 octobre 2007 - Ajout de la fonction CheckRulesSync.
    void CheckRulesSync(CStringArray& RulesList);

    // ************************************************************************************************************
    // JMR-MODIF - Le 3 juin 2007 - Ajout des fonctions nécessaires à la gestion des risques.

    // Obtient le nombre de risques contenus dans le gestionnaire de risques.
    int GetRiskCount() const
    {
        return m_Risks.GetRiskCount();
    }

    // Obtient le nom du risque, en spécifiant son index.
    CString GetRiskName(size_t Index) const
    {
        return m_Risks.GetRiskName(Index);
    }

    // Inscrit le nom du risque, en spécifiant son index.
    void SetRiskName(size_t Index, CString Value)
    {
        m_Risks.SetRiskName(Index, Value);
    }

    // Obtient la description du risque, en spécifiant son index.
    CString GetRiskDesc(size_t Index) const
    {
        return m_Risks.GetRiskDesc(Index);
    }

    // Inscrit la description du risque, en spécifiant son index.
    void SetRiskDesc(size_t Index, CString Value)
    {
        m_Risks.SetRiskDesc(Index, Value);
    }

    // Obtient le type du risque, en spécifiant son index.
    CString GetRiskType(std::size_t index) const
    {
        int     count = PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementCount();
        CString riskType = m_Risks.GetRiskType(index);

        for (int i = 0; i < count; ++i)
            if (riskType == PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementAt(i))
                return m_Risks.GetRiskType(index);

        return _T("");
    }

    // Inscrit le type du risque, en spécifiant son index.
    void SetRiskType(size_t Index, CString Value)
    {
        m_Risks.SetRiskType(Index, Value);
    }

    // Obtient l'impact du risque, en spécifiant son index.
    int GetRiskImpact(size_t Index) const
    {
        return m_Risks.GetRiskImpact(Index);
    }

    // Inscrit l'impact du risque, en spécifiant son index.
    void SetRiskImpact(size_t Index, int Value)
    {
        m_Risks.SetRiskImpact(Index, Value);
    }

    // Obtient la probabilité du risque, en spécifiant son index.
    int GetRiskProbability(size_t Index) const
    {
        return m_Risks.GetRiskProbability(Index);
    }

    // Inscrit la probabilité du risque, en spécifiant son index.
    void SetRiskProbability(size_t Index, int Value)
    {
        m_Risks.SetRiskProbability(Index, Value);
    }

    // Obtient la sévérité du risque, en spécifiant son index.
    int GetRiskSeverity(size_t Index) const
    {
        return m_Risks.GetRiskSeverity(Index);
    }

    // Inscrit la sévérité du risque, en spécifiant son index.
    void SetRiskSeverity(size_t Index, int Value)
    {
        m_Risks.SetRiskSeverity(Index, Value);
    }

    // Obtient l'estimation unitaire du risque, en spécifiant son index.
    float GetRiskUE(size_t Index) const
    {
        return m_Risks.GetRiskUE(Index);
    }

    // Inscrit l'estimation unitaire du risque, en spécifiant son index.
    void SetRiskUE(size_t Index, float Value)
    {
        m_Risks.SetRiskUE(Index, Value);
    }

    // Obtient la perte operationnelle annuelle du risque, en spécifiant son index.
    float GetRiskPOA(size_t Index) const
    {
        return m_Risks.GetRiskPOA(Index);
    }

    // Inscrit la perte operationnelle annuelle du risque, en spécifiant son index.
    void SetRiskPOA(size_t Index, float Value)
    {
        m_Risks.SetRiskPOA(Index, Value);
    }

    // Obtient l'action du risque, en spécifiant son index.
    bool GetRiskAction(size_t Index) const
    {
        return m_Risks.GetRiskAction(Index);
    }

    // Inscrit l'action du risque, en spécifiant son index.
    void SetRiskAction(size_t Index, bool Value)
    {
        m_Risks.SetRiskAction(Index, Value);
    }
    // ************************************************************************************************************

protected:

    virtual void AdjustElementPosition();

    void OnAddNewCombination(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh);
    void OnDelCurrentCombination(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh);

    void OnAddDeliverableCombination(ZBProperty&        Property,
                                     CString&            value,
                                     ZBPropertySet&    Properties,
                                     bool&                Refresh);

    void OnDelDeliverableCombination(ZBProperty&        Property,
                                     CString&            value,
                                     ZBPropertySet&    Properties,
                                     bool&                Refresh);

    float GetMaxActivationPerc(const CString Master);
    void CheckInitialCombination();

    // ************************************************************************************************************
    // JMR-MODIF - Le 10 juin 2007 - Ajout des fonctions nécesaires à la gestion des risques.

    void OnAddNewRisk(ZBProperty&        Property,
                      CString&            value,
                      ZBPropertySet&    Properties,
                      bool&            Refresh);

    void OnDelCurrentRisk(ZBProperty&        Property,
                          CString&            value,
                          ZBPropertySet&    Properties,
                          bool&            Refresh);

    int AddNewRisk()
    {
        return m_Risks.AddNewRisk();
    }

    bool DeleteRisk(size_t Index)
    {
        return m_Risks.DeleteRisk(Index);
    }
    // ************************************************************************************************************

private:

    // JMR-MODIF - Le 25 décembre 2006 - Ajout de la fonction GetRuleNameByGUID.
    CString GetRuleNameByGUID(PSS_LogicalRulesEntity* p_Rule, CString RuleGUID);

private:

    // The model for the canvas. The model holds all information about 
    // the canvas, while the viewport actually displays it.
    CRect                            m_CommentRect;
    ZBProcCombinations                m_Combinations;
    ZBBPSimPropertiesProcedure        m_SimulationProperties;

    ZBBPUnitProperties2                m_UnitProp;
    ZBBPCostPropertiesProcedure2    m_CostProcedureProp;

    CStringArray                    m_UnitDoubleValidationTypeArray;

    // JMR-MODIF - Le 22 novembre 2006 - Ajout de la variable m_Rules
    ZBProcRules                        m_Rules;

    // JMR-MODIF - Le 3 juin 2007 - Ajout de la variable m_Risks
    ZBProcRisk                        m_Risks;
};

inline PSS_AnnualNumberPropertiesBP& ZBBPProcedureSymbol::GetProcedureActivation()
{
    return m_SimulationProperties.GetProcedureActivation();
}

inline void ZBBPProcedureSymbol::SetProcedureActivation(const double value)
{
    m_SimulationProperties.SetProcedureActivation(value);
}

inline void ZBBPProcedureSymbol::SetProcedureActivation(PSS_AnnualNumberPropertiesBP& AnnualNumberProp)
{
    m_SimulationProperties.GetProcedureActivation() = AnnualNumberProp;
}

inline PSS_AnnualNumberPropertiesBP& ZBBPProcedureSymbol::GetProcedureCost()
{
    return m_SimulationProperties.GetProcedureCost();
}

inline void ZBBPProcedureSymbol::SetProcedureCost(const double value)
{
    m_SimulationProperties.SetProcedureCost(value);
}

inline void ZBBPProcedureSymbol::SetProcedureCost(PSS_AnnualNumberPropertiesBP& AnnualNumberProp)
{
    m_SimulationProperties.GetProcedureCost() = AnnualNumberProp;
}

inline PSS_AnnualNumberPropertiesBP& ZBBPProcedureSymbol::GetProcedureWorkloadForecast()
{
    return m_SimulationProperties.GetProcedureWorkloadForecast();
}

inline void ZBBPProcedureSymbol::SetProcedureWorkloadForecast(const double value)
{
    m_SimulationProperties.SetProcedureWorkloadForecast(value);
}

inline void ZBBPProcedureSymbol::SetProcedureWorkloadForecast(PSS_AnnualNumberPropertiesBP& AnnualNumberProp)
{
    m_SimulationProperties.GetProcedureWorkloadForecast() = AnnualNumberProp;
}

inline PSS_AnnualNumberPropertiesBP& ZBBPProcedureSymbol::GetProcedureCostForecast()
{
    return m_SimulationProperties.GetProcedureCostForecast();
}

inline void ZBBPProcedureSymbol::SetProcedureCostForecast(const double value)
{
    m_SimulationProperties.SetProcedureCostForecast(value);
}

inline void ZBBPProcedureSymbol::SetProcedureCostForecast(PSS_AnnualNumberPropertiesBP& AnnualNumberProp)
{
    m_SimulationProperties.GetProcedureCostForecast() = AnnualNumberProp;
}

inline double ZBBPProcedureSymbol::GetProcedureWorkloadPerActivity() const
{
    return m_SimulationProperties.GetProcedureWorkloadPerActivity();
}

inline void ZBBPProcedureSymbol::SetProcedureWorkloadPerActivity(const double value)
{
    m_SimulationProperties.SetProcedureWorkloadPerActivity(value);
}

inline double ZBBPProcedureSymbol::GetProcedureCostPerActivity() const
{
    return m_SimulationProperties.GetProcedureCostPerActivity();
}

inline void ZBBPProcedureSymbol::SetProcedureCostPerActivity(const double value)
{
    m_SimulationProperties.SetProcedureCostPerActivity(value);
}

inline int ZBBPProcedureSymbol::GetRightSubMenu() const
{
    return 2;
}

inline int ZBBPProcedureSymbol::GetIconIndex() const
{
    return (IsLocal()) ? 4 : 12;
}

#endif
