/****************************************************************************
 * ==> PSS_ObjectNotesDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an object notes dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ObjectNotesDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ObjectNotesDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_ObjectNotesDialog)
    ON_BN_CLICKED(IDC_DELETENOTES, OnDeleteNotes)
    ON_EN_CHANGE(IDC_NOTESEDIT, OnChangeNotesEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ObjectNotesDialog
//---------------------------------------------------------------------------
PSS_ObjectNotesDialog::PSS_ObjectNotesDialog(const CString& comment,
                                             const CString& userName,
                                             CWnd*          pParent) :
    ZIDialog(PSS_ObjectNotesDialog::IDD, TRUE, pParent),
    m_UserName(userName),
    m_Comment(comment)
{
    m_SaveText.LoadString(IDS_SAVETEXTBUTTON);
    m_TextChanged = FALSE;
}
//---------------------------------------------------------------------------
void PSS_ObjectNotesDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ObjectNotesDialog)
    DDX_Text(pDX, IDC_NOTESEDIT, m_Comment);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ObjectNotesDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    if (!m_UserName.IsEmpty())
    {
        // if a username is defined, change the window title
        CString title;
        GetWindowText(title);
        title += " - " + m_UserName;
        SetWindowText(title);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ObjectNotesDialog::OnChangeNotesEdit()
{
    // todo -cFeature -oJean: if this is a RICHEDIT control, it will not send this notification unless overridding
    //                        the ZIDialog::OnInitDialog() function and calling CRichEditCtrl().SetEventMask()
    //                        with the ENM_CHANGE flag set in the mask
    if (!m_TextChanged && GetDlgItem(IDOK))
    {
        m_TextChanged = TRUE;
        GetDlgItem(IDOK)->SetWindowText(m_SaveText);
    }
}
//---------------------------------------------------------------------------
void PSS_ObjectNotesDialog::OnDeleteNotes()
{
    EndDialog(IDC_DELETENOTES);
}
//---------------------------------------------------------------------------
void PSS_ObjectNotesDialog::OnOK()
{
    UpdateData();

    // if empty, asks to delete the notes
    if (m_Comment.IsEmpty())
    {
        EndDialog(IDC_DELETENOTES);
        return;
    }
    
    ZIDialog::OnOK();
}
//---------------------------------------------------------------------------
