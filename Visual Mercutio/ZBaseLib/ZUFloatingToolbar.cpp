// ZUFloatingToolbar.cpp: implementation of the ZUFloatingToolbar class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUFloatingToolbar.h"
#include "basefrm.h"

// ZConfigW
#include "ZConfigW.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

//////////////////////////////////////////////////////////////////////
// Static internal variable initialization
ZBToolbarSet                ZUFloatingToolbar::m_ToolbarSet;
ZBMenubarSet                ZUFloatingToolbar::m_MenubarSet;
ZAWindowConfiguration*        ZUFloatingToolbar::m_pWndConf            = NULL;
SECToolBarManager*            ZUFloatingToolbar::m_pToolBarManager    = NULL;
SECMenuBar*                    ZUFloatingToolbar::m_pMenuBarManager    = NULL;
EModelNotation                ZUFloatingToolbar::m_CurrentNotation    = E_MN_Unknown;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUFloatingToolbar::ZUFloatingToolbar()
{
}

ZUFloatingToolbar::~ZUFloatingToolbar()
{
}

void ZUFloatingToolbar::Initialize( ZAWindowConfiguration*    pWndConf,
                                    SECToolBarManager*        pToolBarManager,
                                    SECMenuBar*                pMenuBarManager)
{
    m_pWndConf            = pWndConf;
    m_pToolBarManager    = pToolBarManager;
    m_pMenuBarManager    = pMenuBarManager;
}

// JMR-MODIF - Le 31 août 2005 - Ajout de la fonction Release, pour permettre le nettoyage des ressources utilisées.
void ZUFloatingToolbar::Release()
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pTbData;

    for ( pTbData = i.GetFirst(); pTbData != NULL; pTbData = i.GetNext() )
    {
        delete pTbData;
    }

    m_ToolbarSet.RemoveAll();

    ZBMenubarIterator j( &m_MenubarSet );
    _MenubarData* pMbData;

    for ( pMbData = j.GetFirst(); pMbData != NULL; pMbData = j.GetNext() )
    {
        delete pMbData;
    }

    m_MenubarSet.RemoveAll();
}

bool ZUFloatingToolbar::RegisterToolbar( CString Name, UINT nIDToolBar, CFrameWnd* pFrame, EModelNotation Notation )
{
    // Check existence of toolbar
    if ( ToolbarExist( nIDToolBar ) )
    {
        return true;
    }

    int ActSize = m_ToolbarSet.GetSize();

    m_ToolbarSet.Add( new _ToolbarData( Name, nIDToolBar, pFrame, Notation ) );

    return ( m_ToolbarSet.GetSize() > ActSize ) ? true : false;
}

bool ZUFloatingToolbar::UnRegisterToolbar( UINT nIDToolBar )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_nIDToolBar == nIDToolBar )
        {
            SECCustomToolBar* pTb = NULL;

            if ( m_pToolBarManager )
            {
                pTb = m_pToolBarManager->ToolBarFromID( nIDToolBar );
            }

            // If toolbar found, hide the control bar
            if ( pTb )
            {
                pData->m_pFrame->ShowControlBar( pTb, FALSE, FALSE );
            }

            // Then remove the control bar from the set
            i.Remove();

            // Then delete the data pointer
            delete pData;
            return true;
        }
    }

    // Not found
    return false;
}

bool ZUFloatingToolbar::RegisterToolbar( CString Name, CControlBar* pBar, CFrameWnd* pFrame, EModelNotation Notation )
{
    // Check existence of toolbar
    if ( ToolbarExist( Name ) )
    {
        return true;
    }

    int ActSize = m_ToolbarSet.GetSize();

    m_ToolbarSet.Add( new _ToolbarData( Name, pBar, pFrame, Notation ) );

    return ( m_ToolbarSet.GetSize() > ActSize ) ? true : false;
}

bool ZUFloatingToolbar::UnRegisterToolbar( CControlBar* pBar )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pBar == pBar )
        {
            // First, hide the control bar
            pData->m_pFrame->ShowControlBar( pData->m_pBar, FALSE, FALSE );

            // Then remove the control bar from the set
            i.Remove();

            // Then delete the data pointer
            delete pData;
            return true;
        }
    }

    // Not found
    return false;
}

