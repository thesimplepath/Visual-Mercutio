// **************************************************************************************************************
// *                                        Classe ZVSelectPrestationDlg                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 27 février 2006 - Ajout de la classe ZVSelectPrestationDlg.                                    *
// **************************************************************************************************************
// * Cette classe représente l'interface de sélection d'une prestation, ou d'un groupe de prestations, dans la    *
// * liste.                                                                                                        *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVSelectPrestationDlg.h"

#include "PSS_LogicalPrestationsEntity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVSelectPrestationDlg dialog

BEGIN_MESSAGE_MAP(ZVSelectPrestationDlg, CDialog)
    //{{AFX_MSG_MAP(ZVSelectPrestationDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_PRESTATIONS_TREE, OnSelchangedPrestationsTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectPrestationDlg::ZVSelectPrestationDlg(const CString                    Title                        /*= ""*/,
                                             PSS_LogicalPrestationsEntity*    pMainPrestation                /*= NULL*/,
                                             bool                            AllowPrestationSelection    /*= true*/,
                                             CWnd*                            pParent                        /*=NULL*/)
    : CDialog(ZVSelectPrestationDlg::IDD, pParent),
    m_pPrestationEntity(NULL),
    m_Title(Title),
    m_pMainPrestation(pMainPrestation),
    m_AllowPrestationSelection(AllowPrestationSelection)
{
    //{{AFX_DATA_INIT(ZVSelectPrestationDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

ZVSelectPrestationDlg::ZVSelectPrestationDlg(UINT                            nTitle,
                                             PSS_LogicalPrestationsEntity*    pMainPrestation,
                                             bool                            AllowPrestationSelection    /*= true*/,
                                             CWnd*                            pParent                        /*=NULL*/)
    : CDialog(ZVSelectPrestationDlg::IDD, pParent),
    m_pPrestationEntity(NULL),
    m_pMainPrestation(pMainPrestation),
    m_AllowPrestationSelection(AllowPrestationSelection)
{
    m_Title.LoadString(nTitle);
}

ZVSelectPrestationDlg::~ZVSelectPrestationDlg()
{
    Release();
}

void ZVSelectPrestationDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}

void ZVSelectPrestationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVSelectPrestationDlg)
    DDX_Control(pDX, IDC_PRESTATIONS_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectPrestationDlg message handlers

BOOL ZVSelectPrestationDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString m_Text;
    m_Text.LoadString(IDS_PRESTATION_ROOT_T);
    m_Ctrl.Initialize(m_Text, m_pMainPrestation);

    if (!m_Title.IsEmpty())
    {
        SetWindowText(m_Title);
    }

    if (GetDlgItem(IDOK))
    {
        GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVSelectPrestationDlg::OnOK()
{
    // Save the selected item
    m_pPrestationEntity = m_Ctrl.GetSelectedPrestationEntity();

    CDialog::OnOK();
}

void ZVSelectPrestationDlg::OnSelchangedPrestationsTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    BOOL Enable = FALSE;
    PSS_PrestationsEntity* pEntity = m_Ctrl.GetSelectedPrestationEntity();

    if (pEntity)
    {
        if (m_AllowPrestationSelection && ISA(pEntity, PSS_LogicalPrestationsEntity))
        {
            Enable = TRUE;
        }
    }

    if (GetDlgItem(IDOK))
    {
        GetDlgItem(IDOK)->EnableWindow(Enable);
    }

    *pResult = 0;
}
