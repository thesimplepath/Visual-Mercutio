// ZVReferenceFileDlg.cpp : implementation file

#include "stdafx.h"
#include "ZVReferenceFileDlg.h"

// processsoft
#include "zBaseLib\FileDlg.h"
#include "zBaseLib\ZAGlobal.h"
#include "PSS_NewFormDialog.h"
#include "ZVInputURLDialog.h"
#include "ZVReferenceFileDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 12 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

BEGIN_MESSAGE_MAP( ZVReferenceFileDlg, CDialog )
    //{{AFX_MSG_MAP(ZVReferenceFileDlg)
    ON_BN_CLICKED(IDC_ADDFILE, OnAddfile)
    ON_BN_CLICKED(IDC_ADDURL, OnAddurl)
    ON_BN_CLICKED(IDC_SCRIPTOR, OnScriptor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVReferenceFileDlg dialog

ZVReferenceFileDlg::ZVReferenceFileDlg(    const CString    Reference        /*= _T( "" )*/,
                                        int                InsertionType    /*= 0*/,
                                        int                ActivationType    /*= 0*/,
                                        CWnd*            pParent            /*= NULL*/ )
    : CDialog( ZVReferenceFileDlg::IDD, pParent )
{
    //{{AFX_DATA_INIT(ZVReferenceFileDlg)
    m_Reference = Reference;
    //}}AFX_DATA_INIT

    m_InsertionType = InsertionType;
    m_ActivationType = ActivationType;
}

void ZVReferenceFileDlg::CheckControlState()
{
    UpdateData();

    if ( m_Reference.Find( _T( "file://" ) ) != -1 )
    {
    }
    else if ( m_Reference.Find( _T( "http://" ) ) != -1 )
    {
    }
    else
    {
    }
}

void ZVReferenceFileDlg::SaveValuesToObject()
{
    // Retreive the activation type
    int CurSel = m_ActivationTypeCtrl.GetCurSel();

    if ( CurSel != LB_ERR )
    {
        CString Text;
        m_ActivationTypeCtrl.GetLBText( CurSel, Text );

        m_ActivationType = ZAGlobal::GetActivationType( Text );
    }

    // Retreive the insertion type
    CurSel = m_InsertionTypeCtrl.GetCurSel();

    if ( CurSel != LB_ERR )
    {
        CString Text;
        m_InsertionTypeCtrl.GetLBText( CurSel, Text );

        m_InsertionType = ZAGlobal::GetInsertionType( Text );
    }
}

void ZVReferenceFileDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVReferenceFileDlg)
    DDX_Control(pDX, IDC_ACTIVATIONTYPE, m_ActivationTypeCtrl);
    DDX_Control(pDX, IDC_INSERTIONTYPE, m_InsertionTypeCtrl);
    DDX_Text(pDX, IDC_REFERENCE_FILE, m_Reference);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL ZVReferenceFileDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // fill the activation type list box
    std::size_t count = (ZAGlobal::GetArrayActivationType()) ? ZAGlobal::GetArrayActivationType()->GetSize() : 0;

    for (std::size_t i = 0; i < count; ++i)
        m_ActivationTypeCtrl.AddString(ZAGlobal::GetArrayActivationType()->GetAt(i));

    // fill the insertion type list box
    count = (ZAGlobal::GetArrayInsertionType()) ? ZAGlobal::GetArrayInsertionType()->GetSize() : 0;

    for (std::size_t i = 0; i < count; ++i)
        m_InsertionTypeCtrl.AddString(ZAGlobal::GetArrayInsertionType()->GetAt(i));

    // set the right activation type
    m_ActivationTypeCtrl.SelectString(-1, ZAGlobal::GetActivationTypeString(m_ActivationType));

    // set the right insertion type
    m_InsertionTypeCtrl.SelectString(-1, ZAGlobal::GetInsertionTypeString(m_InsertionType));

    CheckControlState();

    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void ZVReferenceFileDlg::OnAddfile()
{
    // Set the "*.*" files filter
    CString strFilter;
    VERIFY( strFilter.LoadString( AFX_IDS_ALLFILTER ) );
    strFilter += (char)'\0';    // Next string please
    strFilter += _T( "*.*" );
    strFilter += (char)'\0';    // Last string

    ZIFileDialog FileDialog( IDS_SELECT_A_FILE, strFilter, 1 );

    if ( FileDialog.DoModal() == IDOK )
    {
        CString File = FileDialog.GetFilename();

        // Check if not empty
        if ( !File.IsEmpty() )
        {
            if ( File.Find( _T( "file://" ) ) == -1 )
            {
                m_Reference = _T( "file://" ) + File;
            }
            else
            {
                m_Reference = File;
            }

            m_Reference.MakeLower();
            UpdateData( FALSE );
            CheckControlState();
        }
    }
}

void ZVReferenceFileDlg::OnAddurl()
{
    ZVInputURLDialog InputURLDialog;

    if ( InputURLDialog.DoModal() == IDOK )
    {
        CString URL = InputURLDialog.GetURL();

        // Check if not empty
        if ( !URL.IsEmpty() )
        {
            if ( URL.Find( _T( "http://" ) ) == -1 && URL.Find( _T( "ftp://" ) ) == -1 )
            {
                m_Reference = _T( "http://" ) + URL;
            }
            else
            {
                m_Reference = URL;
            }

            m_Reference.MakeLower();
            UpdateData( FALSE );
            CheckControlState();
        }
    }
}

void ZVReferenceFileDlg::OnScriptor()
{
    PSS_NewFormDialog newFormDialog(&ZAGlobal::GetTemplateManager(),
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

void ZVReferenceFileDlg::OnOK()
{
    CDialog::OnOK();
}
