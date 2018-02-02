//## begin module%334FC46302F6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%334FC46302F6.cm

//## begin module%334FC46302F6.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%334FC46302F6.cp

//## Module: VTools%334FC46302F6; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\VTools.cpp

//## begin module%334FC46302F6.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302F6.additionalIncludes

//## begin module%334FC46302F6.includes preserve=yes
//## end module%334FC46302F6.includes

// VTools
#include "VTools.h"
//## begin module%334FC46302F6.declarations preserve=no
//## end module%334FC46302F6.declarations

//## begin module%334FC46302F6.additionalDeclarations preserve=yes
#include "ZDDoc.h"
#include "ZAGlobal.h"
//## end module%334FC46302F6.additionalDeclarations

// Class ZIVisualTool 

//## begin ZIVisualTool::CurrentToolType%334FC4620032.attr preserve=no  public: static ToolType {V} VToolEdit
ToolType ZIVisualTool::m_CurrentToolType = VToolEdit;
//## end ZIVisualTool::CurrentToolType%334FC4620032.attr

//## begin ZIVisualTool::ToolsList%334FC4620033.attr preserve=no  public: static CPtrList {V} 
CPtrList ZIVisualTool::m_ToolsList;
//## end ZIVisualTool::ToolsList%334FC4620033.attr

//## begin ZIVisualTool::DownPoint%334FC4620034.attr preserve=no  public: static CPoint {V} 
CPoint ZIVisualTool::m_DownPoint;
//## end ZIVisualTool::DownPoint%334FC4620034.attr

//## begin ZIVisualTool::LastPoint%334FC4620035.attr preserve=no  public: static CPoint {V} 
CPoint ZIVisualTool::m_LastPoint;
//## end ZIVisualTool::LastPoint%334FC4620035.attr

//## begin ZIVisualTool::nDownFlags%334FC4620036.attr preserve=no  public: static UINT {V} 
UINT ZIVisualTool::m_nDownFlags;
//## end ZIVisualTool::nDownFlags%334FC4620036.attr

//## begin ZIVisualTool::ToolMode%3546151F00B6.attr preserve=no  public: static VisualToolModes {U} NormalMode
VisualToolModes ZIVisualTool::m_ToolMode = NormalMode;
//## end ZIVisualTool::ToolMode%3546151F00B6.attr

//## begin ZIVisualTool::Rect%35461F590396.attr preserve=no  public: static CRect {U} 
CRect ZIVisualTool::m_Rect;
//## end ZIVisualTool::Rect%35461F590396.attr

ZIVisualTool::ZIVisualTool ( ToolType ObjectToolType )
	//## begin ZIVisualTool::ZIVisualTool%832040471.hasinit preserve=no
	//## end ZIVisualTool::ZIVisualTool%832040471.hasinit
	//## begin ZIVisualTool::ZIVisualTool%832040471.initialization preserve=yes
	//## end ZIVisualTool::ZIVisualTool%832040471.initialization
{
	//## begin ZIVisualTool::ZIVisualTool%832040471.body preserve=yes
	m_hcurNormal		= AfxGetApp()->LoadStandardCursor( IDC_ARROW );
	m_ObjectToolType	= ObjectToolType;

	m_ToolsList.AddTail( this );
	//## end ZIVisualTool::ZIVisualTool%832040471.body
}


ZIVisualTool::~ZIVisualTool()
{
	//## begin ZIVisualTool::~ZIVisualTool%.body preserve=yes
	//## begin ZIVisualTool::FindTool%832040472.body preserve=yes
	//## end ZIVisualTool::~ZIVisualTool%.body
}

//## Other Operations (implementation)
void ZIVisualTool::OnLButtonDown ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualTool::OnLButtonDown%832038253.body preserve=yes
	// deactivate any in-place active item on this view!
//	pView->SetCapture();
	m_nDownFlags	= nFlags;
	m_DownPoint		= point;
	m_LastPoint		= point;
	//## end ZIVisualTool::OnLButtonDown%832038253.body
}

void ZIVisualTool::OnLButtonDblClk ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualTool::OnLButtonDblClk%832038254.body preserve=yes
	//## end ZIVisualTool::OnLButtonDblClk%832038254.body
}

void ZIVisualTool::OnLButtonUp ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualTool::OnLButtonUp%832038255.body preserve=yes
	ReleaseCapture();

//	if (point == m_DownPoint)
//		m_CurrentToolType = VToolEdit;
	//## end ZIVisualTool::OnLButtonUp%832038255.body
}

void ZIVisualTool::OnMouseMove ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualTool::OnMouseMove%832038256.body preserve=yes
	m_LastPoint = point;
//	SetCursor( m_hcurNormal );
	//## end ZIVisualTool::OnMouseMove%832038256.body
}

