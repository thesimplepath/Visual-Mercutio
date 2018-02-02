// ZZCPropertyListCtrl.cpp : implementation file

#include "stdafx.h"
#include "ZCPropertyListCtrl.h"
#include "ZBPropertyManager.h"

#include "zProperty\ZBPropertyItem.h"

// Observer message classes
#include "zProperty\ZBPropertyObserverMsg.h"
#include "zProperty\ZBPropertyItemObserverMsg.h"
#include "zBaseLib\ZBToolbarObserverMsg.h"
#include "zBaseLib\ZBKeyboardObserverMsg.h"

#include "zPtyMgrRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// JMR-MODIF - Le 23 février 2006 - Changement de la couleur par défaut des propriétés ReadOnly.
#define			COLOR_READONLY	RGB( 128, 128, 128 )

//////////////////////////////////////////////////////////////////////
// Constant definition
static bool		gInMoveSplitterMode	= false;
static int		gMaxLeft			= 0;
static int		gMaxRight			= 0;

static CRect 	gInitialRect	( 0, 0, 0, 0 );
static CPoint 	gInitialPoint	( 0, 0 );
static CPoint 	gLastPoint		( 0, 0 );

#define PROPERTY_LEFT_BORDER	16

IMPLEMENT_DYNAMIC( ZCPropertyListCtrl, CDragListBox )

BEGIN_MESSAGE_MAP( ZCPropertyListCtrl, CDragListBox )
	//{{AFX_MSG_MAP(ZCPropertyListCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelChange)
	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_KEYPRESSED_EDIT, OnKeyPressed)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListCtrl

ZCPropertyListCtrl::ZCPropertyListCtrl( LPCTSTR pIniFile /*= NULL*/ )
	: m_pPropertyItemManager		( NULL ),
	  m_pWndInPlaceControl			( NULL ),
	  m_nSelectedItem				( -1 ),
	  m_pCurrentProperties			( NULL ),
	  m_IniFile						( _T( "" ) ),
	  m_IniFileLoaded				( false ),
	  m_SplitterX					( 100 ),
	  m_pSrcDragPropertyItem		( NULL ),
	  m_SrcDragPropertyItemIndex	( -1 ),
	  m_ListInReadOnly				( false )
{
	m_pPropertyItemManager = new ZBPropertyItemManager;

	// If an ini file pointer is defined
	if ( pIniFile )
	{
		m_IniFile = pIniFile;
		m_pPropertyItemManager->LoadStateFromIniFile( m_IniFile );
		m_IniFileLoaded = true;
	}

	HINSTANCE hInstResource;

	hInstResource = AfxFindResourceHandle( MAKEINTRESOURCE( IDC_SPLITTER_H ),
										   RT_GROUP_CURSOR );

	// Load icon resource
	m_hcurSplitter = (HCURSOR)::LoadImage( hInstResource, MAKEINTRESOURCE( IDC_SPLITTER_H ), IMAGE_CURSOR, 0, 0, 0 );	
}

ZCPropertyListCtrl::~ZCPropertyListCtrl()
{
	// Before destroying this class, saves information to the inifile
	// if there is one defined
	if ( !m_IniFile.IsEmpty() )
	{
		m_pPropertyItemManager->SaveStateToIniFile( m_IniFile );
	}

	if ( m_pPropertyItemManager )
	{
		delete m_pPropertyItemManager;
		m_pPropertyItemManager = NULL;
	}

	if ( m_pWndInPlaceControl )
	{
		delete m_pWndInPlaceControl;
		m_pWndInPlaceControl = NULL;
	}

	// Destroy the cursor (if any)
	if ( m_hcurSplitter != NULL )
	{
		::DestroyCursor( m_hcurSplitter );
	}
}

void ZCPropertyListCtrl::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
	if ( pMsg && ISA( pMsg, ZBPropertyObserverMsg ) )
	{

		if ( ( (ZBPropertyObserverMsg*)pMsg )->GetpProperties() && m_pPropertyItemManager )
		{
			Initialize( ( (ZBPropertyObserverMsg*)pMsg )->GetpProperties() );
		}
		else
		{
			Empty();
		}
	}
	else if ( pMsg && ISA( pMsg, ZBKeyboardObserverMsg ) )
	{
		if ( dynamic_cast<ZBKeyboardObserverMsg*>( pMsg )->GetMessageID() == WM_KEYPRESSED_EDIT )
		{
			switch( dynamic_cast<ZBKeyboardObserverMsg*>( pMsg )->GetKey() )
			{
				case VK_ESCAPE:
				{
					// Remove the focus by setting the focus to the list control
					SetFocus();
					return;
				}

				case VK_RETURN:
				case VK_TAB:
				{
					// Edit next item
					EditNextItem();
					return;
				}

				case ( VK_SHIFT|VK_TAB ):
				{
					// Edit previous item
					EditPreviousItem();
					return;
				}

				default:
				{
					break;
				}
			}
		}
	}
	else if ( pMsg && ISA( pMsg, ZBToolbarObserverMsg ) )
	{
		switch( dynamic_cast<ZBToolbarObserverMsg*>( pMsg )->GetMessageID() )
		{
			case WM_VALUESAVED_EDIT:
			{
				// Remove the focus by setting the focus to the list control
				SetCurrentData();
				break;
			}

			case WM_SETFOCUS_EDIT:
			{
				break;
			}

			case WM_KILLFOCUS_EDIT:
			{
				// Remove the focus by setting the focus to the list control
				SetFocus();
				break;
			}

			default:
			{
				break;
			}
		}
	}
}

