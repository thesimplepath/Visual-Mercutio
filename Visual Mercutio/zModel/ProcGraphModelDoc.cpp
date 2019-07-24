// ProcGraphModelDoc.cpp : implementation of the ZDProcessGraphModelDoc class

#include "stdafx.h"
#include "ProcGraphModelDoc.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zBaseLib\ZBDocumentObserverMsg.h"
#include "zBaseLib\File.h"
#include "zBaseLib\ZILog.h"
#include "zBaseLib\ZUFloatingToolbar.h"
#include "zBaseLib\ZUGUID.h"
#include "zBaseLib\MsgBox.h"
#include "ProcGraphModelView.h"
#include "ProcGraphChildFrm.h"
#include "ProcGraphModelCtlr.h"
#include "ZBDocObserverMsg.h"
#include "ZBUnitObserverMsg.h"
#include "ZBLogicalSystemEntity.h"
#include "ZBGenericSymbolErrorLine.h"

#include "zModelRes.h"

#include <IO.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 29 septembre 2005 - Ajout des décorations unicode _T(), nettoyage du code inutile.(En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelDoc

IMPLEMENT_SERIAL(ZDProcessGraphModelDoc, ZDBaseDocument, g_DefVersion)

BEGIN_MESSAGE_MAP( ZDProcessGraphModelDoc, ZDBaseDocument )
    //{{AFX_MSG_MAP(ZDProcessGraphModelDoc)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelDoc construction/destruction

ZDProcessGraphModelDoc::ZDProcessGraphModelDoc()
    : m_pModel                        ( NULL ),
      m_IsInModelCreation            ( false ),
      m_BrowseInSameWindow            ( false ),
      m_pUnitManager                ( NULL ),
      m_DynamicPropertiesManager    ( NULL ),
      m_UseWorkflow                    ( false ),
      m_pUserManager                ( NULL ),
      m_pMail                        ( NULL ),
      m_pTemplateManager            ( NULL ),
      m_IntegrateCostSimulation        ( false ),
      m_CheckConsistency            ( false ),
      m_pWorkflowDefinition            ( NULL ),
      m_pOutputLog                    ( NULL ),
      m_pAnalyzerLog                ( NULL ),
      m_pSearchLog                    ( NULL ),
      m_pWorflowLog                    ( NULL ),
      m_PaperSize                    ( 0, 0 ),
      m_StandardSize                ( -1 ),
      m_Orientation                    ( -1 ),
      m_ShowPageBorder                ( false )
{
    IsDocumentClosing = FALSE;

    // JMR-MODIF - Le 25 avril 2006 - Initialisation de la variable b_IsReadOnly.
    b_IsReadOnly = FALSE;

    m_GUID = ZUGUID::CreateNewGUID();
}

ZDProcessGraphModelDoc::~ZDProcessGraphModelDoc()
{
    DeleteWorkflowDefinition();

    // Delete the dynamic properties manager
    if ( m_DynamicPropertiesManager )
    {
        delete m_DynamicPropertiesManager;
        m_DynamicPropertiesManager = NULL;
    }

    // Delete the model
    if ( m_pModel )
    {
        // JMR-MODIF - Le 29 septembre 2005 - Nettoyage des memory leaks, nettoyage du modèle et de ses références.
        m_pModel->GetRoot()->DeleteModelSet();

        delete m_pModel;
        m_pModel = NULL;
    }
}

void ZDProcessGraphModelDoc::Initialize( ZILog*                pOutputLog,
                                         ZILog*                pAnalyzerLog,
                                         ZILog*                pSearchLog,
                                         ZILog*                pWorflowLog,
                                         ZUUserManager*        pUserManager,
                                         ZUMail*            pMail,
                                         ZDTemplateManager*    pTemplateManager )
{
    m_pOutputLog        = pOutputLog;
    m_pAnalyzerLog        = pAnalyzerLog;
    m_pSearchLog        = pSearchLog;
    m_pWorflowLog        = pWorflowLog;
    m_pUserManager        = pUserManager;
    m_pMail                = pMail;
    m_pTemplateManager    = pTemplateManager;
}

// Cette fonction permet de configurer le nouveau document pour le modèle.
void ZDProcessGraphModelDoc::SetNewModel( ZDProcessGraphModelMdl* pModel )
{
    if ( m_pModel )
    {
        delete m_pModel;
    }

    m_pModel = NULL;

    // Assign new created model
    m_pModel = pModel;

    // If a new model is defined, create the first page
    if ( m_pModel && !m_pModel->MainPageSetExist() )
    {
        m_pModel->CreateNewPage( m_pModel );
    }

    // Now create the new associated viewport
    ZIProcessGraphModelView* pView = GetFirstModelView();

    if ( pView && m_pModel )
    {
        // Create the new associated model controller
        // and assigns it to the viewport
        pView->GetViewport()->AssignNewController( m_pModel->CreateController(pView->GetViewport() ), m_pModel );

        // Sets the new model
        pView->SetModel( m_pModel );

        // Initialize the viewport
        pView->GetViewport()->OnInitialUpdateVp();

        // Switch the context
        ZUFloatingToolbar::SwitchContext( m_pModel->GetNotation() );

        // *******************************************************************************************************
        // JMR-MODIF - Le 12 juillet 2005 - La prise en charge du format de page rend cette modification obsolète.
        // RS-MODIF 14.12.04 set page size to A4 (210x296)
//        CSize test;
//        test.cx = 793;
//        test.cy = 1118;
        //GetCanvasModel()->SetSize(test);
//        pView->GetViewport()->GetCanvasModel()->SetSize(test);
        // *******************************************************************************************************

        // Build the message
        ZBDocObserverMsg DocMsg( ZBDocObserverMsg::OpenDocument, this );
        AfxGetMainWnd()->SendMessageToDescendants( UM_INITIALIZEDOCUMENTMODEL, 0, (LPARAM)&DocMsg );
    }
}

