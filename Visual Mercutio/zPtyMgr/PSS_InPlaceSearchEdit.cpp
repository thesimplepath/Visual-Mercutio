/****************************************************************************
 * ==> PSS_InPlaceSearchEdit -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place search edit                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceSearchEdit.h"

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
IMPLEMENT_DYNAMIC(PSS_InPlaceSearchEdit, PSS_SearchEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceSearchEdit, PSS_SearchEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceSearchEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceSearchEdit
//---------------------------------------------------------------------------
PSS_InPlaceSearchEdit::PSS_InPlaceSearchEdit(bool isReadOnly) :
    PSS_InPlaceEdit(CString(_T("")), isReadOnly),
    PSS_SearchEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceSearchEdit::PSS_InPlaceSearchEdit(const PSS_InPlaceSearchEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceSearchEdit& PSS_InPlaceSearchEdit::operator = (const PSS_InPlaceSearchEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceSearchEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
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

    // sets the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_String;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceSearchEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                      float             initValue,
                                                      CWnd*             pWndParent,
                                                      const CRect&      rect,
                                                      DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 1);

    SetEditText(initValue);

    // save the initial value
    m_FloatInitialValue = initValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_Float;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceSearchEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                      double            initValue,
                                                      CWnd*             pWndParent,
                                                      const CRect&      rect,
                                                      DWORD             exStyle)
{
    m_pItem = pItem;

    const BOOL result = Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle, rect, pWndParent, 1);

    SetEditText(initValue);

    // save the initial value
    m_DoubleInitialValue = initValue;

    // reset the changed value
    SetHasChanged(false);

    // set the type
    PSS_InPlaceEdit::m_Type = PSS_InPlaceEdit::IE_T_Double;

    // set the current selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceSearchEdit::GetEditText() const
{
    CString text;

    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(text);

    return text;
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::SetEditText(const CString& text)
{
    m_StrValue = text;

    if (::IsWindow(GetSafeHwnd()))
        SetWindowText(text);
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::SetEditText(float value)
{
    // set the float value
    m_FloatValue = value;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_FloatValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::SetEditText(double dValue)
{
    // set the double value
    m_DoubleValue = dValue;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_DoubleValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
bool PSS_InPlaceSearchEdit::IsEditCtrlHit(const CPoint& point) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::CancelEdit()
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
void PSS_InPlaceSearchEdit::SaveValue()
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
                    // set the changed flag for the property item
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

    // set the focus to properties control
    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::OnMenuCommand(int MenuCommand)
{
    PSS_PropertyListCtrl* pParent = dynamic_cast<PSS_PropertyListCtrl*>(GetParent());

    // process the menu command
    if (pParent)
    {
        PSS_PropertyItem* pItem         = pParent->GetCurrentPropertyItem();
        CString           proposedValue = GetEditText();

        bool refresh;

        // process the data
        if (pItem && pParent->ProcessMenuCommandCurrentPropertyData(MenuCommand, pItem, proposedValue, refresh))
        {
            // change the window text to the proposed value
            SetEditText(proposedValue);

            // set the changed value
            SetHasChanged(true);

            // set the focus to the edit
            SetFocus();

            // force the control list to reload values
            if (refresh)
                pParent->Refresh(true, true);
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceSearchEdit::PreTranslateMessage(MSG* pMsg)
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
int PSS_InPlaceSearchEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DoCreateButton(TRUE);

    if (PSS_SearchEdit::OnCreate(lpCreateStruct) == -1)
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
BOOL PSS_InPlaceSearchEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // set the changed flag
    m_HasChanged = true;

    // call the base function
    PSS_SearchEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_InPlaceSearchEdit::OnSetFocus(CWnd* pOldWnd)
{
    PSS_SearchEdit::OnSetFocus(pOldWnd);
}
//---------------------------------------------------------------------------
