/****************************************************************************
 * ==> PSS_PublishModelBannerDialog ----------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model banners to publish *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishModelBannerDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"
#include "zBaseLib\File.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelBannerDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelBannerDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelBannerDialog
//---------------------------------------------------------------------------
PSS_PublishModelBannerDialog::PSS_PublishModelBannerDialog(const CString& hyperLink,
                                                           const CString& imageFileName,
                                                           CWnd*          pParent) :
    ZIWizardDialog(PSS_PublishModelBannerDialog::IDD,
                   IDB_WZBMP1,
                   0,
                   0,
                   IDS_PUBLISHMODELBANNER_S,
                   IDS_PUBLISHMODELBANNER_T),
    m_HyperLink(hyperLink),
    m_ImageFilename(imageFileName)
{
    m_Image.SetSearchType(PSS_SearchEditButton::IE_T_File);
}
//---------------------------------------------------------------------------
void PSS_PublishModelBannerDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelBannerDialog)
    DDX_Control(pDX, IDC_BANNERIMAGE, m_Image);
    DDX_Text(pDX, IDC_BANNERHYPERLINK, m_HyperLink);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelBannerDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    // initialize the logo filename
    m_Image.SetWindowText(m_ImageFilename);

    // return TRUE unless the focus was set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelBannerDialog::OnOK()
{
    UpdateData();

    // check the image reference
    m_Image.GetWindowText(m_ImageFilename);

    if (!m_ImageFilename.IsEmpty() && !ZFile::Exist(m_ImageFilename))
    {
        MsgBox mbox;
        mbox.DisplayMsgBox(IDS_IMAGEFILENAME_NOTFOUND, MB_OK);
        return;
    }

    ZIWizardDialog::OnOK();
}
//---------------------------------------------------------------------------
