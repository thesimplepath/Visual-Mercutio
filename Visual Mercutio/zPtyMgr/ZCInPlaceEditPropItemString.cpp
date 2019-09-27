// ZCInPlaceEditPropItemString.cpp : implementation file
//

#include "stdafx.h"
#include "ZCInPlaceEditPropItemString.h"
#include "ZCPropertyListCtrl.h"
#include "zBaseLib\ZUStringFormater.h"

// Observer message classes
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceEdit


IMPLEMENT_DYNAMIC(ZCInPlaceEdit, CEdit)



void ZCInPlaceEdit::SetEditText(const CString& strText)
{
    m_strText = strText;

    SetWindowText(strText);
}

void ZCInPlaceEdit::SetEditText(double dValue)
{
    // Sets the double value
    m_dValue = dValue;
    // Build the string
    CString strInitText;
    // Format the value function of the string format specified
    strInitText = ZUStringFormatter::GetFormattedBuffer(m_dValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

void ZCInPlaceEdit::SetEditText(float fValue)
{
    // Sets the float value
    m_fValue = fValue;
    // Build the string
    CString strInitText;
    // Format the value function of the string format specified
    strInitText = ZUStringFormatter::GetFormattedBuffer(m_fValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

CString ZCInPlaceEdit::GetEditText() const
{
    CString strText;
    GetWindowText(strText);
    return strText;
}

BOOL ZCInPlaceEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        switch (pMsg->wParam)
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

    return PSS_DragEdit::PreTranslateMessage(pMsg);
}

void ZCInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // Sets the has changed flag
    m_HasChanged = true;
    // Call the base function
    PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);
}

void ZCInPlaceEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}


void ZCInPlaceEdit::CancelEdit()
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
    // Reset the change flag
    m_HasChanged = false;

}

void ZCInPlaceEdit::SaveValue()
{
    // If the value has changed, request a save
    if (m_HasChanged)
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
                        ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer(ProposedValue, value, m_pItem->GetStringFormat());
                        if (!ConversionCorrect)
                            ZCInPlaceEdit::CancelEdit();
                        break;
                    }
                    case ZIInPlaceEdit::IPE_FLOAT:
                    {
                        // Check the conversion
                        float value;
                        ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer(ProposedValue, value, m_pItem->GetStringFormat());
                        if (!ConversionCorrect)
                            ZCInPlaceEdit::CancelEdit();
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
}

BEGIN_MESSAGE_MAP(ZCInPlaceEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(ZCInPlaceEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceEdit message handlers

int ZCInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_DragEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CFont* pFont = GetParent()->GetFont();
    SetFont(pFont);

    SetWindowText(m_strText);

    return 0;
}

BOOL ZCInPlaceEdit::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceEditPropItemString

IMPLEMENT_DYNAMIC(ZCInPlaceEditPropItemString, ZCInPlaceEdit)

BEGIN_MESSAGE_MAP(ZCInPlaceEditPropItemString, ZCInPlaceEdit)
    //{{AFX_MSG_MAP(ZCInPlaceEditPropItemString)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZCInPlaceEditPropItemString::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}


BOOL ZCInPlaceEditPropItemString::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0*/)
{
    m_pItem = pItem;

    rect.DeflateRect(0, 1);
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle;
    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;
    BOOL rValue = Create(dwStyle, rect, pWndParent, 1);
    // Sets the right text
    SetEditText(strInitText);
    // Saves the initial value
    m_strInitialValueText = GetEditText();
    // Reset the change flag
    m_HasChanged = false;
    // Set the selection to all
    SetSelAll();
    return rValue;

    //pEdit->CreateEx(WS_EX_TRANSPARENT, _T("EDIT"), NULL, WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_LEFT|exDwStyle, rect, pWndParent, 1);
}




/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceEditPropItemNumber

IMPLEMENT_DYNAMIC(ZCInPlaceEditPropItemNumber, ZCInPlaceEdit)


BEGIN_MESSAGE_MAP(ZCInPlaceEditPropItemNumber, ZCInPlaceEdit)
    //{{AFX_MSG_MAP(ZCInPlaceEditPropItemNumber)
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZCInPlaceEditPropItemNumber::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}


BOOL ZCInPlaceEditPropItemNumber::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, double dInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0*/)
{
    m_pItem = pItem;

    rect.DeflateRect(0, 1);
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle;
    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;
    BOOL rValue = Create(dwStyle, rect, pWndParent, 1);
    // Sets the right text
    SetEditText(dInitValue);
    // Saves the initial value
    m_dInitialValue = dInitValue;
    // Reset the change flag
    m_HasChanged = false;
    // Set the selection to all
    SetSelAll();
    return rValue;
}


BOOL ZCInPlaceEditPropItemNumber::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, float fInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0*/)
{
    m_pItem = pItem;

    rect.DeflateRect(0, 1);
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle;
    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;
    BOOL rValue = Create(dwStyle, rect, pWndParent, 1);
    // Sets the right text
    SetEditText(fInitValue);
    // Saves the initial value
    m_fInitialValue = fInitValue;
    // Reset the change flag
    m_HasChanged = false;
    // Set the selection to all
    SetSelAll();
    return rValue;
}


// Allows only number chars
void ZCInPlaceEditPropItemNumber::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // Check the validity of the char
    if (!isdigit(nChar) && nChar != '.' && nChar != '-' && nChar != '+' && nChar != '\'' && nChar != ',' && nChar != '%' && nChar != 0x08)
        return;
    // Call the base function
    ZCInPlaceEdit::OnChar(nChar, nRepCnt, nFlags);
}
