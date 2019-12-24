/****************************************************************************
 * ==> PSS_ProcessGraphModelMdl --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelMdlH
#define PSS_ProcessGraphModelMdlH

#if _MSC_VER >= 1000
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
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// processsoft
#include "zBaseLib\PSS_UserManager.h"
#include "zBaseLib\PSS_Subject.h"
#include "zBaseSym\PSS_ObjectPath.h"
#include "zBaseSym\PSS_BasicSymbolAcceptVisitor.h"
#include "zBaseSym\PSS_BasicSymbolVisitor.h"
#include "zBaseSym\PSS_NavigableModel.h"
#include "zProperty\ZIProperties.h"
#include "zEvent\PSS_ActivityResources.h"
#include "ZBUserGroupEntity.h"
#include "ZBLogicalSystemEntity.h"
#include "PSS_LogicalPrestationsEntity.h"
#include "PSS_LogicalRulesEntity.h"

// resources
#include "PSS_LanguageDefs.h"

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
class PSS_Symbol;
class PSS_LinkSymbol;
class PSS_Log;
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelViewport;
class PSS_ProcessGraphModelView;
class PSS_ProcessGraphModelController;
class ZDProcessGraphPage;
class ZBUserGroupEntity;
class ZBPropertyAttributes;
class ZBUserEntity;
class ZBLogicalSystemEntity;
class PSS_LogicalPrestationsEntity;
class ZBPrestationsEntity;
class PSS_LogicalRulesEntity;
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

// scope symbols in stingray foundation library
using namespace sfl;

class AFX_EXT_CLASS PSS_ProcessGraphModelMdl : public CODModel,
                                               public PSS_Subject,
                                               public PSS_ObjectPath,
                                               public ZIProperties,
                                               public PSS_NavigableModel,
                                               public PSS_BasicSymbolAcceptVisitor
{
    DECLARE_SERIAL(PSS_ProcessGraphModelMdl)

    public:
        typedef CCArray_T<ZDProcessGraphPage*, ZDProcessGraphPage*> IProcessGraphPageSet;
        typedef Iterator_T<ZDProcessGraphPage*>                     IProcessGraphPageIterator;

        /**
        * Constructor
        *@param name - model name
        *@param pParent - parent model, can be NULL
        */
        PSS_ProcessGraphModelMdl(const CString& name = _T(""), PSS_ProcessGraphModelMdl* pParent = NULL);

        virtual ~PSS_ProcessGraphModelMdl();

        /**
        * Deletes the model set
        */
        virtual void DeleteModelSet();

        /**
        * Detaches all the observers in the hierarchy
        *@param pViewport - the viewport
        *@param pDocument - the model document
        */
        virtual void DetachAllObserversInHierarchy(PSS_ProcessGraphModelViewport* pViewport,
                                                   PSS_ProcessGraphModelDoc*      pDocument);

        /**
        * Creates a controller for the model
        *@param pVp - the viewport
        *@return the model controller, NULL on error
        */
        virtual PSS_ProcessGraphModelController* CreateController(PSS_ProcessGraphModelViewport* pVp);

        /**
        * Creates a viewport for the model
        *@param pView - the view
        *@return the model viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* CreateViewport(PSS_ProcessGraphModelView* pView);

        /**
        * Gets the owner document
        *@return the owner document
        */
        virtual       CDocument* GetDocument();
        virtual const CDocument* GetDocument() const;

        /**
        * Gets the owner controller
        *@return the owner controller
        */
        virtual inline       CODController* GetController();
        virtual inline const CODController* GetController() const;

        /**
        * Sets a new controller for this model
        *@param pCtrl - the model controller
        */
        virtual inline void SetController(CODController* pCtlr);

        /**
        * Gets the model notation
        *@return the model notation
        */
        virtual inline EModelNotation GetNotation() const;

        /**
        * Sets the model notation
        *@param value - the model notation
        */
        virtual inline void SetNotation(EModelNotation value);

        /**
        * Checks if the model is in the ABC notation
        *@return true if the model is in the ABC notation, otherwise false
        */
        virtual inline bool IsModelInABCNotation() const;

        /**
        * Checks if the model is in the UML notation
        *@return true if the model is in the UML notation, otherwise false
        */
        virtual inline bool IsModelInUMLNotation() const;

        /**
        * Checks if the model is in the Beryl notation
        *@return true if the model is in the Beryl notation, otherwise false
        */
        virtual inline bool IsModelInBerylNotation() const;

        /**
        * Checks if the model notation is unknown
        *@return true if the model notation is unknown, otherwise false
        */
        virtual inline bool IsModelNotationUnknow() const;

        /**
        * Gets if the consistency should be checked
        *@return true if the consistency should be checked, otherwise false
        */
        virtual bool GetCheckConsistency() const;

        /**
        * Sets if the consistency should be checked
        *@param value - if true, the consistency should be checked
        */
        virtual void SetCheckConsistency(bool value);

        /**
        * Gets if the cost simulation should be integrated
        *@return true if the cost simulation should be integrated, otherwise false
        */
        virtual bool GetIntegrateCostSimulation() const;

        /**
        * Sets if the cost simulation should be integrated
        *@param value - if true, the cost simulation should be integrated
        */
        virtual void SetIntegrateCostSimulation(bool value);

        /**
        * Gets if the workflow should be used
        *@return true if the workflow should be used, otherwise false
        */
        virtual bool GetUseWorkflow() const;

        /**
        * Sets if the workflow should be used
        *@param value - if true, the workflow should be used
        */
        virtual void SetUseWorkflow(bool value);

        /**
        * Gets if the page border should be shown
        *@return true if the page border should be shown, otherwise false
        */
        virtual bool GetShowPageBorder() const;

        /**
        * Sets if the page border should be shown
        *@param value - if true, the page border should be shown
        */
        virtual void SetShowPageBorder(bool value);

        /**
        * Gets the model language
        *@return the model language
        */
        virtual const ELanguage GetLanguage();

        /**
        * Sets the model language
        *@param value - the model language
        */
        virtual void SetLanguage(ELanguage value);

        /**
        * Checks if the model is in cut operation
        *@return true if the model is in cut operation, otherwise false
        */
        virtual inline bool IsInCutOperation();

        /**
        * Sets the the model as in cut operation
        *@param value - if true, the model will be in cut operation
        */
        virtual inline void SetInCutOperation(bool value);

        /**
        * Gets the image resource identifier
        *@return the image resource identifier
        */
        virtual inline UINT GetSymbolImageIDRes() const;

        /**
        * Gets the main user group
        *@return the main user group, NULL on error
        */
        static inline ZBUserGroupEntity* GetMainUserGroup();

        /**
        * Assigns the main user group
        *@param pMainUserGroup - the main user group
        */
        static inline void AssignMainUserGroup(ZBUserGroupEntity* pMainUserGroup);

        /**
        * Checks if the main user group is valid
        *@return true if the main user group is valid, otherwise false
        */
        virtual inline bool MainUserGroupIsValid() const;

        /**
        * Sets the main user group as valid
        *@param value - if true, the main user group is valid
        */
        virtual inline void SetMainUserGroupValid(bool value = true);

        /**
        * Retrieves the unit global unique identifier
        *@param name - the unit name
        *@param[out] error - if true, an error occurred while the unit global unique identifier was retrieved
        *@return the unit global unique identifier
        */
        virtual CString RetrieveUnitGUID(const CString& name, bool& error) const;

        /**
        * Retrieves the unit name from its unit global unique identifier
        *@param guid - the unit global unique identifier
        *@param[out] error - if true, an error occurred while the unit name was retrieved
        *@return the unit name
        */
        virtual CString RetrieveUnitName(const CString& guid, bool& error) const;

        /**
        * Retrieves the unit description from its unit global unique identifier
        *@param guid - the unit global unique identifier
        *@param[out] error - if true, an error occurred while the unit name was retrieved
        *@return the unit description
        */
        virtual CString RetrieveUnitDescription(const CString& guid, bool& error) const;

        /**
        * Retrieves the unit cost from its unit global unique identifier
        *@param guid - the unit global unique identifier
        *@param[out] error - if true, an error occurred while the unit name was retrieved
        *@return the unit cost
        */
        virtual float RetrieveUnitCost(const CString& guid, bool& error) const;

        /**
        * Reassigns the unit
        *@param pLog - the log
        */
        virtual void ReassignUnit(PSS_Log* pLog = NULL);

        /**
        * Gets the main logical system
        *@return the main logical system, NULL on error
        */
        static inline ZBLogicalSystemEntity* GetMainLogicalSystem();

        /**
        * Assigns the main logical system
        *@param pMainLogicalSystem - the main logical system
        */
        static inline void AssignMainLogicalSystem(ZBLogicalSystemEntity* pMainLogicalSystem);

        /**
        * Checks if the main logical system is valid
        *@return true if the main logical system is valid, otherwise false
        */
        virtual inline bool MainLogicalSystemIsValid() const;

        /**
        * Sets the main logical system as valid
        *@param value - if true, the main logical system is valid
        */
        virtual inline void SetMainLogicalSystemValid(bool value = true);

        /**
        * Retrieves the logical system global unique identifier
        *@param name - the logical system name
        *@param[out] error - if true, an error occurred while the logical system global unique identifier was retrieved
        *@return the logical system global unique identifier
        */
        virtual CString RetrieveLogicalSystemGUID(const CString& name, bool& error) const;

        /**
        * Retrieves the logical system name from its unit global unique identifier
        *@param guid - the logical system global unique identifier
        *@param[out] error - if true, an error occurred while the logical system name was retrieved
        *@return the logical system name
        */
        virtual CString RetrieveLogicalSystemName(const CString& guid, bool& error) const;

        /**
        * Retrieves the logical system description from its unit global unique identifier
        *@param guid - the logical system global unique identifier
        *@param[out] error - if true, an error occurred while the logical system description was retrieved
        *@return the logical system description
        */
        virtual CString RetrieveLogicalSystemDescription(const CString& guid, bool& error) const;

        /**
        * Reassigns the logical system
        *@param pLog - the log
        */
        virtual void ReassignSystem(PSS_Log* pLog = NULL);

        /**
        * Gets the main logical prestations
        *@return the main logical prestations, NULL on error
        */
        static inline PSS_LogicalPrestationsEntity* GetMainLogicalPrestations();

        /**
        * Assigns the main logical prestations
        *@param pMainLogicalPrestations - the main logical prestations
        */
        static inline void AssignMainLogicalPrestations(PSS_LogicalPrestationsEntity* pMainLogicalPrestations);

        /**
        * Checks if the main logical prestations are valid
        *@return true if the main logical prestations are valid, otherwise false
        */
        virtual inline bool MainLogicalPrestationsIsValid() const;

        /**
        * Sets the main logical prestations as valid
        *@param value - if true, the main logical prestations are valid
        */
        virtual inline void SetMainLogicalPrestationsValid(bool value = true);

        /**
        * Retrieves the logical prestation name from its unit global unique identifier
        *@param guid - the logical prestation global unique identifier
        *@param[out] error - if true, an error occurred while the logical prestation name was retrieved
        *@return the logical system name
        */
        virtual CString RetrievePrestationName(const CString& guid, bool& error) const;

        /**
        * Reassigns the logical prestations
        *@param pLog - the log
        */
        virtual void ReassignPrestations(PSS_Log* pLog = NULL);

        /**
        * Gets the main logical rules
        *@return the main logical rules, NULL on error
        */
        static inline PSS_LogicalRulesEntity* GetMainLogicalRules();

        /**
        * Assigns the main logical rules
        *@param pMainLogicalRules - the main logical rules
        */
        static inline void AssignMainLogicalRules(PSS_LogicalRulesEntity* pMainLogicalRules);

        /**
        * Checks if the main logical rules are valid
        *@return true if the main logical rules are valid, otherwise false
        */
        virtual inline bool MainLogicalRulesIsValid() const;

        /**
        * Sets the main logical rules as valid
        *@param value - if true, the main logical rules are valid
        */
        virtual inline void SetMainLogicalRulesValid(bool value = true);

        /**
        * Retrieves the rule name from its unit global unique identifier
        *@param guid - the rule global unique identifier
        *@param[out] error - if true, an error occurred while the logical rule name was retrieved
        *@return the logical rule name
        */
        virtual CString RetrieveRuleName(const CString guid, bool& error) const;

        /**
        * Reassigns the logical rules
        *@param pLog - the log
        */
        virtual void ReassignRules(PSS_Log* pLog = NULL);

        /**
        * Checks if the main page set exists
        *@return true if the main page set exists, otherwise false
        */
        virtual inline bool MainPageSetExist();

        /**
        * Checks if the model has a page set
        *@return true if the model has a page set, otherwise false
        */
        virtual inline bool HasPageSet() const;

        /**
        * Gets the main page set
        *@return the main page set, NULL on error
        */
        virtual IProcessGraphPageSet* GetMainPageSet();

        /**
        * Gets the page set
        *@return the page set, NULL on error
        */
        virtual inline IProcessGraphPageSet* GetPageSet();

        /**
        * Allocates the main page set
        *@return the newly allocated main page set, NULL on error
        */
        virtual IProcessGraphPageSet* AllocateMainPageSet();

        /**
        * Allocates the page set
        *@return the newly allocated page set, NULL on error
        */
        virtual IProcessGraphPageSet* AllocatePageSet();

        /**
        * Gets the root main model page
        *@return the root main model page, NULL on error
        */
        virtual ZDProcessGraphPage* GetRootMainModelPage();

        /**
        * Gets the root main model page
        *@param pPage - the root main model page
        */
        virtual void SetRootMainModelPage(ZDProcessGraphPage* pPage);

        /**
        * Gets the main model page
        *@return the main model page, NULL on error
        */
        virtual ZDProcessGraphPage* GetMainModelPage();

        /**
        * Sets the main model page
        *@param pPage - the main model page
        */
        virtual void SetMainModelPage(ZDProcessGraphPage* pPage);

        /**
        * Finds the model page
        *@param modelName - the model name to search in
        *@param inSubModel - if true, the search should be extended to sub-models
        *@return the model page, NULL if not found or on error
        */
        virtual ZDProcessGraphPage* FindModelPage(const CString& modelName, bool inSubModel = false);

        /**
        * Finds the model page
        *@param pModel - the model to search in
        *@param inSubModel - if true, the search should be extended to sub-models
        *@return the model page, NULL if not found or on error
        */
        virtual ZDProcessGraphPage* FindModelPage(PSS_ProcessGraphModelMdl* pModel, bool inSubModel = false);

        /**
        * Finds the page
        *@param pageName - the page name to search
        *@return the page, NULL if not found or on error
        */
        virtual ZDProcessGraphPage* FindPage(const CString& pageName);

        /**
        * Checks if a page exists
        *@param pageName - the page name to search
        *@return true if the page exists, otherwise false
        */
        virtual bool PageExist(const CString& pageName);

        /**
        * Creates a new page
        *@param pModel - the model which will contain the page
        *@param pageName - the page name
        *@param pInModel - in model
        *@return the newly created page, NULL on error
        */
        virtual ZDProcessGraphPage* CreateNewPage(PSS_ProcessGraphModelMdl* pModel,
                                                  const CString&            pageName = _T(""),
                                                  PSS_ProcessGraphModelMdl* pInModel = NULL);

        /**
        * Gets the valid next page name
        *@return the valid next page name
        */
        virtual CString GetValidNextPageName();

        /**
        * Gets the existing page name array
        *@return the existing page name array, NULL on error
        */
        virtual CStringArray* GetExistingPageNameArray();

        /**
        * Deletes a page
        *@param pageName - the page name to delete
        *@param deleteModel - if true, the model will also be deleted
        *@return true on success, otherwise false
        */
        virtual bool DeletePage(const CString& pageName, bool deleteModel = false);

        /**
        * Notifies about the page deletion
        *@param pPage - the deleting page
        */
        virtual void NotifyDeletePage(ZDProcessGraphPage* pPage);

        /**
        * Gets the owner page model
        *@param pLookForPage - the page which should be looked for
        *@return the owner page model, NULL on error
        */
        virtual PSS_ProcessGraphModelMdl* GetOwnerPageModel(ZDProcessGraphPage* pLookForPage);

        /**
        * Propagates the new symbol attributes
        *@param pAttributes - the new attributes to propagate
        *@param objectID - the object identifier
        */
        virtual void PropagateNewSymbolAttributes(ZBPropertyAttributes* pAttributes, int objectID);

        /**
        * Refreshes the symbol attributes
        *@param redraw - if true, the symbol will be redrawn immediately
        */
        virtual void RefreshSymbolAttributes(bool redraw = false);

        /**
        * Checks if the model has properties
        *@return true if the model has properties, otherwise false
        */
        virtual bool HasProperties() const;

        /**
        * Fills a property set with the model properties
        *@param[out] props - the property set to fill with the model properties
        *@param numericValue - if true, only the numeric values will be get
        *@param groupValue - if true, the values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(ZBPropertySet& props, bool numericValue = false, bool groupValue = false);

        /**
        * Saves the new changes to the model properties
        *@param props - the property set containing the changes to save
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(ZBPropertySet& props);

        /**
        * Fills a model property
        *@param[out] prop - the property to fill
        *@return true on success, otherwise false
        */
        virtual bool FillProperty(ZBProperty& prop);

        /**
        * Saves the new changes to a property in the model
        *@param prop - the property containing the changes to save
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(ZBProperty& prop);

        /**
        * Checks the property value
        *@parap prop - the property to check
        *@param value - the value to check against
        *@param props - the property set at which the property belongs
        *@return true if check succeeded, otherwise false
        */
        virtual bool CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@parap prop - the property to process
        *@param value - the property value
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the model will be refreshed immediately
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - the menu command identifier to process
        *@param prop - the property for which the menu command should be processed
        *@param value - the property value
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the model will be refreshed immediately
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int            menuCmdID,
                                        ZBProperty&    prop,
                                        CString&       value,
                                        ZBPropertySet& props,
                                        bool&          refresh);

        /**
        * Creates the symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

        /**
        * Checks if properties are read-only
        *@return true if properties are read-only, otherwise false
        */
        virtual bool IsPropertiesReadOnly() const;

        /**
        * Clears the path
        */
        virtual void ClearPath();

        /**
        * Calculates the absolute path
        */
        virtual void CalculateAbsolutePath();

        /**
        * Checks if the unique symbol name was already allocated
        *@param symbolName - the symbol name to check
        *@returnt true if the unique symbol name was already allocated, otherwise false
        */
        virtual bool SymbolNameAlreadyAllocated(const CString& symbolName);

        /**
        * Checks if the unique reference number was already allocated
        *@param refNumber - the reference number to check
        *@returnt true if the unique reference number was already allocated, otherwise false
        */
        virtual bool ReferenceNumberAlreadyAllocated(int refNumber);

        /**
        * Checks if the unique reference number was already allocated
        *@param refNumber - the string containing the reference number to check
        *@returnt true if the unique reference number was already allocated, otherwise false
        */
        virtual bool ReferenceNumberAlreadyAllocated(const CString& refNumber);

        /**
        * Gets the next available reference number as a string
        *@return the string containing the next available reference number
        */
        virtual CString GetNextAvailableReferenceNumberStr();

        /**
        * Gets the next available reference number
        *@param pRootModel - the root model to search from, if NULL the search will be performed in the cuurent model
        *@return the next available reference number
        */
        virtual int GetNextAvailableReferenceNumber(PSS_ProcessGraphModelMdl* pRootModel = NULL);

        /**
        * Gets an array containing all the existing reference numbers
        *@return an array containing all the existing reference numbers, NULL on error
        */
        virtual CStringArray* GetExistingReferenceNumberArray();

        /**
        * Checks if the object can be visited
        *@param visitor - the visitor
        *@return true if the object can be visited, otherwise false
        */
        virtual bool AcceptVisitor(PSS_BasicSymbolVisitor& visitor);

        /**
        * Gets the start symbols
        *@param nodes - the nodes that will contain the start symbols
        *@param deep - if true, the search will also be performed in the children symbols
        *@return the found start symbol count
        */
        virtual std::size_t GetStartSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Generates the model workflow
        *@param pLog - the log
        *@param pDoc - the model document
        *@return true on success, otherwise false
        */
        virtual bool GenerateModelWorkflow(PSS_Log* pLog, PSS_ProcessGraphModelDoc* pDoc);

        /**
        * Checks the model workflow
        *@param pLog - the log
        *@param modelIsClean - if TRUE, the model is clean
        *@return true if the model workflow was validated, otherwise false
        */
        virtual bool CheckModelWorkflow(PSS_Log* pLog, BOOL modelIsClean);

        /**
        * Sets the default workflow property
        *@param redefineOnExisting - if true, the default property will be redefined if already exists
        */
        virtual void SetDefaultWkfProperty(bool redefineOnExisting = false);

        /**
        * Deletes all the activities linked to the workflow
        */
        virtual void DeleteAllActivitiesLinkedToWorkflow();

        /**
        * Recalculates the parent
        */
        virtual void RecalculateParent();

        /**
        * Recalculates the child model
        */
        virtual void RecalculateChildModel();

        /**
        * Recalculates the reference
        */
        virtual void RecalculateReference();

        /**
        * Recalculates the symbol references
        */
        virtual void RecalculateSymbolReferences();

        /**
        * Gets the symbol model
        *@param pSymbolToFind - the symbol to find
        *@return the symbol model, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* GetSymbolModel(PSS_Symbol* pSymbolToFind);

        /**
        * Gets the link symbol model
        *@param pSymbolToFind - the symbol to find
        *@return the symbol model, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* GetLinkSymbolModel(PSS_LinkSymbol* pSymbolToFind);

        /**
        * Gets the root model
        *@return the root model, NULL on error
        */
        virtual PSS_ProcessGraphModelMdl* GetRoot();

        /**
        * Gets the parent model
        *@return the parent model, NULL on error
        */
        virtual inline PSS_ProcessGraphModelMdl* GetParent();

        /**
        * Sets the parent model
        *@param pModel - the parent model
        */
        virtual void SetParent(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Creates an empty model
        *@param name - the model name
        *@param pParent - the parent model
        *@return the newly created model
        */
        virtual inline PSS_ProcessGraphModelMdl* CreateEmptyModel(const CString&            name    = _T(""),
                                                                  PSS_ProcessGraphModelMdl* pParent = NULL);

        /**
        * Sets the background component
        *@param bgComp - the background component
        *@param toAll - if true, the background should be applied to all children
        *@param stretchToModel - if true, the background should be stretched to model
        */
        virtual void SetBackgroundComponent(CODComponent& bgComp, bool toAll = true, bool stretchToModel = false);

        /**
        * Clears the background component
        *@param toAll - if true, the background should be cleared in all children
        */
        virtual void ClearBackgroundComponent(bool toAll = true);

        /**
        * Redraws the component
        *@param comp - the component to redraw
        */
        virtual void RedrawComponent(CODComponent& comp);

        /**
        * Redraws all the components contained in the set
        *@param compSet - the set containing the components to redraw
        */
        virtual void RedrawComponentSet(CODComponentSet& compSet);

        /**
        * Selects all components
        */
        virtual void SelectAllComponents();

        /**
        * Unselects all components
        */
        virtual void UnselectAllComponents();

        /**
        * Selects a component
        *@param comp - the component to select
        */
        virtual void SelectComponent(CODComponent& comp);

        /**
        * Selects all components contained in the set
        *@param compSet - the set containing the components to select
        */
        virtual void SelectComponentSet(CODComponentSet& compSet);

        /**
        * Unselects a component
        *@param comp - the component to unselect
        */
        virtual void UnselectComponent(CODComponent& comp);

        /**
        * Selects all components contained in the set
        *@param compSet - the set containing the components to select
        */
        virtual void UnselectComponentSet(CODComponentSet& compSet);

        /**
        * Checks if a component is selected
        *@param comp - the component to check
        *@return true if the component is selected, otherwise false
        */
        virtual bool IsComponentSelected(CODComponent& comp);

        /**
        * Deletes a component from the model
        *@param pComp - the component to delete
        */
        virtual void DeleteComponent(CODComponent* pComp);

        /**
        * Deletes all the components contained in a set from the model
        *@param pCompSet - the set containing the components to delete
        */
        virtual void DeleteComponents(CODComponentSet* pCompSet);

        /**
        * Checks if a symbol exists in the model
        *@param pCompToFind - the symbol component to search
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@return true if the symbol exists in the model, otherwise false
        */
        virtual bool SymbolExistInModel(CODComponent* pCompToFind, bool inSubModel = true);

        /**
        * Finds symbols
        *@param pCompToFind - the symbol component to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbol(CODComponent* pCompToFind, bool inSubModel = true);

        /**
        * Finds symbols
        *@param pCompToFind - the symbol component to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbol(CODModel* pModel, bool inSubModel = true, bool localOnly = false);

        /**
        * Finds symbols
        *@param name - the symbol name to find
        *@param path - the symbol path to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbol(const CString& name,
                                            const CString& path          = _T(""),
                                            bool           inSubModel    = true,
                                            bool           caseSensitive = false,
                                            bool           onlyLocal     = false);

        /**
        * Finds symbols from their paths
        *@param path - the symbol path to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolFromPath(const CString& path,
                                                    bool           inSubModel    = true,
                                                    bool           caseSensitive = false,
                                                    bool           onlyLocal     = false);

        /**
        * Finds symbols by their reference numbers
        *@param refNumber - the symbol reference number to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolByRefNumber(int refNumber, bool inSubModel = true);

        /**
        * Finds symbols from their partial names
        *@param name - the symbol partial name to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolPartialName(const CString& name,
                                                       bool           inSubModel    = true,
                                                       bool           caseSensitive = false,
                                                       bool           onlyLocal     = false);

        /**
        * Finds items
        *@param argument - the search argument
        *@param pLog - the log
        *@param pPropAttributes - the property attributes
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param partialSearch - if true, the search will stop on the first matching item found
        *@return the found matching item count
        */
        virtual std::size_t Find(const CString&        argument,
                                 PSS_Log*              pLog,
                                 ZBPropertyAttributes* pPropAttributes = NULL,
                                 bool                  inSubModel      = true,
                                 bool                  caseSensitive   = false,
                                 bool                  partialSearch   = false);

        /**
        * Finds a model
        *@param name - the model name to search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param pRootModel - the root model to search from, if NULL the search will be performed from the current model
        *@return the model, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* FindModel(const CString&            name,
                                                    bool                      caseSensitive = false,
                                                    PSS_ProcessGraphModelMdl* pRootModel    = NULL);

        /**
        * Finds a model from its path
        *@param path - the model path to search
        *@param caseSensitive - if true, the search will be case sensitive
        *@return the model, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* FindModelFromPath(const CString& path, bool caseSensitive = false);

        /**
        * Checks if a sub-model exists
        *@param pModel - the sub-model to search
        *@return true if the sub-model exists, otherwise false
        */
        virtual bool SubModelExist(CODModel* pModel);

        /**
        * Checks if a sub-model exists
        *@param modelName - the sub-model name to search
        *@param caseSensitive - if true, the search will be case sensitive
        *@return true if the sub-model exists, otherwise false
        */
        virtual bool SubModelExist(const CString& modelName, bool caseSensitive = false);

        /**
        * Gets the meta-file handle
        *@return the meta-file handle
        */
        virtual inline HENHMETAFILE GetMetaFileHandle() const;

        /**
        * Sets the meta-file handle
        *@param hMetaFile - the meta-file handle
        */
        virtual inline void SetMetaFileHandle(HENHMETAFILE hMetaFile);

        /**
        * Draws a meta-file to the device context
        *@param pDC - the device context to draw to
        *@param rect - the rectangle surrounding the paint area
        */
        virtual void DrawMetaFile(CDC* pDC, const CRect& rect);

        /**
        * Recalculates all the process links
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RecalculateAllLinks();

        /**
        * Gets the model name
        *@return the model name
        */
        virtual const CString GetModelName() const;

        /**
        * Sets the model name
        *@param value - the model name
        */
        virtual void SetModelName(const CString& value);

        /**
        * Gets the model description
        *@return the model description
        */
        virtual const CString GetDescription() const;

        /**
        * Sets the model description
        *@param value - the model description
        */
        virtual void SetDescription(const CString& value);

        /**
        * Gets the connected user
        *@return the connected user
        */
        virtual inline const CString GetConnectedUser() const;

        /**
        * Sets the connected user
        *@param value - the connected user
        */
        virtual inline void SetConnectedUser(const CString& value);

        /**
        * Gets the background file name
        *@return the background file name
        */
        virtual CString GetBkGndFileName() const;

        /**
        * Sets the background file name
        *@param fileName - the background file name
        */
        virtual void SetBkGndFileName(const CString& fileName);

        /**
        * Checks if the background is a logo
        *@return TRUE if the background is a logo, otherwise FALSE
        */
        virtual BOOL IsLogo();

        /**
        * Sets if the background is a logo
        *@param isLogo - if TRUE, the background is a logo
        */
        virtual void SetIsLogo(BOOL isLogo);

        /**
        * Checks if the background must be restored
        *@return TRUE if the background must be restored, otherwise FALSE
        */
        virtual BOOL IsBkGndMustBeRestored() const;

        /**
        * Resets the background must be restored flag
        */
        virtual void ResetBkGndMustBeRestored();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Called when the model is read from the file
        *@return ar - the serialization archive
        */
        virtual void PostRead(CArchive& ar);

        /**
        * Called when the model is written to the file
        *@return ar - the serialization archive
        */
        virtual void PostWrite(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

        /**
        * Called when the document at which this model belongs is opened
        *@param documentVersion - the document version
        */
        virtual void OnPostOpenDocument(long documentVersion);

        /**
        * Called when the property is about to change
        *@param newValue - the new property value
        *@param prop - the changing property
        *@param props - the property set at which the property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props);

        /**
        * Called after the property changed
        *@param prop - the changed property
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the model will be refreshed immediately
        *@return true if the property content has changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh);

        /**
        * Called when an internal property drag&drop occured
        *@param srcProp - source property
        *@param dstProp - destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(ZBProperty&    srcProp,
                                                ZBProperty&    dstProp,
                                                bool           top2Down,
                                                ZBPropertySet& props);

        /**
        * Called when the symbol name changed
        *@param comp - the symbol component on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnSymbolNameChanged(CODComponent& Comp, const CString& oldName);

        /**
        * Called when the page name changed
        *@param pPage - the page on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnPageNameChanged(ZDProcessGraphPage* pPage, const CString& oldName);

        /**
        * Called when the user entity name changed
        *@param pUserEntity - the user entity on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString& oldName);

    protected:
        /**
        * Component reference
        */
        class IComponentRef
        {
            public:
                /**
                * Constructor
                *@param pSymbol - the symbol
                */
                IComponentRef(PSS_Symbol* pSymbol = NULL);

                /**
                * Adds a reference to the component
                */
                void AddRef();

                /**
                * Removes a reference from the component
                */
                void RemoveRef();

                /**
                * Gets the component reference count
                *@return the component reference count
                */
                std::size_t GetRef() const;

                /**
                * Gets the component reference count
                *@return the component reference count
                */
                PSS_Symbol* GetSymbol() const;
        
            private:
                PSS_Symbol* m_pSymbol;
                std::size_t m_Ref;
        };

        static ZBUserGroupEntity*                     m_pMainUserGroup;
        static ZBLogicalSystemEntity*                 m_pMainLogicalSystem;
        static PSS_LogicalPrestationsEntity*          m_pMainLogicalPrestations;
        static PSS_LogicalRulesEntity*                m_pMainLogicalRules;
        static CArray<IComponentRef*, IComponentRef*> m_SymbolParsed;
        static CODComponentSet                        m_FindSet;
        static int                                    m_RecursionCounter;
        static bool                                   m_IsInRecursion;
        CODController*                                m_pCtlr;
        IProcessGraphPageSet*                         m_pPageSet;
        EModelNotation                                m_Notation;
        CString                                       m_Name;
        bool                                          m_MainUserGroupIsValid;
        bool                                          m_MainLogicalSystemIsValid;
        bool                                          m_MainLogicalPrestationsIsValid;
        bool                                          m_MainLogicalRulesIsValid;
        bool                                          m_IsInCutOperation;

        /**
        * Deletes all the pages
        *@return true on success, otherwise false
        */
        virtual bool DeleteAllPages();

        /**
        * Deletes all the pages contained in the set
        *@return true on success, otherwise false
        */
        virtual bool DeleteAllPageInSet();

        /**
        * Serializes the page set content
        *@param ar - the archive
        */
        virtual void SerializePageSet(CArchive& ar);

        /**
        * Gets the symbols entering a symbol
        *@param pComp - the symbol from which the entering symbols should be found
        *@param[out] nodes - the node array which will contain the entering symbols
        *@return the found entering symbol count
        */
        virtual std::size_t GetEnteringSymbols(PSS_Symbol* pComp, CODNodeArray& nodes);

        /**
        * Gets the symbols following a symbol
        *@param pComp - the symbol from which the following symbols should be found
        *@param[out] nodes - the node array which will contain the following symbols
        *@return the found following symbol count
        */
        virtual std::size_t GetFollowingSymbols(PSS_Symbol* pComp, CODNodeArray& nodes);

        /**
        * Gets the symbols entering on the edge of a symbol
        *@param pComp - the symbol from which the entering symbols should be found
        *@param[out] edges - the edge array which will contain the entering symbols
        *@return the found entering symbol count
        */
        virtual std::size_t GetEdgesEntering(PSS_Symbol* pComp, CODEdgeArray& edges);

        /**
        * Gets the symbols leaving the edge of a symbol
        *@param pComp - the symbol from which the leaving symbols should be found
        *@param[out] edges - the edge array which will contain the leaving symbols
        *@return the found leaving symbol count
        */
        virtual std::size_t GetEdgesLeaving(PSS_Symbol* pComp, CODEdgeArray& edges);

        /**
        * Gets the symbols entering a generic symbol
        *@param pComp - the symbol from which the entering symbols should be found
        *@param[out] nodes - the node array which will contain the entering symbols
        *@param pClass - the symbol runtime class
        *@return the found entering symbol count
        */
        virtual std::size_t GetEnteringSymbolsISA(PSS_Symbol* pComp, CODNodeArray& nodes, const CRuntimeClass* pClass);

        /**
        * Gets the symbols following a generic symbol
        *@param pComp - the symbol from which the following symbols should be found
        *@param[out] nodes - the node array which will contain the following symbols
        *@param pClass - the symbol runtime class
        *@return the found following symbol count
        */
        virtual std::size_t GetFollowingSymbolsISA(PSS_Symbol* pComp, CODNodeArray& nodes, const CRuntimeClass* pClass);

        /**
        * Gets the symbols entering on the edge of a generic symbol
        *@param pComp - the symbol from which the entering symbols should be found
        *@param[out] edges - the edge array which will contain the entering symbols
        *@param pClass - the symbol runtime class
        *@return the found entering symbol count
        */
        virtual std::size_t GetEdgesEnteringISA(PSS_Symbol* pComp, CODEdgeArray& edges, const CRuntimeClass* pClass);

        /**
        * Gets the symbols leaving the edge of a generic symbol
        *@param pComp - the symbol from which the leaving symbols should be found
        *@param[out] edges - the edge array which will contain the leaving symbols
        *@param pClass - the symbol runtime class
        *@return the found leaving symbol count
        */
        virtual std::size_t GetEdgesLeavingISA(PSS_Symbol* pComp, CODEdgeArray& edges, const CRuntimeClass* pClass);

        /**
        * Keeps only a kind of generic symbol
        *@param[out] nodes - the node array which will contain the symbols to keep
        *@param pClass - the symbol runtime class
        *@return the kept symbol count
        */
        virtual std::size_t KeepOnlySymbolsISA(CODNodeArray& nodes, const CRuntimeClass* pClass);

        /**
        * Keeps only a kind of generic links
        *@param[out] edges - the edge array which will contain the links to keep
        *@param pClass - the link runtime class
        *@return the kept link count
        */
        virtual std::size_t KeepOnlyLinksISA(CODEdgeArray& edges, const CRuntimeClass* pClass);

        /**
        * Counts the activities in a symbol
        *@param pSymbol - the symbol for which the activities should be counted
        *@param nodes - the node array containing the activities to count
        *@return the activity count
        */
        virtual std::size_t CountActivities(PSS_Symbol* pSymbol, const CODNodeArray& nodes);

        /**
        * Counts the links connected to a symbol
        *@param pCompToFind - the symbol for which the connected links should be found
        *@param edges - the edge array containing the connected links
        *@return the found connected link count
        */
        virtual std::size_t CountLinks(CODLinkComponent* pCompToFind, const CODEdgeArray& edges);

        /**
        * Gets the symbols of type
        *@param[out] nodes - node array containing the found symbols
        *@param pClass - the symbol runtime class
        *@param deep - if true, the search will also be processed in the children
        *@return the found symbol count
        */
        virtual std::size_t GetSymbolsISA(CODNodeArray&        nodes,
                                          const CRuntimeClass* pClass,
                                          bool                 deep = false);

        /**
        * Finds symbols
        *@param pCompToFind - the symbol component to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolPvt(CODComponent* pCompToFind, bool inSubModel = true);

        /**
        * Finds symbols
        *@param pCompToFind - the symbol component to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolPvt(CODModel* pModel, bool inSubModel = true, bool onlyLocal = false);

        /**
        * Finds symbols
        *@param name - the symbol name to find
        *@param path - the symbol path to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolPvt(const CString& name,
                                               const CString& path          = _T(""),
                                               bool           inSubModel    = true,
                                               bool           caseSensitive = false,
                                               bool           onlyLocal     = false);

        /**
        * Finds symbols from their paths
        *@param path - the symbol path to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolFromPathPvt(const CString& path,
                                                       bool           inSubModel    = true,
                                                       bool           caseSensitive = false,
                                                       bool           onlyLocal     = false);

        /**
        * Finds symbols by their reference numbers
        *@param refNumber - the symbol reference number to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolByRefNumberPvt(int refNumber, bool inSubModel = true);

        /**
        * Finds symbols from their partial names
        *@param name - the symbol partial name to find
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param localOnly - if true, only the local components will be included in the search
        *@return a set containing the matching symbols, NULL if not found or on error
        */
        virtual CODComponentSet* FindSymbolPartialNamePvt(const CString& name,
                                                          bool           inSubModel    = true,
                                                          bool           caseSensitive = false,
                                                          bool           onlyLocal     = false);

        /**
        * Finds items
        *@param argument - the search argument
        *@param pLog - the log
        *@param pPropAttributes - the property attributes
        *@param inSubModel - if true, the sub-models will also be included in the search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param partialSearch - if true, the search will stop on the first matching item found
        *@return the found matching item count
        */
        virtual void FindPvt(const CString&        argument,
                             PSS_Log*              pLog,
                             ZBPropertyAttributes* pPropAttributes = NULL,
                             bool                  inSubModel      = true,
                             bool                  caseSensitive   = false,
                             bool                  partialSearch   = false);

        /**
        * Finds a model from its path
        *@param path - the model path to search
        *@param caseSensitive - if true, the search will be case sensitive
        *@return the model, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* FindModelFromPathPvt(const CString& path, bool caseSensitive = false);

        /**
        * Sets the background component to model
        *@param bgComp - the background component
        *@param stretchToModel - if true, the background will be stretched to the model
        */
        virtual void SetBackgroundComponentToModel(CODComponent& bgComp, bool stretchToModel = false);

        /**
        * Sets the background component to all items in the model
        *@param bgComp - the background component
        *@param stretchToModel - if true, the background will be stretched to the model
        */
        virtual void SetBackgroundComponentToAll(CODComponent& bgComp, bool stretchToModel = false);

        /**
        * Clears the model background component
        */
        virtual void ClearBackgroundComponentToModel();

        /**
        * Clears the background component in all model items
        */
        virtual void ClearBackgroundComponentToAll();

        /**
        * Adds a symbol in the array
        *@param pComp - the symbol to add
        *@return the symbol reference counter
        */
        virtual std::size_t AddSymbolInParsedArray(PSS_Symbol* pComp);

        /**
        * Finds a symbol in the array
        *@param pComp - the symbol to find
        *@return the symbol reference, NULL if not found or on error
        */
        virtual IComponentRef* FindSymbolInParsedArray(PSS_Symbol* pComp);

        /**
        * Removes all symbol in parsed array
        */
        virtual void RemoveAllSymbolInParsedArray();

    private:
        static std::size_t        m_FindCounter;
        PSS_ProcessGraphModelMdl* m_pParent;
        HENHMETAFILE              m_hMetaFile;
        CStringArray              m_AuthorizedUser;
        CString                   m_ParentName;
        CString                   m_ConnectedUser;
        CString                   m_BgFileName;
        int                       m_NextAvailableRefNb;
        BOOL                      m_BgFlag;
        BOOL                      m_IsLogo;

        /**
        * Gets the existing page name array
        *@param[out] pageArray - the page array which will be populated with the result
        */
        void GetExistingPageNameArray(CStringArray& pageArray);

        /**
        * Gets the next available reference number
        *@param pRootModel - the root model to search from, if NULL the search will be performed in the cuurent model
        *@return the next available reference number
        */
        int GetNextAvailableRefNb(PSS_ProcessGraphModelMdl* pRootModel);

        /**
        * Gets an array containing all the existing reference numbers
        *@param[out] refNbArray - the array that will contain the existing reference numbers
        */
        void GetExistingReferenceNumberArray(CStringArray& refNbArray);
};

//---------------------------------------------------------------------------
// PSS_ProcessGraphModelMdl
//---------------------------------------------------------------------------
CODController* PSS_ProcessGraphModelMdl::GetController()
{
    return m_pCtlr;
}
//---------------------------------------------------------------------------
const CODController* PSS_ProcessGraphModelMdl::GetController() const
{
    return m_pCtlr;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetController(CODController* pCtlr)
{
    m_pCtlr = pCtlr;
}
//---------------------------------------------------------------------------
EModelNotation PSS_ProcessGraphModelMdl::GetNotation() const
{
    return m_Notation;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetNotation(EModelNotation value)
{
    m_Notation = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsModelInABCNotation() const
{
    return (m_Notation == E_MN_ABC);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsModelInUMLNotation() const
{
    return (m_Notation == E_MN_UML);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsModelInBerylNotation() const
{
    return (m_Notation == E_MN_Beryl);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsModelNotationUnknow() const
{
    return (m_Notation == E_MN_Unknown);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsInCutOperation()
{
    return m_IsInCutOperation;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetInCutOperation(bool value)
{
    m_IsInCutOperation = value;
}
//---------------------------------------------------------------------------
UINT PSS_ProcessGraphModelMdl::GetSymbolImageIDRes() const
{
    return -1;
}
//---------------------------------------------------------------------------
ZBUserGroupEntity* PSS_ProcessGraphModelMdl::GetMainUserGroup()
{
    return m_pMainUserGroup;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::AssignMainUserGroup(ZBUserGroupEntity* pMainUserGroup)
{
    m_pMainUserGroup = pMainUserGroup;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::MainUserGroupIsValid() const
{
    return m_MainUserGroupIsValid;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetMainUserGroupValid(bool value)
{
    m_MainUserGroupIsValid = value;
}
//---------------------------------------------------------------------------
ZBLogicalSystemEntity* PSS_ProcessGraphModelMdl::GetMainLogicalSystem()
{
    return m_pMainLogicalSystem;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::AssignMainLogicalSystem(ZBLogicalSystemEntity* pMainLogicalSystem)
{
    m_pMainLogicalSystem = pMainLogicalSystem;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::MainLogicalSystemIsValid() const
{
    return m_MainLogicalSystemIsValid;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetMainLogicalSystemValid(bool value)
{
    m_MainLogicalSystemIsValid = value;
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_ProcessGraphModelMdl::GetMainLogicalPrestations()
{
    return m_pMainLogicalPrestations;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::AssignMainLogicalPrestations(PSS_LogicalPrestationsEntity* pMainLogicalPrestations)
{
    m_pMainLogicalPrestations = pMainLogicalPrestations;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::MainLogicalPrestationsIsValid() const
{
    return m_MainLogicalPrestationsIsValid;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetMainLogicalPrestationsValid(bool value)
{
    m_MainLogicalPrestationsIsValid = value;
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_ProcessGraphModelMdl::GetMainLogicalRules()
{
    return m_pMainLogicalRules;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::AssignMainLogicalRules(PSS_LogicalRulesEntity* pMainLogicalRules)
{
    m_pMainLogicalRules = pMainLogicalRules;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::MainLogicalRulesIsValid() const
{
    return m_MainLogicalRulesIsValid;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetMainLogicalRulesValid(bool value)
{
    m_MainLogicalRulesIsValid = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::MainPageSetExist()
{
    return GetMainPageSet();
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::HasPageSet() const
{
    return m_pPageSet;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::IProcessGraphPageSet* PSS_ProcessGraphModelMdl::GetPageSet()
{
    return m_pPageSet;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::CreateEmptyModel(const CString&            name,
                                                                     PSS_ProcessGraphModelMdl* pParent)
{
    return new PSS_ProcessGraphModelMdl(name, pParent);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::GetParent()
{
    return m_pParent;
}
//---------------------------------------------------------------------------
HENHMETAFILE PSS_ProcessGraphModelMdl::GetMetaFileHandle() const
{
    return m_hMetaFile;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetMetaFileHandle(HENHMETAFILE hMetaFile)
{
    if (m_hMetaFile)
        ::DeleteEnhMetaFile(m_hMetaFile);

    m_hMetaFile = hMetaFile;
}
//---------------------------------------------------------------------------
const CString PSS_ProcessGraphModelMdl::GetConnectedUser() const
{
    return m_ConnectedUser;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetConnectedUser(const CString& value)
{
    m_ConnectedUser = value;
}
//---------------------------------------------------------------------------

#endif
