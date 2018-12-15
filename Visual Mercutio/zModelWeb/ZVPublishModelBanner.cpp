// ZVPublishModelBanner.cpp : implementation file

#include "stdafx.h"
#include "ZVPublishModelBanner.h"

#include "zBaseLib\MsgBox.h"
#include "zBaseLib\File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelBanner dialog

BEGIN_MESSAGE_MAP( ZVPublishModelBanner, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVPublishModelBanner)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishModelBanner::ZVPublishModelBanner( CString    HyperLink        /*= _T( "" )*/,
                                            CString    ImageFilename    /*= _T( "" )*/,
                                            CWnd*    pParent            /*= NULL*/ )
    : ZIWizardDialog( ZVPublishModelBanner::IDD,    // Dialog template
                      IDB_WZBMP1,                    // Bitmap to display
                      0,                            // Icon do display
                      0,                            // Window Title
                      IDS_PUBLISHMODELBANNER_S,        // Wizard title
                      IDS_PUBLISHMODELBANNER_T ),    // Wizard text
    m_HyperLink        ( HyperLink ),
    m_ImageFilename    ( ImageFilename )
{
    //{{AFX_DATA_INIT(ZVPublishModelBanner)
    //}}AFX_DATA_INIT

    m_Image.SetSearchType( ZSEARCHEDIT_FILE );
}

void ZVPublishModelBanner::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVPublishModelBanner)
    DDX_Control(pDX, IDC_BANNERIMAGE, m_Image);
    DDX_Text(pDX, IDC_BANNERHYPERLINK, m_HyperLink);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelBanner message handlers

BOOL ZVPublishModelBanner::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    // Initialize the logo filename
    m_Image.SetWindowText( m_ImageFilename );

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVPublishModelBanner::OnOK()
{
    UpdateData();

    // Check the image ref
    m_Image.GetWindowText( m_ImageFilename );

    if ( !m_ImageFilename.IsEmpty() && !ZFile::Exist( m_ImageFilename ) )
    {
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_IMAGEFILENAME_NOTFOUND, MB_OK );
        return;
    }

    ZIWizardDialog::OnOK();
}
