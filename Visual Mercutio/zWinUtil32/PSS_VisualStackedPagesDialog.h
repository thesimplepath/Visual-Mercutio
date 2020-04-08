/****************************************************************************
 * ==> PSS_VisualStackedPagesDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a visual stacked pages dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************
 * Usage instructions:                                                      *
 * A. Create a dialog and modify its base class from CDialog to             *
 *    ZVisualStackedDialog. Add controls as you like it.  Allocate one      *
 *    control (listbox or similar) to contain a list of pages. Add a        *
 *    picture control as a placeholder for stacked pages                    *
 * B. Add a picture control ID to previous dialog constructor               *
 * C. Add a pointer variable of type ZVisualStackedPageInfo to dialog. It   *
 *    holds a pointer to currently active page. Initialize it to NULL       *
 * D. Add implementation of CreatePage() abstract function. It should       *
 *    perform "new ZVisualStackedPage derived class"                        *
 * E. Create pages (child dialogs with border and disable set to off).      *
 *    Modify base class from CDialog to ZVisualStackedPage                  *
 * F. In ZVisualStackedDialog::OnInitDialog() use AddPage() to add a page   *
 *    and also add a page title to a listbox (or similar) for navigating    *
 *    through the pages. Activate a page and initialize a pointer to        *
 *    currently active page                                                 *
 * G. Add a handler when a listbox item is changed. In the  handler, first  *
 *    deactivate currently active page. Then activate a selected page and   *
 *    update a pointer to point to this new page                            *
 * H. ZVisualStackedDialog will automatically delete pages                  *
 * I. Use ZVisualStackedDialogIterator to iterate through the pages one at  *
 *    a time and perform any action                                         *
 * J. Override ZVisualStackedPage virtual functions On...                   *
 ****************************************************************************/

#ifndef PSS_VisualStackedPageDialogH
#define PSS_VisualStackedPageDialogH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// class prototypes
class PSS_VisualStackedPageDialog;

