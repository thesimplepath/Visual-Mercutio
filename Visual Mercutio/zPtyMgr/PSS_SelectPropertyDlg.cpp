/****************************************************************************
 * ==> PSS_SelectPropertyDlg -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog box to select a property                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectPropertyDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_InputValue.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"

// resources
#include "zPtyMgrRes.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectPropertyDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectPropertyDlg)
    ON_BN_CLICKED(IDC_PROPTYPE, OnProptype)
    ON_BN_CLICKED(IDC_PROPTYPE2, OnProptype)
    ON_BN_CLICKED(IDC_PROPTYPE3, OnProptype)
    ON_BN_CLICKED(ID_RENAMEATTRIBUTE, OnRenameAttribute)
    ON_BN_CLICKED(ID_DELATTRIBUTE, OnDeleteAttribute)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectPropertyDlg
//---------------------------------------------------------------------------
PSS_SelectPropertyDlg::PSS_SelectPropertyDlg(PSS_Properties*               pProperties,
                                             int                           showType,
                                             bool                          selection,
                                             bool                          allowItemSelection,
                                             bool                          allowCategorySelection,
                                             PSS_DynamicPropertiesManager* pPropManager,
                                             PSS_ProcessGraphModelMdl*     pModel,
                                             CWnd*                         pParent) :
    CDialog(PSS_SelectPropertyDlg::IDD, pParent),
    m_pProperties(pProperties),
    m_pPropSet(NULL),
    m_pSelectedProperty(NULL),
    m_pPropManager(pPropManager),
    m_pModel(pModel),
    m_PropType(showType),
    m_AllowItemSelection(allowItemSelection),
    m_AllowCategorySelection(allowCategorySelection),
    m_Selection(selection)
{}
//---------------------------------------------------------------------------
PSS_SelectPropertyDlg::PSS_SelectPropertyDlg(PSS_Properties::IPropertySet* pPropSet,
                                             int                           showType,
                                             bool                          selection,
                                             bool                          allowItemSelection,
                                             bool                          allowCategorySelection,
                                             PSS_DynamicPropertiesManager* pPropManager,
                                             PSS_ProcessGraphModelMdl*     pModel,
                                             CWnd*                         pParent) :
    CDialog(PSS_SelectPropertyDlg::IDD, pParent),
    m_pProperties(NULL),
    m_pPropSet(pPropSet),
    m_pSelectedProperty(NULL),
    m_pPropManager(pPropManager),
    m_pModel(pModel),
    m_PropType(showType),
    m_AllowItemSelection(allowItemSelection),
    m_AllowCategorySelection(allowCategorySelection),
    m_Selection(selection)
{}
//---------------------------------------------------------------------------
void PSS_SelectPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectPropertyDlg)
    DDX_Control(pDX, IDC_PROPERTIES_LIST, m_PropertyList);
    DDX_Radio  (pDX, IDC_PROPTYPE,        m_PropType);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectPropertyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // set the right type
    m_PropertyList.SetShowType(PSS_PropertyItemManager::IEPropertyShowType(m_PropType));

    // read-only list
    m_PropertyList.SetListInReadOnly();

    // initialize the control
    if (m_pPropSet)
        m_PropertyList.Initialize(*m_pPropSet);
    else
        m_PropertyList.Initialize(m_pProperties);

    if (!m_Selection)
    {
        if (GetDlgItem(IDCANCEL))
            GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

        CString str;
        str.LoadString(IDS_CLOSE_TEXT);

        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->SetWindowText(str);
    }

    CheckControlStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectPropertyDlg::OnProptype()
{
    UpdateData(TRUE);

    // set the right type
    m_PropertyList.SetShowType(PSS_PropertyItemManager::IEPropertyShowType(m_PropType));

    // reinitialize the control
    if (m_pPropSet)
        m_PropertyList.Initialize(*m_pPropSet);
    else
        m_PropertyList.Initialize(m_pProperties);

    CheckControlStates();
}
//---------------------------------------------------------------------------
void PSS_SelectPropertyDlg::OnRenameAttribute()
{
    PSS_PropertyItem* pItem = m_PropertyList.GetCurrentPropertyItem();

    if (pItem && ISA(pItem, PSS_PropertyItemCategory))
        pItem = NULL;

    if (!pItem)
        return;

    // call the dialog to input the new name
    PSS_InputValue InputValue(IDS_RENAMEATTRIB, pItem->GetName());

    if (InputValue.DoModal() == IDOK)
    {
        // search the attribute in the dynamic property manager
        PSS_Property* pProp = m_PropertyList.GetMatchingProperty(pItem);

        if (pProp)
        {
            PSS_Property* pProperty = m_pPropManager->GetPropertyItem(pProp->GetCategoryID(), pProp->GetItemID());

            if (pProperty)
            {
                pProperty->SetLabel(InputValue.GetValue());

                // reassign the property to all symbols
                PSS_DynamicAttributesManipulator::ReassignProperty(m_pModel, pProperty);

                // close the dialog
                CDialog::EndDialog(IDOK);

            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SelectPropertyDlg::OnDeleteAttribute()
{
    PSS_MsgBox mBox;

    if (mBox.Show(IDS_CONFIRMDELATTRIB, MB_YESNO) == IDNO)
        return;

    PSS_PropertyItem* pItem = m_PropertyList.GetCurrentPropertyItem();

    if (pItem && ISA(pItem, PSS_PropertyItemCategory))
        pItem = NULL;

    if (!pItem)
        return;

    // search the attribute in the dynamic property manager
    PSS_Property* pProp = m_PropertyList.GetMatchingProperty(pItem);

    if (pProp)
    {
        PSS_Property* pProperty = m_pPropManager->GetPropertyItem(pProp->GetCategoryID(), pProp->GetItemID());

        if (pProperty)
        {
            // reassign the property to all symbols
            PSS_DynamicAttributesManipulator::DeleteProperty(m_pModel, pProperty);

            // unregister the property
            m_pPropManager->UnregisterProperty(pProp->GetCategoryID(), pProp->GetItemID());
 
            // close the dialog
            CDialog::EndDialog(IDOK);

        }
    }
}
//---------------------------------------------------------------------------
void PSS_SelectPropertyDlg::OnOK()
{
    BOOL enable = FALSE;

    if (m_Selection)
    {
        const int curSel = m_PropertyList.GetCurSel();

        if (curSel != LB_ERR)
        {
            PSS_PropertyItemCategory* pCatProp = dynamic_cast<PSS_PropertyItemCategory*>(m_PropertyList.GetPropertyItem(curSel));

            if (m_AllowItemSelection && !pCatProp)
                enable = TRUE;
            else
            if (m_AllowCategorySelection && pCatProp)
                enable = TRUE;
        }

        if (!enable)
        {
            // error message
            PSS_MsgBox mBox;
            mBox.Show(IDS_MUSTSELECT_ATTRIBUTE, MB_OK);
            return;
        }

        m_pSelectedProperty = m_PropertyList.GetPropertyItem(curSel);
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectPropertyDlg::CheckControlStates()
{
    if (GetDlgItem(ID_RENAMEATTRIBUTE))
        GetDlgItem(ID_RENAMEATTRIBUTE)->EnableWindow(m_PropType == 2 && m_pPropManager && m_pModel);

    if (GetDlgItem(ID_DELATTRIBUTE))
        GetDlgItem(ID_DELATTRIBUTE)->EnableWindow(m_PropType == 2 && m_pPropManager && m_pModel);

}
//---------------------------------------------------------------------------
