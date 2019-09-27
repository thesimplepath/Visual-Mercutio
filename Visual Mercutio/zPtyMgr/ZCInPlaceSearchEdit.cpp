// ZCInPlaceSearchEdit.cpp : implementation file

#include "stdafx.h"
#include "ZCInPlaceSearchEdit.h"
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

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceSearchEdit

IMPLEMENT_DYNAMIC(ZCInPlaceSearchEdit, PSS_SearchEdit)

BEGIN_MESSAGE_MAP(ZCInPlaceSearchEdit, PSS_SearchEdit)
    //{{AFX_MSG_MAP(ZCInPlaceSearchEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCInPlaceSearchEdit::ZCInPlaceSearchEdit(bool IsReadOnly /*= false*/)
    : ZIInPlaceEdit(_T(""), IsReadOnly)
{}

BOOL ZCInPlaceSearchEdit::PreTranslateMessage(MSG* pMsg)
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
            }

            case VK_RETURN:
            case VK_TAB:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);

                // Notify observers
                if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
                {
                    GetParent()->PostMessage(WM_KEYPRESSED_EDIT,
                        (GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | pMsg->wParam) : pMsg->wParam);

                    return TRUE;
                }
            }

            default:
            {
                break;
            }
        }
    }

    return PSS_SearchEdit::PreTranslateMessage(pMsg);
}

void ZCInPlaceSearchEdit::SetEditText(const CString& strText)
{
    m_strText = strText;

    if (::IsWindow(GetSafeHwnd()))
    {
        SetWindowText(strText);
    }
}

void ZCInPlaceSearchEdit::SetEditText(double dValue)
{
    // Sets the double value
    m_dValue = dValue;

    // Build the string
    CString strInitText;

    // Format the value function of the string format specified
    strInitText = ZUStringFormatter::GetFormattedBuffer(m_dValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

void ZCInPlaceSearchEdit::SetEditText(float fValue)
{
    // Sets the float value
    m_fValue = fValue;

    // Build the string
    CString strInitText;

    // Format the value function of the string format specified
    strInitText = ZUStringFormatter::GetFormattedBuffer(m_fValue, m_pItem->GetStringFormat());
    SetEditText(strInitText);
}

CString ZCInPlaceSearchEdit::GetEditText() const
{
    CString strText;

    if (::IsWindow(GetSafeHwnd()))
    {
        GetWindowText(strText);
    }

    return strText;
}

BOOL ZCInPlaceSearchEdit::InitializeInPlaceEditCtrl(ZBPropertyItem*    pItem,
                                                    const CString&        strInitText,
                                                    CWnd*                pWndParent,
                                                    CRect&                rect,
                                                    DWORD                exDwStyle        /*= 0"*/)
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

BOOL ZCInPlaceSearchEdit::InitializeInPlaceEditCtrl(ZBPropertyItem*    pItem,
                                                    double                dInitValue,
                                                    CWnd*                pWndParent,
                                                    CRect&                rect,
                                                    DWORD                exDwStyle    /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 1);
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
BOOL ZCInPlaceSearchEdit::InitializeInPlaceEditCtrl(ZBPropertyItem*    pItem,
                                                    float                fInitValue,
                                                    CWnd*                pWndParent,
                                                    CRect&                rect,
                                                    DWORD                exDwStyle    /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exDwStyle, rect, pWndParent, 1);
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

bool ZCInPlaceSearchEdit::IsEditCtrlHit(CPoint point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return (rect.PtInRect(point)) ? true : false;
}

void ZCInPlaceSearchEdit::SaveValue()
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

                        ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer(ProposedValue,
                                                                                      value,
                                                                                      m_pItem->GetStringFormat());

                        if (!ConversionCorrect)
                        {
                            ZCInPlaceSearchEdit::CancelEdit();
                        }

                        break;
                    }

                    case ZIInPlaceEdit::IPE_FLOAT:
                    {
                        // Check the conversion
                        float value;

                        ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer(ProposedValue,
                                                                                      value,
                                                                                      m_pItem->GetStringFormat());

                        if (!ConversionCorrect)
                        {
                            ZCInPlaceSearchEdit::CancelEdit();
                        }

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

void ZCInPlaceSearchEdit::CancelEdit()
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
// ZCInPlaceSearchEdit message handlers

void ZCInPlaceSearchEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // Sets the has changed flag
    m_HasChanged = true;

    // Call the base function
    PSS_SearchEdit::OnChar(nChar, nRepCnt, nFlags);
}

void ZCInPlaceSearchEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}

void ZCInPlaceSearchEdit::OnMenuCommand(int MenuCommand)
{
    // Process Extended
    if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
    {
        ZBPropertyItem* pItem = dynamic_cast<ZCPropertyListCtrl*>(GetParent())->GetCurrentPropertyItem();

        CString ProposedValue = GetEditText();

        // If correct, process the data
        bool Refresh;

        if (pItem && dynamic_cast<ZCPropertyListCtrl*>(GetParent())->ProcessMenuCommandCurrentPropertyData(MenuCommand, pItem, ProposedValue, Refresh))
        {
            // Change the window text to the proposed value
            SetEditText(ProposedValue);

            // Set the has changed value
            SetHasChanged(true);

            // Set the focus to the edit
            SetFocus();

            if (Refresh)
            {
                // Force the control list to reload values
                dynamic_cast<ZCPropertyListCtrl*>(GetParent())->Refresh(true, true);
            }
        }
    }
}

int ZCInPlaceSearchEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DoCreateButton(TRUE);

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
    {
        dwStyle |= ES_READONLY;
    }

    SetFont(pFont);

    return 0;
}

BOOL ZCInPlaceSearchEdit::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;
}

void ZCInPlaceSearchEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_SearchEdit::OnSetFocus(pOldWnd);
}
