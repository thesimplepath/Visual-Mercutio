// ZIObjectNotesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZIObjectNotesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIObjectNotesDialog dialog


ZIObjectNotesDialog::ZIObjectNotesDialog(const CString Comment /*= ""*/, 
                                         const CString Username /*= ""*/, 
                                         CWnd* pParent /*=NULL*/)
    : ZIDialog(ZIObjectNotesDialog::IDD, TRUE, pParent),
      m_Comment(Comment),
      m_Username(Username)
{
    //{{AFX_DATA_INIT(ZIObjectNotesDialog)
    //}}AFX_DATA_INIT

    m_SaveText.LoadString( IDS_SAVETEXTBUTTON );
    m_TextChanged = FALSE;
}


void ZIObjectNotesDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIObjectNotesDialog)
    DDX_Text(pDX, IDC_NOTESEDIT, m_Comment);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIObjectNotesDialog, ZIDialog)
    //{{AFX_MSG_MAP(ZIObjectNotesDialog)
    ON_BN_CLICKED(IDC_DELETENOTES, OnDeleteNotes)
    ON_EN_CHANGE(IDC_NOTESEDIT, OnChangeNotesEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIObjectNotesDialog message handlers

void ZIObjectNotesDialog::OnDeleteNotes() 
{
    EndDialog( IDC_DELETENOTES );    
}

void ZIObjectNotesDialog::OnChangeNotesEdit() 
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    if (!m_TextChanged && GetDlgItem( IDOK ))
    {
        m_TextChanged = TRUE;
        GetDlgItem( IDOK )->SetWindowText( m_SaveText );
    }
}

void ZIObjectNotesDialog::OnOK() 
{
    UpdateData();

    if (m_Comment.IsEmpty())
    {
        // If empty, asks to delete the notes
        EndDialog( IDC_DELETENOTES );    
        return;
    }
    
    ZIDialog::OnOK();
}

BOOL ZIObjectNotesDialog::OnInitDialog() 
{
    ZIDialog::OnInitDialog();
    
    if (!m_Username.IsEmpty())
    {
        // If a username is defined, change the window title
        CString    Title;
        GetWindowText( Title );
        Title += " - " + m_Username;
        SetWindowText( Title );
    }
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
