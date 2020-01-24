/****************************************************************************
 * ==> PSS_ProcessGraphModelControllerBP -----------------------------------*
 ****************************************************************************
 * Description : Provides a graphic model controller for banking processes  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelControllerBPH
#define PSS_ProcessGraphModelControllerBPH

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

// processsoft
#include "zModel\PSS_ProcessGraphModelController.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_ModelisationToolbarName    _T("BP_ModelisationToolbar")
#define M_ModelGenerationToolbarName _T("BP_ModelGenerationToolbar")
#define M_MainMenubarName            _T("BP_MainMenubar")
#define M_ModelisationToolBarID      AFX_IDW_TOOLBAR + 30
#define M_GenerationToolBarID        AFX_IDW_TOOLBAR + 31
//---------------------------------------------------------------------------

using namespace sfl;

/**
* Graphic model controller for banking processes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphModelControllerBP : public PSS_ProcessGraphModelController
{
    public:
        /**
        * Constructor
        *@param pViewport - the viewport
        */
        PSS_ProcessGraphModelControllerBP(PSS_ProcessGraphModelViewport* pViewport);

        /**
        * Inserts a page symbol
        */
        virtual void InsertPageSymbol();

        /**
        * Inserts a door symbol
        */
        virtual void InsertDoorSymbol();

        /**
        * Checks if an item can be dropped
        *@param pObj - the item object to drop
        *@param point - the drop point
        *@return true if an item can be dropped, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item
        *@param pObj - the item object to drop
        *@param point - the drop point
        *@return true if drop succeeded, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Checks if an item can be dropped on a model
        *@param pObj - the item object to drop
        *@param point - the drop point
        *@return true if an item can be dropped on the model, otherwise false
        */
        virtual bool AcceptDropItemToModel(CObject* pObj, const CPoint& point);

        /**
        * Drops an item on a model
        *@param pObj - the item object to drop
        *@param point - the drop point
        *@return true if drop succeeded, otherwise false
        */
        virtual bool DropItemToModel(CObject* pObj, const CPoint& point);

        /**
        * Checks the objects contained in the component set may be duplicated
        *@param pCompSet - the component set containing the objects to check
        *@return true if the objects contained in the component set may be duplicated
        */
        virtual bool CanDuplicateObject(CODComponentSet* pCompSet);

        /**
        * Called by the controller once all the symbols were completely duplicated
        *@param pCompSet - the component set containing the duplicated symbol
        */
        virtual void OnSymbolDuplicated(CODComponentSet* pCompSet);

    protected:
        virtual ~PSS_ProcessGraphModelControllerBP();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessGraphModelControllerBP)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessGraphModelControllerBP)
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
        afx_msg void OnUpdateViewModelGenToolbar(CCmdUI* pCmdUI);
        afx_msg void OnViewModelToolbar();
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

        /**
        * Called after a cut and paste operation was performed
        *@param pCompSet - the component set containing the cut and paste objects
        */
        virtual void OnPostCutPasteOperation(CODComponentSet* pCompSet);

    private:
        static SECCustomToolBar* m_pWndModelisationBar;
        static SECCustomToolBar* m_pWndModelGenerationBar;

        /**
        * Called when a process should be duplicated
        *@param pModel - the model containing the process to duplicate
        */
        void DoDuplicateProcess(PSS_ProcessGraphModelMdl* pModel);
};

#endif
