// ProcGraphModelCtlrBP.cpp : implementation of the ZDProcessGraphModelControllerBP class

#include "stdafx.h"
#include "ProcGraphModelCtlrBP.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_FloatingToolBar.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zModel\ProcGraphModelVp.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ProcGraphModelDoc.h"
#define _ZMODELEXPORT
#include "zModel\ProcGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\ZUBuildSymbolNewName.h"
#include "zModel\ZDProcessGraphPage.h"
#include "zModel\ZVInsertModelNewPageDlg.h"
#include "zModel\ZVRenameModelPageDlg.h"
#include "zModel\ZVRenameModelPageInTreeDlg.h"
#include "zModel\ZVDeleteModelPageDlg.h"
#include "zModel\ZBUnitObserverMsg.h"
#include "zModel\ZBDocObserverMsg.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBBPPackageSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"
#include "zModelBP\ZBBPGenericSymbol.h"
#include "zModelBP\ZBBPTextZone.h"
#include "ProcGraphModelMdlBP.h"
#include "ZUDeleteCorruptedSymbols.h"
#include "ZBSesterceRecalculationAutomate.h"
#include "ZBDurationRecalculationAutomate.h"
#include "ZVInputAttributesSelectionDlg.h"
#include "ZVRiskCalculateParametersDlg.h"
#include "ZUCalculateRisks.h"
#include "zBaseLib\PSS_Global.h"

// resources
#include "zModelBPRes.h"
#include "zModel\zModelRes.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Static member initialization
SECCustomToolBar*    ZDProcessGraphModelControllerBP::m_pwndModelisationBar = NULL;
SECCustomToolBar*    ZDProcessGraphModelControllerBP::m_pwndModelGenerationBar = NULL;

BEGIN_MESSAGE_MAP(ZDProcessGraphModelControllerBP, ZDProcessGraphModelController)
    //{{AFX_MSG_MAP(ZDProcessGraphModelControllerBP)
    ON_COMMAND(ID_INS_BP_PROCEDURE, OnInsProcedure)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_PROCEDURE, OnUpdateInsProcedure)
    ON_COMMAND(ID_INS_BP_PROCESS, OnInsProcess)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_PROCESS, OnUpdateInsProcess)
    ON_COMMAND(ID_INS_BP_PAGE, OnInsPage)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_PAGE, OnUpdateInsPage)
    ON_COMMAND(ID_INS_BP_DOOR, OnInsDoor)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_DOOR, OnUpdateInsDoor)
    ON_COMMAND(ID_INS_BP_STOP, OnInsStop)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_STOP, OnUpdateInsStop)
    ON_COMMAND(ID_INS_BP_START, OnInsStart)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_START, OnUpdateInsStart)
    ON_COMMAND(ID_INS_BP_DELIVERABLE, OnInsDeliverable)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_DELIVERABLE, OnUpdateInsDeliverable)
    ON_COMMAND(ID_INS_BP_PACKAGE, OnInsPackage)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_PACKAGE, OnUpdateInsPackage)
    ON_COMMAND(ID_INS_BP_ALERT, OnInsAlert)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_ALERT, OnUpdateInsAlert)
    ON_COMMAND(ID_INS_BP_DOCUMENT, OnInsDocument)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_DOCUMENT, OnUpdateInsDocument)
    ON_COMMAND(ID_INS_BP_INDICATOR, OnInsIndicator)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_INDICATOR, OnUpdateInsIndicator)
    ON_COMMAND(ID_INS_BP_QUALITY, OnInsQuality)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_QUALITY, OnUpdateInsQuality)
    ON_COMMAND(ID_INS_BP_DELAY, OnInsDelay)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_DELAY, OnUpdateInsDelay)
    ON_COMMAND(ID_INS_BP_IN_PROCESS, OnInsInProcess)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_IN_PROCESS, OnUpdateInsInProcess)
    ON_COMMAND(ID_INS_BP_NOT_VALIDATED, OnInsNotValidated)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_NOT_VALIDATED, OnUpdateInsNotValidated)
    ON_COMMAND(ID_INS_BP_VALIDATED, OnInsValidated)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_VALIDATED, OnUpdateInsValidated)
    ON_COMMAND(ID_INS_BP_RISK, OnInsRisk)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_RISK, OnUpdateInsRisk)
    ON_COMMAND(ID_INS_BP_INCIDENT, OnInsIncident)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_INCIDENT, OnUpdateInsIncident)
    ON_COMMAND(ID_INS_BP_CRI, OnInsCRI)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_CRI, OnUpdateInsCRI)
    ON_COMMAND(ID_INS_BP_CRE, OnInsCRE)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_CRE, OnUpdateInsCRE)
    ON_COMMAND(ID_INS_BP_CRO, OnInsCRO)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_CRO, OnUpdateInsCRO)
    ON_COMMAND(ID_INS_BP_OPAP1, OnInsOPAP1)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_OPAP1, OnUpdateInsOPAP1)
    ON_COMMAND(ID_INS_BP_OPAP2, OnInsOPAP2)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_OPAP2, OnUpdateInsOPAP2)
    ON_COMMAND(ID_INS_BP_OPAP3, OnInsOPAP3)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_OPAP3, OnUpdateInsOPAP3)
    ON_COMMAND(ID_INS_BP_TEXTZONE, OnInsTextZone)
    ON_UPDATE_COMMAND_UI(ID_INS_BP_TEXTZONE, OnUpdateInsTextZone)
    ON_COMMAND(ID_SHOWPROCESS_PREVIEW, OnShowProcessPreview)
    ON_UPDATE_COMMAND_UI(ID_SHOWPROCESS_PREVIEW, OnUpdateShowProcessPreview)
    ON_COMMAND(ID_OD_MEASUREMENTS, OnOdMeasurements)
    ON_COMMAND(ID_LINKTOFILE_PACKAGE, OnLinktoFilePackage)
    ON_COMMAND(ID_UNLINKFROMFILE_PACKAGE, OnUnlinkFromFilePackage)
    ON_UPDATE_COMMAND_UI(ID_UNLINKFROMFILE_PACKAGE, OnUpdateUnlinkFromFilePackage)
    ON_COMMAND(ID_LOAD_PACKAGE, OnLoadPackage)
    ON_UPDATE_COMMAND_UI(ID_LOAD_PACKAGE, OnUpdateLoadPackage)
    ON_COMMAND(ID_UNLOAD_PACKAGE, OnUnloadPackage)
    ON_UPDATE_COMMAND_UI(ID_UNLOAD_PACKAGE, OnUpdateUnloadPackage)
    ON_COMMAND(ID_OD_VIEW_COMPS, OnViewComponents)
    ON_COMMAND(ID_VIEW_MODELGENTOOLBAR, OnViewModelGenToolbar)
    ON_COMMAND(ID_VIEW_MODELTOOLBAR, OnViewModelToolbar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_MODELGENTOOLBAR, OnUpdateViewModelGenToolbar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_MODELTOOLBAR, OnUpdateViewModelToolbar)
    ON_COMMAND(ID_CHECK_MODEL, OnCheckModel)
    ON_UPDATE_COMMAND_UI(ID_CHECK_MODEL, OnUpdateCheckModel)
    ON_COMMAND(ID_RECALCULATE_MODEL_PARAM, OnRecalculateModelParameters)
    ON_UPDATE_COMMAND_UI(ID_RECALCULATE_MODEL_PARAM, OnUpdateRecalculateModelParameters)
    ON_COMMAND(ID_RECALCULATE_MODEL_DURATION, OnRecalculateModelDurations)
    ON_UPDATE_COMMAND_UI(ID_RECALCULATE_MODEL_DURATION, OnUpdateRecalculateModelDurations)
    ON_COMMAND(ID_CALCULATE_RISKS, OnCalculateRisks)
    ON_UPDATE_COMMAND_UI(ID_CALCULATE_RISKS, OnUpdateCalculateRisks)
    ON_COMMAND(ID_INSERT_MODELPAGE, OnInsertPage)
    ON_COMMAND(ID_RENAME_MODELPAGE, OnRenamePage)
    ON_COMMAND(ID_DELETE_MODELPAGE, OnDeletePage)
    ON_COMMAND(ID_RENAME_CURRENTMODELPAGE, OnRenameCurrentPage)
    ON_COMMAND(ID_PLAY_SIMULATION, OnPlaySimulation)
    ON_UPDATE_COMMAND_UI(ID_PLAY_SIMULATION, OnUpdatePlaySimulation)
    ON_COMMAND(ID_PAUSE_SIMULATION, OnPauseSimulation)
    ON_UPDATE_COMMAND_UI(ID_PAUSE_SIMULATION, OnUpdatePauseSimulation)
    ON_COMMAND(ID_STOP_SIMULATION, OnStopSimulation)
    ON_UPDATE_COMMAND_UI(ID_STOP_SIMULATION, OnUpdateStopSimulation)
    ON_COMMAND(ID_REW_SIMULATION, OnRewSimulation)
    ON_UPDATE_COMMAND_UI(ID_REW_SIMULATION, OnUpdateRewSimulation)
    ON_COMMAND(ID_FWD_SIMULATION, OnFwdSimulation)
    ON_UPDATE_COMMAND_UI(ID_FWD_SIMULATION, OnUpdateFwdSimulation)
    ON_COMMAND(ID_SHOWINPUTATTRIBUTES, OnShowInputAttributes)
    ON_UPDATE_COMMAND_UI(ID_SHOWINPUTATTRIBUTES, OnUpdateShowInputAttributes)
    ON_COMMAND(ID_EDIT_FORMATPAINTER, OnFormatPainter)
    ON_UPDATE_COMMAND_UI(ID_EDIT_FORMATPAINTER, OnUpdateFormatPainter)
    ON_COMMAND(ID_OD_PROPERTIES, OnProperties)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelControllerBP

