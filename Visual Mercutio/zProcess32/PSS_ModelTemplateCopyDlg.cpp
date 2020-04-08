/****************************************************************************
 * ==> PSS_ModelTemplateCopyDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a model template copy dialog                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelTemplateCopyDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"

// resources
#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelTemplateCopyDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_ModelTemplateCopyDlg)
    ON_EN_CHANGE(IDC_TITLE, OnChangeTitle)
    ON_BN_CLICKED(ID_DONTSAVE, OnDontSave)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelTemplateCopyDlg
//---------------------------------------------------------------------------
PSS_ModelTemplateCopyDlg::PSS_ModelTemplateCopyDlg(const CString&   fileExtension,
                                                   const CString&   dir,
                                                   PSS_FolderStamp* pFolderStamp,
                                                   BOOL             allowReplace,
                                                   CWnd*            pParent) :
    PSS_Dialog(PSS_ModelTemplateCopyDlg::IDD, TRUE, pParent),
    m_pFolderStamp(pFolderStamp),
    m_FileExtension(fileExtension),
    m_Directory(dir),
    m_AllowReplace(allowReplace),
    m_FileExist(false)
{
    if (m_pFolderStamp)
    {
        m_Title       = m_pFolderStamp->GetTitle();
        m_Description = m_pFolderStamp->GetDescription();

        #ifndef _WIN32
            // in 16 bit only, 8 character are used for the file name
            m_FileName = m_pFolderStamp->GetTitle().Left(8);
        #endif
        #ifdef _WIN32
                m_FileName = m_pFolderStamp->GetTitle();
        #endif
    }

    m_ModelDirectory.SetSearchType(PSS_SearchEditButton::IE_T_Directory, IDS_CHOOSEDIRECTORY, m_Directory);

    // if the directory is empty, use the current one
    if (m_Directory.IsEmpty())
        ::GetCurrentDirectory(500, m_Directory.GetBuffer(500));
}
//---------------------------------------------------------------------------
PSS_ModelTemplateCopyDlg::~PSS_ModelTemplateCopyDlg()
{}
//---------------------------------------------------------------------------
void PSS_ModelTemplateCopyDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ModelTemplateCopyDlg)
    DDX_Control(pDX, IDC_MODELDIR,    m_ModelDirectory);
    DDX_Text   (pDX, IDC_TITLE,       m_Title);
    DDX_Text   (pDX, IDC_DESCRIPTION, m_Description);
    DDX_Text   (pDX, IDC_FILENAME,    m_FileName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ModelTemplateCopyDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    m_ModelDirectory.SetWindowText(m_Directory);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ModelTemplateCopyDlg::OnChangeTitle()
{
    // NOTE a rich edit control will not send this notification unless the ZIDialog::OnInitDialog()
    // function is overridden and the CRichEditCtrl().SetEventMask() is called with the ENM_CHANGE
    // flag in the mask

    // get input and change the file name
    UpdateData(TRUE);

    #ifndef _WIN32
        // in 16 bit only, copy 8 character from the title
        m_FileName = m_sTitle.Left(8);
    #endif
    #ifdef _WIN32
        m_FileName = m_Title;
    #endif

    UpdateData(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ModelTemplateCopyDlg::OnDontSave()
{
    PSS_Dialog::EndDialog(ID_DONTSAVE);
}
//---------------------------------------------------------------------------
void PSS_ModelTemplateCopyDlg::OnOK()
{
    UpdateData(TRUE);

    m_ModelDirectory.GetWindowText(m_Directory);
    m_Directory = PSS_Directory::NormalizeDirectory(m_Directory);

    if (m_Directory.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_DIRECTORY_MISSING, MB_OK);
        return;
    }

    if (m_FileName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FILENAMEMISSING, MB_OK);
        return;
    }

    if (m_Title.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_TITLEMISSING, MB_OK);
        return;
    }

    // check if normal template is specified
    if (m_FileName + _T(".") + m_FileExtension == g_NormalModelTemplateFileName)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NORMALTMPL_CANNOTBEUSED, MB_OK);
        return;
    }

    #ifndef _WIN32
        if (m_FileName.GetLength() > 8 || m_FileName.Find('.') != -1)
    #endif
    #ifdef _WIN32
        if (m_FileName.Find('.') != -1)
    #endif
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_TEMPLATEFILENAMEERROR, MB_OK);
            return;
        }

    // build the complete file name to check if already exist
    const CString fileName = m_Directory + _T("\\") + m_FileName + _T(".") + m_FileExtension;
    CFileStatus   status;

    if (CFile::GetStatus(fileName, status))
    {
        PSS_MsgBox mBox;

        // if does not allow file replacement, show an error message and return
        if (!m_AllowReplace)
        {
            mBox.Show(IDS_FORMALREADYEXIST, MB_OK);
            return;
        }

        if (mBox.Show(IDS_FORMALREADYEXIST_CONTREPLACE, MB_YESNO) == IDNO)
            return;

        // set the flag for selected file exists
        m_FileExist = true;
    }

    // set the selected file name
    m_FileName = fileName;
    UpdateData(FALSE);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