bool ZUFloatingToolbar::RegisterMenubar( CString Name, CMenu* pMenu, CFrameWnd* pFrame, EModelNotation Notation )
{
    // Check existence of toolbar
    if ( MenubarExist( Name ) )
    {
        return true;
    }

    int ActSize = m_MenubarSet.GetSize();

    m_MenubarSet.Add( new _MenubarData( Name, pMenu, pFrame, Notation ) );

    return ( m_MenubarSet.GetSize() > ActSize ) ? true : false;
}

bool ZUFloatingToolbar::UnRegisterMenubar( CMenu* pMenu )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pMenu == pMenu )
        {
            // First, hide the menu bar
            // Then remove the menu bar from the set
            i.Remove();

            // Then delete the data pointer
            delete pData;
            return true;
        }
    }

    // Not found
    return false;
}

bool ZUFloatingToolbar::RegisterMenubar( CString Name, UINT nIDRes, CFrameWnd* pFrame, EModelNotation Notation )
{
    // Check existence of toolbar
    if ( MenubarExist( Name ) )
    {
        return true;
    }

    int ActSize = m_MenubarSet.GetSize();

    if ( pFrame && ISA( pFrame, ZIBaseMainFrame ) )
    {
        // Used to load additional menu
        dynamic_cast<ZIBaseMainFrame*>( pFrame )->LoadAdditionalMenus( 1, nIDRes );
    }

    // Add the menu to the internal array
    m_MenubarSet.Add( new _MenubarData( Name, nIDRes, pFrame, Notation ) );

    return ( m_MenubarSet.GetSize() > ActSize ) ? true : false;
}

bool ZUFloatingToolbar::RegisterAndLoadMenubar( CString Name, UINT nIDRes, CFrameWnd* pFrame, EModelNotation Notation )
{
    if ( pFrame && ISA( pFrame, ZIBaseMainFrame ) )
    {
        dynamic_cast<ZIBaseMainFrame*>( pFrame )->LoadMenuBar( nIDRes );
        return ZUFloatingToolbar::RegisterMenubar( Name, nIDRes, pFrame, Notation );
    }

    return false;
}

bool ZUFloatingToolbar::UnRegisterMenubar( UINT nIDRes )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_nIDRes == nIDRes )
        {
            // First, hide the menu bar
            // Then remove the menu bar from the set
            i.Remove();

            // Then delete the data pointer
            delete pData;
            return true;
        }
    }

    // Not found
    return false;
}

bool ZUFloatingToolbar::SwitchContext( EModelNotation Notation )
{
    // If we already are in the current notation,
    // do nothing
    if ( m_CurrentNotation != Notation )
    {
        // First, hide all toolbars from the current notation
        if ( !HideToolbars( m_CurrentNotation ) )
        {
            return false;
        }

        // First, hide all menu bars from the current notation
        if ( !HideMenubars( m_CurrentNotation ) )
        {
            return false;
        }

        // Then show all toolbars of the new notation
        if ( !ShowToolbars( Notation ) )
        {
            return false;
        }
    }

    // Then show all menu bars of the new notation
    if ( !ShowMenubars( Notation ) )
    {
        return false;
    }

    // Keeps the current notation
    m_CurrentNotation = Notation;
    return true;
}

bool ZUFloatingToolbar::ToolbarExist( CString Name )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_Name == Name )
        {
            return true;
        }
    }

    return false;
}

bool ZUFloatingToolbar::ToolbarExist( UINT nIDToolBar )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_nIDToolBar == nIDToolBar )
        {
            return true;
        }
    }

    return false;
}

bool ZUFloatingToolbar::ToolbarExist( CControlBar* pBar )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pBar == pBar )
        {
            return true;
        }
    }

    return false;
}

bool ZUFloatingToolbar::MenubarExist( CString Name )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_Name == Name )
        {
            return true;
        }
    }

    return false;
}

bool ZUFloatingToolbar::MenubarExist( UINT nIDRes )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_nIDRes == nIDRes )
        {
            return true;
        }
    }

    return false;
}

