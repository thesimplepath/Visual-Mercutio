/****************************************************************************
 * ==> PSS_DynamicAttributesDuplicationDlg ---------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic attributes duplication dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DynamicAttributesDuplicationDlg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DynamicAttributesDuplicationDlg, PSS_WizardDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DynamicAttributesDuplicationDlg, PSS_WizardDialog)
    ON_LBN_SELCHANGE(IDC_ATTRIB_CATEGORY_LIST, OnLbnSelchangeAttribCategoryList)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DynamicAttributesDuplicationDlg
//---------------------------------------------------------------------------
PSS_DynamicAttributesDuplicationDlg::PSS_DynamicAttributesDuplicationDlg(PSS_ProcessGraphModelDoc* pModelDoc,
                                                                         bool                      symbolSelected) :
    PSS_WizardDialog(PSS_DynamicAttributesDuplicationDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_DYNATTRS3_ST_T,
                     IDS_WZ_DYNATTRS3_ST_S),
    m_pModelDoc(pModelDoc),
    m_DupValuesIsChecked(TRUE),
    m_InternalNameChange(false)
{}
//---------------------------------------------------------------------------
PSS_DynamicAttributesDuplicationDlg::~PSS_DynamicAttributesDuplicationDlg()
{}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesDuplicationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DynamicAttributesDuplicationDlg)
    DDX_Control(pDX, IDC_ATTRIB_CATEGORY_LIST, m_CategoryList);
    DDX_Text   (pDX, IDC_ATTRIB_NAME,          m_Name);
    DDX_Text   (pDX, IDC_ATTRIB_CATEGORY_NAME, m_Category);
    DDX_Check  (pDX, IDC_DUPLICATE_VALUES,     m_DupValuesIsChecked);
    DDX_Control(pDX, IDC_ATTRIB_NAME,          m_AttribNameTxtBox);
    DDX_Control(pDX, IDC_DUPLICATE_VALUES,     m_DuplicateValues);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DynamicAttributesDuplicationDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (m_pModelDoc && m_pModelDoc->GetModel() && m_pModelDoc->GetDynamicPropertiesManager())
    {
        PSS_DynamicAttributesManipulator::GetCategories(m_pModelDoc->GetModel(), m_StaticAttribArray, m_DynamicAttribArray);

        const int attribCount = m_DynamicAttribArray.GetSize();

        // fill the dynamic attribute list
        for (int i = 0; i < attribCount; ++i)
            m_CategoryList.AddString(m_DynamicAttribArray.GetAt(i));
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesDuplicationDlg::OnLbnSelchangeAttribCategoryList()
{
    // the lines below are required to keep the values states (MFC bug?)
    m_AttribNameTxtBox.GetWindowText(m_Name);
    m_DupValuesIsChecked = m_DuplicateValues.GetCheck();

    const int curSel = m_CategoryList.GetCurSel();

    if (curSel == LB_ERR)
        return;

    m_InternalNameChange = true;

    m_CategoryList.GetText(curSel, m_Category);
    UpdateData(FALSE);

    m_InternalNameChange = false;
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesDuplicationDlg::OnBnClickedOk()
{
    UpdateData(TRUE);

    // check if the fields required to allow the copy were filled
    if (m_Category.IsEmpty() || m_Name.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_COPYNAMEORCATEGORY_IS_MISSING, MB_OK);
        return;
    }

    const int staticArrCount = m_StaticAttribArray.GetSize();

    // check if the selected name is available and not already attributed to a static attribute
    for (int i = 0; i < staticArrCount; ++i)
        if (m_StaticAttribArray.GetAt(i) == m_Name)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROPCATEGORYNAME_EXIST, MB_OK);
            return;
        }

    const int dynArrCount = m_DynamicAttribArray.GetSize();

    // check if the selected name is available and not already attributed to a dynamic attribute
    for (int i = 0; i < dynArrCount; ++i)
        if (m_DynamicAttribArray.GetAt(i) == m_Name)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROPCATEGORYNAME_EXIST, MB_OK);
            return;
        }

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
