//## begin module%3624CA420321.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3624CA420321.cm

//## begin module%3624CA420321.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%3624CA420321.cp

//## Module: ViewMod%3624CA420321; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ViewMod.cpp

//## begin module%3624CA420321.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3624CA420321.additionalIncludes

//## begin module%3624CA420321.includes preserve=yes
//## end module%3624CA420321.includes

// ViewMod
#include "ViewMod.h"

#include "DocWrite.h"

// ZIViewCd
#include "zBaseLib\ZIViewCd.h"
#include "ZAApp.h"
#include "zBaseLib\VTools.h"
#include "zBaseLib\ZACheck.h"
#include "zBaseLib\ZARadio.h"
#include "zBaseLib\ZANumbrd.h"
#include "zBaseLib\ZASquare.h"
#include "zBaseLib\zabntext.h"
#include "zBaseLib\zaBitmap.h"
#include "zBaseLib\ZAMultiC.h"
#include "zBaseLib\ZAMStr.h"

#include "zBaseLib\Edit.h"

// BObjUtil
#include "zBaseLib\BObjUtil.h"

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	#include "Property.h"
#endif

#include "zWinUtil32\CalWnd.h"
#include "zWinUtil32\ZIObjectNotesDialog.h"

#include "zBaseLib\FileDlg.h"

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	#include "zDesigner\wizformc.h"
	#include "zDesigner\ziwzform.h"
	#include "zDesigner\ziwzfrml.h"
	#include "zDesigner\wzalign.h"
	#include "zDesigner\WZFRMTST.h"
	#include "zDesigner\wizcalc.h"
	#include "zDesigner\ziwzrnde.h"
	#include "zWinUtil32\colorsel.h"
	#include "zDesigner\SelStyle.h"
	#include "zDesigner\BordDef.h"
#endif

#include "zBaseLib\ZBFieldObserverMsg.h"

#ifdef _ZDESIGNER
#include "zDesigner\planfdoc.h"
#endif

#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage de code inutile. (En commentaires)

IMPLEMENT_DYNCREATE( ZIViewModify, ZIViewRead )

BEGIN_MESSAGE_MAP( ZIViewModify, ZIViewRead )
	//{{AFX_MSG_MAP(ZIViewModify)
	ON_WM_MOUSEMOVE()

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	ON_COMMAND(ID_TODAY, OnToday)
	ON_COMMAND(ID_EDITION_PROTECTOBJECT, OnEditionProtectObject)
	ON_UPDATE_COMMAND_UI(ID_EDITION_PROTECTOBJECT, OnUpdateEditionProtectObject)
	ON_MESSAGE(ID_PROCESS_CALCULATE_MESSAGE, ProcessCalculate)
	ON_MESSAGE(ID_PROCESS_FIELD_EDITNEXT, OnProcessFieldEditNext)
	ON_MESSAGE(ID_PROCESS_FIELD_CHANGE, ProcessFieldChange)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText )
	ON_COMMAND(ID_ADDOBJECTNOTES, OnAddObjectNotes)
	ON_COMMAND(ID_DELETEOBJECTNOTES, OnDeleteObjectNotes)
	ON_UPDATE_COMMAND_UI(ID_DELETEOBJECTNOTES, OnUpdateDeleteObjectNotes)
	ON_MESSAGE(UM_SPHELP_EMPTYOBJECT, OnEmptyObject)
	ON_MESSAGE(UM_SPHELP_WIZARDMENU, OnWizardMenu)
	ON_MESSAGE(UM_SPHELP_CALENDAROBJECT, OnCalendarObject)
	ON_MESSAGE(UM_SPHELP_NOTEOBJECT, OnObjectNote)
	ON_MESSAGE(UM_SPHELP_ASSOCIATIONOBJECT, OnAssociationMenu)
	ON_MESSAGE(ID_SPECIALHELPMENU, OnMenuSelected)
	ON_COMMAND(ID_SUBMENU1_SELECTOBJECT, OnSubmenu1Selectobject)
	ON_COMMAND(ID_SUBMENU1_UNSELECTOBJECT, OnSubmenu1Unselectobject)
	ON_MESSAGE(ID_CLEARSELECTIONALL, OnClearSelectionAll)
	ON_MESSAGE(ID_POINTERINSELECTION, OnPointerSelection)
	ON_MESSAGE(ID_POINTERHASSELECTED, OnPointerHasSelected)
	ON_MESSAGE(ID_FIELD_EDITNEXT, OnFieldEditNext)
	ON_MESSAGE(ID_FIELD_DESELECTALLOBJECT, OnDeselectAllObjects)
	ON_COMMAND(ID_INSERT_FILE, OnInsertFile)
	ON_UPDATE_COMMAND_UI(ID_INSERT_FILE, OnUpdateInsertFile)
	ON_MESSAGE(UM_SPHELP_PROPERTYOBJECT, OnObjectProperty)
	ON_COMMAND(ID_FIELD_POSITION_SIZE, OnFieldPositionSize)
	ON_COMMAND(ID_FIELD_PROPERTY, OnFieldProperty)
	ON_COMMAND(ID_WIZARD_CREATEFORMULA, OnWizardCreateFormula)
	ON_COMMAND(ID_SUBMENU1_FONTCHANGE, OnSubmenu1Fontchange)
	ON_UPDATE_COMMAND_UI(ID_SUBMENU1_FONTCHANGE, OnUpdateSubmenu1Fontchange)
	ON_COMMAND(ID_SUBMENU_FORMAT, OnSubmenuFormat)
	ON_COMMAND(ID_WIZARD_MODIFYfORMULA, OnSubmenuModifyFormula)
	ON_UPDATE_COMMAND_UI(ID_SUBMENU_FORMAT, OnUpdateSubMenuFormat)
	ON_UPDATE_COMMAND_UI(ID_SUBMENU1_ALIGN, OnUpdateSubmenuAlign)
	ON_UPDATE_COMMAND_UI(ID_WIZARD_MODIFYfORMULA, OnUpdateSubmenuModifyFormula)
	ON_COMMAND(ID_SUBMENU1_ALIGN, OnSubmenuAlign)
	ON_COMMAND(ID_SUBMENU1_HIDEPRTOBJECT, OnSubmenuHidePrtObject)
	ON_UPDATE_COMMAND_UI(ID_SUBMENU1_HIDEPRTOBJECT, OnUpdateSubmenuHidePrtObject)
	ON_COMMAND(ID_SUBMENU1_OBJECTHIDE, OnSubmenuObjectHide)
	ON_UPDATE_COMMAND_UI(ID_SUBMENU1_OBJECTHIDE, OnUpdateSubmenuObjectHide)
	ON_COMMAND(ID_SUBMENU1_CHANGECOLOR, OnSubmenuChangeColor)
	ON_COMMAND(ID_WIZARD_FORMATFIELD, OnWizardFormat)
	ON_COMMAND(ID_WIZARD_CALCULATED, OnWizardCalculated)
	ON_COMMAND(ID_FIELD_ALIGNCENTER, OnFieldAlignCenter)
	ON_COMMAND(ID_FIELD_ALIGNLEFT, OnFieldAlignLeft)
	ON_COMMAND(ID_FIELD_ALIGNRIGHT, OnFieldAlignRight)
	ON_UPDATE_COMMAND_UI(ID_FIELD_ALIGNCENTER, OnUpdateFieldAlignCenter)
	ON_UPDATE_COMMAND_UI(ID_FIELD_ALIGNLEFT, OnUpdateFieldAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_FIELD_ALIGNRIGHT, OnUpdateFieldAlignRight)
	ON_COMMAND(ID_FIELD_APPLYROUNDED, OnFieldApplyRounded)
	ON_COMMAND(ID_SUBMENU1_CHANGEFILLCOLOR, OnSubmenuChangeFillcolor)
	ON_COMMAND(ID_SECTION_ALIGN, OnSectionAlign)
	ON_COMMAND(ID_SECTION_CHANGE_STYLE, OnSectionChangeStyle)
	ON_COMMAND(ID_SECTION_CHANGECOLOR, OnSectionChangeColor)
	ON_COMMAND(ID_SECTION_CHANGEFILLCOLOR, OnSectionChangeFillColor)
	ON_COMMAND(ID_SECTION_FONTCHANGE, OnSectionFontChange)
	ON_COMMAND(ID_CHANGE_BORDER, OnChangeBorder)
	ON_MESSAGE(ID_CALCULATE_MESSAGE, OnCalculateAllFormula)
	ON_MESSAGE(ID_FIELD_CHANGE, OnFieldChange)
	ON_COMMAND(ID_SUBMENU1_CHANGELINECOLOR, OnChangeLineColor)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%3624CA420321.additionalDeclarations

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class ZIViewModify 

