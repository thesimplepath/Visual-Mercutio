// ZBPropertyItems.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPropertyItems.h"

#include "ZCInPlaceEditPropItemString.h"
#include "ZCInPlaceListBox.h"
#include "ZCInPlaceExtendedEdit.h"
#include "ZCInPlaceIntelliEdit.h"
#include "ZCInPlaceMultiLineEdit.h"
#include "ZCInPlaceSearchEdit.h"
#include "ZCInPlaceDurationEdit.h"
#include "ZCInPlaceDateEdit.h"
//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
#include "ZCInPlaceTimeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemString

IMPLEMENT_DYNAMIC( ZBPropertyItemString, ZBPropertyItem )

void ZBPropertyItemString::CreateInPlaceControl( CWnd*                pWndParent,
                                                 CRect&                rect,
                                                 ZIInPlaceEdit*&    pWndInPlaceControl,
                                                 CSize                ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );

    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceEditPropItemString();
    pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemList

IMPLEMENT_DYNAMIC( ZBPropertyItemList, ZBPropertyItem )

void ZBPropertyItemList::CreateInPlaceControl( CWnd*            pWndParent,
                                               CRect&            rect,
                                               ZIInPlaceEdit*&    pWndInPlaceControl,
                                               CSize            ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );
    
    pWndInPlaceControl = new ZCInPlaceListBox( IsReadOnly() );
    pWndInPlaceControl->InitializeInPlaceEditCtrl( this, GetData(), pWndParent, rect );

    SetItemListData( (ZCInPlaceListBox*)pWndInPlaceControl );
    ( (ZCInPlaceListBox*)pWndInPlaceControl )->SetCurSel( GetData(), false );
    ( (ZCInPlaceListBox*)pWndInPlaceControl )->ResetListBoxHeight();
}

void ZBPropertyItemList::SetData( const CString sText )
{
    m_strText = sText;
}

void ZBPropertyItemList::SetItemListData( ZCInPlaceListBox* pWndInPlaceControl )
{
    LPCTSTR pStrText;

    for( int i = 0; ( pStrText = GetItemData( i ) ) != NULL; i++ )
    {
        pWndInPlaceControl->AddString( pStrText );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemExtended

IMPLEMENT_DYNAMIC( ZBPropertyItemExtended, ZBPropertyItem )

void ZBPropertyItemExtended::CreateInPlaceControl( CWnd*            pWndParent,
                                                   CRect&            rect,
                                                   ZIInPlaceEdit*&    pWndInPlaceControl,
                                                   CSize            ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceExtendedEdit( IsReadOnly() );

    // For processing extended command
    ( (ZCInPlaceExtendedEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_EXTENDED );

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_DOUBLE:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_dValue, pWndParent, rect );
            break;
        }

        case PI_FLOAT:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_fValue, pWndParent, rect );
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemIntelliEdit

IMPLEMENT_DYNAMIC( ZBPropertyItemIntelliEdit, ZBPropertyItem )

void ZBPropertyItemIntelliEdit::CreateInPlaceControl( CWnd*                pWndParent,
                                                      CRect&            rect,
                                                      ZIInPlaceEdit*&    pWndInPlaceControl,
                                                      CSize                ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceIntelliEdit( IsReadOnly() );

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_DOUBLE:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_dValue, pWndParent, rect );
            break;
        }

        case PI_FLOAT:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_fValue, pWndParent, rect );
            break;
        }
    }

    // Initialize the control array of values
    ((ZCInPlaceIntelliEdit*)pWndInPlaceControl)->Initialize( m_data,
                                                            ( ExtendedSize.cx != 0 && ExtendedSize.cy != 0 ) ? &ExtendedSize : NULL );
}

void ZBPropertyItemIntelliEdit::SetData( const CString sText )
{
    m_strText = sText;
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemMultiLineEdit

IMPLEMENT_DYNAMIC( ZBPropertyItemMultiLineEdit, ZBPropertyItem )

void ZBPropertyItemMultiLineEdit::CreateInPlaceControl( CWnd*            pWndParent,
                                                        CRect&            rect,
                                                        ZIInPlaceEdit*&    pWndInPlaceControl,
                                                        CSize            ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );

    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceMultiLineEdit( IsReadOnly() );

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_DOUBLE:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_dValue, pWndParent, rect );
            break;
        }

        case PI_FLOAT:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_fValue, pWndParent, rect );
            break;
        }
    }

    // Initialize the control
    if ( ExtendedSize.cx != 0 && ExtendedSize.cy != 0 )
    {
        ( (ZCInPlaceMultiLineEdit*)pWndInPlaceControl )->Initialize( ExtendedSize );
    }
    else
    {
        ( (ZCInPlaceMultiLineEdit*)pWndInPlaceControl )->Initialize();
    }
}

