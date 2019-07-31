/****************************************************************************
 * ==> PSS_FileVersionDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a file version dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FileVersionDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileVersionDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_FileVersionDialog)
    ON_NOTIFY(UDN_DELTAPOS, IDC_FILEVERSION_SPIN, OnDeltaposFileversionSpin)
    ON_EN_CHANGE(IDC_FILEVERSION, OnChangeFileVersion)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileVersionDialog
//---------------------------------------------------------------------------
PSS_FileVersionDialog::PSS_FileVersionDialog(long fileVersion, CWnd* pParent) :
    ZIDialog(PSS_FileVersionDialog::IDD, TRUE, pParent),
    m_FileVersion(fileVersion)
{}
//---------------------------------------------------------------------------
void PSS_FileVersionDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_FileVersionDialog)
    DDX_Control(pDX, IDC_FILEVERSION_SPIN, m_FileVersionSpin);
    DDX_Text   (pDX, IDC_FILEVERSION,      m_FileVersion);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_FileVersionDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();
    
    m_FileVersionSpin.SetRange(0, UD_MAXVAL);
    m_FileVersionSpin.SetPos(m_FileVersion);

    if (GetDlgItem(IDC_FILEVERSION))
        m_FileVersionSpin.SetBuddy(GetDlgItem(IDC_FILEVERSION));

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FileVersionDialog::OnDeltaposFileversionSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

    m_FileVersion = m_FileVersionSpin.GetPos() & 0x0000FFFF;
    UpdateData(FALSE);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FileVersionDialog::OnChangeFileVersion()
{
    // todo -cFeature -oJean: if this is a RICHEDIT control, it will not send this notification unless overridding
    //                        the ZIDialog::OnInitDialog() function and calling CRichEditCtrl().SetEventMask()
    //                        with the ENM_CHANGE flag set in the mask
    UpdateData();
    m_FileVersionSpin.SetPos(m_FileVersion);
}
//---------------------------------------------------------------------------