// JMR-MODIF - Le 14 juillet 2005 - Supprimé ancienne implémentation de cette fonction, car remplaçée
// par une structure plus souple.
/*bool ZDProcessGraphModelDoc::GetPrinterPageSize(CSize&    PaperSize,
                                                short&    StandardSize,
                                                short&    Orientation,
                                                bool    Retreive *//*= false*//*)
{
    // If the page size needs to be retreived
    if (Retreive == true || m_StandardSize == -1 || m_Orientation == -1)
    {
        ZIProcessGraphModelView* pView = GetFirstModelView();

        // If no view or no default printer
        // set the standard page as A4 and Portrait
        if (!pView || !pView->GetPrinterPageSize(m_PaperSize, m_StandardSize, m_Orientation))
        {
            m_PaperSize.cx    = 203;
            m_PaperSize.cy    = 271;

            m_StandardSize    = DMPAPER_A4;
            m_Orientation    = DMORIENT_PORTRAIT;
        }
    }

    PaperSize        = m_PaperSize;
    StandardSize    = m_StandardSize;
    Orientation        = m_Orientation;

    return true;
}*/

// JMR-MODIF - Le 14 juillet 2005 - Nouvelle implémentation de la fonction.
// Cette fonction permet d'obtenir les paramètres de la page du document.
ZVDocumentPageSetup* ZDProcessGraphModelDoc::GetPrinterPageSize()
{
    ZIProcessGraphModelView* pView = GetFirstModelView();

    if ( pView != NULL )
    {
        // La seule condition où m_StandardSize et m_Orientation ne valent pas -1,
        // c'est à la suite de la sérialisation, si l'on a ouvert un document existant.
        // Aussi, il faut mettre à jour la structure des pages.
        if ( m_StandardSize != -1 && m_Orientation != -1 )
        {
            pView->SetPrinterPageSize( m_PaperSize, m_StandardSize, m_Orientation );
        }

        return pView->GetPrinterPageSize();
    }
    else return NULL;
}

void ZDProcessGraphModelDoc::SetPageUnits( ZBPageUnits& value )
{
    m_PageUnits = value;
}

void ZDProcessGraphModelDoc::SetPageUnits( CODRuler& value )
{
    m_PageUnits = value;
}

void ZDProcessGraphModelDoc::DeleteWorkflowDefinition()
{
    if ( m_pWorkflowDefinition )
    {
        delete m_pWorkflowDefinition;
    }

    m_pWorkflowDefinition = NULL;
}

void ZDProcessGraphModelDoc::SetUseWorkflow( bool value )
{ 
    if ( value )
    {
        if ( !m_pWorkflowDefinition )
        {
            m_pWorkflowDefinition = new ZBWorkflowDefinition;
        }
    }
    else
    {
        // If want to clear the use of workflow,
        // delete the workflow definition object
        DeleteWorkflowDefinition();
    }

    m_UseWorkflow = value;
}

// JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
bool ZDProcessGraphModelDoc::CheckModelWorkflow( BOOL ModelIsClean )
{
    return GetModel()->CheckModelWorkflow( m_pOutputLog, ModelIsClean );
}

bool ZDProcessGraphModelDoc::GenerateModelWorkflow()
{
    bool Result = GetModel()->GenerateModelWorkflow( m_pOutputLog, this );

    return Result;
}

CView* ZDProcessGraphModelDoc::FindView( const CString Name )
{
    // Run throug all views
    POSITION pos = GetFirstViewPosition();
    CView* pView = GetNextView( pos );

    while ( pView )
    {
        if ( ISA( pView, ZIProcessGraphModelView ) )
        {
            if ( ( (ZIProcessGraphModelView*)pView )->GetViewName() == Name )
            {
                return pView;
            }
        }

        pView = GetNextView( pos );
    }

    return NULL;
}

CView* ZDProcessGraphModelDoc::ActivateView( const CString Name )
{
    CView* pView = FindView( Name );

    if ( pView )
    {
        CWnd* pWnd = pView->GetParent();

        if ( pWnd && ISA( pWnd, ZIProcessGraphChildFrame ) )
        {
            if ( AfxGetMainWnd() && ISA( AfxGetMainWnd(), CMDIFrameWnd ) )
            {
                ( (CMDIFrameWnd*)AfxGetMainWnd() )->MDIActivate( pWnd );

                return pView;
            }
        }
    }

    return NULL;
}

ZIProcessGraphModelView* ZDProcessGraphModelDoc::GetFirstModelView()
{
    POSITION pos = GetFirstViewPosition();
    CView* pView = GetNextView( pos );

    while ( pView )
    {
        if ( ISA( pView, ZIProcessGraphModelView ) )
        {
            return (ZIProcessGraphModelView*)pView;
        }

        pView = GetNextView( pos );
    }

    return NULL;
}

