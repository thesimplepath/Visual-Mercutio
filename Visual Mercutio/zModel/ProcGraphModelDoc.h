// ProcGraphModelDoc.h : interface of the ZDProcessGraphModelDoc class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTIVDOC_H__037E37C0_6ACE_4FB6_B930_41786C8809CE__INCLUDED_)
#define AFX_OBJECTIVDOC_H__037E37C0_6ACE_4FB6_B930_41786C8809CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "Define.h"

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"

#include "ProcGraphModelMdl.h"
#include "ZBUnitManager.h"
#include "ZBModelSet.h"

// BaseDoc
#include "zBaseLib\BaseDoc.h"

#include "ZBPageUnits.h"

#include "ZBWorkflowDefinition.h"

#include "zLanguageDef.h"

#include "zBaseLib\ZVDocumentPageSetup.h"

// Forward declaration
class ZILog;
class ZIProcessGraphModelView;
class ZUUserManager;
class ZUMail;
class ZDTemplateManager;
class ZBDynamicPropertiesManager;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 septembre 2005 - Ajout des décorations unicode _T(), nettoyage du code inutile.(En commentaires)

class AFX_EXT_CLASS ZDProcessGraphModelDoc : public ZDBaseDocument,
                                             public ZISubject,
                                             public ZIObserver
{
public:

    DECLARE_SERIAL( ZDProcessGraphModelDoc )

    // Inherited feature
    typedef ZDBaseDocument inherited;

    // Can be created to be used with ReadFromFile method
    ZDProcessGraphModelDoc();
    virtual ~ZDProcessGraphModelDoc();

    virtual void PreCloseFrame( CFrameWnd* pFrame );

    virtual void Initialize( ZILog*                pOutputLog,
                             ZILog*                pAnalyzerLog,
                             ZILog*                pSearchLog,
                             ZILog*                pWorflowLog,
                             ZUUserManager*        pUserManager,
                             ZUMail*            pMail,
                             ZDTemplateManager*    pTemplateManager );

    // JMR-MODIF - Le 29 septembre 2005 - Ajout de la fonction IsClosing.
    BOOL IsClosing();

    virtual ZUUserManager* GetpUserManager() const
    {
        return m_pUserManager;
    }

    virtual ZUMail* GetpMail() const
    {
        return m_pMail;
    }

    virtual ZDTemplateManager* GetpTemplateManager() const
    {
        return m_pTemplateManager;
    }

    // Returns the guid of this file
    CString GetGUID() const
    {
        return m_GUID;
    }

    // User def guid management methods
    bool HasUserDefAssigned() const
    {
        return ( m_UserDefGUID.IsEmpty() ) ? false : true;
    }

    CString    GetUserDefGUID() const;
    void    AssignUserDefGUID( const CString value );
    bool    AssignCurrentUserDefGUID();
    void    ReassignUnit( ZILog* pLog = NULL );

    // System def guid management methods
    bool HasSystemDefAssigned() const
    {
        return ( m_SystemDefGUID.IsEmpty() ) ? false : true;
    }

    CString    GetSystemDefGUID() const;
    void    AssignSystemDefGUID( const CString value );
    bool    AssignCurrentSystemDefGUID();
    void    ReassignSystem( ZILog* pLog = NULL );

    // ********************************************************************************
    // JMR-MODIF - Le 26 janvier 2006 - Ajout de l'infrastructure pour les prestations.
    bool HasPrestationsDefsAssigned() const
    {
        return ( m_PrestationsDefGUID.IsEmpty() ) ? false : true;
    }

    CString    GetPrestationsDefGUID() const;
    void    AssignPrestationsDefGUID( const CString value );
    bool    AssignCurrentPrestationsDefGUID();
    void    ReassignPrestations( ZILog* pLog = NULL );
    // ********************************************************************************

    // ********************************************************************************
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de l'infrastructure pour les règles.
    bool HasRulesDefsAssigned() const
    {
        return ( m_RulesDefGUID.IsEmpty() ) ? false : true;
    }

    CString    GetRulesDefGUID() const;
    void    AssignRulesDefGUID( const CString value );
    bool    AssignCurrentRulesDefGUID();
    void    ReassignRules( ZILog* pLog = NULL );
    // ********************************************************************************

    // Page unit functions
    virtual ZBPageUnits& GetPageUnits()
    {
        return m_PageUnits;
    }

    virtual void            SetPageUnits( ZBPageUnits& value );
    virtual void            SetPageUnits( CODRuler& value );

    // Unit functions
    bool    InsertUnit( const CString Filename );
    bool    LoadAllUnits();
    bool    LoadUnit( const CString Filename, ZDProcessGraphModelMdl& Model );

    bool IsUnit()
    {
        return GetDocumentStamp().GetFileType() == E_FD_LibraryType;
    }

    bool HasUnit() const
    {
        return ( m_pUnitManager != NULL ) ? true : false;
    }

    // Notation functions
    EModelNotation GetNotation() const
    {
        return GetModelConst()->GetNotation();
    }

    void SetNotation(EModelNotation value)
    {
        GetModel()->SetNotation( value );
    }

    bool IsModelInABCNotation() const
    {
        return GetModelConst()->IsModelInABCNotation();
    }

    bool IsModelInUMLNotation() const
    {
        return GetModelConst()->IsModelInUMLNotation();
    }

    bool IsModelInBerylNotation() const
    {
        return GetModelConst()->IsModelInBerylNotation();
    }

    bool IsModelNotationUnknow() const
    {
        return GetModelConst()->IsModelNotationUnknow();
    }

    // JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
    bool CheckModelWorkflow( BOOL ModelIsClean );
    bool GenerateModelWorkflow();
    void DeleteWorkflowDefinition();

    bool BrowseInSameWindow() const
    {
        return m_BrowseInSameWindow;
    }

    void SetBrowseInSameWindow( bool value )
    {
        m_BrowseInSameWindow = value; 
    }

    CString        GetWorkflowFilename() const;
    void        ClearWorkflowFilename();
    void        SetWorkflowFilename( CString value );

    ZBDate*        GetWorkflowLastUpdateDate();
    void        SetWorkflowLastUpdateDate( ZBDate value );

    bool        GetCheckConsistency() const;
    void        SetCheckConsistency( bool value );

    bool        GetIntegrateCostSimulation() const;
    void        SetIntegrateCostSimulation( bool value );

    bool        GetUseWorkflow() const { return m_UseWorkflow; };
    void        SetUseWorkflow( bool value );

    int            GetHourPerDay() const;
    void        SetHourPerDay( int value );

    int            GetDayPerWeek() const;
    void        SetDayPerWeek( int value );

    int            GetDayPerMonth() const;
    void        SetDayPerMonth( int value );

    int            GetDayPerYear() const;
    void        SetDayPerYear( int value );

    CString        GetCurrencySymbol() const;
    void        SetCurrencySymbol( CString value );

    bool        GetSaveModelInWorkflow() const;
    void        SetSaveModelInWorkflow( bool value );

    bool        GetShowPageBorder() const;
    void        SetShowPageBorder( bool value );

    const ELanguage GetLanguage()
    {
        return GetModel()->GetLanguage();
    }

    void SetLanguage(const ELanguage value)
    {
        GetModel()->SetLanguage(value);
    }

    // ****************************************************************************
    // JMR-MODIF - Le 25 avril 2006 - Ajout des fonctions IsReadOnly et SetReadOnly

    BOOL IsReadOnly()
    {
        return b_IsReadOnly;
    }

    void SetReadOnly( BOOL Value )
    {
        b_IsReadOnly = Value;
    }
    // ****************************************************************************

    ZILog* GetModelOutputLog()
    {
        return m_pOutputLog;
    }

    ZILog* GetAnalyzerOutputLog()
    {
        return m_pAnalyzerLog;
    }

    ZILog* GetSearchOutputLog()
    {
        return m_pSearchLog;
    }

    ZILog* GetWorkflowOutputLog()
    {
        return m_pWorflowLog;
    }

    // Once the doucument is open, the OnPostOpenDocument method is called
    // from the framework
    virtual void OnPostOpenDocument();

    ///////////////////////////////////////////////////////
    // User group Get and Set methods
    ZBUserGroupEntity* GetMainUserGroup()
    {
        return GetModel()->GetMainUserGroup();
    }

    void AssignMainUserGroup( ZBUserGroupEntity* pMainUserGroup )
    {
        GetModel()->AssignMainUserGroup( pMainUserGroup );
    }

    ///////////////////////////////////////////////////////
    // Logical system Get and Set methods
    ZBLogicalSystemEntity* GetMainLogicalSystem()
    {
        return GetModel()->GetMainLogicalSystem();
    }

    void AssignMainLogicalSystem( ZBLogicalSystemEntity* pMainLogicalSystem )
    {
        GetModel()->AssignMainLogicalSystem( pMainLogicalSystem );
    }

    ///////////////////////////////////////////////////////
    // JMR-MODIF - Le 26 janvier 2006 - Ajout des fonctions Get and Set pour les prestations.
    ZBLogicalPrestationsEntity* GetMainLogicalPrestations()
    {
        return GetModel()->GetMainLogicalPrestations();
    }

    void AssignMainLogicalPrestations( ZBLogicalPrestationsEntity* pMainLogicalPrestations )
    {
        GetModel()->AssignMainLogicalPrestations( pMainLogicalPrestations );
    }

    ///////////////////////////////////////////////////////
    // JMR-MODIF - Le 19 novembre 2006 - Ajout des fonctions Get and Set pour les règles.
    ZBLogicalRulesEntity* GetMainLogicalRules()
    {
        return GetModel()->GetMainLogicalRules();
    }

    void AssignMainLogicalRules( ZBLogicalRulesEntity* pMainLogicalRules )
    {
        GetModel()->AssignMainLogicalRules( pMainLogicalRules );
    }

    // Implementation for ZIModelDocument interface

    // Gets a pointer to the model of the canvas.
    ZDProcessGraphModelMdl* GetModel();
    ZDProcessGraphModelMdl* GetModelConst() const;
    void SetNewModel( ZDProcessGraphModelMdl* pModel );

    virtual CDocTemplate* GetDocTemplate() const;
    virtual void SetModifiedFlag( BOOL bModified = TRUE );

    // Printer functions
    ZVDocumentPageSetup* GetPrinterPageSize();

    // View functions
    ZIProcessGraphModelView* GetFirstModelView();
    virtual CView* FindView( const CString Name );
    virtual CView* ActivateView( const CString Name );
    CView*    SwitchView( CView* pNewView, size_t Index = 0 );

    // Determines if the canvas has been modified.
    virtual BOOL IsModified();

    bool IsInModelCreation() const
    {
        return m_IsInModelCreation;
    }

    // Dynamic properties manager functions
    ZBDynamicPropertiesManager* GetDynamicPropertiesManager()
    {
        return m_DynamicPropertiesManager;
    }

    bool HasDynamicPropertiesManager() const
    {
        return m_DynamicPropertiesManager != NULL;
    }

    void AllocatePropertiesManager( bool DeleteFirst = false );

    /////////////////////////////////////////////////////////
    // Operations

    // Observer call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDProcessGraphModelDoc)
    public:
    virtual BOOL OnNewDocument();
    virtual void DeleteContents();
    virtual void OnCloseDocument();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual BOOL OnSaveDocument (const char* pszPathName);
    //}}AFX_VIRTUAL

    // JMR-MODIF - Le 9 juillet 2006 - Surcharge de la fonction DoFileSave.
    BOOL DoFileSave();

    // JMR-MODIF - Le 27 avril 2006 - Ajout de la fonction SetFileReadOnly.
    BOOL SetFileReadOnly( const char* pszPathName, BOOL Value );

    // Reader and Writer methods
    // These methods don't use the standard MVC framework
    bool ReadFromFile( const CString Filename );
    bool SaveToFile( const CString Filename );

    virtual void Serialize( CArchive& ar );

    ////////////////////////////////////////////////////////////
    // Implementation

#ifdef _DEBUG

    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;

#endif

// Generated message map functions
protected:

    //{{AFX_MSG(ZDProcessGraphModelDoc)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    bool CreateUnitManager();

protected:

    ZDProcessGraphModelMdl        m_EmptyModel;

    // The model for the canvas. The model holds all information about
    // the canvas, while the viewport actually displays it.
    ZDProcessGraphModelMdl*        m_pModel;

private:

    // JMR-MODIF - Le 29 septembre 2005 - Ajout de la variable IsDocumentClosing.
    BOOL                        IsDocumentClosing;

    // JMR-MODIF - Le 25 avril 2006 - Ajout de la variable IsReadOnly.
    BOOL                        b_IsReadOnly;

    CString                        m_GUID;
    CString                        m_UserDefGUID;
    CString                        m_SystemDefGUID;
    // JMR-MODIF - Le 26 janvier 2006 - Ajout de la variable m_PrestationsDefGUID.
    CString                        m_PrestationsDefGUID;
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de la variable m_RulesDefGUID.
    CString                        m_RulesDefGUID;

    ZBPageUnits                    m_PageUnits;
    ZUUserManager*                m_pUserManager;
    ZUMail*                        m_pMail;
    ZDTemplateManager*            m_pTemplateManager;
    ZBDynamicPropertiesManager*    m_DynamicPropertiesManager;

    bool                        m_IsInModelCreation;
    ZBUnitManager*                m_pUnitManager;
    ZBModelSet                    m_DocumentModelSet;
    ZBModelSet                    m_UnitModelSet;

    bool                        m_UseWorkflow;
    bool                        m_BrowseInSameWindow;
    bool                        m_IntegrateCostSimulation;
    bool                        m_CheckConsistency;

    // Number of hours per day for cost simulation
    int                            m_HourPerDay;

    // Number of days per week for cost simulation
    int                            m_DayPerWeek;

    // Number of days per month for cost simulation
    int                            m_DayPerMonth;

    // Number of days per year for cost simulation
    int                            m_DayPerYear;

    // Currency symbol to use for amounts
    CString                        m_CurrencySymbol;

    // The show page border flag
    bool                        m_ShowPageBorder;

    CSize                        m_PaperSize;
    short                        m_StandardSize;
    short                        m_Orientation;

    ZBWorkflowDefinition*        m_pWorkflowDefinition;

    ZILog*                        m_pOutputLog;
    ZILog*                        m_pAnalyzerLog;
    ZILog*                        m_pSearchLog;
    ZILog*                        m_pWorflowLog;
};

