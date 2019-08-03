/****************************************************************************
 * ==> PSS_UrlInputDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an url input dialog box                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UrlInputDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UrlInputDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_UrlInputDialog)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UrlInputDialog
//---------------------------------------------------------------------------
PSS_UrlInputDialog::PSS_UrlInputDialog(const CString& url, CWnd* pParent) :
    CDialog(PSS_UrlInputDialog::IDD, pParent),
    m_URL(url)
{}
//---------------------------------------------------------------------------
void PSS_UrlInputDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_UrlInputDialog)
    DDX_Text(pDX, IDC_URL, m_URL);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
