// ZVChoosePropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVChoosePropertyDlg.h"

#include "zModel\PSS_ProcessGraphModelMdl.h"

#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"

#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_InputValue.h"
#include "zPtyMgrRes.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVChoosePropertyDlg dialog


ZVChoosePropertyDlg::ZVChoosePropertyDlg(PSS_Properties* pProperties, int ShowType /*= 0*/, bool Selection /*= true*/,
                                         bool AllowItemSelection /*= true*/, bool AllowCategorySelection /*= false*/,
                                         PSS_DynamicPropertiesManager* pPropManager /*=NULL*/,
                                         PSS_ProcessGraphModelMdl* pModel /*=NULL*/,
                                         CWnd* pParent /*=NULL*/)
    : CDialog(ZVChoosePropertyDlg::IDD, pParent),
    m_pProperties(pProperties),
    m_Selection(Selection),
    m_pPropSet(NULL),
    m_pSelectedProperty(NULL),
    m_AllowItemSelection(AllowItemSelection),
    m_AllowCategorySelection(AllowCategorySelection),
    m_pPropManager(pPropManager),
    m_pModel(pModel)
{
    //{{AFX_DATA_INIT(ZVChoosePropertyDlg)
    m_PropType = ShowType;
    //}}AFX_DATA_INIT
}

ZVChoosePropertyDlg::ZVChoosePropertyDlg(PSS_Properties::IPropertySet* pPropSet, int ShowType /*= 0*/, bool Selection /*= true*/,
                                         bool AllowItemSelection /*= true*/, bool AllowCategorySelection /*= false*/,
                                         PSS_DynamicPropertiesManager* pPropManager /*=NULL*/,
                                         PSS_ProcessGraphModelMdl* pModel /*=NULL*/,
                                         CWnd* pParent /*=NULL*/)
    : CDialog(ZVChoosePropertyDlg::IDD, pParent),
    m_pPropSet(pPropSet),
    m_Selection(Selection),
    m_pProperties(NULL),
    m_pSelectedProperty(NULL),
    m_AllowItemSelection(AllowItemSelection),
    m_AllowCategorySelection(AllowCategorySelection),
    m_pPropManager(pPropManager),
    m_pModel(pModel)
{
    m_PropType = ShowType;
}


void ZVChoosePropertyDlg::CheckControlStates()
{
    if (GetDlgItem(ID_RENAMEATTRIBUTE))
        GetDlgItem(ID_RENAMEATTRIBUTE)->EnableWindow(m_PropType == 2 && m_pPropManager != NULL && m_pModel != NULL);
    if (GetDlgItem(ID_DELATTRIBUTE))
        GetDlgItem(ID_DELATTRIBUTE)->EnableWindow(m_PropType == 2 && m_pPropManager != NULL && m_pModel != NULL);

}

void ZVChoosePropertyDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVChoosePropertyDlg)
    DDX_Control(pDX, IDC_PROPERTIES_LIST, m_PropertyList);
    DDX_Radio(pDX, IDC_PROPTYPE, m_PropType);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVChoosePropertyDlg, CDialog)
    //{{AFX_MSG_MAP(ZVChoosePropertyDlg)
    ON_BN_CLICKED(IDC_PROPTYPE, OnProptype)
    ON_BN_CLICKED(ID_DELATTRIBUTE, OnDeleteAttribute)
    ON_BN_CLICKED(ID_RENAMEATTRIBUTE, OnRenameAttribute)
    ON_BN_CLICKED(IDC_PROPTYPE2, OnProptype)
    ON_BN_CLICKED(IDC_PROPTYPE3, OnProptype)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// ZVChoosePropertyDlg message handlers