inline CString ZDProcessGraphModelDoc::GetUserDefGUID() const
{
    return m_UserDefGUID;
}

inline void ZDProcessGraphModelDoc::AssignUserDefGUID( const CString value )
{
    m_UserDefGUID = value;
}

inline CString ZDProcessGraphModelDoc::GetSystemDefGUID() const
{
    return m_SystemDefGUID;
}

inline void ZDProcessGraphModelDoc::AssignSystemDefGUID( const CString value )
{
    m_SystemDefGUID = value;
}

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction GetPrestationsDefGUID.
inline CString ZDProcessGraphModelDoc::GetPrestationsDefGUID() const
{
    return m_PrestationsDefGUID;
}

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction AssignPrestationsDefGUID.
inline void ZDProcessGraphModelDoc::AssignPrestationsDefGUID( const CString value )
{
    m_PrestationsDefGUID = value;
}

// JMR-MODIF - Le 19 novembre 2006 - Ajout de la fonction GetRulesDefGUID.
inline CString ZDProcessGraphModelDoc::GetRulesDefGUID() const
{
    return m_RulesDefGUID;
}

// JMR-MODIF - Le 19 novembre 2006 - Ajout de la fonction AssignRulesDefGUID.
inline void ZDProcessGraphModelDoc::AssignRulesDefGUID( const CString value )
{
    m_RulesDefGUID = value;
}

