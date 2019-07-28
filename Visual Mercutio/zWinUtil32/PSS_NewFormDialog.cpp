/****************************************************************************
 * ==> PSS_NewForm ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a new form wizard dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_NewFormDialog.h"

#include "zBaseLib\msgbox.h"
#include "planfin.hdf"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_NewFormPropertySheet, PSS_BasePropSheet)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_NewFormPropertySheet, PSS_BasePropSheet)
    //{{AFX_MSG_MAP(PSS_NewFormPropertySheet)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_NewFormPropertySheet
//---------------------------------------------------------------------------
PSS_NewFormPropertySheet::PSS_NewFormPropertySheet(ZDTemplateManager* pTemplateManager) :
    PSS_BasePropSheet(),
    m_pTemplateManager(pTemplateManager),
    m_FirstInitialization(TRUE)
{
    Initialize();
    m_FirstInitialization = FALSE;
}
//---------------------------------------------------------------------------
PSS_NewFormPropertySheet::PSS_NewFormPropertySheet(const PSS_NewFormPropertySheet& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_NewFormPropertySheet::~PSS_NewFormPropertySheet()
{
    ClearContents();
}
//---------------------------------------------------------------------------
const PSS_NewFormPropertySheet& PSS_NewFormPropertySheet::operator = (const PSS_NewFormPropertySheet& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_NewFormPropertySheet::Initialize()
{
    ASSERT(m_pTemplateManager);

    // set the size of the internal array for pointer page
    if (m_FirstInitialization)
        PSS_BasePropSheet::GetPageArray().SetSize(m_pTemplateManager->GetSize());

    const std::size_t templateCount = m_pTemplateManager->GetSize();

    // iterate through all template directory
    for (std::size_t i = 0; i < templateCount; ++i)
    {
        ZDTemplateDir* pTemplateDir = m_pTemplateManager->GetTemplateDirAt(i);

        if (!pTemplateDir)
            continue;

        std::unique_ptr<PSS_GenericFormPage> pFormPage
                (new PSS_GenericFormPage(NULL, pTemplateDir->GetTitle(), m_pTemplateManager));

        if (!m_FirstInitialization)
        {
            // remove the old page
            RemovePage(0);
            delete (m_PageArray[i]);
        }

        // replace the pointer to the previous page or insert the right pointer
        PSS_BasePropSheet::GetPageArray().SetAt(i, pFormPage.get());
        AddPage(pFormPage.get());
        pFormPage.release();
    }

    m_RootCaption = m_pTemplateManager->GetRootCaption();

    // activate the first page to refresh the contents (but not in Initialization mode)
    if (!m_FirstInitialization)
        SetActivePage(0);
}
//---------------------------------------------------------------------------
void PSS_NewFormPropertySheet::ClearContents()
{
    const int pageCount = m_PageArray.GetSize();

    // free the pages allocated on the fly by the PSS_NewForm class
    for (int i = 0; i < pageCount; ++i)
        delete (m_PageArray[i]);

    PSS_BasePropSheet::GetPageArray().RemoveAll();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_NewFormDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_NewFormDialog)
    ON_BN_CLICKED(IDC_MOVE_TOGENERAL, OnMoveToGeneralTab)
    ON_MESSAGE(UM_SETCOMMENT, OnCommentChange)
    ON_MESSAGE(UM_FORMS_SELECTED, OnFormsSelected)
    ON_MESSAGE(UM_FORMACTIVATE, OnFormActivate)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_NewFormDialog
//---------------------------------------------------------------------------
PSS_NewFormDialog::PSS_NewFormDialog(ZDTemplateManager*        pTemplateManager,
                                     IEDialogFormType          type,
                                     IEDialogFormExtensionType extensionType) :
    ZIWizardDialog(PSS_NewFormDialog::IDD,
                   IDB_WZBMP2,
                   0,
                   0,
                   0,
                   0),
    m_CopyFormat(TRUE),
    m_pTemplateManager(pTemplateManager),
    m_pSystemPropertySheet(NULL),
    m_pCurrentTemplateDir(NULL),
    m_pCurrentTemplateFile(NULL),
    m_Type(type),
    m_ExtensionType(extensionType)
{
    ASSERT(m_pTemplateManager);
    m_pSystemPropertySheet = new PSS_NewFormPropertySheet(m_pTemplateManager);
}
//---------------------------------------------------------------------------
PSS_NewFormDialog::~PSS_NewFormDialog()
{
    if (m_pSystemPropertySheet)
        delete m_pSystemPropertySheet;
}
//---------------------------------------------------------------------------
void PSS_NewFormDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_NewFormDialog)
    DDX_Control(pDX, IDC_COPYFORMAT, m_CopyFormatWnd);
    DDX_Control(pDX, IDOK,           m_Button);
    DDX_Text   (pDX, IDC_COMMENT,    m_Comment);
    DDX_Check  (pDX, IDC_COPYFORMAT, m_CopyFormat);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_NewFormDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    m_MoveToGeneralTabBtn.AutoLoad(IDC_MOVE_TOGENERAL, this);
    m_MoveToGeneralTabBtn.EnableWindow(FALSE);
    m_Button.EnableWindow(FALSE);

    CString text;
    UINT    resID;

    switch (m_Type)
    {
        case IE_T_AttachForm:
            // on attach, change the window title and the button text
            SetWizardWindowTitle(IDS_ATTACHTITLE);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_PROCESSTEXT; break;
                case IE_ET_ModelForm:   resID = IDS_MODELTEXT;   break;
                default:                resID = IDS_FORMSTEXT;   break;
            }

            SetWizardSubjectText(resID);
            SetWizardBodyText(IDS_ATTACHFORMDLG_TEXT);

            // the button text
            text.LoadString(IDS_ATTACHBUTTONTEXT);
            m_Button.SetWindowText(text);

            m_MoveToGeneralTabBtn.ShowWindow(SW_HIDE);

            break;

        case IE_T_OpenForm:
            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_OPENPROCESSTITLE; break;
                case IE_ET_ModelForm:   resID = IDS_OPENMODELTITLE;   break;
                default:                resID = IDS_OPENTITLE;        break;
            }

            SetWizardWindowTitle(resID);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_PROCESSTEXT; break;
                case IE_ET_ModelForm:   resID = IDS_MODELTEXT;   break;
                default:                resID = IDS_FORMSTEXT;   break;
            }

            SetWizardSubjectText(resID);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_OPENPROCESSDLG_TEXT; break;
                case IE_ET_ModelForm:   resID = IDS_OPENMODELDLG_TEXT;   break;
                default:                resID = IDS_OPENFORMDLG_TEXT;    break;
            }

            SetWizardBodyText(resID);

            // the button text
            text.LoadString(IDS_OPENBUTTONTEXT);
            m_Button.SetWindowText(text);

            m_MoveToGeneralTabBtn.ShowWindow(SW_HIDE);
            m_CopyFormatWnd.ShowWindow(SW_HIDE);

            break;

        case IE_T_StartForm:
            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_STARTPROCESSTITLE; break;
                case IE_ET_ModelForm:   resID = IDS_STARTMODELTITLE;   break;
                default:                resID = IDS_STARTTITLE;        break;
            }

            SetWizardWindowTitle(resID);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_PROCESSTEXT; break;
                case IE_ET_ModelForm:   resID = IDS_MODELTEXT;   break;
                default:                resID = IDS_FORMSTEXT;   break;
            }

            SetWizardSubjectText(resID);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_STARTPROCESSDLG_TEXT; break;
                case IE_ET_ModelForm:   resID = IDS_STARTMODELDLG_TEXT;   break;
                default:                resID = IDS_STARTFORMDLG_TEXT;    break;
            }

            SetWizardBodyText(resID);

            // the button text
            text.LoadString(IDS_STARTBUTTONTEXT);
            m_Button.SetWindowText(text);

            m_CopyFormatWnd.ShowWindow(SW_HIDE);
            m_MoveToGeneralTabBtn.ShowWindow(SW_SHOW);

            break;

        case IE_T_SelectForm:
            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_SELECTPROCESSTITLE; break;
                case IE_ET_ModelForm:   resID = IDS_SELECTMODELTITLE;   break;
                default:                resID = IDS_SELECTTITLE;        break;
            }

            SetWizardWindowTitle(resID);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_PROCESSTEXT; break;
                case IE_ET_ModelForm:   resID = IDS_MODELTEXT;   break;
                default:                resID = IDS_FORMSTEXT;   break;
            }

            SetWizardSubjectText(resID);

            switch (m_ExtensionType)
            {
                case IE_ET_ProcessForm: resID = IDS_SELECTPROCESSDLG_TEXT; break;
                case IE_ET_ModelForm:   resID = IDS_SELECTMODELDLG_TEXT;   break;
                default:                resID = IDS_SELECTFORMDLG_TEXT;    break;
            }

            SetWizardBodyText(resID);

            // the button text
            text.LoadString(IDS_SELECTBUTTONTEXT);
            m_Button.SetWindowText(text);

            m_CopyFormatWnd.ShowWindow(SW_HIDE);
            m_MoveToGeneralTabBtn.ShowWindow(SW_SHOW);

            break;
    }

    CRect rect;

    // get the dialog client rect to reposition the property sheet
    GetClientRect(&rect);

    // create the dialog child property sheet
    m_pSystemPropertySheet->Create(this, WS_SYSMENU | WS_CHILD | DS_MODALFRAME);

    CRect propRect;

    // resize the property sheet
    m_pSystemPropertySheet->GetClientRect(&propRect);

    #ifndef _WIN32
        m_pSystemPropertySheet->MoveWindow(rect.left + 3, rect.top + 75, propRect.Width(), propRect.Height() - 25);
    #else
        m_pSystemPropertySheet->MoveWindow(rect.left + 3, rect.top + 75, propRect.Width(), propRect.Height());
    #endif

    // show the property sheet
    m_pSystemPropertySheet->ShowWindow(SW_SHOW);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_NewFormDialog::OnCommentChange(UINT message, LONG lParam)
{
    ASSERT(m_pTemplateManager);

    PSS_GenericFormPage* pFormPage =
            ((PSS_GenericFormPage*)m_pSystemPropertySheet->GetPageArray()[m_pSystemPropertySheet->GetCurPage()]);
    ASSERT(pFormPage);

    // find the right template directory
    m_pCurrentTemplateDir = m_pTemplateManager->FindTemplateDir(pFormPage->GetCaption());

    // no template?
    if (!m_pCurrentTemplateDir)
        return 0;

    // find the right file
    m_pCurrentTemplateFile = m_pCurrentTemplateDir->GetTemplateFileAt(message);

    if (m_pCurrentTemplateFile)
    {
        m_SelectedFormName = m_pCurrentTemplateFile->GetTitle();
        m_SelectedFileName = m_pCurrentTemplateFile->GetFilename();
        m_Comment          = m_pCurrentTemplateFile->GetDescription();

        UpdateData(FALSE);
    }

    // check if the move to general button tab may be enabled
    m_MoveToGeneralTabBtn.EnableWindow(pFormPage->GetCaption() != m_pSystemPropertySheet->GetRootCaption());
    m_Button.EnableWindow(TRUE);

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_NewFormDialog::OnFormActivate(UINT message, LONG lParam)
{
    m_MoveToGeneralTabBtn.EnableWindow(FALSE);
    m_Button.EnableWindow(FALSE);

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_NewFormDialog::OnFormsSelected(UINT message, LONG lParam)
{
    OnOK();

    return 1;
}
//---------------------------------------------------------------------------
void PSS_NewFormDialog::OnMoveToGeneralTab()
{
    ASSERT(m_pTemplateManager);

    // find the right template directory
    if (m_pTemplateManager->MoveTemplateFile(m_pCurrentTemplateFile->GetFilename(),
                                             m_pCurrentTemplateDir->GetTitle(),
                                             m_pSystemPropertySheet->GetRootCaption()))
    {
        m_pSystemPropertySheet->Initialize();
        m_SelectedFileName     = _T("");
        m_pCurrentTemplateFile = NULL;
        m_pCurrentTemplateDir  = NULL;
    }
}
//---------------------------------------------------------------------------
void PSS_NewFormDialog::OnOK()
{
    ZIWizardDialog::OnOK();
}
//---------------------------------------------------------------------------
