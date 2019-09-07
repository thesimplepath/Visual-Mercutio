/****************************************************************************
 * ==> PSS_ModifyView ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify view                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ModifyView.h"

// processsoft
#include "zBaseLib\ZIViewCd.h"
#include "zBaseLib\PSS_VisualTool.h"
#include "zBaseLib\PSS_PLFNCheckBtn.h"
#include "zBaseLib\ZARadio.h"
#include "zBaseLib\PSS_PLFNAutoNumbered.h"
#include "zBaseLib\ZASquare.h"
#include "zBaseLib\PSS_PLFNBoundText.h"
#include "zBaseLib\PSS_PLFNBitmap.h"
#include "zBaseLib\PSS_PLFNMultiColumn.h"
#include "zBaseLib\PSS_PLFNMaskString.h"
#include "zBaseLib\PSS_Edit.h"
#include "zBaseLib\PSS_ObjectUtility.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\ZBFieldObserverMsg.h"
#include "zWinUtil32\PSS_CalendarWindowDialog.h"
#include "zWinUtil32\PSS_ObjectNotesDialog.h"
#include "DocWrite.h"
#include "ZAApp.h"

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
#include "Resource.h"

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
        ON_COMMAND(ID_WIZARD_MODIFYfORMULA, OnSubmenuModifyFormula)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU_FORMAT, OnUpdateSubMenuFormat)
        ON_UPDATE_COMMAND_UI(ID_SUBMENU1_ALIGN, OnUpdateSubmenuAlign)
        ON_UPDATE_COMMAND_UI(ID_WIZARD_MODIFYfORMULA, OnUpdateSubmenuModifyFormula)
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
    m_ViewType = FormModifyView;

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
void PSS_ModifyView::EditObject(PlanFinObject* pObj)
{
    CDC* pDC = GetDC();
    ASSERT(pDC);

    OnPrepareDC(pDC);
    DeselectAllObject(this, pDC, GetDocument());

    // delete the existing edit control
    if (GetDocument()->GetEditControl())
    {
        delete GetDocument()->GetEditControl();
        GetDocument()->AssignEditControl(NULL);
    }

    GetDocument()->AssignEditControl(CreateEditControl(pObj, pDC));

    // control was successfully created?
    if (GetDocument()->GetEditControl())
    {
        GetDocument()->GetEditControl()->Create(PSS_Global::IsFormDesigner(),
                                                this,
                                                pDC,
                                                GetDocument(),
                                                pObj,
                                                ZAApp::ZAGetApp()->GetFieldRepository(),
                                                ZAApp::ZAGetApp()->IsAutoCalculate(),
                                                ZAApp::ZAGetApp()->GoNextEdit());

        GetDocument()->SetModifiedFlag(TRUE);
    }

    VERIFY(ReleaseDC(pDC));
}
//---------------------------------------------------------------------------
PSS_Edit* PSS_ModifyView::CreateEditControl(PlanFinObject* pObj, CDC* pDC)
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
            PLFNSquare* pSquare = dynamic_cast<PLFNSquare*>(pObj);

            if (pSquare && pSquare->GetpObject())
                return CreateEditControl(const_cast<PlanFinObject*>(pSquare->GetpObject()), pDC);

            return NULL;
        }

        case IDS_NUMBEREDSECTION_CLASS:
        {
            PSS_PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

            if (pAutoNumbered && pAutoNumbered->GetObject())
                return CreateEditControl(const_cast<PlanFinObject*>(pAutoNumbered->GetObject()), pDC);

            return NULL;
        }

        case IDS_CHECK_CLASS:
        {
            PSS_PLFNCheckBtn* pCheck = dynamic_cast<PSS_PLFNCheckBtn*>(pObj);

            if (pCheck)
            {
                pCheck->EditObject(this, pDC, GetDocument());
                GetDocument()->SetModifiedFlag(TRUE);
            }

            return NULL;
        }

        case IDS_RADIO_CLASS:
        {
            PLFNRadio* pRadio = dynamic_cast<PLFNRadio*>(pObj);

            if (pRadio)
            {
                pRadio->EditObject(this, pDC, GetDocument());
                GetDocument()->SetModifiedFlag(TRUE);
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
void PSS_ModifyView::AddObjectNotes(PlanFinObject* pObj)
{
    if (!pObj)
        return;

    PSS_ObjectNotesDialog objectNotesDialog(pObj->GetNotesPointer() ? pObj->GetNotesPointer()->GetComment()  : _T(""),
                                            pObj->GetNotesPointer() ? pObj->GetNotesPointer()->GetUsername() : _T(""));

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
    if (!ZAApp::ZAGetApp()->IsCursorCapturedValid(point, this))
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
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
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
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return;

        ZDDocumentReadWrite* pDoc = dynamic_cast<ZDDocumentReadWrite*>(GetDocument());
        ASSERT(pDoc);

        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return;

        PlanFinObject *pObj = GetDocument()->GetSelectedObject();

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
        GetDocument()->SetModifiedFlag();
        RedrawWindow();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateEditionProtectObject(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        GetDocument()->CalculateAllFormula(this, TRUE);

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnProcessFieldEditNext(WPARAM wParam, LPARAM lParam)
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject*       pObj                  = (PlanFinObject*)lParam;
        PlanFinObject*       pNextEditObj          = NULL;
        double               currentEditedTabOrder = pObj->GetTabOrder();
        ZDDocumentReadWrite* pDoc                  = dynamic_cast<ZDDocumentReadWrite*>(GetDocument());
        ASSERT(pDoc);

        if (!pDoc->GetEditedObject() || !pObj)
            return 1;

        // get the current page
        const int page = pDoc->GetCurrentPage();

        PlanFinObject* pObjTemp  = NULL;
        POSITION       pPosition = pDoc->GetObjectList().GetHeadPosition();

        while (!pPosition)
        {
            pObjTemp = (PlanFinObject*)pDoc->GetObjectList().GetNext(pPosition);

            // if the same object, continue
            if (pObj == pObjTemp)
                continue;

            // iterate throught objects and find the next editable object within the same page
            if (page == pObjTemp->GetObjectPage())
            {
                // skip non editable object
                if (pObjTemp->IsReadOnlyAtRuntime()               ||
                    pObjTemp->GetIsStatic()                       ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PLFNStatic)) ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PLFNCheck))  ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PLFNRadio))  ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PLFNLine))   ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PLFNRect))   ||
                    pObjTemp->IsKindOf(RUNTIME_CLASS(PLFNNumbered)))
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
            ASSERT(pDC);
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
        // to all document data
        if (GetDocument() && lParam)
            GetDocument()->PropagateFieldValue((PlanFinObject*)lParam, -2);

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
            PlanFinObject* pObject = FindHitObject(cursorPos);

            if (pObject)
            {
                // adjust the text by filling in TOOLTIPTEXT
                m_StrToolTip.ReleaseBuffer();
                m_StrToolTip = m_ToolTipTypeObject + PSS_ObjectUtility::GetClassName(pObject);

                if (ZAApp::ZAGetApp()->GetFieldRepository())
                {
                    ZAObjectDefinition* pObjectDefinition = 
                            ZAApp::ZAGetApp()->GetFieldRepository()->FindField(pObject->GetObjectName());

                    if (pObjectDefinition && !pObjectDefinition->GetHelpUserDescription().IsEmpty())
                    {
                        m_StrToolTip += _T("\n");
                        m_StrToolTip += pObjectDefinition->GetHelpUserDescription();
                    }
                }

                if (pObject->GetNotesPointer())
                {
                    m_StrToolTip += _T("\n") + m_ToolTipNoteText;

                    if (!pObject->GetNotesPointer()->GetUsername().IsEmpty())
                        m_StrToolTip += _T("[") + pObject->GetNotesPointer()->GetUsername() + _T("]");

                    m_StrToolTip += _T("\n") + pObject->GetNotesPointer()->GetComment();
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
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return;

        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        AddObjectNotes(pObj);

        OnSubmenu1Unselectobject();
        GetDocument()->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnDeleteObjectNotes()
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return;

        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj || !pObj->GetNotesPointer())
            return;

        pObj->DeleteNotes();
        OnSubmenu1Unselectobject();
        GetDocument()->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateDeleteObjectNotes(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (pObj)
            pCmdUI->Enable(pObj->GetNotesPointer() != NULL);
        else
            pCmdUI->Enable(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnEmptyObject(WPARAM wParam, LPARAM lParam)
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject* pObj = (PlanFinObject*)lParam;

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
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject* pObj = (PlanFinObject*)lParam;

        HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_WIZARDMENU), RT_MENU);

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

        // show the menu
        ::TrackPopupMenu(subMenu,
                         TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                         point.x,
                         point.y,
                         0,
                         AfxGetMainWnd()->GetSafeHwnd(),
                         NULL);

        SetCapture();

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnCalendarObject(WPARAM wParam, LPARAM lParam)
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject* pObj = (PlanFinObject*)lParam;

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

                // to notify the view about field change, pass the adress of the object, so the routine
                // that proceed the message can know which object has changed
                AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));
                GetDocument()->SetModifiedFlag();
            }
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnObjectNote(WPARAM wParam, LPARAM lParam)
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject* pObj = (PlanFinObject*)lParam;

        if (pObj)
            AddObjectNotes(pObj);

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnAssociationMenu(WPARAM wParam, LPARAM lParam)
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject* pObj = (PlanFinObject*)lParam;

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

            associationMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd());
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

        PlanFinObject*    pObj      = GetDocument()->GetSelectedObject();
        CStringArray&     strArray  = ((PLFNLong*)pObj)->GetAssociations().GetAssociationArray();
        const std::size_t arraySize = strArray.GetSize();
        PLFNLong*         pLong     = dynamic_cast<PLFNLong*>(pObj);

        // check if the standard schema is selected
        if (arraySize == wParam - MENU_COMMAND)
        {
            if (pLong)
                pLong->SetCurrentAssociation(NULL);

            // change the necessary calculated and number fields
            GetDocument()->ChangeFieldForCalculation();
            GetDocument()->UpdateAllViews(NULL);

            // recalculate
            AfxGetMainWnd()->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);
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
        GetDocument()->ChangeFieldForCalculation();
        GetDocument()->UpdateAllViews(NULL);

        // recalculate
        AfxGetMainWnd()->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

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
        ZDDocument* pDoc = GetDocument();
        ASSERT(pDoc);
        PlanFinObject* pObj;

        // search wich element is selected
        if ((pObj = pDoc->GetHead()) == NULL)
            return;

        do
        {
            if (pObj->IsSelectObject())
            {
                // translate the point in logical coordinates
                CDC* pDC = GetDC();
                ASSERT(pDC);
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
        CDC* pDC = GetDC();
        ASSERT(pDC);
        OnPrepareDC(pDC);

        DeselectAllObject(this, pDC, GetDocument());
        VERIFY(ReleaseDC(pDC));

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnPointerSelection(WPARAM wParam, LPARAM lParam)
    {
        TRACE(_T(" On Pointer In Selection ZIView 1 "));

        if (ZAApp::ZAGetApp()->GetCurrentDocument() != GetDocument() || IsKindOf(RUNTIME_CLASS(ZIViewCode)))
            return 0;

        CPoint* pPoint = (CPoint*)lParam;
        ScreenToClient(pPoint);

        // translate the point in logical coordinates
        CDC* pDC = GetDC();
        ASSERT(pDC);
        OnPrepareDC(pDC);
        pDC->DPtoLP(pPoint);

        PlanFinObject* pObj = FindHitObject(*pPoint);

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

        TRACE(_T(" On Pointer In Selection ZIView 2 "));
        VERIFY(ReleaseDC(pDC));

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnPointerHasSelected(WPARAM wParam, LPARAM lParam)
    {
        if (ZAApp::ZAGetApp()->GetCurrentDocument() != GetDocument() || IsKindOf(RUNTIME_CLASS(ZIViewCode)))
            return(0);

        // translate the point in logical coordinates
        CDC* pDC = GetDC();
        ASSERT(pDC);
        OnPrepareDC(pDC);

        ZBFieldObserverMsg msg(UM_NOTIFY_POINTEROBJSELECTED, m_pOldPointerSelectedObj);

        ZISubject* pSubject = dynamic_cast<ZISubject*>(AfxGetMainWnd());

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
        CDC* pDC = GetDC();
        ASSERT(pDC);
        OnPrepareDC(pDC);

        ZDDocument* pDoc = GetDocument();
        ASSERT(pDoc);

        PlanFinObject* pObj;

        // search wich element is selected
        if ((pObj = pDoc->GetHead()) == NULL)
            return 1;

        do
        {
            if (pObj->IsSelectObject())
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
            GetDocument()->InsertBinaryDocument(fileDialog.GetFileName());
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateInsertFile(CCmdUI* pCmdUI)
    {
        pCmdUI->Enable(!GetDocument()->IsReadOnlyAtRuntime());
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    afx_msg LONG PSS_ModifyView::OnObjectProperty(WPARAM wParam, LPARAM lParam)
    {
        // check read-only mode
        if (!GetDocument() || GetDocument()->IsReadOnlyAtRuntime())
            return 1;

        PlanFinObject* pObj = (PlanFinObject*)lParam;

        if (pObj)
        {
            // todo FIXME -cFeature -oJean: This property class seems to be no longer used. Check which class is matching now
            ZIProperty prop(pObj, pObj->GetPropertyTabs(), PropertyTabGeneral);

            if (prop.DoModal() == IDOK)
                GetDocument()->SetModifiedFlag();

            SetFocus();
        }

        return 1;
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldPositionSize()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
            GetDocument()->SetModifiedFlag();
            UpdateWindow();
        }

        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldProperty()
    {
        PlanFinObject *pObj = GetDocument()->GetSelectedObject();

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
            GetDocument()->SetModifiedFlag();
            UpdateWindow();
        }

        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnWizardCreateFormula()
    {
        ZDDocumentReadWrite* pDoc = dynamic_cast<ZDDocumentReadWrite*>(GetDocument());
        ASSERT(pDoc);

        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIWizardFormulaCreation dlgWizard(pObj);
        dlgWizard.DoModal();

        // unselect the current object
        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenu1Fontchange()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        LOGFONT lf;
        std::memset(&lf, 0, sizeof(LOGFONT));

        ZAFont* pFont = NULL;

        // if a font is already defined
        if (pObj->GethFont() != NoFontDefined)
        {
            pFont = GetDocument()->GetFontManager().GetFont(pObj->GethFont());
            pFont->GetObject(sizeof(LOGFONT), &lf);
        }

        // init the dialog
        CFontDialog dlgFont(&lf, CF_EFFECTS | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT);

        if (pFont)
            dlgFont.m_cf.rgbColors = pFont->GetFontColor();

        // show the dialog
        if (dlgFont.DoModal() == IDOK)
        {
            HandleFont hFont = GetDocument()->GetFontManager().FindFont(&lf, dlgFont.GetColor());

            if (hFont == NoFontDefined)
            {
                ZAFont* pNewFont = new ZAFont();
                pNewFont->Create(&lf, dlgFont.GetColor());
                hFont = GetDocument()->GetFontManager().AddFont(pNewFont);
            }

            pObj->SethFont(hFont);

            // to notify the view about field change, pass the adress of the object, so the routine that proceed
            // the message can know which object has changed
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

            // update all views, it's may be a little bit longer but the dialog will be repainted
            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
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
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
        PlanFinObject*    pTemporaryObject;
        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            pTemporaryObject = ((PlanFinObject*)pAutoNumbered->GetpObject())->Clone();
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
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
            return;
        }

        // set the changed variable
        pTemporaryObject->ConvertFormattedObject(dlgWizard.GetFieldValue());

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            ((PlanFinObject*)pAutoNumbered->GetpObject())->CopyObject(pTemporaryObject);
        else
            // set the changed variable, copy the temporary object to the initial object
            pObj->CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, (LPARAM)pObj);

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        // updata all views, it's may be a little bit longer but the dialog will be repainted
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuModifyFormula()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        // must be a calculated number field
        if (!pLong || !pLong->IsCalculatedField())
            return;

        PlanFinObject* pTemporaryObject = pObj->Clone();

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
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

        if (ZAApp::ZAGetApp()->IsAutoCalculate())
            AfxGetMainWnd()->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubMenuFormat(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            pCmdUI->Enable(TRUE);
            return;
        }

        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, replace the object by the pointed object
        if (pAutoNumbered)
            pObj = (PlanFinObject*)pAutoNumbered->GetpObject();

        // this wizard is available for long, time and auto numbered fields
        pCmdUI->Enable(pObj->IsKindOf(RUNTIME_CLASS(PLFNLong)) || pObj->IsKindOf(RUNTIME_CLASS(PLFNTime)));
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuAlign(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            pCmdUI->Enable(TRUE);
            return;
        }

        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, replace the object by the pointed object
        if (pAutoNumbered)
            pObj = (PlanFinObject*)pAutoNumbered->GetpObject();

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
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // clone the object
        PlanFinObject*    pTemporaryObject;
        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            pTemporaryObject = ((PlanFinObject*)pAutoNumbered->GetpObject())->Clone();
        else
            pTemporaryObject = pObj->Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        // call the wizard
        ZIWZAlign dlgWizard(pTemporaryObject, NULL, TRUE);

        // initialize variable
        if (dlgWizard.DoModal() == IDCANCEL)
        {
            delete pTemporaryObject;

            // unselect all objects
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
            return;
        }

        // if auto-numbered, pass the pointed object
        if (pAutoNumbered)
            ((PlanFinObject*)pAutoNumbered->GetpObject())->CopyObject(pTemporaryObject);
        else
            // set the changed variable, copy the temporary object to the initial object
            pObj->CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuHidePrtObject()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        pObj->SetbMustBePrinted(!pObj->GetbMustBePrinted());
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuHidePrtObject(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (pObj)
        {
            pCmdUI->Enable(pObj->GetbIsVisible());
            pCmdUI->SetCheck(!pObj->GetbMustBePrinted());
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuObjectHide()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        pObj->SetbIsVisible(!pObj->GetbIsVisible());
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateSubmenuObjectHide(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (pObj)
        {
            pCmdUI->Enable(pObj->GetbMustBePrinted());
            pCmdUI->SetCheck(!pObj->GetbIsVisible());
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSubmenuChangeColor()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnWizardFormat()
    {
        ZDDocumentReadWrite* pDoc = dynamic_cast<ZDDocumentReadWrite*>(GetDocument());
        ASSERT(pDoc);

        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIWizardFormatStart dlgWizard;
        dlgWizard.DoModal();

        // unselect the current object
        OnSubmenu1Unselectobject();
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnWizardCalculated()
    {
        ZDDocumentReadWrite* pDoc = dynamic_cast<ZDDocumentReadWrite*>(GetDocument());
        ASSERT(pDoc);

        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
            ZIWizardCalculated dlgWizard;
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
        PlanFinObject* pObj = GetDocument()->GetEditedObject();

        if (!pObj)
            if (!(pObj = GetDocument()->GetSelectedObject()))
            {
                // call the selector tool
                pObj = ChooseObject();

                if (!pObj)
                    return;
            }

        pObj->SetJustify(pObj->GetJustify(GetDocument()) & ~DT_RIGHT | DT_CENTER);
        Invalidate(TRUE);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldAlignLeft()
    {
        PlanFinObject* pObj = GetDocument()->GetEditedObject();

        if (!pObj)
            if (!(pObj = GetDocument()->GetSelectedObject()))
            {
                // call the selector tool
                pObj = ChooseObject();

                if (!pObj)
                    return;
            }

        pObj->SetJustify(pObj->GetJustify(GetDocument()) & ~DT_CENTER & ~DT_RIGHT);
        Invalidate(TRUE);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldAlignRight()
    {
        PlanFinObject* pObj = GetDocument()->GetEditedObject();

        if (!pObj)
            if (!(pObj = GetDocument()->GetSelectedObject()))
            {
                // call the selector tool
                pObj = ChooseObject();

                if (!pObj)
                    return;
            }

        pObj->SetJustify(pObj->GetJustify(GetDocument()) & ~DT_CENTER | DT_RIGHT);
        Invalidate(TRUE);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
    //---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateFieldAlignCenter(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetEditedObject();

        if (pObj)
            pCmdUI->SetCheck((pObj->GetJustify(GetDocument()) & DT_CENTER) > 0);
        else
            pCmdUI->SetCheck(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateFieldAlignLeft(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetEditedObject();

        if (pObj)
            pCmdUI->SetCheck((!(pObj->GetJustify(GetDocument()) & DT_CENTER) &&
                              !(pObj->GetJustify(GetDocument()) & DT_RIGHT)));
        else
            pCmdUI->SetCheck(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnUpdateFieldAlignRight(CCmdUI* pCmdUI)
    {
        PlanFinObject* pObj = GetDocument()->GetEditedObject();

        if (pObj)
            pCmdUI->SetCheck((pObj->GetJustify(GetDocument()) & DT_RIGHT) > 0);
        else
            pCmdUI->SetCheck(FALSE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnFieldApplyRounded()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        if (!pObj->IsKindOf(RUNTIME_CLASS(PLFNLong)))
            return;

        PLFNLong* pLong = dynamic_cast<PLFNLong*>(pObj);

        if (!pLong || !pLong->IsCalculatedField())
            return;

        PlanFinObject* pTemporaryObject = pObj->Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIWZRounded rounded(pTemporaryObject, NULL, TRUE);

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
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, (LPARAM)pObj);

        if (ZAApp::ZAGetApp()->IsAutoCalculate())
            AfxGetMainWnd()->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        Invalidate(TRUE);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
void PSS_ModifyView::OnSubmenuChangeFillcolor()
{
    PlanFinObject* pObj = GetDocument()->GetSelectedObject();

    if (!pObj)
    {
        // call the selector tool
        pObj = ChooseObject();

        if (!pObj)
            return;
    }

    // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
    ZIColorSelection colorSelection(pObj->GetFillColor());
    colorSelection.ChooseColor();

    if (colorSelection.ColorHasChanged())
    {
        pObj->SetFillColor(colorSelection.GetColor());
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag(TRUE);
    }

    // unselect all objects
    AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
}
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionAlign()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        PLFNAutoNumbered* pAutoNumbered = dynamic_cast<PLFNAutoNumbered*>(pObj);

        // if not auto-numbered, return
        if (!pAutoNumbered)
            return;

        // Clone the object
        PlanFinObject* pTemporaryObject = pAutoNumbered->GetTextLevel().Clone();

        if (!pTemporaryObject)
            return;

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        // call the Wizard
        ZIWZAlign dlgWizard(pTemporaryObject, NULL, TRUE);

        // initialize variable
        if (dlgWizard.DoModal() == IDCANCEL)
        {
            delete pTemporaryObject;

            // unselect all objects
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
            return;
        }

        // set the changed variable, copy the temporary object to the initial object
        pAutoNumbered->GetTextLevel().CopyObject(pTemporaryObject);

        delete pTemporaryObject;

        // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
        // can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pObj));

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);

        // update all views, it's may be a little bit longer but the dialog will be repainted
        GetDocument()->UpdateAllViews(NULL);
        GetDocument()->SetModifiedFlag(TRUE);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionChangeStyle()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
        ZISelectStyleDlg selectStyleDlg;

        if (selectStyleDlg.DoModal() == IDOK)
        {
            pObj->SethStyle(selectStyleDlg.GetSelectedStyle());

            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag();
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionChangeColor()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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
        ZIColorSelection colorSelection(pObj->GetColor(this));
        colorSelection.ChooseColor();

        if (colorSelection.ColorHasChanged())
        {
            pObj->SetColor(colorSelection.GetColor());

            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionChangeFillColor()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // call the selector tool
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
        ZIColorSelection colorSelection(pObj->GetFillColor());
        colorSelection.ChooseColor();

        if (colorSelection.ColorHasChanged())
        {
            pObj->SetFillColor(colorSelection.GetColor());

            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnSectionFontChange()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

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

        // replace the object by the pointed object
        pObj = &pAutoNumbered->GetTextLevel();

        LOGFONT lf;
        std::memset(&lf, 0, sizeof(LOGFONT));

        ZAFont* pFont = NULL;

        // if a font is already defined
        if (pObj->GethFont() != NoFontDefined)
        {
            pFont = GetDocument()->GetFontManager().GetFont(pObj->GethFont());
            pFont->GetObject(sizeof(LOGFONT), &lf);
        }

        // init the dialog
        CFontDialog dlgFont(&lf, CF_EFFECTS | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT);

        if (pFont)
            dlgFont.m_cf.rgbColors = pFont->GetFontColor();

        // show the dialog
        if (dlgFont.DoModal() == IDOK)
        {
            HandleFont hFont = GetDocument()->GetFontManager().FindFont(&lf, dlgFont.GetColor());

            if (hFont == NoFontDefined)
            {
                ZAFont* pNewFont = new ZAFont();

                pNewFont->Create(&lf, dlgFont.GetColor());
                hFont = GetDocument()->GetFontManager().AddFont(pNewFont);
            }

            pObj->SethFont(hFont);

            // to notify the view about field change, pass the adress of the object, so the routine that proceed the message
            // can know which object has changed
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, (LPARAM)pObj);

            // update all views, it's may be a little bit longer but already the dialog should be repainted
            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnChangeBorder()
    {
        PlanFinObject* pObj = GetDocument()->GetSelectedObject();

        if (!pObj)
        {
            // Call the selector tool
            pObj = ChooseObject();

            if (!pObj)
                return;
        }

        ZABorder* pBorder = pObj->GetpBorder();
        BOOL      newBorderHasBeenAllocated = FALSE;

        // no border defined for the object
        if (!pBorder)
        {
            // If no border defined, allocates one
            newBorderHasBeenAllocated = TRUE;

            std::unique_ptr<ZABorder> pNewBorder(new ZABorder());
            pObj->SetpBorder(pNewBorder.get());
            pBorder = pNewBorder.release();
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIBorderDefDlg borderDefDlg(pBorder);

        // show the border dialog box
        if (borderDefDlg.DoModal() == IDCANCEL)
        {
            // if the user cancel the border definition, and one object has been temporarily allocated, delete it
            if (newBorderHasBeenAllocated)
            {
                delete pBorder;
                pObj->SetpBorder(NULL);
            }
        }
        else
        {
            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag();
        }
    }
#endif
//---------------------------------------------------------------------------
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    void PSS_ModifyView::OnChangeLineColor()
    {
        PlanFinObject* pObj     = GetDocument()->GetSelectedObject();
        PLFNGraphic*   pGraphic = dynamic_cast<PLFNGraphic*>(pObj);

        if (!pGraphic)
        {
            // call the selector tool
            pGraphic = dynamic_cast<PLFNGraphic*>(ChooseObject());

            if (!pGraphic)
                return;
        }

        // todo FIXME -cFeature -oJean: This class seems to be no longer used. Check which class is matching now
        ZIColorSelection colorSelection(pGraphic->GetGraphicColor());
        colorSelection.ChooseColor();

        if (colorSelection.ColorHasChanged())
        {
            pGraphic->SetGraphicColor(colorSelection.GetColor());

            GetDocument()->UpdateAllViews(NULL);
            GetDocument()->SetModifiedFlag(TRUE);
        }

        // unselect all objects
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    }
#endif
//---------------------------------------------------------------------------
