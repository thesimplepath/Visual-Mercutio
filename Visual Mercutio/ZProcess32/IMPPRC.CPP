// impprc.cpp : implementation file
//

#include "stdafx.h"
#include "ImpPrc.h"
// FileDlg
#include "zBaseLib\PSS_FileDialog.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIImportProcess dialog


ZIImportProcess::ZIImportProcess(CString File, BOOL Import, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZIImportProcess::IDD, TRUE, pParent), 
      m_Import(Import), m_InitialFile(File)
{
    //{{AFX_DATA_INIT(ZIImportProcess)
    m_File = m_InitialFile;
    //}}AFX_DATA_INIT
}

void ZIImportProcess::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIImportProcess)
    DDX_Text(pDX, IDC_FILETOIMPORT, m_File);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIImportProcess, CDialog)
    //{{AFX_MSG_MAP(ZIImportProcess)
    ON_BN_CLICKED(IDC_SELECT, OnSelect)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIImportProcess message handlers

void ZIImportProcess::OnSelect()
{
    CString title;
    if (m_Import)
        title.LoadString(IDS_IMPORTFILE_CHOOSETITLE);
    else
        title.LoadString(IDS_EXPORTPROCESSFILE_CHOOSETITLE);
    // set the "*.txt" files filter
    CString strFilter;
    VERIFY(strFilter.LoadString(AFX_IDS_ALLFILTER));
    strFilter += (char)'\0';        // next string please
    strFilter += "*.*";
    strFilter += (char)'\0';        // last string

    PSS_FileDialog fileDialog( title, strFilter, 1 );
    if (fileDialog.DoModal() == IDOK)
    {
        m_File = fileDialog.GetFileName();
        UpdateData( FALSE );
    }
    
}

void ZIImportProcess::OnOK()
{
    UpdateData();
    if (m_File.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.ShowMsgBox( IDS_FILENAMEMISSING, MB_OK );
        return;
    }
    ZIDialog::OnOK();
}

BOOL ZIImportProcess::OnInitDialog() 
{
    ZIDialog::OnInitDialog();
    
    if (m_Import == FALSE)
    {
        CString    Title;
        Title.LoadString( IDS_EXPORTPROCESS_TITLE );
        SetWindowText( Title );

        if (GetDlgItem(IDOK))
        {
            Title.LoadString( IDS_EXPORTPROCESS_BUTTON );
            GetDlgItem(IDOK)->SetWindowText( Title );
        }
    }



    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