void ZCPropertyListCtrl::LoadStateFromIniFile( const CString IniFile )
{
	// If an ini file is not empty
	if ( !IniFile.IsEmpty() )
	{
		if ( m_IniFile != IniFile )
		{
			m_IniFile = IniFile;
			m_pPropertyItemManager->LoadStateFromIniFile( m_IniFile );
			m_IniFileLoaded = true;
		}
	}
}

void ZCPropertyListCtrl::Initialize( ZIProperties* pProperties /*= NULL*/, LPCTSTR pIniFile /*= NULL*/ )
{
	// Check if the value has changed, 
	// then request the control to save its value
	if ( m_pWndInPlaceControl && m_pWndInPlaceControl->GetHasChanged() )
	{
		m_pWndInPlaceControl->SaveValue();
	}

	if ( pProperties )
	{
		m_pCurrentProperties = pProperties;
	}

	// First, updates the properties. 
	// If there is no properties, then nothing is done
	m_pPropertyItemManager->UpdatePropertyData();

	// Then fill the property set with properties
	m_pPropertyItemManager->UpdateControlData( m_pCurrentProperties );

	if ( m_pPropertyItemManager )
	{
		m_pPropertyItemManager->SetPropertyListCtrl( this );
	}

	// If an ini file pointer is defined
	if ( pIniFile )
	{
		if ( m_IniFile != pIniFile )
		{
			m_IniFile = pIniFile;
			m_pPropertyItemManager->LoadStateFromIniFile( m_IniFile );
			m_IniFileLoaded = true;
		}
	}

	Refresh();
}

void ZCPropertyListCtrl::Initialize( ZBPropertySet& PropSet, LPCTSTR pIniFile /*= NULL*/ )
{
	// Check if the value has changed, 
	// then request the control to save its value
	if ( m_pWndInPlaceControl && m_pWndInPlaceControl->GetHasChanged() )
	{
		m_pWndInPlaceControl->SaveValue();
	}

	// First, updates the properties. 
	// If there is no properties, then nothing is done
	m_pPropertyItemManager->UpdatePropertyData();

	// Then fill the property set with properties
	m_pPropertyItemManager->UpdateControlData( PropSet );

	if ( m_pPropertyItemManager )
	{
		m_pPropertyItemManager->SetPropertyListCtrl( this );
	}

	// If an ini file pointer is defined
	if ( pIniFile )
	{
		if ( m_IniFile != pIniFile )
		{
			m_IniFile = pIniFile;
			m_pPropertyItemManager->LoadStateFromIniFile( m_IniFile );
			m_IniFileLoaded = true;
		}
	}

	Refresh();
}

void ZCPropertyListCtrl::Refresh( bool DeleteEditCtrl /*= true*/, bool ReloadControlData /*= false*/ )
{
	// JMR-MODIF - Le 9 juin 2005 - Sauvegarde la valeur de l'emplacement de l'affichage avant le
	// rafraîchissement.
	int iIndex					= GetTopIndex();
	int nPreviousSelectedItem	= -1;

	// Save the selected item
	if ( !DeleteEditCtrl )
	{
		nPreviousSelectedItem	= m_nSelectedItem;
	}

	// Reset the content
	ResetContent( DeleteEditCtrl );

	if ( ReloadControlData )
	{
		// Then fill the property set with properties
		m_pPropertyItemManager->UpdateControlData( m_pCurrentProperties );
	}

	int nItem = 0;

	// Run through all items
	ZBItemCategoryIterator i( &m_pPropertyItemManager->GetItemCategorySet() );

	// RS-MODIF 08.08.2005: correction affichage attribut dynamique temps
	//for ( ZBPropertyItemCategory* pPropertyItemTab = i.GetFirst(); pPropertyItemTab; pPropertyItemTab = i.GetNext() )

	ZBPropertyItemCategory* pPropertyItemTab;

	for ( pPropertyItemTab = i.GetFirst(); pPropertyItemTab; pPropertyItemTab = i.GetNext() )
	{
		if ( pPropertyItemTab->GetEnabled() )
		{
			InsertPropertyItem( pPropertyItemTab, nItem );

			// Do the expand only if children are visible
			if ( pPropertyItemTab->GetChildrenVisible() )
			{
				DoExpand( pPropertyItemTab, nItem );
			}

			nItem++;
		}
	}

	// If necessary to redisplay the edit control
	if ( !DeleteEditCtrl )
	{
		m_nSelectedItem = nPreviousSelectedItem;

		// Sets the current selection
		SetCurSel( nPreviousSelectedItem );
	}

	// Redraw the complete list control
	RedrawAll();

	// JMR-MODIF - Le 9 juin 2005 - Replace la position courante de l'affichage à l'emplacement choisi par
	// l'utilisateur.
	if ( iIndex <= GetCount() && iIndex > GetTopIndex() )
	{
		SetTopIndex( iIndex );
	}
}

void ZCPropertyListCtrl::Empty()
{
	// First, updates the properties. 
	// If there is no properties, then nothing is done
	m_pPropertyItemManager->UpdatePropertyData();

	// Reset the content
	ResetContent( true );

	// And finally empty the property manager
	m_pPropertyItemManager->Empty();
}

