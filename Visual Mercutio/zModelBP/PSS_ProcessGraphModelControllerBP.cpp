/****************************************************************************
 * ==> PSS_ProcessGraphModelControllerBP -----------------------------------*
 ****************************************************************************
 * Description : Provides a graphic model controller for banking processes  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelControllerBP.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_FloatingToolBar.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_ProcessGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\PSS_BuildSymbolNewName.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModel\PSS_InsertModelNewPageDlg.h"
#include "zModel\PSS_RenameModelPageDlg.h"
#include "zModel\PSS_RenameModelPageInTreeDlg.h"
#include "zModel\PSS_DeleteModelPageDlg.h"
#include "zModel\PSS_UnitObserverMsg.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_PackageSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zModelBP\PSS_GenericSymbolBP.h"
#include "zModelBP\PSS_TextZoneBP.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_DeleteCorruptedSymbols.h"
#include "PSS_SesterceRecalculationAutomate.h"
#include "PSS_DurationRecalculationAutomate.h"
#include "PSS_InputAttributesSelectionDlg.h"
#include "PSS_RiskCalculateParametersDlg.h"
#include "PSS_CalculateRisks.h"

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

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
SECCustomToolBar* PSS_ProcessGraphModelControllerBP::m_pWndModelisationBar    = NULL;
SECCustomToolBar* PSS_ProcessGraphModelControllerBP::m_pWndModelGenerationBar = NULL;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessGraphModelControllerBP, PSS_ProcessGraphModelController)
    //{{AFX_MSG_MAP(PSS_ProcessGraphModelControllerBP)
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
    ON_UPDATE_COMMAND_UI(ID_VIEW_MODELGENTOOLBAR, OnUpdateViewModelGenToolbar)
    ON_COMMAND(ID_VIEW_MODELTOOLBAR, OnViewModelToolbar)
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
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelControllerBP
//---------------------------------------------------------------------------
PSS_ProcessGraphModelControllerBP::PSS_ProcessGraphModelControllerBP(PSS_ProcessGraphModelViewport* pViewport) :
    PSS_ProcessGraphModelController(pViewport)
{
    // load the component main menus
    m_SymbolRightMainMenu.LoadMenu(IDR_SYMBOL_RIGHTMENU_BP);
    m_SymbolRefRightMainMenu.LoadMenu(IDR_SYMBOL_REF_RIGHTMENU_BP);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelControllerBP::~PSS_ProcessGraphModelControllerBP()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::InsertPageSymbol()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_PageSymbolBP> pSymbol(new PSS_PageSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::InsertDoorSymbol()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_DoorSymbolBP> pSymbol(new PSS_DoorSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelControllerBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // Call the base class
    return PSS_ProcessGraphModelController::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelControllerBP::DropItem(CObject* pObj, const CPoint& point)
{
    // Call the base class
    return PSS_ProcessGraphModelController::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelControllerBP::AcceptDropItemToModel(CObject* pObj, const CPoint& point)
{
    // Call the base class
    return PSS_ProcessGraphModelController::AcceptDropItemToModel(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelControllerBP::DropItemToModel(CObject* pObj, const CPoint& point)
{
    // Call the base class
    return PSS_ProcessGraphModelController::DropItemToModel(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelControllerBP::CanDuplicateObject(CODComponentSet* pCompSet)
{
    CODComponentIterator it(pCompSet);

    // check if a process or a package was selected
    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        if (pComp && (ISA(pComp, PSS_ProcessSymbolBP) || ISA(pComp, PSS_PackageSymbolBP)))
            return false;

    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnSymbolDuplicated(CODComponentSet* pCompSet)
{
    // call the base class method to duplicate simple object
    PSS_ProcessGraphModelController::OnSymbolDuplicated(pCompSet);

    CODComponentIterator it(pCompSet);
    const int            countCopySet = m_CopySet.GetSize();
    int                  pos          = 0;

    // iterate through added elements and change their names. If symbols contain child components, asks the user
    // to duplicate sub-components. Notify observers for all added symbols
    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext(), ++pos)
    {
        if (!pComp)
            continue;

        PSS_ProcessSymbolBP* pProcessSym = dynamic_cast<PSS_ProcessSymbolBP*>(pComp);

        if (pProcessSym)
        {
            DoDuplicateProcess(reinterpret_cast<PSS_ProcessGraphModelMdl*>(pProcessSym->GetChildModel()));
            continue;
        }

        PSS_DoorSymbolBP* pDoorSym = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

        // if a door symbol, remove the linked process
        if (pDoorSym)
        {
            pDoorSym->RemoveTwinDoorSymbol(false);
            continue;
        }

        PSS_PageSymbolBP* pPageSym = dynamic_cast<PSS_PageSymbolBP*>(pComp);

        // if a page symbol, remove the linked page
        if (pPageSym)
            pPageSym->RemoveTwinPageSymbol(false);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsProcedure()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_ProcedureSymbolBP> pSymbol(new PSS_ProcedureSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_PROCEDUREBP);
    m_CurrentCursor = IDC_INS_PROCEDUREBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_PROCEDURE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsProcedure(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PROCEDURE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsProcess()
{
    ClearSelectionToSet();

    // set creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_ProcessSymbolBP> pSymbol(new PSS_ProcessSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_PROCESSBP);
    m_CurrentCursor = IDC_INS_PROCESSBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_PROCESS;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsProcess(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PROCESS);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsPage()
{
    InsertPageSymbol();

    // change the cursor
    SetCustomCursor(IDC_INS_PAGEBP);
    m_CurrentCursor = IDC_INS_PAGEBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_PAGE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsPage(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsDoor()
{
    InsertDoorSymbol();

    // change the cursor
    SetCustomCursor(IDC_INS_DOORBP);
    m_CurrentCursor = IDC_INS_DOORBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_DOOR;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsDoor(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DOOR);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsStop()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_StopSymbolBP> pSymbol(new PSS_StopSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_STOPBP);
    m_CurrentCursor = IDC_INS_STOPBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_STOP;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsStop(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_STOP);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsStart()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_StartSymbolBP> pSymbol(new PSS_StartSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_STARTBP);
    m_CurrentCursor = IDC_INS_STARTBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_START;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsStart(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_START);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsDeliverable()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    // create the deliverable symbol
    std::unique_ptr<PSS_DeliverableLinkSymbolBP> pLinkComp(new PSS_DeliverableLinkSymbolBP());
    pLinkComp->CreateOrthogonal();
    OnInsertLink(pLinkComp.get());
    pLinkComp.release();

    // change the cursor
    SetCustomCursor(IDC_INS_DELIVERABLEBP);
    m_CurrentCursor = IDC_INS_DELIVERABLEBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_DELIVERABLE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsDeliverable(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DELIVERABLE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsPackage()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_PackageSymbolBP> pSymbol(new PSS_PackageSymbolBP());
    pSymbol->Create();
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_PACKAGEBP);
    m_CurrentCursor = IDC_INS_PACKAGEBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_PACKAGE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsPackage(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_PACKAGE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsAlert()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_ALERT);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_ALERTBP);
    m_CurrentCursor = IDC_INS_ALERTBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_ALERT;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsAlert(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_ALERT);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsDocument()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_DOCUMENT);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_DOCUMENTBP);
    m_CurrentCursor = IDC_INS_DOCUMENTBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_DOCUMENT;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsDocument(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DOCUMENT);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsIndicator()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_INDICATOR);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_INDICATORBP);
    m_CurrentCursor = IDC_INS_INDICATORBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_INDICATOR;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsIndicator(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_INDICATOR);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsQuality()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_QUALITY);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_QUALITYBP);
    m_CurrentCursor = IDC_INS_QUALITYBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_QUALITY;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsQuality(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_QUALITY);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsDelay()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_DELAY);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_DELAYBP);
    m_CurrentCursor = IDC_INS_DELAYBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_DELAY;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsDelay(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_DELAY);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsInProcess()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_IN_PROCESS);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_IN_PROCESSBP);
    m_CurrentCursor = IDC_INS_IN_PROCESSBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_IN_PROCESS;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsInProcess(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_IN_PROCESS);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsNotValidated()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_NOT_VALIDATED);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_NOT_VALIDATEDBP);
    m_CurrentCursor = IDC_INS_NOT_VALIDATEDBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_NOT_VALIDATED;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsNotValidated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_NOT_VALIDATED);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsValidated()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_VALIDATED);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_VALIDATEDBP);
    m_CurrentCursor = IDC_INS_VALIDATEDBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_VALIDATED;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsValidated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_VALIDATED);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsRisk()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_RISK);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_RISKBP);
    m_CurrentCursor = IDC_INS_RISKBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_RISK;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsRisk(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_RISK);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsIncident()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_INCIDENT);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_INCIDENTBP);
    m_CurrentCursor = IDC_INS_INCIDENTBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_INCIDENT;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsIncident(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_INCIDENT);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsCRI()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_CRI);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_CRIBP);
    m_CurrentCursor = IDC_INS_CRIBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_CRI;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsCRI(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_CRI);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsCRE()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_CRE);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_CREBP);
    m_CurrentCursor = IDC_INS_CREBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_CRE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsCRE(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_CRE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsCRO()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_CRO);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_CROBP);
    m_CurrentCursor = IDC_INS_CROBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_CRO;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsCRO(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_CRO);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsOPAP1()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_OPAP1);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_OPAP1BP);
    m_CurrentCursor = IDC_INS_OPAP1BP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_OPAP1;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsOPAP1(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_OPAP1);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsOPAP2()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_OPAP2);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_OPAP2BP);
    m_CurrentCursor = IDC_INS_OPAP2BP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_OPAP2;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsOPAP2(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_OPAP2);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsOPAP3()
{
    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_GenericSymbolBP> pSymbol(new PSS_GenericSymbolBP());
    pSymbol->Create(IDR_OPAP3);
    OnInsertSymbol(pSymbol.get());
    pSymbol.release();

    // change the cursor
    SetCustomCursor(IDC_INS_OPAP3BP);
    m_CurrentCursor = IDC_INS_OPAP3BP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_OPAP3;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsOPAP3(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_OPAP3);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsTextZone()
{
    CODViewport* pCanvasVp = GetCanvasVp();

    if (!pCanvasVp)
        return;

    // create a default anchor point
    CPoint ptLog;

    // get the client DC to draw to
    CClientDC dc(GetWnd());
    pCanvasVp->PrepareDC(&dc, FALSE);

    ClearSelectionToSet();

    // set the creation flag
    m_NewSymbolCreated = true;

    std::unique_ptr<PSS_TextZoneBP> pTextZone(new PSS_TextZoneBP());
    pTextZone->Create(ptLog, &dc);
    OnInsertSymbol(pTextZone.get());
    pTextZone.release();

    // change the cursor
    SetCustomCursor(IDC_INS_TEXTZONEBP);
    m_CurrentCursor = IDC_INS_TEXTZONEBP;

    // set the current command ID
    m_CurrentCommandID = ID_INS_BP_TEXTZONE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateInsTextZone(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CurrentCommandID == ID_INS_BP_TEXTZONE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnShowProcessPreview()
{
    CODComponent* pComp = NULL;

    AssignSymbolHit();

    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(m_pCompHit);

    if (pProcess)
    {
        pProcess->SetShowPreview(!pProcess->GetShowPreview());

        CODViewport* pViewport = GetVp();

        // update the symbol
        if (pViewport)
        {
            CODComponentSet compSet;
            compSet.Add(m_pSymbolHit);
            pViewport->DrawComponents(&compSet);
        }

        // set the document as modified
        if (GetDocument())
            GetDocument()->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateShowProcessPreview(CCmdUI* pCmdUI)
{
    CODComponent* pComp = NULL;

    AssignSymbolHit();

    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(m_pCompHit);

    if (pProcess)
    {
        pCmdUI->Enable(TRUE);
        pCmdUI->SetCheck(pProcess->GetShowPreview());
    }
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnOdMeasurements()
{
    CODController::OnMeasurements();

    CDocument*   pDocument = GetDocument();
    CODViewport* pCanvasVp = GetCanvasVp();

    if (!pDocument || !pCanvasVp || !pCanvasVp->GetRuler())
        return;

    // set the document as modified
    pDocument->SetModifiedFlag(TRUE);

    PSS_ProcessGraphModelDoc* pProcessGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocument);

    if (pProcessGraphModelDoc)
        pProcessGraphModelDoc->SetPageUnits(*pCanvasVp->GetRuler());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnLinktoFilePackage()
{
    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);

    // todo -cCheck -oJean: package type was tested against m_pSymbolHit, but was get from m_pCompHit. Is the same pointer?
    //PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pCompHit);
    if (m_pSymbolHit != m_pCompHit)
        ::OutputDebugString("PSS_ProcessGraphModelControllerBP - OnLinktoFilePackage - m_pSymbolHit is not equal to m_pCompHit");

    if (!pPackage)
        return;

    CString title;
    VERIFY(title.LoadString(IDS_SELECTUNITIMPORT_TITLE));

    const CString extension = g_SearchAllModelExtension;

    // todo -cFeature -oJean: Localize me
    // build the first file filter
    CString filter = _T("Modèle (*.mlf)");
    filter += (char)'\0';
    filter += extension;
    filter += (char)'\0';

    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    // append the "*.*" all files filter
    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';

    PSS_FileDialog fileDialog(IDS_SELECTUNIT_FILEDLGTITLE, filter, 2);

    if (fileDialog.DoModal() == IDCANCEL)
        return;

    // check if it's a unit
    PSS_FolderStamp folderStamp;

    if (!folderStamp.ReadFromFile(fileDialog.GetFileName()))
        return;

    // set the file name
    pPackage->SetFileNameLinkedTo(fileDialog.GetFileName());

    CODViewport* pViewport = GetVp();

    // update the symbol
    if (pViewport)
    {
        CODComponentSet compSet;
        compSet.Add(m_pSymbolHit);
        pViewport->DrawComponents(&compSet);
    }

    CDocument* pDocument = GetDocument();

    // set the document as modified
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUnlinkFromFilePackage()
{
    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);

    // todo -cCheck -oJean: package type was tested against m_pSymbolHit, but was get from m_pCompHit. Is the same pointer?
    //PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pCompHit);
    if (m_pSymbolHit != m_pCompHit)
        ::OutputDebugString("PSS_ProcessGraphModelControllerBP - OnLinktoFilePackage - m_pSymbolHit is not equal to m_pCompHit");

    if (!pPackage)
        return;

    // unload the package
    if (pPackage->IsLinkedToFileName() && pPackage->IsLoaded())
        pPackage->UnloadPackage();

    // clear the link
    pPackage->ClearLinkedToFileName();

    CODViewport* pViewport = GetVp();

    // update the symbol
    if (pViewport)
    {
        CODComponentSet compSet;
        compSet.Add(m_pSymbolHit);
        pViewport->DrawComponents(&compSet);
    }

    CDocument* pDocument = GetDocument();

    // set the document as modified
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateUnlinkFromFilePackage(CCmdUI* pCmdUI)
{
    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);
    pCmdUI->Enable(pPackage && pPackage->IsLinkedToFileName());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnLoadPackage()
{
    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);

    // todo -cCheck -oJean: package type was tested against m_pSymbolHit, but was get from m_pCompHit. Is the same pointer?
    //PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pCompHit);
    if (m_pSymbolHit != m_pCompHit)
        ::OutputDebugString("PSS_ProcessGraphModelControllerBP - OnLinktoFilePackage - m_pSymbolHit is not equal to m_pCompHit");

    if (!pPackage)
        return;

    // unload the package first
    if (pPackage->IsLinkedToFileName() && pPackage->IsLoaded())
        pPackage->UnloadPackage();

    if (pPackage->IsLinkedToFileName() && !pPackage->IsLoaded())
    {
        PSS_ProcessGraphModelView* pView        = GetView();
        CDocument*                 pDoc         = GetDocument();
        PSS_ProcessModelDocTmpl*   pDocTemplate = pDoc ? dynamic_cast<PSS_ProcessModelDocTmpl*>(pDoc->GetDocTemplate()) : NULL;

        if (pDocTemplate)
            if (!pPackage->LoadPackage(pDocTemplate, GetModel()))
                return;

        CODViewport* pViewport = GetVp();

        // update the symbol
        if (pViewport)
        {
            CODComponentSet compSet;
            compSet.Add(m_pSymbolHit);
            pViewport->DrawComponents(&compSet);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateLoadPackage(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);

    pCmdUI->Enable(pPackage && pPackage->IsLinkedToFileName());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUnloadPackage()
{
    AssignSymbolHit();

    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);

    // todo -cCheck -oJean: package type was tested against m_pSymbolHit, but was get from m_pCompHit. Is the same pointer?
    //PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pCompHit);
    if (m_pSymbolHit != m_pCompHit)
        ::OutputDebugString("PSS_ProcessGraphModelControllerBP - OnLinktoFilePackage - m_pSymbolHit is not equal to m_pCompHit");

    if (!pPackage)
        return;

    if (pPackage->IsLinkedToFileName() && pPackage->IsLoaded())
    {
        // unload the package first
        pPackage->UnloadPackage();

        CODViewport* pViewport = GetVp();

        // update the symbol
        if (pViewport)
        {
            CODComponentSet compSet;
            compSet.Add(m_pSymbolHit);
            pViewport->DrawComponents(&compSet);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateUnloadPackage(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    PSS_PackageSymbolBP* pPackage = dynamic_cast<PSS_PackageSymbolBP*>(m_pSymbolHit);

    pCmdUI->Enable(pPackage && pPackage->IsLinkedToFileName() && pPackage->IsLoaded());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnViewComponents()
{
    CODController::OnViewComponents();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnViewModelGenToolbar()
{
    if (!m_pWndModelGenerationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());

        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();

        if (pMgr)
            m_pWndModelGenerationBar = pMgr->ToolBarFromID(M_GenerationToolBarID);
    }

    if (m_pWndModelGenerationBar)
    {
        CFrameWnd* pFrameWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

        if (pFrameWnd)
            pFrameWnd->ShowControlBar(m_pWndModelGenerationBar, !(m_pWndModelGenerationBar->GetStyle() & WS_VISIBLE), FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateViewModelGenToolbar(CCmdUI* pCmdUI)
{
    if (!m_pWndModelGenerationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());

        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();

        if (pMgr)
            m_pWndModelisationBar = pMgr->ToolBarFromID(M_GenerationToolBarID);
    }

    if (m_pWndModelGenerationBar)
        pCmdUI->SetCheck(m_pWndModelGenerationBar->GetStyle() & WS_VISIBLE);
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnViewModelToolbar()
{
    if (!m_pWndModelisationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());

        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();

        if (pMgr)
            m_pWndModelisationBar = pMgr->ToolBarFromID(M_ModelisationToolBarID);
    }

    if (m_pWndModelisationBar)
    {
        CFrameWnd* pFrameWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

        if (pFrameWnd)
            pFrameWnd->ShowControlBar(m_pWndModelisationBar, !(m_pWndModelisationBar->GetStyle() & WS_VISIBLE), FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateViewModelToolbar(CCmdUI* pCmdUI)
{
    if (!m_pWndModelisationBar)
    {
        ASSERT(PSS_FloatingToolBar::GetToolBarManager());
        ASSERT_KINDOF(SECToolBarManager, PSS_FloatingToolBar::GetToolBarManager());

        SECToolBarManager* pMgr = PSS_FloatingToolBar::GetToolBarManager();

        if (pMgr)
            m_pWndModelisationBar = pMgr->ToolBarFromID(M_ModelisationToolBarID);
    }

    if (m_pWndModelisationBar)
        pCmdUI->SetCheck(m_pWndModelisationBar->GetStyle() & WS_VISIBLE);
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnCheckModel()
{
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pModelDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pModel       = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModelDoc->GetModel());
    BOOL                        modelIsClean = FALSE;

    if (pModel)
    {
        PSS_DeleteCorruptedSymbols verifySymbols;
        verifySymbols.CheckModel(pModel);

        if (verifySymbols.GetCorruptedSymbolList()->GetCount() > 0)
        {
            DeleteComponents(verifySymbols.GetCorruptedSymbolList());
            pModelDoc->SetModifiedFlag();
            modelIsClean = TRUE;
        }
    }

    // check if consistency is set
    if (pModelDoc->GetCheckConsistency())
    {
        // ask to activate the output symbol log tab
        PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGSYMBOL_TAB);
        pModelDoc->NotifyAllObservers(&msg);

        CWaitCursor wait;

        pModelDoc->CheckModelWorkflow(modelIsClean);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateCheckModel(CCmdUI* pCmdUI)
{
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pModelDoc->GetCheckConsistency());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnRecalculateModelParameters()
{
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pModelDoc)
        return;

    // check if cost simulation is set
    if (pModelDoc->GetIntegrateCostSimulation())
    {
        // ask to activate the output analyzer log tab
        PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGANALYZER_TAB);
        pModelDoc->NotifyAllObservers(&msg);

        CWaitCursor wait;

        // unselect all components
        UnselectAllComponents();

        // initialize the calculator
        PSS_SesterceRecalculationAutomate automate(GetRootModel(), pModelDoc->GetAnalyzerOutputLog());
        automate.SetMaxWaitingForOtherLinks(1000);
        automate.SetMaxPaused(1000);
        automate.SetMaxLoop(2000);
        automate.Start(1);

        // set the document as modified
        pModelDoc->SetModifiedFlag();

        PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();

        // refresh symbol attributes
        if (pRootModel)
            pRootModel->RefreshSymbolAttributes(true);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateRecalculateModelParameters(CCmdUI* pCmdUI)
{
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pModelDoc->GetIntegrateCostSimulation());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnRecalculateModelDurations()
{
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pModelDoc)
        return;

    AssignSymbolHit();

    PSS_StartSymbolBP* pStartSymbol = dynamic_cast<PSS_StartSymbolBP*>(m_pSymbolHit);
    ASSERT(pStartSymbol);

    // check if cost simulation is set
    if (pModelDoc->GetIntegrateCostSimulation())
    {
        // ask to activate the output analyzer log tab
        PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGANALYZER_TAB);
        pModelDoc->NotifyAllObservers(&msg);

        CWaitCursor wait;

        // unselect all components
        UnselectAllComponents();

        // initialize the calculator
        PSS_DurationRecalculationAutomate automate(pStartSymbol, GetRootModel(), pModelDoc->GetAnalyzerOutputLog());
        automate.SetMaxWaitingForOtherLinks(1000);
        automate.SetMaxPaused(1000);
        automate.SetMaxLoop(2000);
        automate.SetAllowIncompletePath();
        automate.Start(1);

        // launch the second pass
        automate.IncrementPass();
        automate.Start(1);

        // set the modified flag
        pModelDoc->SetModifiedFlag();

        PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();

        // refresh symbol attributes
        if (pRootModel)
            pRootModel->RefreshSymbolAttributes(true);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateRecalculateModelDurations(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    pCmdUI->Enable(pModelDoc && pModelDoc->GetIntegrateCostSimulation() && m_pSymbolHit && ISA(m_pSymbolHit, PSS_StartSymbolBP));
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnCalculateRisks()
{
    PSS_Application* pApp      = PSS_Application::Instance();
    PSS_MainForm*    pMainForm = pApp ? pApp->GetMainForm() : NULL;

    if (!pMainForm)
        return;

    CString                   currencySymbol = PSS_Global::GetLocaleCurrency();
    PSS_ProcessGraphModelMdl* pModel         = GetRootModel();

    if (pModel)
    {
        PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pModel->GetDocument());

        // get the model currency symbol
        if (pDoc)
            currencySymbol = pDoc->GetCurrencySymbol();
    }

    PSS_RiskCalculateParametersDlg riskParametersDlg(pMainForm->GetApplicationIniFileName(), currencySymbol);

    if (riskParametersDlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

        if (pDoc)
        {
            PSS_CalculateRisks calculateRisks(riskParametersDlg.GetOrangeSeverityLevel(),
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
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateCalculateRisks(CCmdUI* pCmdUI)
{
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnInsertPage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    // filter object classes
    PSS_RuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
    rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

    PSS_InsertModelNewPageDlg dlg(pRoot,
                                  pRoot->GetValidNextPageName(),
                                  pRoot->GetExistingPageNameArray(),
                                  &rtClasses);

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphModelMdl* pModel = pRoot->CreateEmptyModel(dlg.GetPageName(), dlg.GetParentModel());
        PSS_ProcessGraphPage*     pPage  = pRoot->CreateNewPage(pModel, dlg.GetPageName(), dlg.GetParentModel());
        BrowseModel(pModel, dlg.GetParentModel());

        CWnd* pWnd = ::AfxGetMainWnd();

        // build the message
        if (pWnd)
        {
            PSS_DocObserverMsg docMsg;
            pWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        CDocument* pDocument = GetDocument();

        // set the document as modified
        if (pDocument)
            pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnRenamePage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    const CString newPage = pRoot->GetValidNextPageName();

    // filter object classes
    PSS_RuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
    rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

    PSS_RenameModelPageDlg dlg(pRoot, pRoot->GetExistingPageNameArray(), NULL, &rtClasses);

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphPage* pPage = dlg.GetSelectedPage();

        if (pPage)
        {
            // keep the old page name
            CString OldPageName = pPage->GetPageName();

            // rename the page
            pPage->SetPageName(dlg.GetPageName());

            // notify the owner model about page changes
            pRoot->OnPageNameChanged(pPage, OldPageName);
        }

        CWnd* pWnd = ::AfxGetMainWnd();

        // build the message
        if (pWnd)
        {
            PSS_DocObserverMsg docMsg;
            pWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        CDocument* pDocument = GetDocument();

        // set the document as modified
        if (pDocument)
            GetDocument()->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnDeletePage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    // filter object classes
    PSS_RuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
    rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

    PSS_DeleteModelPageDlg dlg(pRoot, &rtClasses);

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphPage* pPage = dlg.GetSelectedPage();

        if (pPage)
        {
            // move to the root model
            BrowseModel(pRoot, pRoot->GetParent());

            // delete the page and its associated model
            pRoot->DeletePage(pPage->GetPageName(), true);

            CWnd* pWnd = ::AfxGetMainWnd();

            // build the message
            if (pWnd)
            {
                PSS_DocObserverMsg docMsg;
                pWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
            }

            CDocument* pDocument = GetDocument();

            // set the document as modified
            if (pDocument)
                pDocument->SetModifiedFlag(TRUE);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnRenameCurrentPage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    const CString newPage = pRoot->GetValidNextPageName();

    // find the current page
    PSS_ProcessGraphPage* pCurrentPage = pRoot->FindModelPage(pModel, true);

    if (!pCurrentPage)
        return;

    // Keeps the old page name
    const CString oldPageName = pCurrentPage->GetPageName();

    PSS_RenameModelPageInTreeDlg dlg(newPage, pRoot->GetExistingPageNameArray());

    if (dlg.DoModal() == IDOK)
    {
        if (pCurrentPage)
        {
            pCurrentPage->SetPageName(dlg.GetPageName());

            // notify the owner model about page changes
            pRoot->OnPageNameChanged(pCurrentPage, oldPageName);

            CFrameWnd* pFrameWnd    = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());
            CFrameWnd* pActiveFrame = pFrameWnd ? pFrameWnd->GetActiveFrame() : NULL;

            // force the active window title to refresh
            if (pActiveFrame)
                pActiveFrame->OnUpdateFrameTitle(TRUE);
        }

        CWnd* pWnd = ::AfxGetMainWnd();

        // build the message
        if (pWnd)
        {
            PSS_DocObserverMsg docMsg;
            pWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        CDocument* pDocument = GetDocument();

        // set the document as modified
        if (pDocument)
            pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnPlaySimulation()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdatePlaySimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnPauseSimulation()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdatePauseSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnStopSimulation()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateStopSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnRewSimulation()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateRewSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnFwdSimulation()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateFwdSimulation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnShowInputAttributes()
{
    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel());

    if (!pModel)
        return;

    PSS_InputAttributesSelectionDlg dlg(pModel->GetInputAttributes(), pDoc->GetDynamicPropertiesManager());
    dlg.DoModal();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateShowInputAttributes(CCmdUI* pCmdUI)
{
    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel());

    pCmdUI->Enable(pDoc->GetDynamicPropertiesManager() && pModel && pModel->GetInputAttributes());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnFormatPainter()
{
    if (!m_IsInFormatPainter)
    {
        // on first click above the button, change the icon and copy the selection
        m_state         = OD_SYMBOL_READY;
        m_CurrentCursor = IDC_FORMATPAINTER;

        SetCustomCursor(IDC_FORMATPAINTER);
        AssignSymbolHit();

        m_pFormatPainterSymbol = m_pSymbolHit;
        m_IsInFormatPainter    = true;
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnUpdateFormatPainter(CCmdUI* pCmdUI)
{
    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // check if symbol clicked, allow the format painter if yes
    if (pSymbolHit)
    {
        CODComponentSet* pSelection = GetSelection();
        pCmdUI->Enable(pSelection && pSelection->GetSize() == 1 && !pSymbolHit->IsGeneric());
    }
    else
    if (pLinkSymbolHit)
    {
        CODComponentSet* pSelection = GetSelection();
        pCmdUI->Enable(pSelection && pSelection->GetSize() == 1);
    }
    else
        pCmdUI->Enable(FALSE);

    pCmdUI->SetCheck(m_IsInFormatPainter);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnProperties()
{
    CODController::OnProperties();

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(m_LastSelectedElement);

    if (pSymbol)
        pSymbol->DuplicateStyleOnTwinSymbol();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::OnPostCutPasteOperation(CODComponentSet* pCompSet)
{
    CODComponentIterator it(pCompSet);

    // remove the reference on the twin door symbol from the set
    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

        if (pDoor)
        {
            pDoor->SetTwinDoorSymbol(NULL);
            pDoor->SetTwinDoorReferenceNumber(-1);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelControllerBP::DoDuplicateProcess(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pPageSet = pModel->GetPageSet();

    // iterate through all pages
    if (pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

            // don't check for itself
            if (pModel && pModel != pModel)
                DoDuplicateProcess(pModel);
        }
    }

    // process the model components
    CODComponentSet* pSet      = pModel->GetComponents();
    const int        compCount = pSet->GetSize();

    for (int i = 0; i < compCount; ++i)
    {
        CODComponent*   pComp       = pSet->GetAt(i);
        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        // if the same reference number was found, return true
        if (pSymbol)
        {
            PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();

            if (pRootModel)
            {
                const int refNumber = pRootModel->GetNextAvailableReferenceNumber();

                pSymbol->SetSymbolReferenceNumber(refNumber);

                // get the next available name
                PSS_BuildSymbolNewName newNameBuilder(pSymbol->GetSymbolName());
                pSymbol->SetSymbolName(newNameBuilder.GetNextAvailableSymbolName(*pRootModel, refNumber));
            }
        }
        else
        if (pLinkSymbol)
        {
            PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();

            if (pRootModel)
            {
                const int refNumber = pRootModel->GetNextAvailableReferenceNumber();

                pSymbol->SetSymbolReferenceNumber(refNumber);

                // get the next available name
                PSS_BuildSymbolNewName newNameBuilder(pSymbol->GetSymbolName());
                pSymbol->SetSymbolName(newNameBuilder.GetNextAvailableSymbolName(*pRootModel, refNumber));
            }
        }

        if (pSymbol && pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                DoDuplicateProcess(pChildModel);
        }
    }
}
//---------------------------------------------------------------------------