CView*    ZDProcessGraphModelDoc::SwitchView( CView* pNewView, size_t Index /*= 0*/ )
{
    CView* pActiveView = ( (CFrameWnd*)AfxGetMainWnd() )->GetActiveView();

    // Get the view ID
    UINT temp = ::GetWindowLong( pActiveView->m_hWnd, GWL_ID );

    ::SetWindowLong( pActiveView->m_hWnd, GWL_ID, ::GetWindowLong( pNewView->m_hWnd, GWL_ID ) );
    ::SetWindowLong( pNewView->m_hWnd, GWL_ID, temp );

    pActiveView->ShowWindow( SW_HIDE );

    pNewView->ShowWindow( SW_SHOW );

    ( (CFrameWnd*) AfxGetMainWnd() )->SetActiveView( pNewView );
    ( (CFrameWnd*) AfxGetMainWnd() )->RecalcLayout();

    pNewView->Invalidate();

    return pActiveView;
}

bool ZDProcessGraphModelDoc::CreateUnitManager()
{
    m_pUnitManager = new ZBUnitManager;

    if ( !m_pUnitManager )
    {
        return false;
    }

    if ( GetDocTemplate() && ISA( GetDocTemplate(), ZDProcessModelDocTmpl ) )
    {
        m_pUnitManager->Initialize( (ZDProcessModelDocTmpl*)GetDocTemplate() );
    }

    return true;
}

bool ZDProcessGraphModelDoc::InsertUnit( const CString Filename )
{
    ZFile File( Filename );

    if ( !File.Exist() )
    {
        return false;
    }

    if ( !m_pUnitManager )
    {
        CreateUnitManager();
    }

    ZBUnit* pUnit = m_pUnitManager->CreateNewUnit( _T( "" ), Filename );

    if ( !pUnit )
    {
        return false;
    }

    if ( !m_pUnitManager->LoadUnit( pUnit ) )
    {
        return false;
    }

    m_pUnitManager->FillModelSet( m_UnitModelSet );

    // Build the message
    ZBUnitObserverMsg UnitMsg( ZBUnitObserverMsg::OpenUnit, NULL, pUnit );
    AfxGetMainWnd()->SendMessageToDescendants( UM_ADDUNITMODEL, 0, (LPARAM)&UnitMsg );

    // Model has been modified
    SetModifiedFlag();

    return true;
}

bool ZDProcessGraphModelDoc::LoadAllUnits()
{
    if ( m_pUnitManager )
    {
        return m_pUnitManager->LoadAllUnits();
    }

    return false;
}

void ZDProcessGraphModelDoc::PreCloseFrame( CFrameWnd* pFrame )
{
    if ( pFrame->GetActiveView() && ISA( pFrame->GetActiveView(), ZIProcessGraphModelView ) )
    {
        ZIProcessGraphModelView* pView = (ZIProcessGraphModelView*)pFrame->GetActiveView();

        // Notify all document observers about the close
        ZBDocumentObserverMsg Msg( UM_CLOSEDOCUMENT, this );
        NotifyAllObservers( &Msg );

        // And all model observers
        if ( m_pModel )
        {
            m_pModel->NotifyAllObservers( &Msg );
        }

        if ( m_pModel )
        {
            // JMR-MODIF - Le 29 septembre 2005 - Nettoyage des memory leaks, nettoyage du modèle et de ses références.
            m_pModel->GetRoot()->DetachAllObserversInHierarchy( pView->GetViewport(), this );

            m_pModel->RemoveObserver( pView->GetViewport() );
            m_pModel->DetachObserver( this );
        }

        m_EmptyModel.RemoveObserver( pView->GetViewport() );
        m_EmptyModel.DetachObserver( this );
    }

    // Call the base class function
    ZDBaseDocument::PreCloseFrame( pFrame );
}

bool ZDProcessGraphModelDoc::AssignCurrentUserDefGUID()
{
    ZBUserGroupEntity* pUserGroup = GetMainUserGroup();

    // No user group, error
    if ( !pUserGroup )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_USERGROUP );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }
    }
    else
    {
        // Assigns the current GUID
        AssignUserDefGUID( pUserGroup->GetGUID() );

        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_USERGROUP_ASSIGNED );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }

        // Main user group is valid
        GetModel()->SetMainUserGroupValid();

        // Modified
        SetModifiedFlag();

        return true;
    }

    return false;
}

void ZDProcessGraphModelDoc::ReassignUnit( ZILog* pLog /*= NULL*/ )
{
    ASSERT( GetModel() );

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_UNITREASSIGN_START );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    // Main user group is not valid
    if ( GetModel()->MainUserGroupIsValid() )
    {
        GetModel()->ReassignUnit( pLog );
    }
    else
    {
        if ( pLog )
        {
            CString message;
            message.LoadString( IDS_AL_UNITCANNOTREASSIGN );
            ZBGenericSymbolErrorLine e( message );
            pLog->AddLine( e );
        }

        return;
    }

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_UNITREASSIGN_STOP );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }
}

bool ZDProcessGraphModelDoc::AssignCurrentSystemDefGUID()
{
    ZBLogicalSystemEntity* pSystem = GetMainLogicalSystem();

    // No system, error
    if ( !pSystem )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_SYSTEMDEF );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }
    }
    else
    {
        // Assigns the current system
        AssignSystemDefGUID( pSystem->GetGUID() );

        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_SYSTEMDEFXML_ASSIGNED );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }

        // Main logical system is valid
        GetModel()->SetMainLogicalSystemValid();

        // Modified
        SetModifiedFlag();

        return true;
    }

    return false;
}

