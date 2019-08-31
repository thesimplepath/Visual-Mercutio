/****************************************************************************
 * ==> PSS_WorkspaceFilePropertiesDlg --------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace file properties dialog box            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceFilePropertiesDlg.h"

// processsoft
#include "PSS_File.h"
#include "zBaseLibRes.h"
#include "PSS_MsgBox.h"
#include "PSS_FileDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceFilePropertiesDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_WorkspaceFilePropertiesDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceFilePropertiesDlg
//---------------------------------------------------------------------------
PSS_WorkspaceFilePropertiesDlg::PSS_WorkspaceFilePropertiesDlg(ZBWorkspaceGroupEntity* pRootGroup,
                                                               const CString&          title,
                                                               const CString&          completeFileName,
                                                               CWnd*                   pParent) :
    CDialog(PSS_WorkspaceFilePropertiesDlg::IDD, pParent),
    m_FileTitle(title),
    m_FileName(completeFileName)
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceFilePropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WorkspaceFilePropertiesDlg)
    DDX_Text(pDX, IDC_FILE_TITLE,        m_FileTitle);
    DDX_Text(pDX, IDC_FILE_COMPLETEPATH, m_FileName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceFilePropertiesDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE the OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceFilePropertiesDlg::OnOK()
{
    UpdateData(TRUE);

    if (!PSS_File::Exist(m_FileName))
    {
        // error message
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_WKS_FILENAME_DEXIST, MB_YESNO) == IDYES)
        {
            CString title;
            VERIFY(title.LoadString(IDS_WORKSPACE_FILESELECT_T));

            // set the "*.*" files filter
            CString filters;
            VERIFY(filters.LoadString(AFX_IDS_ALLFILTER));
            filters += (char)'\0';
            filters += "*.*";
            filters += (char)'\0';

            PSS_FileDialog fileDialog(title, filters, 1);

            if (fileDialog.DoModal() == IDOK)
            {
                m_FileName = fileDialog.GetFileName();
                UpdateData(FALSE);
            }
        }
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
