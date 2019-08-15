/****************************************************************************
 * ==> PSS_TemplateCopyDialog ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a template copy dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TemplateCopyDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TemplateCopyDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_TemplateCopyDialog)
    ON_EN_CHANGE(IDC_TITLE, OnChangeTitle)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TemplateCopyDialog
//---------------------------------------------------------------------------
PSS_TemplateCopyDialog::PSS_TemplateCopyDialog(ZDTemplateManager* pTemplateManager,
                                               const CString&     fileExtension,
                                               PSS_FolderStamp*   pFolderStamp,
                                               BOOL               allowReplace,
                                               CWnd*              pParent) :
    ZIDialog(PSS_TemplateCopyDialog::IDD, TRUE, pParent),
    m_pTemplateManager(pTemplateManager), 
    m_pFolderStamp(pFolderStamp),
    m_FileExtension(fileExtension),
    m_AllowReplace(allowReplace),
    m_FileExist(false)
{
    if (m_pFolderStamp)
    {
        m_Title = m_pFolderStamp->GetTitle();
        #ifdef _WIN32
            m_FileName = m_pFolderStamp->GetTitle();
        #else
            // in 16 bit, only 8 character for the file name
            m_FileName = m_pFolderStamp->GetTitle().Left(8);
        #endif
        m_Description = m_pFolderStamp->GetExplanation();
    }
}
//---------------------------------------------------------------------------
void PSS_TemplateCopyDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_TemplateCopyDialog)
    DDX_Control(pDX, IDC_TEMPLATEDIR, m_TemplateDirList);
    DDX_Text   (pDX, IDC_TITLE,       m_Title);
    DDX_Text   (pDX, IDC_FILENAME,    m_FileName);
    DDX_Text   (pDX, IDC_DESCRIPTION, m_Description);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateCopyDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    #ifdef _WIN32
        m_TemplateDirList.Initialize(m_pTemplateManager, TRUE);
    #else
        // initialize the template list
        m_TemplateDirList.ResetContent();

        const std::size_t templateCount = m_pTemplateManager->GetSize();

        // iterate through all template directory and insert all pages from the template manager
        for (std::size_t i = 0; i < templateCount; ++i)
        {
            ZDTemplateDir* pTemplateDir = m_pTemplateManager->GetTemplateDirAt(i);

            if (pTemplateDir)
                m_TemplateDirList.AddString(pTemplateDir->GetTitle());
        }

        m_TemplateDirList.SetCurSel(0);
    #endif

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_TemplateCopyDialog::OnChangeTitle()
{
    // NOTE be careful, a rich edit control will not send this notification unless the ZIDialog::OnInitDialog()
    // is overriden, and the CRichEditCtrl().SetEventMask() is called with the ENM_CHANGE flag in its mask

    // get input and change the file name
    UpdateData(TRUE);

    #ifdef _WIN32
        m_FileName = m_Title;
    #else
        // in 16 bit, copy only 8 character of the title
        m_FileName = m_Title.Left(8);
    #endif

    UpdateData(FALSE);
}
//---------------------------------------------------------------------------
void PSS_TemplateCopyDialog::OnOK()
{
    UpdateData(TRUE);

    // get the template directory
    #ifdef _WIN32
        // insert all pages from the template manager
        ZDTemplateDir* pTemplateDir = m_TemplateDirList.GetSelectedFolderItem();
    #else
        const int currentSelection = m_TemplateDirList.GetCurSel();

        if (currentSelection == LB_ERR)
            return;

        // insert all pages from the template manager
        ZDTemplateDir* pTemplateDir = m_pTemplateManager->GetTemplateDirAt(currentSelection);
    #endif

    if (!pTemplateDir)
    {
        MsgBox mBox;
        mBox.DisplayMsgBox(IDS_CATEGORYMISSING, MB_OK);
        return;
    }

    if (m_FileName.IsEmpty())
    {
        MsgBox mBox;
        mBox.DisplayMsgBox(IDS_FILENAMEMISSING, MB_OK);
        return;
    }

    if (m_Title.IsEmpty())
    {
        MsgBox mBox;
        mBox.DisplayMsgBox(IDS_TITLEMISSING, MB_OK);
        return;
    }

    #ifdef _WIN32
        if (m_FileName.Find('.') != -1)
    #else
        if (m_FileName.GetLength() > 8 || m_FileName.Find('.') != -1)
    #endif
    {
        MsgBox mBox;
        mBox.DisplayMsgBox(IDS_TEMPLATEFILENAMEERROR, MB_OK);
        return;
    }

    // build the complete file name to know if already exist
    const CString     fileName = pTemplateDir->GetDirectory() + "\\" + m_FileName + "." + m_FileExtension;
          CFileStatus status;

    if (CFile::GetStatus(fileName, status))
    {
        MsgBox mBox;

        // if not exists, allow file replacement dialog box if possible, otherwise show an error message and return
        if (!m_AllowReplace)
        {
            mBox.DisplayMsgBox(IDS_FORMALREADYEXIST, MB_OK);
            return;
        }
        else
        if (mBox.DisplayMsgBox(IDS_FORMALREADYEXIST_CONTREPLACE, MB_YESNO) == IDNO)
            return;

        // set the selected file exists flag
        m_FileExist = true;
    }

    // set the complete file name
    m_FileName = fileName;

    UpdateData(FALSE);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
