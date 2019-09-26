/****************************************************************************
 * ==> PSS_SearchEdit ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a search edit                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SearchEdit.h"

// processsoft
#include "zBaseLib\PSS_FileDialog.h"
#include "SHFileInfo.h"

#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SearchEditButton, CButton)
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SearchEditButton
//---------------------------------------------------------------------------
PSS_SearchEditButton::PSS_SearchEditButton() :
    CButton(),
    m_pWnd(NULL),
    m_pMenu(NULL),
    m_pEdit(NULL),
    m_Type(IE_T_Directory),
    m_ID(0),
    m_Menu(0),
    m_FilterCount(0),
    m_EnableMenuItems(false),
    m_NoNotify(false),
    m_IsProcessingMenuItems(false)
{
    ::NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(::NONCLIENTMETRICS);
    VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(::NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&ncm.lfMessageFont);
}
//---------------------------------------------------------------------------
PSS_SearchEditButton::~PSS_SearchEditButton()
{}
//---------------------------------------------------------------------------
BOOL PSS_SearchEditButton::Create(PSS_SearchEdit* pWnd,
                                  IEType          type,
                                  UINT            menu,
                                  const CString&  title,
                                  const CString&  initialDir,
                                  const CString&  filters,
                                  std::size_t     filterCount,
                                  bool            enableMenuItems,
                                  bool            noNotify,
                                  bool            resize)
{
    ASSERT(type != -1);
    ASSERT_VALID(pWnd);

    // assign values
    m_Type            = type;
    m_Menu            = menu;
    m_pMenu           = NULL;
    m_Title           = title;
    m_InitialDir      = initialDir;
    m_Filters         = filters;
    m_FilterCount     = filterCount;
    m_pEdit           = pWnd;
    m_EnableMenuItems = enableMenuItems;
    m_NoNotify        = noNotify;

    return CreateButton(pWnd, type, resize);
}
//---------------------------------------------------------------------------
BOOL PSS_SearchEditButton::Create(PSS_SearchEdit* pWnd,
                                  IEType          type,
                                  CMenu*          pMenu,
                                  const CString&  title,
                                  const CString&  initialDir,
                                  const CString&  filters,
                                  std::size_t     filterCount,
                                  bool            enableMenuItems,
                                  bool            noNotify,
                                  bool            resize)
{
    ASSERT(type != -1);
    ASSERT_VALID(pWnd);

    // assign values
    m_Type            =  type;
    m_pMenu           =  pMenu;
    m_Menu            = -1;
    m_Title           =  title;
    m_InitialDir      =  initialDir;
    m_Filters         =  filters;
    m_FilterCount     =  filterCount;
    m_pEdit           =  pWnd;
    m_EnableMenuItems =  enableMenuItems;
    m_NoNotify        =  noNotify;

    return CreateButton(pWnd, type, resize);
}
//---------------------------------------------------------------------------
UINT PSS_SearchEditButton::GetNextID(CWnd* pWnd) const
{
    for (UINT i = 32767; i != 1; --i)
        if (!pWnd->GetDlgItem(i))
            return i;

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_SearchEditButton::CreateButton(CWnd* pWnd, IEType type, bool resize)
{
    m_pWnd           = pWnd;
    CWnd* pParentWnd = pWnd->GetParent();
    ASSERT_VALID(pParentWnd);

    CRect rc;
    m_pWnd->GetWindowRect(&rc);

    if (resize)
        m_pWnd->SetWindowPos(NULL,
                             0,
                             0,
                             rc.Width() - 23,
                             rc.Height(),
                             SWP_NOZORDER | SWP_NOMOVE);

    pParentWnd->ScreenToClient(&rc);
    rc.left = rc.right - 18;

    const DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CENTER | BS_VCENTER;

    switch (m_Type)
    {
        case IE_T_Directory:
        case IE_T_File:
        case IE_T_Extended:
            if (CButton::Create(_T( "..." ),
                                style,
                                rc,
                                pParentWnd,
                                GetNextID(pParentWnd)))
            {
                SetWindowPos(m_pWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
                EnableWindow(m_pWnd->IsWindowEnabled());
                SetFont(&m_Font);
                return TRUE;
            }

            break;

        case IE_T_Popup:
            if (CButton::Create(_T("..."),
                                style | BS_ICON,
                                rc,
                                pParentWnd,
                                GetNextID(pParentWnd)))
            {
                SetWindowPos(m_pWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
                EnableWindow(m_pWnd->IsWindowEnabled());
                SetFont(&m_Font);

                CImageList imageList;
                CBitmap    bitmap;

                bitmap.LoadBitmap(IDB_MENU_BUTTON);
                imageList.Create(15, 17, ILC_COLORDDB | ILC_MASK, 1, 1);
                imageList.Add(&bitmap, RGB(255, 0, 255));

                SetIcon(imageList.ExtractIcon(0));

                imageList.Detach();
                bitmap.Detach();

                return TRUE;
            }

            break;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_SearchEditButton::OnClicked()
{
    if (m_IsProcessingMenuItems)
        return;

    switch (m_Type)
    {
        case IE_T_Directory:
        {
            CSHFileInfo sfi;
            sfi.m_strTitle = _T(m_Title);

            if (sfi.BrowseForFolder(GetParent()) == IDOK)
                m_pWnd->SetWindowText(sfi.m_strPath);

            break;
        }

        case IE_T_File:
        {
            PSS_FileDialog fileDlg(m_Title, m_Filters, m_FilterCount, m_InitialDir);

            if (fileDlg.DoModal() == IDOK)
                m_pWnd->SetWindowText(fileDlg.GetFileName());

            break;
        }

        case IE_T_Popup:
        {
            ASSERT(m_Menu != -1 || m_pMenu);
            SetState(TRUE);

            CRect rc;
            GetWindowRect(&rc);

            CWnd*  pParentWnd = m_pWnd->GetParent();
            CMenu* pPopup     = NULL;
            CMenu  menu;

            if (m_pMenu)
                pPopup = m_pMenu->GetSubMenu(0);
            else
            {
                VERIFY(menu.LoadMenu(m_Menu));
                pPopup = menu.GetSubMenu(0);
            }

            ASSERT(pPopup);

            CWnd* pWndPopupOwner = this;

            while (pWndPopupOwner->GetStyle() & WS_CHILD)
                pWndPopupOwner = pWndPopupOwner->GetParent();

            if (pPopup)
            {
                // enable all menu items
                if (m_EnableMenuItems)
                {
                    const UINT count = pPopup->GetMenuItemCount();

                    for (UINT i = 0; i < count; ++i)
                        pPopup->EnableMenuItem(i, MF_BYPOSITION | MF_ENABLED);
                }

                UINT flags = TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL | TPM_RETURNCMD;

                if (m_NoNotify)
                    flags |= TPM_NONOTIFY;

                // set the flag for menu processing
                m_IsProcessingMenuItems = true;

                const int value = pPopup->TrackPopupMenu(flags,
                                                         rc.right,
                                                         rc.top,
                                                         m_EnableMenuItems ? pParentWnd : pWndPopupOwner,
                                                         &rc);

                if (m_pEdit && value > 0)
                    m_pEdit->OnMenuCommand(value);

                // resets the flag
                m_IsProcessingMenuItems = false;
            }

            // return the button state to normal
            SetState(FALSE);

            break;
        }

        case IE_T_Extended:
            if (m_pEdit)
                m_pEdit->OnExtendedCommand();

            break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SearchEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_SearchEdit)
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SearchEdit
//---------------------------------------------------------------------------
PSS_SearchEdit::PSS_SearchEdit() :
    PSS_DragEdit(),
    m_pMenu(NULL),
    m_pParentWnd(NULL),
    m_Type(PSS_SearchEditButton::IE_T_Directory),
    m_FilterCount(0),
    m_Menu(-1),
    m_DoCreateButton(FALSE),
    m_BeingResized(false),
    m_BeingCreated(false),
    m_EnableMenuItems(false),
    m_NoNotify(false)
{}
//---------------------------------------------------------------------------
PSS_SearchEdit::~PSS_SearchEdit()
{}
//---------------------------------------------------------------------------
BOOL PSS_SearchEdit::Create(DWORD style, const RECT& rect, CWnd* pParentWnd, UINT id)
{
    m_BeingCreated = true;

    return CEdit::Create(style, rect, pParentWnd, id);
}
//---------------------------------------------------------------------------
BOOL PSS_SearchEdit::Create(LPCTSTR         pClassName,
                            LPCTSTR         pWindowName,
                            DWORD           style,
                            const RECT&     rect,
                            CWnd*           pParentWnd,
                            UINT            id,
                            CCreateContext* pContext)
{
    return CWnd::Create(pClassName, pWindowName, style, rect, pParentWnd, id, pContext);
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type)
{
    m_Type            =  type;
    m_Menu            = -1;
    m_pMenu           =  NULL;
    m_EnableMenuItems =  false;
    m_NoNotify        =  false;
    m_Title           =  _T("");
    m_InitialDir      =  _T("");
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type, UINT menu, bool enableMenuItems, bool noNotify)
{
    m_Type            = type;
    m_Menu            = menu;
    m_pMenu           = NULL;
    m_EnableMenuItems = enableMenuItems;
    m_NoNotify        = noNotify;
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type, CMenu* pMenu, bool enableMenuItems, bool noNotify)
{
    m_Type            =  type;
    m_Menu            = -1;
    m_pMenu           =  pMenu;
    m_EnableMenuItems =  enableMenuItems;
    m_NoNotify        =  noNotify;
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type, const CString& title, const CString& initialDir)
{
    m_Type       = type;
    m_Title      = title;
    m_InitialDir = initialDir;

    switch (type)
    {
        case PSS_SearchEditButton::IE_T_Directory:
        case PSS_SearchEditButton::IE_T_File:
        {
            m_Menu  = -1;
            m_pMenu =  NULL;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type, UINT nID, const CString& initialDir)
{
    m_Type       = type;
    m_InitialDir = initialDir;

    m_Title.LoadString(nID);

    switch (type)
    {
        case PSS_SearchEditButton::IE_T_Directory:
        case PSS_SearchEditButton::IE_T_File:
        {
            m_Menu  = -1;
            m_pMenu =  NULL;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type,
                                   const CString&               title,
                                   const CString&               initialDir,
                                   const CString&               filters,
                                   std::size_t                  filterCount)
{
    m_Type        = type;
    m_Title       = title;
    m_InitialDir  = initialDir;
    m_Filters     = filters;
    m_FilterCount = filterCount;

    switch (type)
    {
        case PSS_SearchEditButton::IE_T_Directory:
        case PSS_SearchEditButton::IE_T_File:
        {
            m_Menu  = -1;
            m_pMenu =  NULL;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::SetSearchType(PSS_SearchEditButton::IEType type,
                                   UINT                         id,
                                   const CString&               initialDir,
                                   const CString&               filters,
                                   std::size_t                  filterCount)
{
    m_Type        = type;
    m_InitialDir  = initialDir;
    m_Filters     = filters;
    m_FilterCount = filterCount;

    m_Title.LoadString(id);

    switch (type)
    {
        case PSS_SearchEditButton::IE_T_Directory:
        case PSS_SearchEditButton::IE_T_File:
        {
            m_Menu  = -1;
            m_pMenu =  NULL;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::OnMenuCommand(int menuCommand)
{
    // Do nothing in the base class
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::OnExtendedCommand()
{
    // Do nothing in the base class
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::DoCreateButton(BOOL value)
{
    m_DoCreateButton = value;
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::PreSubclassWindow()
{
    PSS_DragEdit::PreSubclassWindow();

    if (m_BeingCreated)
        return;

    // created when invoked from a dialog
    CreateButton(true);
}
//---------------------------------------------------------------------------
int PSS_SearchEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_DragEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (m_BeingCreated && m_DoCreateButton)
        CreateButton(false);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::OnEnable(BOOL bEnable)
{
    PSS_DragEdit::OnEnable(bEnable);

    if (m_DoCreateButton)
        m_Button.EnableWindow(bEnable);
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::OnShowWindow(BOOL bShow, UINT nStatus)
{
    PSS_DragEdit::OnShowWindow(bShow, nStatus);

    if (m_DoCreateButton)
        m_Button.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::OnSize(UINT nType, int cx, int cy)
{
    // to avoid recursion
    if (m_BeingResized)
        return;

    PSS_DragEdit::OnSize(nType, cx, cy);

    if (!::IsWindow(m_Button.GetSafeHwnd()))
        return;

    // start resize controls
    m_BeingResized = true;

    CRect rc;
    GetWindowRect(&rc);

    SetWindowPos(NULL,
                 0,
                 0,
                 rc.Width() - 23,
                 rc.Height(),
                 SWP_NOZORDER | SWP_NOMOVE);

    CWnd* pWndParent = GetParent();
    ASSERT_VALID(pWndParent);

    pWndParent->ScreenToClient(&rc);
    rc.left = rc.right - 18;

    m_Button.MoveWindow(&rc);

    // end resize controls
    m_BeingResized = false;
}
//---------------------------------------------------------------------------
void PSS_SearchEdit::CreateButton(bool resize)
{
    if (m_pMenu)
    {
        if (!m_Button.Create(this,
                             m_Type,
                             m_pMenu,
                             m_Title,
                             m_InitialDir,
                             m_Filters,
                             m_FilterCount,
                             m_EnableMenuItems,
                             m_NoNotify,
                             resize))
        {
            TRACE0(_T("Failed to create browse button.\n"));
            return;
        }
    }
    else
    if (!m_Button.Create(this,
                         m_Type,
                         m_Menu,
                         m_Title,
                         m_InitialDir,
                         m_Filters,
                         m_FilterCount,
                         m_EnableMenuItems,
                         m_NoNotify,
                         resize))
    {
        TRACE0(_T("Failed to create browse button.\n"));
        return;
    }
}
//---------------------------------------------------------------------------
