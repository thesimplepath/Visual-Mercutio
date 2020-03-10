/****************************************************************************
 * ==> PSS_DeliverableLinkSymbolBP -----------------------------------------*
 ****************************************************************************
 * Description : Provides a deliverable link symbol for banking process     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DeliverableLinkSymbolBPH
#define PSS_DeliverableLinkSymbolBPH

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
#ifndef PSS_DeliverableLinkSymbolBP
    #define PSS_DeliverableLinkSymbolBP ZBDeliverableLinkSymbol
#endif

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModel\PSS_LogicalRulesEntity.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_ProcRules.h"
#include "PSS_RulesPropertiesBP.h"
#include "PSS_ProcRisk.h"
#include "PSS_RiskPropertiesBP.h"
#include "PSS_RiskTypeContainer.h"
#include "PSS_RiskImpactContainer.h"
#include "PSS_RiskProbabilityContainer.h"
#include "PSS_AnnualNumberPropertiesBP.h"
#include "PSS_SimPropertiesDeliverableBP.h"
#include "PSS_CostPropertiesDeliverableBP.h"
#include "PSS_UnitPropertiesBP.h"

// class name mapping
#ifndef PSS_DoorSymbolBP
    #define PSS_DoorSymbolBP ZBBPDoorSymbol
#endif
#ifndef PSS_PageSymbolBP
    #define PSS_PageSymbolBP ZBBPPageSymbol
#endif
#ifndef PSS_ProcedureSymbolBP
    #define PSS_ProcedureSymbolBP ZBBPProcedureSymbol
#endif
#ifndef PSS_ProcessSymbolBP
    #define PSS_ProcessSymbolBP ZBBPProcessSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_DoorSymbolBP;
class PSS_PageSymbolBP;
class PSS_ProcedureSymbolBP;
class PSS_ProcessSymbolBP;
class PSS_ProcessGraphModelMdl;

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
* Deliverable link symbol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DeliverableLinkSymbolBP : public PSS_LinkSymbol
{
    DECLARE_SERIAL(PSS_DeliverableLinkSymbolBP)

    public:
        PSS_DeliverableLinkSymbolBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DeliverableLinkSymbolBP(const PSS_DeliverableLinkSymbolBP& other);

        virtual ~PSS_DeliverableLinkSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DeliverableLinkSymbolBP& operator = (const PSS_DeliverableLinkSymbolBP& other);

        /**
        * Creates the link symbol
        *@param style - the style, ignored if -1
        *@param pointSize - the point size, ignored if -1
        *@param color - the color, ignored if -1
        *@param transparent - the transparency, ignored if -1
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(int style = -1, int pointSize = -1, COLORREF color = -1, int transparent = -1);

        /**
        * Creates the link symbol in an orthogonal way
        *@param style - the style, ignored if -1
        *@param pointSize - the point size, ignored if -1
        *@param color - the color, ignored if -1
        *@param transparent - the transparency, ignored if -1
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateOrthogonal(int style = -1, int pointSize = -1, COLORREF color = -1, int transparent = -1);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual CODComponent* Dup() const;

        /**
        * Copies the symbol definition from another symbol
        *@param src - the source symbol to copy from
        */
        virtual void CopySymbolDefinitionFrom(const CODSymbolComponent& src);

        /**
        * Checks if the name may be edited even if the dynamic properties aren't enabled on the symbol
        *@return true if the name may be edited even if the dynamic properties aren't enabled on the symbol, otherwise false
        */
        virtual bool CanEditNonDynamicName() const;

        /**
        * Checks if a dropped item may be accepted by the symbol
        *@param pObj - item to check and accept
        *@param point - drop point in pixels
        *@return true if the dropped item is accepted by the symbol, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item in the symbol
        *@param pObj - dropped item
        *@param point - drop point in pixels
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Checks if external applications are accepted by the symbol
        *@return true if external applications are accepted by the symbol, otherwise false
        */
        virtual bool AcceptExtApp() const;

        /**
        * Checks if external files are accepted by the symbol
        *@return true if external files are accepted by the symbol, otherwise false
        */
        virtual bool AcceptExtFile() const;

        /**
        * Checks if symbol has units
        *@return true if symbol has units, otherwise false
        */
        virtual inline bool HasUnit() const;

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetUnitName() const;

        /**
        * Sets the unit name
        *@param pValue - the unit name
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
        *@param pValue - the unit GUID
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
        *@param[out] strArray - the string array which will contain the unit double validation type
        */
        virtual inline void GetUnitDoubleValidationTypeStringArray(CStringArray& strArray) const;

        /**
        * Converts the unit double validation string to type
        *@param type - the string containing the type to convert
        *@return the converted type
        */
        virtual inline int ConvertUnitDoubleValidationString2Type(const CString& type) const;

        /**
        * Gets the unit double validation type as a string
        *@param value - the unit double validation type to convert
        *@return the converted string
        */
        virtual inline CString GetUnitDoubleValidationTypeString(const int value) const;

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
        *@param[in, out] propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(ZBPropertySet& propSet);

        /**
        * Saves a symbol property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(PSS_Property& prop);

        /**
        * Checks the property value
        *@param[in, out] prop - property to check
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
        */
        virtual bool CheckPropertyValue(PSS_Property& prop, CString& value, ZBPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(PSS_Property& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int            menuCmdID,
                                        PSS_Property&  prop,
                                        CString&       value,
                                        ZBPropertySet& props,
                                        bool&          refresh);

        /**
        * Creates the symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

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
        * Moves a port attached to the symbol
        *@param pPort - the port to move
        *@param offsetX - the move offset on the x axis
        *@param offsetY - the move offset on the y axis
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MovePort(CODPortComponent* pPort, const int offsetX, const int offsetY);

        /**
        * Gets the rule list
        *@return the rule list
        */
        virtual CString GetRuleList() const;

        /**
        * Sets the rule list
        *@param rules - the rule list
        */
        virtual void SetRuleList(const CString& rules);

        /**
        * Adds a rule
        *@param rule - the rule to add
        */
        virtual void AddRule(const CString& rule);

        /**
        * Removes a rule
        *@param rule - the rule to remove
        */
        virtual void RemoveRule(const CString& rule);

        /**
        * Removes all the rules
        */
        virtual inline void RemoveAllRules();

        /**
        * Checks if a rule exists
        *@param rule - the rule to check
        *@return true if the rule exists, otherwise false
        */
        virtual bool RuleExist(const CString& rule);

        /**
        * Gets the rule at index
        *@param index - the index
        *@return the rule at index, empty string if not found or on error
        */
        virtual CString GetRuleAt(std::size_t index) const;

        /**
        * Gets the rule count
        *@return the rule count
        */
        virtual std::size_t GetRuleCount() const;

        /**
        * Gets the text item list
        *@return the text item list
        */
        virtual CString GetTextItemList() const;

        /**
        * Sets the text item list
        *@param items - the text item list
        */
        virtual void SetTextItemList(const CString& items);

        /**
        * Adds a text item
        *@param item - the text item to add
        */
        virtual void AddTextItem(const CString& item);

        /**
        * Removes a text item
        *@param item - the text item to remove
        */
        virtual void RemoveTextItem(const CString& item);

        /**
        * Removes all the text items
        */
        virtual inline void RemoveAllTextItems();

        /**
        * Checks if a text item exists
        *@param item - the text item to check
        *@return true if the text item exists, otherwise false
        */
        virtual bool TextItemExist(const CString& item) const;

        /**
        * Gets the text item at index
        *@param index - the index
        *@return the text item at index, empty string if not found or on error
        */
        virtual CString GetTextItemAt(std::size_t index) const;

        /**
        * Gets the text item count
        *@return the text item count
        */
        virtual std::size_t GetTextItemCount() const;

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
        * Sets the input workload percent
        *@param value - the input workload percent
        *@note This function is kept for compatibility reason with Beta 1
        */
        virtual inline void SetInWorkloadPercent(const float value);

        /**
        * Gets the output workload percent
        *@return the output workload percent
        */
        virtual inline float GetOutWorkloadPercent() const;

        /**
        * Sets the output workload percent
        *@param value - the output workload percent
        */
        virtual inline void SetOutWorkloadPercent(const float value);

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
        * Gets the case duration
        *@return the case duration
        */
        virtual inline double GetCaseDuration() const;

        /**
        * Sets the case duration
        *@param value -  the case duration
        */
        virtual inline void SetCaseDuration(const double value);

        /**
        * Gets the maximum case duration
        *@return the maximum case duration
        */
        virtual inline double GetCaseDurationMax() const;

        /**
        * Sets the maximum case duration
        *@param value - the maximum case duration
        *@return the maximum case duration
        */
        virtual inline void SetCaseDurationMax(const double value);

        /**
        * Gets the target duration
        *@return the target duration
        */
        virtual inline double GetTargetDuration() const;

        /**
        * Sets the target duration
        *@param value - the target duration
        */
        virtual inline void SetTargetDuration(const double value);

        /**
        * Gets the green line duration
        *@return the green line duration
        */
        virtual inline double GetGreenLineDuration() const;

        /**
        * Sets the green line duration
        *@param value - the green line duration
        */
        virtual inline void SetGreenLineDuration(const double value);

        /**
        * Gets the deliverable cost
        *@return the deliverable cost
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetCost();

        /**
        * Sets the deliverable cost
        *@param value - the deliverable cost
        */
        virtual inline void SetCost(const double value);

        /**
        * Sets the deliverable cost
        *@param annualNumberProp - the property containing the deliverable cost
        */
        virtual inline void SetCost(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the deliverable workload forecast
        *@return the deliverable workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetWorkloadForecast();

        /**
        * Sets the deliverable workload forecast
        *@param value - the deliverable workload forecast
        */
        virtual inline void SetWorkloadForecast(const double value);

        /**
        * Sets the deliverable workload forecast
        *@param annualNumberProp - the deliverable workload forecast
        */
        virtual inline void SetWorkloadForecast(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the reference object to the quantity
        *@return the reference object to the quantity
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetQuantity();

        /**
        * Sets the new quantity
        *@param annualNumberProp - the property containing the new quantity
        */
        virtual inline void SetQuantity(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Sets the new quantity using the original equalizer
        *@param annualNumberProp - the property containing the new quantity
        */
        virtual inline void SetQuantityUsingOriginalEqualizer(PSS_AnnualNumberPropertiesBP& annualNumberProp);

        /**
        * Gets the year quantity
        *@return the year quantity
        */
        virtual inline double GetQuantityYear() const;

        /**
        * Sets the year quantity
        *@param value - the year quantity
        */
        virtual inline void SetQuantityYear(const double value);

        /**
        * Gets the January quantity
        *@return the January quantity
        */
        virtual inline double GetQuantityJanuary() const;

        /**
        * Sets the January quantity
        *@param value - the January quantity
        */
        virtual inline void SetQuantityJanuary(const double value);

        /**
        * Gets the February quantity
        *@return the February quantity
        */
        virtual inline double GetQuantityFebruary() const;

        /**
        * Sets the February quantity
        *@param value - the February quantity
        */
        virtual inline void SetQuantityFebruary(const double value);

        /**
        * Gets the March quantity
        *@return the March quantity
        */
        virtual inline double GetQuantityMarch() const;

        /**
        * Sets the March quantity
        *@param value - the March quantity
        */
        virtual inline void SetQuantityMarch(const double value);

        /**
        * Gets the April quantity
        *@return the April quantity
        */
        virtual inline double GetQuantityApril() const;

        /**
        * Sets the April quantity
        *@param value - the April quantity
        */
        virtual inline void SetQuantityApril(const double value);

        /**
        * Gets the May quantity
        *@return the May quantity
        */
        virtual inline double GetQuantityMay() const;

        /**
        * Sets the May quantity
        *@param value - the May quantity
        */
        virtual inline void SetQuantityMay(const double value);

        /**
        * Gets the June quantity
        *@return the June quantity
        */
        virtual inline double GetQuantityJune() const;

        /**
        * Sets the June quantity
        *@param value - the June quantity
        */
        virtual inline void SetQuantityJune(const double value);

        /**
        * Gets the July quantity
        *@return the July quantity
        */
        virtual inline double GetQuantityJuly() const;

        /**
        * Sets the July quantity
        *@param value - the July quantity
        */
        virtual inline void SetQuantityJuly(const double value);

        /**
        * Gets the August quantity
        *@return the August quantity
        */
        virtual inline double GetQuantityAugust() const;

        /**
        * Sets the August quantity
        *@param value - the August quantity
        */
        virtual inline void SetQuantityAugust(const double value);

        /**
        * Gets the September quantity
        *@return the September quantity
        */
        virtual inline double GetQuantitySeptember() const;

        /**
        * Sets the September quantity
        *@param value - the September quantity
        */
        virtual inline void SetQuantitySeptember(const double value);

        /**
        * Gets the October quantity
        *@return the October quantity
        */
        virtual inline double GetQuantityOctober() const;

        /**
        * Sets the October quantity
        *@param value - the October quantity
        */
        virtual inline void SetQuantityOctober(const double value);

        /**
        * Gets the November quantity
        *@return the November quantity
        */
        virtual inline double GetQuantityNovember() const;

        /**
        * Sets the November quantity
        *@param value - the November quantity
        */
        virtual inline void SetQuantityNovember(const double value);

        /**
        * Gets the December quantity
        *@return the December quantity
        */
        virtual inline double GetQuantityDecember() const;

        /**
        * Sets the December quantity
        *@param value - the December quantity
        */
        virtual inline void SetQuantityDecember(const double value);

        /**
        * Checks if the year quantity is locked
        *@return true if the year quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityYear() const;

        /**
        * Locks or unlocks the year quantity
        *@param value - if true, the year quantity is locked
        */
        virtual inline void SetLockQuantityYear(const bool value);

        /**
        * Checks if the January quantity is locked
        *@return true if the January quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityJanuary() const;

        /**
        * Locks or unlocks the January quantity
        *@param value - if true, the January quantity is locked
        */
        virtual inline void SetLockQuantityJanuary(const bool value);

        /**
        * Checks if the February quantity is locked
        *@return true if the February quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityFebruary() const;

        /**
        * Locks or unlocks the February quantity
        *@param value - if true, the February quantity is locked
        */
        virtual inline void SetLockQuantityFebruary(const bool value);

        /**
        * Checks if the March quantity is locked
        *@return true if the March quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityMarch() const;

        /**
        * Locks or unlocks the March quantity
        *@param value - if true, the March quantity is locked
        */
        virtual inline void SetLockQuantityMarch(const bool value);

        /**
        * Checks if the April quantity is locked
        *@return true if the April quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityApril() const;

        /**
        * Locks or unlocks the Abril quantity
        *@param value - if true, the Abril quantity is locked
        */
        virtual inline void SetLockQuantityApril(const bool value);

        /**
        * Checks if the May quantity is locked
        *@return true if the May quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityMay() const;

        /**
        * Locks or unlocks the May quantity
        *@param value - if true, the May quantity is locked
        */
        virtual inline void SetLockQuantityMay(const bool value);

        /**
        * Checks if the June quantity is locked
        *@return true if the June quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityJune() const;

        /**
        * Locks or unlocks the June quantity
        *@param value - if true, the June quantity is locked
        */
        virtual inline void SetLockQuantityJune(const bool value);

        /**
        * Checks if the July quantity is locked
        *@return true if the July quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityJuly() const;

        /**
        * Locks or unlocks the July quantity
        *@param value - if true, the July quantity is locked
        */
        virtual inline void SetLockQuantityJuly(const bool value);

        /**
        * Checks if the August quantity is locked
        *@return true if the August quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityAugust() const;

        /**
        * Locks or unlocks the August quantity
        *@param value - if true, the August quantity is locked
        */
        virtual inline void SetLockQuantityAugust(const bool value);

        /**
        * Checks if the September quantity is locked
        *@return true if the September quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantitySeptember() const;

        /**
        * Locks or unlocks the September quantity
        *@param value - if true, the September quantity is locked
        */
        virtual inline void SetLockQuantitySeptember(const bool value);

        /**
        * Checks if the October quantity is locked
        *@return true if the October quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityOctober() const;

        /**
        * Locks or unlocks the october quantity
        *@param value - if true, the October quantity is locked
        */
        virtual inline void SetLockQuantityOctober(const bool value);

        /**
        * Checks if the November quantity is locked
        *@return true if the November quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityNovember() const;

        /**
        * Locks or unlocks the November quantity
        *@param value - if true, the November quantity is locked
        */
        virtual inline void SetLockQuantityNovember(const bool value);

        /**
        * Checks if the December quantity is locked
        *@return true if the December quantity is locked, otherwise false
        */
        virtual inline bool GetLockQuantityDecember() const;

        /**
        * Locks or unlocks the December quantity
        *@param value - if true, the December quantity is locked
        */
        virtual inline void SetLockQuantityDecember(const bool value);

        /**
        * Gets if the equalizer should be forced
        *@return true if the equalizer should be forced, otherwise false
        */
        virtual inline bool GetForceEqualizer() const;

        /**
        * Sets if the equalizer should be forced
        *@param value - if true, the equalizer will be forced
        */
        virtual inline void SetForceEqualizer(bool value);

        /**
        * Gets the attached procedure combination name
        *@return the attached procedure combination name
        */
        virtual CString GetCombinationName() const;

        /**
        * Gets the attached procedure max combination percentage
        *@return the attached procedure max combination percentage, -1.0f on error
        */
        virtual float GetCombinationMaxPercentage() const;

        /**
        * Checks if the deliverable is a master of a procedure combination attached to this deliverable
        *@returns true if the deliverable is a master of a procedure combination attached to this deliverable, otherwise false
        */
        virtual bool IsMasterOfCombination() const;

        /**
        * Sets the line visual info in order to provide a visula info of the percentage
        *@parem percent - the percentage
        */
        virtual void SetVisualInfo(int percent);

        /**
        * Gets the source procedure attached to this deliverable
        *@return the source procedure attached to this deliverable
        */
        virtual PSS_ProcedureSymbolBP* GetSourceProcedure() const;

        /**
        * Gets the destination procedure attached to this deliverable
        *@return the destination procedure attached to this deliverable
        */
        virtual PSS_ProcedureSymbolBP* GetTargetProcedure() const;

        /**
        * Gets the coming from model for this deliverable
        *@return the coming from model for this deliverable
        */
        virtual PSS_ProcessGraphModelMdl* GetComingFromModel() const;

        /**
        * Gets the coming from process for this deliverable
        *@return the coming from process for this deliverable
        */
        virtual PSS_ProcessSymbolBP* GetComingFromProcess() const;

        /**
        * Gets the going to model for this deliverable
        *@return the going to model for this deliverable
        */
        virtual PSS_ProcessGraphModelMdl* GetGoingToModel() const;

        /**
        * Gets the going to process for this deliverable
        *@return the going to process for this deliverable
        */
        virtual PSS_ProcessSymbolBP* GetGoingToProcess() const;

        /**
        * Checks if the deliverable is an initial deliverable
        *@return true if the deliverable is an initial deliverable, otherwise false
        */
        virtual bool IsInitial() const;

        /**
        * Checks if the deliverable is a final deliverable
        *@return true if the deliverable is a final deliverable, otherwise false
        */
        virtual bool IsFinal() const;

        /**
        * Checks if the deliverable is a an interprocess deliverable
        *@return true if the deliverable is a an interprocess deliverable, otherwise false
        */
        virtual bool IsInterProcess() const;

        /**
        * Creates a new label and adds it to the symbol
        *@param pText - the label text to show
        *@param ctrlPoint - the control point type
        *@param pDC - the device context to draw on
        */
        virtual CODLabelComponent* CreateLabel(const LPCTSTR          pText,
                                               const OD_CONTROL_POINT ctrlPoint,
                                               CDC*                   pDC = NULL);

        /**
        * Checks if the deliverable contains a rule
        *@param ruleName - the rule name to check
        *@return TRUE if the deliverable contains the rule, otherwise FALSE
        */
        virtual BOOL ContainsRule(const CString& ruleName) const;

        /**
        * Gets the rules which are no longer synchronized with this deliverable
        *@param[out] rulesList - the rules which are no longer synchronized with this deliverable
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
        * Called before the symbol is deleted
        *@param pModel - the model containing the symbol about to be deleted
        *@param pCtrl - the model controller
        *@return true if the symbol can be deleted, otherwise false
        */
        virtual bool OnPreDelete(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called when the symbol name is changing
        *@param oldName - the old component name
        *@param newName - the new component name
        */
        virtual void OnSymbolNameChange(const CString& oldName, const CString& newName);

        /**
        * Called when an internal property drag&drop occurred in the symbol
        *@param[in, out] srcProperty - the source property
        *@param[in, out] dstProperty - the destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param[in, out] props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(PSS_Property&  srcProperty,
                                                PSS_Property&  dstProperty,
                                                bool           top2Down,
                                                ZBPropertySet& props);

        /**
        * Called before the property changes
        *@param newValue - the new value
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, ZBPropertySet& props);

        /**
        * Called after the property changed
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(PSS_Property& prop, ZBPropertySet& props, bool& refresh);

        /**
        * Called after a connection was performed
        *@param pConnection - the connection
        */
        virtual void OnConnect(CODConnection* pConnection);

        /**
        * Called before a connection is removed
        *@param pConnection - the connection
        */
        virtual void OnDisconnect(CODConnection* pConnection);

        /**
        * Called when a connection moves
        *@param pConnection - the moving connection
        *@return TRUE if the connection is allowed to move, otherwise FALSE
        */
        virtual BOOL OnConnectionMove(CODConnection* pConnection);

        /**
        * Called when the dependent on the connection is removed
        *@param pConnection - the connection
        *@return TRUE if the dependent was removed, otherwise FALSE
        */
        virtual BOOL OnRemoveDependent(CODConnection* pConnection);

        /**
        * Called when the symbol is double clicked
        *@return TRUE if the double click was performed, otherwise FALSE
        */
        virtual inline BOOL OnDoubleClick();

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
        virtual void OnAddNewRisk(PSS_Property& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when a risk is deleted
        *@param[in, out] prop - the property containing the risk
        *@param[in, out] value - the property value
        *@param[in, out] props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        */
        virtual void OnDelCurrentRisk(PSS_Property& prop, CString& value, ZBPropertySet& props, bool& refresh);

    private:
        PSS_AnnualNumberPropertiesBP    m_Quantity;
        PSS_SimPropertiesDeliverableBP  m_SimProperties;
        PSS_CostPropertiesDeliverableBP m_CostDeliverableProperties;
        PSS_UnitPropertiesBP            m_UnitProp;
        PSS_ProcRules                   m_Rules;
        PSS_ProcRisk                    m_Risks;
        CStringArray                    m_UnitDoubleValidationTypeArray;

        /**
        * Notifies that the name changed
        *@param oldName - the old component name
        *@param newName - the new component name
        *@param pRootModel - the root model
        */
        void NotifyNameChange(const CString&              oldName,
                              const CString&              nNewName,
                              PSS_ProcessGraphModelMdlBP* m_RootModel = NULL);

        /**
        * Creates the symbol name
        *@return true on success, otherwise false
        */
        bool CreateSymbolName();

        /**
        * Performs a connection between a door symbol and a procedure symbol
        *@param pSrc - the source symbol to connect
        *@param pDst - the destination symbol to connect
        *@param pModel - the model
        *@return true on success, otherwise false
        */
        bool DoDoorProcedureConnection(PSS_DoorSymbolBP* pSrc, PSS_ProcedureSymbolBP* pDst, CODModel* pModel);

        /**
        * Performs a connection between a procedure symbol and a door symbol
        *@param pSrc - the source symbol to connect
        *@param pDst - the destination symbol to connect
        *@param pModel - the model
        *@return true on success, otherwise false
        */
        bool DoProcedureDoorConnection(PSS_ProcedureSymbolBP* pSrc, PSS_DoorSymbolBP* pDst, CODModel* pModel);

        /**
        * Performs a connection between a page symbol and a procedure symbol
        *@param pSrc - the source symbol to connect
        *@param pDst - the destination symbol to connect
        *@param pModel - the model
        *@return true on success, otherwise false
        */
        bool DoPageProcedureConnection(PSS_PageSymbolBP* pSrc, PSS_ProcedureSymbolBP* pDst, CODModel* pModel);

        /**
        * Performs a connection between a procedure symbol and a page symbol
        *@param pSrc - the source symbol to connect
        *@param pDst - the destination symbol to connect
        *@param pModel - the model
        *@return true on success, otherwise false
        */
        bool DoProcedurePageConnection(PSS_ProcedureSymbolBP* pSrc, PSS_PageSymbolBP* pDst, CODModel* pModel);

        /**
        * Performs a connection between two process symbols
        *@param pSrc - the source symbol to connect
        *@param pDst - the destination symbol to connect
        *@param pModel - the model
        *@return true on success, otherwise false
        */
        bool DoProcessProcessConnection(PSS_ProcessSymbolBP* pSrc, PSS_ProcessSymbolBP* pDst, CODModel* pModel);

        /**
        * Checks the deliverable status
        */
        void CheckDeliverableStatus();

        /**
        * Save the properties to the quantity
        *@param props - the properties to save
        */
        void SavePropertiesToQuantity(const ZBPropertySet& props);

        /**
        * Sets a new number and equalizes the deliverable
        *@param prop - the property containing the number
        *@param props - the properties
        */
        void SetNewNumberAndEqualize(const PSS_Property& prop, const ZBPropertySet& props);

        /**
        * Saves the equalizer to the properties
        *@param[out] props - the properties
        */
        void SaveEqualizerToProperties(ZBPropertySet& props);

        /**
        * Adjusts the deliverable points
        */
        void AdjustPoints();

        /**
        * Gets the rule name by GUID
        *@param pRule - the rule for which the name should be get
        *@param ruleGUID - the rule GUID matching with the name to get
        *@return the rule name matching with the GUID
        */
        CString GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID);
};

//---------------------------------------------------------------------------
// PSS_DeliverableLinkSymbolBP
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::HasUnit() const
{
    return false;
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetUnitName() const
{
    return m_UnitProp.GetUnitName();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetUnitName(const CString& value)
{
    m_UnitProp.SetUnitName(value);
}
//---------------------------------------------------------------------------
float PSS_DeliverableLinkSymbolBP::GetUnitCost() const
{
    return m_UnitProp.GetUnitCost();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetUnitCost(const float value)
{
    m_UnitProp.SetUnitCost(value);
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetUnitGUID() const
{
    return m_UnitProp.GetUnitGUID();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetUnitGUID(const CString& value)
{
    m_UnitProp.SetUnitGUID(value);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetUnitDoubleValidationType() const
{
    return m_UnitProp.GetUnitDoubleValidationType();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetUnitDoubleValidationType(const int value)
{
    m_UnitProp.SetUnitDoubleValidationType(value);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::GetUnitDoubleValidationTypeStringArray(CStringArray& strArray) const
{
    m_UnitProp.GetUnitDoubleValidationTypeStringArray(strArray);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::ConvertUnitDoubleValidationString2Type(const CString& type) const
{
    return m_UnitProp.ConvertUnitDoubleValidationString2Type(type);
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetUnitDoubleValidationTypeString(const int value) const
{
    return m_UnitProp.GetUnitDoubleValidationTypeString(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::IncludeDescriptionArea() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::IncludeAttributeArea() const
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::RemoveAllRules()
{
    SetRuleList(_T(""));
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::RemoveAllTextItems()
{
    SetTextItemList(_T(""));
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetProcessingTime() const
{
    return m_CostDeliverableProperties.GetProcessingTime();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetProcessingTime(const double value)
{
    m_CostDeliverableProperties.SetProcessingTime(value);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetInWorkloadPercent(const float value)
{
    m_CostDeliverableProperties.SetInWorkloadPercent(value);
}
//---------------------------------------------------------------------------
float PSS_DeliverableLinkSymbolBP::GetOutWorkloadPercent() const
{
    return m_CostDeliverableProperties.GetOutWorkloadPercent();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetOutWorkloadPercent(const float value)
{
    m_CostDeliverableProperties.SetOutWorkloadPercent(value);
}
//---------------------------------------------------------------------------
float PSS_DeliverableLinkSymbolBP::GetUnitaryCost() const
{
    return m_CostDeliverableProperties.GetUnitaryCost();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetUnitaryCost(const float value)
{
    m_CostDeliverableProperties.SetUnitaryCost(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetCaseDuration() const
{
    return m_CostDeliverableProperties.GetCaseDuration();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetCaseDuration(const double value)
{
    m_CostDeliverableProperties.SetCaseDuration(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetCaseDurationMax() const
{
    return m_CostDeliverableProperties.GetCaseDurationMax();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetCaseDurationMax(const double value)
{
    m_CostDeliverableProperties.SetCaseDurationMax(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetTargetDuration() const
{
    return m_CostDeliverableProperties.GetTargetDuration();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetTargetDuration(const double value)
{
    m_CostDeliverableProperties.SetTargetDuration(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetGreenLineDuration() const
{
    return m_CostDeliverableProperties.GetGreenLineDuration();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetGreenLineDuration(const double value)
{
    m_CostDeliverableProperties.SetGreenLineDuration(value);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_DeliverableLinkSymbolBP::GetCost()
{
    return m_SimProperties.GetCost();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetCost(const double value)
{
    m_SimProperties.SetCost(value);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetCost(PSS_AnnualNumberPropertiesBP& AnnualNumberProp)
{
    m_SimProperties.GetCost() = AnnualNumberProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_DeliverableLinkSymbolBP::GetWorkloadForecast()
{
    return m_SimProperties.GetWorkloadForecast();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetWorkloadForecast(const double value)
{
    m_SimProperties.SetWorkloadForecast(value);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetWorkloadForecast(PSS_AnnualNumberPropertiesBP& AnnualNumberProp)
{
    m_SimProperties.GetWorkloadForecast() = AnnualNumberProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_DeliverableLinkSymbolBP::GetQuantity()
{
    return m_Quantity;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantity(PSS_AnnualNumberPropertiesBP& annualNumberProp)
{
    GetQuantity() = annualNumberProp;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityUsingOriginalEqualizer(PSS_AnnualNumberPropertiesBP& annualNumberProp)
{
    m_Quantity.SetAndCalculateQuantitiesBasedOnYear(annualNumberProp.GetNumberYear());
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityYear() const
{
    return m_Quantity.GetNumberYear();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityYear(const double value)
{
    m_Quantity.SetNumberYear(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityJanuary() const
{
    return m_Quantity.GetNumberJanuary();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityJanuary(const double value)
{
    m_Quantity.SetNumberJanuary(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityFebruary() const
{
    return m_Quantity.GetNumberFebruary();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityFebruary(const double value)
{
    m_Quantity.SetNumberFebruary(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityMarch() const
{
    return m_Quantity.GetNumberMarch();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityMarch(const double value)
{
    m_Quantity.SetNumberMarch(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityApril() const
{
    return m_Quantity.GetNumberApril();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityApril(const double value)
{
    m_Quantity.SetNumberApril(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityMay() const
{
    return m_Quantity.GetNumberMay();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityMay(const double value)
{
    m_Quantity.SetNumberMay(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityJune() const
{
    return m_Quantity.GetNumberJune();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityJune(const double value)
{
    m_Quantity.SetNumberJune(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityJuly() const
{
    return m_Quantity.GetNumberJuly();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityJuly(const double value)
{
    m_Quantity.SetNumberJuly(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityAugust() const
{
    return m_Quantity.GetNumberAugust();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityAugust(const double value)
{
    m_Quantity.SetNumberAugust(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantitySeptember() const
{
    return m_Quantity.GetNumberSeptember();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantitySeptember(const double value)
{
    m_Quantity.SetNumberSeptember(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityOctober() const
{
    return m_Quantity.GetNumberOctober();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityOctober(const double value)
{
    m_Quantity.SetNumberOctober(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityNovember() const
{
    return m_Quantity.GetNumberNovember();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityNovember(const double value)
{
    m_Quantity.SetNumberNovember(value);
}
//---------------------------------------------------------------------------
double PSS_DeliverableLinkSymbolBP::GetQuantityDecember() const
{
    return m_Quantity.GetNumberDecember();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetQuantityDecember(const double value)
{
    m_Quantity.SetNumberDecember(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityYear() const
{
    return m_Quantity.GetLockNumberYear();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityYear(const bool value)
{
    m_Quantity.SetLockNumberYear(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityJanuary() const
{
    return m_Quantity.GetLockNumberJanuary();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityJanuary(const bool value)
{
    m_Quantity.SetLockNumberJanuary(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityFebruary() const
{
    return m_Quantity.GetLockNumberFebruary();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityFebruary(const bool value)
{
    m_Quantity.SetLockNumberFebruary(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityMarch() const
{
    return m_Quantity.GetLockNumberMarch();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityMarch(const bool value)
{
    m_Quantity.SetLockNumberMarch(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityApril() const
{
    return m_Quantity.GetLockNumberApril();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityApril(const bool value)
{
    m_Quantity.SetLockNumberApril(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityMay() const
{
    return m_Quantity.GetLockNumberMay();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityMay(const bool value)
{
    m_Quantity.SetLockNumberMay(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityJune() const
{
    return m_Quantity.GetLockNumberJune();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityJune(const bool value)
{
    m_Quantity.SetLockNumberJune(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityJuly() const
{
    return m_Quantity.GetLockNumberJuly();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityJuly(const bool value)
{
    m_Quantity.SetLockNumberJuly(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityAugust() const
{
    return m_Quantity.GetLockNumberAugust();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityAugust(const bool value)
{
    m_Quantity.SetLockNumberAugust(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantitySeptember() const
{
    return m_Quantity.GetLockNumberSeptember();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantitySeptember(const bool value)
{
    m_Quantity.SetLockNumberSeptember(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityOctober() const
{
    return m_Quantity.GetLockNumberOctober();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityOctober(const bool value)
{
    m_Quantity.SetLockNumberOctober(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityNovember() const
{
    return m_Quantity.GetLockNumberNovember();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityNovember(const bool value)
{
    m_Quantity.SetLockNumberNovember(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetLockQuantityDecember() const
{
    return m_Quantity.GetLockNumberDecember();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetLockQuantityDecember(const bool value)
{
    m_Quantity.SetLockNumberDecember(value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetForceEqualizer() const
{
    return m_Quantity.GetForceEqualizer();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetForceEqualizer(bool value)
{
    m_Quantity.SetForceEqualizer(value);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetRiskCount() const
{
    return m_Risks.GetRiskCount();
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetRiskName(std::size_t index) const
{
    return m_Risks.GetRiskName(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskName(std::size_t index, const CString& value)
{
    m_Risks.SetRiskName(index, value);
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetRiskDesc(std::size_t index) const
{
    return m_Risks.GetRiskDesc(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskDesc(std::size_t index, const CString& value)
{
    m_Risks.SetRiskDesc(index, value);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskType(std::size_t index, const CString& value)
{
    m_Risks.SetRiskType(index, value);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetRiskImpact(std::size_t index) const
{
    return m_Risks.GetRiskImpact(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskImpact(std::size_t index, int value)
{
    m_Risks.SetRiskImpact(index, value);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetRiskProbability(std::size_t index) const
{
    return m_Risks.GetRiskProbability(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskProbability(std::size_t index, int value)
{
    m_Risks.SetRiskProbability(index, value);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetRiskSeverity(std::size_t index) const
{
    return m_Risks.GetRiskSeverity(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskSeverity(std::size_t index, int value)
{
    m_Risks.SetRiskSeverity(index, value);
}
//---------------------------------------------------------------------------
float PSS_DeliverableLinkSymbolBP::GetRiskUE(std::size_t index) const
{
    return m_Risks.GetRiskUE(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskUE(std::size_t index, float value)
{
    m_Risks.SetRiskUE(index, value);
}
//---------------------------------------------------------------------------
float PSS_DeliverableLinkSymbolBP::GetRiskPOA(std::size_t index) const
{
    return m_Risks.GetRiskPOA(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskPOA(std::size_t index, float value)
{
    m_Risks.SetRiskPOA(index, value);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::GetRiskAction(std::size_t index) const
{
    return m_Risks.GetRiskAction(index);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRiskAction(std::size_t index, bool value)
{
    m_Risks.SetRiskAction(index, value);
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetRightSubMenu() const
{
    return 3;
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::GetIconIndex() const
{
    return (IsLocal()) ? 6 : 14;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliverableLinkSymbolBP::OnDoubleClick()
{
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_DeliverableLinkSymbolBP::AddNewRisk()
{
    return m_Risks.AddNewRisk();
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DeleteRisk(std::size_t index)
{
    return m_Risks.DeleteRisk(index);
}
//---------------------------------------------------------------------------

#endif
