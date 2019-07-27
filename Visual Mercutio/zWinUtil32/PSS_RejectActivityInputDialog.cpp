/****************************************************************************
 * ==> PSS_RejectActivityInputDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a reject activity input dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RejectActivityInputDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RejectActivityInputDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_RejectActivityInputDialog)
    ON_CBN_SELCHANGE(IDC_REJECTCATEGORY, OnSelChangeRejectCategory)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RejectActivityInputDialog
//---------------------------------------------------------------------------
PSS_RejectActivityInputDialog::PSS_RejectActivityInputDialog(CStringArray* pArray, CWnd* pParent) :
    ZIDialog(PSS_RejectActivityInputDialog::IDD, TRUE, pParent),
    m_pArray(pArray)
{}
//---------------------------------------------------------------------------
void PSS_RejectActivityInputDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RejectActivityInputDialog)
    DDX_Control(pDX, IDC_REJECTCATEGORY, m_RejectCategory);
    DDX_Text   (pDX, IDC_REJECT_TEXT,    m_RejectText);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RejectActivityInputDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    if (m_pArray)
    {
        const int arrayCount = m_pArray->GetSize();

        for (int i = 0; i < arrayCount; ++i)
            m_RejectCategory.AddString(m_pArray->GetAt(i));
    }

    // add the owner user text at the last position
    m_OwnerText.LoadString(IDS_SELFTEXT_REJECTCATEGORY);
    m_RejectCategory.AddString(m_OwnerText);

    m_RejectCategory.SetCurSel(0);
    CheckControlStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RejectActivityInputDialog::OnSelChangeRejectCategory()
{
    CheckControlStates();
}
//---------------------------------------------------------------------------
void PSS_RejectActivityInputDialog::OnOK()
{
    UpdateData(TRUE);

    const int curSel = m_RejectCategory.GetCurSel();

    // save text if necessary
    if (curSel != CB_ERR)
    {
        CString selectedText;
        m_RejectCategory.GetLBText(curSel, selectedText);

        // differs from owner user text?
        if (selectedText != m_OwnerText)
            m_RejectText = selectedText;
    }

    if (m_RejectText.IsEmpty())
    {
        MsgBox mBox;

        // ask the user if he wants to insert it from the central repository
        if (mBox.DisplayMsgBox(IDS_REJECTTEXTEMPTY, MB_YESNO) == IDNO)
            return;
    }

    // assign value back, otherwise OnOK from CDialog will scrap changes
    UpdateData(FALSE);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_RejectActivityInputDialog::CheckControlStates()
{
    const int curSel = m_RejectCategory.GetCurSel();

    if (curSel == CB_ERR)
        return;

    CString selectedText;
    m_RejectCategory.GetLBText(curSel, selectedText);

    if (m_OwnerText == selectedText)
    {
        if (GetDlgItem(IDC_REJECT_TEXT))
            GetDlgItem(IDC_REJECT_TEXT)->ShowWindow(SW_SHOW);
    }
    else
    if (GetDlgItem(IDC_REJECT_TEXT))
        GetDlgItem(IDC_REJECT_TEXT)->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