void ZDProcessGraphModelDoc::ReassignSystem( ZILog* pLog /*= NULL*/ )
{
    ASSERT( GetModel() );

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_SYSTEMREASSIGN_START );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    // If the logical system file is valid,
    // then run through elements and assigns system
    if ( GetModel()->MainLogicalSystemIsValid() )
    {
        GetModel()->ReassignSystem( pLog );
    }
    else
    {
        if ( pLog )
        {
            CString message;
            message.LoadString( IDS_AL_SYSTEMCANNOTREASSIGN );
            ZBGenericSymbolErrorLine e( message );
            pLog->AddLine( e );
        }

        return;
    }

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_SYSTEMREASSIGN_STOP );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }
}

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction AssignCurrentPrestationsDefGUID.
bool ZDProcessGraphModelDoc::AssignCurrentPrestationsDefGUID()
{
    ZBLogicalPrestationsEntity* pPrestations = GetMainLogicalPrestations();

    // No prestations, error
    if ( !pPrestations )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_PRESTATIONSDEF );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }
    }
    else
    {
        // Assigns the current GUID
        AssignPrestationsDefGUID( pPrestations->GetGUID() );

        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_PRESTATIONS_ASSIGNED );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }

        // Main prestation is valid
        GetModel()->SetMainLogicalPrestationsValid();

        // Modified
        SetModifiedFlag();

        return true;
    }

    return false;
}

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction ReassignPrestations.
void ZDProcessGraphModelDoc::ReassignPrestations( ZILog* pLog /*= NULL*/ )
{
    ASSERT( GetModel() );

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_PRESTATIONSREASSIGN_START );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    // Main prestations is not valid
    if ( GetModel()->MainLogicalPrestationsIsValid() )
    {
        GetModel()->ReassignPrestations( pLog );
    }
    else
    {
        if ( pLog )
        {
            CString message;
            message.LoadString( IDS_AL_PRESTATIONSCANNOTREASSIGN );
            ZBGenericSymbolErrorLine e( message );
            pLog->AddLine( e );
        }

        return;
    }

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_PRESTATIONSREASSIGN_STOP );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }
}

// JMR-MODIF - Le 19 novembre 2006 - Ajout de la fonction AssignCurrentRulesDefGUID.
bool ZDProcessGraphModelDoc::AssignCurrentRulesDefGUID()
{
    ZBLogicalRulesEntity* pRules = GetMainLogicalRules();

    // No Rules, error
    if ( !pRules )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_RULESDEF );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }
    }
    else
    {
        // Assigns the current GUID
        AssignRulesDefGUID( pRules->GetGUID() );

        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_RULES_ASSIGNED );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );
        }

        // Main rule is valid
        GetModel()->SetMainLogicalRulesValid();

        // Modified
        SetModifiedFlag();

        return true;
    }

    return false;
}

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction ReassignRules.
void ZDProcessGraphModelDoc::ReassignRules( ZILog* pLog /*= NULL*/ )
{
    ASSERT( GetModel() );

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_RULESREASSIGN_START );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }

    // Main Rules is not valid
    if ( GetModel()->MainLogicalRulesIsValid() )
    {
        GetModel()->ReassignRules( pLog );
    }
    else
    {
        if ( pLog )
        {
            CString message;
            message.LoadString( IDS_AL_RULESCANNOTREASSIGN );
            ZBGenericSymbolErrorLine e( message );
            pLog->AddLine( e );
        }

        return;
    }

    if ( pLog )
    {
        CString message;
        message.LoadString( IDS_AL_RULESREASSIGN_STOP );
        ZBGenericSymbolErrorLine e( message );
        pLog->AddLine( e );
    }
}

