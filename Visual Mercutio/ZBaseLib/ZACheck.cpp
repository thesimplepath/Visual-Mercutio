//## begin module%3373B18A0140.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3373B18A0140.cm

//## begin module%3373B18A0140.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%3373B18A0140.cp

//## Module: ZACheck%3373B18A0140; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZACheck.cpp

//## begin module%3373B18A0140.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3373B18A0140.additionalIncludes

//## begin module%3373B18A0140.includes preserve=yes
//## end module%3373B18A0140.includes

// ZACheck
#include "ZACheck.h"
//## begin module%3373B18A0140.declarations preserve=no
//## end module%3373B18A0140.declarations

//## begin module%3373B18A0140.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNCheck, PLFNTwoStates, def_Version)
//## end module%3373B18A0140.additionalDeclarations


// Class PLFNCheck 

PLFNCheck::PLFNCheck()
  //## begin PLFNCheck::PLFNCheck%.hasinit preserve=no
  //## end PLFNCheck::PLFNCheck%.hasinit
  //## begin PLFNCheck::PLFNCheck%.initialization preserve=yes
  //## end PLFNCheck::PLFNCheck%.initialization
{
  //## begin PLFNCheck::PLFNCheck%.body preserve=yes
  //## end PLFNCheck::PLFNCheck%.body
}

PLFNCheck::PLFNCheck(const PLFNCheck &right)
  //## begin PLFNCheck::PLFNCheck%copy.hasinit preserve=no
  //## end PLFNCheck::PLFNCheck%copy.hasinit
  //## begin PLFNCheck::PLFNCheck%copy.initialization preserve=yes
  //## end PLFNCheck::PLFNCheck%copy.initialization
{
  //## begin PLFNCheck::PLFNCheck%copy.body preserve=yes
  *this = right;
  //## end PLFNCheck::PLFNCheck%copy.body
}


PLFNCheck::~PLFNCheck()
{
  //## begin PLFNCheck::~PLFNCheck%.body preserve=yes
  //## end PLFNCheck::~PLFNCheck%.body
}


const PLFNCheck & PLFNCheck::operator=(const PLFNCheck &right)
{
  //## begin PLFNCheck::operator=%.body preserve=yes
	this->PLFNTwoStates::operator=( (inherited&)right );
	return *this;
  //## end PLFNCheck::operator=%.body
}



//## Other Operations (implementation)
const PLFNCheck& PLFNCheck::operator = (const PLFNCheck* right)
{
  //## begin PLFNCheck::operator =%863220179.body preserve=yes
	this->PLFNTwoStates::operator=( (inherited*)right );
	return *this;
  //## end PLFNCheck::operator =%863220179.body
}

PlanFinObject* PLFNCheck::Clone ()
{
  //## begin PLFNCheck::Clone%863220180.body preserve=yes
	PLFNCheck*	pObject = new PLFNCheck( *this );
	return pObject;
  //## end PLFNCheck::Clone%863220180.body
}

void PLFNCheck::Serialize (CArchive& ar)
{
  //## begin PLFNCheck::Serialize%863220181.body preserve=yes
	PLFNTwoStates::Serialize(ar);
  //## end PLFNCheck::Serialize%863220181.body
}

