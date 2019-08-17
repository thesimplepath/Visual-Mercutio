// ZVLogicalSystemInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVLogicalSystemInfoDlg.h"

#include "ZBLogicalSystemEntity.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystemInfoDlg dialog

BEGIN_MESSAGE_MAP( ZVLogicalSystemInfoDlg, CDialog )
    //{{AFX_MSG_MAP(ZVLogicalSystemInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVLogicalSystemInfoDlg::ZVLogicalSystemInfoDlg( UINT                    nTitleID        /*= -1*/,
                                                ZBLogicalSystemEntity*    pLogicalSystem    /*= NULL*/,
                                                const CString            Name            /*= _T( "" )*/,
                                                const CString            Description        /*= _T( "" )*/,
                                                bool                    ModifyMode        /*= false*/,
                                                CWnd*                    pParent            /*=NULL*/ )
    : CDialog            ( ZVLogicalSystemInfoDlg::IDD, pParent ),
      m_pLogicalSystem    ( pLogicalSystem ),
      m_ModifyMode        ( ModifyMode )
{
    //{{AFX_DATA_INIT(ZVLogicalSystemInfoDlg)
    m_Description = Description;
    m_Name = Name;
    //}}AFX_DATA_INIT

    // Assigns also the initial cost
    if ( nTitleID != -1 )
        m_Title.LoadString( nTitleID );
}

void ZVLogicalSystemInfoDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVLogicalSystemInfoDlg)
    DDX_Text(pDX, IDC_LOGICALSYSTEM_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_LOGICALSYSTEM_NAME, m_Name);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystemInfoDlg message handlers

void ZVLogicalSystemInfoDlg::OnOK() 
{
    UpdateData( TRUE );

    if ( !m_ModifyMode )
    {
        if ( m_pLogicalSystem && m_pLogicalSystem->SystemExist( m_Name ) )
        {
            // Already exists
            PSS_MsgBox mBox;
            mBox.ShowMsgBox( IDS_LOGICALSYSTEM_ALREADYEXIST, MB_OK );
            return;
        }
    }

    CDialog::OnOK();
}

BOOL ZVLogicalSystemInfoDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    if ( !m_Title.IsEmpty() )
        SetWindowText( m_Title );

    if ( m_ModifyMode )
    {
        if ( GetDlgItem( IDC_LOGICALSYSTEM_NAME ) )
            GetDlgItem( IDC_LOGICALSYSTEM_NAME )->EnableWindow( FALSE );
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
