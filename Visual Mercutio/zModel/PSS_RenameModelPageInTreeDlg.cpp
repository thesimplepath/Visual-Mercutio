/****************************************************************************
 * ==> PSS_RenameModelPageInTreeDlg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a rename model page in tree dialog box            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RenameModelPageInTreeDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RenameModelPageInTreeDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_RenameModelPageInTreeDlg)
    //}}AFX_MSG_MAP
    ON_EN_CHANGE(IDC_PAGENAME, OnChangePageName)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RenameModelPageInTreeDlg
//---------------------------------------------------------------------------
PSS_RenameModelPageInTreeDlg::PSS_RenameModelPageInTreeDlg(const CString& proposedName,
                                                           CStringArray*  pPageNameArray,
                                                           CWnd*          pParent) :
    PSS_Dialog(PSS_RenameModelPageInTreeDlg::IDD, TRUE, pParent),
    m_pPageNameArray(pPageNameArray),
    m_PageName(proposedName)
{}
//---------------------------------------------------------------------------
PSS_RenameModelPageInTreeDlg::~PSS_RenameModelPageInTreeDlg()
{}
//---------------------------------------------------------------------------
void PSS_RenameModelPageInTreeDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RenameModelPageInTreeDlg)
    //}}AFX_DATA_MAP
}
BOOL PSS_RenameModelPageInTreeDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (GetDlgItem(IDC_PAGENAME))
        GetDlgItem(IDC_PAGENAME)->SetWindowText(m_PageName);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RenameModelPageInTreeDlg::OnChangePageName()
{
    if (GetDlgItem(IDC_PAGENAME))
        GetDlgItem(IDC_PAGENAME)->GetWindowText(m_PageName);
}
//---------------------------------------------------------------------------
void PSS_RenameModelPageInTreeDlg::OnOK()
{
    // the page name cannot be empty
    if (m_PageName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
        return;
    }

    // check if the page name is unique in the model and still not attributed to another page
    if (m_pPageNameArray)
    {
        const int pageNameCount = m_pPageNameArray->GetSize();

        for (int i = 0; i < pageNameCount; ++i)
            if (m_PageName == m_pPageNameArray->GetAt(i))
            {
                // show error message
                PSS_MsgBox mBox;
                mBox.Show(IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK);
                return;
            }
    }

    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