void ZCPropertyListCtrl::EditNextItem()
{
	int nCount = GetCount();

	if ( nCount > 0 )
	{
		int nPreviousItem = GetCurSel();
		int nItem;

		if ( nPreviousItem >= ( nCount - 1 ) )
		{
			nItem = 0;
		}
		else
		{
			nItem = nPreviousItem + 1;
		}

		// Edit the item
		CreateInPlaceControl( nItem, nPreviousItem );

		// Move the current selection
		SetCurSel( nItem );
	}
}

void ZCPropertyListCtrl::EditPreviousItem()
{
	int nCount = GetCount();

	if ( nCount > 0 )
	{
		int nPreviousItem = GetCurSel();
		int nItem;

		if ( nPreviousItem <= 0 )
		{
			nItem = nCount - 1;
		}
		else
		{
			nItem = nPreviousItem - 1;
		}

		// Edit the item
		CreateInPlaceControl( nItem, nPreviousItem );

		// Move the current selection
		SetCurSel( nItem );
	}
}

ZBPropertyItem* ZCPropertyListCtrl::GetCurrentPropertyItem()
{
	int nItem = GetCurSel();

	if ( nItem >= 0 )
	{
		return GetPropertyItem( nItem );
	}

	return NULL;
}

ZBPropertyItem* ZCPropertyListCtrl::GetPropertyItem( int nIndex )
{
	return nIndex >= 0 && nIndex < GetCount() ? reinterpret_cast<ZBPropertyItem*>( GetItemData( nIndex ) ) : NULL;
}

void ZCPropertyListCtrl::DeletePropertyItem( ZBPropertyItem* pPropertyItem )
{
	int Count = GetCount();

	for ( int i = 0; i < Count; ++i )
	{
		ZBPropertyItem* pProp = reinterpret_cast<ZBPropertyItem*>( GetItemData( i ) );

		if ( pProp == pPropertyItem )
		{
			DeletePropertyItem( i );
			break;
		}
	}
}

void ZCPropertyListCtrl::SetPropertyItemManager( ZBPropertyItemManager* pPropertyItemManager )
{
	if ( m_pPropertyItemManager )
	{
		delete m_pPropertyItemManager;
	}

	m_pPropertyItemManager = pPropertyItemManager;

	// Now initialize the control
	Initialize();
}

void ZCPropertyListCtrl::GetItemValueRect( CRect& rect )
{
	rect.left	 = m_SplitterX + 3;
	rect.bottom	-= 1;
}

void ZCPropertyListCtrl::NoInPlaceControl()
{
	if ( m_pWndInPlaceControl )
	{
		// Before deleting the control,
		// Detach observer on edit control
		DetachObserverForEditCtrl();

		// Then delete the control
		delete m_pWndInPlaceControl;

		m_pWndInPlaceControl = NULL;
	}
}

void ZCPropertyListCtrl::ResetContent( bool DeleteEditCtrl /*= true*/ )
{
	if ( DeleteEditCtrl )
	{
		NoInPlaceControl();
	}

	m_nSelectedItem = -1;

	CDragListBox::ResetContent();
}

void ZCPropertyListCtrl::PreSubclassWindow()
{
	CDragListBox::PreSubclassWindow();

	ModifyStyle( 0, LBS_OWNERDRAWFIXED | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY );
}

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListCtrl message handlers

int ZCPropertyListCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDragListBox::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}
	
	// Create the caption font.
	if ( !m_Font.CreateFont( 15,
							 6,
							 0,
							 0,
							 FW_NORMAL,
							 0,
							 0,
							 0,
							 ANSI_CHARSET,
							 OUT_TT_PRECIS,
							 CLIP_DEFAULT_PRECIS,
							 PROOF_QUALITY,
							 0,
							 _T( "Tahoma" ) ) )
	{
		TRACE0( _T( "Unable to create caption font.\n" ) );
		return -1;
	}

	// Create the bold caption font.
	if ( !m_FontBold.CreateFont( 15,
								 6,
								 0,
								 0,
								 FW_BOLD,
								 0,
								 0,
								 0,
								 ANSI_CHARSET,
								 OUT_TT_PRECIS,
								 CLIP_DEFAULT_PRECIS,
								 PROOF_QUALITY,
								 0,
								 _T( "Tahoma" ) ) )
	{
		TRACE0( _T( "Unable to create caption font.\n" ) );
		return -1;
	}

	return 0;
}

void ZCPropertyListCtrl::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
#if 1
	if( lpDrawItemStruct->itemAction & ODA_FOCUS )
	{
		return;
	}
