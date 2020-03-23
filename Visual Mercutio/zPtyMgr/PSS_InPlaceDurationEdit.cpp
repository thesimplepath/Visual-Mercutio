/****************************************************************************
 * ==> PSS_InPlaceDurationEdit ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place duration edit                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceDurationEdit.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_MenuObserverMsg.h"
#include "zProperty\PSS_PropertyItem.h"
#include "PSS_PropertyListCtrl.h"
#include "PSS_InputDurationDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlaceDurationEdit, PSS_SearchEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceDurationEdit, PSS_SearchEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceDurationEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceDurationEdit
//---------------------------------------------------------------------------
PSS_InPlaceDurationEdit::PSS_InPlaceDurationEdit(const PSS_InPlaceDurationEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceDurationEdit& PSS_InPlaceDurationEdit::operator = (const PSS_InPlaceDurationEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDurationEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                        const CString&    initText,
                                                        CWnd*             pWndParent,
                                                        const CRect&      rect,
                                                        DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 1);

    SetEditText(initText);

    // save the initial value
    m_StrInitialValue = initText;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_String;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDurationEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem*   pItem,
                                                        const PSS_Duration& durationInitValue,
                                                        CWnd*               pWndParent,
                                                        const CRect&        rect,
                                                        DWORD               exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 1);

    SetEditText(durationInitValue);

    // save the initial value
    m_InitialDurationValue = durationInitValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_Duration;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceDurationEdit::GetEditText() const
{
    CString text;

    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(text);

    return text;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::SetEditText(const CString& strText)
{
    m_StrValue = strText;

    if (::IsWindow(GetSafeHwnd()))
        SetWindowText(strText);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::SetEditText(const PSS_Duration& durationValue)
{
    // set the duration value
    m_DurationValue = durationValue;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_DurationValue, m_pItem->GetStringFormat());
    SetEditText(initText);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceDurationEdit::IsEditCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case PSS_InPlaceEdit::IE_T_String:
            // set back the initial value
            SetEditText(m_StrInitialValue);
            break;

        case PSS_InPlaceEdit::IE_T_Duration:
            // set back the initial duration value
            SetEditText(m_InitialDurationValue);
            break;
    }

    // Set the focus to properties control
    SetFocus();

    // Reset the has changed value
    SetHasChanged(false);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::SaveValue()
{
    if (GetHasChanged())
    {
        PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

        if (pParent)
        {
            CString proposedValue = GetEditText();

            // process the data
            if (m_pItem)
            {
                bool conversionCorrect = true;

                switch (GetEditType())
                {
                    case PSS_InPlaceEdit::IE_T_String:
                        // do nothing for string
                        break;

                    case PSS_InPlaceEdit::IE_T_Duration:
                    {
                        // check the conversion
                        PSS_Duration value;
                        conversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(proposedValue,
                                                                                        value,
                                                                                        m_pItem->GetStringFormat());

                        if (!conversionCorrect)
                            CancelEdit();

                        break;
                    }
                }

                // if the conversion succeeded and the value is checked, save the edit value
                if (conversionCorrect && pParent->CheckCurrentPropertyData(m_pItem, proposedValue))
                {
                    // notify that the property item changed
                    m_pItem->SetHasChanged();

                    // notify observers about the changed value
                    PSS_ToolbarObserverMsg msg(WM_VALUESAVED_EDIT);
                    NotifyAllObservers(&msg);

                    // reset the changed flag
                    m_HasChanged = false;

                    return;
                }
            }

            // change the window text to the proposed value
            SetEditText(proposedValue);
        }
    }

    // set the focus to the control
    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::OnExtendedCommand()
{
    PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

    // process the extended command
    if (pParent)
    {
        PSS_PropertyItem* pItem = pParent->GetCurrentPropertyItem();

        CString proposedValue = GetEditText();

        // save the value
        SaveValue();

        // the extended duration function is handled internally, the standard duration dialog should be owned by the caller
        if (pItem)
        {
            PSS_Duration value;
            bool         conversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(proposedValue,
                                                                                         value,
                                                                                         pItem->GetStringFormat());

            // check the conversion
            if (conversionCorrect)
            {
                // show the duration dialog and change the window text to the proposed value
                PSS_InputDurationDlg dlg(value.GetDays(), value.GetHours(), value.GetMinutes(), value.GetSeconds());
                dlg.DoModal();

                // set the new duration
                value.SetDuration(dlg.GetDays(), dlg.GetHours(), dlg.GetMinutes(), dlg.GetSeconds());
 
                // format the value using the specified string format
                proposedValue = PSS_StringFormatter::GetFormattedBuffer((PSS_Duration&)value, pItem->GetStringFormat());
                SetEditText(proposedValue);

                // set the changed value
                SetHasChanged(true);
            }
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDurationEdit::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return PSS_SearchEdit::PreTranslateMessage(pMsg);

    if (pMsg->message == WM_KEYDOWN)
        switch (pMsg->wParam)
        {
            case VK_DELETE:
                SetHasChanged(true);
                break;

            case VK_ESCAPE:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);

                // cancel the edit
                CancelEdit();

                PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

                // notify the observers
                if (pParent)
                {
                    pParent->PostMessage(WM_KEYPRESSED_EDIT, pMsg->wParam);
                    return TRUE;
                }

                break;
            }

            case VK_RETURN:
            case VK_TAB:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);

                PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

                // notify the observers
                if (pParent)
                {
                    pParent->PostMessage(WM_KEYPRESSED_EDIT,
                                         (::GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | pMsg->wParam) : pMsg->wParam);
                    return TRUE;
                }

                break;
            }

            default:
                break;
        }

    return PSS_SearchEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_InPlaceDurationEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DoCreateButton(TRUE);

    if (PSS_SearchEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);

    CWnd* pParent = GetParent();
    ASSERT(pParent);

    CFont* pFont   = pParent->GetFont();
    DWORD  dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;

    SetFont(pFont);

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDurationEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // set the changed flag
    m_HasChanged = true;

    // call the base function
    PSS_SearchEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDurationEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_SearchEdit::OnSetFocus(pOldWnd);
}
//---------------------------------------------------------------------------