bool ZUFloatingToolbar::MenubarExist( CMenu* pMenu )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pMenu == pMenu )
        {
            return true;
        }
    }

    return false;
}

bool ZUFloatingToolbar::HideToolbars( EModelNotation Notation )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_Notation == Notation )
        {
            if ( pData->m_pBar )
            {
                // hide the control bar
                pData->m_pFrame->ShowControlBar( pData->m_pBar, FALSE, TRUE );
            }
            else
            {
                SECCustomToolBar* pTb = NULL;

                if ( m_pToolBarManager )
                {
                    pTb = m_pToolBarManager->ToolBarFromID( pData->m_nIDToolBar );
                }

                // If toolbar found, hide the control bar
                if ( pTb )
                {
                    pData->m_pFrame->ShowControlBar( pTb, FALSE, FALSE );
                }
            }
        }
    }

    return true;
}

bool ZUFloatingToolbar::ShowToolbars( EModelNotation Notation )
{
    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_Notation == Notation )
        {
            if ( pData->m_pBar )
            {
                // Show the control bar
                pData->m_pFrame->ShowControlBar( pData->m_pBar, TRUE, TRUE );
            }
            else
            {
                SECCustomToolBar* pTb = NULL;

                if ( m_pToolBarManager )
                {
                    pTb = m_pToolBarManager->ToolBarFromID( pData->m_nIDToolBar );
                }

                // If toolbar found, hide the control bar
                if ( pTb )
                {
                    pData->m_pFrame->ShowControlBar( pTb, TRUE, TRUE );
                }
            }
        }
    }

    return true;
}

bool ZUFloatingToolbar::HideMenubars( EModelNotation Notation )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_Notation == Notation )
        {
            if ( pData->m_nIDRes == -1 )
            {
                // First, hide the control bar
                pData->m_pFrame->Invalidate();
                pData->m_pFrame->SetMenu( NULL );
                pData->m_pFrame->RecalcLayout();    // Position and size everything
                pData->m_pFrame->UpdateWindow();
            }
        }
    }

    return true;
}

bool ZUFloatingToolbar::ShowMenubars(EModelNotation Notation )
{
    ZBMenubarIterator i( &m_MenubarSet );
    _MenubarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_Notation == Notation )
        {
            if ( pData->m_nIDRes == -1 )
            {
                pData->m_pFrame->Invalidate();
                pData->m_pFrame->SetMenu( pData->m_pMenu );
                pData->m_pFrame->DrawMenuBar();
                pData->m_pFrame->RecalcLayout();    // Position and size everything
                pData->m_pFrame->UpdateWindow();
            }
            else
            {
                ASSERT( pData->m_pFrame != NULL );
                ASSERT_KINDOF( SECMDIFrameWnd, pData->m_pFrame );
                SECMDIFrameWnd* pMainWnd = (SECMDIFrameWnd*)pData->m_pFrame;

                // Update the menubar, if any
                pMainWnd->ActivateMenu( pData->m_nIDRes );
            }
        }
    }

    return true;
}

void ZUFloatingToolbar::ReloadBarState()
{
    if ( !m_pWndConf )
    {
        return;
    }

    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pBar )
        {
            m_pWndConf->RestoreWindowPosition( pData->m_pBar, pData->m_Name, TRUE );
        }
    }
}

void ZUFloatingToolbar::ReloadBarState( const CString Name )
{
    if ( !m_pWndConf )
    {
        return;
    }

    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pBar && pData->m_Name == Name )
        {
            m_pWndConf->RestoreWindowPosition( pData->m_pBar, pData->m_Name, TRUE );
        }
    }
}

void ZUFloatingToolbar::SaveBarState()
{
    if ( !m_pWndConf )
    {
        return;
    }

    ZBToolbarIterator i( &m_ToolbarSet );
    _ToolbarData* pData;

    for ( pData = i.GetFirst(); pData != NULL; pData = i.GetNext() )
    {
        if ( pData->m_pBar )
        {
            m_pWndConf->SaveWindowPosition( pData->m_pBar, pData->m_Name, TRUE );
        }
    }
}
