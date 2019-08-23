/****************************************************************************
 * ==> PSS_PublishModelAttributesDialog ------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model attributes to      *
 *               publish                                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelAttributesDialog.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelAttributesDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelAttributesDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelAttributesDialog
//---------------------------------------------------------------------------
PSS_PublishModelAttributesDialog::PSS_PublishModelAttributesDialog(ZBPropertyAttributes* pPropAttributes,
                                                                   ZBPropertySet*        pPropSet,
                                                                   CWnd*                 pParent) :
    PSS_WizardDialog(PSS_PublishModelAttributesDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_PUBLISHMODELATTRIBUTES_S,
                     IDS_PUBLISHMODELATTRIBUTES_T),
      m_pPropAttributes(pPropAttributes),
      m_pPropSet(pPropSet)
{}
//---------------------------------------------------------------------------
void PSS_PublishModelAttributesDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelAttributesDialog)
    DDX_Control(pDX, IDC_HTMLATTRIBUTE_TREE, m_Attributes);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelAttributesDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // initialize the attribute tree control
    m_Attributes.Initialize(m_pPropAttributes,m_pPropSet);

    // return TRUE unless the focus was set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelAttributesDialog::OnOK()
{
    UpdateData();
    m_Attributes.FillCorrespondingCheckedItems();

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
