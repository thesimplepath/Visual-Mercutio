/****************************************************************************
 * ==> PSS_InPlaceMultiLineEdit --------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place multiline edit                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceMultiLineEdit.h"

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
IMPLEMENT_DYNAMIC(PSS_InPlaceMultiLineEdit, CEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceMultiLineEdit, PSS_MultiLineEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceMultiLineEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceMultiLineEdit
//---------------------------------------------------------------------------
PSS_InPlaceMultiLineEdit::PSS_InPlaceMultiLineEdit(bool isReadOnly) :
    PSS_InPlaceEdit(CString(_T("")), isReadOnly),
    PSS_MultiLineEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceMultiLineEdit::PSS_InPlaceMultiLineEdit(const PSS_InPlaceMultiLineEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceMultiLineEdit& PSS_InPlaceMultiLineEdit::operator = (const PSS_InPlaceMultiLineEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceMultiLineEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                         const CString&    initText,
                                                         CWnd*             pWndParent,
                                                         const CRect&      rect,
                                                         DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = PSS_MultiLineEdit::Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 0);

    SetEditText(initText);

    // save the initial value
    m_StrInitialValue = initText;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    m_Type = PSS_InPlaceEdit::IE_T_String;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceMultiLineEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                         float             initValue,
                                                         CWnd*             pWndParent,
                                                         const CRect&      rect,
                                                         DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = PSS_MultiLineEdit::Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL | ES_LEFT | exStyle,
                                                  rect,
                                                  pWndParent,
                                                  0);

    SetEditText(initValue);

    // save the initial value
    m_FloatInitialValue = initValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    m_Type = PSS_InPlaceEdit::IE_T_Float;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceMultiLineEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                         double            initValue,
                                                         CWnd*             pWndParent,
                                                         const CRect&      rect,
                                                         DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = PSS_MultiLineEdit::Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL | ES_LEFT | exStyle,
                                                  rect,
                                                  pWndParent,
                                                  0);

    SetEditText(initValue);

    // save the initial value
    m_DoubleInitialValue = initValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    m_Type = PSS_InPlaceEdit::IE_T_Double;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceMultiLineEdit::GetEditText() const
{
    CString text;

    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(text);

    return text;
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::SetEditText(const CString& text)
{
    m_StrValue = text;

    if (::IsWindow(GetSafeHwnd()))
        PSS_MultiLineEdit::SetEditText(text);
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::SetEditText(float value)
{
    // set the float value
    m_FloatValue = value;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_FloatValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::SetEditText(double value)
{
    // set the double value
    m_DoubleValue = value;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_DoubleValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceMultiLineEdit::IsEditCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case PSS_InPlaceEdit::IE_T_String:
            // set back the initial value
            SetEditText(m_StrInitialValue);
            break;

        case PSS_InPlaceEdit::IE_T_Double:
            // set back the initial double value
            SetEditText(m_DoubleInitialValue);
            break;

        case PSS_InPlaceEdit::IE_T_Float:
            // set back the initial float value
            SetEditText(m_FloatInitialValue);
            break;
    }

    // set the focus to properties control
    SetFocus();

    // reset the changed value
    SetHasChanged(false);
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::SaveValue()
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

                    case PSS_InPlaceEdit::IE_T_Double:
                    {
                        double value;

                        conversionCorrect = PSS_StringFormatter::ConvertFormattedBuffer(proposedValue,
                                                                                        value,
                                                                                        m_pItem->GetStringFormat());

                        // check the conversion
                        if (!conversionCorrect)
                            CancelEdit();

                        break;
                    }

                    case PSS_InPlaceEdit::IE_T_Float:
                    {
                        float value;

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

                    // notify observers about changed value
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

    // set the focus to properties control
    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::OnExtendedCommand()
{
    PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

    // process the extended command
    if (pParent)
    {
        PSS_PropertyItem* pItem         = pParent->GetCurrentPropertyItem();
        CString           proposedValue = GetEditText();

        // save the value
        SaveValue();

        bool refresh = false;

        // process the data
        if (pItem && pParent->ProcessExtendedCurrentPropertyData(pItem, proposedValue, refresh))
        {
            // change the window text to the proposed value
            SetEditText(proposedValue);

            // set the changed value
            SetHasChanged(true);

            // if the control need to be refreshed
            if (refresh)
                // force the control list to reload values
                pParent->Refresh(true, true);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::OnEditTextChanged()
{
    // change the flag
    SetHasChanged(true);
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceMultiLineEdit::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return PSS_MultiLineEdit::PreTranslateMessage(pMsg);

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

    return PSS_MultiLineEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_InPlaceMultiLineEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_MultiLineEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);

    CWnd* pParent = GetParent();
    ASSERT(pParent);

    CFont* pFont = pParent->GetFont();
    DWORD  style = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    if (m_IsReadOnly)
        style |= ES_READONLY;

    SetFont(pFont);

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceMultiLineEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // set the changed flag
    m_HasChanged = true;

    // call the base function
    PSS_MultiLineEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_InPlaceMultiLineEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_MultiLineEdit::OnSetFocus(pOldWnd);
}
//---------------------------------------------------------------------------