ZIViewModify::ZIViewModify()
//## begin ZIViewModify::ZIViewModify%.hasinit preserve=no
//## end ZIViewModify::ZIViewModify%.hasinit
//## begin ZIViewModify::ZIViewModify%.initialization preserve=yes
//## end ZIViewModify::ZIViewModify%.initialization
{
	//## begin ZIViewModify::ZIViewModify%.body preserve=yes
	m_ViewType = FormModifyView;

	m_ToolTipNoteText.LoadString( IDS_TOOLTIPNOTETEXT );
	m_ToolTipTypeObject.LoadString( IDS_TOOLTIPOBJECTTYPE );
	//## end ZIViewModify::ZIViewModify%.body
}

ZIViewModify::~ZIViewModify()
{
	//## begin ZIViewModify::~ZIViewModify%.body preserve=yes
	//## end ZIViewModify::~ZIViewModify%.body
}

//## Other Operations (implementation)
void ZIViewModify::OnDraw ( CDC* pDC )
{
	//## begin ZIViewModify::OnDraw%908380093.body preserve=yes
	ZIViewRead::OnDraw( pDC );
	//## end ZIViewModify::OnDraw%908380093.body
}

void ZIViewModify::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( !ZAApp::ZAGetApp()->IsCursorCapturedValid( point, this ) )
		ReleaseCapture();

	// Find the current select tool
	// and keep its pointer.
	// But if control key pressed
	// Take the selection tool directly
	ZIVisualTool* pTool = ZIVisualTool::FindTool( ZIVisualTool::m_CurrentToolType );

	if ( pTool != NULL )
		pTool->OnMouseMove( this, nFlags, point );
}

void ZIViewModify::EditObject ( PlanFinObject* pObj )
{
  //## begin ZIViewModify::EditObject%938177640.body preserve=yes
	CDC *pDC = GetDC();
	ASSERT( pDC );

	OnPrepareDC( pDC );
	DeselectAllObject( this, pDC, GetDocument() );

	// First, delete the existing edit control
	if ( GetDocument()->GetEditControl() != NULL )
	{
		delete GetDocument()->GetEditControl();
		GetDocument()->AssignEditControl( NULL );
	}

	GetDocument()->AssignEditControl( CreateEditControl( pObj, pDC ) );

	// If control successfully created
	if ( GetDocument()->GetEditControl() )
	{
		GetDocument()->GetEditControl()->Create( ZAGlobal::IsFormDesigner(),
												 this,
												 pDC,
												 GetDocument(),
												 pObj, 
												 ZAApp::ZAGetApp()->GetFieldRepository(),
												 ZAApp::ZAGetApp()->IsAutoCalculate(),
												 ZAApp::ZAGetApp()->GoNextEdit() );

		GetDocument()->SetModifiedFlag( TRUE );
	}

	VERIFY( ReleaseDC( pDC ) );
	//## end ZIViewModify::EditObject%938177640.body
}

Edit* ZIViewModify::CreateEditControl ( PlanFinObject* pObj, CDC* pDC )
{
	//## begin ZIViewModify::CreateEditControl%938177641.body preserve=yes
	switch ( ZBObjectUtility::GetClassNameID( pObj ) )
	{
		case IDS_STATICTEXT_CLASS: 
		{
			return new CalcEdit;
		}

		case IDS_DATE_CLASS: 
		{
			return new TimeEdit;
		}

		case IDS_CALCULATED_CLASS: 
		{
			return new CalcEdit;
		}

		case IDS_HISTOAMOUNT_CLASS: 
		{
			return new NumEditHistoric;
		}

		case IDS_AMOUNT_CLASS: 
		{
			if ( pObj->IsMemberOfMultiColumn() )
				return new NumEditHistoric;
			else
				return new NumEdit;
		}

		case IDS_MULTITEXTSTATIC_CLASS: 
		{
			return new CalcEdit;
		}

		case IDS_MULTITEXT_CLASS: 
		{
			return new StrEdit( TRUE );
		}

		case IDS_HISTOTEXT_CLASS: 
		{
			return new StrEditHistoric;
		}

		case IDS_TEXT_CLASS: 
		{
			if ( pObj->IsMemberOfMultiColumn() )
				return new StrEditHistoric;
			else
				return new StrEdit;
		}

		case IDS_SQUARETEXT_CLASS: 
		{
			if ( dynamic_cast<PLFNSquare*>( pObj )->GetpObject() )
				return CreateEditControl( const_cast<PlanFinObject*>( dynamic_cast<PLFNSquare*>( pObj )->GetpObject() ),
										  pDC );

			return NULL;
		}

		case IDS_NUMBEREDSECTION_CLASS: 
		{
			if ( dynamic_cast<PLFNAutoNumbered*>( pObj )->GetpObject() )
				return CreateEditControl( const_cast<PlanFinObject*>( dynamic_cast<PLFNAutoNumbered*>( pObj )->GetpObject() ),
										  pDC );

			return NULL;
		}

		case IDS_CHECK_CLASS: 
		{
			dynamic_cast<PLFNCheck*>( pObj )->EditObject( this, pDC, GetDocument() );
			GetDocument()->SetModifiedFlag( TRUE );

			return NULL;
		}

		case IDS_RADIO_CLASS: 
		{
			dynamic_cast<PLFNRadio*>( pObj )->EditObject( this, pDC, GetDocument() );
			GetDocument()->SetModifiedFlag( TRUE );

			return NULL;
		}

		case IDS_MASKSTRING_CLASS: 
		{
			return new MaskEdit;
		}

		case IDS_MASKSTRINGHISTO_CLASS: 
		{
			return new MaskEdit;
		}

		case IDS_MULTICOLUMN_CLASS: 
		{
			return new MultiColumnEdit;
		}

		default: break;
	}

	return NULL;
	//## end ZIViewModify::CreateEditControl%938177641.body
}

