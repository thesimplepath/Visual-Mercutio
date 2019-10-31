// ProcGraphModelMdl.h : interface of the ZDProcessGraphModelMdl class

#if !defined(AFX_OBJECTIVMDL_H__720C6641_0BFA_4FCA_A706_6D6312331D23__INCLUDED_)
#define AFX_OBJECTIVMDL_H__720C6641_0BFA_4FCA_A706_6D6312331D23__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_Subject.h"
#include "zBaseSym\ZIObjectPath.h"
#include "zProperty\ZIProperties.h"
#include "zBaseSym\ZIBasicSymbolAcceptVisitor.h"
#include "zBaseSym\ZIBasicSymbolVisitor.h"
#include "zBaseSym\ZINavigableModel.h"
#include "PSS_LanguageDefs.h"

// JMR-MODIF - Le 26 mai 2005 - Ajout de cet include pour résoudre une erreur de lien.
#include "zModel\ZBUserGroupEntity.h"

// JMR-MODIF - Le 19 novembre 2006 - Déplacé l'include ZBLogicalSystemEntity.h depuis fichier .cpp
#include "ZBLogicalSystemEntity.h"

// JMR-MODIF - Le 26 janvier 2006 - Ajout de l'en-tête ZBLogicalPrestationsEntity.h
#include "zModel\ZBLogicalPrestationsEntity.h"

// JMR-MODIF - Le 19 novembre 2006 - Ajout de l'en-tête ZBLogicalRulesEntity.h
#include "zModel\ZBLogicalRulesEntity.h"

// Forward declaration
class ZBSymbol;
class ZBLinkSymbol;
class PSS_Log;
class ZDProcessGraphModelDoc;
class ZIProcessGraphModelViewport;
class ZIProcessGraphModelView;
class ZDProcessGraphModelController;
class ZDProcessGraphPage;
class ZBUserGroupEntity;
class ZBPropertyAttributes;
class ZBUserEntity;
class ZBLogicalSystemEntity;
class ZBLogicalPrestationsEntity;
class ZBPrestationsEntity;
class ZBLogicalRulesEntity;
class ZBRulesEntity;

// processsoft
#include "zEvent\ZResourc.h"
#include "zBaseLib\PSS_UserManager.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 septembre 2005 - Ajout de la décoration unicode _T( ), nettoyage du code non utilisé.

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBProcessGraphPageSet | An array of ZBSymbolEntity pointers.
//@iex typedef CCArray_T<ZDProcessGraphPage*,ZDProcessGraphPage*> ZBProcessGraphPageSet;
typedef CCArray_T<ZDProcessGraphPage*, ZDProcessGraphPage*> ZBProcessGraphPageSet;

//@type ZBProcessGraphPageIterator | An iterator for ZBProcessGraphPageSet collections.
//@iex typedef Iterator_T<ZDProcessGraphPage*> ZBProcessGraphPageIterator;
typedef Iterator_T<ZDProcessGraphPage*> ZBProcessGraphPageIterator;