#endif

	ZBPropertyItem* pPropertyItem = (ZBPropertyItem*)lpDrawItemStruct->itemData;
	ASSERT( pPropertyItem != NULL );

	CDC dc;
	dc.Attach( lpDrawItemStruct->hDC );

	CRect rect;
	GetClientRect( rect );

	int nLeftBorder = rect.left + PROPERTY_LEFT_BORDER;

	// + / -
	bool bTabItem = ToBool( ISA( pPropertyItem,ZBPropertyItemCategory ) );

	if( bTabItem )
	{
		CRect rcSign( lpDrawItemStruct->rcItem );
		rcSign.right = nLeftBorder;

		rcSign.DeflateRect( 4, 4 );

		rcSign.right	+= 1;
		rcSign.bottom	+= 1;

		dc.FillRect( rcSign, CBrush::FromHandle( (HBRUSH)GetStockObject( WHITE_BRUSH ) ) );
		dc.FrameRect( rcSign, CBrush::FromHandle( (HBRUSH)GetStockObject( BLACK_BRUSH ) ) );
		
		CPoint ptCenter( rcSign.CenterPoint() );

		// Minus
		dc.MoveTo( ptCenter.x - 2, ptCenter.y );
		dc.LineTo( ptCenter.x + 3, ptCenter.y );

		if( !static_cast<ZBPropertyItemCategory*>( pPropertyItem )->GetChildrenVisible() )
		{
			// Plus
			dc.MoveTo( ptCenter.x, ptCenter.y - 2 );
			dc.LineTo( ptCenter.x, ptCenter.y + 3 );
		}
	}

	CPen pen( PS_SOLID, 1, RGB( 198, 198, 198 ) );
	CPen* pOldPen = dc.SelectObject( &pen );

	dc.MoveTo( nLeftBorder, rect.top );
	dc.LineTo( nLeftBorder, rect.bottom );

	rect		 = lpDrawItemStruct->rcItem;
	rect.left	+= PROPERTY_LEFT_BORDER;

	int nBottom = rect.bottom - 1;

	dc.MoveTo( nLeftBorder, nBottom );
	dc.LineTo( rect.right, nBottom );

	nLeftBorder = m_SplitterX;

	dc.MoveTo( nLeftBorder, rect.top );
	dc.LineTo( nLeftBorder, nBottom );

	rect.left	+= 1;
	rect.bottom -= 1;
	rect.right	 = nLeftBorder;

	int nCrBackground;
	int nCrText;
	// JMR-MODIF - Le 23 février 2006 - Changement de la couleur par défaut des propriétés ReadOnly.
//	int nCrTextReadOnly;

	if ( ( lpDrawItemStruct->itemAction | ODA_SELECT ) && ( lpDrawItemStruct->itemState & ODS_SELECTED ) )
	{
		nCrBackground	= COLOR_HIGHLIGHT;
		nCrText			= COLOR_HIGHLIGHTTEXT;
		// JMR-MODIF - Le 23 février 2006 - Changement de la couleur par défaut des propriétés ReadOnly.
//		nCrTextReadOnly	= COLOR_GRAYTEXT;
	}
	else
	{
		nCrBackground	= COLOR_WINDOW;
		nCrText			= COLOR_WINDOWTEXT;
		// JMR-MODIF - Le 23 février 2006 - Changement de la couleur par défaut des propriétés ReadOnly.
//		nCrTextReadOnly	= COLOR_GRAYTEXT;
	}

	COLORREF crBackground	= ::GetSysColor( nCrBackground );
	COLORREF crText			= ::GetSysColor( nCrText );
	// JMR-MODIF - Le 23 février 2006 - Changement de la couleur par défaut des propriétés ReadOnly.
//	COLORREF crTextReadOnly	= ::GetSysColor( nCrTextReadOnly );
	COLORREF crTextReadOnly	= COLOR_READONLY;//::GetSysColor( nCrTextReadOnly );

	dc.FillSolidRect( rect, crBackground );
	COLORREF crOldBkColor	= dc.SetBkColor( crBackground );
	COLORREF crOldTextColor	= dc.SetTextColor( ( pPropertyItem->CanBeEdited() ) ? crText : crTextReadOnly );

	rect.left	+= 3;
	rect.right	-= 3;

	CFont* pOldFont = NULL;
	CFont fontLabel;

	if ( bTabItem )
	{
		pOldFont = dc.SelectObject( &m_FontBold );
	}
	else
	{
		pOldFont = dc.SelectObject( &m_Font );
	}

	// Draw the title
	dc.DrawText( pPropertyItem->GetName(), &rect, DT_SINGLELINE | DT_VCENTER );


	// If not selected, draw the value
	if ( !( lpDrawItemStruct->itemState & ODS_SELECTED ) || !pPropertyItem->CanBeEdited() )
	{
		rect = lpDrawItemStruct->rcItem;
		GetItemValueRect( rect );
		pPropertyItem->DrawValue( &dc, rect );
	}

	dc.SelectObject( pOldPen );
	dc.SetTextColor( crOldTextColor );
	dc.SetBkColor( crOldBkColor );

	if ( pOldFont != NULL )
	{
		dc.SelectObject( pOldFont );
	}

	dc.Detach();
}

void ZCPropertyListCtrl::DoCollapse( ZBPropertyItemCategory* pPropertyItemTab, int nItem )
{
	ASSERT( pPropertyItemTab->GetChildrenVisible() );

	nItem++;

	for( int nNumber = pPropertyItemTab->GetNumberEnabledItems(); nNumber > 0; nNumber-- )
	{
		DeleteString( nItem );
	}

	pPropertyItemTab->SetChildrenVisible( false );
}

