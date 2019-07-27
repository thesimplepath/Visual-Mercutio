/****************************************************************************
 * ==> PSS_SysVarDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system variables converter dialog box           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SysVarDialog.h"

// processsoft
#include "PSS_SysVarConverter.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const char* g_Symbol[] =
{
    g_Today,
    g_FileName,
    g_ExchFileName,
    g_ProcExchFileName,
    g_Author,
    g_Modifier,
    g_CreationDate,
    g_ModificationDate,
    g_PublishDate,
    g_FileVer,
    NULL
};

const UINT g_SymbolID[] =
{
    IDS_TODAY_SYSVAR,
    IDS_FILENAME_SYSVAR,
    IDS_EXCHFILENAME_SYSVAR,
    IDS_PROCEXCHFILENAME_SYSVAR,
    IDS_AUTHOR_SYSVAR,
    IDS_MODIFIER_SYSVAR,
    IDS_CREATIONDATE_SYSVAR,
    IDS_MODIFICATIONDATE_SYSVAR,
    IDS_PUBLISHDATE_SYSVAR,
    IDS_FILEVER_SYSVAR,
    0
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SysVarDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_SysVarDialog)
    ON_LBN_SELCHANGE(IDC_SYSTEMVARLIST, OnSelchangeSystemVarlist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SysVarDialog
//---------------------------------------------------------------------------
PSS_SysVarDialog::PSS_SysVarDialog(CWnd* pParent) :
    ZIDialog(PSS_SysVarDialog::IDD, TRUE, pParent)
{}
//---------------------------------------------------------------------------
void PSS_SysVarDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SysVarDialog)
    DDX_Control(pDX, IDC_SYSTEMVARLIST, m_SysVarList);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SysVarDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();
    
    std::size_t index = 0;

    while (g_SymbolID[index])
    {
        CString text;
        text.LoadString(g_SymbolID[index]);
        m_SysVarList.AddString(text);
        ++index;
    }

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(FALSE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SysVarDialog::OnSelchangeSystemVarlist()
{
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(m_SysVarList.GetCurSel() != LB_ERR);
}
//---------------------------------------------------------------------------
void PSS_SysVarDialog::OnOK()
{
    const int curSel = m_SysVarList.GetCurSel();

    if (curSel != LB_ERR)
        m_Keyword = g_Symbol[curSel];

    ZIDialog::OnOK();
}
//---------------------------------------------------------------------------