ZDProcessGraphModelControllerBP::ZDProcessGraphModelControllerBP(ZIProcessGraphModelViewport* pViewport)
    : ZDProcessGraphModelController(pViewport)
{
    // Load the right main menu for components
    m_SymbolRightMainMenu.LoadMenu(IDR_SYMBOL_RIGHTMENU_BP);
    m_SymbolRefRightMainMenu.LoadMenu(IDR_SYMBOL_REF_RIGHTMENU_BP);
}

ZDProcessGraphModelControllerBP::~ZDProcessGraphModelControllerBP()
{}

// Proceed the drop of an object to the model
bool ZDProcessGraphModelControllerBP::DropItemToModel(CObject* pObj, CPoint pt)
{
    // Call the base class
    return ZDProcessGraphModelController::DropItemToModel(pObj, pt);
}

// Check if the drop can be done successfuly on the model
bool ZDProcessGraphModelControllerBP::AcceptDropItemToModel(CObject* pObj, CPoint pt)
{
    // Call the base class
    return ZDProcessGraphModelController::AcceptDropItemToModel(pObj, pt);
}

// Proceed the drop of an object
bool ZDProcessGraphModelControllerBP::DropItem(CObject* pObj, CPoint pt)
{
    // Call the base class
    return ZDProcessGraphModelController::DropItem(pObj, pt);
}

// Check if the drop can be done successfuly
bool ZDProcessGraphModelControllerBP::AcceptDropItem(CObject* pObj, CPoint pt)
{
    // Call the base class
    return ZDProcessGraphModelController::AcceptDropItem(pObj, pt);
}

void ZDProcessGraphModelControllerBP::InsertPageSymbol()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPPageSymbol* pSymbol = new ZBBPPageSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);
}

void ZDProcessGraphModelControllerBP::InsertDoorSymbol()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPDoorSymbol* pSymbol = new ZBBPDoorSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);
}

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelControllerBP message handlers

void ZDProcessGraphModelControllerBP::OnInsPackage()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPPackageSymbol* pSymbol = new ZBBPPackageSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_PACKAGEBP);
    m_CurrentCursor = IDC_INS_PACKAGEBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_PACKAGE;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsPackage(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PACKAGE);
}

void ZDProcessGraphModelControllerBP::OnInsProcedure()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPProcedureSymbol* pSymbol = new ZBBPProcedureSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_PROCEDUREBP);
    m_CurrentCursor = IDC_INS_PROCEDUREBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_PROCEDURE;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsProcedure(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PROCEDURE);
}

void ZDProcessGraphModelControllerBP::OnInsProcess()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPProcessSymbol* pSymbol = new ZBBPProcessSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_PROCESSBP);
    m_CurrentCursor = IDC_INS_PROCESSBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_PROCESS;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsProcess(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PROCESS);
}