void ZCPropertyListCtrl::DoExpand( ZBPropertyItemCategory* pPropertyItemTab, int& nItem )
{
	// Now run through category's elements
	ZBPropertyItemIterator i( &pPropertyItemTab->GetPropertyItemSet() );

	for ( ZBPropertyItem* pPropertyItem = i.GetFirst(); pPropertyItem; pPropertyItem = i.GetNext() )
	{
		if ( pPropertyItem->GetEnabled() )
		{
			InsertPropertyItem( pPropertyItem, ++nItem );
		}
	}

	pPropertyItemTab->SetChildrenVisible();
}

void ZCPropertyListCtrl::DoCollapseExpand( int nItem, ZBPropertyItem* pPropertyItem )
{	
	if( pPropertyItem == NULL )
	{
		pPropertyItem = GetPropertyItem( nItem );
	}

	if( pPropertyItem == NULL )
	{
		return;
	}

	if( pPropertyItem->IsKindOf( RUNTIME_CLASS( ZBPropertyItemCategory ) ) )
	{
		if( SetCurrentData() )
		{
			NoInPlaceControl();
		}

		ZBPropertyItemCategory* pPropertyItemTab = static_cast<ZBPropertyItemCategory*>( pPropertyItem );

		if( pPropertyItemTab->GetChildrenVisible() )
		{
			DoCollapse( pPropertyItemTab, nItem );
		}
		else
		{
			DoExpand( pPropertyItemTab, nItem );
		}

		// We need to save the collapsed and expand attribute
		SavePropertyState( pPropertyItemTab );
	}
}

void ZCPropertyListCtrl::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	CDragListBox::OnLButtonDblClk( nFlags, point );

	DoCollapseExpand( GetCurSel() );
}

BOOL ZCPropertyListCtrl::PreTranslateMessage( MSG* pMsg )
{
	if( pMsg->message == WM_KEYDOWN )
	{
		int nItem	= GetCurSel();
		char nChar	= char( pMsg->wParam );
		bool bDone	= true;

		ZBPropertyItem* pPropertyItem = GetPropertyItem( nItem );

		if( pPropertyItem != NULL )
		{
			if( pPropertyItem->IsKindOf( RUNTIME_CLASS( ZBPropertyItemCategory ) ) )
			{
				bool bChildrenVisible = static_cast<ZBPropertyItemCategory*>(pPropertyItem)->GetChildrenVisible();

				switch( nChar )
				{
					case VK_RETURN:
					{
						DoCollapseExpand( nItem, pPropertyItem );
						break;
					}

					case VK_ADD:
					{
						if( !bChildrenVisible )
						{
							DoExpand( (ZBPropertyItemCategory*)pPropertyItem, nItem );
						}

						break;
					}

					case VK_SUBTRACT:
					{
						if( bChildrenVisible )
						{
							DoCollapse( (ZBPropertyItemCategory*)pPropertyItem, nItem );
						}

						break;
					}

					case VK_TAB:
					{
						if ( GetKeyState( VK_SHIFT ) & 0x80000000 )
						{
							// Edit previous item
							EditPreviousItem();
						}
						else
						{
							// Edit next item
							EditNextItem();
						}

						break;
					}

					default:
					{
						bDone = false;
					}
				}
			}
			else
			{
				switch( nChar )
				{
					case VK_TAB:
					{
						if ( GetKeyState( VK_SHIFT ) & 0x80000000 )
						{
							// Edit previous item
							EditPreviousItem();
						}
						else
						{
							// Edit next item
							EditNextItem();
						}

						break;
					}

					case VK_RETURN:
					{
						if( m_pWndInPlaceControl != NULL )
						{
							dynamic_cast<CWnd*>( m_pWndInPlaceControl )->SetFocus();
						}

						break;
					}

					default:
					{
						bDone = false;
					}
				}
			}
		}
		else
		{
			bDone = false;
		}

		if( bDone )
		{
			return TRUE;
		}
		else
		{
			if( GetFocus() == this && IsCharAlpha( nChar ) )
			{
				if( LookupPropertyItem( nChar ) )
				{
					OnSelChange();
				}

				return TRUE;
			}
		}
	}

	return CDragListBox::PreTranslateMessage( pMsg );
}

int ZCPropertyListCtrl::FindPropertyItem( char nStartChar, int nFromIndex, int nCount )
{
	const CString strStartChar( nStartChar );

	while( nCount-- )
	{
		ZBPropertyItem* pPropertyItem = reinterpret_cast<ZBPropertyItem*>( GetItemData( nFromIndex ) );
		ASSERT( pPropertyItem != NULL );

		if( pPropertyItem->GetName().Left( 1 ).CompareNoCase( strStartChar ) == 0 )
		{
			return nFromIndex;
		}

		nFromIndex++;
	}

	return -1;
}

bool ZCPropertyListCtrl::LookupPropertyItem( char nStartChar )
{
	int nCount = GetCount();

	if( nCount )
	{
		int nCurrItem = GetCurSel() + 1;

		if( nCurrItem == nCount )
		{
			nCurrItem = 0;
		}

		int nFindIndex = FindPropertyItem( nStartChar, nCurrItem, nCount - nCurrItem );

		if( nFindIndex == -1 && nCurrItem > 0 )
		{
			nFindIndex = FindPropertyItem( nStartChar, 0, nCurrItem );
		}

		if( nFindIndex != -1 )
		{
			SetCurSel( nFindIndex );
			return true;
		}
	}

	return false;
}