class AFX_EXT_CLASS ZDProcessGraphModelMdl : public CODModel,
    public PSS_Subject,
    public ZIObjectPath,
    public ZIProperties,
    public ZINavigableModel,
    public ZIBasicSymbolAcceptVisitor
{
    DECLARE_SERIAL(ZDProcessGraphModelMdl)

public:

    ZDProcessGraphModelMdl(const CString Name = _T(""), ZDProcessGraphModelMdl* pParent = NULL);
    virtual ~ZDProcessGraphModelMdl();

    // JMR-MODIF - Le 27 septembre 2005 - Ajout de la fonction DeleteModelSet.
    void                                    DeleteModelSet();

    // JMR-MODIF - Le 3 octobre 2005 - Ajout de la fonction DetachAllObserversInHierarchy.
    void                                    DetachAllObserversInHierarchy(ZIProcessGraphModelViewport*    m_pViewport,
                                                                          ZDProcessGraphModelDoc*        m_pDocument);

    // This method creates the associated controller
    virtual ZDProcessGraphModelController*    CreateController(ZIProcessGraphModelViewport* pVp);

    // This method creates the method associated viewport
    virtual ZIProcessGraphModelViewport*    CreateViewport(ZIProcessGraphModelView* pView);

    // Returns the owner document pointer
    CDocument*            GetDocument() const;
    const CDocument*    GetDocumentConst() const;

    // Returns the owner controller pointer as const
    const CODController* GetControllerConst() const
    {
        return m_pCtlr;
    }

    // Returns the owner controller pointer
    CODController* GetController()
    {
        return m_pCtlr;
    }

    // Sets a new controller for this model
    virtual void SetController(CODController* pCtlr)
    {
        m_pCtlr = pCtlr;
    }

    ///////////////////////////////////////////////////////
    // Notation methods
    EModelNotation GetNotation() const
    {
        return m_Notation;
    }

    void SetNotation(EModelNotation value)
    {
        m_Notation = value;
    }

    bool IsModelInABCNotation() const
    {
        return m_Notation == E_MN_ABC;
    }

    bool IsModelInUMLNotation() const
    {
        return m_Notation == E_MN_UML;
    }

    bool IsModelInBerylNotation() const
    {
        return m_Notation == E_MN_Beryl;
    }

    bool IsModelNotationUnknow() const
    {
        return m_Notation == E_MN_Unknown;
    }

    bool            GetCheckConsistency() const;
    void            SetCheckConsistency(bool value);

    bool            GetIntegrateCostSimulation() const;
    void            SetIntegrateCostSimulation(bool value);

    bool            GetUseWorkflow() const;
    void            SetUseWorkflow(bool value);

    bool            GetShowPageBorder() const;
    void            SetShowPageBorder(bool value);

    const ELanguage GetLanguage();
    void            SetLanguage(ELanguage value);

    bool IsInCutOperation()
    {
        return m_IsInCutOperation;
    }

    void SetInCutOperation(bool Value)
    {
        m_IsInCutOperation = Value;
    }

    // Returns the Image Resource ID for symbols
    virtual UINT GetSymbolImageIDRes() const
    {
        return -1;
    }

    // Once the model is read from the file, the PostRead method is called
    // from the document
    virtual void PostRead(CArchive& ar);

    // Once the model is written to the file, the PostWrite method is called
    // from the document
    virtual void PostWrite(CArchive& ar);

    // the OnPostOpenDocument method is called once the framework has 
    // open the document
    virtual void OnPostOpenDocument(long DocumentVersion);

    ///////////////////////////////////////////////////////
    // User group Get and Set methods
    static ZBUserGroupEntity* GetMainUserGroup()
    {
        return m_pMainUserGroup;
    }

    static void AssignMainUserGroup(ZBUserGroupEntity* pMainUserGroup)
    {
        m_pMainUserGroup = pMainUserGroup;
    }

    bool MainUserGroupIsValid() const
    {
        return m_MainUserGroupIsValid;
    }

    void SetMainUserGroupValid(bool value = true)
    {
        m_MainUserGroupIsValid = value;
    }

    // Unit retreival methods
    CString RetreiveUnitGUID(const CString Name, bool& Error) const;
    CString RetreiveUnitName(const CString GUID, bool& Error) const;
    CString RetreiveUnitDescription(const CString GUID, bool& Error) const;

    float    RetreiveUnitCost(const CString GUID, bool& Error) const;

    virtual void ReassignUnit(PSS_Log* pLog = NULL)
    {}

    ///////////////////////////////////////////////////////
    // Logical system Get and Set methods
    static ZBLogicalSystemEntity* GetMainLogicalSystem()
    {
        return m_pMainLogicalSystem;
    }

    static void AssignMainLogicalSystem(ZBLogicalSystemEntity* pMainLogicalSystem)
    {
        m_pMainLogicalSystem = pMainLogicalSystem;
    }

    bool MainLogicalSystemIsValid() const
    {
        return m_MainLogicalSystemIsValid;
    }

    void SetMainLogicalSystemValid(bool value = true)
    {
        m_MainLogicalSystemIsValid = value;
    }

    // Logical system retreival methods
    CString            RetreiveLogicalSystemGUID(const CString Name, bool& Error) const;
    CString            RetreiveLogicalSystemName(const CString GUID, bool& Error) const;
    CString            RetreiveLogicalSystemDescription(const CString GUID, bool& Error) const;

    virtual void    ReassignSystem(PSS_Log* pLog = NULL)
    {}

    //************************************************************************************************
    // JMR-MODIF - Le 26 janvier 2006 - Ajout des fonctions concernant les prestations.
    static ZBLogicalPrestationsEntity* GetMainLogicalPrestations()
    {
        return m_pMainLogicalPrestations;
    }

    static void AssignMainLogicalPrestations(ZBLogicalPrestationsEntity* pMainLogicalPrestations)
    {
        m_pMainLogicalPrestations = pMainLogicalPrestations;
    }

    bool MainLogicalPrestationsIsValid() const
    {
        return m_MainLogicalPrestationsIsValid;
    }

    void SetMainLogicalPrestationsValid(bool value = true)
    {
        m_MainLogicalPrestationsIsValid = value;
    }

    // Unit retreival methods
    //CString RetreivePrestationsGUID            ( const CString Name, bool& Error ) const;
    CString RetreivePrestationName(const CString GUID, bool& Error) const;
    //CString RetreivePrestationsDescription    ( const CString GUID, bool& Error ) const;

    virtual void ReassignPrestations(PSS_Log* pLog = NULL)
    {}
    //************************************************************************************************

    //************************************************************************************************
    // JMR-MODIF - Le 26 janvier 2006 - Ajout des fonctions concernant les règles.
    static ZBLogicalRulesEntity* GetMainLogicalRules()
    {
        return m_pMainLogicalRules;
    }

    static void AssignMainLogicalRules(ZBLogicalRulesEntity* pMainLogicalRules)
    {
        m_pMainLogicalRules = pMainLogicalRules;
    }

    bool MainLogicalRulesIsValid() const
    {
        return m_MainLogicalRulesIsValid;
    }

    void SetMainLogicalRulesValid(bool value = true)
    {
        m_MainLogicalRulesIsValid = value;
    }

    // Unit retreival methods
    //CString RetreiveRulesGUID            ( const CString Name, bool& Error ) const;
    CString RetreiveRuleName(const CString GUID, bool& Error) const;
    //CString RetreiveRulesDescription    ( const CString GUID, bool& Error ) const;

    virtual void ReassignRules(PSS_Log* pLog = NULL)
    {}
    //************************************************************************************************

    ///////////////////////////////////////////////////////
    // Page management methods
    bool MainPageSetExist()
    {
        return (GetMainPageSet() != NULL) ? true : false;
    }

    bool HasPageSet() const
    {
        return (m_pPageSet != NULL) ? true : false;
    }

    ZBProcessGraphPageSet*    GetMainPageSet();
    ZBProcessGraphPageSet*    GetPageSet()
    {
        return m_pPageSet;
    }

    ZBProcessGraphPageSet*    AllocateMainPageSet();
    ZBProcessGraphPageSet*    AllocatePageSet();

    ZDProcessGraphPage*        GetRootMainModelPage();
    void                    SetRootMainModelPage(ZDProcessGraphPage* pPage);

    ZDProcessGraphPage*        GetMainModelPage();
    void                    SetMainModelPage(ZDProcessGraphPage* pPage);

    ZDProcessGraphPage*        FindModelPage(const CString ModelName, bool InSubModel = false);
    ZDProcessGraphPage*        FindModelPage(ZDProcessGraphModelMdl* pModel, bool InSubModel = false);

    ZDProcessGraphPage*        FindPage(const CString PageName);
    bool                    PageExist(const CString PageName);

    ZDProcessGraphPage*        CreateNewPage(ZDProcessGraphModelMdl*    pModel,
                                             CString                    PageName = _T(""),
                                             ZDProcessGraphModelMdl*    pInModel = NULL);

    CString                    GetValidNextPageName();
    CStringArray*            GetExistingPageNameArray();
    bool                    DeletePage(const CString PageName, bool DeleteModel = false);
    virtual void            NotifyDeletePage(ZDProcessGraphPage* pPage)
    {}

    ZDProcessGraphModelMdl*    GetOwnerPageModel(ZDProcessGraphPage* pLookForPage);

    void                    PropagateNewSymbolAttributes(ZBPropertyAttributes* pAttributes, int ObjectID);
    void                    RefreshSymbolAttributes(bool Redraw = false);

    ///////////////////////////////////////////////////////
    // ZIProperties methods

    // Return true if the object has properties
    virtual bool HasProperties() const
    {
        return true;
    }

    // Call to retreive properties for the object
    virtual bool FillProperties(ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false);

    // Call to save new changes to object's properties
    virtual bool SaveProperties(ZBPropertySet& PropSet);

    // Called to retreive a property for the object
    virtual bool FillProperty(ZBProperty& Property);

    // Called to save a property for the object
    virtual bool SaveProperty(ZBProperty& Property);

    // Called to check the property value
    virtual bool CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties);

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh);

    // Called to process the a menu command for the property value
    virtual bool ProcessMenuCommand(int            MenuCommand,
                                    ZBProperty&    Property,
                                    CString&        value,
                                    ZBPropertySet&    Properties,
                                    bool&            Refresh)
    {
        // Do nothing
        return false;
    }

    // Called before the property changed
    virtual bool OnPrePropertyChanged(CString NewValue, ZBProperty& Property, ZBPropertySet& Properties)
    {
        // Do nothing
        return true;
    }

    // Called after the property changed
    virtual bool OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
    {
        // No change
        return false;
    }

    // Called when an internal drag&drop of property occured
    virtual bool OnDropInternalPropertyItem(ZBProperty& SrcProperty,
                                            ZBProperty& DstProperty,
                                            bool Top2Down,
                                            ZBPropertySet& Properties)
    {
        // Do nothing
        return true;
    }

    // Call to create the properties
    virtual bool CreateSymbolProperties();

    // Call to know if properties can be edited
    virtual bool IsPropertiesReadOnly() const
    {
        return false;
    }

    ///////////////////////////////////////////////////////
    // ZIObjectPath    methods
    virtual void                    ClearPath();
    virtual void                    CalculateAbsolutePath();

    ///////////////////////////////////////////////////////
    // Unique Symbol Name methods
    bool                            SymbolNameAlreadyAllocated(const CString SymbolName);

    ///////////////////////////////////////////////////////
    // Unique Reference number methods
    bool                            ReferenceNumberAlreadyAllocated(int ReferenceNumber);
    bool                            ReferenceNumberAlreadyAllocated(const CString ReferenceNumberStr);

    CString                            GetNextAvailableReferenceNumberStr();

    // JMR-MODIF - Le 22 mai 2006 - Ajout du paramètre m_RootModel.
    int                                GetNextAvailableReferenceNumber(ZDProcessGraphModelMdl* m_RootModel = NULL);

    CStringArray*                    GetExistingReferenceNumberArray();

    //////////////////////////////////////////////////////////////////////
    // ZIBasicSymbolAcceptVisitor methods

    /* AcceptVisitor method let the object be visited
       by concreted derived ZIBasicSymbolVisitor classes */
    virtual bool                    AcceptVisitor(ZIBasicSymbolVisitor& Visitor);

    ///////////////////////////////////////////////////////
    // ZINavigableModel methods

    // Methods to obtain start symbols
    virtual size_t GetStartSymbols(CODNodeArray& Nodes, bool Deep = false)
    {
        // We don't know what start symbols exists.
        // The class implementing the method knows it.
        return 0;
    }

    //////////////////////////////////////////////////////////////////////
    // Model generation methods
    // JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
    virtual bool CheckModelWorkflow(PSS_Log* pLog, BOOL ModelIsClean)
    {
        return false;
    }

    virtual bool GenerateModelWorkflow(PSS_Log* pLog, ZDProcessGraphModelDoc* pDoc)
    {
        return false;
    }

    virtual void                    SetDefaultWkfProperty(bool RedefineOnExisting = false);
    virtual void                    DeleteAllActivitiesLinkedToWorkflow();

    virtual void                    RecalculateParentPtr();
    virtual void                    RecalculateChildModelPtr();
    virtual void                    RecalculateReference();
    virtual void                    RecalculateSymbolReferences()
    {
        // Do nothing
    }

    virtual ZDProcessGraphModelMdl* GetSymbolModel(ZBSymbol* pSymbolToFind);
    virtual ZDProcessGraphModelMdl* GetLinkSymbolModel(ZBLinkSymbol* pSymbolToFind);

    virtual ZDProcessGraphModelMdl* GetRoot();
    virtual ZDProcessGraphModelMdl* GetParent()
    {
        return m_pParent;
    }

    virtual void                    SetParent(ZDProcessGraphModelMdl* value);

    // Call-back on symbols
    virtual void                    OnSymbolNameChanged(CODComponent& Comp, const CString OldName);
    virtual void                    OnPageNameChanged(ZDProcessGraphPage* pPage, const CString OldName);
    virtual void                    OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString OldName);

    // Called to create the adequate model
    virtual ZDProcessGraphModelMdl* CreateEmptyModel(const CString                Name = _T(""),
                                                     ZDProcessGraphModelMdl*    pParent = NULL)
    {
        return new ZDProcessGraphModelMdl(Name, pParent);
    }

    // Drawing functions
    void                            SetBackgroundComponent(CODComponent& BkgndComponent,
                                                           bool            ToAll = true,
                                                           bool            StretchToModel = false);

    void                            ClearBackgroundComponent(bool ToAll = true);

    void                            ReDrawComponent(CODComponent& Comp);
    void                            ReDrawComponentSet(CODComponentSet& Set);

    // Selection functions
    void                            SelectAllComponents();
    void                            UnselectAllComponents();
    void                            SelectComponent(CODComponent& Comp);
    void                            SelectComponentSet(CODComponentSet& Set);
    void                            UnselectComponent(CODComponent& Comp);
    void                            UnselectComponentSet(CODComponentSet& Set);
    bool                            IsComponentSelected(CODComponent& Comp);

    // Delete a symbol or symbol sets from the model
    void                            DeleteComponents(CODComponentSet* pCompSet);
    void                            DeleteComponent(CODComponent* pComp);

    // Find methods
    bool                            SymbolExistInModel(CODComponent* pCompToFind, bool InSubModel = true);

    virtual CODComponentSet*        FindSymbol(CODComponent* pCompToFind, bool InSubModel = true);
    virtual CODComponentSet*        FindSymbol(CODModel*                pModel,
                                               bool                    InSubModel = true,
                                               bool                    OnlyLocal = false);

    virtual CODComponentSet*        FindSymbol(const CString            Name,
                                               const CString            Path = _T(""),
                                               bool                    InSubModel = true,
                                               bool                    CaseSensitive = false,
                                               bool                    OnlyLocal = false);

    virtual CODComponentSet*        FindSymbolFromPath(const CString            Path,
                                                       bool                    InSubModel = true,
                                                       bool                    CaseSensitive = false,
                                                       bool                    OnlyLocal = false);

    virtual CODComponentSet*        FindSymbolByRefNumber(int RefNumber, bool InSubModel = true);

    virtual CODComponentSet*        FindSymbolPartialName(const CString            Name,
                                                          bool                    InSubModel = true,
                                                          bool                    CaseSensitive = false,
                                                          bool                    OnlyLocal = false);

    virtual size_t                    Find(const CString            What,
                                           PSS_Log*                pLog,
                                           ZBPropertyAttributes*    pPropAttributes = NULL,
                                           bool                    InSubModel = true,
                                           bool                    CaseSensitive = false,
                                           bool                    PartialSearch = false);

    ZDProcessGraphModelMdl*            FindModelFromPath(const CString Path, bool CaseSensitive = false);
    ZDProcessGraphModelMdl*            FindModel(const CString                Name,
                                                 bool                        CaseSensitive = false,
                                                 ZDProcessGraphModelMdl*    m_RootModel = NULL);

    bool                            SubModelExist(CODModel* pModel);
    bool                            SubModelExist(const CString ModelName, bool CaseSensitive = false);

    void                            DrawMetaFile(CDC* pDC, CRect& Rect);
    void                            SetMetaFileHandle(HENHMETAFILE hMetaFile);

    HENHMETAFILE                     GetMetaFileHandle()
    {
        return m_hMetaFile;
    }

    //    Recalculates all links for the process
    virtual BOOL                    RecalculateAllLinks();

    void                            SetModelName(const CString value);
    const CString                    GetModelName();

    const CString                    GetDescription();
    void                            SetDescription(const CString& value);

    // Contains the connected user.
    const CString                    GetConnectedUser() const;
    void                            SetConnectedUser(CString value);

    //////////////////////////////////////////////////////////////////////
    // JMR-MODIF - Le 5 août 2005 - Fonctions concernant le tramage.

    CString                            GetBkGndFilename();

    void                            SetBkGndFilename(CString Filename);
    void                            ResetBkGndMustBeRestored();
    void                            SetIsLogo(BOOL IsLogo);

    BOOL                            IsBkGndMustBeRestored();
    BOOL                            IsLogo();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDProcessGraphModelMdl)
