/****************************************************************************
 * ==> PSS_ReferenceFileDialog ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a reference file dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ReferenceFileDialog.h"

// processsoft
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_Global.h"
#include "PSS_NewFormDialog.h"
#include "PSS_UrlInputDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ReferenceFileDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_ReferenceFileDialog)
    ON_BN_CLICKED(IDC_ADDFILE, OnAddfile)
    ON_BN_CLICKED(IDC_ADDURL, OnAddurl)
    ON_BN_CLICKED(IDC_SCRIPTOR, OnScriptor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ReferenceFileDialog
//---------------------------------------------------------------------------
PSS_ReferenceFileDialog::PSS_ReferenceFileDialog(const CString& reference,
                                                 int            insertionType,
                                                 int            activationType,
                                                 CWnd*          pParent) :
    CDialog(PSS_ReferenceFileDialog::IDD, pParent),
    m_Reference(reference),
    m_InsertionType(insertionType),
    m_ActivationType(activationType)
{}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ReferenceFileDialog)
    DDX_Control(pDX, IDC_ACTIVATIONTYPE, m_ActivationTypeCtrl);
    DDX_Control(pDX, IDC_INSERTIONTYPE,  m_InsertionTypeCtrl);
    DDX_Text   (pDX, IDC_REFERENCE_FILE, m_Reference);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ReferenceFileDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // fill the activation type list box
    std::size_t count = (PSS_Global::GetArrayActivationType() ? PSS_Global::GetArrayActivationType()->GetSize() : 0);

    for (std::size_t i = 0; i < count; ++i)
        m_ActivationTypeCtrl.AddString(PSS_Global::GetArrayActivationType()->GetAt(i));

    // fill the insertion type list box
    count = (PSS_Global::GetArrayInsertionType()) ? PSS_Global::GetArrayInsertionType()->GetSize() : 0;

    for (std::size_t i = 0; i < count; ++i)
        m_InsertionTypeCtrl.AddString(PSS_Global::GetArrayInsertionType()->GetAt(i));

    // set the right activation type
    m_ActivationTypeCtrl.SelectString(-1, PSS_Global::GetActivationTypeString(m_ActivationType));

    // set the right insertion type
    m_InsertionTypeCtrl.SelectString(-1, PSS_Global::GetInsertionTypeString(m_InsertionType));

    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::OnAddfile()
{
    CString filters;

    // set the "*.*" files filter
    VERIFY(filters.LoadString(AFX_IDS_ALLFILTER));
    filters += (char)'\0';
    filters += _T("*.*");
    filters += (char)'\0';

    PSS_FileDialog fileDialog(IDS_SELECT_A_FILE, filters, 1);

    if (fileDialog.DoModal() == IDOK)
    {
        CString fileName = fileDialog.GetFileName();

        // is empty?
        if (!fileName.IsEmpty())
        {
            if (fileName.Find(_T("file://")) == -1)
                m_Reference = _T("file://") + fileName;
            else
                m_Reference = fileName;

            m_Reference.MakeLower();
            UpdateData(FALSE);
            CheckControlState();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::OnAddurl()
{
    PSS_UrlInputDialog urlInputDialog;

    if (urlInputDialog.DoModal() == IDOK)
    {
        const CString url = urlInputDialog.GetURL();

        // is empty?
        if (!url.IsEmpty())
        {
            if (url.Find(_T("http://")) == -1 && url.Find(_T("ftp://")) == -1)
                m_Reference = _T("http://") + url;
            else
                m_Reference = url;

            m_Reference.MakeLower();
            UpdateData(FALSE);
            CheckControlState();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::OnScriptor()
{
    PSS_NewFormDialog newFormDialog(&PSS_Global::GetTemplateManager(),
                                    PSS_NewFormDialog::IE_T_SelectForm,
                                    PSS_NewFormDialog::IE_ET_Form);

    if (newFormDialog.DoModal() != IDOK)
        return;

    // check if not empty
    if (!newFormDialog.GetFormName().IsEmpty())
    {
        m_Reference = newFormDialog.GetFormName();
        UpdateData(FALSE);
        CheckControlState();
    }
}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::OnOK()
{
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::SaveValuesToObject()
{
    // get the activation type
    int curSel = m_ActivationTypeCtrl.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString text;
        m_ActivationTypeCtrl.GetLBText(curSel, text);

        m_ActivationType = PSS_Global::GetActivationType(text);
    }

    // get the insertion type
    curSel = m_InsertionTypeCtrl.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString text;
        m_InsertionTypeCtrl.GetLBText(curSel, text);

        m_InsertionType = PSS_Global::GetInsertionType(text);
    }
}
//---------------------------------------------------------------------------
void PSS_ReferenceFileDialog::CheckControlState()
{
    UpdateData();
}
//---------------------------------------------------------------------------
