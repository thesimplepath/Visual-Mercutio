/****************************************************************************
 * ==> PSS_InPlaceDateEdit -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place date edit                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceDateEdit.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_MenuObserverMsg.h"
#include "zProperty\PSS_PropertyItem.h"
#include "ZCPropertyListCtrl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlaceDateEdit, PSS_SearchEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceDateEdit, PSS_SearchEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceDateEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceDateEdit
//---------------------------------------------------------------------------
PSS_InPlaceDateEdit::PSS_InPlaceDateEdit(const PSS_InPlaceDateEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceDateEdit& PSS_InPlaceDateEdit::operator = (const PSS_InPlaceDateEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDateEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
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
BOOL PSS_InPlaceDateEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                    const PSS_Date&   dateInitValue,
                                                    CWnd*             pWndParent,
                                                    const CRect&      rect,
                                                    DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 1);

    SetEditText(dateInitValue);

    // save the initial value
    m_InitialDateValue = dateInitValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_Date;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceDateEdit::GetEditText() const
{
    CString strText;

    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(strText);

    return strText;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::SetEditText(const CString& text)
{
    m_StrValue = text;

    if (::IsWindow(GetSafeHwnd()))
        SetWindowText(text);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::SetEditText(const PSS_Date& dateValue)
{
    // set the duration value
    m_DateValue = dateValue;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_DateValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceDateEdit::IsEditCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case PSS_InPlaceEdit::IE_T_String:
            // set back the initial value
            SetEditText(m_StrInitialValue);
            break;

        case PSS_InPlaceEdit::IE_T_Date:
            // set back the initial duration value
            SetEditText(m_InitialDateValue);
            break;
    }

    // set the focus to properties control
    SetFocus();

    // reset the changed value
    SetHasChanged(false);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::SaveValue()
{
    if (GetHasChanged())
    {
        ZCPropertyListCtrl* pParent = dynamic_cast<ZCPropertyListCtrl*>(GetParent());

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

                    case PSS_InPlaceEdit::IE_T_Date:
                    {
                        // check the conversion
                        PSS_Date value;
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

                    // reset the change flag
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
void PSS_InPlaceDateEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::OnExtendedCommand()
{
    ZCPropertyListCtrl* pParent = dynamic_cast<ZCPropertyListCtrl*>(GetParent());

    // process the extended command
    if (pParent)
    {
        PSS_PropertyItem* pItem = dynamic_cast<ZCPropertyListCtrl*>(GetParent())->GetCurrentPropertyItem();

        CString proposedValue = GetEditText();

        // save the value
        SaveValue();

        // the extended date function is handled internally, the standard date dialog should be owned by the caller
        if (pItem)
        {
            // show the date dialog and change the window text to the proposed value
            PSS_Date value;
            bool     conversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(proposedValue,
                                                                                     value,
                                                                                     pItem->GetStringFormat());

            // check the conversion
            if (conversionCorrect)
            {
                // format the value using the specified string format
                proposedValue = PSS_StringFormatter::GetFormattedBuffer(value, pItem->GetStringFormat());
                SetEditText(proposedValue);

                // set the changed value
                SetHasChanged(true);
            }
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDateEdit::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return PSS_SearchEdit::PreTranslateMessage(pMsg);

    if (pMsg->message == WM_KEYDOWN)
    {
        CWnd* pOwner = GetOwner();

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

                ZCPropertyListCtrl* pParent = dynamic_cast<ZCPropertyListCtrl*>(GetParent());

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

                ZCPropertyListCtrl* pParent = dynamic_cast<ZCPropertyListCtrl*>(GetParent());

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
    }

    return PSS_SearchEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_InPlaceDateEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DoCreateButton(FALSE);

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
BOOL PSS_InPlaceDateEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // set the changed flag
    m_HasChanged = true;

    // call the base function
    PSS_SearchEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDateEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_SearchEdit::OnSetFocus(pOldWnd);
}
//---------------------------------------------------------------------------
