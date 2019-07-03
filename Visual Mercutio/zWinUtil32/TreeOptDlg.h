//=============================================================================
// class ZVisualStackedPage
// struct ZVisualStackedPageInfo
// class ZVisualStackedDialog
// class ZVisualStackedDialogIterator
//
// A. Create a dialog and modify its base class from CDialog to 
// ZVisualStackedDialog. Add controls as you like it. Allocate one control
// (listbox or similar) to contain a list of pages. Add a picture control
// as a placeholder for stacked pages.
// B. Add a picture control ID to previous dialog constructor.
// C. Add a pointer variable of type ZVisualStackedPageInfo to dialog. It 
// holds a pointer to currently active page. Initialize it to NULL.
// D. Add implementation of CreatePage() abstract function. It should perform
// "new ZVisualStackedPage derived class".
// E. Create pages (child dialogs with border and disable set to off). Modify
// base class from CDialog to ZVisualStackedPage.
// F. In ZVisualStackedDialog::OnInitDialog() use AddPage() to add a page and
// also add a page title to a listbox (or similar) for navigating thru the
// pages. Activate a page and initialize a pointer to currently active page.
// G. Add a handler when a listbox item is changed. In the handler, first 
// deactivate currently active page. Then activate a selected page and 
// update a pointer to point to this new page.
// H. ZVisualStackedDialog will automatically delete pages.
// I. Use ZVisualStackedDialogIterator to iterate thru the pages one at a time
// and perform any action.
// J. Override ZVisualStackedPage virtual functions On....
//=============================================================================

//
// This is a stacked dialog page class declaration. 
//

class AFX_EXT_CLASS ZVisualStackedPage : public CDialog 
{
public:
    ZVisualStackedPage(LPCTSTR lpszTemplateName, CWnd* pParent = NULL);
    ZVisualStackedPage(UINT nIDTemplate, CWnd* pParent = NULL);
    virtual ~ZVisualStackedPage();

    virtual void OnSetActive(void);
    virtual void OnKillActive(void);
    virtual void OnCreatePage(void);
    virtual void OnDestroyPage(void);

    //{{AFX_VIRTUAL(ZVisualStackedPage)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(ZVisualStackedPage)
    virtual void OnOK();
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//
// Helper structure to maintain information about each page.
//

struct AFX_EXT_CLASS ZVisualStackedPageInfo 
{
    CString Title; // Title of this page 
    UINT DialogID; // Resource ID of this page
    ZVisualStackedPage *Dialog;
    long HelpID;
    BOOL Created;
    DWORD Data1; // User defined data
    DWORD Data2; // User defined data
};

//
// This is a stacked dialog class declaration. This is an abstract class.
// Must derive a class and implement CreatePage() member function.
//

class AFX_EXT_CLASS ZVisualStackedDialog : public CDialog 
{
protected:
    UINT PlaceHolder;
    CTypedPtrList<CPtrList,ZVisualStackedPageInfo*> List;

private:
    void init(UINT placeholder);
    void flush(void);

public:
    ZVisualStackedDialog(UINT placeholder, LPCTSTR lpszTemplateName, CWnd* pParent = NULL);
    ZVisualStackedDialog(UINT placeholder, UINT nIDTemplate, CWnd* pParent = NULL);
    virtual ~ZVisualStackedDialog();

    ZVisualStackedPageInfo *AddPage(LPCTSTR title, UINT dlgid, long helpid = 0L,
                                    DWORD data1 = 0, DWORD data2 = 0);
    void DelPage(ZVisualStackedPageInfo *page);
    void DelAllPages(void);

    void ActivatePage(ZVisualStackedPageInfo *page);
    void DeactivatePage(ZVisualStackedPageInfo *page);

    // Use new to create a pointer to ZVisualStackedPage derived class
    virtual ZVisualStackedPage *CreatePage(LPCTSTR title, UINT dlgid) = 0;

    //{{AFX_VIRTUAL(ZVisualStackedDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(ZVisualStackedDialog)
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

friend class ZVisualStackedDialogIterator;
};

//
// Iterator class to iterate thru the list of pages maintained by the
// ZVisualStackedDialog class
//

class AFX_EXT_CLASS ZVisualStackedDialogIterator 
{
private:
    const ZVisualStackedDialog& Owner;
    POSITION Pos;
public:
    ZVisualStackedDialogIterator(const ZVisualStackedDialog& obj) 
            :Owner(obj) { Reset(); }
    void Reset(void) { Pos = Owner.List.GetHeadPosition(); }
    void Next(void) { Owner.List.GetNext(Pos); }
    ZVisualStackedPageInfo* Current(void) 
                { return (ZVisualStackedPageInfo*)Owner.List.GetAt(Pos); }
    BOOL IsDone(void) { return (Pos == NULL) ? TRUE : FALSE; }
};