void ZDProcessGraphModelControllerBP::OnInsPage()
{
    InsertPageSymbol();

    // Change the cursor
    SetCustomCursor(IDC_INS_PAGEBP);
    m_CurrentCursor = IDC_INS_PAGEBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_PAGE;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsPage(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PAGE);
}

void ZDProcessGraphModelControllerBP::OnInsDoor()
{
    InsertDoorSymbol();

    // Change the cursor
    SetCustomCursor(IDC_INS_DOORBP);
    m_CurrentCursor = IDC_INS_DOORBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_DOOR;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsDoor(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DOOR);
}

void ZDProcessGraphModelControllerBP::OnInsStop()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPStopSymbol* pSymbol = new ZBBPStopSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_STOPBP);
    m_CurrentCursor = IDC_INS_STOPBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_STOP;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsStop(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_STOP);
}

void ZDProcessGraphModelControllerBP::OnInsStart()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPStartSymbol* pSymbol = new ZBBPStartSymbol();
    pSymbol->Create();
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_STARTBP);
    m_CurrentCursor = IDC_INS_STARTBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_START;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsStart(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_START);
}

// Crée un symbole de type livrable, et l'insère dans la liste des symboles.
void ZDProcessGraphModelControllerBP::OnInsDeliverable()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    // Crée l'objet livrable
    ZBDeliverableLinkSymbol* pLinkComp = new ZBDeliverableLinkSymbol();
    pLinkComp->CreateOrthogonal();    // Crée le "squelette" et les propriétés graphiques du symbole.
    OnInsertLink(pLinkComp);

    // Change the cursor
    SetCustomCursor(IDC_INS_DELIVERABLEBP);
    m_CurrentCursor = IDC_INS_DELIVERABLEBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_DELIVERABLE;
}

void ZDProcessGraphModelControllerBP::OnUpdateInsDeliverable(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DELIVERABLE);
}

// JMR-MODIF - Le 19 octobre 2005 - Cette fonction permet l'ajout d'un symbole de type alerte.
void ZDProcessGraphModelControllerBP::OnInsAlert()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_ALERT);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_ALERTBP);
    m_CurrentCursor = IDC_INS_ALERTBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_ALERT;
}

// JMR-MODIF - Le 19 octobre 2005 - Cette fonction permet de mettre à jour la commande du symbole de type alerte.
void ZDProcessGraphModelControllerBP::OnUpdateInsAlert(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_ALERT);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Document.
void ZDProcessGraphModelControllerBP::OnInsDocument()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_DOCUMENT);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_DOCUMENTBP);
    m_CurrentCursor = IDC_INS_DOCUMENTBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_DOCUMENT;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Document.
void ZDProcessGraphModelControllerBP::OnUpdateInsDocument(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DOCUMENT);
}

// JMR-MODIF - Le 19 octobre 2005 - Cette fonction permet l'ajout d'un symbole de type indicateur.
void ZDProcessGraphModelControllerBP::OnInsIndicator()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_INDICATOR);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_INDICATORBP);
    m_CurrentCursor = IDC_INS_INDICATORBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_INDICATOR;
}

// JMR-MODIF - Le 19 octobre 2005 - Cette fonction permet de mettre à jour la commande du symbole de type indicateur.
void ZDProcessGraphModelControllerBP::OnUpdateInsIndicator(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_INDICATOR);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Qualité.
void ZDProcessGraphModelControllerBP::OnInsQuality()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_QUALITY);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_QUALITYBP);
    m_CurrentCursor = IDC_INS_QUALITYBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_QUALITY;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Qualité.
void ZDProcessGraphModelControllerBP::OnUpdateInsQuality(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_QUALITY);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Délai.
void ZDProcessGraphModelControllerBP::OnInsDelay()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_DELAY);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_DELAYBP);
    m_CurrentCursor = IDC_INS_DELAYBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_DELAY;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Délai.
void ZDProcessGraphModelControllerBP::OnUpdateInsDelay(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DELAY);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type En cours.
void ZDProcessGraphModelControllerBP::OnInsInProcess()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_IN_PROCESS);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_IN_PROCESSBP);
    m_CurrentCursor = IDC_INS_IN_PROCESSBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_IN_PROCESS;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type En cours.
void ZDProcessGraphModelControllerBP::OnUpdateInsInProcess(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_IN_PROCESS);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Non validé.
void ZDProcessGraphModelControllerBP::OnInsNotValidated()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_NOT_VALIDATED);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_NOT_VALIDATEDBP);
    m_CurrentCursor = IDC_INS_NOT_VALIDATEDBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_NOT_VALIDATED;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Non validé.
void ZDProcessGraphModelControllerBP::OnUpdateInsNotValidated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_NOT_VALIDATED);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Validé.
void ZDProcessGraphModelControllerBP::OnInsValidated()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_VALIDATED);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_VALIDATEDBP);
    m_CurrentCursor = IDC_INS_VALIDATEDBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_VALIDATED;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Validé.
void ZDProcessGraphModelControllerBP::OnUpdateInsValidated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_VALIDATED);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Risque.
void ZDProcessGraphModelControllerBP::OnInsRisk()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_RISK);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_RISKBP);
    m_CurrentCursor = IDC_INS_RISKBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_RISK;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Risque.
void ZDProcessGraphModelControllerBP::OnUpdateInsRisk(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_RISK);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type Incident.
void ZDProcessGraphModelControllerBP::OnInsIncident()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_INCIDENT);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_INCIDENTBP);
    m_CurrentCursor = IDC_INS_INCIDENTBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_INCIDENT;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type Incident.
void ZDProcessGraphModelControllerBP::OnUpdateInsIncident(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_INCIDENT);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type CRI.
void ZDProcessGraphModelControllerBP::OnInsCRI()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_CRI);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_CRIBP);
    m_CurrentCursor = IDC_INS_CRIBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_CRI;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type CRI.
void ZDProcessGraphModelControllerBP::OnUpdateInsCRI(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_CRI);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type CRE.
void ZDProcessGraphModelControllerBP::OnInsCRE()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_CRE);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_CREBP);
    m_CurrentCursor = IDC_INS_CREBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_CRE;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type CRE.
void ZDProcessGraphModelControllerBP::OnUpdateInsCRE(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_CRE);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type CRO.
void ZDProcessGraphModelControllerBP::OnInsCRO()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_CRO);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_CROBP);
    m_CurrentCursor = IDC_INS_CROBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_CRO;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type CRO.