public:
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:

#ifdef _DEBUG
    virtual void            AssertValid() const;
    virtual void            Dump(CDumpContext& dc) const;
#endif // _DEBUG

private:

    // Private page management methods
    void                    _GetExistingPageNameArray(CStringArray& PageArray);

    // Private Unique Reference number methods
    // JMR-MODIF - Le 2 juillet 2006 - Remplacement de la fonction interne _GetNextAvailableReferenceNumber.
//    bool                    _GetNextAvailableReferenceNumber( int& ReferenceNumber );
    int                        _GetNextAvailableReferenceNumber(ZDProcessGraphModelMdl* m_RootModel);
    void                    _GetExistingReferenceNumberArray(CStringArray& ReferenceNumberArray);

protected:

    // Page management methods
    bool                    DeleteAllPages();
    bool                    DeleteAllPageInSet();
    void                    SerializePageSet(CArchive& ar);

    // Connection methods
    size_t                    GetFollowingSymbols(ZBSymbol* pComp, CODNodeArray& Nodes);
    size_t                    GetEnteringSymbols(ZBSymbol* pComp, CODNodeArray& Nodes);
    size_t                    GetEdgesLeaving(ZBSymbol* pComp, CODEdgeArray& Edges);
    size_t                    GetEdgesEntering(ZBSymbol* pComp, CODEdgeArray& Edges);

    // Generic connection methods
    size_t                    GetFollowingSymbolsISA(ZBSymbol*                pComp,
                                                     CODNodeArray&            Nodes,
                                                     const CRuntimeClass*    pClass);

    size_t                    GetEnteringSymbolsISA(ZBSymbol*                pComp,
                                                    CODNodeArray&            Nodes,
                                                    const CRuntimeClass*    pClass);

    size_t                    GetEdgesLeavingISA(ZBSymbol*                pComp,
                                                 CODEdgeArray&            Edges,
                                                 const CRuntimeClass*    pClass);

    size_t                    GetEdgesEnteringISA(ZBSymbol*                pComp,
                                                  CODEdgeArray&            Edges,
                                                  const CRuntimeClass*    pClass);

    // Filtering methods
    size_t                    KeepOnlySymbolsISA(CODNodeArray& Nodes, const CRuntimeClass* pClass);
    size_t                    KeepOnlyLinksISA(CODEdgeArray& Edges, const CRuntimeClass* pClass);

    // Find methods
    size_t                    FindActivity(ZBSymbol* pCompToFind, CODNodeArray& Nodes);
    size_t                    FindLink(CODLinkComponent* pCompToFind, CODEdgeArray& Edges);

    // Retrieval methods
    size_t                    GetSymbolsISA(CODNodeArray&            Nodes,
                                            const CRuntimeClass*    pClass,
                                            bool                    Deep = false);

    // Find methods
    CODComponentSet*        _FindSymbol(CODComponent* pCompToFind, bool InSubModel = true);

    CODComponentSet*        _FindSymbol(CODModel*                pModel,
                                        bool                    InSubModel = true,
                                        bool                    OnlyLocal = false);

    CODComponentSet*        _FindSymbol(const CString            Name,
                                        const CString            Path = _T(""),
                                        bool                    InSubModel = true,
                                        bool                    CaseSensitive = false,
                                        bool                    OnlyLocal = false);

    CODComponentSet*        _FindSymbolFromPath(const CString            Path,
                                                bool                    InSubModel = true,
                                                bool                    CaseSensitive = false,
                                                bool                    OnlyLocal = false);

    CODComponentSet*        _FindSymbolByRefNumber(int RefNumber, bool InSubModel = true);

    CODComponentSet*        _FindSymbolPartialName(const CString            Name,
                                                   bool                    InSubModel = true,
                                                   bool                    CaseSensitive = false,
                                                   bool                    OnlyLocal = false);

    void                    _Find(const CString            What,
                                  PSS_Log*                pLog,
                                  ZBPropertyAttributes*    pPropAttributes = NULL,
                                  bool                    InSubModel = true,
                                  bool                    CaseSensitive = false,
                                  bool                    PartialSearch = false);

    ZDProcessGraphModelMdl* _FindModelFromPath(const CString Path, bool CaseSensitive = false);
    // JMR-MODIF - Le 28 mars 2006 - Suppression de la fonction _FindModel.
