
// RS-MODIF 08.08.2005 ajout de l'attribut dynamic "temps"

// ZCInPlaceTimeEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZCInPlaceTimeEdit.h"
#include "ZCPropertyListCtrl.h"

#include "zProperty\ZBPropertyItem.h"

#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_MenuObserverMsg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceTimeEdit

IMPLEMENT_DYNAMIC(ZCInPlaceTimeEdit, PSS_SearchEdit)

BEGIN_MESSAGE_MAP(ZCInPlaceTimeEdit, PSS_SearchEdit)
    //{{AFX_MSG_MAP(ZCInPlaceTimeEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ZCInPlaceTimeEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        CWnd* pOwner = GetOwner();
        WPARAM nChar = pMsg->wParam;

        switch (nChar)
        {
            case VK_DELETE:
            {
                SetHasChanged(true);
                break;
            }
            case VK_ESCAPE:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                // First, cancel the edit
                CancelEdit();
                // Notify observers
                if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
                {
                    GetParent()->PostMessage(WM_KEYPRESSED_EDIT, pMsg->wParam);
                    return TRUE;
                }

                //                ZBKeyboardObserverMsg Msg( WM_KEYPRESSED_EDIT, pMsg->wParam ); 
                //                NotifyAllObservers( &Msg );
                //                return TRUE;
            }
            case VK_RETURN:
            case VK_TAB:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                // First, save the value
//                SaveValue();
                // Notify observers
                if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
                {
                    GetParent()->PostMessage(WM_KEYPRESSED_EDIT, (GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | pMsg->wParam) : pMsg->wParam);
                    return TRUE;
                }
                // Notify observers
//                ZBKeyboardObserverMsg Msg( WM_KEYPRESSED_EDIT, (GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT|pMsg->wParam) : pMsg->wParam ); 
//                NotifyAllObservers( &Msg );
//                return TRUE;
            }
            default:
                ;
        }
    }

    return PSS_SearchEdit::PreTranslateMessage(pMsg);
}

void ZCInPlaceTimeEdit::SetEditText(const CString& strText)
{
    m_strText = strText;

    if (::IsWindow(GetSafeHwnd()))
        SetWindowText(strText);
}

void ZCInPlaceTimeEdit::SetEditText(PSS_TimeSpan& TimeValue)
{
    // Sets the duration value
    m_TimeValue = TimeValue;
    // Build the string
    CString strInitText;
    // Format the value function of the string format specified
    strInitText = ZUStringFormatter::GetFormattedBuffer((PSS_TimeSpan&)m_TimeValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

CString ZCInPlaceTimeEdit::GetEditText() const
{
    CString strText;
    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(strText);
    return strText;
}


BOOL ZCInPlaceTimeEdit::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 1);
    SetEditText(strInitText);
    // Saves the initial value
    m_strInitialValueText = strInitText;
    // Reset the has changed value
    SetHasChanged(false);
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_STRING;
    // Sets the current selection to all
    SetSelAll();
    return rValue;
}

BOOL ZCInPlaceTimeEdit::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, PSS_TimeSpan& TimeInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 1);
    SetEditText((PSS_TimeSpan&)TimeInitValue);
    // Saves the initial value
    m_InitialTimeValue = TimeInitValue;
    // Reset the has changed value
    SetHasChanged(false);
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_TIME;
    // Sets the current selection to all
    SetSelAll();
    return rValue;
}

bool ZCInPlaceTimeEdit::IsEditCtrlHit(CPoint point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return (rect.PtInRect(point)) ? true : false;
}



void ZCInPlaceTimeEdit::SaveValue()
{
    if (GetHasChanged())
    {
        if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
        {
            CString ProposedValue = GetEditText();
            // If correct, process the data
            if (m_pItem)
            {
                bool ConversionCorrect = true;
                switch (GetEditType())
                {
                    case ZIInPlaceEdit::IPE_STRING:
                    {
                        // do nothing for string
                        break;
                    }
                    case ZIInPlaceEdit::IPE_TIME:
                    {
                        // Check the conversion
                        PSS_TimeSpan value;

                        ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer(ProposedValue, (PSS_TimeSpan&)value, m_pItem->GetStringFormat());
                        if (!ConversionCorrect)
                            ZCInPlaceTimeEdit::CancelEdit();
                        break;
                    }
                }
                // Now, if conversion correct and check value, save the edit value
                if (ConversionCorrect &&
                    dynamic_cast<ZCPropertyListCtrl*>(GetParent())->CheckCurrentPropertyData(m_pItem, ProposedValue))
                {
                    // Set the has changed flag for the property item
                    m_pItem->SetHasChanged();
                    // Notify observers for value changed
                    PSS_ToolbarObserverMsg msg(WM_VALUESAVED_EDIT);
                    NotifyAllObservers(&msg);
                    // Reset the change flag
                    m_HasChanged = false;
                    // OK
                    return;
                }
            }
            // Otherwise, not correct
            // Change the window text to the proposed value
            SetEditText(ProposedValue);
        }
    }
    // Set the focus to properties control
    SetFocus();
}


void ZCInPlaceTimeEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case ZIInPlaceEdit::IPE_STRING:
        {
            // Set back the initial value
            SetEditText(m_strInitialValueText);
            break;
        }
        case ZIInPlaceEdit::IPE_TIME:
        {
            // Set back the initial duration value
            SetEditText((PSS_TimeSpan&)m_InitialTimeValue);
            break;
        }
    }
    // Set the focus to properties control
    SetFocus();
    // Reset the has changed value
    SetHasChanged(false);
}



/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceDateEdit message handlers

void ZCInPlaceTimeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // Sets the has changed flag
    m_HasChanged = true;

    // Call the base function
    PSS_SearchEdit::OnChar(nChar, nRepCnt, nFlags);
}

void ZCInPlaceTimeEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}

void ZCInPlaceTimeEdit::OnExtendedCommand()
{
    // Process Extended
    if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
    {
        ZBPropertyItem* pItem = dynamic_cast<ZCPropertyListCtrl*>(GetParent())->GetCurrentPropertyItem();

        CString ProposedValue = GetEditText();
        // Save the value
        SaveValue();
        // The extended function for duration is handled internally.
        // We own the standard duration dialog
        if (pItem)
        {
            // Display the duration dialog and 
            // Change the window text to the proposed value

            // Check the conversion
            PSS_TimeSpan value;
            bool ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer(ProposedValue, (PSS_TimeSpan&)value, pItem->GetStringFormat());
            if (ConversionCorrect)
            {

                // Format the value function of the string format specified
                ProposedValue = ZUStringFormatter::GetFormattedBuffer((PSS_TimeSpan&)value, pItem->GetStringFormat());
                SetEditText(ProposedValue);
                // Set the has changed value
                SetHasChanged(true);
            }
        }
    }
}

int ZCInPlaceTimeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DoCreateButton(FALSE);

    if (PSS_SearchEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);

    CWnd* pParent = GetParent();
    ASSERT(pParent != NULL);

    CFont* pFont = pParent->GetFont();
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;
    SetFont(pFont);

    return 0;
}


BOOL ZCInPlaceTimeEdit::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}

void ZCInPlaceTimeEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_SearchEdit::OnSetFocus(pOldWnd);
}
