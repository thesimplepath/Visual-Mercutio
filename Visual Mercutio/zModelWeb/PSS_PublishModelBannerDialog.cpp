/****************************************************************************
 * ==> PSS_PublishModelBannerDialog ----------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model banners to publish *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishModelBannerDialog.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_File.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelBannerDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelBannerDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelBannerDialog
//---------------------------------------------------------------------------
PSS_PublishModelBannerDialog::PSS_PublishModelBannerDialog(const CString& hyperLink,
                                                           const CString& imageFileName,
                                                           CWnd*          pParent) :
    PSS_WizardDialog(PSS_PublishModelBannerDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_PUBLISHMODELBANNER_S,
                     IDS_PUBLISHMODELBANNER_T),
    m_HyperLink(hyperLink),
    m_ImageFileName(imageFileName)
{
    m_Image.SetSearchType(PSS_SearchEditButton::IEType::IE_T_File);
}
//---------------------------------------------------------------------------
void PSS_PublishModelBannerDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelBannerDialog)
    DDX_Control(pDX, IDC_BANNERIMAGE,     m_Image);
    DDX_Text   (pDX, IDC_BANNERHYPERLINK, m_HyperLink);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelBannerDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // initialize the logo file name
    m_Image.SetWindowText(m_ImageFileName);

    // return TRUE unless the focus was set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelBannerDialog::OnOK()
{
    UpdateData();

    // check the image reference
    m_Image.GetWindowText(m_ImageFileName);

    if (!m_ImageFileName.IsEmpty() && !PSS_File::Exist(m_ImageFileName))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_IMAGEFILENAME_NOTFOUND, MB_OK);
        return;
    }

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
