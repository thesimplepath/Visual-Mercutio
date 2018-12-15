// ZBPropertyItem.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPropertyItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItem

IMPLEMENT_DYNAMIC( ZBPropertyItem, CObject )

bool ZBPropertyItem::SetEnabled( bool bEnable )
{
    bool bChanged    = m_bEnabled != bEnable;
    m_bEnabled        = bEnable;

    return bChanged;
}

void ZBPropertyItem::CreateInPlaceControl( CWnd*            /*pWndParent*/,
                                           CRect&            /*rect*/,
                                           ZIInPlaceEdit*&    pWndInPlaceControl,
                                           CSize            ExtendedSize        /*= CSize()*/)
{
    DestroyInPlaceControl( pWndInPlaceControl );
}

void ZBPropertyItem::DestroyInPlaceControl( ZIInPlaceEdit*& pWndInPlaceControl )
{
    if ( pWndInPlaceControl != NULL )
    {
        // Check if the value has changed, 
        // then request the control to save its value
        if ( pWndInPlaceControl->GetHasChanged() )
        {
            pWndInPlaceControl->SaveValue();
        }

        delete pWndInPlaceControl;
        pWndInPlaceControl = NULL;
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemCategory

IMPLEMENT_DYNAMIC( ZBPropertyItemCategory, ZBPropertyItem )

void ZBPropertyItemCategory::RemoveAllPropertyItems()
{
    // Run through all items
    ZBPropertyItemIterator i( &m_PropertyItemSet );

    for ( ZBPropertyItem* pItem = i.GetFirst(); pItem; pItem = i.GetNext() )
    {
        // If enable, increment the counter
        delete pItem;
    }

    // Then remove all elements
    m_PropertyItemSet.RemoveAll();
}

int ZBPropertyItemCategory::GetNumberEnabledItems() const
{
    int nNumberEnabledItems = 0;

    // Run through all items
    ZBPropertyItemIterator i( &m_PropertyItemSet );

    for ( ZBPropertyItem* pItem = i.GetFirst(); pItem; pItem = i.GetNext() )
    {
        // If enable, increment the counter
        if ( pItem->GetEnabled() )
        {
            nNumberEnabledItems++;
        }
    }

    return nNumberEnabledItems;
}

ZBPropertyItem* ZBPropertyItemCategory::GetPropertyItem( LPCTSTR pStrItemName )
{
    // Run through all items
    ZBPropertyItemIterator i( &m_PropertyItemSet );

    for ( ZBPropertyItem* pItem = i.GetFirst(); pItem; pItem = i.GetNext() )
    {
        // If the same name
        if ( pItem->GetName() == pStrItemName )
        {
            return pItem;
        }
    }

    return NULL;
}

ZBPropertyItem* ZBPropertyItemCategory::GetPropertyItem( int nPropertyID )
{
    // Run through all items
    ZBPropertyItemIterator i( &m_PropertyItemSet );

    for ( ZBPropertyItem* pItem = i.GetFirst(); pItem; pItem = i.GetNext() )
    {
        // If the same ID
        if ( pItem->GetPropertyID() == nPropertyID )
        {
            return pItem;
        }
    }

    return NULL;
}

bool ZBPropertyItemCategory::PropertyItemExist( ZBPropertyItem* pPropertyItem )
{
    // Run through all items
    ZBPropertyItemIterator i( &m_PropertyItemSet );

    for ( ZBPropertyItem* pItem = i.GetFirst(); pItem; pItem = i.GetNext() )
    {
        // If the same pointer
        if ( pItem == pPropertyItem )
        {
            return true;
        }
    }

    return false;
}
