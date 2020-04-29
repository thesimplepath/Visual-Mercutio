/****************************************************************************
 * ==> PSS_InPlaceTimeEdit -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place time edit                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceTimeEdit.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_MenuObserverMsg.h"
#include "zProperty\PSS_PropertyItem.h"
#include "PSS_PropertyListCtrl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlaceTimeEdit, PSS_SearchEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceTimeEdit, PSS_SearchEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceTimeEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceTimeEdit
//---------------------------------------------------------------------------
PSS_InPlaceTimeEdit::PSS_InPlaceTimeEdit(const PSS_InPlaceTimeEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceTimeEdit& PSS_InPlaceTimeEdit::operator = (const PSS_InPlaceTimeEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceTimeEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
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
BOOL PSS_InPlaceTimeEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem*   pItem,
                                                    const PSS_TimeSpan& timeInitValue,
                                                    CWnd*               pWndParent,
                                                    const CRect&        rect,
                                                    DWORD               exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 1);

    SetEditText(timeInitValue);

    // save the initial value
    m_InitialTimeValue = timeInitValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_Time;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceTimeEdit::GetEditText() const
{
    CString text;

    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(text);

    return text;
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::SetEditText(const CString& text)
{
    m_StrValue = text;

    if (::IsWindow(GetSafeHwnd()))
        SetWindowText(text);
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::SetEditText(const PSS_TimeSpan& timeValue)
{
    // set the duration value
    m_TimeValue = timeValue;

    // Format the value function of the string format specified
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_TimeValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceTimeEdit::IsEditCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case PSS_InPlaceEdit::IE_T_String:
            // set back the initial value
            SetEditText(m_StrInitialValue);
            break;

        case PSS_InPlaceEdit::IE_T_Time:
            // set back the initial duration value
            SetEditText(m_InitialTimeValue);
            break;
    }

    // set the focus to properties control
    SetFocus();

    // reset the has changed value
    SetHasChanged(false);
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::SaveValue()
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

                    case PSS_InPlaceEdit::IE_T_Time:
                    {
                        PSS_TimeSpan value;

                        conversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(proposedValue,
                                                                                        value,
                                                                                        m_pItem->GetStringFormat());

                        // check the conversion
                        if (!conversionCorrect)
                            CancelEdit();

                        break;
                    }
                }

                // if conversion succeeded and value is checked, save the edit value
                if (conversionCorrect && pParent->CheckCurrentPropertyData(m_pItem, proposedValue))
                {
                    // set the has changed flag for the property item
                    m_pItem->SetHasChanged();

                    // notify the observers about the changed value
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

    // set the focus to properties control
    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::OnExtendedCommand()
{
    PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

    // process the extended command
    if (pParent)
    {
        PSS_PropertyItem* pItem         = pParent->GetCurrentPropertyItem();
        CString           proposedValue = GetEditText();

        // save the value
        SaveValue();

        // the extended time function is handled internally, the standard time dialog should be owned by the caller
        if (pItem)
        {
            PSS_TimeSpan value;

            const bool conversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(proposedValue,
                                                                                       value,
                                                                                       pItem->GetStringFormat());

            // check the conversion
            if (conversionCorrect)
            {
                // format the value using the specified string format
                proposedValue = PSS_StringFormatter::GetFormattedBuffer((PSS_TimeSpan&)value, pItem->GetStringFormat());

                SetEditText(proposedValue);

                // set the changed value
                SetHasChanged(true);
            }
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceTimeEdit::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return PSS_SearchEdit::PreTranslateMessage(pMsg);

    if (pMsg->message == WM_KEYDOWN)
    {
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
                    pParent->PostMessage(WM_KEYPRESSED_EDIT, (GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | pMsg->wParam) : pMsg->wParam);
                    return TRUE;
                }

                break;
            }

            default:
                break;
        }
    }

    return PSS_SearchEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_InPlaceTimeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DoCreateButton(FALSE);

    if (PSS_SearchEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);

    CWnd* pParent = GetParent();
    PSS_Assert(pParent);

    CFont* pFont = pParent->GetFont();
    DWORD  style = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    if (m_IsReadOnly)
        style |= ES_READONLY;

    SetFont(pFont);

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceTimeEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // set the changed flag
    m_HasChanged = true;

    // call the base function
    PSS_SearchEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_InPlaceTimeEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_SearchEdit::OnSetFocus(pOldWnd);
}
//---------------------------------------------------------------------------
