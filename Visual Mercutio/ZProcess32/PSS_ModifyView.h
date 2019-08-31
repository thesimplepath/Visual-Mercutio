/****************************************************************************
 * ==> PSS_ModifyView ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify view                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModifyViewH
#define PSS_ModifyViewH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ReadView.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Modify view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModifyView : public PSS_ReadView
{
    DECLARE_DYNCREATE(PSS_ModifyView)

    public:
        typedef PSS_ReadView inherited;

        /**
        * Processes the editable object
        *@param pObj - object
        */
        virtual void EditObject(PlanFinObject* pObj = NULL);

    protected:
        CString m_ToolTipTypeObject;
        CString m_ToolTipNoteText;

        PSS_ModifyView();
        virtual ~PSS_ModifyView();

        /**
        * Creates an edit control
        *@param pObj - edit object
        *@param pDC - device context
        *@return the right edit control based on the object
        */
        virtual PSS_Edit* CreateEditControl(PlanFinObject* pObj, CDC* pDC = NULL);

        /**
        * Adds a notes object
        *@param pObj - object
        */
        void AddObjectNotes(PlanFinObject* pObj);

        /**
        * Gets the right popup menu identifier
        *@return the right popup menu identifier
        */
        virtual inline UINT GetRightPopupMenuID();

        /**
        * Called when the view is drawn
        *@param pDC - device context
        */
        virtual void OnDraw(CDC* pDC);

        /// Generated message map functions
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        #if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
        //{{AFX_MSG(ZIViewModify)
            afx_msg LONG OnCalculateAllFormula(UINT message, LONG wParam);
            afx_msg LONG OnFieldChange(UINT message, LONG wParam);
            afx_msg void OnToday();
            afx_msg void OnEditionProtectObject();
            afx_msg void OnUpdateEditionProtectObject(CCmdUI* pCmdUI);
            afx_msg LONG ProcessCalculate(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnProcessFieldEditNext(WPARAM wParam, LPARAM lParam);
            afx_msg LONG ProcessFieldChange(WPARAM wParam, LPARAM lParam);
            afx_msg BOOL OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
            afx_msg void OnAddObjectNotes();
            afx_msg void OnDeleteObjectNotes();
            afx_msg void OnUpdateDeleteObjectNotes(CCmdUI* pCmdUI);
            afx_msg LONG OnEmptyObject(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnWizardMenu(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnCalendarObject(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnObjectNote(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnAssociationMenu(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnMenuSelected(WPARAM wParam, LPARAM lParam);
            afx_msg void OnSubmenu1Selectobject();
            afx_msg void OnSubmenu1Unselectobject();
            afx_msg LONG OnClearSelectionAll(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnPointerSelection(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnPointerHasSelected(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnFieldEditNext(WPARAM wParam, LPARAM lParam);
            afx_msg LONG OnDeselectAllObjects(WPARAM wParam, LPARAM lParam);
            afx_msg void OnInsertFile();
            afx_msg void OnUpdateInsertFile(CCmdUI* pCmdUI);
            afx_msg LONG OnObjectProperty(WPARAM wParam, LPARAM lParam);
            afx_msg void OnFieldPositionSize();
            afx_msg void OnFieldProperty();
            afx_msg void OnWizardCreateFormula();
            afx_msg void OnSubmenu1Fontchange();
            afx_msg void OnUpdateSubmenu1Fontchange(CCmdUI* pCmdUI);
            afx_msg void OnSubmenuFormat();
            afx_msg void OnSubmenuModifyFormula();
            afx_msg void OnUpdateSubMenuFormat(CCmdUI* pCmdUI);
            afx_msg void OnUpdateSubmenuAlign(CCmdUI* pCmdUI);
            afx_msg void OnUpdateSubmenuModifyFormula(CCmdUI* pCmdUI);
            afx_msg void OnSubmenuAlign();
            afx_msg void OnSubmenuHidePrtObject();
            afx_msg void OnUpdateSubmenuHidePrtObject(CCmdUI* pCmdUI);
            afx_msg void OnSubmenuObjectHide();
            afx_msg void OnUpdateSubmenuObjectHide(CCmdUI* pCmdUI);
            afx_msg void OnSubmenuChangeColor();
            afx_msg void OnWizardFormat();
            afx_msg void OnWizardCalculated();
            afx_msg void OnFieldAlignCenter();
            afx_msg void OnFieldAlignLeft();
            afx_msg void OnFieldAlignRight();
            afx_msg void OnUpdateFieldAlignCenter(CCmdUI* pCmdUI);
            afx_msg void OnUpdateFieldAlignLeft(CCmdUI* pCmdUI);
            afx_msg void OnUpdateFieldAlignRight(CCmdUI* pCmdUI);
            afx_msg void OnFieldApplyRounded();
            afx_msg void OnSubmenuChangeFillcolor();
            afx_msg void OnSectionAlign();
            afx_msg void OnSectionChangeStyle();
            afx_msg void OnSectionChangeColor();
            afx_msg void OnSectionChangeFillColor();
            afx_msg void OnSectionFontChange();
            afx_msg void OnChangeBorder();
            afx_msg void OnChangeLineColor();
        #endif
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ModifyView(const PSS_ModifyView& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ModifyView& operator = (const PSS_ModifyView& other);
};

//---------------------------------------------------------------------------
// PSS_ModifyView
//---------------------------------------------------------------------------
UINT PSS_ModifyView::GetRightPopupMenuID()
{
    #if defined (_ZSCRIPTOR)
        return IDR_CONTEXT1_SCRIPTOR;
    #elif defined (_ZDESIGNER)
        return IDR_CONTEXT1;
    #else
        return -1;
    #endif
}
//---------------------------------------------------------------------------

#endif