void ZIViewModify::AddObjectNotes ( PlanFinObject* pObj )
{
	//## begin ZIViewModify::AddObjectNotes%941353880.body preserve=yes
	ZIObjectNotesDialog	ObjectNotesDialog( ( pObj->GetNotesPointer() ) ? pObj->GetNotesPointer()->GetComment() : _T( "" ),
										   ( pObj->GetNotesPointer() ) ? pObj->GetNotesPointer()->GetUsername() : _T( "" ) );

	switch ( ObjectNotesDialog.DoModal() )
	{
		case IDOK:
		{
			// Save the notes
			pObj->AddNotes( ObjectNotesDialog.GetComment(), ZAGlobal::GetConnectedUserName() );
			break;
		}

		case IDC_DELETENOTES:
		{
			// Delete the notes
			pObj->DeleteNotes();
			break;
		}
	}
	//## end ZIViewModify::AddObjectNotes%941353880.body
}

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )

afx_msg LONG ZIViewModify::OnCalculateAllFormula ( UINT message, LONG wParam )
{
	//## begin ZIViewModify::OnCalculateAllFormula%938112087.body preserve=yes
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	// post a message to not slow the process
	return PostMessage( ID_PROCESS_CALCULATE_MESSAGE );
	//## end ZIViewModify::OnCalculateAllFormula%938112087.body
}

afx_msg LONG ZIViewModify::OnFieldChange ( UINT message, LONG wParam )
{
	//## begin ZIViewModify::OnFieldChange%938112088.body preserve=yes
	return PostMessage( ID_PROCESS_FIELD_CHANGE, 0, wParam );
	//## end ZIViewModify::OnFieldChange%938112088.body
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Additional Declarations

//## begin ZIViewModify%3624C8EC015D.declarations preserve=yes
//## end ZIViewModify%3624C8EC015D.declarations

//## begin module%3624CA420321.epilog preserve=yes
void ZIViewModify::OnToday()
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return;

	ZDDocumentReadWrite	*pDoc = GetDocument();
	ASSERT( pDoc );

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// Only valid on date object
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) )
		return;

	// End the edition
	SetFocus();

	// Release the mouse cursor capture
	ReleaseCapture();

	// Set Today to the object
	( (PLFNTime*)pObj )->SetToday();	

	// Deselect the current object
	OnSubmenu1Unselectobject();
}

void ZIViewModify::OnEditionProtectObject()
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return;

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	if ( ( (PLFNLong*)pObj )->KeepTheValue() )
	{
		( (PLFNLong*)pObj )->SetKeepTheValue( FALSE );
	}
	else
	{
		( (PLFNLong*)pObj )->SetKeepTheValue();
	}

	OnSubmenu1Unselectobject();
	GetDocument()->SetModifiedFlag();
	RedrawWindow();
}

void ZIViewModify::OnUpdateEditionProtectObject( CCmdUI* pCmdUI )
{
	PlanFinObject  *obj = GetDocument()->GetSelectedObject();

	if ( obj )
	{
		// If the object is a number and is a calculated field
		if ( obj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) && ( (PLFNLong*)obj )->IsCalculatedField() )
		{
			pCmdUI->Enable( TRUE );
			pCmdUI->SetCheck( ( (PLFNLong*)obj )->KeepTheValue() );
		}
		else pCmdUI->Enable( FALSE );
	}
	else pCmdUI->Enable( TRUE );
}

void ZIViewModify::OnAddObjectNotes() 
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return;

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	AddObjectNotes( pObj );

	OnSubmenu1Unselectobject();
	GetDocument()->SetModifiedFlag();
}

void ZIViewModify::OnDeleteObjectNotes() 
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return;

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj || ( pObj && pObj->GetNotesPointer() == NULL ) )
		return;

	pObj->DeleteNotes();
	OnSubmenu1Unselectobject();
	GetDocument()->SetModifiedFlag();
}

void ZIViewModify::OnUpdateDeleteObjectNotes( CCmdUI* pCmdUI )
{
	PlanFinObject  *pObj = GetDocument()->GetSelectedObject();

	if ( pObj )
		pCmdUI->Enable( pObj->GetNotesPointer() != NULL );
	else
		pCmdUI->Enable( FALSE );
}

afx_msg LONG ZIViewModify::ProcessCalculate( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	GetDocument()->CalculateAllFormula( this, TRUE );

	return 1;
}

afx_msg LONG ZIViewModify::OnProcessFieldEditNext( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject*			obj						= (PlanFinObject*)lParam;
	PlanFinObject*			NextEditObj				= NULL;
	double					CurrentEditedTabOrder	= obj->GetTabOrder();
	ZDDocumentReadWrite*	pDoc					= GetDocument();
	ASSERT( pDoc );

	if ( !pDoc->GetEditedObject() || !obj )
		return 1;

	// Retreive the current page
	int iPage;
    iPage = pDoc->GetCurrentPage();

	POSITION		Position;
	PlanFinObject  *objTemp = NULL;

	Position = pDoc->GetObjectList().GetHeadPosition();

	while ( Position != NULL )
	{
		objTemp = (PlanFinObject *)pDoc->GetObjectList().GetNext( Position );

		// If the same object continue;
		if ( obj == objTemp )
			continue;

		// Run throught objects and find the next
		// editable object within the same page
		if( iPage == objTemp->GetObjectPage() )
		{
			// Skip non editable object
			if ( objTemp->IsReadOnlyAtRuntime() || 
				 objTemp->GetIsStatic() ||
				 objTemp->IsKindOf( RUNTIME_CLASS( PLFNStatic ) ) ||
				 ( objTemp->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) && ( (PLFNLong*)objTemp )->IsCalculatedField() ) ||
				 objTemp->IsKindOf( RUNTIME_CLASS( PLFNCheck ) ) ||
				 objTemp->IsKindOf( RUNTIME_CLASS( PLFNRadio ) ) ||
				 objTemp->IsKindOf( RUNTIME_CLASS( PLFNLine ) ) ||
				 objTemp->IsKindOf( RUNTIME_CLASS( PLFNRect ) ) ||
				 objTemp->IsKindOf( RUNTIME_CLASS( PLFNNumbered ) ) )
			{
				continue;
			}

			// Test if the object in the list is greater than the edited tab order
			if ( objTemp->GetTabOrder() > CurrentEditedTabOrder )
			{
				// If an NextEditObj is defined and the object is greater than its tab order,
				// continue and do not assign the new pointer object.
				if ( NextEditObj && objTemp->GetTabOrder() > NextEditObj->GetTabOrder() )
					continue;
				
				NextEditObj = objTemp;
			}
		}
	}

	// If an object found
	if ( NextEditObj )
	{
		// translate the point in logical coordinates
		CDC *pDC = GetDC();
		ASSERT( pDC );
		OnPrepareDC( pDC );

		// Save the pointer to the object only
		// to be able to remove the flag later
		pDoc->SetEditedObject( NextEditObj );

		// Get the client rect and move the scroll bar
		// if necessary to see the edited object
		CRect		rect = NextEditObj->GetClientRect();
		pDC->LPtoDP( &rect );
		CPoint		MiddleObjectPoint( rect.left + ( rect.Width() / 2 ), rect.top + ( rect.Height() / 2 ) );
		CRect	WndRect;
		GetClientRect( &WndRect );
		
		if ( !WndRect.PtInRect( MiddleObjectPoint ) )
		{
			CPoint	DevicePoint = GetDeviceScrollPosition();
			MiddleObjectPoint.x = __max( 0, MiddleObjectPoint.x - WndRect.Width() );
			MiddleObjectPoint.y = __max( 0, MiddleObjectPoint.y - WndRect.Height() + 20 );
			pDC->DPtoLP( &MiddleObjectPoint );
			ScrollToPosition( MiddleObjectPoint );
			OnPrepareDC( pDC );
		}

		EditObject( NextEditObj );

		VERIFY( ReleaseDC( pDC ) );
	}

	return 1;
}

