/****************************************************************************
 * ==> PSS_FindSymbolExtDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a find symbol dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FindSymbolExtDlg.h"

// processsoft
#include "zProperty\PSS_PropertyAttributes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FindSymbolExtDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_FindSymbolExtDlg)
    ON_EN_CHANGE(IDC_SYMBOLNAME, OnChangeSymbolName)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FindSymbolExtDlg
//---------------------------------------------------------------------------
PSS_FindSymbolExtDlg::PSS_FindSymbolExtDlg(PSS_PropertyAttributes*       pPropAttributes,
                                           PSS_Properties::IPropertySet* pPropSet,
                                           CWnd*                         pParent) :
    PSS_Dialog(PSS_FindSymbolExtDlg::IDD, TRUE, pParent),
    m_pPropAttributes(pPropAttributes),
    m_pPropSet(pPropSet),
    m_InAllModels(TRUE),
    m_CaseSensitive(FALSE),
    m_PartialSearch(TRUE)
{}
//---------------------------------------------------------------------------
PSS_FindSymbolExtDlg::~PSS_FindSymbolExtDlg()
{}
//---------------------------------------------------------------------------
void PSS_FindSymbolExtDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_FindSymbolExtDlg)
    DDX_Control(pDX, IDC_ATTRIBUTE_TREE, m_AttributeText);
    DDX_Check  (pDX, IDC_INALLMODELS,    m_InAllModels);
    DDX_Check  (pDX, IDC_CASESENSITIVE,  m_CaseSensitive);
    DDX_Check  (pDX, IDC_PARTIAL,        m_PartialSearch);
    DDX_Text   (pDX, IDC_WHAT,           m_SearchArgument);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_FindSymbolExtDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    // initialize the attribute tree control
    m_AttributeText.Initialize(m_pPropAttributes, m_pPropSet);

    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FindSymbolExtDlg::OnChangeSymbolName()
{
    // if this is a RICHEDIT control, it will not send this notification unless the
    // ZIDialog::OnInitDialog() function is overriden, and the CRichEditCtrl().SetEventMask()
    // function is called with the ENM_CHANGE flag in the mask
    CheckControlState();

    // set default to search button
    if (GetDlgItem(IDC_FIND))
        SetDefID(IDC_FIND);
}
//---------------------------------------------------------------------------
void PSS_FindSymbolExtDlg::OnOK()
{
    m_AttributeText.FillMatchingCheckedItems();
    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_FindSymbolExtDlg::CheckControlState()
{
    UpdateData();

    if (GetDlgItem(IDC_FIND))
        GetDlgItem(IDC_FIND)->EnableWindow(!m_SearchArgument.IsEmpty());
}
//---------------------------------------------------------------------------