void ZDProcessGraphModelDoc::OnPostOpenDocument()
{
    ASSERT( GetModel() );

    // Call the PostOpenDocument method
    GetModel()->OnPostOpenDocument( GetDocumentStamp().GetInternalVersion() );

    // Check if we have the right GUID for the SystemDef, the UserDef, the PrestationsDef and the RulesDef
    ZBUserGroupEntity* pUserGroup = GetMainUserGroup();

    if ( !pUserGroup )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_USERGROUP );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );

            // Main user group is not valid
            GetModel()->SetMainUserGroupValid( false );
        }
    }
    else
    {
        // If the current userdef GUID is not empty and is different
        // then display an error message
        // and set the flag for avoiding updates on userdef's linked items
        if ( !m_UserDefGUID.IsEmpty() && m_UserDefGUID != pUserGroup->GetGUID() )
        {
            if ( m_pOutputLog )
            {
                CString message;
                message.LoadString( IDS_ERR_USERGROUP_DIFFMODEL );
                ZBGenericSymbolErrorLine e( message );
                m_pOutputLog->AddLine( e );
            }

            // Main user group is not valid
            GetModel()->SetMainUserGroupValid( false );
        }
        else
        {
            // Main user group is valid
            GetModel()->SetMainUserGroupValid();
        }
    }

    ZBLogicalSystemEntity* pSystem = GetMainLogicalSystem();

    // No system, error
    if ( !pSystem )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_SYSTEMDEF );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );

            // Main logical system is not valid
            GetModel()->SetMainLogicalSystemValid( false );
        }
    }
    else
    {
        // If the current systemdef GUID is not empty and is different
        // then display an error message
        // and set the flag for avoiding updates on system's linked items
        if ( !m_SystemDefGUID.IsEmpty() && m_SystemDefGUID != pSystem->GetGUID() )
        {
            if ( m_pOutputLog )
            {
                CString message;
                message.LoadString( IDS_ERR_SYSTEMDEFXML_DIFFMODEL );
                ZBGenericSymbolErrorLine e( message );
                m_pOutputLog->AddLine( e );
            }

            // Main logical system is not valid
            GetModel()->SetMainLogicalSystemValid( false );
        }
        else
        {
            // Main logical system is valid
            GetModel()->SetMainLogicalSystemValid();
        }
    }

    // ************************************************************************************************************
    // JMR-MODIF - Le 1er février 2006 - Ajout du code pour la synchronisation des documents de prestations.

    ZBLogicalPrestationsEntity* pPrestations = GetMainLogicalPrestations();

    // No prestations, error
    if ( !pPrestations )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_PRESTATIONSDEF );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );

            // Main logical prestations is not valid
            GetModel()->SetMainLogicalPrestationsValid( false );
        }
    }
    else
    {
        // If the current prestationsdef GUID is not empty and is different
        // then display an error message
        // and set the flag for avoiding updates on prestations's linked items
        if ( !m_PrestationsDefGUID.IsEmpty() && m_PrestationsDefGUID != pPrestations->GetGUID() )
        {
            if ( m_pOutputLog )
            {
                CString message;
                message.LoadString( IDS_ERR_PRESTATIONSDEFXML_DIFFMODEL );
                ZBGenericSymbolErrorLine e( message );
                m_pOutputLog->AddLine( e );
            }

            // Main logical prestations is not valid
            GetModel()->SetMainLogicalPrestationsValid( false );
        }
        else
        {
            // Main logical prestations is valid
            GetModel()->SetMainLogicalPrestationsValid();
        }
    }
    // ************************************************************************************************************

    // ************************************************************************************************************
    // JMR-MODIF - Le 19 novembre 2006 - Ajout du code pour la synchronisation des documents des règles.

    ZBLogicalRulesEntity* pRules = GetMainLogicalRules();

    // No Rules, error
    if ( !pRules )
    {
        if ( m_pOutputLog )
        {
            CString message;
            message.LoadString( IDS_ERR_MISSING_RULESDEF );
            ZBGenericSymbolErrorLine e( message );
            m_pOutputLog->AddLine( e );

            // Main logical Rules is not valid
            GetModel()->SetMainLogicalRulesValid( false );
        }
    }
    else
    {
        // If the current Rulesdef GUID is not empty and is different
        // then display an error message
        // and set the flag for avoiding updates on Rules's linked items
        if ( !m_RulesDefGUID.IsEmpty() && m_RulesDefGUID != pRules->GetGUID() )
        {
            if ( m_pOutputLog )
            {
                CString message;
                message.LoadString( IDS_ERR_RULESDEFXML_DIFFMODEL );
                ZBGenericSymbolErrorLine e( message );
                m_pOutputLog->AddLine( e );
            }

            // Main logical rules is not valid
            GetModel()->SetMainLogicalRulesValid( false );
        }
        else
        {
            // Main logical rules is valid
            GetModel()->SetMainLogicalRulesValid();
        }
    }
    // ************************************************************************************************************

    // Message to notify end of fileopen
    if ( m_pOutputLog )
    {
        CString message;
        message.Format( IDS_MSG_OPENMODEL_END, GetModel()->GetModelName(), GetPathName() );
        ZBGenericSymbolErrorLine e( message );
        m_pOutputLog->AddLine( e );
    }
}

// Allocate the dynamic properties manager
// if the pointer is null and the parameter DeleteFirst is set to true, 
// delete it first
void ZDProcessGraphModelDoc::AllocatePropertiesManager( bool DeleteFirst /*= false*/ )
{
    if ( DeleteFirst && m_DynamicPropertiesManager )
    {
        delete m_DynamicPropertiesManager;
    }

    m_DynamicPropertiesManager = new ZBDynamicPropertiesManager;
}

BOOL ZDProcessGraphModelDoc::IsModified()
{
    return ZDBaseDocument::IsModified() || GetModel()->IsModified();
}

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelDoc commands

void ZDProcessGraphModelDoc::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
    // Forward the message to the controller
    if ( GetFirstModelView() && GetFirstModelView()->GetModelController() )
    {
        GetFirstModelView()->GetModelController()->OnUpdate( pSubject, pMsg );
    }
}

void ZDProcessGraphModelDoc::DeleteContents()
{
    // JMR-MODIF - Le 29 septembre 2005 - Ajout de la variable DocumentAlreadyOpened.
    // Cette modification devrait être provisoire, et disparaître lorsque le multi-documents sera mieux géré.
    static BOOL DocumentAlreadyOpened = FALSE;

    // JMR-MODIF - Le 29 septembre 2005 - Initialise un nouveau modèle que si le document n'est pas en cours de fermeture.
    if ( IsDocumentClosing == FALSE && DocumentAlreadyOpened == FALSE )
    {
        m_EmptyModel.Initialize();
        GetModel()->Initialize();

        DocumentAlreadyOpened = TRUE;
    }

    ZDBaseDocument::DeleteContents();
}

// JMR-MODIF - Le 29 septembre 2005 - Cette fonction permet de déterminer si le document est en cours de fermeture.
BOOL ZDProcessGraphModelDoc::IsClosing()
{
    return IsDocumentClosing;
}