afx_msg LONG ZIViewModify::ProcessFieldChange( WPARAM wParam, LPARAM lParam )
{
	// To all document data
	if ( GetDocument() && lParam )
	{
		GetDocument()->PropagateFieldValue( (PlanFinObject*)lParam, -2 );
	}

	return 1;
}

afx_msg LONG ZIViewModify::OnEmptyObject( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject* obj = (PlanFinObject*)lParam;

	if ( obj )
	{
		SetFocus();
		obj->EmptyObject();
		obj->NotifyObjectHasChanged();
	}

	return 1;
}

afx_msg LONG ZIViewModify::OnWizardMenu( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject* obj = (PlanFinObject*)lParam;

	HINSTANCE hInst = AfxFindResourceHandle( MAKEINTRESOURCE ( IDR_WIZARDMENU ), RT_MENU );

	// Display the Wizard context menu
	HMENU	DummyMenu = ::LoadMenu( hInst, MAKEINTRESOURCE( IDR_WIZARDMENU ) );
	HMENU	SubMenu;
	ReleaseCapture();

	if ( obj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) && ( (PLFNLong*)obj )->IsCalculatedField() )
	{
		SubMenu = ::GetSubMenu( DummyMenu, 0 );
	}
	else if ( obj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
	{
		SubMenu = ::GetSubMenu( DummyMenu, 1 );
	}
	else if ( obj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) )
	{
		SubMenu = ::GetSubMenu( DummyMenu, 2 );
	}
	else
	{
		SubMenu = ::GetSubMenu( DummyMenu, 3 );
	}

	CPoint	point;
	::GetCursorPos( &point );

	// Set the object as selected
	obj->SelectObject();

	// Display the menu
	::TrackPopupMenu( SubMenu,
					  TPM_LEFTALIGN | TPM_RIGHTBUTTON,
					  point.x,
					  point.y,
					  0,
					  AfxGetMainWnd()->GetSafeHwnd(),
					  NULL );

	SetCapture();

	return 1;
}

afx_msg LONG ZIViewModify::OnCalendarObject( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject* obj = (PlanFinObject*)lParam;

	if ( obj )
	{
		CPoint point;
		::GetCursorPos( &point );
		ZICalendarWnd CalendarWnd( this );

		if ( CalendarWnd.HandleCalendar( point ) )
		{
			if ( obj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) )
				reinterpret_cast<PLFNTime*>( obj )->SetTimeValue( CalendarWnd.GetDate() );

			// To notify the view that on field change
			// Pass the adress of the object
			// then the routine that proceed the message
			// can know wich object has changed
			AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)obj );
			GetDocument()->SetModifiedFlag();
		}
	}

	return 1;
}

afx_msg LONG ZIViewModify::OnObjectProperty( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject* obj = (PlanFinObject*)lParam;

	if ( obj )
	{
		ZIProperty	Property( obj, obj->GetPropertyTabs(), PropertyTabGeneral );

		if ( Property.DoModal() == IDOK )
			GetDocument()->SetModifiedFlag();

		SetFocus();
	}

	return 1;
}

afx_msg LONG ZIViewModify::OnObjectNote( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject*	obj = (PlanFinObject*)lParam;

	if ( obj )
		AddObjectNotes( obj );

	return 1;
}

afx_msg LONG ZIViewModify::OnAssociationMenu( WPARAM wParam, LPARAM lParam )
{
	// Check read-only mode
	if ( !GetDocument() || GetDocument()->IsReadOnlyAtRuntime() )
		return 1;

	PlanFinObject*	obj = (PlanFinObject*)lParam;

	if ( obj )
	{
		CMenu AssociationMenu;
		AssociationMenu.CreatePopupMenu();

		CStringArray&	Array				= ( (PLFNLong*)obj )->GetAssociations().GetAssociationArray();
		UINT			uiMenuState;
		BOOL			bStandardFounded	= FALSE;

		for ( int i = 0; i < Array.GetSize(); ++i )
		{
			// Test if there is the standard schema in the array
			if ( GetDocument()->GetDefaultAssociationString() == Array[i] )
				bStandardFounded = TRUE;

			if ( ( (PLFNLong*)obj )->GetCurrentAssociation() &&
				 ( (PLFNLong*)obj )->GetCurrentAssociation()->GetAssociationName() == Array[i] )
			{
				uiMenuState = MF_DISABLED | MF_CHECKED | MF_GRAYED;
			}
			else
			{
				uiMenuState = MF_ENABLED;
			}

			AssociationMenu.AppendMenu( uiMenuState, MENU_COMMAND + i, Array[i] );
		}

		// If no standard schema, add it to the menu
		if ( !bStandardFounded )
		{
			if ( !( (PLFNLong*)obj )->GetCurrentAssociation() )
				uiMenuState = MF_DISABLED | MF_CHECKED | MF_GRAYED;
			else
				uiMenuState = MF_ENABLED;

			AssociationMenu.AppendMenu( uiMenuState, MENU_COMMAND + i, GetDocument()->GetDefaultAssociationString() );
		}

		CPoint	pt;
		::GetCursorPos( &pt );
		AssociationMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd() );
		AssociationMenu.DestroyMenu();
	}

	return 1;
}

afx_msg LONG ZIViewModify::OnMenuSelected( WPARAM wParam, LPARAM lParam )
{
	SetFocus();
	PlanFinObject  *pObj	= GetDocument()->GetSelectedObject();
	CStringArray&	Array	= ( (PLFNLong*)pObj )->GetAssociations().GetAssociationArray();

	// Test if the standard schema selected
	if ( Array.GetSize() == wParam - MENU_COMMAND )
	{
		if ( pObj )
			( (PLFNLong*)pObj )->SetCurrentAssociation( NULL );

		// Change the necessary calculated and number fields
		GetDocument()->ChangeFieldForCalculation();
		GetDocument()->UpdateAllViews( NULL );

		// Recalculate
		AfxGetMainWnd( )->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );
		return 1;
	}

	for ( int i = 0; i < Array.GetSize(); ++i )
	{
		if ( wParam == MENU_COMMAND + i )
		{
			if ( pObj )
				( (PLFNLong*)pObj )->SetCurrentAssociation( Array[i] );

			break;
		}
	}

	// Change the necessary calculated and number fields
	GetDocument()->ChangeFieldForCalculation();
	GetDocument()->UpdateAllViews( NULL );

	// Recalculate
	AfxGetMainWnd( )->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );

	return 1;
}