void ZIVisualTool::OnCancel ()
{
	//## begin ZIVisualTool::OnCancel%832038257.body preserve=yes
	m_CurrentToolType = VToolEdit;
	//## end ZIVisualTool::OnCancel%832038257.body
}

ZIVisualTool* ZIVisualTool::FindTool ( ToolType ObjectToolType )
{
	//## begin ZIVisualTool::FindTool%832040472.body preserve=yes
	POSITION pos = m_ToolsList.GetHeadPosition();

	while ( pos != NULL )
	{
		ZIVisualTool* pTool = (ZIVisualTool*)m_ToolsList.GetNext( pos );

		if ( pTool->m_ObjectToolType == ObjectToolType )
			return pTool;
	}

	return NULL;
	//## end ZIVisualTool::FindTool%832040472.body
}

// Additional Declarations

//## begin ZIVisualTool%334FC46103DF.declarations preserve=yes
//## end ZIVisualTool%334FC46103DF.declarations

// Class ZIVisualToolEdit 

ZIVisualToolEdit::ZIVisualToolEdit()
	//## begin ZIVisualToolEdit::ZIVisualToolEdit%.hasinit preserve=no
	//## end ZIVisualToolEdit::ZIVisualToolEdit%.hasinit
	//## begin ZIVisualToolEdit::ZIVisualToolEdit%.initialization preserve=yes
	: ZIVisualTool(VToolEdit)
	//## end ZIVisualToolEdit::ZIVisualToolEdit%.initialization
{
	//## begin ZIVisualToolEdit::ZIVisualToolEdit%.body preserve=yes
	HINSTANCE hInst	= AfxFindResourceHandle( MAKEINTRESOURCE ( IDC_EDITABLE ), RT_GROUP_CURSOR );
	m_hcurEdit		= ::LoadCursor( hInst, MAKEINTRESOURCE ( IDC_EDITABLE ) );
	//## end ZIVisualToolEdit::ZIVisualToolEdit%.body
}

ZIVisualToolEdit::~ZIVisualToolEdit()
{
	//## begin ZIVisualToolEdit::~ZIVisualToolEdit%.body preserve=yes
	//## end ZIVisualToolEdit::~ZIVisualToolEdit%.body
}

//## Other Operations (implementation)
void ZIVisualToolEdit::OnLButtonDown ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualToolEdit::OnLButtonDown%832038253.body preserve=yes

	// Check read-only mode
	if ( !pView->GetDocument() || pView->GetDocument()->IsReadOnlyAtRuntime() )
		return;

	CPoint local = point;
	pView->ClientToDoc( local );
	
	ZDDocument*	pDoc = pView->GetDocument();
	ASSERT( pDoc );

	// Run thought the list of object
	// and detect if the cursor in
	// on one object
	PlanFinObject  *obj;

	// Retreive the current page
	int iPage;
    iPage = pDoc->GetCurrentPage();

	// Search wich element is selected
	if( ( obj=pDoc->GetHead() ) == NULL )
		return;

	do
	{
		// If we are on the right page and on the object
		if ( iPage == obj->GetObjectPage() && obj->IsSelected( local ) )
		{
			switch ( pView->GetViewType() )
			{
				case FormModifyView:
				{
					// If the cursor is on the object
					if ( !obj->IsReadOnlyAtRuntime() )
					{
						if ( !obj->IsSelectObject() && !obj->GetIsStatic() )
						{
							// Save the pointer to the object only
							// to be able to remove the flag later
							pDoc->SetEditedObject( obj );
							pView->EditObject( obj );
						}
					}

					break;
				}

				case FormDesignView:
				{
					// If the cursor is on the object
					if ( !obj->IsSelectObject() )
					{
						// Save the pointer to the object only
						// to be able to remove the flag later
						pDoc->SetEditedObject( obj );
						pView->EditObject( obj );
					}

					break;
				}

				// Default, do nothing
				default: break;
			}	// End switch

			break;	// We do or not the right processing
		}
	}
	while( ( obj=pDoc->GetNext() ) != NULL );

	// Set the focus to this view
	// This one is required for the
	// Edit control. With this one all
	// Edit control loose the focus and
	// save the buffer. Otherwise the caret
	// still running in the Edit control.
	if ( !obj )
		pView->SetFocus();
	//## end ZIVisualToolEdit::OnLButtonDown%832038253.body
}

void ZIVisualToolEdit::OnLButtonUp ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualToolEdit::OnLButtonUp%832038255.body preserve=yes
	ZIVisualTool::OnLButtonUp( pView, nFlags, point );
	//## end ZIVisualToolEdit::OnLButtonUp%832038255.body
}

