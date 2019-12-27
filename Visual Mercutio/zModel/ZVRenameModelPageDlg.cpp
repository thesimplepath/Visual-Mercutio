// **************************************************************************************************************
// *                                          ZVRenameModelPageDlg                                                *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de sélectionner une page, puis de la renommer.                            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRenameModelPageDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "PSS_ModelSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 3 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVRenameModelPageDlg dialog

BEGIN_MESSAGE_MAP(ZVRenameModelPageDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(ZVRenameModelPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVRenameModelPageDlg::ZVRenameModelPageDlg(PSS_ProcessGraphModelMdl*    pModel,
                                           CStringArray*            pArrayPageName    /*= NULL*/,
                                           ZDProcessGraphPage*        pPageToRename    /*= NULL*/,
                                           PSS_RuntimeClassSet*        pSet            /*= NULL*/,
                                           CWnd*                    pParent            /*= NULL*/)
    : PSS_Dialog(ZVRenameModelPageDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pArrayPageName(pArrayPageName),
    m_pSelectedPage(NULL),
    m_pPageToRename(pPageToRename),
    m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVRenameModelPageDlg)
    m_PageName = _T("");
    //}}AFX_DATA_INIT

    // If a page to rename is defined, assigns the selected page
    if (m_pPageToRename)
    {
        m_pSelectedPage = m_pPageToRename;
    }
}

void ZVRenameModelPageDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVRenameModelPageDlg)
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    DDX_Text(pDX, IDC_PAGENAME, m_PageName);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRenameModelPageDlg message handlers

BOOL ZVRenameModelPageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        PSS_ModelSet DocumentModelSet;
        DocumentModelSet.AddModel(m_pModel);

        m_SymbolTree.Initialize(_T("Document"), &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);

        // Set the OK disabled at startup
        if (GetDlgItem(IDOK))
        {
            GetDlgItem(IDOK)->EnableWindow(FALSE);
        }
    }

    if (m_pPageToRename)
    {
        m_SymbolTree.SelectItemName(m_pPageToRename->GetPageName());
        m_SymbolTree.EnableWindow(FALSE);
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVRenameModelPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (m_SymbolTree.GetSelectedPage() != NULL)
    {
        m_pSelectedPage = m_SymbolTree.GetSelectedPage();
        m_PageName = m_pSelectedPage->GetPageName();

        if (GetDlgItem(IDOK))
        {
            GetDlgItem(IDOK)->EnableWindow(TRUE);
        }
    }
    else
    {
        m_pSelectedPage = NULL;
        m_PageName = _T("");

        if (GetDlgItem(IDOK))
        {
            GetDlgItem(IDOK)->EnableWindow(FALSE);
        }
    }

    UpdateData(FALSE);

    *pResult = 0;
}

void ZVRenameModelPageDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_PageName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
        return;
    }

    // Check existence of new page name
    if (m_pArrayPageName)
    {
        for (int i = 0; i < m_pArrayPageName->GetSize(); ++i)
        {
            if (m_PageName == m_pArrayPageName->GetAt(i))
            {
                // Display error message
                PSS_MsgBox mBox;
                mBox.Show(IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK);
                return;
            }
        }
    }

    PSS_Dialog::OnOK();
}