void ZIViewModify::OnSubmenu1Selectobject()
{
	// Do nothing.	
}

void ZIViewModify::OnSubmenu1Unselectobject()
{
	ZDDocument *pDoc = GetDocument();
	ASSERT( pDoc );
	PlanFinObject *obj;

	// Search wich element is selected
	if( ( obj = pDoc->GetHead() ) == NULL )
		return;

	do
	{
		if( obj->IsSelectObject() )
		{
			// translate the point in logical coordinates
			CDC *pDC = GetDC();
			ASSERT( pDC );
			OnPrepareDC( pDC );

			obj->SelectObject( this, pDC, FALSE );
			VERIFY( ReleaseDC( pDC ) );

			break;
		}
	}
	while( ( obj = pDoc->GetNext() ) != NULL );
}

void ZIViewModify::OnFieldPositionSize()
{
	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	ZIProperty Property( pObj, pObj->GetPropertyTabs(), PropertyTabSize );

	if ( Property.DoModal() == IDOK )
	{
		GetDocument()->SetModifiedFlag();
		UpdateWindow();
	}

	OnSubmenu1Unselectobject();
}

void ZIViewModify::OnFieldProperty()
{
	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	ZIProperty Property( pObj, pObj->GetPropertyTabs(), PropertyTabGeneral );

	if ( Property.DoModal() == IDOK )
	{
		GetDocument()->SetModifiedFlag();
		UpdateWindow();
	}

	OnSubmenu1Unselectobject();
}

afx_msg LONG ZIViewModify::OnClearSelectionAll( WPARAM wParam, LPARAM lParam )
{
	CDC *pDC = GetDC();
	ASSERT( pDC );
	OnPrepareDC( pDC );

	DeselectAllObject( this, pDC, GetDocument() );
	VERIFY( ReleaseDC( pDC ) );

	return( 1 );
}

afx_msg LONG ZIViewModify::OnPointerSelection( WPARAM wParam, LPARAM lParam )
{                                                
	TRACE( _T( " On Pointer In Selection ZIView 1 " ) );

	if ( ZAApp::ZAGetApp()->GetCurrentDocument() != GetDocument() || this->IsKindOf( RUNTIME_CLASS( ZIViewCode ) ) )
		return( 0 );
	
	CPoint*	point = (CPoint*)lParam;
	ScreenToClient( point );

	// translate the point in logical coordinates
	CDC *pDC = GetDC();
	ASSERT( pDC );
	OnPrepareDC( pDC );
	pDC->DPtoLP( point );      

	PlanFinObject* pObj = FindHitObject( *point );

	if ( m_pOldPointerSelectedObj && pObj != m_pOldPointerSelectedObj )
	{
		// Clear the old object
		m_pOldPointerSelectedObj->DisplayCodeName( pDC, this, FALSE, this );
		m_pOldPointerSelectedObj = NULL;
	}

	if ( pObj && pObj != m_pOldPointerSelectedObj )
	{
		pObj->DisplayCodeName( pDC, this );
		m_pOldPointerSelectedObj = pObj;
	}

	TRACE( _T( " On Pointer In Selection ZIView 2 " ) );
	VERIFY( ReleaseDC( pDC ) );

	return( 1 );
}

afx_msg LONG ZIViewModify::OnPointerHasSelected( WPARAM wParam, LPARAM lParam )
{
	if ( ZAApp::ZAGetApp()->GetCurrentDocument() != GetDocument() || IsKindOf( RUNTIME_CLASS( ZIViewCode ) ) )
		return( 0 );

	// translate the point in logical coordinates
	CDC *pDC = GetDC();
	ASSERT( pDC );
	OnPrepareDC( pDC );

	ZBFieldObserverMsg Msg( UM_NOTIFY_POINTEROBJSELECTED, m_pOldPointerSelectedObj );

	dynamic_cast<ZISubject*>( AfxGetMainWnd() )->NotifyAllObservers( &Msg );

	if ( m_pOldPointerSelectedObj )
	{
		// Clear the old object
		m_pOldPointerSelectedObj->DisplayCodeName( pDC, this, FALSE, this );
		m_pOldPointerSelectedObj = NULL;
	}

	VERIFY( ReleaseDC( pDC ) );

	return( 1 );
}

afx_msg LONG ZIViewModify::OnDeselectAllObjects( WPARAM wParam, LPARAM lParam )
{
	CDC *pDC = GetDC();
	ASSERT( pDC );
	OnPrepareDC( pDC );

	ZDDocument *pDoc = GetDocument();
	ASSERT( pDoc );

	PlanFinObject  *obj;

	// Search wich element is selected
	if( ( obj = pDoc->GetHead() ) == NULL )
		return( 1 );

	do
	{
		if( obj->IsSelectObject() )
			obj->SelectObject( this, pDC, FALSE );
	}
	while( ( obj = pDoc->GetNext() ) != NULL );

	VERIFY( ReleaseDC( pDC ) );

	return( 1 );
}

afx_msg LONG ZIViewModify::OnFieldEditNext ( UINT message, LONG wParam )
{
	return PostMessage( ID_PROCESS_FIELD_EDITNEXT, 0, wParam );
}

void ZIViewModify::OnInsertFile() 
{
	CString title;
	VERIFY( title.LoadString( IDS_SELECT_A_FILE ) );

	// set the "*.*" files filter
	CString strFilter;
	VERIFY( strFilter.LoadString( AFX_IDS_ALLFILTER ) );
	strFilter += (char)'\0';        // next string please
	strFilter += _T( "*.*" );
	strFilter += (char)'\0';        // last string

	ZIFileDialog	FileDialog( title, strFilter, 1 );

	if ( FileDialog.DoModal() == IDOK )
	{
		GetDocument()->InsertBinaryDocument( FileDialog.GetFilename() );
	}
}

void ZIViewModify::OnUpdateInsertFile( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( !GetDocument()->IsReadOnlyAtRuntime() );	
}

void ZIViewModify::OnWizardCreateFormula()
{
	ZDDocumentReadWrite *pDoc = GetDocument();
	ASSERT( pDoc );

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();
	ZIWizardFormulaCreation	dlgWizard( pObj );
	dlgWizard.DoModal();

	// Deselect the current object
	OnSubmenu1Unselectobject();
}