/**
* Helper structure to keep information about each page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
struct AFX_EXT_CLASS PSS_VisualStackedPageInfo
{
    PSS_VisualStackedPageDialog* m_pDialog;
    CString                      m_Title;    // page title
    UINT                         m_DialogID; // page resource ID
    long                         m_HelpID;
    DWORD                        m_Data1;    // user defined data
    DWORD                        m_Data2;    // user defined data
    BOOL                         m_Created;

    PSS_VisualStackedPageInfo() :
        m_pDialog(NULL),
        m_DialogID(-1),
        m_HelpID(-1),
        m_Data1(0),
        m_Data2(0),
        m_Created(FALSE)
    {}
};

/**
* Visual stacked page dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_VisualStackedPageDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param pTemplateName - template name
        *@param pParent - parent window, can be NULL
        */
        PSS_VisualStackedPageDialog(LPCTSTR pTemplateName, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param templateID - template identifier
        *@param pParent - parent window, can be NULL
        */
        PSS_VisualStackedPageDialog(UINT templateID, CWnd* pParent = NULL);

        virtual ~PSS_VisualStackedPageDialog();

        /**
        * Called when dialog become active
        */
        virtual void OnSetActive();

        /**
        * Called when dialog become inactive
        */
        virtual void OnKillActive();

        /**
        * Called when a page is created
        */
        virtual void OnCreatePage();

        /**
        * Called when a page is deleted
        */
        virtual void OnDestroyPage();

    protected:
        //{{AFX_VIRTUAL(PSS_VisualStackedPageDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        //{{AFX_MSG(PSS_VisualStackedPageDialog)
        virtual void OnOK();
        virtual void OnCancel();
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Visual stacked pages dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*@note This class is abstract, must derive a class and implement CreatePage() member function
*@note Usage is very easy and consists of several steps:
*      - Create a dialog and place any controls you need. Be sure to put a control which contains a list of pages
*        (listbox, tree control or similar). Also place a picture control which is a placeholder for pages
*      - Use class wizard to create a class associated with this dialog resource. Manually modify a base class from
*        CDialog to ZVisualStackedDialog. Modify a constructor of ZVisualStackedDialog so that it has a resource ID
*        of the picture control as a first argument. You must implement a function CreatePage() which is abstract in
*        base class ZVisualStackedDialog. This function should return a pointer to a page dialog (use new to make an
*        instance of a class derived from ZVisualStackedPage; see next step). Also add a private pointer to object
*        of type ZVisualStackedPageInfo (for example CurrentPage). This pointer should be initially set to NULL (it
*        will point to a currently active page information structure)
*      - Create a dialog resource for each stacked page. Set border to none, dialog is disabled and is a child dialog.
*        Use class wizard to create a class associated with each page and manually modify base class from CDialog to
*        ZVisualStackedPage
*      - In ZVisualStackedDialog derived class OnInitDialog() member function, use the following pseudocode to add
*        pages to the stacked dialog:
*          ZVisualStackedPageInfo *info;
*          info = AddPage("Title A", IDD_PAGE_A);
*      - Add "Title A" to listbox (or treeview) which contans a list of page titles
*      - Use SetItemData((DWORD)info) to associate page information structure with listbox item
*      - This code will add a page to a stacked dialog internal list and also add a title of the page to the listbox (or
*        other control) which enables the user to select a page to work with. AddPage() function will execute abstract
*        function CreatePage() which must be implemented. Also initialize the CurrentPage pointer to point to the
*        ZVisualStackedPageInfo pointer of the current page. Select title in listbox which corresponds to selected page
*      - Add a handler for selection change in listbox. Use the following pseudo code in the handler
*      - Get an index of current selection
*          ZVisualStackedPageInfo *info = GetItemData(selection)
*          DeactivatePage(CurrentPage)
*          CurrentPage = info
*          ActivatePage(CurrentPage)
*      - CurrentPage is a private pointer which is initialised in OnInitDialog() and points to the current page
*      - That's all. Now, when you select a listbox item, selection change handler will deactivate the current page and
*        activate the page associated with the new selection in the listbox. You can also use DelAllPages() member function
*        to remove all pages (destroy and delete them) and add a completely different set of pages (depending on your
*        application). OnDestroy member function of ZVisualStackedDialog class will clean up so that there are no
*        memory/resource leaks
*/
class AFX_EXT_CLASS PSS_VisualStackedPagesDialog : public CDialog
{
    friend class PSS_VisualStackedPagesDialogIterator;

    public:
        /**
        * Constructor
        *@param placeholder - placeholder
        *@param pTemplateName - template name
        *@param pParent - parent window, can be NULL
        */
        PSS_VisualStackedPagesDialog(UINT placeholder, LPCTSTR pTemplateName, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param placeholder - placeholder
        *@param templateID - template identifier
        *@param pParent - parent window, can be NULL
        */
        PSS_VisualStackedPagesDialog(UINT placeholder, UINT templateID, CWnd* pParent = NULL);

        virtual ~PSS_VisualStackedPagesDialog();

        /**
        * Adds a page
        *@param pTitle - page title
        *@param dlgID - dialog identifier
        *@param helpID - help page identifier
        *@param data1 - user data 1
        *@param data2 - user data 2
        *@return newly added page, NULL on error
        */
        virtual PSS_VisualStackedPageInfo* AddPage(LPCTSTR pTitle,
                                                   UINT    dlgID,
                                                   long    helpID = 0L,
                                                   DWORD   data1  = 0,
                                                   DWORD   data2  = 0);

        /**
        * Deletes a page
        *@param pPage - page to delete
        */
        virtual void DelPage(PSS_VisualStackedPageInfo* pPage);

        /**
        * Deletes all the page
        */
        virtual void DelAllPages();

        /**
        * Activates a page
        *@param pPage - page to activate
        */
        virtual void ActivatePage(PSS_VisualStackedPageInfo* pPage);

        /**
        * Deactivates a page
        *@param pPage - page to deactivate
        */
        virtual void DeactivatePage(PSS_VisualStackedPageInfo* pPage);

        /**
        * Creates a page
        *@param pTitle - page title
        *@param dlgID - dialog identifier
        */
        virtual PSS_VisualStackedPageDialog* CreatePage(LPCTSTR pTitle, UINT dlgID) = 0;

    protected:
        CTypedPtrList<CPtrList, PSS_VisualStackedPageInfo*> m_List;
        UINT                                                m_PlaceHolder;

        //{{AFX_VIRTUAL(PSS_VisualStackedPagesDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        //{{AFX_MSG(PSS_VisualStackedPagesDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnDestroy();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Initializes the dialog
        *@param placeholder - placeholder
        */
        void Init(UINT placeholder);

        /**
        * Flushes the dialog
        */
        void Flush();
};

/**
* Iterator class to iterate through the page list maintained by the PSS_VisualStackedDialog class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_VisualStackedPagesDialogIterator
{
    public:
        /**
        * Constructor
        *@param owner - iterator owner
        */
        PSS_VisualStackedPagesDialogIterator(const PSS_VisualStackedPagesDialog& owner);

        /**
        * Resets the iterator
        */
        virtual void Reset();

        /**
        * Selects the next item
        */
        virtual void Next();

        /**
        * Gets the current item
        *@return the current item
        */
        virtual PSS_VisualStackedPageInfo* Current();

        /**
        * Checks if iterator reached the end
        *@return TRUE if iterator reached the end, otherwise FALSE
        */
        virtual BOOL IsDone();

    private:
        const PSS_VisualStackedPagesDialog& m_Owner;
        POSITION                            m_pPos;
};

#endif
