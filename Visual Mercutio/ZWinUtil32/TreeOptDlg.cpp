/*
Usage is very easy and consists of several steps: 

Create a dialog and place any controls you need. Be sure to put a control which contains a list of pages (listbox, tree control or similar). Also place a picture control which is a placeholder for pages. 
Use class wizard to create a class associated with this dialog resource. Manually modify a base class from CDialog to ZVisualStackedDialog. Modify a constructor of ZVisualStackedDialog so that it has a resource ID of the picture control as a first argument. You must implement a function CreatePage() which is abstract in base class ZVisualStackedDialog. This function should return a pointer to a page dialog (use new to make an instance of a class derived from ZVisualStackedPage; see next step). Also add a private pointer to object of type ZVisualStackedPageInfo (for example CurrentPage). This pointer should be initially set to NULL (it will point to a currently active page information structure). 
Create a dialog resource for each stacked page. Set border to none, dialog is disabled and is a child dialog. Use class wizard to create a class associated with each page and manually modify base class from CDialog to ZVisualStackedPage. 
In ZVisualStackedDialog derived class OnInitDialog() member function, use the following pseudocode to add pages to the stacked dialog: 
ZVisualStackedPageInfo *info;
info = AddPage("Title A", IDD_PAGE_A); 
Add "Title A" to listbox (or treeview) which contans a list of page titles 
Use SetItemData((DWORD)info) to associate page information structure with listbox item 

This code will add a page to a stacked dialog internal list and also add a title of the page to the listbox (or other control) which enables the user to select a page to work with. AddPage() function will execute abstract function CreatePage() which must be implemented. Also initialize the CurrentPage pointer to point to the ZVisualStackedPageInfo pointer of the current page. Select title in listbox which corresponds to selected page. 

Add a handler for selection change in listbox. Use the following pseudo code in the handler. 
Get an index of current selection
ZVisualStackedPageInfo *info = GetItemData(selection)
DeactivatePage(CurrentPage)
CurrentPage = info
ActivatePage(CurrentPage) 

CurrentPage is a private pointer which is initialised in OnInitDialog() and points to the current page. 

That's all. Now, when you select a listbox item, selection change handler will deactivate the current page and activate the page associated with the new selection in the listbox. You can also use DelAllPages() member function to remove all pages (destroy and delete them) and add a completely different set of pages (depending on your application). OnDestroy member function of ZVisualStackedDialog class will clean up so that there are no memory/resource leaks.

*/

#include "StdAfx.h"
#include "TreeOptDlg.h"


//=============================================================================
// class ZVisualStackedPage
//=============================================================================

BEGIN_MESSAGE_MAP(ZVisualStackedPage, CDialog)
    //{{AFX_MSG_MAP(ZVisualStackedPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVisualStackedPage::ZVisualStackedPage(LPCTSTR lpszTemplateName, CWnd* pParent)
                   :CDialog(lpszTemplateName,pParent)
{
}

ZVisualStackedPage::ZVisualStackedPage(UINT nIDTemplate, CWnd* pParent)
                   :CDialog(nIDTemplate,pParent)
{
}

ZVisualStackedPage::~ZVisualStackedPage()
{
}

void ZVisualStackedPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVisualStackedPage)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

void ZVisualStackedPage::OnOK()
{
}

void ZVisualStackedPage::OnCancel()
{
}

