// **************************************************************************************************************
// *                                          Classe ZVRiskModifyStaticDlg                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 25 juin 2007 - Ajout de la classe ZVRiskModifyStaticDlg.                                    *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de modifier un élément dans les listes déroulantes utilisées par les    *
// * risques.                                                                                                    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskModifyStaticDlg.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_TextFile.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "ZVRiskNewFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZVRiskModifyStaticDlg, CDialog)
    //{{AFX_MSG_MAP(ZVRiskModifyStaticDlg)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_EN_CHANGE(IDC_STATIC_MODIFY_ELEMENT, OnEnChangeStaticModifyElement)
    ON_LBN_SELCHANGE(IDC_STATIC_ELEMENTS_LIST, OnLbnSelchangeStaticElementsList)
    ON_BN_CLICKED(IDC_STATIC_NEW_FILE, OnBnClickedStaticNewFile)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVRiskModifyStaticDlg dialog

ZVRiskModifyStaticDlg::ZVRiskModifyStaticDlg(CString    fileName,
                                             CString    Extension,
                                             int        NbElements,
                                             CWnd*        pParent        /*= NULL*/)
    : CDialog(ZVRiskModifyStaticDlg::IDD, pParent),
    m_FileName(fileName),
    m_Extension(Extension),
    i_NbElements(NbElements),
    m_Element(_T(""))
{
    //{{AFX_DATA_INIT(ZVRiskModifyStaticDlg)
    //}}AFX_DATA_INIT
}

// Cette fonction retourne le nom du fichier utilisé pour la liste en cours de modification.
CString ZVRiskModifyStaticDlg::GetFileName()
{
    return m_FileName;
}

void ZVRiskModifyStaticDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVRiskModifyStaticDlg)
    DDX_Control(pDX, IDC_STATIC_ELEMENTS_LIST, m_ElementsListCtrl);
    DDX_Control(pDX, IDC_STATIC_MODIFY_ELEMENT, m_ElementCtrl);
    DDX_Text(pDX, IDC_STATIC_MODIFY_ELEMENT, m_Element);
    DDX_Control(pDX, IDOK, m_OK);
    DDX_Control(pDX, IDC_ELEMENT_NUMBER, m_ElementNbrCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRiskModifyStaticDlg message handlers

// Cette fonction est appelée lorsque la fenêtre s'initialise.
BOOL ZVRiskModifyStaticDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    PSS_TextFile p_File;

    if (p_File.OpenRead(m_FileName) == TRUE)
    {
        BOOL    m_EndReached = FALSE;
        CString    m_Text = _T("");
        int        i_Count = 0;

        while (m_EndReached != TRUE)
        {
            p_File >> m_Text;

            if (m_Text.IsEmpty() == false)
            {
                m_ElementsListCtrl.AddString(m_Text);
                i_Count++;
            }
            else
            {
                m_EndReached = TRUE;
            }
        }

        p_File.CloseFile();

        if (i_Count != i_NbElements)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CORRUPTED_RISK_FILE, MB_OK);

            m_ElementsListCtrl.EnableWindow(FALSE);
            m_ElementCtrl.EnableWindow(FALSE);
            m_OK.EnableWindow(FALSE);
        }
    }
    else
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOT_OPEN_RISK_FILE, MB_OK);

        m_ElementsListCtrl.EnableWindow(FALSE);
        m_ElementCtrl.EnableWindow(FALSE);
        m_OK.EnableWindow(FALSE);
    }

    return TRUE;
}

// Cette fonction est appelée lorsque l'utilisateur entre une saisie dans la boîte de texte des éléments à modifier.
void ZVRiskModifyStaticDlg::OnEnChangeStaticModifyElement()
{
    int i_Index = m_ElementsListCtrl.GetCurSel();

    if (i_Index >= 0 && i_Index < i_NbElements)
    {
        CString s_Index = _T("");
        CString s_Formater = _T("");

        s_Formater.LoadString(IDS_RISK_STRING_FORMATER);
        s_Formater += _T(" ");

        s_Index.Format(s_Formater, (m_ElementsListCtrl.GetCurSel()));

        m_ElementCtrl.GetWindowText(m_Element);

        m_ElementsListCtrl.DeleteString(i_Index);
        m_ElementsListCtrl.InsertString(i_Index, s_Index + m_Element);
        m_ElementsListCtrl.SetCurSel(i_Index);
    }
}

// Cette fonction est appelée lorsque la sélection de la liste des éléments a changé.
void ZVRiskModifyStaticDlg::OnLbnSelchangeStaticElementsList()
{
    CString s_Index = _T("");
    s_Index.Format(IDS_RISK_STRING_FORMATER, (m_ElementsListCtrl.GetCurSel()));

    m_ElementNbrCtrl.SetWindowText(s_Index);

    m_ElementsListCtrl.GetText(m_ElementsListCtrl.GetCurSel(), m_Element);

    m_Element.Delete(0, 4);

    m_ElementCtrl.SetWindowText(m_Element);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Nouveau"
void ZVRiskModifyStaticDlg::OnBnClickedStaticNewFile()
{
    ZVRiskNewFileDlg m_NewFileDlg(m_Extension);

    if (m_NewFileDlg.DoModal() == IDOK)
    {
        m_FileName = m_NewFileDlg.GetDirectory() + _T("\\") + m_NewFileDlg.GetFileName() + m_Extension;

        while (m_ElementsListCtrl.GetCount() > 0)
        {
            m_ElementsListCtrl.DeleteString(0);
        }
    }

    for (int i = 0; i < i_NbElements; i++)
    {
        CString m_NewEntry = _T("");
        m_NewEntry.Format(IDS_RISK_STRING_ENTRY, i, i);

        m_ElementsListCtrl.AddString(m_NewEntry);
    }
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton OK.
void ZVRiskModifyStaticDlg::OnBnClickedOk()
{
    PSS_File m_File;

    if (m_File.Exist(m_FileName) == TRUE)
        CFile::Remove(m_FileName);

    PSS_TextFile pNewFile;

    pNewFile.OpenWrite(m_FileName);

    for (int i = 0; i < m_ElementsListCtrl.GetCount(); i++)
    {
        CString s = _T("");
        m_ElementsListCtrl.GetText(i, s);
        pNewFile << s + _T("\r\n");
    }

    pNewFile.CloseFile();

    OnOK();
}