void ZIVisualToolEdit::OnMouseMove ( ZIView* pView, UINT nFlags, const CPoint& point )
{
  //## begin ZIVisualToolEdit::OnMouseMove%832038256.body preserve=yes
	CWnd* pActiveWnd = pView->GetActiveWindow();

	if ( !pActiveWnd || !pActiveWnd->IsChild( pView ) ) // also check for NULL for Win32
		return;

	CPoint local = point;
	pView->ClientToDoc( local );

	// Check read-only mode
	if ( !pView->GetDocument() || pView->GetDocument()->IsReadOnlyAtRuntime() )
	{
		ZIVisualTool::OnMouseMove( pView, nFlags, local );

		if ( ::IsWindow( pView->GetToolTip().m_hWnd ) )
			// Use Activate() to hide the tooltip.
			pView->GetToolTip().Activate( FALSE );

		return;
	}
	// Reader view cannot change anything.
	if ( pView->GetViewType() != FormReadView )
	{
  		BOOL bReleaseCapture = FALSE;

		if ( ZAGlobal::ShowAnimation() )
		{
			ZDDocument*	pDoc = pView->GetDocument();
			ASSERT( pDoc );

//			if (/*ZAApp::ZAGetApp()->IsCursorCapturedValid( local, pView )*/)
//			{
				// Run thought the list of object
				// and detect if the cursor in
				// on one object
				PlanFinObject  *obj;

				// Retreive the current page
				int iPage;
				iPage = pDoc->GetCurrentPage();

				// Search wich element is selected
				if( ( obj=pDoc->GetHead() ) != NULL )
				{
					do
					{
						// If we are on the right page and on the object
						if ( iPage == obj->GetObjectPage() && obj->IsSelected( local ) )
						{
							switch ( pView->GetViewType() )
							{
								case FormModifyView:
								{
									// If the cursor is on the object
									if ( !obj->IsReadOnlyAtRuntime() )
									{
										if ( !obj->IsSelectObject() && !obj->GetIsStatic() )
										{
											pView->SetCapture();
											if ( GetCursor() !=  m_hcurEdit )
												SetCursor( m_hcurEdit );

											if ( ::IsWindow( pView->GetToolTip().m_hWnd ) )
												// Use Activate() to hide the tooltip.
												pView->GetToolTip().Activate( TRUE );

											return;
										}
									}

									break;
								}

								case FormDesignView:
								{
									// If the cursor is on the object
									if ( !obj->IsSelectObject() )
									{
										pView->SetCapture();
										if ( GetCursor() !=  m_hcurEdit )
											SetCursor( m_hcurEdit );
									}

									if ( ::IsWindow( pView->GetToolTip().m_hWnd ) )
										// Use Activate() to hide the tooltip.
										pView->GetToolTip().Activate( TRUE );

									return;
								}

								// Default, do nothing
								default: break;
							}	// End switch

							break;	// We do or not the right processing
						}
					}
					while( ( obj = pDoc->GetNext() ) != NULL );
				}
//			}
		}
		ZIVisualTool::OnMouseMove( pView, nFlags, local );
	}

	if ( ::IsWindow( pView->GetToolTip().m_hWnd ) )
		// Use Activate() to hide the tooltip.
		pView->GetToolTip().Activate( FALSE );

	ReleaseCapture();
	//## end ZIVisualToolEdit::OnMouseMove%832038256.body
}

// Additional Declarations
  //## begin ZIVisualToolEdit%334FC4620038.declarations preserve=yes
  //## end ZIVisualToolEdit%334FC4620038.declarations

// Class ZIVisualToolObjectCreator 

ZIVisualToolObjectCreator::ZIVisualToolObjectCreator ( ToolType ObjectToolType )
	//## begin ZIVisualToolObjectCreator::ZIVisualToolObjectCreator%833838851.hasinit preserve=no
	: m_CreationStarted	( FALSE ),
	//## end ZIVisualToolObjectCreator::ZIVisualToolObjectCreator%833838851.hasinit
	//## begin ZIVisualToolObjectCreator::ZIVisualToolObjectCreator%833838851.initialization preserve=yes
	  ZIVisualTool		( ObjectToolType )
	//## end ZIVisualToolObjectCreator::ZIVisualToolObjectCreator%833838851.initialization
{
	//## begin ZIVisualToolObjectCreator::ZIVisualToolObjectCreator%833838851.body preserve=yes
	m_hcurCreation = AfxGetApp()->LoadCursor( IDC_NEWOBJECT );
	//## end ZIVisualToolObjectCreator::ZIVisualToolObjectCreator%833838851.body
}

ZIVisualToolObjectCreator::~ZIVisualToolObjectCreator()
{
  //## begin ZIVisualToolObjectCreator::~ZIVisualToolObjectCreator%.body preserve=yes
  //## end ZIVisualToolObjectCreator::~ZIVisualToolObjectCreator%.body
}