BOOL ZVisualStackedPage::OnInitDialog() 
{
    CDialog::OnInitDialog();

    DWORD style = GetStyle();
    ASSERT((style & WS_CHILD) != 0);
    ASSERT((style & WS_BORDER) == 0);
    ASSERT((style & WS_DISABLED) != 0);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

// Executed when a page is displayed
void ZVisualStackedPage::OnSetActive(void)
{
}

// Executed before a page becomes invisible
void ZVisualStackedPage::OnKillActive(void)
{
}

// Executed after the page is created
void ZVisualStackedPage::OnCreatePage(void)
{
}

// Executed before the page is destroyed
void ZVisualStackedPage::OnDestroyPage(void)
{
}

//=============================================================================
// class ZVisualStackedDialog
//=============================================================================

BEGIN_MESSAGE_MAP(ZVisualStackedDialog, CDialog)
    //{{AFX_MSG_MAP(ZVisualStackedDialog)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


ZVisualStackedDialog::ZVisualStackedDialog(UINT placeholder, 
                                        LPCTSTR lpszTemplateName, CWnd* pParent)
                     :CDialog(lpszTemplateName,pParent)
{
    init(placeholder);
}

ZVisualStackedDialog::ZVisualStackedDialog(UINT placeholder, 
                                        UINT nIDTemplate, CWnd* pParent)
                     :CDialog(nIDTemplate,pParent)
{
    init(placeholder);
}

ZVisualStackedDialog::~ZVisualStackedDialog()
{
}

void ZVisualStackedDialog::init(UINT placeholder)
{
    PlaceHolder = placeholder;
}

void ZVisualStackedDialog::flush(void)
{
    POSITION pos = List.GetHeadPosition();
    while (pos) {
        ZVisualStackedPageInfo *ptr = (ZVisualStackedPageInfo*)List.GetNext(pos);
        if (ptr)
            DelPage(ptr);
    };
    List.RemoveAll();
}

BOOL ZVisualStackedDialog::OnInitDialog() 
{
    CDialog::OnInitDialog();
    ModifyStyleEx (0, WS_EX_CONTROLPARENT);    
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVisualStackedDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVisualStackedDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

void ZVisualStackedDialog::OnDestroy() 
{
    DelAllPages(); 
    CDialog::OnDestroy();
}

ZVisualStackedPageInfo *ZVisualStackedDialog::AddPage(LPCTSTR title, 
                        UINT dlgid, long helpid, DWORD data1, DWORD data2) 
{
    ZVisualStackedPageInfo *page = new ZVisualStackedPageInfo;
    page->Title = title;
    page->DialogID = dlgid;
    page->Dialog = NULL;
    page->HelpID = helpid;
    page->Created = FALSE;
    page->Data1 = data1;
    page->Data2 = data2;

    List.AddTail(page);

    page->Dialog = CreatePage(page->Title,page->DialogID);
    page->Dialog->Create(page->DialogID,this);
    ASSERT(page->Dialog != NULL);
    ASSERT(IsWindow(page->Dialog->m_hWnd) != FALSE);

    CRect rect;
    CWnd *wnd = GetDlgItem(PlaceHolder);
    ASSERT(wnd != NULL);
    ASSERT(IsWindow(wnd->m_hWnd) != FALSE);
    wnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    page->Dialog->SetWindowPos(NULL, rect.left, rect.top, 0, 0, 
                                    SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
    page->Dialog->EnableWindow(TRUE);
    page->Dialog->OnCreatePage();
    page->Created = TRUE;

    return page;
}

void ZVisualStackedDialog::DelPage(ZVisualStackedPageInfo *page)
{
    ASSERT(page != NULL);
    if (page->Created) 
	{
        page->Created = FALSE;
        ASSERT(page->Dialog != NULL);
        page->Dialog->OnKillActive();
        page->Dialog->OnDestroyPage();
        page->Dialog->DestroyWindow();
        delete page->Dialog;
        page->Dialog = NULL;
    }
    POSITION pos = List.GetHeadPosition();
    while (pos) 
	{
        ZVisualStackedPageInfo *ptr = (ZVisualStackedPageInfo*)List.GetAt(pos);
        if (ptr == page) 
		{
            List.RemoveAt(pos);
            delete ptr;
            break;
        }
        List.GetNext(pos);
    }
}

void ZVisualStackedDialog::DelAllPages(void)
{
    flush();
}

void ZVisualStackedDialog::ActivatePage(ZVisualStackedPageInfo *page)
{
    ASSERT(page != NULL);
    ASSERT(page->Dialog != NULL);
    ASSERT(page->Created != FALSE);
    ZVisualStackedPage *dialog = page->Dialog;
    dialog->ShowWindow(SW_SHOW);
    dialog->InvalidateRect(NULL);
    dialog->UpdateWindow();
    dialog->OnSetActive();
}

void ZVisualStackedDialog::DeactivatePage(ZVisualStackedPageInfo *page)
{
    ASSERT(page != NULL);
    ASSERT(page->Dialog != NULL);
    ASSERT(page->Created != FALSE);
    ZVisualStackedPage *dialog = page->Dialog;
    dialog->OnKillActive();
    dialog->ShowWindow(SW_HIDE); 
}

