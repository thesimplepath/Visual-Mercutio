// ZVReferenceFileDlg.cpp : implementation file

#include "stdafx.h"
#include "ZVReferenceFileDlg.h"

#include "NewForm.h"
#include "zBaseLib\FileDlg.h"
#include "ZVInputURLDialog.h"

#include "zBaseLib\ZAGlobal.h"
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

/////////////////////////////////////////////////////////////////////////////
// ZVReferenceFileDlg message handlers

BOOL ZVReferenceFileDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Fill the activation type list box
    size_t Count = ( ZAGlobal::GetArrayActivationType() ) ? ZAGlobal::GetArrayActivationType()->GetSize() : 0;

    for ( size_t i = 0; i < Count; ++i )
    {
        m_ActivationTypeCtrl.AddString( ZAGlobal::GetArrayActivationType()->GetAt( i ) );
    }

    // Fill the insertion type list box
    Count = ( ZAGlobal::GetArrayInsertionType() ) ? ZAGlobal::GetArrayInsertionType()->GetSize() : 0;

    for ( i = 0; i < Count; ++i )
    {
        m_InsertionTypeCtrl.AddString( ZAGlobal::GetArrayInsertionType()->GetAt( i ) );
    }

    // Sets the right activation type
    m_ActivationTypeCtrl.SelectString( -1, ZAGlobal::GetActivationTypeString( m_ActivationType ) );

    // Sets the right insertion type
    m_InsertionTypeCtrl.SelectString( -1, ZAGlobal::GetInsertionTypeString( m_InsertionType ) );

    CheckControlState();

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

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
    ZINewForm NewForm( &ZAGlobal::GetTemplateManager(), SelectForm, FormType );

    if ( NewForm.DoModal() != IDOK )
    {
        return;
    }

    // Check if not empty
    if ( !NewForm.GetFormName().IsEmpty() )
    {
        m_Reference = NewForm.GetFormName();
        UpdateData( FALSE );
        CheckControlState();
    }
}

void ZVReferenceFileDlg::OnOK()
{
    CDialog::OnOK();
}