inline CString ZDProcessGraphModelDoc::GetWorkflowFilename() const
{
    return ( m_pWorkflowDefinition ) ? m_pWorkflowDefinition->GetWorkflowFilename() : _T( "" );
}

inline void ZDProcessGraphModelDoc::SetWorkflowFilename( CString value )
{
    if ( m_pWorkflowDefinition )
    {
        m_pWorkflowDefinition->SetWorkflowFilename( value );
    }
}

inline ZBDate* ZDProcessGraphModelDoc::GetWorkflowLastUpdateDate()
{
    return ( m_pWorkflowDefinition ) ? &m_pWorkflowDefinition->GetWorkflowLastUpdateDate() : NULL;
}

inline void ZDProcessGraphModelDoc::SetWorkflowLastUpdateDate( ZBDate value )
{
    if ( m_pWorkflowDefinition )
    {
        m_pWorkflowDefinition->SetWorkflowLastUpdateDate( value );
    }
}

inline bool ZDProcessGraphModelDoc::GetCheckConsistency() const
{
    return m_CheckConsistency;
}

inline void ZDProcessGraphModelDoc::SetCheckConsistency( bool value )
{
    m_CheckConsistency = value;
}

inline bool ZDProcessGraphModelDoc::GetSaveModelInWorkflow() const
{
    return ( m_pWorkflowDefinition ) ? m_pWorkflowDefinition->GetSaveModelInWorkflow() : false;
}

