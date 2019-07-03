// tmplsava.cpp : implementation file
//

#include "stdafx.h"
#include "tmplsava.h"
#include "zBaseLib\MsgBox.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZITemplateCopyDlg dialog


ZITemplateCopyDlg::ZITemplateCopyDlg(ZDTemplateManager* pTemplateManager, CString FileExtension, ZDFolderStamp* pFolderStamp, BOOL AllowReplace /*= FALSE*/, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZITemplateCopyDlg::IDD, TRUE, pParent), 
      m_pTemplateManager(pTemplateManager), 
      m_FileExtension(FileExtension),
      m_pFolderStamp(pFolderStamp),
      m_AllowReplace(AllowReplace),
      m_FileExist(false)
{
    //{{AFX_DATA_INIT(ZITemplateCopyDlg)
    m_sDescription = "";
    m_sFilename = "";
    m_sTitle = "";
    //}}AFX_DATA_INIT
    if (m_pFolderStamp)
    {
        m_sDescription = m_pFolderStamp->GetExplanation();
#ifdef _WIN32
        m_sFilename = m_pFolderStamp->GetTitle();
#endif
#ifndef _WIN32
        // In 16bit only 8 character for the filename
        m_sFilename = m_pFolderStamp->GetTitle().Left(8);
#endif
        m_sTitle = m_pFolderStamp->GetTitle();
    }
}

void ZITemplateCopyDlg::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZITemplateCopyDlg)
    DDX_Control(pDX, IDC_TEMPLATEDIR, m_TemplateDirList);
    DDX_Text(pDX, IDC_DESCRIPTION, m_sDescription);
    DDX_Text(pDX, IDC_FILENAME, m_sFilename);
    DDX_Text(pDX, IDC_TITLE, m_sTitle);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZITemplateCopyDlg, CDialog)
    //{{AFX_MSG_MAP(ZITemplateCopyDlg)
    ON_EN_CHANGE(IDC_TITLE, OnChangeTitle)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZITemplateCopyDlg message handlers

void ZITemplateCopyDlg::OnOK()
{
    UpdateData( TRUE );
    
    // Retrieve the TemplateDirectory
#ifndef _WIN32    
    int iCurrentSelection = m_TemplateDirList.GetCurSel();
    if (iCurrentSelection == LB_ERR)
        return;
    // Insert all pages from the Template Manager
    // Run throughout all template directory    
      ZDTemplateDir* pTemplateDir = m_pTemplateManager->GetTemplateDirAt( iCurrentSelection );
#endif

#ifdef _WIN32    
    // Insert all pages from the Template Manager
    // Run throughout all template directory    
      ZDTemplateDir* pTemplateDir = m_TemplateDirList.GetSelectedFolderItem();
#endif

      if (!pTemplateDir)
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_CATEGORYMISSING, MB_OK );
          return;
    }

    if (m_sFilename.IsEmpty())
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_FILENAMEMISSING, MB_OK );
        return;
    }
    if (m_sTitle.IsEmpty())
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_TITLEMISSING, MB_OK );
        return;
    }
#ifndef _WIN32    
    if (m_sFilename.GetLength() > 8 || m_sFilename.Find( '.' ) != -1)
#endif
#ifdef _WIN32    
    if (m_sFilename.Find( '.' ) != -1)
#endif
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_TEMPLATEFILENAMEERROR, MB_OK );
        return;
    }                      
    // Build the complete filename to know if already exist
    CString    sFile = pTemplateDir->GetDirectory() + "\\" + m_sFilename + "." + m_FileExtension;
    CFileStatus status;
    if (CFile::GetStatus( sFile, status ))
    {
        // If does not allow replacement of file
        // error message and return
        MsgBox        mbox;
        if (!m_AllowReplace)
        {
            mbox.DisplayMsgBox( IDS_FORMALREADYEXIST, MB_OK );
            return;
        }
        if (mbox.DisplayMsgBox( IDS_FORMALREADYEXIST_CONTREPLACE, MB_YESNO ) == IDNO)
            return;
        // Set the flag for file chosen exists
        m_FileExist = true;
    }
    // Add the extension
    m_sFilename = sFile;
    UpdateData( FALSE );
    CDialog::OnOK();
}

BOOL ZITemplateCopyDlg::OnInitDialog()
{
    ZIDialog::OnInitDialog();

#ifndef _WIN32    
    // Initialize the template list
    m_TemplateDirList.ResetContent();
    
    // Insert all pages from the Template Manager
    // Run throughout all template directory    
      ZDTemplateDir* pTemplateDir;
    for (size_t i = 0; i < (size_t)m_pTemplateManager->GetSize(); ++i)
      {
          pTemplateDir = m_pTemplateManager->GetTemplateDirAt( i );
          if (pTemplateDir)
              m_TemplateDirList.AddString( pTemplateDir->GetTitle() );
      }
    m_TemplateDirList.SetCurSel( 0 );
#endif

#ifdef _WIN32    
    m_TemplateDirList.Initialize( m_pTemplateManager, TRUE );
#endif

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZITemplateCopyDlg::OnChangeTitle() 
{
    // If this is a RICHEDIT control, the control will not
    // send this notification unless you override the ZIDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // Trap input and change the filename
    UpdateData( TRUE );
#ifndef _WIN32    
    // In 16bit only copy 8 character of the title
    m_sFilename = m_sTitle.Left(8);
#endif
#ifdef _WIN32    
    m_sFilename = m_sTitle;
#endif
    UpdateData( FALSE );
}