//    ZDProcessGraphModelMdl*    _FindModel                        ( const CString Name, bool CaseSensitive = false );

    // Drawing methods
    void                    SetBackgroundComponentToModel(CODComponent&    BkgndComponent,
                                                          bool            StretchToModel = false);

    void                    _SetBackgroundComponentToAll(CODComponent&    BkgndComponent,
                                                         bool            StretchToModel = false);

    void                    ClearBackgroundComponentToModel();
    void                    _ClearBackgroundComponentToAll();

protected:

    class ZBComponentRef
    {
    public:

        ZBComponentRef(ZBSymbol* pSymbol = NULL)
        {
            m_pSymbol = pSymbol;
            m_Ref = 1;
        }

        void AddRef()
        {
            ++m_Ref;
        }

        void RemoveRef()
        {
            --m_Ref;
        }

        size_t GetRef() const
        {
            return m_Ref;
        }

        ZBSymbol*    m_pSymbol;
        size_t        m_Ref;
    };

    void RemoveAllSymbolInParsedArray();

    // Find a symbol in the array,
    // if found, return its reference
    ZBComponentRef* FindSymbolInParsedArray(ZBSymbol* pComp);

    // Add a symbol in the array and return its reference counter
    size_t AddSymbolInParsedArray(ZBSymbol* pComp);