bool ZCPropertyListCtrl::SetCurrentData()
{
	if( m_pWndInPlaceControl != NULL && m_nSelectedItem != -1 )
	{
		ZBPropertyItem* pPropertyItemEdited = GetPropertyItem( m_nSelectedItem );

		if ( pPropertyItemEdited != NULL )
		{
			pPropertyItemEdited->SetData( m_pWndInPlaceControl->GetEditText() );

			bool bRefresh = false;

			m_pPropertyItemManager->OnDataChanged( pPropertyItemEdited, this, m_nSelectedItem, bRefresh );

			// If the control need to be refreshed
			if ( bRefresh )
			{
				// Force the control list to reload values
				Refresh( true, true );
			}
			else
			{
				// When a data has changed,
				// Check the state
				CheckState();
			}

			return true;
		}
	}

	return false;
}

afx_msg LONG ZCPropertyListCtrl::OnKeyPressed( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
	{
		case VK_ESCAPE:
		{
			// Remove the focus by setting the focus to the list control
			SetFocus();
			return 1;
		}

		case VK_RETURN:
		case VK_TAB:
		{
			// Edit next item
			if ( !m_ListInReadOnly )
			{
				EditNextItem();
			}

			return 1;
		}

		case ( VK_SHIFT | VK_TAB ):
		{
			// Edit previous item
			if ( !m_ListInReadOnly )
			{
				EditPreviousItem();
			}

			return 1;
		}

		default:
		{
			break;
		}
	}

	return 0;
}

void ZCPropertyListCtrl::OnSelChange()
{
	int nItem = GetCurSel();

	if ( m_nSelectedItem != nItem && !m_ListInReadOnly )
	{
		CreateInPlaceControl( nItem, nItem );
	}
}

void ZCPropertyListCtrl::DetachObserverForEditCtrl()
{
	// If a previous edit control exists, remove it as an observer.
	if ( m_pWndInPlaceControl )
	{
		m_pWndInPlaceControl->DetachAllObservers();
		DetachObserver( m_pWndInPlaceControl );
	}
}

void ZCPropertyListCtrl::CreateInPlaceControl( int nItem, int nPreviousItem /*= -1*/ )
{
	ZBPropertyItem* pPreviousPropertyItem = NULL;

	if ( nPreviousItem != -1 )
	{
		pPreviousPropertyItem = GetPropertyItem( nPreviousItem );
	}

	CRect rect;

	GetItemRect( nItem, rect );
	GetItemValueRect( rect );

	// Save the value if necessary when deleted
	if ( m_pWndInPlaceControl )
	{
		// Assigns the control size to the property item
		if ( m_pWndInPlaceControl->GetSize().cx != 0 &&
			 m_pWndInPlaceControl->GetSize().cy != 0 &&
			 pPreviousPropertyItem != NULL )
		{
			pPreviousPropertyItem->SetSize( m_pWndInPlaceControl->GetSize() );
		}

		if ( m_pWndInPlaceControl->GetExtendedSize().cx != 0 &&
			 m_pWndInPlaceControl->GetExtendedSize().cy != 0 &&
			 pPreviousPropertyItem != NULL )
		{
			pPreviousPropertyItem->SetExtendedSize( m_pWndInPlaceControl->GetExtendedSize() );
		}

		// Request the manager to save the property state
		SavePropertyState( pPreviousPropertyItem );

		// save the control value
		m_pWndInPlaceControl->SaveValue();
	}

	// Detach observer on edit control
	DetachObserverForEditCtrl();

	// Get the requested property item
	ZBPropertyItem* pPropertyItem = GetPropertyItem( nItem );
	ASSERT( pPropertyItem != NULL );

	if ( pPropertyItem->CanBeEdited() )
	{
		// First, retreive the property state
		_ZBPropertyState* pPropState = GetPropertyState( pPropertyItem );

		if ( pPropState								&&
			 pPropState->GetExtendedSize().cx != 0	&&
			 pPropState->GetExtendedSize().cy != 0 )
		{
			pPropertyItem->CreateInPlaceControl( this, rect, m_pWndInPlaceControl, pPropState->GetExtendedSize() );
		}
		else
		{
			pPropertyItem->CreateInPlaceControl( this, rect, m_pWndInPlaceControl );
		}

		// Notify windows about editing properties
		AfxGetMainWnd()->SendMessageToDescendants( UM_START_PROPERTY_EDITION, 0, (LPARAM)NULL );
	}
	else
	{
		pPropertyItem->DestroyInPlaceControl( m_pWndInPlaceControl );
	}

	// If the edit control exists,
	// set observers
	if ( m_pWndInPlaceControl )
	{
		m_pWndInPlaceControl->AttachObserver( this );
		AttachObserver( m_pWndInPlaceControl );
	}

	// Redraw the old selected item
	if ( m_nSelectedItem != nItem )
	{
		RedrawItem( m_nSelectedItem );
	}

	// Saves the selected item
	m_nSelectedItem = nItem;
	SetCurSel( m_nSelectedItem );

	if ( m_pWndInPlaceControl )
	{
		// Sets the focus to the newly created control
		dynamic_cast<CWnd*>( m_pWndInPlaceControl )->SetFocus();
	}
	
	// Notify all observers
	ZBProperty* pProperty = m_pPropertyItemManager->GetCorrespondingProperty( pPropertyItem );
	ZBPropertyItemObserverMsg Msg( pProperty );

	// Notify all observers
	NotifyAllObservers( &Msg );
}

