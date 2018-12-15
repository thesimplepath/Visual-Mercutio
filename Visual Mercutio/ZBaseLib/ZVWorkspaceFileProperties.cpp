// ZVWorkspaceFileProperties.cpp : implementation file
//

#include "stdafx.h"
#include "ZVWorkspaceFileProperties.h"

#include "File.h"

#include "zBaseLibRes.h"
#include "MsgBox.h"
#include "FileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceFileProperties dialog


ZVWorkspaceFileProperties::ZVWorkspaceFileProperties(ZBWorkspaceGroupEntity* pRootGroup /*= NULL*/, 
                                                     const CString Title /*= ""*/, 
                                                     const CString CompleteFilename /*= ""*/,
                                                     CWnd* pParent /*=NULL*/)
    : CDialog(ZVWorkspaceFileProperties::IDD, pParent),
      m_Filename(CompleteFilename)
{
    //{{AFX_DATA_INIT(ZVWorkspaceFileProperties)
    m_FileTitle = Title;
    m_Filename = CompleteFilename;
    //}}AFX_DATA_INIT
}


void ZVWorkspaceFileProperties::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVWorkspaceFileProperties)
    DDX_Text(pDX, IDC_FILE_TITLE, m_FileTitle);
    DDX_Text(pDX, IDC_FILE_COMPLETEPATH, m_Filename);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVWorkspaceFileProperties, CDialog)
    //{{AFX_MSG_MAP(ZVWorkspaceFileProperties)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceFileProperties message handlers

void ZVWorkspaceFileProperties::OnOK() 
{
    UpdateData( TRUE );
    
    if (!ZFile::Exist( m_Filename ))
    {
        // Error message
        MsgBox        mbox;
        if (mbox.DisplayMsgBox( IDS_WKS_FILENAME_DEXIST, MB_YESNO ) == IDYES)
        {
            CString title;
            VERIFY(title.LoadString(IDS_WORKSPACE_FILESELECT_T));

            // set the "*.*" files filter
            CString strFilter;
            VERIFY(strFilter.LoadString(AFX_IDS_ALLFILTER));
            strFilter += (char)'\0';        // next string please
            strFilter += "*.*";
            strFilter += (char)'\0';        // last string

            ZIFileDialog    FileDialog( title, strFilter, 1 );
            if (FileDialog.DoModal() == IDOK)
            {
                m_Filename = FileDialog.GetFilename();
                UpdateData( FALSE );
            }
        }
    }

    CDialog::OnOK();
}

BOOL ZVWorkspaceFileProperties::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