inline bool ZDProcessGraphModelDoc::GetIntegrateCostSimulation() const
{
    return m_IntegrateCostSimulation;
}

inline void ZDProcessGraphModelDoc::SetIntegrateCostSimulation( bool value )
{
    m_IntegrateCostSimulation = value;
}

inline int ZDProcessGraphModelDoc::GetHourPerDay() const
{
    return m_HourPerDay;
}

inline void ZDProcessGraphModelDoc::SetHourPerDay( int value )
{
    m_HourPerDay = value;
}

inline int ZDProcessGraphModelDoc::GetDayPerWeek() const
{
    return m_DayPerWeek;
}

inline void ZDProcessGraphModelDoc::SetDayPerWeek( int value )
{
    m_DayPerWeek = value;
}

inline int ZDProcessGraphModelDoc::GetDayPerMonth() const
{
    return m_DayPerMonth;
}

inline void ZDProcessGraphModelDoc::SetDayPerMonth( int value )
{
    m_DayPerMonth = value;
}

inline int ZDProcessGraphModelDoc::GetDayPerYear() const
{
    return m_DayPerYear;
}

inline void ZDProcessGraphModelDoc::SetDayPerYear( int value )
{
    m_DayPerYear = value;
}

inline bool ZDProcessGraphModelDoc::GetShowPageBorder() const
{
    return m_ShowPageBorder;
}