void ZDProcessGraphModelControllerBP::OnUpdateInsCRO(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_CRO);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type OPAP1.
void ZDProcessGraphModelControllerBP::OnInsOPAP1()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_OPAP1);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_OPAP1BP);
    m_CurrentCursor = IDC_INS_OPAP1BP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_OPAP1;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type OPAP1.
void ZDProcessGraphModelControllerBP::OnUpdateInsOPAP1(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_OPAP1);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type OPAP2.
void ZDProcessGraphModelControllerBP::OnInsOPAP2()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_OPAP2);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_OPAP2BP);
    m_CurrentCursor = IDC_INS_OPAP2BP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_OPAP2;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type OPAP2.
void ZDProcessGraphModelControllerBP::OnUpdateInsOPAP2(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_OPAP2);
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet l'ajout d'un symbole de type OPAP3.
void ZDProcessGraphModelControllerBP::OnInsOPAP3()
{
    ClearSelectionToSet();

    // Set flag for creation
    m_NewSymbolCreated = true;

    ZBBPGenericSymbol* pSymbol = new ZBBPGenericSymbol();
    pSymbol->Create(IDR_OPAP3);
    OnInsertSymbol(pSymbol);

    // Change the cursor
    SetCustomCursor(IDC_INS_OPAP3BP);
    m_CurrentCursor = IDC_INS_OPAP3BP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_OPAP3;
}

// JMR-MODIF - Le 4 janvier 2006 - Cette fonction permet de mettre à jour la commande du symbole de type OPAP3.
void ZDProcessGraphModelControllerBP::OnUpdateInsOPAP3(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_OPAP3);
}

// JMR-MODIF - Le 4 avril 2006 - Cette fonction permet l'ajout d'un symbole de type zone de texte.
void ZDProcessGraphModelControllerBP::OnInsTextZone()
{
    // Crée un point d'ancrage par défaut
    CPoint ptLog;

    ptLog.x = 0;
    ptLog.y = 0;

    // Obtient le DC client
    CClientDC dc(GetWnd());
    GetCanvasVp()->PrepareDC(&dc, FALSE);

    ClearSelectionToSet();

    // Pose le drapeau de création
    m_NewSymbolCreated = true;

    ZBBPTextZone* pTextZone = new ZBBPTextZone();
    pTextZone->Create(ptLog, &dc);
    OnInsertSymbol(pTextZone);

    // Change the cursor
    SetCustomCursor(IDC_INS_TEXTZONEBP);
    m_CurrentCursor = IDC_INS_TEXTZONEBP;

    // Sets the current command ID
    m_CurrentCommandID = ID_INS_BP_TEXTZONE;
}

// JMR-MODIF - Le 22 mars 2006 - Cette fonction permet de mettre à jour la commande du symbole de type zone de texte.
void ZDProcessGraphModelControllerBP::OnUpdateInsTextZone(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_TEXTZONE);
}