void ZVChoosePropertyDlg::OnOK()
{
    BOOL Enable = FALSE;
    if (m_Selection)
    {
        int CurSel = m_PropertyList.GetCurSel();
        if (CurSel != LB_ERR)
        {
            PSS_PropertyItem* pProperty = m_PropertyList.GetPropertyItem(CurSel);

            if (pProperty)
            {
                if (m_AllowItemSelection &&
                    !ISA(pProperty, PSS_PropertyItemCategory))
                    Enable = TRUE;
                if (m_AllowCategorySelection &&
                    ISA(pProperty, PSS_PropertyItemCategory))
                    Enable = TRUE;
            }
        }
        if (!Enable)
        {
            // Error message
            PSS_MsgBox mBox;
            mBox.Show(IDS_MUSTSELECT_ATTRIBUTE, MB_OK);
            return;
        }
        m_pSelectedProperty = m_PropertyList.GetPropertyItem(CurSel);
    }

    CDialog::OnOK();
}

BOOL ZVChoosePropertyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Sets the right type
    m_PropertyList.SetDisplayType((PropertyDisplayType)m_PropType);
    // Read-only list
    m_PropertyList.SetListInReadOnly();
    // Initialize the control
    if (m_pPropSet)
        m_PropertyList.Initialize(*m_pPropSet);
    else
        m_PropertyList.Initialize(m_pProperties);

    if (m_Selection == false)
    {
        if (GetDlgItem(IDCANCEL))
            GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

        CString s;
        s.LoadString(IDS_CLOSE_TEXT);
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->SetWindowText(s);
    }
    CheckControlStates();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVChoosePropertyDlg::OnProptype()
{
    UpdateData(TRUE);

    // Sets the right type
    m_PropertyList.SetDisplayType((PropertyDisplayType)m_PropType);
    // Re-Initialize the control
    if (m_pPropSet)
        m_PropertyList.Initialize(*m_pPropSet);
    else
        m_PropertyList.Initialize(m_pProperties);

    CheckControlStates();
}


void ZVChoosePropertyDlg::OnDeleteAttribute()
{
    PSS_MsgBox mBox;
    if (mBox.Show(IDS_CONFIRMDELATTRIB, MB_YESNO) == IDNO)
        return;

    PSS_PropertyItem* pItem = m_PropertyList.GetCurrentPropertyItem();
    if (pItem && ISA(pItem, PSS_PropertyItemCategory))
        pItem = NULL;
    if (!pItem)
        return;


    // Find the attribute in the Dynamic Property manager
    PSS_Property* pProp = m_PropertyList.GetCorrespondingProperty(pItem);
    if (pProp)
    {
        PSS_Property* pProperty = m_pPropManager->GetPropertyItem(pProp->GetCategoryID(), pProp->GetItemID());
        if (pProperty)
        {
            //            m_PropertyList.DeletePropertyItem( pItem );
            //            m_PropertyList.Refresh();
                        // Reassign the property to all symbols
            PSS_DynamicAttributesManipulator::DeleteProperty(m_pModel, pProperty);
            // Finally, unregister the property
            m_pPropManager->UnregisterProperty(pProp->GetCategoryID(), pProp->GetItemID());
            // Close the dialog
            CDialog::EndDialog(IDOK);

        }
    }

}

void ZVChoosePropertyDlg::OnRenameAttribute()
{
    PSS_PropertyItem* pItem = m_PropertyList.GetCurrentPropertyItem();
    if (pItem && ISA(pItem, PSS_PropertyItemCategory))
        pItem = NULL;
    if (!pItem)
        return;
    // Call the dialog to input the new name
    PSS_InputValue InputValue(IDS_RENAMEATTRIB, pItem->GetName());

    if (InputValue.DoModal() == IDOK)
    {
        // Find the attribute in the Dynamic Property manager
        PSS_Property* pProp = m_PropertyList.GetCorrespondingProperty(pItem);
        if (pProp)
        {
            PSS_Property* pProperty = m_pPropManager->GetPropertyItem(pProp->GetCategoryID(), pProp->GetItemID());
            if (pProperty)
            {
                pProperty->SetLabel(InputValue.GetValue());
                //                pItem->SetName( InputValue.GetValue() );
                //                m_PropertyList.Refresh();
                                // Reassign the property to all symbols
                PSS_DynamicAttributesManipulator::ReassignProperty(m_pModel, pProperty);
                // Close the dialog
                CDialog::EndDialog(IDOK);

            }
        }
    }


}

