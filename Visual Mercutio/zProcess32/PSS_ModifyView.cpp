/****************************************************************************
 * ==> PSS_ModifyView ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify view                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ModifyView.h"

// processsoft
#include "zBaseLib\PSS_CodeView.h"
#include "zBaseLib\PSS_VisualTool.h"
#include "zBaseLib\PSS_PLFNCheckBtn.h"
#include "zBaseLib\PSS_PLFNRadioBtn.h"
#include "zBaseLib\PSS_PLFNAutoNumbered.h"
#include "zBaseLib\PSS_PLFNSquare.h"
#include "zBaseLib\PSS_PLFNBoundText.h"
#include "zBaseLib\PSS_PLFNBitmap.h"
#include "zBaseLib\PSS_PLFNMultiColumn.h"
#include "zBaseLib\PSS_PLFNMaskString.h"
#include "zBaseLib\PSS_Edit.h"
#include "zBaseLib\PSS_ObjectUtility.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_FieldObserverMsg.h"
#include "zWinUtil32\PSS_CalendarWindowDialog.h"
#include "zWinUtil32\PSS_ObjectNotesDialog.h"
#include "PSS_DocumentReadWrite.h"
#include "PSS_App.h"

#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    #include "zDesigner\wizformc.h"
    #include "zDesigner\ziwzform.h"
    #include "zDesigner\ziwzfrml.h"
    #include "zDesigner\wzalign.h"
    #include "zDesigner\WZFRMTST.h"
    #include "zDesigner\wizcalc.h"
    #include "zDesigner\ziwzrnde.h"
    #include "zDesigner\SelStyle.h"
    #include "zDesigner\BordDef.h"
    #include "zWinUtil32\colorsel.h"
    #include "Property.h"

    #ifdef _ZDESIGNER
        #include "zDesigner\planfdoc.h"
    #endif
#endif

// resources
#include "Resources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ModifyView, PSS_ReadView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModifyView, PSS_ReadView)
    //{{AFX_MSG_MAP(PSS_ModifyView)
    ON_WM_MOUSEMOVE()
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        ON_COMMAND(ID_TODAY, OnToday)
        ON_COMMAND(ID_EDITION_PROTECTOBJECT, OnEditionProtectObject)
        ON_UPDATE_COMMAND_UI(ID_EDITION_PROTECTOBJECT, OnUpdateEditionProtectObject)
        ON_MESSAGE(ID_PROCESS_CALCULATE_MESSAGE, ProcessCalculate)
        ON_MESSAGE(ID_PROCESS_FIELD_EDITNEXT, OnProcessFieldEditNext)
        ON_MESSAGE(ID_PROCESS_FIELD_CHANGE, ProcessFieldChange)
        ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNeedText)
        ON_COMMAND(ID_ADDOBJECTNOTES, OnAddObjectNotes)
        ON_COMMAND(ID_DELETEOBJECTNOTES, OnDeleteObjectNotes)
        ON_UPDATE_COMMAND_UI(ID_DELETEOBJECTNOTES, OnUpdateDeleteObjectNotes)
        ON_MESSAGE(UM_SPHELP_EMPTYOBJECT, OnEmptyObject)
        ON_MESSAGE(UM_SPHELP_WIZARDMENU, OnWizardMenu)
        ON_MESSAGE(UM_SPHELP_CALENDAROBJECT, OnCalendarObject)
        ON_MESSAGE(UM_SPHELP_NOTEOBJECT, OnObjectNote)
        ON_MESSAGE(UM_SPHELP_ASSOCIATIONOBJECT, OnAssociationMenu)
        ON_MESSAGE(ID_SPECIALHELPMENU, OnMenuSelected)
        ON_COMMAND(ID_SUBMENU1_SELECTOBJECT, OnSubmenu1Selectobject)
        ON_COMMAND(ID_SUBMENU1_UNSELECTOBJECT, OnSubmenu1Unselectobject)
        ON_MESSAGE(ID_CLEARSELECTIONALL, OnClearSelectionAll)
        ON_MESSAGE(ID_POINTERINSELECTION, OnPointerSelection)
        ON_MESSAGE(ID_POINTERHASSELECTED, OnPointerHasSelected)
        ON_MESSAGE(ID_FIELD_EDITNEXT, OnFieldEditNext)
        ON_MESSAGE(ID_FIELD_DESELECTALLOBJECT, OnDeselectAllObjects)
        ON_COMMAND(ID_INSERT_FILE, OnInsertFile)
        ON_UPDATE_COMMAND_UI(ID_INSERT_FILE, OnUpdateInsertFile)
        ON_MESSAGE(UM_SPHELP_PROPERTYOBJECT, OnObjectProperty)
        ON_COMMAND(ID_FIELD_POSITION_SIZE, OnFieldPositionSize)
        ON_COMMAND(ID_FIELD_PROPERTY, OnFieldProperty)
        ON_COMMAND(ID_WIZARD_CREATEFORMULA, OnWizardCreateFormula)
        ON_COMMAND(ID_SUBMENU1_FONTCHANGE, OnSubmenu1Fontchange)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU1_FONTCHANGE, OnUpdateSubmenu1Fontchange)
        ON_COMMAND(ID_SUBMENU_FORMAT, OnSubmenuFormat)
        ON_COMMAND(ID_WIZARD_MODIFYFORMULA, OnSubmenuModifyFormula)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU_FORMAT, OnUpdateSubMenuFormat)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU1_ALIGN, OnUpdateSubmenuAlign)
        ON_UPDATE_COMMAND_UI(ID_WIZARD_MODIFYFORMULA, OnUpdateSubmenuModifyFormula)
        ON_COMMAND(ID_SUBMENU1_ALIGN, OnSubmenuAlign)
        ON_COMMAND(ID_SUBMENU1_HIDEPRTOBJECT, OnSubmenuHidePrtObject)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU1_HIDEPRTOBJECT, OnUpdateSubmenuHidePrtObject)
        ON_COMMAND(ID_SUBMENU1_OBJECTHIDE, OnSubmenuObjectHide)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU1_OBJECTHIDE, OnUpdateSubmenuObjectHide)
        ON_COMMAND(ID_SUBMENU1_CHANGECOLOR, OnSubmenuChangeColor)
        ON_COMMAND(ID_WIZARD_FORMATFIELD, OnWizardFormat)
        ON_COMMAND(ID_WIZARD_CALCULATED, OnWizardCalculated)
        ON_COMMAND(ID_FIELD_ALIGNCENTER, OnFieldAlignCenter)
        ON_COMMAND(ID_FIELD_ALIGNLEFT, OnFieldAlignLeft)
        ON_COMMAND(ID_FIELD_ALIGNRIGHT, OnFieldAlignRight)
        ON_UPDATE_COMMAND_UI(ID_FIELD_ALIGNCENTER, OnUpdateFieldAlignCenter)
        ON_UPDATE_COMMAND_UI(ID_FIELD_ALIGNLEFT, OnUpdateFieldAlignLeft)
        ON_UPDATE_COMMAND_UI(ID_FIELD_ALIGNRIGHT, OnUpdateFieldAlignRight)
        ON_COMMAND(ID_FIELD_APPLYROUNDED, OnFieldApplyRounded)
        ON_COMMAND(ID_SUBMENU1_CHANGEFILLCOLOR, OnSubmenuChangeFillcolor)
        ON_COMMAND(ID_SECTION_ALIGN, OnSectionAlign)
        ON_COMMAND(ID_SECTION_CHANGE_STYLE, OnSectionChangeStyle)
        ON_COMMAND(ID_SECTION_CHANGECOLOR, OnSectionChangeColor)
        ON_COMMAND(ID_SECTION_CHANGEFILLCOLOR, OnSectionChangeFillColor)
        ON_COMMAND(ID_SECTION_FONTCHANGE, OnSectionFontChange)
        ON_COMMAND(ID_CHANGE_BORDER, OnChangeBorder)
        ON_MESSAGE(ID_CALCULATE_MESSAGE, OnCalculateAllFormula)
        ON_MESSAGE(ID_FIELD_CHANGE, OnFieldChange)
        ON_COMMAND(ID_SUBMENU1_CHANGELINECOLOR, OnChangeLineColor)
    #endif
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModifyView
//---------------------------------------------------------------------------
PSS_ModifyView::PSS_ModifyView() :
    PSS_ReadView()
{
    m_ViewType = PSS_View::IE_VT_FormModify;

    m_ToolTipNoteText.LoadString(IDS_TOOLTIPNOTETEXT);
    m_ToolTipTypeObject.LoadString(IDS_TOOLTIPOBJECTTYPE);
}
//---------------------------------------------------------------------------
PSS_ModifyView::PSS_ModifyView(const PSS_ModifyView& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ModifyView::~PSS_ModifyView()
{}
//---------------------------------------------------------------------------
const PSS_ModifyView& PSS_ModifyView::operator = (const PSS_ModifyView& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ModifyView::EditObject(PSS_PlanFinObject* pObj)
{
    PSS_Document* pDocument = GetDocument();

    if (!pDocument)
        return;

    CDC* pDC = GetDC();
    PSS_Assert(pDC);

    OnPrepareDC(pDC);
    DeselectAllObject(this, pDC, pDocument);

    // delete the existing edit control
    if (pDocument->GetEditControl())
    {
        delete pDocument->GetEditControl();
        pDocument->AssignEditControl(NULL);
    }

    pDocument->AssignEditControl(CreateEditControl(pObj, pDC));

    // control was successfully created?
    if (pDocument->GetEditControl())
    {
        PSS_App* pApp = PSS_App::GetApp();

        if (pApp)
            pDocument->GetEditControl()->Create(PSS_Global::IsFormDesigner(),
                                                this,
                                                pDC,
                                                pDocument,
                                                pObj,
                                                pApp->GetFieldRepository(),
                                                pApp->IsAutoCalculate(),
                                                pApp->GoNextEdit());

        pDocument->SetModifiedFlag(TRUE);
    }

    VERIFY(ReleaseDC(pDC));
}
//---------------------------------------------------------------------------
PSS_Edit* PSS_ModifyView::CreateEditControl(PSS_PlanFinObject* pObj, CDC* pDC)
{
    switch (PSS_ObjectUtility::GetClassNameID(pObj))
    {
        case IDS_AMOUNT_CLASS:
            if (pObj->IsMemberOfMultiColumn())
                return new PSS_NumEditHistoric;

            return new PSS_NumEdit;

        case IDS_TEXT_CLASS:
            if (pObj->IsMemberOfMultiColumn())
                return new PSS_StrEditHistoric;

            return new PSS_StrEdit;

        case IDS_SQUARETEXT_CLASS:
        {
            PSS_PLFNSquare* pSquare = dynamic_cast<PSS_PLFNSquare*>(pObj);

            if (pSquare && pSquare->GetObject())
                return CreateEditControl(const_cast<PSS_PlanFinObject*>(pSquare->GetObject()), pDC);

            return NULL;
        }

        case IDS_NUMBEREDSECTION_CLASS:
        {
            PSS_PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

            if (pAutoNumbered && pAutoNumbered->GetObject())
                return CreateEditControl(const_cast<PSS_PlanFinObject*>(pAutoNumbered->GetObject()), pDC);

            return NULL;
        }

        case IDS_CHECK_CLASS:
        {
            PSS_Document* pDocument = GetDocument();

            if (!pDocument)
                return NULL;

            PSS_PLFNCheckBtn* pCheck = dynamic_cast<PSS_PLFNCheckBtn*>(pObj);

            if (pCheck)
            {
                pCheck->EditObject(this, pDC, pDocument);
                pDocument->SetModifiedFlag(TRUE);
            }

            return NULL;
        }

        case IDS_RADIO_CLASS:
        {
            PSS_Document* pDocument = GetDocument();

            if (!pDocument)
                return NULL;

            PSS_PLFNRadioBtn* pRadio = dynamic_cast<PSS_PLFNRadioBtn*>(pObj);

            if (pRadio)
            {
                pRadio->EditObject(this, pDC, pDocument);
                pDocument->SetModifiedFlag(TRUE);
            }

            return NULL;
        }

        case IDS_STATICTEXT_CLASS:      return new PSS_CalcEdit;
        case IDS_DATE_CLASS:            return new PSS_TimeEdit;
        case IDS_CALCULATED_CLASS:      return new PSS_CalcEdit;
        case IDS_HISTOAMOUNT_CLASS:     return new PSS_NumEditHistoric;
        case IDS_MULTITEXTSTATIC_CLASS: return new PSS_CalcEdit;
        case IDS_MULTITEXT_CLASS:       return new PSS_StrEdit(TRUE);
        case IDS_HISTOTEXT_CLASS:       return new PSS_StrEditHistoric;
        case IDS_MASKSTRING_CLASS:      return new PSS_MaskEdit;
        case IDS_MASKSTRINGHISTO_CLASS: return new PSS_MaskEdit;
        case IDS_MULTICOLUMN_CLASS:     return new PSS_MultiColumnEdit;
        default:                        return NULL;
    }
}
//---------------------------------------------------------------------------
void PSS_ModifyView::AddObjectNotes(PSS_PlanFinObject* pObj)
{
    if (!pObj)
        return;

    PSS_ObjectNotesDialog objectNotesDialog(pObj->GetNotes() ? pObj->GetNotes()->GetComment()  : _T(""),
                                            pObj->GetNotes() ? pObj->GetNotes()->GetUserName() : _T(""));

    switch (objectNotesDialog.DoModal())
    {
        case IDOK:
            // save the notes
            pObj->AddNotes(objectNotesDialog.GetComment(), PSS_Global::GetConnectedUserName());
            break;

        case IDC_DELETENOTES:
            // delete the notes
            pObj->DeleteNotes();
            break;
    }
}
//---------------------------------------------------------------------------
void PSS_ModifyView::OnDraw(CDC* pDC)
{
    PSS_ReadView::OnDraw(pDC);
}
//---------------------------------------------------------------------------
void PSS_ModifyView::OnMouseMove(UINT nFlags, CPoint point)
{
    PSS_App* pApp = PSS_App::GetApp();

    if (pApp && !pApp->IsCursorCapturedValid(point, this))
        ReleaseCapture();

    // find the current select tool and keep its pointer, but if control key pressed,
    // take the selection tool directly
    PSS_VisualTool* pTool = PSS_VisualTool::FindTool(PSS_VisualTool::m_CurrentToolType);

    if (pTool != NULL)
        pTool->OnMouseMove(this, nFlags, point);
}
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnCalculateAllFormula(UINT message, LONG wParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        // post a message to not slow down the process
        return PostMessage(ID_PROCESS_CALCULATE_MESSAGE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnFieldChange(UINT message, LONG wParam)
    {
        return PostMessage(ID_PROCESS_FIELD_CHANGE, 0, wParam);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnToday()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return;

        PSS_DocumentReadWrite* pDoc = dynamic_cast<PSS_DocumentReadWrite*>(pDocument);
        PSS_Assert(pDoc);

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (pObj == NULL)
                return;
        }

        PLFNTime* pTime = dynamic_cast<PLFNTime*>(pObj);

        // only valid on date object
        if (!pTime)
            return;

        // end the edition
        SetFocus();

        // release the mouse cursor capture
        ReleaseCapture();

        // set today to the object
        pTime->SetToday();

        // unselect the current object
        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnEditionProtectObject()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return;

        PSS_PlanFinObject *pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        if (!pLong)
            return;

        if (pLong->KeepTheValue())
            pLong->SetKeepTheValue(FALSE);
        else
            pLong->SetKeepTheValue();

        OnSubmenu1Unselectobject();
        pDocument->SetModifiedFlag();
        RedrawWindow();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateEditionProtectObject(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            pCmdUI->Enable(TRUE);
            return;
        }

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        // if the object is a number and is a calculated field
        if (pLong && pLong->IsCalculatedField())
        {
            pCmdUI->Enable(TRUE);
            pCmdUI->SetCheck(pLong->KeepTheValue());
            return;
        }

        pCmdUI->Enable(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::ProcessCalculate(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        pDocument->CalculateAllFormula(this, TRUE);

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnProcessFieldEditNext(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject*     pObj                  = (PSS_PlanFinObject*)lParam;
        PSS_PlanFinObject*     pNextEditObj          = NULL;
        double                 currentEditedTabOrder = pObj->GetTabOrder();
        PSS_DocumentReadWrite* pDoc                  = dynamic_cast<PSS_DocumentReadWrite*>(pDocument);
        PSS_Assert(pDoc);

        if (!pDoc->GetEditedObject() || !pObj)
            return 1;

        // get the current page
        const int page = pDoc->GetCurrentPage();

        PSS_PlanFinObject* pObjTemp  = NULL;
        POSITION           pPosition = pDoc->GetObjectList().GetHeadPosition();

        while (!pPosition)
        {
            pObjTemp = (PSS_PlanFinObject*)pDoc->GetObjectList().GetNext(pPosition);

            // if the same object, continue
            if (pObj == pObjTemp)
                continue;

            // iterate throught objects and find the next editable object within the same page
            if (page == pObjTemp->GetObjectPage())
            {
                // skip non editable object
                if (pObjTemp->IsReadOnlyAtRuntime()                     ||
                    pObjTemp->GetIsStatic()                             ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PSS_PLFNStatic))   ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PSS_PLFNCheckBtn)) ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PSS_PLFNRadioBtn)) ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PSS_PLFNLine))     ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PSS_PLFNRect))     ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PSS_PLFNNumbered)))
                    continue;

                PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObjTemp);

                if (pLong && pLong->IsCalculatedField())
                    continue;

                // test if the object in the list is greater than the edited tab order
                if (pObjTemp->GetTabOrder() > currentEditedTabOrder)
                {
                    // if a next edit object is defined and the object is greater than its tab order,
                    // continue and do not assign the new pointer object
                    if (pNextEditObj && pObjTemp->GetTabOrder() > pNextEditObj->GetTabOrder())
                        continue;

                    pNextEditObj = pObjTemp;
                }
            }
        }

        // if an object found
        if (pNextEditObj)
        {
            // translate the point in logical coordinates
            CDC* pDC = GetDC();
            PSS_Assert(pDC);
            OnPrepareDC(pDC);

            // save the pointer to the object, to be able to remove the flag later
            pDoc->SetEditedObject(pNextEditObj);

            // get the client rect and move the scroll bar, if necessary to see the edited object
            CRect rect = pNextEditObj->GetClientRect();
            pDC->LPtoDP(&rect);

            CPoint middleObjectPoint(rect.left + (rect.Width() / 2), rect.top + (rect.Height() / 2));

            CRect wndRect;
            GetClientRect(&wndRect);

            if (!wndRect.PtInRect(middleObjectPoint))
            {
                const CPoint devicePoint = GetDeviceScrollPosition();
                middleObjectPoint.x = __max(0, middleObjectPoint.x - wndRect.Width());
                middleObjectPoint.y = __max(0, middleObjectPoint.y - wndRect.Height() + 20);
                pDC->DPtoLP(&middleObjectPoint);
                ScrollToPosition(middleObjectPoint);
                OnPrepareDC(pDC);
            }

            EditObject(pNextEditObj);

            VERIFY(ReleaseDC(pDC));
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::ProcessFieldChange(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // to all document data
        if (lParam)
            pDocument->PropagateFieldValue((PSS_PlanFinObject*)lParam, -2);

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    BOOL PSS_ModifyView::OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
    {
        BOOL handledNotify = FALSE;

        TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
        pTTT->hinst       = NULL;
        pTTT->lpszText    = NULL;

        CPoint cursorPos;
        VERIFY(::GetCursorPos(&cursorPos));
        ScreenToClient(&cursorPos);

        CRect clientRect;
        GetClientRect(clientRect);

        // certify that the cursor is in the client rect, because the mainframe also wants
        // these messages to provide tooltips for the toolbar
        if (clientRect.PtInRect(cursorPos))
        {
            ClientToDoc(cursorPos);
            PSS_PlanFinObject* pObject = FindHitObject(cursorPos);

            if (pObject)
            {
                // adjust the text by filling in TOOLTIPTEXT
                m_StrToolTip.ReleaseBuffer();
                m_StrToolTip = m_ToolTipTypeObject + PSS_ObjectUtility::GetClassName(pObject);

                if (PSS_App::GetApp()->GetFieldRepository())
                {
                    PSS_ObjectDefinition* pObjectDefinition = 
                            PSS_App::GetApp()->GetFieldRepository()->FindField(pObject->GetObjectName());

                    if (pObjectDefinition && !pObjectDefinition->GetHelpUserDescription().IsEmpty())
                    {
                        m_StrToolTip += _T("\n");
                        m_StrToolTip += pObjectDefinition->GetHelpUserDescription();
                    }
                }

                if (pObject->GetNotes())
                {
                    m_StrToolTip += _T("\n") + m_ToolTipNoteText;

                    if (!pObject->GetNotes()->GetUsername().IsEmpty())
                        m_StrToolTip += _T("[") + pObject->GetNotes()->GetUsername() + _T("]");

                    m_StrToolTip += _T("\n") + pObject->GetNotes()->GetComment();
                }

                pTTT->hinst    = NULL;
                pTTT->lpszText = m_StrToolTip.GetBuffer(m_StrToolTip.GetLength() + 1);

            }
            else
            {
                m_StrToolTip.ReleaseBuffer();
                m_StrToolTip.Empty();

                pTTT->hinst    = NULL;
                pTTT->lpszText = NULL;
            }

            handledNotify = TRUE;
        }

        return handledNotify;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnAddObjectNotes()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        AddObjectNotes(pObj);

        OnSubmenu1Unselectobject();
        pDocument->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnDeleteObjectNotes()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj || !pObj->GetNotes())
            return;

        pObj->DeleteNotes();
        OnSubmenu1Unselectobject();
        pDocument->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateDeleteObjectNotes(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (pObj)
            pCmdUI->Enable(pObj->GetNotes() != NULL);
        else
            pCmdUI->Enable(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnEmptyObject(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)lParam;

        if (pObj)
        {
            SetFocus();
            pObj->EmptyObject();
            pObj->NotifyObjectHasChanged();
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnWizardMenu(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)lParam;

        HINSTANCE hInst = ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_WIZARDMENU), RT_MENU);

        // show the wizard context menu
        HMENU dummyMenu = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_WIZARDMENU));
        HMENU subMenu;
        ReleaseCapture();

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        if (pLong && pLong->IsCalculatedField())
            subMenu = ::GetSubMenu(dummyMenu, 0);
        else
        if (pLong)
            subMenu = ::GetSubMenu(dummyMenu, 1);
        else
        if (pObj->IsKindOf(RUNTIME_CLASS(PLFNTime)))
            subMenu = ::GetSubMenu(dummyMenu, 2);
        else
            subMenu = ::GetSubMenu(dummyMenu, 3);

        CPoint point;
        ::GetCursorPos(&point);

        // set the object as selected
        pObj->SelectObject();

        CWnd* pWnd = ::AfxGetMainWnd();

        if (pWnd)
            // show the menu
            ::TrackPopupMenu(subMenu,
                             TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                             point.x,
                             point.y,
                             0,
                             pWnd->GetSafeHwnd(),
                             NULL);

        SetCapture();

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnCalendarObject(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)lParam;

        if (pObj)
        {
            CPoint point;
            ::GetCursorPos(&point);

            PSS_CalendarWindowDialog calendarWnd(this);

            if (calendarWnd.HandleCalendar(point))
            {
                PLFNTime* pTime = dynamic_cast<PLFNTime*>(pObj);

                if (pTime)
                    pTime->SetTimeValue(calendarWnd.GetDate());

                CWnd* pWnd = ::AfxGetMainWnd();

                // to notify the view about field change, pass the adress of the object, so the routine
                // that proceed the message can know which object has changed
                if (pWnd)
                    pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

                pDocument->SetModifiedFlag();
            }
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnObjectNote(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)lParam;

        if (pObj)
            AddObjectNotes(pObj);

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnAssociationMenu(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)lParam;

        if (pObj)
        {
            CMenu associationMenu;
            associationMenu.CreatePopupMenu();

            CStringArray& strArray      = ((PLFNLong*)pObj)->GetAssociations().GetAssociationArray();
            PLFNLong*     pLong         = dynamic_cast<PLFNLong*>(pObj);
            BOOL          standardFound = FALSE;
            const int     arrayCount    = strArray.GetSize();
            int           i             = 0;

            for (; i < arrayCount; ++i)
            {
                // check if there is the standard schema in the array
                if (GetDocument()->GetDefaultAssociationString() == strArray[i])
                    standardFound = TRUE;

                UINT menuState;

                if (pLong && pLong->GetCurrentAssociation() && pLong->GetCurrentAssociation()->GetAssociationName() == strArray[i])
                    menuState = MF_DISABLED | MF_CHECKED | MF_GRAYED;
                else
                    menuState = MF_ENABLED;

                associationMenu.AppendMenu(menuState, MENU_COMMAND + i, strArray[i]);
            }

            // if no standard schema, add it to the menu
            if (!standardFound)
            {
                UINT menuState;

                if (pLong && !pLong->GetCurrentAssociation())
                    menuState = MF_DISABLED | MF_CHECKED | MF_GRAYED;
                else
                    menuState = MF_ENABLED;

                associationMenu.AppendMenu(menuState, MENU_COMMAND + i, GetDocument()->GetDefaultAssociationString());
            }

            CPoint pt;
            ::GetCursorPos(&pt);

            associationMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, ::AfxGetMainWnd());
            associationMenu.DestroyMenu();
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnMenuSelected(WPARAM wParam, LPARAM lParam)
    {
        SetFocus();

        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return 1;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        PSS_PlanFinObject* pObj      = pDocument->GetSelectedObject();
        CStringArray&      strArray  = ((PLFNLong*)pObj)->GetAssociations().GetAssociationArray();
        const std::size_t  arraySize = strArray.GetSize();
        PLFNLong*          pLong     = dynamic_cast<PLFNLong*>(pObj);

        // check if the standard schema is selected
        if (arraySize == wParam - MENU_COMMAND)
        {
            if (pLong)
                pLong->SetCurrentAssociation(NULL);

            // change the necessary calculated and number fields
            pDocument->ChangeFieldForCalculation();
            pDocument->UpdateAllViews(NULL);

            // recalculate
            pWnd->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

            return 1;
        }

        for (int i = 0; i < arraySize; ++i)
            if (wParam == MENU_COMMAND + i)
            {
                if (pLong)
                    pLong->SetCurrentAssociation(strArray[i]);

                break;
            }

        // change the necessary calculated and number fields
        pDocument->ChangeFieldForCalculation();
        pDocument->UpdateAllViews(NULL);

        // recalculate
        pWnd->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenu1Selectobject()
    {}
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenu1Unselectobject()
    {
        PSS_Document* pDoc = GetDocument();

        if (!pDoc)
            return;

        PSS_PlanFinObject* pObj;

        // search wich element is selected
        if ((pObj = pDoc->GetHead()) == NULL)
            return;

        do
        {
            if (pObj->IsObjectSelected())
            {
                // translate the point in logical coordinates
                CDC* pDC = GetDC();
                PSS_Assert(pDC);
                OnPrepareDC(pDC);

                pObj->SelectObject(this, pDC, FALSE);
                VERIFY(ReleaseDC(pDC));

                break;
            }
        }
        while ((pObj = pDoc->GetNext()) != NULL);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnClearSelectionAll(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        CDC* pDC = GetDC();
        PSS_Assert(pDC);
        OnPrepareDC(pDC);

        DeselectAllObject(this, pDC, pDocument);
        VERIFY(ReleaseDC(pDC));

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnPointerSelection(WPARAM wParam, LPARAM lParam)
    {
        TRACE("On Pointer In Selection PSS_View 1\n");

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        if (PSS_App::GetApp()->GetCurrentDocument() != pDocument || IsKindOf(RUNTIME_CLASS(PSS_ViewCode)))
            return 0;

        CPoint* pPoint = (CPoint*)lParam;
        ScreenToClient(pPoint);

        // translate the point in logical coordinates
        CDC* pDC = GetDC();
        PSS_Assert(pDC);
        OnPrepareDC(pDC);
        pDC->DPtoLP(pPoint);

        PSS_PlanFinObject* pObj = FindHitObject(*pPoint);

        if (m_pOldPointerSelectedObj && pObj != m_pOldPointerSelectedObj)
        {
            // clear the old object
            m_pOldPointerSelectedObj->DisplayCodeName(pDC, this, FALSE, this);
            m_pOldPointerSelectedObj = NULL;
        }

        if (pObj && pObj != m_pOldPointerSelectedObj)
        {
            pObj->DisplayCodeName(pDC, this);
            m_pOldPointerSelectedObj = pObj;
        }

        TRACE("On Pointer In Selection PSS_View 2\n");
        VERIFY(ReleaseDC(pDC));

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnPointerHasSelected(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        if (PSS_App::GetApp()->GetCurrentDocument() != pDocument || IsKindOf(RUNTIME_CLASS(ZIViewCode)))
            return(0);

        // translate the point in logical coordinates
        CDC* pDC = GetDC();
        PSS_Assert(pDC);
        OnPrepareDC(pDC);

        PSS_FieldObserverMsg msg(UM_NOTIFY_POINTEROBJSELECTED, m_pOldPointerSelectedObj);

        PSS_Subject* pSubject = dynamic_cast<PSS_Subject*>(::AfxGetMainWnd());

        if (pSubject)
            pSubject->NotifyAllObservers(&msg);

        // clear the old object
        if (m_pOldPointerSelectedObj)
        {
            m_pOldPointerSelectedObj->DisplayCodeName(pDC, this, FALSE, this);
            m_pOldPointerSelectedObj = NULL;
        }

        VERIFY(ReleaseDC(pDC));

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnFieldEditNext(WPARAM wParam, LPARAM lParam)
    {
        return PostMessage(ID_PROCESS_FIELD_EDITNEXT, 0, lParam);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnDeselectAllObjects(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        CDC* pDC = GetDC();
        PSS_Assert(pDC);
        OnPrepareDC(pDC);

        PSS_Document* pDoc = pDocument;
        PSS_Assert(pDoc);

        PSS_PlanFinObject* pObj;

        // search wich element is selected
        if ((pObj = pDoc->GetHead()) == NULL)
            return 1;

        do
        {
            if (pObj->IsObjectSelected())
                pObj->SelectObject(this, pDC, FALSE);
        }
        while ((pObj = pDoc->GetNext()) != NULL);

        VERIFY(ReleaseDC(pDC));

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnInsertFile()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        CString title;
        VERIFY(title.LoadString(IDS_SELECT_A_FILE));

        // set the "*.*" files filter
        CString filters;
        VERIFY(filters.LoadString(AFX_IDS_ALLFILTER));
        filters += char('\0');
        filters += _T("*.*");
        filters += char('\0');

        PSS_FileDialog fileDialog(title, filters, 1);

        if (fileDialog.DoModal() == IDOK)
            pDocument->InsertBinaryDocument(fileDialog.GetFileName());
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateInsertFile(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        pCmdUI->Enable(!pDocument->IsReadOnlyAtRuntime());
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnObjectProperty(WPARAM wParam, LPARAM lParam)
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return 1;

        // check read-only mode
        if (pDocument->IsReadOnlyAtRuntime())
            return 1;

        PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)lParam;

        if (pObj)
        {
            // todo FIXME -cFeature -oJean: This property class seems to be no longer used. Check which class is matching now
            ZIProperty prop(pObj, pObj->GetPropertyTabs(), PropertyTabGeneral);

            if (prop.DoModal() == IDOK)
                pDocument->SetModifiedFlag();

            SetFocus();
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldPositionSize()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // todo FIXME -cFeature -oJean: This property class seems to be no longer used. Check which class is matching now
        ZIProperty prop(pObj, pObj->GetPropertyTabs(), PropertyTabSize);

        if (prop.DoModal() == IDOK)
        {
            pDocument->SetModifiedFlag();
            UpdateWindow();
        }

        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldProperty()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject *pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIProperty prop(pObj, pObj->GetPropertyTabs(), PropertyTabGeneral);

        if (prop.DoModal() == IDOK)
        {
            pDocument->SetModifiedFlag();
            UpdateWindow();
        }

        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnWizardCreateFormula()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_DocumentReadWrite* pDoc = dynamic_cast<PSS_DocumentReadWrite*>(pDocument);

        if (pDoc)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_WizardFormulaCreation dlgWizard(pObj);
        dlgWizard.DoModal();

        // unselect the current object
        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenu1Fontchange()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        LOGFONT lf;
        std::memset(&lf, 0, sizeof(LOGFONT));

        PSS_Font* pFont = NULL;

        // if a font is already defined
        if (pObj->GetFont() != g_NoFontDefined)
        {
            pFont = pDocument->GetFontManager().GetFont(pObj->GetFont());
            pFont->GetObject(sizeof(LOGFONT), &lf);
        }

        // init the dialog
        CFontDialog dlgFont(&lf, CF_EFFECTS | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT);

        if (pFont)
            dlgFont.m_cf.rgbColors = pFont->GetFontColor();

        // show the dialog
        if (dlgFont.DoModal() == IDOK)
        {
            PSS_Font::FontHandle hFont = pDocument->GetFontManager().SearchFont(&lf, dlgFont.GetColor());

            if (hFont == g_NoFontDefined)
            {
                PSS_Font* pNewFont = new PSS_Font();
                pNewFont->Create(&lf, dlgFont.GetColor());
                hFont = pDocument->GetFontManager().AddFont(pNewFont);
            }

            pObj->SetFont(hFont);

            // to notify the view about field change, pass the adress of the object, so the routine that proceed
            // the message can know which object has changed
            pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

            // update all views, it's may be a little bit longer but the dialog will be repainted
            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenu1Fontchange(CCmdUI* pCmdUI)
    {}
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuFormat()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        int  result;

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        const BOOL calculated = (pLong && pLong->IsCalculatedField());

        // clone the object
        PSS_PlanFinObject* pTemporaryObject;
        PLFNAutoNumbered*  pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            pTemporaryObject = ((PSS_PlanFinObject*)pAutoNumbered->GetObject())->Clone();
        else
            pTemporaryObject = pObj->Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        // call the wizard
        ZIWZFormat dlgWizard(pTemporaryObject, NULL, TRUE);

        // initialize variable
        dlgWizard.SetFieldValue(pTemporaryObject->GetFormattedObject());

        if ((result = dlgWizard.DoModal()) == IDCANCEL)
        {
            delete pTemporaryObject;

            // unselect all objects
            pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
            return;
        }

        // set the changed variable
        pTemporaryObject->ConvertFormattedObject(dlgWizard.GetFieldValue());

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            ((PSS_PlanFinObject*)pAutoNumbered->GetObject())->CopyObject(pTemporaryObject);
        else
            // set the changed variable, copy the temporary object to the initial object
            pObj->CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, (LPARAM)pObj);

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        // updata all views, it's may be a little bit longer but the dialog will be repainted
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuModifyFormula()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        // must be a calculated number field
        if (!pLong || !pLong->IsCalculatedField())
            return;

        PSS_PlanFinObject* pTemporaryObject = pObj->Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIWZFormula formula(pTemporaryObject, NULL, TRUE);

        if (formula.DoModal() == IDCANCEL)
        {
            delete pTemporaryObject;
            return;
        }

        // set the changed variable, copy the temporary object to the initial object
        pObj->CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

        if (PSS_App::GetApp()->IsAutoCalculate())
            pWnd->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubMenuFormat(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            pCmdUI->Enable(TRUE);
            return;
        }

        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, replace the object by the pointed object
        if (pAutoNumbered)
            pObj = (PSS_PlanFinObject*)pAutoNumbered->GetObject();

        // this wizard is available for long, time and auto numbered fields
        pCmdUI->Enable(pObj->IsKindOf(RUNTIME_CLASS(PLFNLong)) || pObj->IsKindOf(RUNTIME_CLASS(PLFNTime)));
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuAlign(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            pCmdUI->Enable(TRUE);
            return;
        }

        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, replace the object by the pointed object
        if (pAutoNumbered)
            pObj = (PSS_PlanFinObject*)pAutoNumbered->GetObject();

        // check the class type for the wizard, not all classes can be used for the wizard
        pCmdUI->Enable(pObj->IsKindOf(RUNTIME_CLASS(PLFNTime))        ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNBoundText))   ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNNumbEdit))    ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNString))      ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNNumHistory))  ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNNumbNumEdit)) ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNLong))        ||
                       pObj->IsKindOf(RUNTIME_CLASS(PLFNStringHistory)));
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuModifyFormula(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            pCmdUI->Enable(TRUE);
            return;
        }

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        pCmdUI->Enable(pLong && pLong->IsCalculatedField());
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuAlign()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // clone the object
        PSS_PlanFinObject* pTemporaryObject;
        PLFNAutoNumbered*  pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            pTemporaryObject = ((PSS_PlanFinObject*)pAutoNumbered->GetObject())->Clone();
        else
            pTemporaryObject = pObj->Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        // call the wizard
        PSS_WZAlign dlgWizard(pTemporaryObject, NULL, TRUE);

        // initialize variable
        if (dlgWizard.DoModal() == IDCANCEL)
        {
            delete pTemporaryObject;

            // unselect all objects
            pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
            return;
        }

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            ((PSS_PlanFinObject*)pAutoNumbered->GetObject())->CopyObject(pTemporaryObject);
        else
            // set the changed variable, copy the temporary object to the initial object
            pObj->CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuHidePrtObject()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        pObj->SetMustBePrinted(!pObj->GetMustBePrinted());
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuHidePrtObject(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (pObj)
        {
            pCmdUI->Enable(pObj->GetIsVisible());
            pCmdUI->SetCheck(!pObj->GetMustBePrinted());
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuObjectHide()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        pObj->SetIsVisible(!pObj->GetIsVisible());
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuObjectHide(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (pObj)
        {
            pCmdUI->Enable(pObj->GetMustBePrinted());
            pCmdUI->SetCheck(!pObj->GetIsVisible());
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuChangeColor()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIColorSelection ColorSelection(pObj->GetColor(this));
        ColorSelection.ChooseColor();

        if (ColorSelection.ColorHasChanged())
        {
            pObj->SetColor(ColorSelection.GetColor());
            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnWizardFormat()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_DocumentReadWrite* pDoc = dynamic_cast<PSS_DocumentReadWrite*>(pDocument);
        
        if (!pDoc)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_WizardFormatStart dlgWizard;
        dlgWizard.DoModal();

        // unselect the current object
        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnWizardCalculated()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_DocumentReadWrite* pDoc = dynamic_cast<PSS_DocumentReadWrite*>(pDocument);
        PSS_Assert(pDoc);

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        if (pLong && pLong->IsCalculatedField())
        {
            // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
            PSS_WizardCalculated dlgWizard;
            dlgWizard.DoModal();
        }

        // unselect the current object
        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldAlignCenter()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetEditedObject();

        if (!pObj)
            if (!(pObj = pDocument->GetSelectedObject()))
            {
                // call the selector tool
                pObj = ChooseObject();

                if (!pObj)
                    return;
            }

        pObj->SetJustify(pObj->GetJustify(pDocument) & ~DT_RIGHT | DT_CENTER);
        Invalidate(TRUE);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldAlignLeft()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetEditedObject();

        if (!pObj)
            if (!(pObj = pDocument->GetSelectedObject()))
            {
                // call the selector tool
                pObj = ChooseObject();

                if (!pObj)
                    return;
            }

        pObj->SetJustify(pObj->GetJustify(pDocument) & ~DT_CENTER & ~DT_RIGHT);
        Invalidate(TRUE);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldAlignRight()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetEditedObject();

        if (!pObj)
            if (!(pObj = pDocument->GetSelectedObject()))
            {
                // call the selector tool
                pObj = ChooseObject();

                if (!pObj)
                    return;
            }

        pObj->SetJustify(pObj->GetJustify(pDocument) & ~DT_CENTER | DT_RIGHT);
        Invalidate(TRUE);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
    //---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateFieldAlignCenter(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetEditedObject();

        if (pObj)
            pCmdUI->SetCheck((pObj->GetJustify(pDocument) & DT_CENTER) > 0);
        else
            pCmdUI->SetCheck(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateFieldAlignLeft(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetEditedObject();

        if (pObj)
            pCmdUI->SetCheck((!(pObj->GetJustify(pDocument) & DT_CENTER) &&
                              !(pObj->GetJustify(pDocument) & DT_RIGHT)));
        else
            pCmdUI->SetCheck(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateFieldAlignRight(CCmdUI* pCmdUI)
    {
        if (!pCmdUI)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetEditedObject();

        if (pObj)
            pCmdUI->SetCheck((pObj->GetJustify(pDocument) & DT_RIGHT) > 0);
        else
            pCmdUI->SetCheck(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldApplyRounded()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        if (!pObj->IsKindOf(RUNTIME_CLASS(PLFNLong)))
            return;

        PSS_PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        if (!pLong || !pLong->IsCalculatedField())
            return;

        PSS_PlanFinObject* pTemporaryObject = pObj->Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_WZRounded rounded(pTemporaryObject, NULL, TRUE);

        if (rounded.DoModal() == IDCANCEL)
        {
            delete pTemporaryObject;
            return;
        }

        // set the changed variable, copy the temporary object to the initial object
        pObj->CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, (LPARAM)pObj);

        if (PSS_App::GetApp()->IsAutoCalculate())
            pWnd->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        Invalidate(TRUE);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
void PSS_ModifyView::OnSubmenuChangeFillcolor()
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return;

    PSS_Document* pDocument = GetDocument();

    if (!pDocument)
        return;

    PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

    if (!pObj)
    {
        // call the selector tool
        pObj = ChooseObject();

        if (!pObj)
            return;
    }

    // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
    PSS_ColorSelection colorSelection(pObj->GetFillColor());
    colorSelection.ChooseColor();

    if (colorSelection.ColorHasChanged())
    {
        pObj->SetFillColor(colorSelection.GetColor());
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag(TRUE);
    }

    // unselect all objects
    pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
}
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionAlign()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PSS_PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

        // if not auto-numbered, return
        if (!pAutoNumbered)
            return;

        // Clone the object
        PSS_PlanFinObject* pTemporaryObject = pAutoNumbered->GetTextLevel().Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        // call the Wizard
        PSS_WZAlign dlgWizard(pTemporaryObject, NULL, TRUE);

        // initialize variable
        if (dlgWizard.DoModal() == IDCANCEL)
        {
            delete pTemporaryObject;

            // unselect all objects
            pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
            return;
        }

        // set the changed variable, copy the temporary object to the initial object
        pAutoNumbered->GetTextLevel().CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        pDocument->UpdateAllViews(NULL);
        pDocument->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionChangeStyle()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // Call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PSS_PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

        // if not auto-numbered, return
        if (!pAutoNumbered)
            return;

        // replace the pObj by the pointed object
        pObj = &pAutoNumbered->GetTextLevel();

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_SelectStyleDlg selectStyleDlg;

        if (selectStyleDlg.DoModal() == IDOK)
        {
            pObj->SetStyle(selectStyleDlg.GetSelectedStyle());

            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag();
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionChangeColor()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // Call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if not auto-numbered, return
        if (!pAutoNumbered)
            return;

        // replace the pObj by the pointed object
        pObj = &pAutoNumbered->GetTextLevel();

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_ColorSelection colorSelection(pObj->GetColor(this));
        colorSelection.ChooseColor();

        if (colorSelection.ColorHasChanged())
        {
            pObj->SetColor(colorSelection.GetColor());

            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionChangeFillColor()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PSS_PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

        // if not auto-numbered, return
        if (!pAutoNumbered)
            return;

        // replace the pObj by the pointed object
        pObj = &pAutoNumbered->GetTextLevel();

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_ColorSelection colorSelection(pObj->GetFillColor());
        colorSelection.ChooseColor();

        if (colorSelection.ColorHasChanged())
        {
            pObj->SetFillColor(colorSelection.GetColor());

            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionFontChange()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // Call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PSS_PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

        // if not auto-numbered, return
        if (!pAutoNumbered)
            return;

        // replace the object by the pointed object
        pObj = &pAutoNumbered->GetTextLevel();

        LOGFONT lf;
        std::memset(&lf, 0, sizeof(LOGFONT));

        PSS_Font* pFont = NULL;

        // if a font is already defined
        if (pObj->GetFont() != g_NoFontDefined)
        {
            pFont = pDocument->GetFontManager().GetFont(pObj->GetFont());
            pFont->GetObject(sizeof(LOGFONT), &lf);
        }

        // init the dialog
        CFontDialog dlgFont(&lf, CF_EFFECTS | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT);

        if (pFont)
            dlgFont.m_cf.rgbColors = pFont->GetFontColor();

        // show the dialog
        if (dlgFont.DoModal() == IDOK)
        {
            PSS_Font::FontHandle hFont = pDocument->GetFontManager().SearchFont(&lf, dlgFont.GetColor());

            if (hFont == g_NoFontDefined)
            {
                PSS_Font* pNewFont = new PSS_Font();

                pNewFont->Create(&lf, dlgFont.GetColor());
                hFont = pDocument->GetFontManager().AddFont(pNewFont);
            }

            pObj->SetFont(hFont);

            // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
            // can know which object has changed
            pWnd->SendMessageToDescendants(ID_FIELD_CHANGE, 0, (LPARAM)pObj);

            // update all views, it's may be a little bit longer but already the dialog should be repainted
            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnChangeBorder()
    {
        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj = pDocument->GetSelectedObject();

        if (!pObj)
        {
            // Call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PSS_Border* pBorder                   = pObj->GetBorder();
        BOOL        newBorderHasBeenAllocated = FALSE;

        // no border defined for the object
        if (!pBorder)
        {
            // If no border defined, allocates one
            newBorderHasBeenAllocated = TRUE;

            std::unique_ptr<PSS_Border> pNewBorder(new PSS_Border());
            pObj->SetBorder(pNewBorder.get());
            pBorder = pNewBorder.release();
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_BorderDefDlg borderDefDlg(pBorder);

        // show the border dialog box
        if (borderDefDlg.DoModal() == IDCANCEL)
        {
            // if the user cancel the border definition, and one object has been temporarily allocated, delete it
            if (newBorderHasBeenAllocated)
            {
                delete pBorder;
                pObj->SetBorder(NULL);
            }
        }
        else
        {
            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag();
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnChangeLineColor()
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        PSS_Document* pDocument = GetDocument();

        if (!pDocument)
            return;

        PSS_PlanFinObject* pObj     = pDocument->GetSelectedObject();
        PSS_PLFNGraphic*   pGraphic = dynamic_cast<PLFNGraphic*>(pObj);

        if (!pGraphic)
        {
            // call the selector tool
            pGraphic = dynamic_cast<PLFNGraphic*>(ChooseObject());

            if (!pGraphic)
                return;
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        PSS_ColorSelection colorSelection(pGraphic->GetGraphicColor());
        colorSelection.ChooseColor();

        if (colorSelection.ColorHasChanged())
        {
            pGraphic->SetGraphicColor(colorSelection.GetColor());

            pDocument->UpdateAllViews(NULL);
            pDocument->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