void ZDProcessGraphModelDoc::OnCloseDocument()
{
    // JMR-MODIF - Le 29 septembre 2005 - Bascule le flag IsDocumentClosing en mode fermeture.
    IsDocumentClosing = TRUE;

    AfxGetMainWnd()->SendMessageToDescendants( UM_CLOSEDOCUMENTMODELTREE );
    AfxGetMainWnd()->SendMessageToDescendants( UM_CLOSEUNITMODELTREE );

    // ********************************************************************************************************
    // JMR-MODIF - Le 25 avril 2006 - Déverouille le fichier en cours d'utilisation à la fermeture du document.

    // Lorsqu'un utilisateur a verouillé un modèle, il est protégé sur le disque, mais la variable IsReadOnly
    // reste FALSE dans cette classe. Ainsi, seul cet utilisateur déverouille le modèle lorsqu'il le ferme.
    if ( IsReadOnly() == FALSE )
    {
        SetFileReadOnly( GetPathName(), FALSE );
    }
    // ********************************************************************************************************

    ZDBaseDocument::OnCloseDocument();
}

BOOL ZDProcessGraphModelDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
    // JMR-MODIF - Le 29 septembre 2005 - Bascule le flag IsDocumentClosing en mode normal.
    IsDocumentClosing = FALSE;

    // Open file message
    if ( m_pOutputLog )
    {
        CString message;
        message.Format( IDS_MSG_OPENMODEL_START, lpszPathName );
        ZBGenericSymbolErrorLine e( message );
        m_pOutputLog->AddLine( e );
    }

    if ( !ZDBaseDocument::OnOpenDocument( lpszPathName ) )
    {
        return FALSE;
    }
    
    if ( !IsUnit() && HasUnit() )
    {
        // Build the message
        ZBDocObserverMsg DocMsg( ZBDocObserverMsg::OpenDocument, this );
        AfxGetMainWnd()->SendMessageToDescendants( UM_INITIALIZEDOCUMENTMODEL, 0, (LPARAM)&DocMsg );

        // Build the message even if the unit manager is NULL
        ZBUnitObserverMsg UnitMsg( ZBUnitObserverMsg::OpenUnit, m_pUnitManager );
        AfxGetMainWnd()->SendMessageToDescendants( UM_INITIALIZEUNITMODEL, 0, (LPARAM)&UnitMsg );
    }

    // Build the message even if the unit manager is NULL
    ZBDocObserverMsg DocMsg( ZBDocObserverMsg::OpenDocument, this );
    AfxGetMainWnd()->SendMessage( UM_DOCUMENTLOADED, 0, (LPARAM)&DocMsg );

    return TRUE;
}

BOOL ZDProcessGraphModelDoc::OnNewDocument()
{
    // JMR-MODIF - Le 29 septembre 2005 - Bascule le flag IsDocumentClosing en mode normal.
    IsDocumentClosing = FALSE;

    if ( !ZDBaseDocument::OnNewDocument() )
    {
        return FALSE;
    }

    // Set model name for new document
    GetModel()->SetModelName( GetTitle() );

    if ( !IsUnit() && HasUnit() )
    {
        // Build the message
        ZBDocObserverMsg DocMsg( ZBDocObserverMsg::OpenDocument, this );
        AfxGetMainWnd()->SendMessageToDescendants( UM_INITIALIZEDOCUMENTMODEL, 0, (LPARAM)&DocMsg );

        // Build the message even if the unit manager is NULL
        ZBUnitObserverMsg UnitMsg( ZBUnitObserverMsg::OpenUnit, m_pUnitManager );
        AfxGetMainWnd()->SendMessageToDescendants( UM_INITIALIZEUNITMODEL, 0, (LPARAM)&UnitMsg );
    }

    // Build the message even if the unit manager is NULL
    ZBDocObserverMsg DocMsg( ZBDocObserverMsg::OpenDocument, this );
    AfxGetMainWnd()->SendMessage( UM_DOCUMENTLOADED, 0, (LPARAM)&DocMsg );

    // Assigns the current systemdef, userdef, prestationsdef and rulesdef
    AssignCurrentSystemDefGUID();
    AssignCurrentUserDefGUID();
    // JMR-MODIF - Le 1er février 2006 - Ajout de l'attribution d'un GUID aux prestations.
    AssignCurrentPrestationsDefGUID();
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de l'attribution d'un GUID aux règles.
    AssignCurrentRulesDefGUID();

    return TRUE;
}

// JMR-MODIF - Le 9 juillet 2006 - Ajout de la fonction DoFileSave, afin de pouvoir agir sur le verrouillage fichier.
BOOL ZDProcessGraphModelDoc::DoFileSave()
{
    BOOL Result = FALSE;

    // Pour éviter que la boîte de dialogue "Enregistrer sous..." apparaîsse, on déverrouille le fichier.
    SetFileReadOnly( m_strPathName, FALSE );

    Result = CDocument::DoFileSave();

    // Verrouille à nouveau le fichier à la fin de la sauvegarde.
    SetFileReadOnly( m_strPathName, TRUE );

    return Result;
}