void ZIViewModify::OnSubmenu1Fontchange()
{
	PlanFinObject*	pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	LOGFONT			lf;            
	memset( &lf, 0, sizeof( LOGFONT ) );

	ZAFont* pFont = NULL;

	// If a font is already defined
	if ( pObj->GethFont() != NoFontDefined )
	{
  		pFont = GetDocument()->GetFontManager().GetFont( pObj->GethFont() );
  		pFont->GetObject( sizeof( LOGFONT ), &lf );
  	}

	// Init the dialog
	CFontDialog dlgFont( &lf, CF_EFFECTS|CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT );

	if ( pFont )
		dlgFont.m_cf.rgbColors = pFont->GetFontColor();

	// Display the dialog
	if( dlgFont.DoModal() == IDOK )
	{
		HandleFont	hFont = GetDocument()->GetFontManager().FindFont( &lf, dlgFont.GetColor() );

		if ( hFont == NoFontDefined )
		{
			ZAFont*	pNewFont = new ZAFont();
			pNewFont->Create( &lf, dlgFont.GetColor() );
			hFont = GetDocument()->GetFontManager().AddFont( pNewFont );
		}

		pObj->SethFont( hFont );

		// To notify the view that on field change
		// Pass the adress of the object
		// then the routine that proceed the message
		// can know wich object has changed
		AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

		// Updata all Views it's may be a little beat
		// longer but already the dialog should be repainted
		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnUpdateSubmenu1Fontchange( CCmdUI* pCmdUI )
{
}

void ZIViewModify::OnUpdateSubMenuFormat( CCmdUI* pCmdUI )
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		pCmdUI->Enable( TRUE );
		return;
	}

	// if Autonumbered, replace the pObj by the pointed object
	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		pObj = ( (PlanFinObject*)( (PLFNAutoNumbered*)pObj )->GetpObject() );

	// This Wizard is available for Long, Time and Auto Numbered fields
	pCmdUI->Enable ( pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) || 
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) );
}

void ZIViewModify::OnSubmenuFormat()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	int					iRetValue;
	BOOL				bCalculated = FALSE;

	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
	{
		if ( ( (PLFNLong*)pObj )->IsCalculatedField() )
			bCalculated = TRUE;
	}

	// Clone the object
	PlanFinObject* pTemporaryObject;
	
	// if Autonumbered, pass the pointed object
	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		pTemporaryObject = ( (PlanFinObject*)( (PLFNAutoNumbered*)pObj )->GetpObject() )->Clone();
	else
		pTemporaryObject = pObj->Clone();

	if ( pTemporaryObject == NULL )
		return;

	// Call the Wizard
	ZIWZFormat	dlgWizard( pTemporaryObject, NULL, TRUE );
		
	// Initialize variable
	dlgWizard.SetFieldValue( pTemporaryObject->GetFormatedObject( ) );

	if( ( iRetValue=dlgWizard.DoModal() ) == IDCANCEL )
	{
		delete pTemporaryObject;

		// Deselect all objects
		AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
		return;
	}

	// Set the changed variable
	pTemporaryObject->ConvertFormatedObject( dlgWizard.GetFieldValue() );

	// if Autonumbered, pass the pointed object
	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
	{
		( (PlanFinObject*)( (PLFNAutoNumbered*)pObj )->GetpObject() )->CopyObject( pTemporaryObject );
	}
	else
	{
		// Set the changed variable
		// Copy the temporary object
		// to the initial object
		pObj->CopyObject( pTemporaryObject );
	}

	delete pTemporaryObject;

	// To notify the view that on field change
	// Pass the adress of the object
	// then the routine that proceed the message
	// can know wich object has changed
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

	// Deselect all objects
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );

	// Updata all Views it's may be a little beat
	// longer but already the dialog should be repainted
	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->SetModifiedFlag( TRUE );
}

void ZIViewModify::OnUpdateSubmenuModifyFormula( CCmdUI* pCmdUI )
{
	PlanFinObject*	pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		pCmdUI->Enable( TRUE );
		return;
	}

	pCmdUI->Enable ( ( pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) && ( (PLFNLong*)pObj )->IsCalculatedField() ) );
}

void ZIViewModify::OnSubmenuModifyFormula()
{
	PlanFinObject*	pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );

	// Must be calculated number field
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
		return;

	// Must be calculated field
	if ( !( (PLFNLong*)pObj )->IsCalculatedField() )
		return;
	
	PlanFinObject* pTemporaryObject = pObj->Clone();

	if ( pTemporaryObject == NULL )
		return;

	ZIWZFormula	Formula( pTemporaryObject, NULL, TRUE );

	if ( Formula.DoModal() == IDCANCEL )
	{
		delete pTemporaryObject;
		return;
	}

	// Set the changed variable
	// Copy the temporary object
	// to the initial object
	pObj->CopyObject( pTemporaryObject );

	delete pTemporaryObject;
	
	// To notify the view that on field change
	// Pass the adress of the object
	// then the routine that proceed the message
	// can know wich object has changed
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

	if ( ZAApp::ZAGetApp()->IsAutoCalculate() )
		AfxGetMainWnd( )->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );

	// Updata all Views it's may be a little beat
	// longer but already the dialog should be repainted
	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->SetModifiedFlag( TRUE );
}

void ZIViewModify::OnUpdateSubmenuAlign( CCmdUI* pCmdUI )
{
	PlanFinObject*	pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		pCmdUI->Enable( TRUE );
		return;
	}

	// if Autonumbered, replace the pObj by the pointed object
	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		pObj = ( (PlanFinObject*)( (PLFNAutoNumbered*)pObj )->GetpObject() );

	// Test the class type for the wizard
	// not all class can be used for the wizard
	pCmdUI->Enable ( pObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) )		||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNBoundText ) )	||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNNumbEdit ) )	||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNString ) )		||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNNumHistory ) )	||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNNumbNumEdit ) )	||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) )		||
					 pObj->IsKindOf( RUNTIME_CLASS( PLFNStringHistory ) ) );
}

void ZIViewModify::OnSubmenuAlign()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// Clone the object
	PlanFinObject* pTemporaryObject;

	// if Autonumbered, pass the pointed object
	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		pTemporaryObject = ( (PlanFinObject*)( (PLFNAutoNumbered*)pObj )->GetpObject() )->Clone();
	else
		pTemporaryObject = pObj->Clone();
		
	if ( pTemporaryObject == NULL )
		return;

	// Call the Wizard
	ZIWZAlign dlgWizard( pTemporaryObject, NULL, TRUE );
		
	// Initialize variable
	if ( dlgWizard.DoModal() == IDCANCEL )
	{
		delete pTemporaryObject;

		// Deselect all objects
		AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
		return;
	}

	// if Autonumbered, pass the pointed object
	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
	{
		( (PlanFinObject*)( (PLFNAutoNumbered*)pObj )->GetpObject() )->CopyObject( pTemporaryObject );
	}
	else
	{
		// Set the changed variable
		// Copy the temporary object
		// to the initial object
		pObj->CopyObject( pTemporaryObject );
	}

	delete pTemporaryObject;

	// To notify the view that on field change
	// Pass the adress of the object
	// then the routine that proceed the message
	// can know wich object has changed
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

	// Deselect all objects
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );

	// Updata all Views it's may be a little beat
	// longer but already the dialog should be repainted
	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->SetModifiedFlag( TRUE );	
}

void ZIViewModify::OnSubmenuHidePrtObject()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	pObj->SetbMustBePrinted( !pObj->GetbMustBePrinted() );
	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->SetModifiedFlag();
}

void ZIViewModify::OnUpdateSubmenuHidePrtObject( CCmdUI* pCmdUI )
{
	PlanFinObject  *obj = GetDocument()->GetSelectedObject();

	if ( obj )
	{
		pCmdUI->Enable( obj->GetbIsVisible() );
		pCmdUI->SetCheck( !obj->GetbMustBePrinted() );
	}
}