void PLFNCheck::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNCheck::DrawObject%863220182.body preserve=yes
	DrawFillObject( pDC, pView );
	CPen	pen;
  	CPen*	pOldPen = pDC->SelectObject( &GetGraphicPen( pen ) );
  	if (!GetbTextIsCtrl())
  	{
  		CRect	RectControl(m_rctObject);
		// Test if the control is on the right
		if (GetbLeftText())
	  		RectControl.left = RectControl.right - GetuSize();
	  	switch (GetCheckType())
	  	{
	  		case Rounded:
	  		{
	  			pDC->Ellipse( RectControl.left, RectControl.top, RectControl.left+GetuSize(), RectControl.top+GetuSize() );
	  			// Display a point
	  			if (GetbCheckState())
	  			{
	  				// Draw the hand check
	  				CPoint	EndPoint( RectControl.left + (GetuSize() / 2), RectControl.top+GetuSize() - (GetuSize() / 3) );
					pDC->MoveTo( RectControl.left, RectControl.top );
					pDC->LineTo( EndPoint );
					pDC->MoveTo( RectControl.left, RectControl.top+1 );
					pDC->LineTo( EndPoint );
		  			CRect	Rect( RectControl.left, RectControl.top, RectControl.left+GetuSize(), RectControl.top+GetuSize() );
		  			Rect.top -= (GetuSize() / 3);
		  			Rect.right += (GetuSize() / 6);
					pDC->MoveTo( Rect.right, Rect.top );
					pDC->LineTo( EndPoint.x - 1, EndPoint.y + 1 );
					pDC->MoveTo( Rect.right, Rect.top + 1 );
					pDC->LineTo( EndPoint.x - 1, EndPoint.y + 1);
		  		}
	  			
	  			break;
	  		}
	  		case Squared:
	  		{
				// Draw the square
				pDC->MoveTo( RectControl.left, RectControl.top );
				pDC->LineTo( RectControl.left, RectControl.top+GetuSize() );
				pDC->LineTo( RectControl.left+GetuSize(), RectControl.top+GetuSize() );
				pDC->LineTo( RectControl.left+GetuSize(), RectControl.top );
				pDC->LineTo( RectControl.left, RectControl.top );
				// Display a cross
	  			if (GetbCheckState())
	  			{
					pDC->MoveTo( RectControl.left+1, RectControl.top+1 );
					pDC->LineTo( RectControl.left+GetuSize()-1, RectControl.top+GetuSize()-1 );
					pDC->MoveTo( RectControl.left+GetuSize()-1, RectControl.top+1 );
					pDC->LineTo( RectControl.left+1, RectControl.top+GetuSize()-1 );
	  			}
	  			break;
	  		}
	  	}
	}
  	// Draw Text
  	if (GetbShowText())
  	{
		CFont	*OldFont;
		
		OldFont = pDC->SelectObject( GetFont(pView) );
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor( GetColor(pView) );  // text color
		pDC->SetTextAlign( TA_LEFT | TA_BASELINE );
		// If the text does not act as a control 
	  	if (!GetbTextIsCtrl() && !GetbLeftText())
			pDC->TextOut( m_rctObject.left+GetuSize() + GetOffsetText(), m_rctObject.top+GetuSize(), GetsText() );
		else
		{
			pDC->TextOut( m_rctObject.left, m_rctObject.top+GetuSize(), GetsText() );
  			if (GetbCheckState() && GetbTextIsCtrl())
  			{
				pDC->MoveTo( m_rctObject.left+1, m_rctObject.top );
				pDC->LineTo( m_rctObject.right, m_rctObject.bottom-1 );
				pDC->MoveTo( m_rctObject.right, m_rctObject.top );
				pDC->LineTo( m_rctObject.left+1, m_rctObject.bottom-1 );
  			}
		}
		pDC->SelectObject( OldFont );
  	}
	pDC->SelectObject( pOldPen );
	PlanFinObject::DrawObject( pDC, pView );
  //## end PLFNCheck::DrawObject%863220182.body
}

void PLFNCheck::EditObject (CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc)
{
  //## begin PLFNCheck::EditObject%863220183.body preserve=yes
  	SetbCheckState( !GetbCheckState() );
	if (pParentWnd->IsWindowVisible())
	{
		CRect	Rect( m_rctObject );
		Rect.InflateRect( GetuSize(), GetuSize() );
		InvalidateObjectRect( pDC, pParentWnd, &Rect );
	}
//	((ZDDocument*)pDoc)->SetModifiedFlag( TRUE );
//	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)this );
//	CWnd::GetDesktopWindow()->SendMessageToDescendants( ID_NOTIFY_OBJECTSELECTED, ID_NOTIFY_OBJECTSELECTED, (LPARAM)this );
  //## end PLFNCheck::EditObject%863220183.body
}

void PLFNCheck::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNCheck::CopyObject%863615079.body preserve=yes
	((PLFNCheck*)this)->PLFNCheck::operator=( (PLFNCheck*)pSrc );
  //## end PLFNCheck::CopyObject%863615079.body
}

// Additional Declarations
  //## begin PLFNCheck%3373B1310082.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNCheck diagnostics

#ifdef _DEBUG
void PLFNCheck::AssertValid() const
{
	CObject::AssertValid();
}

void PLFNCheck::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNCheck%3373B1310082.declarations
//## begin module%3373B18A0140.epilog preserve=yes
//## end module%3373B18A0140.epilog
