// ZVPublishModelAttributes.cpp : implementation file

#include "stdafx.h"
#include "ZVPublishModelAttributes.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelAttributes dialog

BEGIN_MESSAGE_MAP( ZVPublishModelAttributes, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVPublishModelAttributes)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishModelAttributes::ZVPublishModelAttributes( ZBPropertyAttributes*    pPropAttributes    /*= NULL*/,
                                                    ZBPropertySet*            pPropSet        /*= NULL*/,
                                                    CWnd*                    pParent            /*= NULL*/ )
    : ZIWizardDialog    ( ZVPublishModelAttributes::IDD,    // Dialog template
                          IDB_WZBMP1,                        // Bitmap to display
                          0,                                // Icon do display
                          0,                                // Window Title
                          IDS_PUBLISHMODELATTRIBUTES_S,        // Wizard title
                          IDS_PUBLISHMODELATTRIBUTES_T ),    // Wizard text
      m_pPropAttributes    ( pPropAttributes ),
      m_pPropSet        ( pPropSet )
{
    //{{AFX_DATA_INIT(ZVPublishModelAttributes)
    //}}AFX_DATA_INIT
}

void ZVPublishModelAttributes::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVPublishModelAttributes)
    DDX_Control(pDX, IDC_HTMLATTRIBUTE_TREE, m_Attributes);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelAttributes message handlers

BOOL ZVPublishModelAttributes::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    // Initialize the attribute tree control
    m_Attributes.Initialize( m_pPropAttributes,m_pPropSet );

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVPublishModelAttributes::OnOK()
{
    UpdateData();
    m_Attributes.FillCorrespondingCheckedItems();

    ZIWizardDialog::OnOK();
}