void ZDProcessGraphModelControllerBP::OnShowProcessPreview()
{
    CODComponent* pComp = NULL;

    AssignSymbolHit();

    if (m_pCompHit != NULL && m_pCompHit->IsKindOf(RUNTIME_CLASS(ZBBPProcessSymbol)))
    {
        ZBBPProcessSymbol*    pProcess = (ZBBPProcessSymbol*)m_pCompHit;

        pProcess->SetDisplayPreview(!pProcess->GetDisplayPreview());

        // Update the symbol
        CODComponentSet CompSet;
        CompSet.Add(m_pSymbolHit);
        GetVp()->DrawComponents(&CompSet);

        // Set flag for modification
        if (GetDocument())
        {
            GetDocument()->SetModifiedFlag(TRUE);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateShowProcessPreview(CCmdUI* pCmdUI)
{
    CODComponent* pComp = NULL;

    AssignSymbolHit();

    if (m_pCompHit != NULL && m_pCompHit->IsKindOf(RUNTIME_CLASS(ZBBPProcessSymbol)))
    {
        ZBBPProcessSymbol* pProcess = (ZBBPProcessSymbol*)m_pCompHit;

        pCmdUI->Enable(TRUE);
        pCmdUI->SetCheck(pProcess->GetDisplayPreview());
    }
    else pCmdUI->Enable(FALSE);
}

void ZDProcessGraphModelControllerBP::OnOdMeasurements()
{
    // RS-MODIF 14.12.04 test for page size
    /*CSize test;
    test.cx = 793;
    test.cy = 1118;
    GetCanvasModel()->SetSize(test);*/

    // Call the base class
    CODController::OnMeasurements();

    if (!GetDocument() || !GetCanvasVp()->GetRuler())
    {
        return;
    }

    // Set flag for modification
    GetDocument()->SetModifiedFlag(TRUE);

    if (ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        ((ZDProcessGraphModelDoc*)GetDocument())->SetPageUnits(*(GetCanvasVp()->GetRuler()));
    }
}

void ZDProcessGraphModelControllerBP::OnLinktoFilePackage()
{
    if (m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol))
    {
        ZBBPPackageSymbol* pPackage = (ZBBPPackageSymbol*)m_pCompHit;

        CString title;
        VERIFY(title.LoadString(IDS_SELECTUNITIMPORT_TITLE));

        CString    File = g_SearchAllModelExtension;

        // set the first file filter
        CString strFilter = _T("Modèle (*.mlf)");
        strFilter += (char)'\0';        // next string please
        strFilter += File;
        strFilter += (char)'\0';        // last string

        // append the "*.*" all files filter
        CString allFilter;
        VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
        strFilter += allFilter;
        strFilter += (char)'\0';        // next string please
        strFilter += _T("*.*");
        strFilter += (char)'\0';        // last string

        PSS_FileDialog fileDialog(IDS_SELECTUNIT_FILEDLGTITLE, strFilter, 2);

        if (fileDialog.DoModal() == IDCANCEL)
        {
            return;
        }

        // Check if it is a unit
        PSS_FolderStamp FolderStamp;

        if (!FolderStamp.ReadFromFile(fileDialog.GetFileName()))
        {
            // Error message
            return;
        }

        // Set the file name
        pPackage->SetFileNameLinkedTo(fileDialog.GetFileName());

        // Update the symbol
        CODComponentSet CompSet;
        CompSet.Add(m_pSymbolHit);
        GetVp()->DrawComponents(&CompSet);

        // Set flag for modification
        if (GetDocument())
        {
            GetDocument()->SetModifiedFlag(TRUE);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUnlinkFromFilePackage()
{
    if (m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol))
    {
        ZBBPPackageSymbol* pPackage = (ZBBPPackageSymbol*)m_pCompHit;

        if (pPackage->IsLinkedToFileName() && pPackage->IsLoaded())
        {
            // Unload the package
            pPackage->UnloadPackage();
        }

        // Then clear the link
        pPackage->ClearLinkedToFileName();

        // Update the symbol
        CODComponentSet CompSet;
        CompSet.Add(m_pSymbolHit);
        GetVp()->DrawComponents(&CompSet);

        // Set flag for modification
        if (GetDocument())
        {
            GetDocument()->SetModifiedFlag(TRUE);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateUnlinkFromFilePackage(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol) &&
        ((ZBBPPackageSymbol*)m_pSymbolHit)->IsLinkedToFileName());
}

void ZDProcessGraphModelControllerBP::OnLoadPackage()
{
    if (m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol))
    {
        ZBBPPackageSymbol* pPackage = (ZBBPPackageSymbol*)m_pCompHit;

        if (pPackage->IsLinkedToFileName() && pPackage->IsLoaded())
        {
            // Unload the package first
            pPackage->UnloadPackage();
        }

        if (pPackage->IsLinkedToFileName() && !pPackage->IsLoaded())
        {
            ZIProcessGraphModelView*    pView = GetView();

            if (GetDocument() && GetDocument()->GetDocTemplate() &&
                ISA(GetDocument()->GetDocTemplate(), PSS_ProcessModelDocTmpl))
            {
                if (!pPackage->LoadPackage((PSS_ProcessModelDocTmpl*)GetDocument()->GetDocTemplate(), GetModel()))
                {
                    // Error
                    return;
                }
            }

            // Update the symbol
            CODComponentSet CompSet;
            CompSet.Add(m_pSymbolHit);
            GetVp()->DrawComponents(&CompSet);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateLoadPackage(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    pCmdUI->Enable(m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol) &&
        ((ZBBPPackageSymbol*)m_pSymbolHit)->IsLinkedToFileName());
}

void ZDProcessGraphModelControllerBP::OnUnloadPackage()
{
    AssignSymbolHit();

    if (m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol))
    {
        ZBBPPackageSymbol* pPackage = (ZBBPPackageSymbol*)m_pCompHit;

        if (pPackage->IsLinkedToFileName() && pPackage->IsLoaded())
        {
            // Unload the package first
            pPackage->UnloadPackage();

            // Update the symbol
            CODComponentSet CompSet;
            CompSet.Add(m_pSymbolHit);
            GetVp()->DrawComponents(&CompSet);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateUnloadPackage(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    pCmdUI->Enable(m_pSymbolHit && ISA(m_pSymbolHit, ZBBPPackageSymbol) &&
        ((ZBBPPackageSymbol*)m_pSymbolHit)->IsLinkedToFileName() &&
                   ((ZBBPPackageSymbol*)m_pSymbolHit)->IsLoaded());
}

void ZDProcessGraphModelControllerBP::OnViewComponents()
{
    CODController::OnViewComponents();
}

bool ZDProcessGraphModelControllerBP::CanDuplicateObject(CODComponentSet* pCompSet)
{
    CODComponentIterator i(pCompSet);
    CODComponent* pComp;

    // Check if process or package have been selected
    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
    {
        if (pComp && (ISA(pComp, ZBBPProcessSymbol) || ISA(pComp, ZBBPPackageSymbol)))
        {
            return false;
        }
    }

    return true;
}

void ZDProcessGraphModelControllerBP::OnSymbolDuplicated(CODComponentSet* pCompSet)
{
    // Call the base class method to duplicate simple object
    ZDProcessGraphModelController::OnSymbolDuplicated(pCompSet);

    // Run through added elements and change their names.
    // If symbols have child components, then asks the user to duplicate sub-components
    // Notify observers for all added symbols
    CODComponentIterator i(pCompSet);
    CODComponent* pComp;

    int iPos = 0;
    int CountCopySet = m_setCopy.GetSize();

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext(), ++iPos)
    {
        if (pComp && ISA(pComp, ZBBPProcessSymbol))
        {
            DoDuplicateProcess(reinterpret_cast<ZDProcessGraphModelMdl*>(dynamic_cast<ZBBPProcessSymbol*>(pComp)->GetChildModel()));
        }

        // If a door symbol, remove the process pointed to
        if (ISA(pComp, ZBBPDoorSymbol))
        {
            dynamic_cast<ZBBPDoorSymbol*>(pComp)->RemoveTwinDoorSymbol(false);
        }

        // If a page symbol, remove the page pointed to
        if (ISA(pComp, ZBBPPageSymbol))
        {
            dynamic_cast<ZBBPPageSymbol*>(pComp)->RemoveTwinPageSymbol(false);
        }
    }
}

void ZDProcessGraphModelControllerBP::DoDuplicateProcess(ZDProcessGraphModelMdl* pModel)
{
    if (pModel == NULL)
    {
        return;
    }

    // Run through all pages if there are
    if (pModel->GetPageSet() != NULL)
    {
        ZBProcessGraphPageIterator i(pModel->GetPageSet());

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not check for itself
            if (pPage->GetpModel() && pPage->GetpModel() != pModel)
            {
                DoDuplicateProcess(pPage->GetpModel());
            }
        }
    }

    // Process the model components
    CODComponentSet* pSet = pModel->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If we found the same reference number, return true
        if (ISA(pComp, ZBSymbol))
        {
            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            int RefNumber = GetRootModel()->GetNextAvailableReferenceNumber();

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
//            ( (ZBSymbol*)pComp )->SetSymbolReferenceNumber( GetRootModel()->GetNextAvailableReferenceNumber() );
            ((ZBSymbol*)pComp)->SetSymbolReferenceNumber(RefNumber);

            // Retreive the next available name
            ZUBuildSymbolNewName BuildNewName(((ZBSymbol*)pComp)->GetSymbolName());

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            ((ZBSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel(),
                                                                                      RefNumber));
        }
        // If we found the same reference number, return true
        else if (ISA(pComp, ZBLinkSymbol))
        {
            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            int RefNumber = GetRootModel()->GetNextAvailableReferenceNumber();

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
//            ( (ZBLinkSymbol*)pComp )->SetSymbolReferenceNumber( GetRootModel()->GetNextAvailableReferenceNumber() );
            ((ZBLinkSymbol*)pComp)->SetSymbolReferenceNumber(RefNumber);

            // Retreive the next available name
            ZUBuildSymbolNewName BuildNewName(((ZBLinkSymbol*)pComp)->GetSymbolName());

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            ((ZBLinkSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel(),
                                                                                          RefNumber));
        }

        if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            DoDuplicateProcess(reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel()));
        }
    }
}

void ZDProcessGraphModelControllerBP::OnCheckModel()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc* pDoc = (ZDProcessGraphModelDoc*)GetDocument();

    // JMR-MODIF - Le 9 octobre 2006 - Ajout du test pour vérifier que le pointeur pDoc ne soit pas vide.
    if (pDoc != NULL)
    {
        // JMR-MODIF - Le 5 novembre 2006 - Ajout de la variable ModelIsClean.
        BOOL ModelIsClean = FALSE;

        // ****************************************************************************************
        // JMR-MODIF - Le 5 novembre 2006 - Teste la validité des symboles contenus dans le modèle.
        if (pDoc->GetModel() != NULL)
        {
            ZUDeleteCorruptedSymbols VerifySymbols;

            VerifySymbols.CheckModel(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel()));

            if (VerifySymbols.GetCorruptedSymbolList()->GetCount() > 0)
            {
                DeleteComponents(VerifySymbols.GetCorruptedSymbolList());
                pDoc->SetModifiedFlag();
                ModelIsClean = TRUE;
            }
        }
        // ****************************************************************************************

        // Check if consistency is set
        if (pDoc->GetCheckConsistency())
        {
            // Asks to activate the output symbol log tab
            PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGSYMBOL_TAB);
            pDoc->NotifyAllObservers(&msg);

            CWaitCursor wait;

            // TODO get the output view
            pDoc->CheckModelWorkflow(ModelIsClean);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateCheckModel(CCmdUI* pCmdUI)
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(((ZDProcessGraphModelDoc*)GetDocument())->GetCheckConsistency());
}

void ZDProcessGraphModelControllerBP::OnRecalculateModelParameters()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc* pDoc = (ZDProcessGraphModelDoc*)GetDocument();

    // Check if cost simulation is set
    if (pDoc->GetIntegrateCostSimulation())
    {
        // Asks to activate the output analyzer log tab
        PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGANALYZER_TAB);
        pDoc->NotifyAllObservers(&msg);

        CWaitCursor wait;

        // First unselect all components
        UnselectAllComponents();

        // Initialize the calculator
        ZBSesterceRecalculationAutomate Recalc(GetRootModel(), pDoc->GetAnalyzerOutputLog());
        Recalc.SetMaxWaitingForOtherLinks(1000);
        Recalc.SetMaxPaused(1000);
        Recalc.SetMaxLoop(2000);
        Recalc.Start(1);

        // Set the modified flag
        pDoc->SetModifiedFlag();

        // Refresh symbol attributes
        if (GetRootModel())
        {
            GetRootModel()->RefreshSymbolAttributes(true);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateRecalculateModelParameters(CCmdUI* pCmdUI)
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(((ZDProcessGraphModelDoc*)GetDocument())->GetIntegrateCostSimulation());
}

void ZDProcessGraphModelControllerBP::OnRecalculateModelDurations()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    AssignSymbolHit();
    ASSERT(m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBBPStartSymbol));

    ZBSymbol* pSymbol = dynamic_cast<ZBBPStartSymbol*>(m_pSymbolHit);

    // Assign casted pointer
    ZDProcessGraphModelDoc* pDoc = (ZDProcessGraphModelDoc*)GetDocument();

    // Check if cost simulation is set
    if (pDoc->GetIntegrateCostSimulation())
    {
        // Asks to activate the output analyzer log tab
        PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGANALYZER_TAB);
        pDoc->NotifyAllObservers(&msg);

        CWaitCursor wait;

        // First unselect all components
        UnselectAllComponents();

        // Initialize the calculator
        ZBDurationRecalculationAutomate Recalc(pSymbol, GetRootModel(), pDoc->GetAnalyzerOutputLog());
        Recalc.SetMaxWaitingForOtherLinks(1000);
        Recalc.SetMaxPaused(1000);
        Recalc.SetMaxLoop(2000);
        Recalc.SetAllowUncompletePath(); // Sets the allow uncomplete path
        Recalc.Start(1);

        // Launch the second pass
        Recalc.IncrementPass();
        Recalc.Start(1);

        // Set the modified flag
        pDoc->SetModifiedFlag();

        // Refresh symbol attributes
        if (GetRootModel())
        {
            GetRootModel()->RefreshSymbolAttributes(true);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateRecalculateModelDurations(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (GetDocument() &&
        ISA(GetDocument(), ZDProcessGraphModelDoc) &&
        ((ZDProcessGraphModelDoc*)GetDocument())->GetIntegrateCostSimulation() &&
        m_pSymbolHit != NULL &&
        ISA(m_pSymbolHit, ZBBPStartSymbol))
    {
        bEnable = TRUE;
    }

    pCmdUI->Enable(bEnable);
}

// JMR-MODIF - Le 21 juillet 2007 - Cette fonction permets de démarrer la calculation des risques.
void ZDProcessGraphModelControllerBP::OnCalculateRisks()
{
    CODModel*    pModel = GetRootModel();
    CString        CurrencySymbol = PSS_Global::GetLocaleCurrency();

    if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
        {
            // Retreive the model's currency symbol
            CurrencySymbol = dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
        }
    }

    ZVRiskCalculateParametersDlg riskParametersDlg(PSS_Application::Instance()->GetMainForm()->GetApplicationIniFileName(),
                                                   CurrencySymbol);

    if (riskParametersDlg.DoModal() == IDOK)
    {
        // assign casted pointer
        ZDProcessGraphModelDoc* pDoc = (ZDProcessGraphModelDoc*)GetDocument();

        if (pDoc)
        {
            ZUCalculateRisks calculateRisks(riskParametersDlg.GetOrangeSeverityLevel(),
                                            riskParametersDlg.GetRedSeverityLevel(),
                                            riskParametersDlg.GetOrangeUE(),
                                            riskParametersDlg.GetRedUE(),
                                            riskParametersDlg.GetOrangePOA(),
                                            riskParametersDlg.GetRedPOA(),
                                            riskParametersDlg.IsOrangeActionEnabled(),
                                            riskParametersDlg.IsOrangeNoActionEnabled(),
                                            riskParametersDlg.IsRedActionEnabled(),
                                            riskParametersDlg.IsRedNoActionEnabled(),
                                            riskParametersDlg.IsDefaultColorsEnabled(),
                                            GetRootModel(),
                                            pDoc->GetModelOutputLog());

            calculateRisks.Calculate(*GetRootModel());
        }
    }
}

// JMR-MODIF - Le 21 juillet 2007 - Cette fonction mets à jour l'état de la commande de calculation des risques.
void ZDProcessGraphModelControllerBP::OnUpdateCalculateRisks(CCmdUI* pCmdUI)
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(TRUE);
}

