/****************************************************************************
 * ==> PSS_InPlaceDragEdit -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place draggable edit control and several    *
 *               controls based on it                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceDragEdit.h"

// processsoft
#include "zBaseLib\PSS_StringFormatter.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "ZCPropertyListCtrl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlaceDragEdit, CEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlaceDragEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_InPlaceDragEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlaceDragEdit
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit::PSS_InPlaceDragEdit(const PSS_InPlaceDragEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit& PSS_InPlaceDragEdit::operator = (const PSS_InPlaceDragEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
CWnd* PSS_InPlaceDragEdit::CreateInPlaceEditCtrl(const CString& initText, CWnd* pWndParent, CRect& rect, DWORD exStyle)
{
    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDragEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                    const CString&    initText,
                                                    CWnd*             pWndParent,
                                                    const CRect&      rect,
                                                    DWORD             exStyle)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDragEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                    double            initValue,
                                                    CWnd*             pWndParent,
                                                    const CRect&      rect,
                                                    DWORD             exStyle)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDragEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                    float             initValue,
                                                    CWnd*             pWndParent,
                                                    const CRect&      rect,
                                                    DWORD             exStyle)
{
    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceDragEdit::GetEditText() const
{
    CString text;
    GetWindowText(text);
    return text;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::SetEditText(const CString& text)
{
    m_StrValue = text;
    SetWindowText(text);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::SetEditText(float value)
{
    // set the float value
    m_FloatValue = value;

    // format the value using the specified string format
    const CString initText = PSS_StringFormatter::GetFormattedBuffer(m_FloatValue, m_pItem->GetStringFormat());

    SetEditText(initText);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::SetEditText(double value)
{
    // set the double value
    m_DoubleValue = value;

    // format the value using the specified string format
    const CString strInitText = PSS_StringFormatter::GetFormattedBuffer(m_DoubleValue, m_pItem->GetStringFormat());

    SetEditText(strInitText);
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::CancelEdit()
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

    // reset the changed flag
    m_HasChanged = false;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::SaveValue()
{
    // if the value has changed, save it
    if (m_HasChanged)
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

                // if the conversion succeeded and the value was checked, save the edit value
                if (conversionCorrect && pParent->CheckCurrentPropertyData(m_pItem, proposedValue))
                {
                    // notify that the property ittem changed
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
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDragEdit::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return PSS_DragEdit::PreTranslateMessage(pMsg);

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

                ZCPropertyListCtrl* pParent = dynamic_cast<ZCPropertyListCtrl*>(GetParent());

                // notify the observers
                if (pParent)
                {
                    GetParent()->PostMessage(WM_KEYPRESSED_EDIT, pMsg->wParam);
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
                    GetParent()->PostMessage(WM_KEYPRESSED_EDIT,
                                             (::GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT | pMsg->wParam) : pMsg->wParam);
                    return TRUE;
                }

                break;
            }

            default:
                break;
        }

    return PSS_DragEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
int PSS_InPlaceDragEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_DragEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    CFont* pFont = GetParent()->GetFont();
    SetFont(pFont);

    SetWindowText(m_StrValue);

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceDragEdit::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceDragEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // set the has changed flag
    m_HasChanged = true;

    // call the base function
    PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlacePropItemStringEdit, PSS_InPlaceDragEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlacePropItemStringEdit, PSS_InPlaceDragEdit)
    //{{AFX_MSG_MAP(PSS_InPlacePropItemStringEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlacePropItemStringEdit
//---------------------------------------------------------------------------
PSS_InPlacePropItemStringEdit::PSS_InPlacePropItemStringEdit(const PSS_InPlacePropItemStringEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlacePropItemStringEdit& PSS_InPlacePropItemStringEdit::operator = (const PSS_InPlacePropItemStringEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlacePropItemStringEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                              const CString&    initText,
                                                              CWnd*             pWndParent,
                                                              const CRect&      rect,
                                                              DWORD             exStyle)
{
    m_pItem = pItem;

    const_cast<CRect&>(rect).DeflateRect(0, 1);
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle;

    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;

    const BOOL result = Create(dwStyle, rect, pWndParent, 1);

    // set the right text
    SetEditText(initText);

    // save the initial value
    m_StrInitialValue = GetEditText();

    // reset the changed flag
    m_HasChanged = false;

    // set the selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
void PSS_InPlacePropItemStringEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InPlacePropItemNumberEdit, PSS_InPlaceDragEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InPlacePropItemNumberEdit, PSS_InPlaceDragEdit)
    //{{AFX_MSG_MAP(PSS_InPlacePropItemNumberEdit)
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InPlacePropItemNumberEdit
//---------------------------------------------------------------------------
PSS_InPlacePropItemNumberEdit::PSS_InPlacePropItemNumberEdit(const PSS_InPlacePropItemNumberEdit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InPlacePropItemNumberEdit& PSS_InPlacePropItemNumberEdit::operator = (const PSS_InPlacePropItemNumberEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_InPlacePropItemNumberEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                              float             initValue,
                                                              CWnd*             pWndParent,
                                                              const CRect&      rect,
                                                              DWORD             exStyle)
{
    m_pItem = pItem;

    const_cast<CRect&>(rect).DeflateRect(0, 1);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle;

    if (m_IsReadOnly)
        style |= ES_READONLY;

    const BOOL result = Create(style, rect, pWndParent, 1);

    // set the text
    SetEditText(initValue);

    // save the initial value
    m_FloatInitialValue = initValue;

    // reset the changed flag
    m_HasChanged = false;

    // set the selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlacePropItemNumberEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                              double            initValue,
                                                              CWnd*             pWndParent,
                                                              const CRect&      rect,
                                                              DWORD             exStyle)
{
    m_pItem = pItem;

    const_cast<CRect&>(rect).DeflateRect(0, 1);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | exStyle;

    if (m_IsReadOnly)
        style |= ES_READONLY;

    const BOOL result = Create(style, rect, pWndParent, 1);

    // set the text
    SetEditText(initValue);

    // save the initial value
    m_DoubleInitialValue = initValue;

    // reset the changed flag
    m_HasChanged = false;

    // set the selection to all
    SetSelAll();

    return result;
}
//---------------------------------------------------------------------------
void PSS_InPlacePropItemNumberEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_InPlacePropItemNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // check the char validity
    if (!isdigit(nChar) &&
        nChar != '.'    &&
        nChar != '-'    &&
        nChar != '+'    &&
        nChar != '\''   &&
        nChar != ','    &&
        nChar != '%'    &&
        nChar != 0x08)
        return;

    // call the base function
    PSS_InPlaceDragEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
