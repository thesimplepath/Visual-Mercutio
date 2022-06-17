/****************************************************************************
 * ==> PSS_DynamicAttributesCreation ---------------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic attributes creation wizard              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DynamicAttributesCreation.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "PSS_DynamicAttributesManipulator.h"
#include "PSS_ProcessGraphModelDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_DynamicAttributesCreation
//---------------------------------------------------------------------------
PSS_DynamicAttributesCreation::PSS_DynamicAttributesCreation(PSS_ProcessGraphModelDoc* pModelDoc, bool symbolSelected) :
    m_pModelDoc(pModelDoc),
    m_PropertyType(PSS_Property::IEType::IE_T_EditString),
    m_Visibility(0),
    m_SymbolSelected(symbolSelected)
{}
//---------------------------------------------------------------------------
PSS_DynamicAttributesCreation::~PSS_DynamicAttributesCreation()
{}
//---------------------------------------------------------------------------
int PSS_DynamicAttributesCreation::DoModal()
{
    if (!m_pModelDoc)
        return IDCANCEL;

    PSS_DynamicAttributesSelectCategoryDlg categoryPage(m_pModelDoc);

    if (categoryPage.DoModal() == IDCANCEL)
        return IDCANCEL;

    // assign values
    m_CategoryName = categoryPage.GetCategoryName();

    PSS_DynamicAttributesCreateAttributeDlg attributePage(m_pModelDoc, m_CategoryName, m_SymbolSelected);

    if (attributePage.DoModal() == IDCANCEL)
        return IDCANCEL;

    // assign values
    m_AttributeName        = attributePage.GetAttributeName();
    m_AttributeDescription = attributePage.GetAttributeDescription();
    m_PropertyType         = attributePage.GetPropertyType();
    m_Visibility           = attributePage.GetVisibility();

    return IDOK;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DynamicAttributesSelectCategoryDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_DynamicAttributesSelectCategoryDlg)
    ON_EN_CHANGE(IDC_CATEGORYNAME, OnChangeCategoryName)
    ON_LBN_SELCHANGE(IDC_CATEGORY_LIST, OnSelchangeCategoryList)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DynamicAttributesSelectCategoryDlg
//---------------------------------------------------------------------------
PSS_DynamicAttributesSelectCategoryDlg::PSS_DynamicAttributesSelectCategoryDlg(PSS_ProcessGraphModelDoc* pModelDoc,
                                                                               CWnd*                     pParent) :
    PSS_WizardDialog(PSS_DynamicAttributesSelectCategoryDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_DYNATTRS1_ST_S,
                     IDS_WZ_DYNATTRS1_ST_T),
    m_pModelDoc(pModelDoc),
    m_InternalNameChange(false)
{}
//---------------------------------------------------------------------------
PSS_DynamicAttributesSelectCategoryDlg::~PSS_DynamicAttributesSelectCategoryDlg()
{}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesSelectCategoryDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DynamicAttributesSelectCategoryDlg)
    DDX_Control(pDX, IDC_CATEGORY_LIST, m_CategoryList);
    DDX_Text   (pDX, IDC_CATEGORYNAME,  m_CategoryName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DynamicAttributesSelectCategoryDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (m_pModelDoc && m_pModelDoc->GetModel() && m_pModelDoc->GetDynamicPropertiesManager())
    {
        PSS_DynamicAttributesManipulator::GetCategories(m_pModelDoc->GetModel(), m_StaticAttribArray, m_DynamicAttribArray);

        const int attribCount = m_DynamicAttribArray.GetSize();

        // fill the list box with dynamic categories
        for (int i = 0; i < attribCount; ++i)
            m_CategoryList.AddString(m_DynamicAttribArray.GetAt(i));
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesSelectCategoryDlg::OnChangeCategoryName()
{
    // todo -cFeature -oJean: If this is a RICHEDIT control, it will not send this notification unless
    // the PSS_WizardDialog::OnInitDialog() function is overriden, and the CRichEditCtrl().SetEventMask()
    // is called with the ENM_CHANGE flag in the mask
    if (m_InternalNameChange)
        return;

    UpdateData(TRUE);
    m_CategoryList.SelectString(0, (const char*)m_CategoryName);
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesSelectCategoryDlg::OnSelchangeCategoryList()
{
    const int curSel = m_CategoryList.GetCurSel();

    if (curSel == LB_ERR)
        return;

    m_InternalNameChange = true;

    try
    {
        m_CategoryList.GetText(curSel, m_CategoryName);
        UpdateData(FALSE);
    }
    catch (...)
    {
        m_InternalNameChange = false;
        throw;
    }

    m_InternalNameChange = false;
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesSelectCategoryDlg::OnNext()
{
    // check information
    if (!CheckData())
        return;

    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesSelectCategoryDlg::OnOK()
{
    // check information
    if (!CheckData())
        return;

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesSelectCategoryDlg::CheckData()
{
    UpdateData(TRUE);

    if (m_CategoryName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROPCATEGORYNAME_MISSING, MB_OK);
        return false;
    }

    const int attribCount = m_StaticAttribArray.GetSize();

    for (int i = 0; i < attribCount; ++i)
        if (m_StaticAttribArray.GetAt(i) == m_CategoryName)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROPCATEGORYNAME_EXIST, MB_OK);
            return false;
        }

    return true;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DynamicAttributesCreateAttributeDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_DynamicAttributesCreateAttributeDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DynamicAttributesCreateAttributeDlg
//---------------------------------------------------------------------------
PSS_DynamicAttributesCreateAttributeDlg::PSS_DynamicAttributesCreateAttributeDlg(PSS_ProcessGraphModelDoc* pModelDoc,
                                                                                 const CString&            category,
                                                                                 bool                      symbolSelected,
                                                                                 CWnd*                     pParent) :
    PSS_WizardDialog(PSS_DynamicAttributesCreateAttributeDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_DYNATTRS2_ST_S,
                     IDS_WZ_DYNATTRS2_ST_T),
    m_pModelDoc(pModelDoc),
    m_PropertyType(PSS_Property::IEType::IE_T_EditString),
    m_Category(category),
    m_Visibility(0),
    m_SymbolSelected(symbolSelected)
{}
//---------------------------------------------------------------------------
PSS_DynamicAttributesCreateAttributeDlg::~PSS_DynamicAttributesCreateAttributeDlg()
{}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesCreateAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DynamicAttributesCreateAttributeDlg)
    DDX_Control(pDX, IDC_ATTRIB_VISIBILITY, m_AttributeVisibility);
    DDX_Control(pDX, IDC_ATTRIB_TYPE,       m_AttributeType);
    DDX_Text   (pDX, IDC_ATTR_DESCRIPTION,  m_AttributeDescription);
    DDX_Text   (pDX, IDC_ATTRIB_NAME,       m_AttributeName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DynamicAttributesCreateAttributeDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    CString values;

    // fill comboboxes
    PSS_Tokenizer token;

    // data type combo
    values.LoadString(IDS_PROPTYPE_LIST);

    CString str = token.GetFirstToken(values);

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        m_AttributeType.AddString(str);

        // get the next token
        str = token.GetNextToken();
    }

    // select the first item in the list
    m_AttributeType.SetCurSel(0);

    // visibility combo
    values.LoadString(IDS_PROPVISIBILITY_LIST);

    str = token.GetFirstToken(values);

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        m_AttributeVisibility.AddString(str);

        // get the next token
        str = token.GetNextToken();
    }

    // select the first item in the list
    m_AttributeVisibility.SetCurSel(0);

    // if no symbol selected
    if (!m_SymbolSelected)
    {
        m_AttributeVisibility.SetCurSel(2);
        m_AttributeVisibility.EnableWindow(FALSE);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesCreateAttributeDlg::OnNext()
{
    // check information
    if (!CheckData())
        return;

    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_DynamicAttributesCreateAttributeDlg::OnOK()
{
    // check information
    if (!CheckData())
        return;

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
bool PSS_DynamicAttributesCreateAttributeDlg::CheckData()
{
    UpdateData(TRUE);

    if (m_AttributeName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROPATTRIBNAME_MISSING, MB_OK);
        return false;
    }

    if (!m_pModelDoc || !m_pModelDoc->GetDynamicPropertiesManager())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROP_INITIALIZATIONPRB, MB_OK);
        return false;
    }

    if (m_pModelDoc->GetDynamicPropertiesManager()->PropertyItemExist(m_Category, m_AttributeName))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROPATTRIBNAME_EXIST, MB_OK);
        return false;
    }

    m_Visibility = m_AttributeVisibility.GetCurSel();

    switch (m_AttributeType.GetCurSel())
    {
        case 0:  m_PropertyType = PSS_Property::IEType::IE_T_EditString;    break;
        case 1:  m_PropertyType = PSS_Property::IEType::IE_T_EditMultiline; break;
        case 2:  m_PropertyType = PSS_Property::IEType::IE_T_EditNumber;    break;
        case 3:  m_PropertyType = PSS_Property::IEType::IE_T_EditDate;      break;
        case 4:  m_PropertyType = PSS_Property::IEType::IE_T_EditTime;      break;
        case 5:  m_PropertyType = PSS_Property::IEType::IE_T_EditDuration;  break;
        default: return false;
    }

    return true;
}
//---------------------------------------------------------------------------