//    Call when save document is required.
BOOL ZDProcessGraphModelDoc::OnSaveDocument( const char* pszPathName )
{
    if ( strlen( pszPathName ) == 0 )
    {
        return DoSave( NULL );
    }

    // *******************************************************************************************************
    // JMR-MODIF - Le 25 avril 2006 - Teste si le fichier a été vérouillé avant de tenter de l'enregistrer.

    // Contrôle l'action que l'utilisateur a tenté d'effectuer par rapport au mode de verrouillage.
    if ( b_IsReadOnly == TRUE && GetPathName() == pszPathName )
    {
        // L'utilisateur tente d'écraser un fichier ouvert en lecture seule.
        MsgBox mbox;

        mbox.DisplayMsgBox( IDS_FILE_READONLY_DONOTSAVE, MB_OK );
        return FALSE;
    }
    else if ( b_IsReadOnly == TRUE && GetPathName() != pszPathName )
    {
        // L'utilisateur n'a pas le droit de modifier le fichier ouvert, mais tente de l'enregistrer sous
        // un nouveau nom. Dans ce cas, il obtient les droits de modification pour son nouveau fichier.
        SetReadOnly( FALSE );
    }
    else if ( b_IsReadOnly == FALSE && GetPathName() != pszPathName )
    {
        // L'utilisateur a le droit de modifier le fichier, mais tente de l'enregistrer sous un nouveau nom.
        // Dans ce cas, il convient de déverrouiller l'ancien fichier, puis de verrouiller le nouveau. Puisque
        // GetPathName n'a pas encore été réattribué, il contient toujours le chemin de l'ancien fichier.
        SetFileReadOnly( GetPathName(), FALSE );
    }
    // *******************************************************************************************************

    // if template check the model
    if (DocumentIsTemplate())
    {}

    // Build the new title,
    // FALSE: do not add to MRU
    SetPathName( pszPathName, FALSE );

    // Adapt the model information
    GetModel()->SetModelName( GetTitle() );

    PSS_Application::Instance()->GetMainForm()->UpdateLastLoadedFile(pszPathName);

    // Message to notify the start of filesave
    if ( m_pOutputLog )
    {
        CString message;
        message.Format( IDS_MSG_SAVEMODEL_END, GetModel()->GetModelName(), GetPathName() );
        ZBGenericSymbolErrorLine e( message );
        m_pOutputLog->AddLine( e );
    }

    // Check if we have a GUID defined for the SystemDef, the UserDef, the PrestationsDef and the RulesDef
    if ( m_UserDefGUID.IsEmpty() )
    {
        AssignCurrentUserDefGUID();
    }

    if ( m_SystemDefGUID.IsEmpty() )
    {
        AssignCurrentSystemDefGUID();
    }

    // JMR-MODIF - Le 1er février 2006 - Teste si un GUID est défini pour les prestations.
    if ( m_PrestationsDefGUID.IsEmpty() )
    {
        AssignCurrentPrestationsDefGUID();
    }

    // JMR-MODIF - Le 19 novembre 2006 - Teste si un GUID est défini pour les règles.
    if ( m_RulesDefGUID.IsEmpty() )
    {
        AssignCurrentRulesDefGUID();
    }

    // JMR-MODIF - Le 27 avril 2006 - Déverrouille le fichier le temps que la sauvegarde soit effectuée.
    SetFileReadOnly( pszPathName, FALSE );

    // And save the document
    BOOL RetValue = ZDBaseDocument::OnSaveDocument( pszPathName );

    // JMR-MODIF - Le 27 avril 2006 - Verrouille à nouveau le fichier à la fin de la sauvegarde.
    SetFileReadOnly( pszPathName, TRUE );

    // Build the message
    ZBDocObserverMsg DocMsg;
    AfxGetMainWnd()->SendMessageToDescendants( UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg );

    // Message to notify end of filesave
    if ( m_pOutputLog )
    {
        CString message;
        message.Format( IDS_MSG_SAVEMODEL_END, GetModel()->GetModelName(), GetPathName() );
        ZBGenericSymbolErrorLine e( message );
        m_pOutputLog->AddLine( e );
    }

    return RetValue;
}

// JMR-MODIF - Le 27 avril 2006 - Cette fonction permet de changer la propriété "lecture seule" d'un fichier donné.
BOOL ZDProcessGraphModelDoc::SetFileReadOnly( const char* pszPathName, BOOL Value )
{
    BOOL    bRet    = FALSE;
    ZFile*    theFile    = new ZFile( pszPathName );

    if ( theFile != NULL )
    {
        if ( theFile->Exist() )
        {
            theFile->SetReadOnly( Value );
            bRet = TRUE;
        }

        delete theFile;
        theFile = NULL;
    }

    return bRet;
}

bool ZDProcessGraphModelDoc::ReadFromFile( const CString Filename )
{
    bool            RetValue = false;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );
    loadArchive.m_pDocument        = this;
    loadArchive.m_bForceFlat    = FALSE;

    TRY
    {
        Serialize( loadArchive );
        RetValue = true;
    }
    CATCH( CArchiveException, e )
    {
        RetValue = false;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // If everything is ok, set the pathname.
    if ( RetValue )
    {
        SetPathName( Filename, FALSE );
    }

    return RetValue;
}

bool ZDProcessGraphModelDoc::SaveToFile( const CString Filename )
{
    bool            RetValue = false;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive saveArchive( &file, CArchive::store | CArchive::bNoFlushOnDelete );
    saveArchive.m_pDocument        = this;
    saveArchive.m_bForceFlat    = FALSE;

    TRY
    {
        Serialize( saveArchive );
        RetValue = true;
    }
    CATCH( CArchiveException, e )
    {
        RetValue = false;
    }
    END_CATCH

    saveArchive.Close();
    file.Close();

    // After a save, clear the modified flag
    SetModifiedFlag( FALSE );

    return RetValue;
}

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelDoc diagnostics

#ifdef _DEBUG

void ZDProcessGraphModelDoc::AssertValid() const
{
    ZDBaseDocument::AssertValid();
}

