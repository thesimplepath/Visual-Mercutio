/****************************************************************************
 * ==> PSS_VisualStackedPageDialog -----------------------------------------*
 ****************************************************************************
 * Description : Provides a visual stacked page dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_VisualStackedPagesDialog.h"

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_VisualStackedPageDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_VisualStackedPageDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_VisualStackedPageDialog
//---------------------------------------------------------------------------
PSS_VisualStackedPageDialog::PSS_VisualStackedPageDialog(LPCTSTR pTemplateName, CWnd* pParent) :
    CDialog(pTemplateName, pParent)
{}
//---------------------------------------------------------------------------
PSS_VisualStackedPageDialog::PSS_VisualStackedPageDialog(UINT templateID, CWnd* pParent) :
    CDialog(templateID, pParent)
{}
//---------------------------------------------------------------------------
PSS_VisualStackedPageDialog::~PSS_VisualStackedPageDialog()
{}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_VisualStackedPageDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::OnSetActive(void)
{}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::OnKillActive(void)
{}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::OnCreatePage(void)
{}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::OnDestroyPage(void)
{}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::OnOK()
{}
//---------------------------------------------------------------------------
void PSS_VisualStackedPageDialog::OnCancel()
{}
//---------------------------------------------------------------------------
BOOL PSS_VisualStackedPageDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    const DWORD style = GetStyle();
    ASSERT((style & WS_CHILD)    != 0);
    ASSERT((style & WS_BORDER)   == 0);
    ASSERT((style & WS_DISABLED) != 0);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_VisualStackedPagesDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_VisualStackedPagesDialog)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_VisualStackedPagesDialog
//---------------------------------------------------------------------------
PSS_VisualStackedPagesDialog::PSS_VisualStackedPagesDialog(UINT placeholder, LPCTSTR pTemplateName, CWnd* pParent) :
    CDialog(pTemplateName, pParent),
    m_PlaceHolder(0)
{
    Init(placeholder);
}
//---------------------------------------------------------------------------
PSS_VisualStackedPagesDialog::PSS_VisualStackedPagesDialog(UINT placeholder, UINT templateID, CWnd* pParent) :
    CDialog(templateID, pParent),
    m_PlaceHolder(0)
{
    Init(placeholder);
}
//---------------------------------------------------------------------------
PSS_VisualStackedPagesDialog::~PSS_VisualStackedPagesDialog()
{}
//---------------------------------------------------------------------------
PSS_VisualStackedPageInfo* PSS_VisualStackedPagesDialog::AddPage(LPCTSTR pTitle,
                                                                 UINT    dlgID,
                                                                 long    helpID,
                                                                 DWORD   data1,
                                                                 DWORD   data2) 
{
    std::unique_ptr<PSS_VisualStackedPageInfo> pPage(new PSS_VisualStackedPageInfo());
    pPage->m_Title    = pTitle;
    pPage->m_DialogID = dlgID;
    pPage->m_pDialog  = NULL;
    pPage->m_HelpID   = helpID;
    pPage->m_Created  = FALSE;
    pPage->m_Data1    = data1;
    pPage->m_Data2    = data2;

    m_List.AddTail(pPage.get());

    pPage->m_pDialog = CreatePage(pPage->m_Title, pPage->m_DialogID);
    pPage->m_pDialog->Create(pPage->m_DialogID, this);
    ASSERT(pPage->m_pDialog);
    ASSERT(::IsWindow(pPage->m_pDialog->m_hWnd));

    CWnd* pWnd = GetDlgItem(m_PlaceHolder);
    ASSERT(pWnd);
    ASSERT(::IsWindow(pWnd->m_hWnd));

    CRect rect;
    pWnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    pPage->m_pDialog->SetWindowPos(NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
    pPage->m_pDialog->EnableWindow(TRUE);
    pPage->m_pDialog->OnCreatePage();
    pPage->m_Created = TRUE;

    return pPage.release();
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::DelPage(PSS_VisualStackedPageInfo* pPage)
{
    ASSERT(pPage);

    if (pPage->m_Created)
    {
        pPage->m_Created = FALSE;

        ASSERT(pPage->m_pDialog);
        pPage->m_pDialog->OnKillActive();
        pPage->m_pDialog->OnDestroyPage();
        pPage->m_pDialog->DestroyWindow();
        delete pPage->m_pDialog;
        pPage->m_pDialog = NULL;
    }

    POSITION pPos = m_List.GetHeadPosition();

    while (pPos) 
    {
        PSS_VisualStackedPageInfo* pPtr = (PSS_VisualStackedPageInfo*)m_List.GetAt(pPos);

        if (pPtr == pPage) 
        {
            m_List.RemoveAt(pPos);
            delete pPtr;
            break;
        }

        m_List.GetNext(pPos);
    }
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::DelAllPages(void)
{
    Flush();
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::ActivatePage(PSS_VisualStackedPageInfo* pPage)
{
    ASSERT(pPage);
    ASSERT(pPage->m_pDialog);
    ASSERT(pPage->m_Created);

    PSS_VisualStackedPageDialog* pDialog = pPage->m_pDialog;
    pDialog->ShowWindow(SW_SHOW);
    pDialog->InvalidateRect(NULL);
    pDialog->UpdateWindow();
    pDialog->OnSetActive();
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::DeactivatePage(PSS_VisualStackedPageInfo* pPage)
{
    ASSERT(pPage);
    ASSERT(pPage->m_pDialog);
    ASSERT(pPage->m_Created);

    PSS_VisualStackedPageDialog* pDialog = pPage->m_pDialog;
    pDialog->OnKillActive();
    pDialog->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_VisualStackedPagesDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_VisualStackedPagesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    ModifyStyleEx(0, WS_EX_CONTROLPARENT);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::OnDestroy()
{
    DelAllPages();
    CDialog::OnDestroy();
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::Init(UINT placeholder)
{
    m_PlaceHolder = placeholder;
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialog::Flush()
{
    POSITION pPos = m_List.GetHeadPosition();

    while (pPos)
    {
        PSS_VisualStackedPageInfo* pPtr = (PSS_VisualStackedPageInfo*)m_List.GetNext(pPos);

        if (pPtr)
            DelPage(pPtr);
    }

    m_List.RemoveAll();
}
//---------------------------------------------------------------------------
// PSS_VisualStackedPagesDialogIterator
//---------------------------------------------------------------------------
PSS_VisualStackedPagesDialogIterator::PSS_VisualStackedPagesDialogIterator(const PSS_VisualStackedPagesDialog& owner) :
    m_Owner(owner),
    m_pPos(NULL)
{
    Reset();
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialogIterator::Reset()
{
    m_pPos = m_Owner.m_List.GetHeadPosition();
}
//---------------------------------------------------------------------------
void PSS_VisualStackedPagesDialogIterator::Next()
{
    m_Owner.m_List.GetNext(m_pPos);
}
//---------------------------------------------------------------------------
PSS_VisualStackedPageInfo* PSS_VisualStackedPagesDialogIterator::Current()
{
    return (PSS_VisualStackedPageInfo*)m_Owner.m_List.GetAt(m_pPos);
}
//---------------------------------------------------------------------------
BOOL PSS_VisualStackedPagesDialogIterator::IsDone()
{
    return !m_pPos;
}
//---------------------------------------------------------------------------
