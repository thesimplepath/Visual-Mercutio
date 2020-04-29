/****************************************************************************
 * ==> PSS_ManageValueIntelliEditDlg ---------------------------------------*
 ****************************************************************************
 * Description : Provides a manage intelligent edit value dialog box        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ManageValueIntelliEditDlg.h"

// processsoft
#include "PSS_InputValue.h"

// resources
#include "zBaseLib\zBaseLibRes.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ManageValueIntelliEditDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_ManageValueIntelliEditDlg)
    ON_BN_CLICKED(IDC_ADDVALUE, OnAddvalue)
    ON_BN_CLICKED(IDC_DELVALUE, OnDelvalue)
    ON_LBN_SELCHANGE(IDC_VALUES, OnSelchangeValues)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ManageValueIntelliEditDlg
//---------------------------------------------------------------------------
PSS_ManageValueIntelliEditDlg::PSS_ManageValueIntelliEditDlg(CStringArray* pArrayOfValues, CWnd* pParent) :
    CDialog(IDD_MGVALUE_INTELLI, pParent),
    m_pArrayOfValues(pArrayOfValues)
{}
//---------------------------------------------------------------------------
void PSS_ManageValueIntelliEditDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ManageValueIntelliEditDlg)
    DDX_Control(pDX, IDC_VALUES, m_Values);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ManageValueIntelliEditDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // fill the list box
    if (!m_pArrayOfValues)
        return TRUE;

    m_Values.ResetContent();

    std::size_t count = m_pArrayOfValues->GetSize();

    for (std::size_t i = 0; i < count; ++i)
        m_Values.AddString(m_pArrayOfValues->GetAt(i));

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ManageValueIntelliEditDlg::OnAddvalue()
{
    PSS_InputValue inputValue(IDS_INSERTVALUE_INTELLI);

    if (inputValue.DoModal() == IDOK)
        m_Values.AddString(inputValue.GetValue());

    OnSelchangeValues();
}
//---------------------------------------------------------------------------
void PSS_ManageValueIntelliEditDlg::OnDelvalue()
{
    const int curSel = m_Values.GetCurSel();
    PSS_Assert(curSel != LB_ERR);
    m_Values.DeleteString(curSel);
}
//---------------------------------------------------------------------------
void PSS_ManageValueIntelliEditDlg::OnSelchangeValues()
{
    if (GetDlgItem(IDC_DELVALUE))
        GetDlgItem(IDC_DELVALUE)->EnableWindow(m_Values.GetCurSel() != LB_ERR);
}
//---------------------------------------------------------------------------
void PSS_ManageValueIntelliEditDlg::OnOK()
{
    if (m_pArrayOfValues)
    {
        // remove all elements
        m_pArrayOfValues->RemoveAll();

        CString   str;
        const int count = m_Values.GetCount();

        // copy listbox elements to array
        for (int i = 0; i < count; ++i)
        {
            m_Values.GetText(i, str);
            m_pArrayOfValues->Add(str);
        }
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
