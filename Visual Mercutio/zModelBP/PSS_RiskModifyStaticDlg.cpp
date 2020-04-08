/****************************************************************************
 * ==> PSS_RiskModifyStaticDlg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify risk static dialog box                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskModifyStaticDlg.h"

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
BEGIN_MESSAGE_MAP(PSS_RiskModifyStaticDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_RiskModifyStaticDlg)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_EN_CHANGE(IDC_STATIC_MODIFY_ELEMENT, OnEnChangeStaticModifyElement)
    ON_LBN_SELCHANGE(IDC_STATIC_ELEMENTS_LIST, OnLbnSelchangeStaticElementsList)
    ON_BN_CLICKED(IDC_STATIC_NEW_FILE, OnBnClickedStaticNewFile)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RiskModifyStaticDlg
//---------------------------------------------------------------------------
PSS_RiskModifyStaticDlg::PSS_RiskModifyStaticDlg() :
    CDialog(PSS_RiskModifyStaticDlg::IDD, NULL),
    m_ElementCount(0)
{}
//---------------------------------------------------------------------------
PSS_RiskModifyStaticDlg::PSS_RiskModifyStaticDlg(const CString& fileName,
                                                 const CString& extension,
                                                 int            elementCount,
                                                 CWnd*          pParent) :
    CDialog(PSS_RiskModifyStaticDlg::IDD, pParent),
    m_FileName(fileName),
    m_Extension(extension),
    m_ElementCount(elementCount)
{}
//---------------------------------------------------------------------------
PSS_RiskModifyStaticDlg::~PSS_RiskModifyStaticDlg()
{}
//---------------------------------------------------------------------------
CString PSS_RiskModifyStaticDlg::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_RiskModifyStaticDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RiskModifyStaticDlg)
    DDX_Control(pDX, IDC_STATIC_ELEMENTS_LIST,  m_ElementsListCtrl);
    DDX_Control(pDX, IDC_STATIC_MODIFY_ELEMENT, m_ElementCtrl);
    DDX_Text   (pDX, IDC_STATIC_MODIFY_ELEMENT, m_Element);
    DDX_Control(pDX, IDOK,                      m_OK);
    DDX_Control(pDX, IDC_ELEMENT_NUMBER,        m_ElementNbrCtrl);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RiskModifyStaticDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    PSS_TextFile textFile;

    if (textFile.OpenRead(m_FileName))
    {
        CString text;
        BOOL    endReached = FALSE;
        int     count = 0;

        while (endReached != TRUE)
        {
            textFile >> text;

            if (!text.IsEmpty())
            {
                m_ElementsListCtrl.AddString(text);
                ++count;
            }
            else
                endReached = TRUE;
        }

        textFile.CloseFile();

        if (count != m_ElementCount)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CORRUPTED_RISK_FILE, MB_OK);

            m_ElementsListCtrl.EnableWindow(FALSE);
            m_ElementCtrl.EnableWindow(FALSE);
            m_OK.EnableWindow(FALSE);
        }
    }
    else
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOT_OPEN_RISK_FILE, MB_OK);

        m_ElementsListCtrl.EnableWindow(FALSE);
        m_ElementCtrl.EnableWindow(FALSE);
        m_OK.EnableWindow(FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RiskModifyStaticDlg::OnEnChangeStaticModifyElement()
{
    const int index = m_ElementsListCtrl.GetCurSel();

    if (index >= 0 && index < m_ElementCount)
    {
        CString formater;
        formater.LoadString(IDS_RISK_STRING_FORMATER);
        formater += _T(" ");

        CString str;
        str.Format(formater, (m_ElementsListCtrl.GetCurSel()));

        m_ElementCtrl.GetWindowText(m_Element);

        m_ElementsListCtrl.DeleteString(index);
        m_ElementsListCtrl.InsertString(index, str + m_Element);
        m_ElementsListCtrl.SetCurSel(index);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskModifyStaticDlg::OnLbnSelchangeStaticElementsList()
{
    CString str;
    str.Format(IDS_RISK_STRING_FORMATER, (m_ElementsListCtrl.GetCurSel()));

    m_ElementNbrCtrl.SetWindowText(str);
    m_ElementsListCtrl.GetText(m_ElementsListCtrl.GetCurSel(), m_Element);

    m_Element.Delete(0, 4);
    m_ElementCtrl.SetWindowText(m_Element);
}
//---------------------------------------------------------------------------
void PSS_RiskModifyStaticDlg::OnBnClickedStaticNewFile()
{
    PSS_RiskNewFileDlg newFileDlg(m_Extension);

    if (newFileDlg.DoModal() == IDOK)
    {
        m_FileName = newFileDlg.GetDirectory() + _T("\\") + newFileDlg.GetFileName() + m_Extension;

        while (m_ElementsListCtrl.GetCount() > 0)
            m_ElementsListCtrl.DeleteString(0);
    }

    for (int i = 0; i < m_ElementCount; ++i)
    {
        CString newEntry = _T("");
        newEntry.Format(IDS_RISK_STRING_ENTRY, i, i);

        m_ElementsListCtrl.AddString(newEntry);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskModifyStaticDlg::OnBnClickedOk()
{
    PSS_File file;

    if (file.Exist(m_FileName))
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