void ZIViewModify::OnSubmenuObjectHide()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	pObj->SetbIsVisible( !pObj->GetbIsVisible() );
	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->SetModifiedFlag();
}

void ZIViewModify::OnUpdateSubmenuObjectHide( CCmdUI* pCmdUI )
{
	PlanFinObject *obj = GetDocument()->GetSelectedObject();

	if ( obj )
	{
		pCmdUI->Enable( obj->GetbMustBePrinted() );
		pCmdUI->SetCheck( !obj->GetbIsVisible() );
	}
}

void ZIViewModify::OnSubmenuChangeColor()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	ZIColorSelection ColorSelection( pObj->GetColor( this ) );
	ColorSelection.ChooseColor();

	if ( ColorSelection.ColorHasChanged() )
	{
		pObj->SetColor( ColorSelection.GetColor() );
		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnWizardFormat()
{
	ZDDocumentReadWrite	   *pDoc = GetDocument();
	ASSERT( pDoc );

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	ZIWizardFormatStart	dlgWizard;
	dlgWizard.DoModal();

	// Deselect the current object
	OnSubmenu1Unselectobject();
}

void ZIViewModify::OnWizardCalculated()
{
	ZDDocumentReadWrite *pDoc = GetDocument();
	ASSERT( pDoc );

	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) && ( (PLFNLong*)pObj )->IsCalculatedField() )
	{
		ZIWizardCalculated	dlgWizard;
		dlgWizard.DoModal();
	}

	// Deselect the current object
	OnSubmenu1Unselectobject();
}

void ZIViewModify::OnUpdateFieldAlignCenter( CCmdUI* pCmdUI )
{
	PlanFinObject *pObj = GetDocument()->GetEditedObject();

	if ( pObj )
		pCmdUI->SetCheck( ( pObj->GetJustify( GetDocument() ) & DT_CENTER) > 0 );
	else
		pCmdUI->SetCheck( FALSE );
}

void ZIViewModify::OnFieldAlignCenter()
{
	PlanFinObject *pObj = GetDocument()->GetEditedObject();

	if ( !pObj )
	{
		if ( !( pObj = GetDocument()->GetSelectedObject() ) )
		{
			// Call the selector tool
			pObj = ChooseObject();

			if ( pObj == NULL )
				return;
		}
	}

	pObj->SetJustify( pObj->GetJustify(GetDocument()) & ~DT_RIGHT | DT_CENTER );
	Invalidate( TRUE );
	GetDocument()->SetModifiedFlag( TRUE );
}

void ZIViewModify::OnUpdateFieldAlignLeft( CCmdUI* pCmdUI )
{
	PlanFinObject *pObj = GetDocument()->GetEditedObject();

	if ( pObj )
		pCmdUI->SetCheck( ( !( pObj->GetJustify( GetDocument() ) & DT_CENTER ) &&
						  !( pObj->GetJustify( GetDocument() ) & DT_RIGHT) ) );
	else
		pCmdUI->SetCheck( FALSE );
}

void ZIViewModify::OnFieldAlignLeft()
{
	PlanFinObject *pObj = GetDocument()->GetEditedObject();

	if ( !pObj )
	{
		if ( !( pObj = GetDocument()->GetSelectedObject() ) )
		{
			// Call the selector tool
			pObj = ChooseObject();

			if ( pObj == NULL )
				return;
		}
	}

	pObj->SetJustify( pObj->GetJustify( GetDocument() ) & ~DT_CENTER & ~DT_RIGHT );
	Invalidate( TRUE );
	GetDocument()->SetModifiedFlag( TRUE );
}

void ZIViewModify::OnUpdateFieldAlignRight( CCmdUI* pCmdUI )
{
	PlanFinObject *pObj = GetDocument()->GetEditedObject();

	if ( pObj )
		pCmdUI->SetCheck( ( pObj->GetJustify( GetDocument() ) & DT_RIGHT ) > 0 );
	else
		pCmdUI->SetCheck( FALSE );
}

void ZIViewModify::OnFieldAlignRight()
{
	PlanFinObject *pObj = GetDocument()->GetEditedObject();

	if ( !pObj )
	{
		if ( !( pObj = GetDocument()->GetSelectedObject() ) )
		{
			// Call the selector tool
			pObj = ChooseObject();

			if ( pObj == NULL )
				return;
		}
	}

	pObj->SetJustify( pObj->GetJustify( GetDocument() ) & ~DT_CENTER | DT_RIGHT );
	Invalidate( TRUE );
	GetDocument()->SetModifiedFlag( TRUE );
}

void ZIViewModify::OnFieldApplyRounded()
{
	PlanFinObject *pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );

	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
		return;

	if ( !( (PLFNLong*)pObj )->IsCalculatedField() )
		return;

	PlanFinObject* pTemporaryObject = pObj->Clone();

	if ( pTemporaryObject == NULL )
		return;

	ZIWZRounded	Rounded( pTemporaryObject, NULL, TRUE );

	if ( Rounded.DoModal() == IDCANCEL )
	{
		delete pTemporaryObject;
		return;
	}

	// Set the changed variable
	// Copy the temporary object
	// to the initial object
	pObj->CopyObject( pTemporaryObject );

	delete pTemporaryObject;
	
	// To notify the view that on field change
	// Pass the adress of the object
	// then the routine that proceed the message
	// can know wich object has changed
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

	if ( ZAApp::ZAGetApp()->IsAutoCalculate() )
		AfxGetMainWnd( )->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );

	// Updata all Views it's may be a little beat
	// longer but already the dialog should be repainted
	Invalidate( TRUE );
	GetDocument()->SetModifiedFlag( TRUE );
}

void ZIViewModify::OnSubmenuChangeFillcolor()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}
	
	ZIColorSelection ColorSelection( pObj->GetFillColor() );
	ColorSelection.ChooseColor();

	if ( ColorSelection.ColorHasChanged() )
	{
		pObj->SetFillColor( ColorSelection.GetColor() );
		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnChangeLineColor() 
{
	PlanFinObject*	pObj = GetDocument()->GetSelectedObject();

	if ( !pObj || !ISA( pObj, PLFNGraphic ) )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL || !ISA( pObj, PLFNGraphic ) )
			return;
	}
	
	ZIColorSelection ColorSelection( dynamic_cast<PLFNGraphic*>( pObj )->GetGraphicColor() );
	ColorSelection.ChooseColor();

	if ( ColorSelection.ColorHasChanged() )
	{
		dynamic_cast<PLFNGraphic*>( pObj )->SetGraphicColor( ColorSelection.GetColor() );

		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnSectionAlign()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// if Not Autonumbered, return
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		return;

	// Clone the object
	PlanFinObject* pTemporaryObject = ( (PLFNAutoNumbered*)pObj )->GetTextLevel().Clone();
	
	if ( pTemporaryObject == NULL )
		return;

	// Call the Wizard
	ZIWZAlign dlgWizard( pTemporaryObject, NULL, TRUE );
		
	// Initialize variable
	if ( dlgWizard.DoModal() == IDCANCEL )
	{
		delete pTemporaryObject;

		// Deselect all objects
		AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
		return;
	}

	// Set the changed variable
	// Copy the temporary object
	// to the initial object
	( (PLFNAutoNumbered*)pObj )->GetTextLevel().CopyObject( pTemporaryObject );

	delete pTemporaryObject;

	// To notify the view that on field change
	// Pass the adress of the object
	// then the routine that proceed the message
	// can know wich object has changed
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );

	// Updata all Views it's may be a little beat
	// longer but already the dialog should be repainted
	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->SetModifiedFlag( TRUE );	
}