inline void ZDProcessGraphModelDoc::SetShowPageBorder( bool value )
{
    m_ShowPageBorder = value;
}

inline CString ZDProcessGraphModelDoc::GetCurrencySymbol() const
{
    return m_CurrencySymbol;
}

inline void ZDProcessGraphModelDoc::SetCurrencySymbol( CString value )
{
    m_CurrencySymbol = value;
}

inline void ZDProcessGraphModelDoc::SetSaveModelInWorkflow( bool value )
{
    if ( m_pWorkflowDefinition )
    {
        m_pWorkflowDefinition->SetSaveModelInWorkflow( value );
    }
}

inline void ZDProcessGraphModelDoc::ClearWorkflowFilename()
{
    if ( m_pWorkflowDefinition )
    {
        m_pWorkflowDefinition->ClearWorkflowFilename();
    }
}

inline CDocTemplate* ZDProcessGraphModelDoc::GetDocTemplate() const
{
    return ZDBaseDocument::GetDocTemplate();
}

inline void ZDProcessGraphModelDoc::SetModifiedFlag( BOOL bModified /*= TRUE*/ )
{
    ZDBaseDocument::SetModifiedFlag( bModified );
}

// Gets a pointer to the model of the canvas.
inline ZDProcessGraphModelMdl* ZDProcessGraphModelDoc::GetModel()
{
    return ( m_pModel ) ? m_pModel : &m_EmptyModel;
}

inline ZDProcessGraphModelMdl* ZDProcessGraphModelDoc::GetModelConst() const
{
    return const_cast<ZDProcessGraphModelMdl*>( ( m_pModel ) ? m_pModel : &m_EmptyModel );
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTIVDOC_H__037E37C0_6ACE_4FB6_B930_41786C8809CE__INCLUDED_)
