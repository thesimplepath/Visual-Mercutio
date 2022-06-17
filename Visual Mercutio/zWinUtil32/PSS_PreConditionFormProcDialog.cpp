/****************************************************************************
 * ==> PSS_PreConditionFormProcDialog --------------------------------------*
 ****************************************************************************
 * Description : Provides a pre-condition form process dialog box           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PreConditionFormProcDialog.h"

// processsoft
#include "zBaseLib\PSS_FolderStamp.h"
#include "zBaseLib\PSS_MsgBox.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PreConditionFormProcDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PreConditionFormProcDialog)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PreConditionFormProcDialog
//---------------------------------------------------------------------------
PSS_PreConditionFormProcDialog::PSS_PreConditionFormProcDialog(const CString& activityName,
                                                               CStringArray&  formNameArray,
                                                               BOOL           fileRequired,
                                                               BOOL           isLast,
                                                               BOOL           isProcess,
                                                               CStringArray&  fileArray,
                                                               CWnd*          pParent) :
    PSS_WizardDialog(PSS_PreConditionFormProcDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZPREACTIVITYTITLE_WZ,
                     IDS_WZPREACTIVITYTITLEFORM_T),
    m_ActivityName(_T(activityName)),
    m_FormNameArray(formNameArray),
    m_FileArray(fileArray),
    m_CurrentFormIndex(0),
    m_FileRequired(fileRequired),
    m_IsLast(isLast),
    m_IsProcess(isProcess)
{
    CString title;

    if (m_IsProcess)
        VERIFY(title.LoadString(IDS_SELECTPROCESS_TITLE));
    else
        VERIFY(title.LoadString(IDS_SELECTFORM_TITLE));

    // set the right file filter
    CString filter;

    if (m_IsProcess)
        VERIFY(filter.LoadString(IDS_PROCESSFILE_FILTERTXT));
    else
        VERIFY(filter.LoadString(IDS_FORMFILE_FILTERTXT));

    // next string please
    filter += (char)'\0';

    if (m_IsProcess)
        filter += g_SearchAllProcessExtension;
    else
        filter += g_SearchAllFormExtension;

    // last string
    filter += (char)'\0';

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    filter += allFilter;
    filter += (char)'\0';
    filter += "*.*";
    filter += (char)'\0';

    // defines the edit as search for file
    m_FileName.SetSearchType(PSS_SearchEditButton::IEType::IE_T_File, title, _T(""), filter, 2);
}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PreConditionFormProcDialog)
    DDX_Control(pDX, IDC_PROCFORMFILENAME, m_FileName);
    DDX_Text   (pDX, IDC_ACTIVITYNAME,     m_ActivityName);
    DDX_Text   (pDX, IDC_FORMPROCNAME,     m_FormName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PreConditionFormProcDialog::OnInitDialog()
{
    // if at least one form name, set the form name
    if (m_FormNameArray.GetSize() > 0)
        m_FormName = m_FormNameArray.GetAt(0);

    PSS_WizardDialog::OnInitDialog();

    if (m_IsProcess)
        SetWizardBodyText(IDS_WZPREACTIVITYTITLEPROC_T);

    if (GetDlgItem(IDC_FORM_TEXT))
        GetDlgItem(IDC_FORM_TEXT)->ShowWindow(m_IsProcess ? SW_HIDE : SW_SHOW);

    if (GetDlgItem(IDC_PROC_TEXT))
        GetDlgItem(IDC_PROC_TEXT)->ShowWindow(!m_IsProcess ? SW_HIDE : SW_SHOW);

    BuildText( ( m_FormNameArray.GetSize() > 0 ) ? 0 : -1 );

    CheckStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcDialog::OnOK()
{
    if (!CheckFiles())
        return;

    CString fileName;
    m_FileName.GetWindowText(fileName);

    // save file name
    m_FileArray.Add(fileName);

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcDialog::OnNext()
{
    if (!CheckFiles())
        return;

    CString fileName;
    m_FileName.GetWindowText(fileName);

    // save file name
    m_FileArray.Add(fileName);

    // end reached?
    if (m_CurrentFormIndex >= m_FormNameArray.GetSize() - 1)
    {
        EndDialog(IDNEXT);
        return;
    }

    // next form
    ++m_CurrentFormIndex;

    BuildText(m_CurrentFormIndex);

    m_FileName.SetWindowText(_T(""));

    CheckStates();

    UpdateData(FALSE);
}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcDialog::BuildText(int formIndex)
{
    CString text;

    if (formIndex < 0)
    {
        if (m_IsProcess)
            AfxFormatString1(text, IDS_BASEONPROCNONAME_EXPLANATION, m_ActivityName);
        else
            AfxFormatString1(text, IDS_BASEONFORMNONAME_EXPLANATION, m_ActivityName);
    }
    else
    if (m_IsProcess)
        AfxFormatString2(text, IDS_BASEONPROC_EXPLANATION, m_ActivityName, m_FormNameArray.GetAt(formIndex));
    else
        AfxFormatString2(text, IDS_BASEONFORM_EXPLANATION, m_ActivityName, m_FormNameArray.GetAt(formIndex));

    if (GetDlgItem(IDC_FORMPROC_EXPLANATION))
        GetDlgItem(IDC_FORMPROC_EXPLANATION)->SetWindowText(text);
}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcDialog::CheckStates()
{
    if (m_IsLast && (m_FormNameArray.GetSize() > 0 || m_CurrentFormIndex == m_FormNameArray.GetSize() - 1))
    {
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->ShowWindow(SW_SHOW);

        if (GetDlgItem(IDNEXT))
            GetDlgItem(IDNEXT)->ShowWindow(SW_HIDE);
    }
    else
    {
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

        if (GetDlgItem(IDNEXT))
            GetDlgItem(IDNEXT)->ShowWindow(SW_SHOW);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PreConditionFormProcDialog::CheckFiles()
{
    CString fileName;
    m_FileName.GetWindowText(fileName);

    if (m_FileRequired)
    {
        if (fileName.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROCFORMFILEMISSING, MB_OK);

            return FALSE;
        }

        if ((m_FormNameArray.GetSize() > 0 && m_CurrentFormIndex <= m_FormNameArray.GetSize() - 1))
        {
            PSS_FolderStamp stamp;

            if (!stamp.ReadFromFile(fileName))
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_PROCFORMFILEINVALID, MB_OK);

                return FALSE;
            }

            if (stamp.GetTitle() != m_FormNameArray.GetAt(m_CurrentFormIndex))
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_PROCFORMFILE_TITLENEQ, MB_OK);

                return FALSE;
            }
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