void ZCPropertyListCtrl::ShowInPlaceControl( bool bShow )
{
	if( m_pWndInPlaceControl )
	{
		dynamic_cast<CWnd*>( m_pWndInPlaceControl )->ShowWindow( ( bShow == true ) ? SW_SHOW : SW_HIDE );
	}
}

void ZCPropertyListCtrl::OnKillFocus( CWnd* pNewWnd )
{
	CDragListBox::OnKillFocus( pNewWnd );
}

void ZCPropertyListCtrl::RedrawAll()
{
	ShowInPlaceControl( false );

	// Try to call the invalidation window method
	Invalidate();

	ShowInPlaceControl();
}

void ZCPropertyListCtrl::RedrawItem( int nItem )
{
	ZBPropertyItem* pPropertyItem = GetPropertyItem( nItem );

	if ( pPropertyItem && !ISA( pPropertyItem, ZBPropertyItemCategory ) )
	{
		CRect rect;

		CDC* pDC = GetDC();

		if ( !pDC )
		{
			return;
		}

		CFont* pOldFont = pDC->SelectObject( &m_Font );

		COLORREF crBkColor = pDC->GetBkColor();

		GetItemRect( nItem, rect );
		GetItemValueRect( rect );

		rect.DeflateRect( 1, 1 );

		pDC->FillSolidRect( &rect, crBkColor );

		rect.InflateRect( 1, 1 );

		// JMR-MODIF - Le 23 février 2006 - Changement de la couleur par défaut des propriétés ReadOnly.
/*		COLORREF crOldTextColor =
			pDC->SetTextColor( ( pPropertyItem->CanBeEdited() ) ? ::GetSysColor( COLOR_WINDOWTEXT ) : ::GetSysColor( COLOR_GRAYTEXT ) );
*/
		COLORREF crOldTextColor =
			pDC->SetTextColor( ( pPropertyItem->CanBeEdited() ) ? ::GetSysColor( COLOR_WINDOWTEXT ) : COLOR_READONLY );

		pPropertyItem->DrawValue( pDC, rect );

		pDC->SetTextColor( crOldTextColor );

		if ( pOldFont != NULL )
		{
			pDC->SelectObject( pOldFont );
		}

		ReleaseDC( pDC );
	}
}

void ZCPropertyListCtrl::CheckState()
{
	if ( !IsListInPhase() )
	{
		Refresh( false );
	}
}

bool ZCPropertyListCtrl::IsListInPhase()
{
	int nItem	= 0;
	int nCount	= GetCount();

	// Run trough the item list and check simulatenously the property item manager
	// Run through all items
	ZBItemCategoryIterator i( &m_pPropertyItemManager->GetItemCategorySet() );
	ZBPropertyItemCategory* pPropertyItemTab = i.GetFirst(); 

	for ( int nIndex = 0; ( nIndex < nCount ) && ( pPropertyItemTab != NULL ); ++nIndex, pPropertyItemTab = i.GetNext() )
	{
		// Retreive the item from the list control
		ZBPropertyItem* pItem = GetPropertyItem( nIndex );

		while ( pPropertyItemTab && !pPropertyItemTab->GetEnabled() )
		{
			pPropertyItemTab = i.GetNext();
		}

		// No item, no category, next
		if ( !pItem && !pPropertyItemTab )
		{
			continue;
		}

		// If no item only, return not in phase
		if ( !pItem )
		{
			return false;
		}

		// If no category only, return not in phase
		if ( !pPropertyItemTab )
		{
			return false;
		}

		// Check if the item is a category and the same
		// if not, return not in phase
		if ( !ISA( pItem, ZBPropertyItemCategory ) || pItem != pPropertyItemTab )
		{
			return false;
		}

		// Now process the category.
		// First, check if children are visible
		// if so, then check all childrens
		if ( pPropertyItemTab->GetChildrenVisible() )
		{
			// Now run through category's elements
			ZBPropertyItemIterator j( &pPropertyItemTab->GetPropertyItemSet() );

			for ( ZBPropertyItem* pChildPropertyCatItem = j.GetFirst(); pChildPropertyCatItem; pChildPropertyCatItem = j.GetNext() )
			{
				// Retreive the immediate following item from the list control
				pItem = GetPropertyItem( ++nIndex );

				while ( pChildPropertyCatItem && !pChildPropertyCatItem->GetEnabled() )
				{
					pChildPropertyCatItem = j.GetNext();
				}

				// If no child item category only, break the loop
				if ( !pChildPropertyCatItem )
				{
					--nIndex; // Since we reached the end of elements and all were not enable
					break;
				}

				// Check if the same item
				// if not, return not in phase
				if ( pItem != pChildPropertyCatItem )
				{
					return false;
				}
			} // End while for posChild
		} // End of children visible
	}

	// Check if at the loop end, both iterators are at the end,
	// if not, return not in phase
	if ( ( nIndex < nCount ) || ( pPropertyItemTab != NULL ) )
	{
		return false;
	}

	// In phase
	return true;
}