///////////////////////////////////////////////////////////////////////////
// Simulation command messages

void ZDProcessGraphModelControllerBP::OnPlaySimulation()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = (ZDProcessGraphModelDoc*)GetDocument();
}

void ZDProcessGraphModelControllerBP::OnUpdatePlaySimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelControllerBP::OnPauseSimulation()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = (ZDProcessGraphModelDoc*)GetDocument();
}

void ZDProcessGraphModelControllerBP::OnUpdatePauseSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelControllerBP::OnStopSimulation()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = (ZDProcessGraphModelDoc*)GetDocument();
}

void ZDProcessGraphModelControllerBP::OnUpdateStopSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelControllerBP::OnRewSimulation()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = (ZDProcessGraphModelDoc*)GetDocument();
}

void ZDProcessGraphModelControllerBP::OnUpdateRewSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelControllerBP::OnFwdSimulation()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = (ZDProcessGraphModelDoc*)GetDocument();
}

void ZDProcessGraphModelControllerBP::OnUpdateFwdSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelControllerBP::OnShowInputAttributes()
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = dynamic_cast<ZDProcessGraphModelDoc*>(GetDocument());

    ZVInputAttributesSelectionDlg dlg(dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetInputAttributes(),
                                      pDoc->GetDynamicPropertiesManager());

    dlg.DoModal();
}

