// ProcGraphModelCtlrBP.h : interface of the ZDProcessGraphModelControllerBP class

#if !defined(AFX_ProcGraphModelCtlrBP_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ProcGraphModelCtlrBP_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

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

#include "zModel\ProcGraphModelCtlr.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// toolbar defined name
#define _ModelisationToolbarName    _T( "BP_ModelisationToolbar" )
#define _ModelGenerationToolbarName    _T( "BP_ModelGenerationToolbar" )
#define _MainMenubarName            _T( "BP_MainMenubar" )

#define _ModelisationToolBarID        ( AFX_IDW_TOOLBAR + 30 )
#define _GenerationToolBarID        ( AFX_IDW_TOOLBAR + 31 )

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

class AFX_EXT_CLASS ZDProcessGraphModelControllerBP : public ZDProcessGraphModelController
{
public:

    ZDProcessGraphModelControllerBP( ZIProcessGraphModelViewport* pViewport );

    virtual bool    DropItemToModel( CObject* pObj, CPoint pt );
    virtual bool    AcceptDropItemToModel( CObject* pObj, CPoint pt );

    virtual bool    DropItem( CObject* pObj, CPoint pt );
    virtual bool    AcceptDropItem( CObject* pObj, CPoint pt );

    // Insert symbol methods
    virtual void    InsertPageSymbol();
    virtual void    InsertDoorSymbol();

    /* Called by the controller, once the symbol has been completely
       duplicated. */
    virtual void OnSymbolDuplicated( CODComponentSet* pCompSet );

    // Return true if the objects contained in the pCompSet can be duplicated
    virtual bool CanDuplicateObject( CODComponentSet* pCompSet );

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDProcessGraphModelControllerBP)
    //}}AFX_VIRTUAL

