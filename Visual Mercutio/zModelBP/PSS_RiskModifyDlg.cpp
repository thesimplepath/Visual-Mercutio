/****************************************************************************
 * ==> PSS_RiskModifyDlg ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify risk dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskModifyDlg.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_TextFile.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_RiskNewFileDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RiskModifyDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_RiskModifyDlg)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_ADD_ELEMENT, OnBnClickedAddElement)
    ON_BN_CLICKED(IDC_DEL_ELEMENT, OnBnClickedDelElement)
    ON_EN_CHANGE(IDC_NEW_ELEMENT, OnEnChangeNewElement)
    ON_LBN_SELCHANGE(IDC_ELEMENTS_LIST, OnLbnSelchangeElementsList)
    ON_BN_CLICKED(IDC_NEW_FILE, OnBnClickedNewFile)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RiskModifyDlg
//---------------------------------------------------------------------------
PSS_RiskModifyDlg::PSS_RiskModifyDlg() :
    CDialog(PSS_RiskModifyDlg::IDD, NULL)
{}
//---------------------------------------------------------------------------
PSS_RiskModifyDlg::PSS_RiskModifyDlg(const CString& fileName,
                                     const CString& extension,
                                     CWnd*          pParent) :
    CDialog(PSS_RiskModifyDlg::IDD, pParent),
    m_FileName(fileName),
    m_Extension(extension)
{}
//---------------------------------------------------------------------------
PSS_RiskModifyDlg::~PSS_RiskModifyDlg()
{}
//---------------------------------------------------------------------------
CString PSS_RiskModifyDlg::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RiskModifyDlg)
    DDX_Control(pDX, IDC_ELEMENTS_LIST, m_ElementsListCtrl);
    DDX_Control(pDX, IDC_NEW_ELEMENT,   m_ElementCtrl);
    DDX_Text   (pDX, IDC_NEW_ELEMENT,   m_Element);
    DDX_Control(pDX, IDC_ADD_ELEMENT,   m_Add);
    DDX_Control(pDX, IDC_DEL_ELEMENT,   m_Del);
    DDX_Control(pDX, IDOK,              m_OK);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RiskModifyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    PSS_TextFile textFile;

    if (textFile.OpenRead(m_FileName))
    {
        BOOL    endReached = FALSE;
        CString text;

        while (!endReached)
        {
            textFile >> text;

            if (!text.IsEmpty())
                m_ElementsListCtrl.AddString(text);
            else
                endReached = TRUE;
        }

        textFile.CloseFile();
    }
    else
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOT_OPEN_RISK_FILE, MB_OK);

        m_ElementsListCtrl.EnableWindow(FALSE);
        m_ElementCtrl.EnableWindow(FALSE);
        m_Add.EnableWindow(FALSE);
        m_Del.EnableWindow(FALSE);
        m_OK.EnableWindow(FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::OnEnChangeNewElement()
{
    m_ElementCtrl.GetWindowText(m_Element);

    if (!m_Element.IsEmpty())
        m_Add.EnableWindow(TRUE);
    else
        m_Add.EnableWindow(FALSE);
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::OnLbnSelchangeElementsList()
{
    m_Del.EnableWindow(TRUE);
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::OnBnClickedAddElement()
{
    if (!m_Element.IsEmpty())
        m_ElementsListCtrl.AddString(m_Element);

    m_Element.Empty();
    m_ElementCtrl.SetWindowText(m_Element);
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::OnBnClickedDelElement()
{
    if ((m_ElementsListCtrl.GetCurSel()) >= 0 && (m_ElementsListCtrl.GetCurSel() < m_ElementsListCtrl.GetCount()))
    {
        m_ElementsListCtrl.DeleteString(m_ElementsListCtrl.GetCurSel());
        m_Del.EnableWindow(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::OnBnClickedNewFile()
{
    PSS_RiskNewFileDlg newFileDlg(m_Extension);

    if (newFileDlg.DoModal() == IDOK)
    {
        m_FileName = newFileDlg.GetDirectory() + _T("\\") + newFileDlg.GetFileName() + m_Extension;

        while (m_ElementsListCtrl.GetCount() > 0)
            m_ElementsListCtrl.DeleteString(0);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskModifyDlg::OnBnClickedOk()
{
    PSS_File m_File;

    if (m_File.Exist(m_FileName))
        CFile::Remove(m_FileName);

    PSS_TextFile newFile;
    newFile.OpenWrite(m_FileName);

    const int elementCount = m_ElementsListCtrl.GetCount();

    for (int i = 0; i < elementCount; ++i)
    {
        CString str;
        m_ElementsListCtrl.GetText(i, str);
        newFile << str + _T("\r\n");
    }

    newFile.CloseFile();

    OnOK();
}
//---------------------------------------------------------------------------
