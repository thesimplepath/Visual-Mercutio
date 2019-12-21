// ******************************************************************************************************************
// *                                           Classe ZVPrestationsInfoDlg                                            *
// ******************************************************************************************************************
// * JMR-MODIF - Le 11 octobre 2005 - Ajout de la classe ZVPrestationsInfoDlg.                                        *
// ******************************************************************************************************************
// * Cette classe représente une boîte de dialogue personnalisée pour les messages en provenance du gestionnaire de    *
// * données des prestations.                                                                                        *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZVPrestationsInfoDlg.h"

#include "PSS_LogicalPrestationsEntity.h"

#include "zBaseLib\PSS_MsgBox.h"

#include "zBaseLib\zBaseLibRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVPrestationsInfoDlg dialog

BEGIN_MESSAGE_MAP(ZVPrestationsInfoDlg, CDialog)
    //{{AFX_MSG_MAP(ZVPrestationsInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPrestationsInfoDlg::ZVPrestationsInfoDlg(UINT                        nTitleID            /*= -1*/,
                                           PSS_LogicalPrestationsEntity*    pLogicalPrestation    /*= NULL*/,
                                           const CString                Name                /*= _T( "" )*/,
                                           const CString                Description            /*= _T( "" )*/,
                                           bool                        ModifyMode            /*= false*/,
                                           CWnd*                        pParent                /*=NULL*/)
    : CDialog(ZVPrestationsInfoDlg::IDD, pParent),
    m_pPrestation(pLogicalPrestation),
    m_ModifyMode(ModifyMode)
{
    //{{AFX_DATA_INIT(ZVPrestationsInfoDlg)
    m_Description = Description;
    m_Name = Name;
    //}}AFX_DATA_INIT

    // Assigns also the initial cost
    if (nTitleID != -1)
    {
        m_Title.LoadString(nTitleID);
    }
}

ZVPrestationsInfoDlg::~ZVPrestationsInfoDlg()
{}

void ZVPrestationsInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVPrestationsInfoDlg)
    DDX_Text(pDX, IDC_PRESTATION_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_PRESTATION_NAME, m_Name);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPrestationsInfoDlg message handlers

void ZVPrestationsInfoDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_ModifyMode)
    {
        if (m_pPrestation && m_pPrestation->PrestationExist(m_Name))
        {
            // Already exists
            PSS_MsgBox mBox;
            mBox.Show(IDS_PRESTATION_ALREADYEXIST, MB_OK);
            return;
        }
    }

    CDialog::OnOK();
}

BOOL ZVPrestationsInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (m_ModifyMode)
    {
        if (GetDlgItem(IDC_PRESTATION_NAME))
            GetDlgItem(IDC_PRESTATION_NAME)->EnableWindow(FALSE);
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}