//## Other Operations (implementation)
void ZIVisualToolObjectCreator::OnLButtonDown ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualToolObjectCreator::OnLButtonDown%832038253.body preserve=yes
	// Check read-only mode
	if ( !pView->GetDocument() || pView->GetDocument()->IsReadOnlyAtRuntime() )
		return;

	CPoint local = point;
	pView->ClientToDoc( local );
	
	ZIVisualTool::OnLButtonDown( pView, nFlags, local );
	m_CreationStarted = TRUE;
	pView->SetCapture();
	//## end ZIVisualToolObjectCreator::OnLButtonDown%832038253.body
}

void ZIVisualToolObjectCreator::OnLButtonUp ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualToolObjectCreator::OnLButtonUp%832038255.body preserve=yes
	CPoint local = point;
	pView->ClientToDoc( local );

	ZIVisualTool::OnLButtonUp( pView, nFlags, local );

    // If in multiple selection, then clear the rectangle
    // used for multiple selection.
	if ( m_CreationStarted )
    {
        CClientDC 	TempDC( pView );
		pView->OnPrepareDC( &TempDC );
        CRect		rect( m_DownPoint.x, m_DownPoint.y, m_LastPoint.x, m_LastPoint.y );
	    TempDC.SetROP2( R2_NOTXORPEN );
	    CPen	Pen( PS_DOT, 1, defCOLOR_RED );
	    CPen*	pOldPen;
	    pOldPen = TempDC.SelectObject( &Pen );
        TempDC.Rectangle( rect );
        TempDC.SelectObject( pOldPen );
    	m_LastPoint = local;  
		m_CreationStarted = FALSE;

		// Check if the rect is enough bigger to create an object
		if ( rect.Width() > 2 && rect.Height() > 1 )
		{
			rect.NormalizeRect();

			// Assigns the rectangle
		  	m_Rect = rect;
			CreateObject( rect );
		}

		ZDDocument*	pDoc = pView->GetDocument();
		ASSERT( pDoc );

		// The position have changed
		pDoc->SetModifiedFlag( TRUE );
	}

	ReleaseCapture();
	//## end ZIVisualToolObjectCreator::OnLButtonUp%832038255.body
}

void ZIVisualToolObjectCreator::OnMouseMove ( ZIView* pView, UINT nFlags, const CPoint& point )
{
	//## begin ZIVisualToolObjectCreator::OnMouseMove%832038256.body preserve=yes
	CPoint local = point;
	pView->ClientToDoc( local );

	CWnd* pActiveWnd = pView->GetActiveWindow();
	if ( pActiveWnd && pActiveWnd->IsChild( pView ) )// also check for NULL for Win32
	{
//		if (ZAApp::ZAGetApp()->IsCursorCapturedValid( local, pView ))
			if ( GetCursor() !=  m_hcurCreation )
				SetCursor( m_hcurCreation );

		// If is in creation draw a rectangle
	    // from the initial point to the current point
		if ( m_CreationStarted )
	    {
	        CClientDC 	TempDC( pView );
			pView->OnPrepareDC( &TempDC );
	        CRect		rect( m_DownPoint.x, m_DownPoint.y, m_LastPoint.x, m_LastPoint.y );
		    TempDC.SetROP2( R2_NOTXORPEN );
		    CPen	Pen( PS_DOT, 1, defCOLOR_RED );
		    CPen*	pOldPen;
		    pOldPen = TempDC.SelectObject( &Pen );
	        TempDC.Rectangle( rect );
	        
			ZIVisualTool::OnMouseMove( pView, nFlags, local );
		    rect = CRect( m_DownPoint.x, m_DownPoint.y, m_LastPoint.x, m_LastPoint.y );
	        TempDC.Rectangle( rect );
	        TempDC.SelectObject( pOldPen );
	    }
	}
	//## end ZIVisualToolObjectCreator::OnMouseMove%832038256.body
}

// Additional Declarations
//## begin ZIVisualToolObjectCreator%334FC462007F.declarations preserve=yes
//## end ZIVisualToolObjectCreator%334FC462007F.declarations

//## begin module%334FC46302F6.epilog preserve=yes
//## end module%334FC46302F6.epilog

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZIVisualToolSelection::ZIVisualToolSelection%.initialization preserve=no
	, ZIVisualTool( VToolSelect )
//## end ZIVisualToolSelection::ZIVisualToolSelection%.initialization

//## begin ZIVisualToolSelection::ZIVisualToolSelection%.body preserve=no
	m_hcurSelect = AfxGetApp()->LoadCursor( IDC_DESIGN );
//## end ZIVisualToolSelection::ZIVisualToolSelection%.body

//## begin ZIVisualToolDesignEdit::ZIVisualToolDesignEdit%.initialization preserve=no
  : ZIVisualTool( VToolDesignEdit )
//## end ZIVisualToolDesignEdit::ZIVisualToolDesignEdit%.initialization

#endif