void ZBPropertyItemMultiLineEdit::SetData( const CString sText )
{
    m_strText = sText;
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemDuration

IMPLEMENT_DYNAMIC( ZBPropertyItemDuration, ZBPropertyItem )

void ZBPropertyItemDuration::CreateInPlaceControl( CWnd*            pWndParent,
                                                   CRect&            rect,
                                                   ZIInPlaceEdit*&    pWndInPlaceControl,
                                                   CSize            ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceDurationEdit( IsReadOnly() );

    // For processing extended command
    ( (ZCInPlaceExtendedEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_EXTENDED );

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_DURATION:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_durationValue, pWndParent, rect );
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemDate

IMPLEMENT_DYNAMIC( ZBPropertyItemDate, ZBPropertyItem )

void ZBPropertyItemDate::CreateInPlaceControl( CWnd*            pWndParent,
                                               CRect&            rect,
                                               ZIInPlaceEdit*&    pWndInPlaceControl,
                                               CSize            ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );
    
    pWndInPlaceControl = new ZCInPlaceDateEdit( IsReadOnly() );

    // For processing extended command
    ( (ZCInPlaceExtendedEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_EXTENDED );

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_DATE:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_dateValue, pWndParent, rect );
            break;
        }
    }
}

// RS-MODIF 08.08.2005: ajout de la propriété d'attribut "time"
/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemTime

IMPLEMENT_DYNAMIC( ZBPropertyItemTime, ZBPropertyItem )

void ZBPropertyItemTime::CreateInPlaceControl( CWnd*            pWndParent,
                                               CRect&            rect,
                                               ZIInPlaceEdit*&    pWndInPlaceControl,
                                               CSize            ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceTimeEdit( IsReadOnly() );

    // For processing extended command
    ( (ZCInPlaceExtendedEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_EXTENDED );

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_TIME:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_timeValue, pWndParent, rect );
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemMenuFileDir

IMPLEMENT_DYNAMIC( ZBPropertyItemMenuFileDir, ZBPropertyItem )

void ZBPropertyItemMenuFileDir::CreateInPlaceControl( CWnd*                pWndParent,
                                                      CRect&            rect,
                                                      ZIInPlaceEdit*&    pWndInPlaceControl,
                                                      CSize                ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );

    pWndInPlaceControl = new ZCInPlaceSearchEdit( IsReadOnly() );

    switch( m_ControlType )
    {
        case MFD_MENU:
        {
            // Enable all menu items and no notification
            ( (ZCInPlaceSearchEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_POPUP,
                                                                         m_pMenu,
                                                                         true,
                                                                         true );

            break;
        }

        case MFD_FILE:
        {
            ( (ZCInPlaceSearchEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_FILE );
            break;
        }

        case MFD_DIRECTORY:
        {
            ( (ZCInPlaceSearchEdit*)pWndInPlaceControl )->SetSearchType( ZSEARCHEDIT_DIRECTORY );
            break;
        }
    }

    switch( m_Type )
    {
        case PI_STRING:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_strText, pWndParent, rect );
            break;
        }

        case PI_DOUBLE:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_dValue, pWndParent, rect );
            break;
        }

        case PI_FLOAT:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_fValue, pWndParent, rect );
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemNumber

IMPLEMENT_DYNAMIC( ZBPropertyItemNumber, ZBPropertyItem )

void ZBPropertyItemNumber::CreateInPlaceControl( CWnd*                pWndParent,
                                                 CRect&                rect,
                                                 ZIInPlaceEdit*&    pWndInPlaceControl,
                                                 CSize                ExtendedSize        /*= CSize(0,0)*/ )
{
    CWnd* pWnd = dynamic_cast<CWnd*>( pWndInPlaceControl );
    DestroyInPlaceControl( pWndInPlaceControl );
    
    switch( m_Type )
    {
        case PI_DOUBLE:
        {
            pWndInPlaceControl = new ZCInPlaceEditPropItemNumber( m_dValue, IsReadOnly() );
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_dValue, pWndParent, rect );
            break;
        }

        case PI_FLOAT:
        {
            pWndInPlaceControl = new ZCInPlaceEditPropItemNumber( m_fValue, IsReadOnly() );
            pWndInPlaceControl->InitializeInPlaceEditCtrl( this, m_fValue, pWndParent, rect );
            break;
        }
    }
}