void ZDProcessGraphModelControllerBP::OnUpdateShowInputAttributes(CCmdUI* pCmdUI)
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    // Assign casted pointer
    ZDProcessGraphModelDoc*    pDoc = dynamic_cast<ZDProcessGraphModelDoc*>(GetDocument());

    pCmdUI->Enable(pDoc->GetDynamicPropertiesManager() &&
                   pDoc->GetModel() &&
                   ISA(pDoc->GetModel(), ZDProcessGraphModelMdlBP) &&
                   dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetInputAttributes());
}

///////////////////////////////////////////////////////////////////////////
// Show hide toolbars functions

void ZDProcessGraphModelControllerBP::OnViewModelGenToolbar()
{
    if (!m_pwndModelGenerationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());
        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();
        m_pwndModelGenerationBar = pMgr->ToolBarFromID(_GenerationToolBarID);
    }

    if (m_pwndModelGenerationBar)
    {
        ((CFrameWnd*)AfxGetMainWnd())->
            ShowControlBar(m_pwndModelGenerationBar,
            (m_pwndModelGenerationBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateViewModelGenToolbar(CCmdUI* pCmdUI)
{
    if (!m_pwndModelGenerationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());
        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();
        m_pwndModelisationBar = pMgr->ToolBarFromID(_GenerationToolBarID);
    }

    if (m_pwndModelGenerationBar)
    {
        pCmdUI->SetCheck((m_pwndModelGenerationBar->GetStyle() & WS_VISIBLE) != 0);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void ZDProcessGraphModelControllerBP::OnViewModelToolbar()
{
    if (!m_pwndModelisationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());
        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();
        m_pwndModelisationBar = pMgr->ToolBarFromID(_ModelisationToolBarID);
    }

    if (m_pwndModelisationBar)
    {
        ((CFrameWnd*)AfxGetMainWnd())->
            ShowControlBar(m_pwndModelisationBar, (m_pwndModelisationBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
    }
}

void ZDProcessGraphModelControllerBP::OnUpdateViewModelToolbar(CCmdUI* pCmdUI)
{
    if (!m_pwndModelisationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());
        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();
        m_pwndModelisationBar = pMgr->ToolBarFromID(_ModelisationToolBarID);
    }

    if (m_pwndModelisationBar)
    {
        pCmdUI->SetCheck((m_pwndModelisationBar->GetStyle() & WS_VISIBLE) != 0);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void ZDProcessGraphModelControllerBP::OnInsertPage()
{
    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if (!pRoot)
    {
        return;
    }

    // Filter object classes
    ZBRuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(ZBBPPageSymbol));
    rtClasses.Add(RUNTIME_CLASS(ZBBPProcessSymbol));

    ZVInsertModelNewPageDlg Dlg(pRoot,
                                pRoot->GetValidNextPageName(),
                                pRoot->GetExistingPageNameArray(),
                                &rtClasses);

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphModelMdl*    pModel = pRoot->CreateEmptyModel(Dlg.GetPageName(), Dlg.GetParentModel());
        ZDProcessGraphPage*        pPage = pRoot->CreateNewPage(pModel, Dlg.GetPageName(), Dlg.GetParentModel());
        BrowseModel(pModel, Dlg.GetParentModel());

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelControllerBP::OnRenamePage()
{
    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if (!pRoot)
    {
        return;
    }

    CString NewPage = pRoot->GetValidNextPageName();

    // Filter object classes
    ZBRuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(ZBBPPageSymbol));
    rtClasses.Add(RUNTIME_CLASS(ZBBPProcessSymbol));

    ZVRenameModelPageDlg Dlg(pRoot, pRoot->GetExistingPageNameArray(), NULL, &rtClasses);

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphPage* pPage = Dlg.GetSelectedPage();

        if (pPage)
        {
            // Keeps the old page name
            CString OldPageName = pPage->GetPageName();

            // Rename the page
            pPage->SetPageName(Dlg.GetPageName());

            // Advise the owner model of page changes
            pRoot->OnPageNameChanged(pPage, OldPageName);
        }

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelControllerBP::OnRenameCurrentPage()
{
    /********************************************************************************************************
    // JMR-MODIF - Le 3 avril 2006 - Le changement de boîte de dialogue implique la réecritue de la fonction.

    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if ( !pRoot )
    {
        return;
    }

    CString NewPage = pRoot->GetValidNextPageName();

    // Find the current page
    ZDProcessGraphPage* pCurrentPage = pRoot->FindModelPage( GetModel(), true );

    if ( !pCurrentPage )
    {
        return;
    }

    // Keeps the old page name
    CString OldPageName = pCurrentPage->GetPageName();

    // Filter object classes
    ZBRuntimeClassSet rtClasses;
    rtClasses.Add( RUNTIME_CLASS( ZBBPPageSymbol ) );
    rtClasses.Add( RUNTIME_CLASS( ZBBPProcessSymbol ) );

    ZVRenameModelPageDlg Dlg( pRoot, pRoot->GetExistingPageNameArray(), pCurrentPage, &rtClasses );

    if ( Dlg.DoModal() == IDOK )
    {
        ZDProcessGraphPage* pPage = Dlg.GetSelectedPage();

        if ( pPage )
        {
            pPage->SetPageName( Dlg.GetPageName() );

            // Advise the owner model of page changes
            pRoot->OnPageNameChanged( pPage, OldPageName );

            // Force the refresh of the active window title
            if ( AfxGetMainWnd() &&
                 ISA( AfxGetMainWnd(), CFrameWnd ) &&
                 dynamic_cast<CFrameWnd*>( AfxGetMainWnd() )->GetActiveFrame() )
            {
                dynamic_cast<CFrameWnd*>( AfxGetMainWnd() )->GetActiveFrame()->OnUpdateFrameTitle( TRUE );
            }
        }

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants( UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg );

        // Set flag for modification
        GetDocument()->SetModifiedFlag( TRUE );
    }
    ********************************************************************************************************/

    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if (!pRoot)
    {
        return;
    }

    CString NewPage = pRoot->GetValidNextPageName();

    // Find the current page
    ZDProcessGraphPage* pCurrentPage = pRoot->FindModelPage(GetModel(), true);

    if (!pCurrentPage)
    {
        return;
    }

    // Keeps the old page name
    CString OldPageName = pCurrentPage->GetPageName();

    ZVRenameModelPageInTreeDlg Dlg(NewPage, pRoot->GetExistingPageNameArray());

    if (Dlg.DoModal() == IDOK)
    {
        if (pCurrentPage != NULL)
        {
            pCurrentPage->SetPageName(Dlg.GetPageName());

            // Advise the owner model of page changes
            pRoot->OnPageNameChanged(pCurrentPage, OldPageName);

            // Force the refresh of the active window title
            if (AfxGetMainWnd() &&
                ISA(AfxGetMainWnd(), CFrameWnd) &&
                dynamic_cast<CFrameWnd*>(AfxGetMainWnd())->GetActiveFrame())
            {
                dynamic_cast<CFrameWnd*>(AfxGetMainWnd())->GetActiveFrame()->OnUpdateFrameTitle(TRUE);
            }
        }

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelControllerBP::OnDeletePage()
{
    if (!GetModel()->GetRoot())
    {
        return;
    }

    // filter object classes
    ZBRuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(ZBBPPageSymbol));
    rtClasses.Add(RUNTIME_CLASS(ZBBPProcessSymbol));

    ZVDeleteModelPageDlg Dlg(GetModel()->GetRoot(), &rtClasses);

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphPage* pPage = Dlg.GetSelectedPage();

        if (pPage)
        {
            // First, move to the root model
            BrowseModel(GetModel()->GetRoot(), GetModel()->GetRoot()->GetParent());

            // Delete the page and its associated model
            GetModel()->GetRoot()->DeletePage(pPage->GetPageName(), true);

            // Build the message
            ZBDocObserverMsg    DocMsg;
            AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

            // Set flag for modification
            GetDocument()->SetModifiedFlag(TRUE);
        }
    }
}

void ZDProcessGraphModelControllerBP::OnPostCutPasteOperation(CODComponentSet* pCompSet)
{
    CODComponentIterator i(pCompSet);

    // Remove the reference to the twin for door symbol from the set
    CODComponent* pComp;

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
    {
        if (ISA(pComp, ZBBPDoorSymbol))
        {
            ZBBPDoorSymbol* pDoor = (ZBBPDoorSymbol*)pComp;
            pDoor->SetTwinDoorSymbol(NULL);
            pDoor->SetTwinDoorReferenceNumber(-1);
        }
    }
}

// JMR-MODIF - Le 3 mai 2006 - Création du pinceau de style, mise en fonction et adaptation du code ci-dessous.
void ZDProcessGraphModelControllerBP::OnFormatPainter()
{
    if (!m_IsInFormatPainter)
    {
        // Premier clic sur le bouton : On change d'icône, et on copie la sélection.
        m_state = OD_SYMBOL_READY;
        m_CurrentCursor = IDC_FORMATPAINTER;

        SetCustomCursor(IDC_FORMATPAINTER);

        AssignSymbolHit();
        m_pFormatPainterSymbol = m_pSymbolHit;
        m_IsInFormatPainter = true;
    }
}

// JMR-MODIF - Le 2 septembre 2006 - Fonction surchargée OnProperties pour mettre à jour le format des portes/pages.
void ZDProcessGraphModelControllerBP::OnProperties()
{
    // Appel de la fonction enfant OnProperties.
    CODController::OnProperties();

    if (m_LastSelectedElement != NULL)
    {
        if (ISA(m_LastSelectedElement, ZBSymbol))
        {
            ZBSymbol* m_Symbol = reinterpret_cast<ZBSymbol*>(m_LastSelectedElement);

            if (m_Symbol != NULL)
            {
                m_Symbol->DuplicateStyleOnTwinSymbol();
            }
        }
    }
}

// JMR-MODIF - Le 3 mai 2006 - Création du pinceau de style, mise en fonction et adaptation du code ci-dessous.
void ZDProcessGraphModelControllerBP::OnUpdateFormatPainter(CCmdUI* pCmdUI)
{
    // Check if symbol clicked allow the format painter
    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        pCmdUI->Enable(GetSelection()->GetSize() == 1 &&
                       dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsGeneric() == FALSE);
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        pCmdUI->Enable(GetSelection()->GetSize() == 1);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }

    pCmdUI->SetCheck((m_IsInFormatPainter) ? TRUE : FALSE);
}
