/****************************************************************************
 * ==> PSS_ProcedureSymbolBP -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a procedure symbol for banking process            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcedureSymbolBPH
#define PSS_ProcedureSymbolBPH

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
#ifndef PSS_ProcedureSymbolBP
    #define PSS_ProcedureSymbolBP ZBBPProcedureSymbol
#endif

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LogicalRulesEntity.h"
#include "ZBProcCombinations.h"
#include "PSS_SimPropertiesProcedureBP.h"
#include "ZBBPUnitProp2.h"
#include "PSS_CostPropertiesProcedureBP.h"
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
* Procedure symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcedureSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_ProcedureSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        */
        PSS_ProcedureSymbolBP(const CString& name = _T(""));

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcedureSymbolBP(const PSS_ProcedureSymbolBP& other);

        virtual ~PSS_ProcedureSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcedureSymbolBP& operator = (const PSS_ProcedureSymbolBP& other);

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
        * Checks if this symbol is a procedure
        *@return TRUE if this symbol is a procedure, otherwise FALSE
        */
        virtual inline BOOL IsProcedure() const;

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
        * Checks if external application may be accepted
        *@return true if external application may be accepted, otherwise false
        */
        virtual bool AcceptExtApp() const;

        /**
        * Checks if external file may be accepted
        *@return true if external file may be accepted, otherwise false
        */
        virtual bool AcceptExtFile() const;

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
        *@param[in, out] prop - property to check
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
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
        * Gets the entering up deliverables
        *@param[out] deliverables - a tokenized list containing the result
        *@return the deliverable count
        */
        virtual int GetEnteringUpDeliverable(CString& deliverables);

        /**
        * Gets the entering up deliverables
        *@param[out] edges - the edge array containing the result
        *@return the deliverable count
        */
        virtual int GetEnteringUpDeliverable(CODEdgeArray& edges);

        /**
        * Gets the leaving down deliverables
        *@param[out] deliverables - a tokenized list containing the result
        *@return the deliverable count
        */
        virtual int GetLeavingDownDeliverable(CString& deliverables);

        /**
        * Gets the leaving down deliverables
        *@param[out] edges - the edge array containing the result
        *@return the deliverable count
        */
        virtual int GetLeavingDownDeliverable(CODEdgeArray& edges);

        /**
        * Gets the leaving left deliverables
        *@param[out] deliverables - a tokenized list containing the result
        *@return the deliverable count
        */
        virtual int GetLeavingLeftDeliverable(CString& deliverables);

        /**
        * Gets the leaving left deliverables
        *@param[out] edges - the edge array containing the result
        *@return the deliverable count
        */
        virtual int GetLeavingLeftDeliverable(CODEdgeArray& edges);

        /**
        * Gets the leaving right deliverables
        *@param[out] deliverables - a tokenized list containing the result
        *@return the deliverable count
        */
        virtual int GetLeavingRightDeliverable(CString& deliverables);

        /**
        * Gets the leaving right deliverables
        *@param[out] edges - the edge array containing the result
        *@return the deliverable count
        */
        virtual int GetLeavingRightDeliverable(CODEdgeArray& edges);

        /**
        * Gets the combinations reference
        *@return the combinations reference
        */
        virtual inline ZBProcCombinations& GetCombinations();

        /**
        * Adds a new combination
        *@return the new added combination index, -1 on error
        */
        virtual inline int AddNewCombination();

        /**
        * Gets the combination count
        *@return the combination count
        */
        virtual inline int GetCombinationCount() const;

        /**
        * Gets the combination property at index
        *@param index - the index
        *@return the combination property, NULL if not found or on error
        */
        virtual inline PSS_CombinationPropertiesBP* GetCombinationProperty(std::size_t index) const;

        /**
        * Deletes a combination
        *@param index - the index at which the combination should be deleted
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteCombination(std::size_t index);

        /**
        * Deletes a combination
        *@param pProp - the combination property to delete
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteCombination(PSS_CombinationPropertiesBP* pProp);

        /**
        * Checks if a combination name exists
        *@param name - the combination name to check
        *@return true if the combination name exists, otherwise false
        */
        virtual inline bool CombinationNameExist(const CString& name) const;

        /**
        * Gets the next valid name
        *@return the next valid name
        */
        virtual inline CString GetNextCombinationValidName() const;

        /**
        * Gets the available deliverables
        *@param allDeliverables - all the deliverables required to build the string
        *@return the available deliverables
        */
        virtual inline CString GetAvailableDeliverables(const CString& allDeliverables) const;

        /**
        * Gets the allocated deliverables
        *@return the allocated deliverables
        */
        virtual inline CString GetAllocatedDeliverables() const;

        /**
        * Checks if a deliverable exists in a string
        *@param deliverables - the deliverables name
        *@param value - the string to search in
        *@return true if the deliverable exists in the string, otherwise false
        */
        virtual inline bool IsDeliverableInString(const CString& deliverables, const CString& value) const;

        /**
        * Gets the deliverable combination property
        *@param deliverableName - the deliverable name
        *@return the deliverable combination property, NULL if not found or on error
        */
        virtual inline PSS_CombinationPropertiesBP* LocateCombinationOfDeliverable(const CString& deliverableName) const;

        /**
        * Gets the combination properties index containing a deliverable
        *@param deliverableName - the deliverable name to find
        *@return the combination properties index containing the deliverable, -1 if not found or on error
        */
        virtual inline int LocateCombinationIndexOfDeliverable(const CString& deliverableName) const;

        /**
        * Replaces an old deliverable by a new one
        *@param oldDeliverableName - the old deliverable name to replace
        *@param newDeliverableName - the new deliverable name to replace by
        *@return true on success, otherwise false
        */
        virtual inline bool ReplaceDeliverable(const CString& oldDeliverableName, const CString& newDeliverableName);

        /**
        * Deletes a deliverable from all combinations, including the master
        *@param deliverableName - the deliverable name to delete
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteDeliverableFromAllCombinations(const CString& deliverableName);

        /**
        * Gets the combination name at index
        *@param index - the index
        *@return the combination name, empty string if not found or on error
        */
        virtual inline CString GetCombinationName(std::size_t index) const;

        /**
        * Sets the combination name at index
        *@param index - the index
        *@param value - the combination name
        */
        virtual inline void SetCombinationName(std::size_t index, const CString& value);

        /**
        * Gets the deliberables at index
        *@param index - the index
        *@return the deliverables, empty string if not found or on error
        */
        virtual inline CString GetCombinationDeliverables(std::size_t index) const;

        /**
        * Sets the deliberables at index
        *@param index - the index
        *@return the deliverables, empty string if not found or on error
        */
        virtual inline void SetCombinationDeliverables(std::size_t index, const CString& value);

        /**
        * Adds a deliverable to the deliberables at index
        *@param index - the index
        *@param value - the deliverable to add
        *@return true on success, otherwise false
        */
        virtual inline bool AddCombinationDeliverable(std::size_t index, const CString& value);

        /**
        * Removes a deliverable from the deliverables at index
        *@param index - the index
        *@param value - the deliverable to add
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveCombinationDeliverable(std::size_t index, const CString& value);

        /**
        * Removes all deliverables at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveAllCombinationDeliverable(std::size_t index);

        /**
        * Gets the combination percentage at index
        *@param index - the index
        *@return the combination percentage
        */
        virtual inline float GetCombinationActivationPerc(std::size_t index) const;

        /**
        * Sets the combination percentage at index
        *@param index - the index
        *@param value - the combination percentage
        */
        virtual inline void SetCombinationActivationPerc(std::size_t index, const float value);

        /**
        * Gets the combination master name at index
        *@param index - the index
        *@return the combination master name, empty string if not found or on error
        */
        virtual inline CString GetCombinationMaster(std::size_t index) const;

        /**
        * Sets the combination master name at index
        *@param index - the index
        *@param value - the combination master name
        */
        virtual inline void SetCombinationMaster(std::size_t index, const CString& value);

        /**
        * Calculates the procedure activation based on combinations
        *@return the calculated procedure activation property
        */
        virtual PSS_AnnualNumberPropertiesBP CalculateProcedureActivation();

        /**
        * Gets the cost multiplier factor
        *@return the cost multiplier factor
        */
        virtual inline float GetMultiplier() const;

        /**
        * Sets the cost multiplier factor
        *@param value - the cost multiplier factor
        */
        virtual inline void SetMultiplier(const float value);

        /**
        * Gets the processing time
        *@return the processing time
        */
        virtual inline double GetProcessingTime() const;

        /**
        * Sets the processing time
        *@param value - the processing time
        */
        virtual inline void SetProcessingTime(const double value);

        /**
        * Gets the unitary cost
        *@return the unitary cost
        */
        virtual inline float GetUnitaryCost() const;

        /**
        * Sets the unitary cost
        *@param value - the unitary cost
        */
        virtual inline void SetUnitaryCost(const float value);

        /**
        * Gets the processing duration
        *@return the processing duration
        */
        virtual inline double GetProcessingDuration() const;

        /**
        * Sets the processing duration
        *@param value - the processing duration
        */
        virtual inline void SetProcessingDuration(const double value);

        /**
        * Gets the maximum processing duration
        *@return the maximum processing duration
        */
        virtual inline double GetProcessingDurationMax() const;

        /**
        * Sets the maximum processing duration
        *@param value - the maximum processing duration
        */
        virtual inline void SetProcessingDurationMax(const double value);

        /**
        * Checks if the procedure contains units
        *@return true if the procedure contains units, otherwise false
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
        * Gets the unit double validation type
        *@return the unit double validation type
        */
        virtual inline int GetUnitDoubleValidationType() const;

        /**
        * Sets the unit double validation type
        *@param value - the unit double validation type
        */
        virtual inline void SetUnitDoubleValidationType(const int value);

        /**
        * Gets the unit double validation type as a string array
        *@param[out] strArray - the string array which will contain the result
        */
        virtual inline void GetUnitDoubleValidationTypeStringArray(CStringArray& strArray) const;

        /**
        * Converts the unit double validation string to type
        *@param str - the unit double validation string to convert
        *@return the converted type
        */
        virtual inline int ConvertUnitDoubleValidationString2Type(const CString& str) const;

        /**
        * Gets the unit double validation type as string
        *@param type - the unit double validation type to convert
        *@return the unit double validation type as string
        */
        virtual inline CString GetUnitDoubleValidationTypeString(const int type) const;

        /**
        * Gets the rule list
        *@return the rule list
        */
        virtual CString GetRuleList() const;

        /**
        * Sets the rule list
        *@param value - the rule list
        */
        virtual void SetRuleList(const CString& value);

        /**
        * Checks if a rule exists
        *@param value - the rule to check
        *@return true if the rule exists, otherwise false
        */
        virtual bool RuleExist(const CString& value);

        /**
        * Adds a rule
        *@param value - the rule to add
        */
        virtual void AddRule(const CString& value);

        /**
        * Removes a rule
        *@param value - the rule to remove
        */
        virtual void RemoveRule(const CString& value);

        /**
        * Gets the rule at index
        *@param index - the index
        *@return the rule, empty string if not found or on error
        */
        virtual CString GetRuleAt(std::size_t index);

        /**
        * Gets the rule count
        *@return the rule count
        */
        virtual std::size_t GetRuleCount() const;

        /**
        * Checks if a rule is contained in the rules
        *@param ruleName - the rule name to check
        *@return TRUE if the rule is contained in the rules, otherwise FALSE
        */
        virtual BOOL ContainsRule(const CString& ruleName);

        /**
        * Checks the rules which are no longer synchronized with the referential
        *@param ruleList - the rules to check
        */
        virtual void CheckRulesSync(CStringArray& rulesList);

        /**
        * Removes all the rules
        */
        virtual inline void RemoveAllRules();

        /**
        * Gets the task list
        *@return the task list
        */
        virtual CString GetTaskList() const;

        /**
        * Sets the task list
        *@param value - the task list
        */
        virtual void SetTaskList(const CString& value);

        /**
        * Checks if a task exists
        *@param value - the task to check
        *@return true if the task exists, otherwise false
        */
        virtual bool TaskExist(const CString& value);

        /**
        * Adds a task
        *@param value - the task to add
        */
        virtual void AddTask(const CString& value);

        /**
        * Removes a task
        *@param value - the task to remove
        */
        virtual void RemoveTask(const CString& value);

        /**
        * Gets the task at index
        *@param index - the index
        *@return the task, empty string if not found or on error
        */
        virtual CString GetTaskAt(std::size_t index);

        /**
        * Gets the task count
        *@return the task count
        */
        virtual std::size_t GetTaskCount() const;

        /**
        * Removes all the tasks
        */
        virtual inline void RemoveAllTasks();

        /**
        * Gets the decision list
        *@return the decision list
        */
        virtual CString GetDecisionList() const;

        /**
        * Sets the decision list
        *@param value - the decision list
        */
        virtual void SetDecisionList(const CString& value);

        /**
        * Checks if a decision exists
        *@param value - the decision to check
        *@return true if the decision exists, otherwise false
        */
        virtual bool DecisionExist(const CString& value);

        /**
        * Adds a decision
        *@param value - the decision to add
        */
        virtual void AddDecision(const CString& value);

        /**
        * Removes a decision
        *@param value - the decision to remove
        */
        virtual void RemoveDecision(const CString& value);

        /**
        * Gets the decision at index
        *@param index - the index
        *@return the decision, empty string if not found or on error
        */
        virtual CString GetDecisionAt(std::size_t index);

        /**
        * Gets the decision count
        *@return the decision count
        */
        virtual std::size_t GetDecisionCount() const;

        /**
        * Removes all the decisions
        */
        virtual inline void RemoveAllDecisions();

        /**
        * Gets the procedure activation
        *@return the activation procedure
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureActivation();

        /**
        * Sets the procedure activation
        *@param value - the activation procedure value
        */
        virtual inline void SetProcedureActivation(const double value);

        /**
        * Sets the procedure activation
        *@param annualNumberProp - the activation procedure property
        */
        virtual inline void SetProcedureActivation(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the standard procedure cost
        *@return the standard procedure cost
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureCost();

        /**
        * Sets the standard procedure cost
        *@param value - the standard procedure cost value
        */
        virtual inline void SetProcedureCost(const double value);

        /**
        * Sets the standard procedure cost
        *@param annualNumberProp - the standard procedure cost property
        */
        virtual inline void SetProcedureCost(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the procedure workload forecast
        *@return the procedure workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureWorkloadForecast();

        /**
        * Sets the procedure workload forecast
        *@param value - the procedure workload forecast value
        */
        virtual inline void SetProcedureWorkloadForecast(const double value);

        /**
        * Sets the procedure workload forecast
        *@param annualNumberProp - the procedure workload forecast property
        */
        virtual inline void SetProcedureWorkloadForecast(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the procedure cost forecast
        *@return the procedure cost forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureCostForecast();

        /**
        * Sets the procedure cost forecast
        *@param value - the procedure cost forecast value
        */
        virtual inline void SetProcedureCostForecast(const double value);

        /**
        * Sets the procedure cost forecast
        *@param annualNumberProp - the procedure cost forecast property
        */
        virtual inline void SetProcedureCostForecast(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the procedure workload per activity forecast
        *@return the procedure workload per activity forecast
        */
        virtual inline double GetProcedureWorkloadPerActivity() const;

        /**
        * Sets the procedure workload per activity forecast
        *@param value - the procedure workload per activity forecast value
        */
        virtual inline void SetProcedureWorkloadPerActivity(const double value);

        /**
        * Gets the procedure cost per activity forecast
        *@return the procedure cost per activity forecast
        */
        virtual inline double GetProcedureCostPerActivity() const;

        /**
        * Sets the procedure cost per activity forecast
        *@param value - the procedure cost per activity forecast
        */
        virtual inline void SetProcedureCostPerActivity(const double value);

        /**
        * Gets the risk count
        *@return the risk count
        */
        virtual inline int GetRiskCount() const;

        /**
        * Get the risk name at index
        *@param index - the index
        *@return the risk name at index, empty string if not found or on error
        */
        virtual inline CString GetRiskName(std::size_t index) const;

        /**
        * Set the risk name at index
        *@param index - the index
        *@param value - the risk name
        */
        virtual inline void SetRiskName(std::size_t index, const CString& value);

        /**
        * Get the risk description at index
        *@param index - the index
        *@return the risk description at index, empty string if not found or on error
        */
        virtual inline CString GetRiskDesc(std::size_t index) const;

        /**
        * Set the risk description at index
        *@param index - the index
        *@param value - the risk description
        */
        virtual inline void SetRiskDesc(std::size_t index, const CString& value);

        /**
        * Gets the risk type at index
        *@param index - the index
        *@return the risk type at index, empty string if not found or on error
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
        *@return the risk impact at index
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
        *@return the risk probability at index
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
        *@return the risk severity at index
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
        *@return the risk unitary estimation at index
        */
        virtual inline float GetRiskUE(std::size_t index) const;

        /**
        * Sets the risk unitary estimation at index
        *@param index - the index
        *@param value - the risk unitary estimation
        */
        virtual inline void SetRiskUE(std::size_t index, float value);

        /**
        * Gets the risk annual operating loss (perte opérationnelle annuelle in French) at index
        *@param index - the index
        *@return the risk annual operating loss (perte opérationnelle annuelle in French) at index
        */
        virtual inline float GetRiskPOA(std::size_t index) const;

        /**
        * Sets the risk annual operating loss (perte opérationnelle annuelle in French) at index
        *@param index - the index
        *@param value - the risk annual operating loss (perte opérationnelle annuelle in French)
        */
        virtual inline void SetRiskPOA(std::size_t index, float value);

        /**
        * Gets the risk action at index
        *@param index - the index
        *@return the risk action at index
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
        * Called when the symbol name changed
        *@param[in, out] comp - the component for which the name changed
        *@param oldName - the old component name
        */
        virtual void OnSymbolNameChanged(CODComponent& comp, const CString& oldName);

        /**
        * Called after the property changed
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(ZBProperty& property, ZBPropertySet& properties, bool& refresh);

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
        * Called when a connection was created
        *@param pConnection - the newly created connection
        */
        virtual void OnConnect(CODConnection* pConnection);

        /**
        * Called before a connection is destroyed
        *@param pConnection - the connection about to be disconnected
        */
        virtual void OnDisconnect(CODConnection* pConnection);

        /**
        * Called when a connection moves
        *@param pConnection - the connection which has moved
        *@return TRUE if the connection moved, otherwise FALSE
        */
        virtual BOOL OnConnectionMove(CODConnection* pConnection);

        /**
        * Called by the link when it was disconnected
        *@param pLink - the disconnected link
        */
        virtual void OnLinkDisconnect(CODLinkComponent* pLink);

        /**
        * Called when the symbol is double clicked
        *@return TRUE if the double click was performed, otherwise FALSE
        */
        virtual BOOL OnDoubleClick();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

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

        /**
        * Checks the initial combination
        */
        virtual void CheckInitialCombination();

        /**
        * Gets the maximum activation percent
        *@param master - the master name
        *@return the maximum activation percent
        */
        virtual float GetMaxActivationPerc(const CString& master);

        /**
        * Adds a new risk
        *@return the risk count
        */
        virtual inline int AddNewRisk();

        /**
        * Deletes a risk
        *@param index - the index at which the risk should be deleted
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteRisk(std::size_t index);

        /**
        * Called when a new combination is added
        *@param prop - the property
        *@param[in, out] value - the value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        */
        virtual void OnAddNewCombination(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a combination was deleted
        *@param prop - the property
        *@param[in, out] value - the value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        */
        virtual void OnDelCurrentCombination(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a new deliverable combination is added
        *@param prop - the property
        *@param[in, out] value - the value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        */
        virtual void OnAddDeliverableCombination(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a deliverable combination was deleted
        *@param prop - the property
        *@param[in, out] value - the value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        */
        virtual void OnDelDeliverableCombination(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a new deliverable combination is added
        *@param prop - the property
        *@param[in, out] value - the value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        */
        virtual void OnAddNewRisk(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a risk was deleted
        *@param prop - the property
        *@param[in, out] value - the value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        */
        virtual void OnDelCurrentRisk(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

    private:
        ZBProcCombinations            m_Combinations;
        PSS_SimPropertiesProcedureBP  m_SimulationProperties;
        ZBBPUnitProperties2           m_UnitProp;
        PSS_CostPropertiesProcedureBP m_CostProcedureProp;
        ZBProcRules                   m_Rules;
        ZBProcRisk                    m_Risks;
        CRect                         m_CommentRect;
        CStringArray                  m_UnitDoubleValidationTypeArray;

        /**
        * Gets the rule name by GUID
        *@param pRule - the rule for which the name should be get
        *@param ruleGUID - the rule GUID matching with the name to get
        *@return the rule name matching with the GUID
        */
        CString GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID);
};

//---------------------------------------------------------------------------
// PSS_ProcedureSymbolBP
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_ProcedureSymbolBP::AddRef()
{
    return CODSymbolComponent::AddRef();
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_ProcedureSymbolBP::Release()
{
    return CODSymbolComponent::Release();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcedureSymbolBP::IsProcedure() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::CanContainChildModel() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::IncludeDescriptionArea() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::IncludeAttributeArea() const
{
    return true;
}
//---------------------------------------------------------------------------
ZBProcCombinations& PSS_ProcedureSymbolBP::GetCombinations()
{
    return m_Combinations;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::AddNewCombination()
{
    return m_Combinations.AddNewCombination();
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetCombinationCount() const
{
    return m_Combinations.GetCombinationCount();
}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP* PSS_ProcedureSymbolBP::GetCombinationProperty(std::size_t index) const
{
    return m_Combinations.GetProperty(index);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::DeleteCombination(std::size_t index)
{
    return m_Combinations.DeleteCombination(index);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::DeleteCombination(PSS_CombinationPropertiesBP* pProp)
{
    return m_Combinations.DeleteCombination(pProp);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::CombinationNameExist(const CString& name) const
{
    return m_Combinations.CombinationNameExist(name);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetNextCombinationValidName() const
{
    return m_Combinations.GetNextCombinationValidName();
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetAvailableDeliverables(const CString& allDeliverables) const
{
    return m_Combinations.GetAvailableDeliverables(allDeliverables);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetAllocatedDeliverables() const
{
    return m_Combinations.GetAllocatedDeliverables();
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::IsDeliverableInString(const CString& deliverables, const CString& value) const
{
    return m_Combinations.IsDeliverableInString(deliverables, value);
}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP* PSS_ProcedureSymbolBP::LocateCombinationOfDeliverable(const CString& deliverableName) const
{
    return m_Combinations.LocateCombinationOfDeliverable(deliverableName);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::LocateCombinationIndexOfDeliverable(const CString& deliverableName) const
{
    return m_Combinations.LocateCombinationIndexOfDeliverable(deliverableName);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::ReplaceDeliverable(const CString& oldDeliverableName, const CString& newDeliverableName)
{
    return m_Combinations.ReplaceDeliverable(oldDeliverableName, newDeliverableName);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::DeleteDeliverableFromAllCombinations(const CString& deliverableName)
{
    return m_Combinations.DeleteDeliverableFromAllCombinations(deliverableName);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetCombinationName(std::size_t index) const
{
    return m_Combinations.GetCombinationName(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetCombinationName(std::size_t index, const CString& value)
{
    m_Combinations.SetCombinationName(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetCombinationDeliverables(std::size_t index) const
{
    return m_Combinations.GetCombinationDeliverables(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetCombinationDeliverables(std::size_t index, const CString& value)
{
    m_Combinations.SetCombinationDeliverables(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::AddCombinationDeliverable(std::size_t index, const CString& value)
{
    return m_Combinations.AddCombinationDeliverable(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::RemoveCombinationDeliverable(std::size_t index, const CString& value)
{
    return m_Combinations.RemoveCombinationDeliverable(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::RemoveAllCombinationDeliverable(std::size_t index)
{
    return m_Combinations.RemoveAllCombinationDeliverable(index);
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetCombinationActivationPerc(std::size_t index) const
{
    return m_Combinations.GetCombinationActivationPerc(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetCombinationActivationPerc(std::size_t index, const float value)
{
    m_Combinations.SetCombinationActivationPerc(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetCombinationMaster(std::size_t index) const
{
    return m_Combinations.GetCombinationMaster(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetCombinationMaster(std::size_t index, const CString& value)
{
    m_Combinations.SetCombinationMaster(index, value);
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetMultiplier() const
{
    return m_CostProcedureProp.GetMultiplier();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetMultiplier(const float value)
{
    m_CostProcedureProp.SetMultiplier(value);
}
//---------------------------------------------------------------------------
double PSS_ProcedureSymbolBP::GetProcessingTime() const
{
    return m_CostProcedureProp.GetProcessingTime();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcessingTime(const double value)
{
    m_CostProcedureProp.SetProcessingTime(value);
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetUnitaryCost() const
{
    return m_CostProcedureProp.GetUnitaryCost();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetUnitaryCost(const float value)
{
    m_CostProcedureProp.SetUnitaryCost(value);
}
//---------------------------------------------------------------------------
double PSS_ProcedureSymbolBP::GetProcessingDuration() const
{
    return m_CostProcedureProp.GetProcessingDuration();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcessingDuration(const double value)
{
    m_CostProcedureProp.SetProcessingDuration(value);
}
//---------------------------------------------------------------------------
double PSS_ProcedureSymbolBP::GetProcessingDurationMax() const
{
    return m_CostProcedureProp.GetProcessingDurationMax();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcessingDurationMax(const double value)
{
    m_CostProcedureProp.SetProcessingDurationMax(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::HasUnit() const
{
    return true;
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetUnitName() const
{
    return m_UnitProp.GetUnitName();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetUnitName(const CString& value)
{
    m_UnitProp.SetUnitName(value);
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetUnitCost() const
{
    return m_UnitProp.GetUnitCost();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetUnitCost(const float value)
{
    m_UnitProp.SetUnitCost(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetUnitGUID() const
{
    return m_UnitProp.GetUnitGUID();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetUnitGUID(const CString& value)
{
    m_UnitProp.SetUnitGUID(value);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetUnitDoubleValidationType() const
{
    return m_UnitProp.GetUnitDoubleValidationType();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetUnitDoubleValidationType(const int value)
{
    m_UnitProp.SetUnitDoubleValidationType(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::GetUnitDoubleValidationTypeStringArray(CStringArray& strArray) const
{
    m_UnitProp.GetUnitDoubleValidationTypeStringArray(strArray);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::ConvertUnitDoubleValidationString2Type(const CString& str) const
{
    return m_UnitProp.ConvertUnitDoubleValidationString2Type(str);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetUnitDoubleValidationTypeString(const int type) const
{
    return m_UnitProp.GetUnitDoubleValidationTypeString(type);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::RemoveAllRules()
{
    SetRuleList(_T(""));
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::RemoveAllTasks()
{
    SetTaskList(_T(""));
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::RemoveAllDecisions()
{
    SetDecisionList(_T(""));
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureSymbolBP::GetProcedureActivation()
{
    return m_SimulationProperties.GetProcedureActivation();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureActivation(const double value)
{
    m_SimulationProperties.SetProcedureActivation(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureActivation(PSS_AnnualNumberPropertiesBP& annualNumberProp)
{
    m_SimulationProperties.GetProcedureActivation() = annualNumberProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureSymbolBP::GetProcedureCost()
{
    return m_SimulationProperties.GetProcedureCost();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureCost(const double value)
{
    m_SimulationProperties.SetProcedureCost(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureCost(PSS_AnnualNumberPropertiesBP& annualNumberProp)
{
    m_SimulationProperties.GetProcedureCost() = annualNumberProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureSymbolBP::GetProcedureWorkloadForecast()
{
    return m_SimulationProperties.GetProcedureWorkloadForecast();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureWorkloadForecast(const double value)
{
    m_SimulationProperties.SetProcedureWorkloadForecast(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureWorkloadForecast(PSS_AnnualNumberPropertiesBP& annualNumberProp)
{
    m_SimulationProperties.GetProcedureWorkloadForecast() = annualNumberProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureSymbolBP::GetProcedureCostForecast()
{
    return m_SimulationProperties.GetProcedureCostForecast();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureCostForecast(const double value)
{
    m_SimulationProperties.SetProcedureCostForecast(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureCostForecast(PSS_AnnualNumberPropertiesBP& annualNumberProp)
{
    m_SimulationProperties.GetProcedureCostForecast() = annualNumberProp;
}
//---------------------------------------------------------------------------
double PSS_ProcedureSymbolBP::GetProcedureWorkloadPerActivity() const
{
    return m_SimulationProperties.GetProcedureWorkloadPerActivity();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureWorkloadPerActivity(const double value)
{
    m_SimulationProperties.SetProcedureWorkloadPerActivity(value);
}
//---------------------------------------------------------------------------
double PSS_ProcedureSymbolBP::GetProcedureCostPerActivity() const
{
    return m_SimulationProperties.GetProcedureCostPerActivity();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetProcedureCostPerActivity(const double value)
{
    m_SimulationProperties.SetProcedureCostPerActivity(value);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetRiskCount() const
{
    return m_Risks.GetRiskCount();
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRiskName(std::size_t index) const
{
    return m_Risks.GetRiskName(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskName(std::size_t index, const CString& value)
{
    m_Risks.SetRiskName(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRiskDesc(std::size_t index) const
{
    return m_Risks.GetRiskDesc(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskDesc(std::size_t index, const CString& value)
{
    m_Risks.SetRiskDesc(index, value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskType(std::size_t index, const CString& value)
{
    m_Risks.SetRiskType(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetRiskImpact(std::size_t index) const
{
    return m_Risks.GetRiskImpact(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskImpact(std::size_t index, int value)
{
    m_Risks.SetRiskImpact(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetRiskProbability(std::size_t index) const
{
    return m_Risks.GetRiskProbability(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskProbability(std::size_t index, int value)
{
    m_Risks.SetRiskProbability(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetRiskSeverity(std::size_t index) const
{
    return m_Risks.GetRiskSeverity(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskSeverity(std::size_t index, int value)
{
    m_Risks.SetRiskSeverity(index, value);
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetRiskUE(std::size_t index) const
{
    return m_Risks.GetRiskUE(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskUE(std::size_t index, float value)
{
    m_Risks.SetRiskUE(index, value);
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetRiskPOA(std::size_t index) const
{
    return m_Risks.GetRiskPOA(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskPOA(std::size_t index, float value)
{
    m_Risks.SetRiskPOA(index, value);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::GetRiskAction(std::size_t index) const
{
    return m_Risks.GetRiskAction(index);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRiskAction(std::size_t index, bool value)
{
    m_Risks.SetRiskAction(index, value);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetObjectTypeID() const
{
    return 2;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetRightSubMenu() const
{
    return 2;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetIconIndex() const
{
    return (IsLocal() ? 4 : 12);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::AddNewRisk()
{
    return m_Risks.AddNewRisk();
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::DeleteRisk(std::size_t index)
{
    return m_Risks.DeleteRisk(index);
}
//---------------------------------------------------------------------------

#endif
