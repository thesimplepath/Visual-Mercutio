// **************************************************************************************************************
// *                                      ZVRenameModelPageInTreeDlg                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 3 avril 2006 - Ajout de la classe ZVRenameModelPageInTreeDlg.                                *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de renommer une page sélectionnée dans l'arbre à l'aide du menu        *
// * contextuel.                                                                                                *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRenameModelPageInTreeDlg.h"

#include "zBaseLib\PSS_MsgBox.h"
#include ".\zvrenamemodelpageintreedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVRenameModelPageInTreeDlg dialog

BEGIN_MESSAGE_MAP( ZVRenameModelPageInTreeDlg, ZIDialog )
    //{{AFX_MSG_MAP(ZVRenameModelPageInTreeDlg)
    //}}AFX_MSG_MAP
    ON_EN_CHANGE(IDC_PAGENAME, OnEnChangePagename)
END_MESSAGE_MAP()

ZVRenameModelPageInTreeDlg::ZVRenameModelPageInTreeDlg( CString                    ProposedName    /*= _T( "" )*/,
                                                        CStringArray*            pArrayPageName    /*= NULL*/,
                                                        CWnd*                    pParent            /*= NULL*/ )
    : ZIDialog            ( ZVRenameModelPageInTreeDlg::IDD, TRUE, pParent ),
      m_pArrayPageName    ( pArrayPageName ),
      m_PageName        ( ProposedName )
{
    //{{AFX_DATA_INIT(ZVRenameModelPageInTreeDlg)
    //}}AFX_DATA_INIT
}

void ZVRenameModelPageInTreeDlg::DoDataExchange( CDataExchange* pDX )
{
    ZIDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVRenameModelPageInTreeDlg)
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRenameModelPageInTreeDlg message handlers

BOOL ZVRenameModelPageInTreeDlg::OnInitDialog()
{
    ZIDialog::OnInitDialog();

        if ( GetDlgItem( IDC_PAGENAME ) )
    {
        GetDlgItem( IDC_PAGENAME )->SetWindowText( m_PageName );
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVRenameModelPageInTreeDlg::OnOK()
{
    // Contrôle que le nom de la page ne soit pas vide.
    if ( m_PageName.IsEmpty() )
    {
        PSS_MsgBox mBox;
        mBox.ShowMsgBox( IDS_NEWMODELPAGE_EMPTY, MB_OK );
        return;
    }

    // Contrôle si la page n'est pas déjà attribuée.
    if ( m_pArrayPageName )
    {
        for ( int i = 0; i < m_pArrayPageName->GetSize(); ++i )
        {
            if ( m_PageName == m_pArrayPageName->GetAt( i ) )
            {
                // Display error message
                PSS_MsgBox mBox;
                mBox.ShowMsgBox( IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK );
                return;
            }
        }
    }

    ZIDialog::OnOK();
}

void ZVRenameModelPageInTreeDlg::OnEnChangePagename()
{
    if ( GetDlgItem( IDC_PAGENAME ) )
    {
        GetDlgItem( IDC_PAGENAME )->GetWindowText( m_PageName );
    }
}
