/****************************************************************************
 * ==> PSS_PropertyListCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property list controller                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyListCtrl.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_KeyboardObserverMsg.h"
#include "zProperty\PSS_PropertyItem.h"
#include "zProperty\PSS_PropertyObserverMsg.h"
#include "zProperty\PSS_PropertyItemObserverMsg.h"
#include "PSS_PropertyItemManager.h"

// resources
#include "zPtyMgrRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Color_ReadOnly       RGB(128, 128, 128)
#define M_Property_Left_Border 16
//---------------------------------------------------------------------------
// Global constant
//---------------------------------------------------------------------------
static CRect  g_InitialRect(0, 0, 0, 0);
static CPoint g_InitialPoint(0, 0);
static CPoint g_LastPoint(0, 0);
static int    g_MaxLeft            = 0;
static int    g_MaxRight           = 0;
static bool   g_InMoveSplitterMode = false;
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PropertyListCtrl, CDragListBox)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertyListCtrl, CDragListBox)
    //{{AFX_MSG_MAP(PSS_PropertyListCtrl)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_KEYPRESSED_EDIT, OnKeyPressed)
    ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelChange)
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertyListCtrl
//---------------------------------------------------------------------------
PSS_PropertyListCtrl::PSS_PropertyListCtrl(LPCTSTR pIniFile) :
    CDragListBox(),
    PSS_Subject(),
    PSS_Observer(),
    m_pWndInPlaceControl(NULL),
    m_pPropItemManager(NULL),
    m_pCurrentProps(NULL),
    m_pSrcDragPropItem(NULL),
    m_hCurSplitter(NULL),
    m_SplitterX(100),
    m_SrcDragPropItemIndex(-1),
    m_SelectedItem(-1),
    m_IniFileLoaded(false),
    m_ListInReadOnly(false)
{
    m_pPropItemManager = new PSS_PropertyItemManager;

    // if an ini file is defined
    if (pIniFile)
    {
        m_IniFile = pIniFile;
        m_pPropItemManager->LoadStateFromIniFile(m_IniFile);
        m_IniFileLoaded = true;
    }

    HINSTANCE hInstResource = ::AfxFindResourceHandle(MAKEINTRESOURCE(IDC_SPLITTER_H), RT_GROUP_CURSOR);

    // load cursor from resources
    m_hCurSplitter = HCURSOR(::LoadImage(hInstResource, MAKEINTRESOURCE(IDC_SPLITTER_H), IMAGE_CURSOR, 0, 0, 0));
}
//---------------------------------------------------------------------------
PSS_PropertyListCtrl::PSS_PropertyListCtrl(const PSS_PropertyListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_PropertyListCtrl::~PSS_PropertyListCtrl()
{
    // before destroying this class, saves the information to the ini file, if there is one defined
    if (!m_IniFile.IsEmpty())
        m_pPropItemManager->SaveStateToIniFile(m_IniFile);

    if (m_pPropItemManager)
        delete m_pPropItemManager;

    if (m_pWndInPlaceControl)
        delete m_pWndInPlaceControl;

    // destroy the cursor (if any)
    if (m_hCurSplitter)
        ::DestroyCursor(m_hCurSplitter);
}
//---------------------------------------------------------------------------
PSS_PropertyListCtrl& PSS_PropertyListCtrl::operator = (const PSS_PropertyListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::Initialize(PSS_Properties* pProps, LPCTSTR pIniFile)
{
    // check if the value has changed, and notify the control to save its value
    if (m_pWndInPlaceControl && m_pWndInPlaceControl->GetHasChanged())
        m_pWndInPlaceControl->SaveValue();

    if (pProps)
        m_pCurrentProps = pProps;

    // update the properties, nothing will be done if none
    m_pPropItemManager->UpdatePropertyData();

    // fill the property set with properties
    m_pPropItemManager->UpdateControlData(m_pCurrentProps);

    if (m_pPropItemManager)
        m_pPropItemManager->SetPropertyListCtrl(this);

    // if an ini file is defined
    if (pIniFile)
        if (m_IniFile != pIniFile)
        {
            m_IniFile = pIniFile;
            m_pPropItemManager->LoadStateFromIniFile(m_IniFile);
            m_IniFileLoaded = true;
        }

    Refresh();
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::Initialize(PSS_Properties::IPropertySet& propSet, LPCTSTR pIniFile)
{
    // check if the value has changed, and notify the control to save its value
    if (m_pWndInPlaceControl && m_pWndInPlaceControl->GetHasChanged())
        m_pWndInPlaceControl->SaveValue();

    // update the properties, nothing will be done if none
    m_pPropItemManager->UpdatePropertyData();

    // fill the property set with properties
    m_pPropItemManager->UpdateControlData(propSet);

    if (m_pPropItemManager)
        m_pPropItemManager->SetPropertyListCtrl(this);

    // if an ini file is defined
    if (pIniFile)
        if (m_IniFile != pIniFile)
        {
            m_IniFile = pIniFile;
            m_pPropItemManager->LoadStateFromIniFile(m_IniFile);
            m_IniFileLoaded = true;
        }

    Refresh();
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::LoadStateFromIniFile(const CString& iniFile)
{
    // if an ini file is defined
    if (!iniFile.IsEmpty())
        if (m_IniFile != iniFile)
        {
            m_IniFile = iniFile;
            m_pPropItemManager->LoadStateFromIniFile(m_IniFile);
            m_IniFileLoaded = true;
        }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::Refresh(bool deleteEditCtrl, bool reloadControlData)
{
    const int index                =  GetTopIndex();
    int       previousSelectedItem = -1;

    // save the selected item
    if (!deleteEditCtrl)
        previousSelectedItem = m_SelectedItem;

    // reset the content
    ResetContent(deleteEditCtrl);

    // fill the property set with properties
    if (reloadControlData)
        m_pPropItemManager->UpdateControlData(m_pCurrentProps);

    PSS_PropertyItemManager::IItemCategoryIterator it(&m_pPropItemManager->GetItemCategorySet());
    int                                            item = 0;

    // iterate through all items
    for (PSS_PropertyItemCategory* pPropItemTab = it.GetFirst(); pPropItemTab; pPropItemTab = it.GetNext())
        if (pPropItemTab->GetEnabled())
        {
            InsertPropertyItem(pPropItemTab, item);

            // perform the expand only if children are visible
            if (pPropItemTab->GetChildrenVisible())
                DoExpand(pPropItemTab, item);

            ++item;
        }

    // if needed to show the edit control again
    if (!deleteEditCtrl)
    {
        m_SelectedItem = previousSelectedItem;

        // set the current selection
        SetCurSel(previousSelectedItem);
    }

    // redraw the whole list control
    RedrawAll();

    // restore the previous user selection
    if (index <= GetCount() && index > GetTopIndex())
        SetTopIndex(index);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::RedrawAll()
{
    ShowInPlaceControl(false);

    // invalidate the window
    Invalidate();

    ShowInPlaceControl();
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::Empty()
{
    // update the properties, nothing will be done if none
    m_pPropItemManager->UpdatePropertyData();

    // reset the content
    ResetContent(true);

    // empty the property manager
    m_pPropItemManager->Empty();
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::CheckState()
{
    if (!IsListInPhase())
        Refresh(false);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::SetPropertyItemManager(PSS_PropertyItemManager* pPropItemManager)
{
    if (m_pPropItemManager)
        delete m_pPropItemManager;

    m_pPropItemManager = pPropItemManager;

    // initialize the control
    Initialize();
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertyListCtrl::GetCurrentPropertyItem()
{
    const int item = GetCurSel();

    if (item >= 0)
        return GetPropertyItem(item);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_PropertyListCtrl::GetPropertyItem(int index)
{
    return (index >= 0 && index < GetCount() ? reinterpret_cast<PSS_PropertyItem*>(GetItemData(index)) : NULL);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DeletePropertyItem(PSS_PropertyItem* pPropItem)
{
    const int count = GetCount();

    for (int i = 0; i < count; ++i)
    {
        PSS_PropertyItem* pProp = reinterpret_cast<PSS_PropertyItem*>(GetItemData(i));

        if (pProp == pPropItem)
        {
            DeletePropertyItem(i);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::ResetContent(bool deleteEditCtrl)
{
    if (deleteEditCtrl)
        NoInPlaceControl();

    m_SelectedItem = -1;

    CDragListBox::ResetContent();
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::ShowInPlaceControl(bool show)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(m_pWndInPlaceControl);

    if (pWnd)
        pWnd->ShowWindow(show ? SW_SHOW : SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_PropertyObserverMsg* pPropMsg = dynamic_cast<PSS_PropertyObserverMsg*>(pMsg);

    if (pPropMsg)
    {
        if (pPropMsg->GetProperties() && m_pPropItemManager)
            Initialize(pPropMsg->GetProperties());
        else
            Empty();
    }

    PSS_KeyboardObserverMsg* pKeyboardMsg = dynamic_cast<PSS_KeyboardObserverMsg*>(pMsg);

    if (pKeyboardMsg)
        if (pKeyboardMsg->GetMessageID() == WM_KEYPRESSED_EDIT)
            switch (pKeyboardMsg->GetKey())
            {
                case VK_ESCAPE:
                    // remove the focus by setting it on the list control
                    SetFocus();
                    return;

                case VK_RETURN:
                case VK_TAB:
                    // edit next item
                    EditNextItem();
                    return;

                case (VK_SHIFT | VK_TAB):
                    // edit previous item
                    EditPreviousItem();
                    return;

                default:
                    break;
            }

    PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarMsg)
        switch (pToolbarMsg->GetMessageID())
        {
            case WM_VALUESAVED_EDIT:
                // remove the focus by setting it to the list control
                SetCurrentData();
                break;

            case WM_SETFOCUS_EDIT:
                break;

            case WM_KILLFOCUS_EDIT:
                // Remove the focus by setting it to the list control
                SetFocus();
                break;

            default:
                break;
        }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::PreSubclassWindow()
{
    CDragListBox::PreSubclassWindow();

    ModifyStyle(0, LBS_OWNERDRAWFIXED | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY);
}
//---------------------------------------------------------------------------
BOOL PSS_PropertyListCtrl::PreTranslateMessage(MSG* pMsg)
{
    if (!pMsg)
        return CDragListBox::PreTranslateMessage(pMsg);

    if (pMsg->message == WM_KEYDOWN)
    {
        int  item = GetCurSel();
        bool done = true;

        PSS_PropertyItem* pPropItem = GetPropertyItem(item);

        if (pPropItem)
        {
            PSS_PropertyItemCategory* pPropCategory = dynamic_cast<PSS_PropertyItemCategory*>(pPropItem);

            if (pPropCategory)
            {
                const bool childrenVisible = pPropCategory->GetChildrenVisible();

                switch (char(pMsg->wParam))
                {
                    case VK_RETURN:
                        DoCollapseExpand(item, pPropItem);
                        break;

                    case VK_ADD:
                        if (!childrenVisible)
                            DoExpand(pPropCategory, item);

                        break;

                    case VK_SUBTRACT:
                        if (childrenVisible)
                            DoCollapse(pPropCategory, item);

                        break;

                    case VK_TAB:
                        if (GetKeyState(VK_SHIFT) & 0x80000000)
                            EditPreviousItem();
                        else
                            EditNextItem();

                        break;

                    default:
                        done = false;
                        break;
                }
            }
            else
                switch (char(pMsg->wParam))
                {
                    case VK_TAB:
                        if (GetKeyState(VK_SHIFT) & 0x80000000)
                            EditPreviousItem();
                        else
                            EditNextItem();

                        break;

                    case VK_RETURN:
                    {
                        CWnd* pWnd = dynamic_cast<CWnd*>(m_pWndInPlaceControl);

                        if (pWnd)
                            pWnd->SetFocus();

                        break;
                    }

                    default:
                        done = false;
                        break;
                }
        }
        else
            done = false;

        if (done)
            return TRUE;

        if (GetFocus() == this && ::IsCharAlpha(char(pMsg->wParam)))
        {
            if (LookupPropertyItem(char(pMsg->wParam)))
                OnSelChange();

            return TRUE;
        }
    }

    return CDragListBox::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    #if 1
        if (lpDrawItemStruct->itemAction & ODA_FOCUS)
            return;
    #endif

    PSS_PropertyItem* pPropItem = (PSS_PropertyItem*)lpDrawItemStruct->itemData;
    ASSERT(pPropItem);

    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);

    CRect rect;
    GetClientRect(rect);

    int leftBorder = rect.left + M_Property_Left_Border;

    // + / -
    const bool tabItem = ToBool(ISA(pPropItem, PSS_PropertyItemCategory));

    if (tabItem)
    {
        CRect rcSign(lpDrawItemStruct->rcItem);
        rcSign.right = leftBorder;
        rcSign.DeflateRect(4, 4);

        rcSign.right  += 1;
        rcSign.bottom += 1;

        dc.FillRect (rcSign, CBrush::FromHandle(HBRUSH(::GetStockObject(WHITE_BRUSH))));
        dc.FrameRect(rcSign, CBrush::FromHandle(HBRUSH(::GetStockObject(BLACK_BRUSH))));

        CPoint ptCenter(rcSign.CenterPoint());

        // minus
        dc.MoveTo(ptCenter.x - 2, ptCenter.y);
        dc.LineTo(ptCenter.x + 3, ptCenter.y);

        PSS_PropertyItemCategory* pPropCategory = dynamic_cast<PSS_PropertyItemCategory*>(pPropItem);

        if (pPropCategory && !pPropCategory->GetChildrenVisible())
        {
            // plus
            dc.MoveTo(ptCenter.x, ptCenter.y - 2);
            dc.LineTo(ptCenter.x, ptCenter.y + 3);
        }
    }

    CPen  pen(PS_SOLID, 1, RGB(198, 198, 198));
    CPen* pOldPen = dc.SelectObject(&pen);

    dc.MoveTo(leftBorder, rect.top);
    dc.LineTo(leftBorder, rect.bottom);

    rect       = lpDrawItemStruct->rcItem;
    rect.left += M_Property_Left_Border;

    const int bottom = rect.bottom - 1;

    dc.MoveTo(leftBorder, bottom);
    dc.LineTo(rect.right, bottom);

    leftBorder = m_SplitterX;

    dc.MoveTo(leftBorder, rect.top);
    dc.LineTo(leftBorder, bottom);

    rect.left   += 1;
    rect.bottom -= 1;
    rect.right   = leftBorder;

    int bgCol;
    int textCol;

    if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED))
    {
        bgCol   = COLOR_HIGHLIGHT;
        textCol = COLOR_HIGHLIGHTTEXT;
    }
    else
    {
        bgCol   = COLOR_WINDOW;
        textCol = COLOR_WINDOWTEXT;
    }

    COLORREF crBackground   = ::GetSysColor(bgCol);
    COLORREF crText         = ::GetSysColor(textCol);
    COLORREF crTextReadOnly = M_Color_ReadOnly;

    dc.FillSolidRect(rect, crBackground);
    COLORREF crOldBkColor   = dc.SetBkColor(crBackground);
    COLORREF crOldTextColor = dc.SetTextColor(pPropItem->CanBeEdited() ? crText : crTextReadOnly);

    rect.left  += 3;
    rect.right -= 3;

    CFont* pOldFont = NULL;
    CFont  fontLabel;

    if (tabItem)
        pOldFont = dc.SelectObject(&m_FontBold);
    else
        pOldFont = dc.SelectObject(&m_Font);

    // draw the title
    dc.DrawText(pPropItem->GetName(), &rect, DT_SINGLELINE | DT_VCENTER);

    // if not selected, draw the value
    if (!(lpDrawItemStruct->itemState & ODS_SELECTED) || !pPropItem->CanBeEdited())
    {
        rect = lpDrawItemStruct->rcItem;
        GetItemValueRect(rect);
        pPropItem->DrawValue(&dc, rect);
    }

    dc.SelectObject(pOldPen);
    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);

    if (pOldFont != NULL)
        dc.SelectObject(pOldFont);

    dc.Detach();
}
//---------------------------------------------------------------------------
int PSS_PropertyListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDragListBox::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the caption font
    if (!m_Font.CreateFont(15,
                           6,
                           0,
                           0,
                           FW_NORMAL,
                           0,
                           0,
                           0,
                           ANSI_CHARSET,
                           OUT_TT_PRECIS,
                           CLIP_DEFAULT_PRECIS,
                           PROOF_QUALITY,
                           0,
                           _T("Tahoma")))
    {
        TRACE0(_T("Unable to create caption font.\n"));
        return -1;
    }

    // create the bold caption font
    if (!m_FontBold.CreateFont(15,
                               6,
                               0,
                               0,
                               FW_BOLD,
                               0,
                               0,
                               0,
                               ANSI_CHARSET,
                               OUT_TT_PRECIS,
                               CLIP_DEFAULT_PRECIS,
                               PROOF_QUALITY,
                               0,
                               _T("Tahoma")))
    {
        TRACE0(_T("Unable to create caption font.\n"));
        return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (point.x <= M_Property_Left_Border)
    {
        CDragListBox::OnLButtonDown(nFlags, point);
        DoCollapseExpand(GetCurSel());
        return;
    }

    CRect rect;
    GetClientRect(rect);

    rect.left  = m_SplitterX - 2;
    rect.right = m_SplitterX + 2;

    // check if the cursor is on the splitter
    if (rect.PtInRect(point))
    {
        g_InMoveSplitterMode = true;

        GetClientRect(g_InitialRect);
        g_InitialRect.DeflateRect(2, 2);

        g_InitialPoint = point;
        g_LastPoint.x  = 0;
        g_LastPoint.y  = 0;

        // calculate the max x
        g_MaxRight = g_InitialRect.right - 5;
        g_MaxLeft  = g_InitialRect.left  + M_Property_Left_Border + 5;

        // hide the edition control
        ShowInPlaceControl(false);

        // capture the cursor in the window
        ::SetCursor(m_hCurSplitter);
        SetCapture();
    }
    else
        CDragListBox::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    // check if in splitter moving mode
    if (g_InMoveSplitterMode)
    {
        // release the cursor capture
        ReleaseCapture();

        // convert the point
        CPoint pt(point);

        // check the maximum and the minimum
        if (g_MaxLeft && g_MaxRight)
            if (pt.x > g_MaxRight)
                pt.x = g_MaxRight;
            else
            if (pt.x < g_MaxLeft)
                pt.x = g_MaxLeft;

        // save the splitter position
        m_SplitterX = pt.x;

        // reset flags and value
        g_InMoveSplitterMode = false;
        g_MaxLeft            = 0;
        g_MaxRight           = 0;

        // redraw the entire control
        Invalidate();

        // unselect the item
        SetCurSel(-1);
    }

    CDragListBox::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CDragListBox::OnLButtonDblClk(nFlags, point);

    DoCollapseExpand(GetCurSel());
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
    // check if we are in splitter moving mode
    if (g_InMoveSplitterMode)
    {
        CDC* pDC = GetDC();

        if (!pDC)
            return;

        try
        {
            // convert the point
            CPoint pt(point);

            // check the maximum and the minimum
            if (g_MaxLeft && g_MaxRight)
                if (pt.x > g_MaxRight)
                    pt.x = g_MaxRight;
                else
                if (pt.x < g_MaxLeft)
                    pt.x = g_MaxLeft;

            // set the splitter position for the redraw
            m_SplitterX = pt.x;

            // call the invalidation window method
            Invalidate();
        }
        catch (...)
        {
            ReleaseDC(pDC);
            throw;
        }

        ReleaseDC(pDC);
        return;
    }
    else
    {
        CRect rect;
        GetClientRect(rect);

        rect.left  = m_SplitterX - 2;
        rect.right = m_SplitterX + 2;

        // check if the cursor is on the splitter
        if (rect.PtInRect(point))
        {
            ::SetCursor(m_hCurSplitter);
            return;
        }
    }

    CDragListBox::OnMouseMove(nFlags, point);
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_PropertyListCtrl::OnKeyPressed(WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
        case VK_ESCAPE:
            // remove the focus by setting it to the list control
            SetFocus();
            return 1;

        case VK_RETURN:
        case VK_TAB:
            // edit next item
            if (!m_ListInReadOnly)
                EditNextItem();

            return 1;

        case (VK_SHIFT | VK_TAB):
            // edit previous item
            if (!m_ListInReadOnly)
                EditPreviousItem();

            return 1;

        default:
            return 0;
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnSelChange()
{
    const int item = GetCurSel();

    if (m_SelectedItem != item && !m_ListInReadOnly)
        CreateInPlaceControl(item, item);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnKillFocus(CWnd* pNewWnd)
{
    CDragListBox::OnKillFocus(pNewWnd);
}
//---------------------------------------------------------------------------
BOOL PSS_PropertyListCtrl::BeginDrag(CPoint point)
{
    if (m_ListInReadOnly)
        return FALSE;

    m_SrcDragPropItemIndex = ItemFromPt(point);
    m_pSrcDragPropItem     = GetPropertyItem(m_SrcDragPropItemIndex);

    if ((!m_pSrcDragPropItem || !m_pSrcDragPropItem->IsDragNDropEnabled()) && !ISA(m_pSrcDragPropItem, PSS_PropertyItemCategory))
    {
        m_pSrcDragPropItem = NULL;
        return FALSE;
    }

    m_nLast = -1;

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::Dropped(int nSrcIndex, CPoint point)
{
    if (m_ListInReadOnly)
        return;

    const int index = ItemFromPt(point);

    if (index == m_SrcDragPropItemIndex)
        return;

    PSS_PropertyItem* pDstPropItem = GetPropertyItem((m_SrcDragPropItemIndex < index) ? index - 1 : index);

    // if is the same index, or NULL, or drag&drop is disabled, or a category, do nothing
    if (m_pSrcDragPropItem == pDstPropItem        ||
        !m_pSrcDragPropItem                       ||
        !pDstPropItem                             ||
        !m_pSrcDragPropItem->IsDragNDropEnabled() ||
        ISA(m_pSrcDragPropItem, PSS_PropertyItemCategory))
    {
        Refresh(false, false);
        return;
    }

    // notify the property manager about the move
    if (m_pPropItemManager->OnDropInternalPropertyItem(m_pSrcDragPropItem,
                                                       pDstPropItem,
                                                       m_SrcDragPropItemIndex < index))
        Refresh(true, false);
    else
    if (m_pSrcDragPropItem || m_pSrcDragPropItem->IsDragNDropEnabled())
        Refresh(false, false);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DetachObserverForEditCtrl()
{
    // if a previous edit control exists, remove it from observer
    if (m_pWndInPlaceControl)
    {
        m_pWndInPlaceControl->DetachAllObservers();
        DetachObserver(m_pWndInPlaceControl);
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::CreateInPlaceControl(int item, int previousItem)
{
    PSS_PropertyItem* pPreviousPropItem = NULL;

    if (previousItem != -1)
        pPreviousPropItem = GetPropertyItem(previousItem);

    CRect rect;
    GetItemRect(item, rect);
    GetItemValueRect(rect);

    // save the value when deleted, if needed
    if (m_pWndInPlaceControl)
    {
        // assign the control size to the property item
        if (m_pWndInPlaceControl->GetSize().cx && m_pWndInPlaceControl->GetSize().cy && pPreviousPropItem)
            pPreviousPropItem->SetSize(m_pWndInPlaceControl->GetSize());

        if (m_pWndInPlaceControl->GetExtendedSize().cx && m_pWndInPlaceControl->GetExtendedSize().cy && pPreviousPropItem)
            pPreviousPropItem->SetExtendedSize(m_pWndInPlaceControl->GetExtendedSize());

        // request the manager to save the property state
        SavePropertyState(pPreviousPropItem);

        // save the control value
        m_pWndInPlaceControl->SaveValue();
    }

    // detach observer on edit control
    DetachObserverForEditCtrl();

    // get the requested property item
    PSS_PropertyItem* pPropItem = GetPropertyItem(item);
    ASSERT(pPropItem);

    if (pPropItem->CanBeEdited())
    {
        // get the property state
        PSS_PropertyItemManager::IPropertyState* pPropState = GetPropertyState(pPropItem);

        if (pPropState && pPropState->GetExtendedSize().cx && pPropState->GetExtendedSize().cy)
            pPropItem->CreateInPlaceControl(this, rect, m_pWndInPlaceControl, pPropState->GetExtendedSize());
        else
            pPropItem->CreateInPlaceControl(this, rect, m_pWndInPlaceControl);

        // notify windows about editing properties
        AfxGetMainWnd()->SendMessageToDescendants(UM_START_PROPERTY_EDITION, 0, LPARAM(NULL));
    }
    else
        pPropItem->DestroyInPlaceControl(m_pWndInPlaceControl);

    // if the edit control exists, set the observers
    if (m_pWndInPlaceControl)
    {
        m_pWndInPlaceControl->AttachObserver(this);
        AttachObserver(m_pWndInPlaceControl);
    }

    // redraw the previously selected item
    if (m_SelectedItem != item)
        RedrawItem(m_SelectedItem);

    // save the selected item
    m_SelectedItem = item;
    SetCurSel(m_SelectedItem);

    CWnd* pWnd = dynamic_cast<CWnd*>(m_pWndInPlaceControl);

    if (pWnd)
        // set the focus to the newly created control
        pWnd->SetFocus();

    // notify all the observers
    PSS_Property* pProperty = m_pPropItemManager->GetMatchingProperty(pPropItem);
    PSS_PropertyItemObserverMsg msg(pProperty);

    // notify all observers
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::EditPreviousItem()
{
    const int count = GetCount();

    if (count > 0)
    {
        const int previousItem = GetCurSel();
        int       item;

        if (previousItem <= 0)
            item = (count - 1);
        else
            item = (previousItem - 1);

        // edit the item
        CreateInPlaceControl(item, previousItem);

        // move the current selection
        SetCurSel(item);
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::EditNextItem()
{
    const int count = GetCount();

    if (count > 0)
    {
        const int previousItem = GetCurSel();
        int       item;

        if (previousItem >= (count - 1))
            item = 0;
        else
            item = (previousItem + 1);

        // edit the item
        CreateInPlaceControl(item, previousItem);

        // move the current selection
        SetCurSel(item);
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DoCollapse(PSS_PropertyItemCategory* pPropItemTab, int item)
{
    ASSERT(pPropItemTab && pPropItemTab->GetChildrenVisible());

    ++item;

    for (int number = pPropItemTab->GetEnabledItemNumber(); number > 0; --number)
        DeleteString(item);

    pPropItemTab->SetChildrenVisible(false);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DoExpand(PSS_PropertyItemCategory* pPropItemTab, int& item)
{
    PSS_PropertyItemCategory::IPropertyItemIterator it(&pPropItemTab->GetPropertyItemSet());

    // iterate through category elements
    for (PSS_PropertyItem* pPropItem = it.GetFirst(); pPropItem; pPropItem = it.GetNext())
        if (pPropItem->GetEnabled())
            InsertPropertyItem(pPropItem, ++item);

    pPropItemTab->SetChildrenVisible();
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DoCollapseExpand(int item, PSS_PropertyItem* pPropItem)
{
    if (!pPropItem)
        pPropItem = GetPropertyItem(item);

    if (!pPropItem)
        return;

    PSS_PropertyItemCategory* pPropItemTab = dynamic_cast<PSS_PropertyItemCategory*>(pPropItem);

    if (pPropItemTab)
    {
        if (SetCurrentData())
            NoInPlaceControl();

        if (pPropItemTab->GetChildrenVisible())
            DoCollapse(pPropItemTab, item);
        else
            DoExpand(pPropItemTab, item);

        // save the collapsed and expanded attribute
        SavePropertyState(pPropItemTab);
    }
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::GetItemValueRect(CRect& rect)
{
    rect.left    = m_SplitterX + 3;
    rect.bottom -= 1;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::SetCurrentData()
{
    if (m_pWndInPlaceControl && m_SelectedItem != -1)
    {
        PSS_PropertyItem* pPropItemEdited = GetPropertyItem(m_SelectedItem);

        if (pPropItemEdited)
        {
            pPropItemEdited->SetData(m_pWndInPlaceControl->GetEditText());

            bool refresh = false;

            m_pPropItemManager->OnDataChanged(pPropItemEdited, this, m_SelectedItem, refresh);

            // if the control should be refreshed
            if (refresh)
                // force the control list to reload its values
                Refresh(true, true);
            else
                // When a data changed, check the state
                CheckState();

            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::NoInPlaceControl()
{
    if (m_pWndInPlaceControl)
    {
        // before deleting the control, detach its observer
        DetachObserverForEditCtrl();

        // delete the control
        delete m_pWndInPlaceControl;

        m_pWndInPlaceControl = NULL;
    }
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::IsListInPhase()
{
    int       item  = 0;
    const int count = GetCount();

    PSS_PropertyItemManager::IItemCategoryIterator it(&m_pPropItemManager->GetItemCategorySet());
    PSS_PropertyItemCategory*                      pPropItemTab = it.GetFirst();
    int                                            index        = 0;

    // iterate through the items and check simulatenously the property item manager
    for (int i = 0; (i < count) && pPropItemTab; ++i, pPropItemTab = it.GetNext())
    {
        index = i;

        // get the item from the control list
        PSS_PropertyItem* pItem = GetPropertyItem(i);

        while (pPropItemTab && !pPropItemTab->GetEnabled())
            pPropItemTab = it.GetNext();

        // no item, no category, next
        if (!pItem && !pPropItemTab)
            continue;

        // if no item only, return not in phase
        if (!pItem)
            return false;

        // if no category only, return not in phase
        if (!pPropItemTab)
            return false;

        // check if the item is a category and the same, if not, return not in phase
        if (!ISA(pItem, PSS_PropertyItemCategory) || pItem != pPropItemTab)
            return false;

        // process the category, check if children are visible. If so, check all childrens
        if (pPropItemTab->GetChildrenVisible())
        {
            PSS_PropertyItemCategory::IPropertyItemIterator itTab(&pPropItemTab->GetPropertyItemSet());

            // iterate through category elements
            for (PSS_PropertyItem* pChildPropCatItem = itTab.GetFirst(); pChildPropCatItem; pChildPropCatItem = itTab.GetNext())
            {
                // get the immediate following item from the list control
                pItem = GetPropertyItem(++i);

                while (pChildPropCatItem && !pChildPropCatItem->GetEnabled())
                    pChildPropCatItem = itTab.GetNext();

                // if not only child item category, break the loop
                if (!pChildPropCatItem)
                {
                    // since the end of elements was reached and all were not enable
                    --i;
                    break;
                }

                // check if the same item, if not, return not in phase
                if (pItem != pChildPropCatItem)
                    return false;
            }
        }
    }

    // check if at the loop end, both iterators are at the end. If not, return not in phase
    if ((index < count) || pPropItemTab)
        return false;

    // in phase
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::LookupPropertyItem(char startChar)
{
    const int count = GetCount();

    if (count)
    {
        int curItem = GetCurSel() + 1;

        if (curItem == count)
            curItem = 0;

        int findIndex = SearchPropertyItem(startChar, curItem, count - curItem);

        if (findIndex == -1 && curItem > 0)
            findIndex = SearchPropertyItem(startChar, 0, curItem);

        if (findIndex != -1)
        {
            SetCurSel(findIndex);
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
int PSS_PropertyListCtrl::SearchPropertyItem(char startChar, int fromIndex, int count)
{
    const CString ch(startChar);

    while (--count)
    {
        PSS_PropertyItem* pPropItem = reinterpret_cast<PSS_PropertyItem*>(GetItemData(fromIndex));
        ASSERT(pPropItem);

        if (pPropItem->GetName().Left(1).CompareNoCase(ch) == 0)
            return fromIndex;

        ++fromIndex;
    }

    return -1;
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::RedrawItem(int item)
{
    PSS_PropertyItem* pPropItem = GetPropertyItem(item);

    if (pPropItem && !ISA(pPropItem, PSS_PropertyItemCategory))
    {
        CRect rect;
        CDC*  pDC = GetDC();

        if (!pDC)
            return;

        CFont*   pOldFont  = pDC->SelectObject(&m_Font);
        COLORREF crBkColor = pDC->GetBkColor();

        GetItemRect(item, rect);
        GetItemValueRect(rect);

        rect.DeflateRect(1, 1);

        pDC->FillSolidRect(&rect, crBkColor);

        rect.InflateRect(1, 1);

        COLORREF crOldTextColor =
                pDC->SetTextColor(pPropItem->CanBeEdited() ? ::GetSysColor(COLOR_WINDOWTEXT) : M_Color_ReadOnly);

        pPropItem->DrawValue(pDC, rect);
        pDC->SetTextColor(crOldTextColor);

        if (pOldFont)
            pDC->SelectObject(pOldFont);

        ReleaseDC(pDC);
    }
}
//---------------------------------------------------------------------------
