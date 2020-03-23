/****************************************************************************
 * ==> PSS_InputAttributesDefinitionDlg ------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes definition dialog box         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InputAttributesDefinitionDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "zPtyMgr\PSS_SelectPropertyDlg.h"
#include "PSS_InputAttributes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputAttributesDefinitionDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_InputAttributesDefinitionDlg)
    ON_COMMAND(IDC_CHOOSE_DYNATTR, OnChooseDynAttr)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputAttributesDefinitionDlg
//---------------------------------------------------------------------------
PSS_InputAttributesDefinitionDlg::PSS_InputAttributesDefinitionDlg(PSS_DynamicPropertiesManager* pPropManager,
                                                                   PSS_Properties::IPropertySet* pSet,
                                                                   PSS_InputAttribute*           pInputAttr,
                                                                   CWnd*                         pParent) :
    CDialog(PSS_InputAttributesDefinitionDlg::IDD, pParent),
    m_pPropManager(pPropManager),
    m_pSet(pSet),
    m_pInputAttr(pInputAttr),
    m_CategoryID(-1),
    m_ItemID(-1),
    m_Visibility(-1),
    m_Flag(-1)
{}
//---------------------------------------------------------------------------
PSS_InputAttributesDefinitionDlg::~PSS_InputAttributesDefinitionDlg()
{}
//---------------------------------------------------------------------------
void PSS_InputAttributesDefinitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_InputAttributesDefinitionDlg)
    DDX_Control(pDX, IDC_INPATTR_VISIBILITY, m_VisibilityList);
    DDX_Control(pDX, IDC_INPATTR_FLAG,       m_FlagList);
    DDX_Text   (pDX, IDC_INPATTR_DEFVALUE,   m_DefaultValue);
    DDX_Text   (pDX, IDC_DYNATTRIB,          m_DynamicAttributeName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_InputAttributesDefinitionDlg::OnInitDialog()
{
    if (m_pInputAttr && m_pPropManager)
    {
        PSS_Property* pProp = m_pPropManager->GetPropertyItem(m_pInputAttr->GetCategoryID(), m_pInputAttr->GetItemID());

        if (pProp)
        {
            m_CategoryID           = pProp->GetCategoryID();
            m_ItemID               = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();
        }

        m_DefaultValue = m_pInputAttr->GetDefaultValue();
    }

    CDialog::OnInitDialog();

    if (m_pInputAttr)
    {
        if (GetDlgItem(IDC_CHOOSE_DYNATTR))
            GetDlgItem(IDC_CHOOSE_DYNATTR)->EnableWindow(FALSE);

        m_FlagList.SetCurSel(m_pInputAttr->GetFlag());
        m_VisibilityList.SetCurSel((m_pInputAttr->GetSymbolRef() != -1) ? 0 : 1);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesDefinitionDlg::OnChooseDynAttr()
{
    if (!m_pSet)
        return;

    PSS_SelectPropertyDlg selectDlg(m_pSet, 2);

    if (selectDlg.DoModal() == IDOK)
    {
        PSS_Property* pProp = selectDlg.GetSelectedProperty();

        if (pProp)
        {
            m_CategoryID           = pProp->GetCategoryID();
            m_ItemID               = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();

            // push to dialog data
            UpdateData(FALSE);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_InputAttributesDefinitionDlg::OnOK()
{
    UpdateData(TRUE);

    // a dynamic attributes must be selected
    if (m_DynamicAttributeName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_DYNAMICATTRIBUTES_REQUIRED, MB_OK);
    }

    m_Visibility = m_VisibilityList.GetCurSel();
    m_Flag       = m_FlagList.GetCurSel();

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
