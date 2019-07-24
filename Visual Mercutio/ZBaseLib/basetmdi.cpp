// BaseTMDI.cpp : implementation file
//

#include "stdafx.h"
#include "BaseTMDI.h"
#include "ZDDoc.h"

// DocData
#include "DocData.h"

#include "ZAGlobal.h"

#include <Limits.h>
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIBaseTitleMDIPage

IMPLEMENT_DYNCREATE( ZIBaseTitleMDIPage, SECMDIChildWnd )

BEGIN_MESSAGE_MAP(ZIBaseTitleMDIPage, SECMDIChildWnd)
    //{{AFX_MSG_MAP(ZIBaseTitleMDIPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIBaseTitleMDIPage::ZIBaseTitleMDIPage()
{
    m_sTemplateDef.LoadString    ( IDS_TEMPLATEDEF_TITLE );
    m_sTypeFile.LoadString        ( IDS_TEMPLATE_FILETYPE );
}

ZIBaseTitleMDIPage::~ZIBaseTitleMDIPage()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZIBaseTitleMDIPage message handlers

void ZIBaseTitleMDIPage::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
}

void ZIBaseTitleMDIPage::ActivateFrame( int nCmdShow )
{
    // if another window is open, use default
    if ( GetMDIFrame()->MDIGetActive() )
    {
        SECMDIChildWnd::ActivateFrame( nCmdShow );
    }
    else
    {
        // If the application require to create window maximized
        if ( ZAGlobal::MaximizeFormOnOpen() && ZAGlobal::IsDuringInitialization() )
            SECMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED); // else open maximized.
        else
            SECMDIChildWnd::ActivateFrame( nCmdShow );
    }
}

void ZIBaseTitleMDIPage::OnUpdateFrameTitle( BOOL bAddToTitle )
{
    SECMDIChildWnd::OnUpdateFrameTitle( FALSE );
    CDocument* pDoc = GetActiveDocument();

    if ( bAddToTitle && pDoc && ISA( pDoc, ZDDocument ) && ( (ZDDocument*)pDoc )->GetActiveDocumentData() != NULL )
    {
        char szText[10];
        szText[0] = 0x00;    // Clear the buffer

        if ( m_nWindow > 0 )
            wsprintf( szText, _T( " :%d" ), m_nWindow );

        CString        sTitle;
        CString        sNewTitle;

        if ( ( (ZDDocument*)pDoc )->GetPathName().IsEmpty() )
            sTitle = g_FormExtension;
        else
            sTitle = ( (ZDDocument*)pDoc )->GetTitle();

        if ( ( (ZDDocument*)pDoc )->DocumentIsTemplate() )
        {
            sNewTitle = m_sTypeFile +
                        sTitle +
                        _T( " [" ) +
                        ( (ZDDocument*)pDoc )->GetDocumentStamp().GetTitle() +
                        _T( " : " ) +
                        ( (ZDDocument*)pDoc )->GetActiveDocumentData()->GetStamp().GetTitle() +
                        _T( "]" ) +
                        szText;
        }
        else
        {
            if ( ( (ZDDocument*)pDoc )->GetDocumentStamp().GetFolderName().IsEmpty() )
            {
                sNewTitle = sTitle +
                            _T( " [" ) +
                            m_sTemplateDef +
                            ( (ZDDocument*)pDoc )->GetDocumentStamp().GetTitle() +
                            _T( " : " ) +
                            ( (ZDDocument*)pDoc )->GetActiveDocumentData()->GetStamp().GetTitle() +
                            _T( "]" ) +
                            szText;
            }
            else
            {
                sNewTitle = ( (ZDDocument*)pDoc )->GetDocumentStamp().GetFolderName() +
                            _T( " [" ) +
                            m_sTemplateDef +
                            ( (ZDDocument*)pDoc )->GetDocumentStamp().GetTitle() +
                            _T( " : " ) +
                            ( (ZDDocument*)pDoc )->GetActiveDocumentData()->GetStamp().GetTitle() +
                            _T( "]" ) +
                            szText;
            }
        }

        if ( sTitle != sNewTitle )
            SetWindowText( sNewTitle );
    }
}