void ZIViewModify::OnSectionChangeColor()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// if Not Autonumbered, return
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		return;

	// replace the pObj by the pointed object
	pObj = &( (PLFNAutoNumbered*)pObj )->GetTextLevel();

	ZIColorSelection ColorSelection( pObj->GetColor( this ) );
	ColorSelection.ChooseColor();

	if ( ColorSelection.ColorHasChanged() )
	{
		pObj->SetColor( ColorSelection.GetColor() );

		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnSectionChangeFillColor()
{
	PlanFinObject*	pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// if Not Autonumbered, return
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		return;

	// replace the pObj by the pointed object
	pObj = &( (PLFNAutoNumbered*)pObj )->GetTextLevel();
	
	ZIColorSelection ColorSelection( pObj->GetFillColor() );
	ColorSelection.ChooseColor();

	if ( ColorSelection.ColorHasChanged() )
	{
		pObj->SetFillColor( ColorSelection.GetColor() );

		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnSectionFontChange()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// if Not Autonumbered, return
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		return;

	// replace the pObj by the pointed object
	pObj = &( (PLFNAutoNumbered*)pObj )->GetTextLevel();
	
	LOGFONT lf;            
	memset( &lf, 0, sizeof( LOGFONT ) );

	ZAFont* pFont = NULL;

	// If a font is already defined
	if ( pObj->GethFont() != NoFontDefined )
	{
  		pFont = GetDocument()->GetFontManager().GetFont( pObj->GethFont() );
  		pFont->GetObject( sizeof( LOGFONT ), &lf );
  	}

	// Init the dialog
	CFontDialog dlgFont( &lf, CF_EFFECTS|CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT );

	if ( pFont )
		dlgFont.m_cf.rgbColors = pFont->GetFontColor();

	// Display the dialog
	if( dlgFont.DoModal() == IDOK )
	{
		HandleFont hFont = GetDocument()->GetFontManager().FindFont( &lf, dlgFont.GetColor() );

		if ( hFont == NoFontDefined )
		{
			ZAFont*	pNewFont = new ZAFont();

			pNewFont->Create( &lf, dlgFont.GetColor() );
			hFont = GetDocument()->GetFontManager().AddFont( pNewFont );
		}

		pObj->SethFont( hFont );

		// To notify the view that on field change
		// Pass the adress of the object
		// then the routine that proceed the message
		// can know wich object has changed
		AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pObj );

		// Updata all Views it's may be a little beat
		// longer but already the dialog should be repainted
		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag( TRUE );
	}

	// Deselect all objects
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
}

void ZIViewModify::OnSectionChangeStyle()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	// if Not Autonumbered, return
	if ( !pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
		return;

	// replace the pObj by the pointed object
	pObj = &( (PLFNAutoNumbered*)pObj )->GetTextLevel();
	
	ZISelectStyleDlg SelectStyleDlg;

	if ( SelectStyleDlg.DoModal() == IDOK )
	{
		pObj->SethStyle( SelectStyleDlg.GetSelectedStyle() );

		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag();
	}
}

void ZIViewModify::OnChangeBorder()
{
	PlanFinObject* pObj = GetDocument()->GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = ChooseObject();

		if ( pObj == NULL )
			return;
	}

	ZABorder*	pBorder						= pObj->GetpBorder();
	BOOL		NewBorderHasBeenAllocated	= FALSE;

	// No border defined for the object
	if ( !pBorder )
	{
		// If no border defined, allocates one
		NewBorderHasBeenAllocated	= TRUE;
		pBorder						= new ZABorder;

		pObj->SetpBorder( pBorder );
	}
	ZIBorderDefDlg	BorderDefDlg( pBorder );

	// Display the border dialog box
	if ( BorderDefDlg.DoModal() == IDCANCEL )
	{
		// If the user cancel the border definition
		// and one object has been temporarily allocated
		// delete it
		if ( NewBorderHasBeenAllocated )
		{
			delete pBorder;
			pObj->SetpBorder( NULL );
		}
	}
	else
	{
		GetDocument()->UpdateAllViews( NULL );
		GetDocument()->SetModifiedFlag();
	}
}

BOOL ZIViewModify::OnToolTipNeedText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
    BOOL		bHandledNotify	= FALSE;
    TOOLTIPTEXT	*pTTT			= (TOOLTIPTEXT *)pNMHDR;
	pTTT->hinst					= NULL;
	pTTT->lpszText				= NULL;

    CPoint CursorPos;
	VERIFY( ::GetCursorPos( &CursorPos ) );
    ScreenToClient( &CursorPos );

    CRect ClientRect;
    GetClientRect( ClientRect );

    // Make certain that the cursor is in the client rect, because the
    // mainframe also wants these messages to provide tooltips for the
    // toolbar.
    if ( ClientRect.PtInRect( CursorPos ) )
    {
		ClientToDoc( CursorPos );
		PlanFinObject*	pObject = FindHitObject( CursorPos );

        if ( pObject )
        {
            // Adjust the text by filling in TOOLTIPTEXT
			m_StrToolTip.ReleaseBuffer();
            m_StrToolTip = m_ToolTipTypeObject + ZBObjectUtility::GetClassName( pObject );

			if ( ZAApp::ZAGetApp()->GetFieldRepository() )
			{
				ZAObjectDefinition*	pObjectDefinition = NULL;
				pObjectDefinition = ZAApp::ZAGetApp()->GetFieldRepository()->FindField( pObject->GetObjectName() );

				if ( pObjectDefinition && !pObjectDefinition->GetHelpUserDescription().IsEmpty() )
				{
					m_StrToolTip += _T( "\n" );
					m_StrToolTip += pObjectDefinition->GetHelpUserDescription();
				}
			}

			if ( pObject->GetNotesPointer() )
			{
				m_StrToolTip += _T( "\n" ) + m_ToolTipNoteText;

				if ( !pObject->GetNotesPointer()->GetUsername().IsEmpty() )
					m_StrToolTip += _T( "[" ) + pObject->GetNotesPointer()->GetUsername() + _T( "]" );

				m_StrToolTip += _T( "\n" ) + pObject->GetNotesPointer()->GetComment();
			}

			pTTT->hinst		= NULL;
			pTTT->lpszText	= m_StrToolTip.GetBuffer( m_StrToolTip.GetLength() + 1 );

        }
        else
        {
			m_StrToolTip.ReleaseBuffer();
			m_StrToolTip.Empty();

			pTTT->hinst		= NULL;
			pTTT->lpszText	= NULL;
        }

		bHandledNotify = TRUE;
    }

	return bHandledNotify;
}

#endif

//## end module%3624CA420321.epilog