void ZCPropertyListCtrl::OnMouseMove( UINT nFlags, CPoint point )
{
	// Tests if we are in splitter moving mode
	if ( gInMoveSplitterMode )
	{
		CDC* pDC = GetDC();

		if ( !pDC )
		{
			return;
		}

		// Converts the point
		CPoint pt( point );

		// Check the maximum and the minimum
		if ( gMaxLeft != 0 && gMaxRight != 0 )
		{
			if ( pt.x > gMaxRight )
			{
				pt.x = gMaxRight;
			}
			else if ( pt.x < gMaxLeft )
			{
				pt.x = gMaxLeft;
			}
		}

		// Sets the splitter position for the redraw
		m_SplitterX = pt.x;

		// Call the invalidation window method
		Invalidate();

		// JMR-MODIF - Le 14 février 2006 - Ajout du code pour le nettoyage du Device Context.
		ReleaseDC( pDC );

		return;
	}
	else
	{
		CRect rect;
		GetClientRect( rect );

		rect.left	= m_SplitterX - 2;
		rect.right	= m_SplitterX + 2;

		// Test if the cursor is on the splitter
		if ( rect.PtInRect( point ) )
		{
			::SetCursor( m_hcurSplitter );
			return;
		}
	}

	CDragListBox::OnMouseMove( nFlags, point );
}

void ZCPropertyListCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( point.x <= PROPERTY_LEFT_BORDER )
	{
		CDragListBox::OnLButtonDown( nFlags, point );
		DoCollapseExpand( GetCurSel() );

		return;
	}
	else
	{
		CRect rect;
		GetClientRect( rect );

		rect.left	= m_SplitterX - 2;
		rect.right	= m_SplitterX + 2;

		// Test if the cursor is on the splitter
		if ( rect.PtInRect( point ) )
		{
			gInMoveSplitterMode = true;

			GetClientRect( gInitialRect );
			gInitialRect.DeflateRect( 2, 2 );

			gInitialPoint	= point;
			gLastPoint.x	= 0;
			gLastPoint.y	= 0;

			// Calculates the max in x
			gMaxRight		= gInitialRect.right-5;
			gMaxLeft		= gInitialRect.left+PROPERTY_LEFT_BORDER+5;

			// Hide the edition control
			ShowInPlaceControl( false );

			// Capture the cursor in the window
			::SetCursor( m_hcurSplitter );
			SetCapture();
		}
		else
		{
			CDragListBox::OnLButtonDown( nFlags, point );
		}
	}
}

void ZCPropertyListCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	// Tests if we were in splitter moving mode
	if ( gInMoveSplitterMode )
	{
		// Release the cursor capture
		ReleaseCapture();

		// Converts the point
		CPoint pt( point );

		// Check the maximum and the minimum
		if ( gMaxLeft != 0 && gMaxRight != 0 )
		{
			if ( pt.x > gMaxRight )
			{
				pt.x = gMaxRight;
			}
			else if ( pt.x < gMaxLeft )
			{
				pt.x = gMaxLeft;
			}
		}

		// Saves the splitter position
		m_SplitterX			= pt.x;

		// Reset flags and value
		gInMoveSplitterMode = false;
		gMaxLeft			= 0;
		gMaxRight			= 0;

		// Redraw the entire control
		Invalidate();

		// Unselect the item
		SetCurSel( -1 );
	}

	CDragListBox::OnLButtonUp( nFlags, point );
}

BOOL ZCPropertyListCtrl::BeginDrag( CPoint pt )
{
	if ( m_ListInReadOnly )
	{
		return FALSE;
	}

	m_SrcDragPropertyItemIndex	= ItemFromPt( pt );
	m_pSrcDragPropertyItem		= GetPropertyItem( m_SrcDragPropertyItemIndex );

	if ( ( !m_pSrcDragPropertyItem || !m_pSrcDragPropertyItem->IsEnabledDragNDrop() ) &&
		 !ISA( m_pSrcDragPropertyItem, ZBPropertyItemCategory ) )
	{
		m_pSrcDragPropertyItem = NULL;
		return FALSE;
	}

	m_nLast = -1;

	return TRUE;
}

void ZCPropertyListCtrl::Dropped( int nSrcIndex, CPoint pt )
{
	if ( m_ListInReadOnly )
	{
		return;
	}

	int Index = ItemFromPt( pt );

	if ( Index == m_SrcDragPropertyItemIndex )
	{
		return;
	}

	ZBPropertyItem* pDstPropertyItem = GetPropertyItem( ( m_SrcDragPropertyItemIndex < Index ) ? Index-1 : Index );

	// If it is the same index, or NULL, or disabled drag & drop or a category, do nothing
	if ( m_pSrcDragPropertyItem == pDstPropertyItem		||
		 m_pSrcDragPropertyItem == NULL					||
		 pDstPropertyItem == NULL						||
		 !m_pSrcDragPropertyItem->IsEnabledDragNDrop()	||
		 ISA( m_pSrcDragPropertyItem, ZBPropertyItemCategory ) )
	{
		Refresh( false, false );
		return;
	}

	// Notify the property manager about the move
	if ( m_pPropertyItemManager->OnDropInternalPropertyItem( m_pSrcDragPropertyItem,
															 pDstPropertyItem,
															 ( m_SrcDragPropertyItemIndex < Index ) ) )
	{
		Refresh( true, false );
	}
	else
	{
		if ( m_pSrcDragPropertyItem || m_pSrcDragPropertyItem->IsEnabledDragNDrop() )
		{
			Refresh( false, false );
		}
	}
}
