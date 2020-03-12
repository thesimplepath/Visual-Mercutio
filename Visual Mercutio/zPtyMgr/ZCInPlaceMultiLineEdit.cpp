// ZCInPlaceMultiLineEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZCInPlaceMultiLineEdit.h"
#include "ZCPropertyListCtrl.h"


#include "zProperty\PSS_PropertyItem.h"

#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_MenuObserverMsg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceMultiLineEdit

IMPLEMENT_DYNAMIC(ZCInPlaceMultiLineEdit, CEdit)


ZCInPlaceMultiLineEdit::ZCInPlaceMultiLineEdit(bool IsReadOnly /*= false*/)
    : ZIInPlaceEdit(_T(""), IsReadOnly)
{

}


BEGIN_MESSAGE_MAP(ZCInPlaceMultiLineEdit, PSS_MultiLineEdit)
    //{{AFX_MSG_MAP(ZCInPlaceMultiLineEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL ZCInPlaceMultiLineEdit::PreTranslateMessage(MSG* pMsg)
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
                // Notify observers
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

    return PSS_MultiLineEdit::PreTranslateMessage(pMsg);
}

void ZCInPlaceMultiLineEdit::OnEditTextChanged()
{
    // Change the flag
    SetHasChanged(true);
}

void ZCInPlaceMultiLineEdit::SetEditText(const CString& strText)
{
    m_strText = strText;

    if (::IsWindow(GetSafeHwnd()))
        PSS_MultiLineEdit::SetEditText(strText);
}

void ZCInPlaceMultiLineEdit::SetEditText(double dValue)
{
    // Sets the double value
    m_dValue = dValue;
    // Build the string
    CString strInitText;
    // Format the value function of the string format specified
    strInitText = PSS_StringFormatter::GetFormattedBuffer(m_dValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

void ZCInPlaceMultiLineEdit::SetEditText(float fValue)
{
    // Sets the float value
    m_fValue = fValue;
    // Build the string
    CString strInitText;
    // Format the value function of the string format specified
    strInitText = PSS_StringFormatter::GetFormattedBuffer(m_fValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

CString ZCInPlaceMultiLineEdit::GetEditText() const
{
    CString strText;
    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(strText);
    return strText;
}


BOOL ZCInPlaceMultiLineEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle /*= 0"*/)
{
    m_pItem = pItem;
    BOOL rValue = PSS_MultiLineEdit::Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 0);
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

BOOL ZCInPlaceMultiLineEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, double dInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = PSS_MultiLineEdit::Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 0);
    SetEditText(dInitValue);
    // Saves the initial value
    m_dInitialValue = dInitValue;
    // Reset the has changed value
    SetHasChanged(false);
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_DOUBLE;
    // Sets the current selection to all
    SetSelAll();
    return rValue;
}
BOOL ZCInPlaceMultiLineEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, float fInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = PSS_MultiLineEdit::Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 0);
    SetEditText(fInitValue);
    // Saves the initial value
    m_fInitialValue = fInitValue;
    // Reset the has changed value
    SetHasChanged(false);
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_FLOAT;
    // Sets the current selection to all
    SetSelAll();
    return rValue;
}

bool ZCInPlaceMultiLineEdit::IsEditCtrlHit(CPoint point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return (rect.PtInRect(point)) ? true : false;
}



void ZCInPlaceMultiLineEdit::SaveValue()
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
                    case ZIInPlaceEdit::IPE_DOUBLE:
                    {
                        // Check the conversion
                        double value;
                        ConversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(ProposedValue, value, m_pItem->GetStringFormat());
                        if (!ConversionCorrect)
                            ZCInPlaceMultiLineEdit::CancelEdit();
                        break;
                    }
                    case ZIInPlaceEdit::IPE_FLOAT:
                    {
                        // Check the conversion
                        float value;
                        ConversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(ProposedValue, value, m_pItem->GetStringFormat());
                        if (!ConversionCorrect)
                            ZCInPlaceMultiLineEdit::CancelEdit();
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


void ZCInPlaceMultiLineEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case ZIInPlaceEdit::IPE_STRING:
        {
            // Set back the initial value
            SetEditText(m_strInitialValueText);
            break;
        }
        case ZIInPlaceEdit::IPE_DOUBLE:
        {
            // Set back the initial double value
            SetEditText(m_dInitialValue);
            break;
        }
        case ZIInPlaceEdit::IPE_FLOAT:
        {
            // Set back the initial float value
            SetEditText(m_fInitialValue);
            break;
        }
    }
    // Set the focus to properties control
    SetFocus();
    // Reset the has changed value
    SetHasChanged(false);
}



/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceMultiLineEdit message handlers

void ZCInPlaceMultiLineEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // Sets the has changed flag
    m_HasChanged = true;
    // Call the base function
    PSS_MultiLineEdit::OnChar(nChar, nRepCnt, nFlags);
}

void ZCInPlaceMultiLineEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}

void ZCInPlaceMultiLineEdit::OnExtendedCommand()
{
    // Process Extended
    if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
    {
        PSS_PropertyItem* pItem = dynamic_cast<ZCPropertyListCtrl*>(GetParent())->GetCurrentPropertyItem();

        CString ProposedValue = GetEditText();
        // Save the value
        SaveValue();
        // If correct, process the data
        bool Refresh = false;
        if (pItem && dynamic_cast<ZCPropertyListCtrl*>(GetParent())->ProcessExtendedCurrentPropertyData(pItem, ProposedValue, Refresh))
        {
            // Change the window text to the proposed value
            SetEditText(ProposedValue);
            // Set the has changed value
            SetHasChanged(true);
            // If the control need to be refreshed
            if (Refresh)
            {
                // Force the control list to reload values
                dynamic_cast<ZCPropertyListCtrl*>(GetParent())->Refresh(true, true);
            }
        }
    }
}

int ZCInPlaceMultiLineEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_MultiLineEdit::OnCreate(lpCreateStruct) == -1)
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

BOOL ZCInPlaceMultiLineEdit::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}

void ZCInPlaceMultiLineEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_MultiLineEdit::OnSetFocus(pOldWnd);
}
