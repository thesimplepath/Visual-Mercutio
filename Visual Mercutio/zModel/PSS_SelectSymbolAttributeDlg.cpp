/****************************************************************************
 * ==> PSS_SelectSymbolAttributeDlg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a select symbol attribute dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectSymbolAttributeDlg.h"

// processsoft
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectSymbolAttributeDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectSymbolAttributeDlg)
    ON_BN_CLICKED(ID_APPLYTOALL, OnApplyToAll)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectSymbolAttributeDlg
//---------------------------------------------------------------------------
PSS_SelectSymbolAttributeDlg::PSS_SelectSymbolAttributeDlg(ZBPropertyAttributes* pPropAttributes,
                                                           ZBPropertySet*        pPropSet,
                                                           CWnd*                 pParent) :
    CDialog(PSS_SelectSymbolAttributeDlg::IDD, pParent),
    m_pPropAttributes(pPropAttributes),
    m_pPropSet(pPropSet),
    m_SetAsDefaultToAll(FALSE),
    m_ShowLabel(TRUE)
{
    if (m_pPropAttributes)
        m_ShowLabel = m_pPropAttributes->GetDisplayTitleText();
}
//---------------------------------------------------------------------------
PSS_SelectSymbolAttributeDlg::~PSS_SelectSymbolAttributeDlg()
{}
//---------------------------------------------------------------------------
void PSS_SelectSymbolAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectSymbolAttributeDlg)
    DDX_Control(pDX, IDC_ATTRIBUTE_TREE,     m_AttributeTree);
    DDX_Check  (pDX, IDC_SETASDEFAULT_TOALL, m_SetAsDefaultToAll);
    DDX_Check  (pDX, IDC_SHOWLABEL,          m_ShowLabel);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolAttributeDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // initialize the attribute tree control
    m_AttributeTree.Initialize(m_pPropAttributes, m_pPropSet);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolAttributeDlg::OnApplyToAll()
{
    UpdateData(TRUE);

    // ask the control to fill the matching checked items
    m_AttributeTree.FillMatchingCheckedItems();

    if (m_pPropAttributes)
        m_pPropAttributes->SetDisplayTitleText(m_ShowLabel);

    CDialog::EndDialog(ID_APPLYTOALL);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolAttributeDlg::OnOK()
{
    UpdateData(TRUE);

    // ask the control to fill the matching checked items
    m_AttributeTree.FillMatchingCheckedItems();

    if (m_pPropAttributes)
        m_pPropAttributes->SetDisplayTitleText(m_ShowLabel);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