protected:

    EModelNotation                                    m_Notation;
    CString                                            m_Name;

    // Contains all the pages
    ZBProcessGraphPageSet*                            m_pPageSet;

private:

    ZDProcessGraphModelMdl*                            m_pParent;
    CString                                            m_ParentName;
    HENHMETAFILE                                     m_hMetaFile;

    // Variable that needs to be checked
    CString                                            m_ConnectedUser;
    CStringArray                                    m_AuthorizedUser;

    // Variable for the find
    static size_t                                    m_FindCounter;

    // JMR-MODIF - Le 5 août 2005 - Ajout des variables de tramage.
    CString                                            m_BkGndFilename;
    BOOL                                            bBkGndFlag;
    BOOL                                            bIsLogo;

    // JMR-MODIF - Le 2 juillet 2006 - Ajout d'une nouvelle variable pour la génération des no. de réf.
    int                                                m_NextAvailableRefNbr;

protected:

    CODController*                                    m_pCtlr;

    static    CODComponentSet                            m_FindSet;

    static    CArray<ZBComponentRef*, ZBComponentRef*>    m_SymbolParsed;
    static    int                                        m_RecursionCounter;
    static    bool                                    m_IsInRecursion;

    static    ZBUserGroupEntity*                        m_pMainUserGroup;
    static    ZBLogicalSystemEntity*                    m_pMainLogicalSystem;
    // JMR-MODIF - Le 26 janvier 2006 - Ajout de la variable m_pMainLogicalPrestations.
    static    ZBLogicalPrestationsEntity*                m_pMainLogicalPrestations;
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de la variable m_pMainLogicalRules.
    static    ZBLogicalRulesEntity*                    m_pMainLogicalRules;

    // To know if the user group and the logical system is inline with the model
    bool                                            m_MainUserGroupIsValid;
    bool                                            m_MainLogicalSystemIsValid;
    // JMR-MODIF - Le 26 janvier 2006 - Ajout de la variable m_MainLogicalPrestationsIsValid.
    bool                                            m_MainLogicalPrestationsIsValid;
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de la variable m_MainLogicalRulesIsValid.
    bool                                            m_MainLogicalRulesIsValid;
    bool                                            m_IsInCutOperation;
};

inline void ZDProcessGraphModelMdl::SetMetaFileHandle(HENHMETAFILE hMetaFile)
{
    if (m_hMetaFile)
    {
        ::DeleteEnhMetaFile(m_hMetaFile);
    }

    m_hMetaFile = hMetaFile;
}

inline const CString ZDProcessGraphModelMdl::GetConnectedUser() const
{
    return m_ConnectedUser;
}

inline void ZDProcessGraphModelMdl::SetConnectedUser(CString value)
{
    m_ConnectedUser = value;
}

#endif