// Implementation
protected:

    virtual ~ZDProcessGraphModelControllerBP();

    // Generated message map functions
    //{{AFX_MSG(ZDProcessGraphModelControllerBP)
    afx_msg void OnInsProcedure();
    afx_msg void OnUpdateInsProcedure(CCmdUI* pCmdUI);
    afx_msg void OnInsProcess();
    afx_msg void OnUpdateInsProcess(CCmdUI* pCmdUI);
    afx_msg void OnInsPage();
    afx_msg void OnUpdateInsPage(CCmdUI* pCmdUI);
    afx_msg void OnInsDoor();
    afx_msg void OnUpdateInsDoor(CCmdUI* pCmdUI);
    afx_msg void OnInsStop();
    afx_msg void OnUpdateInsStop(CCmdUI* pCmdUI);
    afx_msg void OnInsStart();
    afx_msg void OnUpdateInsStart(CCmdUI* pCmdUI);
    afx_msg void OnInsDeliverable();
    afx_msg void OnUpdateInsDeliverable(CCmdUI* pCmdUI);
    afx_msg void OnInsPackage();
    afx_msg void OnUpdateInsPackage(CCmdUI* pCmdUI);
    afx_msg void OnInsAlert();
    afx_msg void OnUpdateInsAlert(CCmdUI* pCmdUI);
    afx_msg void OnInsDocument();
    afx_msg void OnUpdateInsDocument(CCmdUI* pCmdUI);
    afx_msg void OnInsIndicator();
    afx_msg void OnUpdateInsIndicator(CCmdUI* pCmdUI);
    afx_msg void OnInsQuality();
    afx_msg void OnUpdateInsQuality(CCmdUI* pCmdUI);
    afx_msg void OnInsDelay();
    afx_msg void OnUpdateInsDelay(CCmdUI* pCmdUI);
    afx_msg void OnInsInProcess();
    afx_msg void OnUpdateInsInProcess(CCmdUI* pCmdUI);
    afx_msg void OnInsNotValidated();
    afx_msg void OnUpdateInsNotValidated(CCmdUI* pCmdUI);
    afx_msg void OnInsValidated();
    afx_msg void OnUpdateInsValidated(CCmdUI* pCmdUI);
    afx_msg void OnInsRisk();
    afx_msg void OnUpdateInsRisk(CCmdUI* pCmdUI);
    afx_msg void OnInsIncident();
    afx_msg void OnUpdateInsIncident(CCmdUI* pCmdUI);
    afx_msg void OnInsCRI();
    afx_msg void OnUpdateInsCRI(CCmdUI* pCmdUI);
    afx_msg void OnInsCRE();
    afx_msg void OnUpdateInsCRE(CCmdUI* pCmdUI);
    afx_msg void OnInsCRO();
    afx_msg void OnUpdateInsCRO(CCmdUI* pCmdUI);
    afx_msg void OnInsOPAP1();
    afx_msg void OnUpdateInsOPAP1(CCmdUI* pCmdUI);
    afx_msg void OnInsOPAP2();
    afx_msg void OnUpdateInsOPAP2(CCmdUI* pCmdUI);
    afx_msg void OnInsOPAP3();
    afx_msg void OnUpdateInsOPAP3(CCmdUI* pCmdUI);
    afx_msg void OnInsTextZone();
    afx_msg void OnUpdateInsTextZone(CCmdUI* pCmdUI);
    afx_msg void OnShowProcessPreview();
    afx_msg void OnUpdateShowProcessPreview(CCmdUI* pCmdUI);
    afx_msg void OnOdMeasurements();
    afx_msg void OnLinktoFilePackage();
    afx_msg void OnUnlinkFromFilePackage();
    afx_msg void OnUpdateUnlinkFromFilePackage(CCmdUI* pCmdUI);
    afx_msg void OnLoadPackage();
    afx_msg void OnUpdateLoadPackage(CCmdUI* pCmdUI);
    afx_msg void OnUnloadPackage();
    afx_msg void OnUpdateUnloadPackage(CCmdUI* pCmdUI);
    afx_msg void OnViewComponents();
    afx_msg void OnViewModelGenToolbar();
    afx_msg void OnViewModelToolbar();
    afx_msg void OnUpdateViewModelGenToolbar(CCmdUI* pCmdUI);
    afx_msg void OnUpdateViewModelToolbar(CCmdUI* pCmdUI);
    afx_msg void OnCheckModel();
    afx_msg void OnUpdateCheckModel(CCmdUI* pCmdUI);
    afx_msg void OnRecalculateModelParameters();
    afx_msg void OnUpdateRecalculateModelParameters(CCmdUI* pCmdUI);
    afx_msg void OnRecalculateModelDurations();
    afx_msg void OnUpdateRecalculateModelDurations(CCmdUI* pCmdUI);
    afx_msg void OnCalculateRisks();
    afx_msg void OnUpdateCalculateRisks(CCmdUI* pCmdUI);
    afx_msg void OnInsertPage();
    afx_msg void OnRenamePage();
    afx_msg void OnDeletePage();
    afx_msg void OnRenameCurrentPage();
    afx_msg void OnPlaySimulation();
    afx_msg void OnUpdatePlaySimulation(CCmdUI* pCmdUI);
    afx_msg void OnPauseSimulation();
    afx_msg void OnUpdatePauseSimulation(CCmdUI* pCmdUI);
    afx_msg void OnStopSimulation();
    afx_msg void OnUpdateStopSimulation(CCmdUI* pCmdUI);
    afx_msg void OnRewSimulation();
    afx_msg void OnUpdateRewSimulation(CCmdUI* pCmdUI);
    afx_msg void OnFwdSimulation();
    afx_msg void OnUpdateFwdSimulation(CCmdUI* pCmdUI);
    afx_msg void OnShowInputAttributes();
    afx_msg void OnUpdateShowInputAttributes(CCmdUI* pCmdUI);
    afx_msg void OnFormatPainter();
    afx_msg void OnUpdateFormatPainter(CCmdUI* pCmdUI);
    afx_msg void OnProperties();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual void OnPostCutPasteOperation( CODComponentSet* pCompSet );

private:

    void DoDuplicateProcess( ZDProcessGraphModelMdl* pModel );

private:

    // The controler contains the toolbar associated
    // In static to avoid loading toolbars and menubars several times
    static SECCustomToolBar* m_pwndModelisationBar;
    static SECCustomToolBar* m_pwndModelGenerationBar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ProcGraphModelCtlrBP_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)