void ZDProcessGraphModelDoc::Dump( CDumpContext& dc ) const
{
    ZDBaseDocument::Dump( dc );
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelDoc serialization

void ZDProcessGraphModelDoc::Serialize( CArchive& ar )
{
    // Serialize stamp and base information.
    ZDBaseDocument::Serialize( ar );

    m_PageUnits.Serialize( ar );
    
    // Serialize the canvas model.
    m_EmptyModel.Serialize( ar );

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            // Store the unique GUID for this file
            ar << m_GUID;

            // Store the adequate user def GUID
            ar << m_UserDefGUID;

            // Store the system user def GUID 
            ar << m_SystemDefGUID;

            // JMR-MODIF - Le 1er février 2006 - A partir de la version 24, les prestations sont aussi disponibles.
            if ( ar.m_pDocument &&
                 dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 24 )
            {
                ar << m_PrestationsDefGUID;
            }

            // JMR-MODIF - Le 19 novembre 2006 - A partir de la version 26, les règles sont aussi disponibles.
            if ( ar.m_pDocument &&
                 dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 26 )
            {
                ar << m_RulesDefGUID;
            }

            ar << m_pModel;
            ar << m_pUnitManager;

            // Serialize workflow data member
            ar << (WORD)m_UseWorkflow;

            // Serialize the workflow definition
            ar << m_pWorkflowDefinition;

            // Serialize the flag for browsing in the same window
            ar << (WORD)m_BrowseInSameWindow;

            // Cost simulation flag
            ar << (WORD)m_IntegrateCostSimulation;

            // Consistency flag
            ar << (WORD)m_CheckConsistency;

            ar << m_HourPerDay;
            ar << m_DayPerWeek;
            ar << m_DayPerMonth;
            ar << m_DayPerYear;
            ar << m_CurrencySymbol;
            ar << (WORD)m_ShowPageBorder;

            // ***************************************************************************************
            // Printer page attributes
            // JMR-MODIF - Le 14 juillet 2005 - Remplace l'ancienne implémentation par la nouvelle implémentation.
            //ar << m_PaperSize;
            //ar << m_StandardSize;
            //ar << m_Orientation;

            ZIProcessGraphModelView* pView = GetFirstModelView();

            if ( pView != NULL )
            {
                ZVDocumentPageSetup* m_pPageSetup = pView->GetPrinterPageSize();

                ar << m_pPageSetup->GetPaperSize();
                ar << m_pPageSetup->GetStandardSize();
                ar << m_pPageSetup->GetOrientation();
            }
            else
            {
                // Ce cas ne devrait pas arriver, mais on inscrit quand même une page par défaut.
                ar << g_DefaultPaperSize;
                ar << g_DefaultStandardSize;
                ar << g_DefaultOrientation;
            }
            // ***************************************************************************************

            // Serialize the dynamic properties    manager
            ar << m_DynamicPropertiesManager;

            // Call the post write method
            GetModel()->PostWrite( ar );
        }
        else
        {
            if ( GetDocumentStamp().GetInternalVersion() >= 19 )
            {
                ar >> m_GUID;
                ar >> m_UserDefGUID;
                ar >> m_SystemDefGUID;

                // JMR-MODIF - Le 1er février 2006 - A partir de la version 24, les prestations sont aussi disponibles.
                if ( ar.m_pDocument &&
                     dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 24 )
                {
                    ar >> m_PrestationsDefGUID;
                }

                // JMR-MODIF - Le 19 novembre 2006 - A partir de la version 26, les règles sont aussi disponibles.
                if ( ar.m_pDocument &&
                     dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 26 )
                {
                    ar >> m_RulesDefGUID;
                }
            }

            ZDProcessGraphModelMdl* pModel = NULL;
            ar >> pModel;
            ar >> m_pUnitManager;

            WORD wValue;
            ar >> wValue;
            m_UseWorkflow = ( wValue == 1 ) ? true : false;
        
            // DeSerialize the workflow definition
            ar >> (CObject*&)m_pWorkflowDefinition;

            // DeSerialize the flag for browsing in the same window
            ar >> wValue;
            m_BrowseInSameWindow = ( wValue == 1 ) ? true : false;

            // Cost simulation flag
            ar >> wValue;
            m_IntegrateCostSimulation = ( wValue == 1 ) ? true : false;

            // Consistency flag
            ar >> wValue;
            m_CheckConsistency = ( wValue == 1 ) ? true : false;

            ar >> m_HourPerDay;
            ar >> m_DayPerWeek;
            ar >> m_DayPerMonth;
            ar >> m_DayPerYear;
            ar >> m_CurrencySymbol;

            // show page border flag
            ar >> wValue;
            m_ShowPageBorder = ( wValue == 1 ) ? true : false;
            
            // Printer page attributes
            ar >> m_PaperSize;
            ar >> m_StandardSize;
            ar >> m_Orientation;

            // Serialize the dynamic properties manager
            if ( ar.m_pDocument &&
                 dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 21 )
            {
                ar >> (CObject*&)m_DynamicPropertiesManager;
            }

            // Now, replace the existing model by the one we've read
            SetNewModel( pModel );

            // Initialize the unit manager is there is one defined
            if ( m_pUnitManager )
            {
                if ( GetDocTemplate() && ISA( GetDocTemplate(), ZDProcessModelDocTmpl ) )
                {
                    m_pUnitManager->Initialize( (ZDProcessModelDocTmpl*)GetDocTemplate() );
                    m_pUnitManager->LoadAllUnits();
                }
            }

            // Call the post read method
            GetModel()->PostRead( ar );
        }
    }
}
