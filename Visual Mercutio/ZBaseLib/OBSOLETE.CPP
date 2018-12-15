// planfobj.cpp : implementation of the ZDDocumentDesign class
//

#include "stdafx.h"

#include "ZIView.h"
#include "obsolete.h"
#include "ZDDoc.h"
#include "zamath.h"
#include "draw.h"

#include <FLOAT.H>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNStringHistory, PLFNString, def_Version)
IMPLEMENT_SERIAL(PLFNCalculated, PLFNLong, def_Version)
IMPLEMENT_SERIAL(PLFNNumHistory, PLFNLong, def_Version)
IMPLEMENT_SERIAL(PLFNNumbered, PLFNStatic, def_Version)
IMPLEMENT_SERIAL(PLFNNumbEdit, PLFNString, def_Version)
IMPLEMENT_SERIAL(PLFNNumbNumEdit, PLFNLong, def_Version)
               


/////////////////////////////////////////////////////////////////////////////
// PLFNNumbered construction/destruction

PLFNNumbered::PLFNNumbered()
{
}
PLFNNumbered::PLFNNumbered(const PLFNNumbered &right)
{
      *this = right;
}

const PLFNNumbered & PLFNNumbered::operator=(const PLFNNumbered *right)
{
    this->PLFNStatic::operator=( (inherited*)right );
    m_iChapter = right->m_iChapter;            
    m_iParagraph = right->m_iParagraph;
    return *this;
}

const PLFNNumbered & PLFNNumbered::operator=(const PLFNNumbered &right)
{
    this->PLFNStatic::operator=( (inherited&)right );
    m_iChapter = right.m_iChapter;            
    m_iParagraph = right.m_iParagraph;
    return *this;
}


PlanFinObject* PLFNNumbered::Clone()
{
    PLFNNumbered*    pObject = new PLFNNumbered( *this );
    return pObject;
}

void PLFNNumbered::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNNumbered*)this)->PLFNNumbered::operator=( (PLFNNumbered*)pSrc );
}

PLFNNumbered::~PLFNNumbered()
{
}


void PLFNNumbered::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
    
    CFont    *OldFont;
    CSize     sizeText;
    char     szBuf[100];
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    pDC->SetBkMode(TRANSPARENT);
/*    
    if (GetColor() == -1)
        pDC->SetTextColor( GetFont()->GetFontColor() );  // text color
    else
        pDC->SetTextColor( GetColor() );  // text color
*/
    pDC->SetTextColor( GetColor(pView) );  // text color
    pDC->SetTextAlign( TA_LEFT | TA_BOTTOM );
    sizeText = pDC->GetTextExtent( m_Str, m_Str.GetLength() );
    m_rctObject.right = m_rctObject.left + sizeText.cx;
    // I change the alignement to bottom to remove the
    // alignement problem with different fonts
    // then I should change the calculation of the text area
    m_rctObject.top = m_rctObject.bottom - sizeText.cy;
//    pDC->TextOut( m_rctObject.left, m_rctObject.bottom, m_Str );
    // Format the chapter and paragraph number
    if( m_iParagraph )
        sprintf( szBuf, "%d.%d ", m_iChapter, m_iParagraph );
    else
        sprintf( szBuf, "%d ", m_iChapter );
    sizeText = pDC->GetTextExtent( szBuf, strlen( szBuf ) );
    pDC->TextOut( m_rctObject.left-sizeText.cx, m_rctObject.bottom, szBuf );

    FormatObject( m_Str );
    pDC->SetTextAlign( 0 );
    pDC->DrawText( GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );

    pDC->SelectObject( OldFont );
    
    PlanFinObject::DrawObject( pDC, pView );
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumbered serialization

void PLFNNumbered::Serialize(CArchive& ar)
{
    PLFNStatic::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << (WORD)m_iParagraph;
        ar << (WORD)m_iChapter;
    }
    else
    {    // Read the elements
        WORD    wTemp;
        ar >> wTemp;
        m_iParagraph = (int)wTemp;
        ar >> wTemp;
        m_iChapter = (int)wTemp;
    }
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumbered diagnostics

#ifdef _DEBUG
void PLFNNumbered::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNNumbered::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// PLFNNumbEdit construction/destruction

PLFNNumbEdit::PLFNNumbEdit()
{
}
PLFNNumbEdit::PLFNNumbEdit(const PLFNNumbEdit &right)
{
      *this = right;
}

const PLFNNumbEdit & PLFNNumbEdit::operator=(const PLFNNumbEdit *right)
{
    this->PLFNString::operator=( (inherited*)right );
    m_iChapter = right->m_iChapter;            
    m_iParagraph = right->m_iParagraph;
    return *this;
}

const PLFNNumbEdit & PLFNNumbEdit::operator=(const PLFNNumbEdit &right)
{
    this->PLFNString::operator=( (inherited&)right );
    m_iChapter = right.m_iChapter;            
    m_iParagraph = right.m_iParagraph;
    return *this;
}


PlanFinObject* PLFNNumbEdit::Clone()
{
    PLFNNumbEdit*    pObject = new PLFNNumbEdit( *this );
    return pObject;
}

void PLFNNumbEdit::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNNumbEdit*)this)->PLFNNumbEdit::operator=( (PLFNNumbEdit*)pSrc );
}

PLFNNumbEdit::~PLFNNumbEdit()
{
}


void PLFNNumbEdit::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
    
    CFont    *OldFont;
    CSize     sizeText;
    char     szBuf[100];
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextAlign( TA_LEFT | TA_BOTTOM );
/*    
    if (GetColor() == -1)
        pDC->SetTextColor( GetFont()->GetFontColor() );  // text color
    else
        pDC->SetTextColor( GetColor() );  // text color
*/        
    pDC->SetTextColor( GetColor(pView) );  // text color
    // Format the chapter and paragraph number
    if( m_iParagraph )
        sprintf( szBuf, "%d.%d ", m_iChapter, m_iParagraph );
    else
        sprintf( szBuf, "%d ", m_iChapter );
    sizeText = pDC->GetTextExtent( szBuf, strlen( szBuf ) );
    pDC->TextOut( m_rctObject.left-sizeText.cx, m_rctObject.bottom, szBuf );

    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        // Before displaying the object
        // format it
//        FormatObject( strFormated, m_Str );
        // BUG BUG BUG
        // I find a bug. 23/03/1995
        // In all string a space preceeds 
        // then to not remove all space and change the
        // design of the Financial Plan I move the
        // string with one space.
        FormatObject( m_Str );
        pDC->SetTextAlign( 0 );
        pDC->DrawText( GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );
//        pDC->DrawText( strFormated, -1, &m_rctObject, DT_LEFT | DT_BOTTOM | DT_SINGLELINE );
    }
    pDC->SelectObject( OldFont );
    
    PlanFinObject::DrawObject( pDC, pView );
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumbEdit serialization

void PLFNNumbEdit::Serialize(CArchive& ar)
{
    PLFNString::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << (WORD)m_iParagraph;
        ar << (WORD)m_iChapter;
    }
    else
    {    // Read the elements
        WORD    wTemp;
        ar >> wTemp;
        m_iParagraph = (int)wTemp;
        ar >> wTemp;
        m_iChapter = (int)wTemp;
    }
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumbEdit diagnostics

#ifdef _DEBUG
void PLFNNumbEdit::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNNumbEdit::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// PLFNNumbNumEdit construction/destruction

PLFNNumbNumEdit::PLFNNumbNumEdit()
{
}
PLFNNumbNumEdit::PLFNNumbNumEdit(const PLFNNumbNumEdit &right)
{
      *this = right;
}

const PLFNNumbNumEdit & PLFNNumbNumEdit::operator=(const PLFNNumbNumEdit *right)
{
    this->PLFNLong::operator=( (inherited*)right );
    m_iChapter = right->m_iChapter;            
    m_iParagraph = right->m_iParagraph;
    return *this;
}
                      
const PLFNNumbNumEdit & PLFNNumbNumEdit::operator=(const PLFNNumbNumEdit &right)
{
    this->PLFNLong::operator=( (inherited&)right );
    m_iChapter = right.m_iChapter;
    m_iParagraph = right.m_iParagraph;
    return *this;
}

                      
PlanFinObject* PLFNNumbNumEdit::Clone()
{
    PLFNNumbNumEdit*    pObject = new PLFNNumbNumEdit( *this );
    return pObject;
}

void PLFNNumbNumEdit::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNNumbNumEdit*)this)->PLFNNumbNumEdit::operator=( (PLFNNumbNumEdit*)pSrc );
}

PLFNNumbNumEdit::~PLFNNumbNumEdit()
{
}


void PLFNNumbNumEdit::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
    
    CFont    *OldFont;
    CSize     sizeText;
    char     szBuf[70];
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextAlign( TA_LEFT | TA_BOTTOM );
/*    
    if (GetColor() == -1)
        pDC->SetTextColor( GetFont()->GetFontColor() );  // text color
    else
        pDC->SetTextColor( GetColor() );  // text color
*/        
    pDC->SetTextColor( GetColor(pView) );  // text color
    // Format the chapter and paragraph number
    if( m_iParagraph )
        sprintf( szBuf, "%d.%d ", m_iChapter, m_iParagraph );
    else
        sprintf( szBuf, "%d ", m_iChapter );
    sizeText = pDC->GetTextExtent( szBuf, strlen( szBuf ) );
    pDC->TextOut( m_rctObject.left-sizeText.cx, m_rctObject.bottom, szBuf );

    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        // Before displaying the object
        // format it
        FormatObject( m_Long );
        // BUG BUG BUG
        // I find a bug. 23/03/1995
        // In all string a space preceeds 
        // then to not remove all space and change the
        // design of the Financial Plan I move the
        // string with one space.
        pDC->SetTextAlign( 0 );
        pDC->DrawText( GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );
//        pDC->TextOut( m_rctObject.left, m_rctObject.bottom, GetFormatedBuffer() );
//        pDC->DrawText( strFormated, -1, &m_rctObject, DT_LEFT | DT_BOTTOM | DT_SINGLELINE );
    }
    pDC->SelectObject( OldFont );
    
    PlanFinObject::DrawObject( pDC, pView );
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumbNumEdit serialization

void PLFNNumbNumEdit::Serialize(CArchive& ar)
{
    PLFNLong::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << (WORD)m_iParagraph;
        ar << (WORD)m_iChapter;
    }
    else
    {    // Read the elements
        WORD    wTemp;
        ar >> wTemp;
        m_iParagraph = (int)wTemp;
        ar >> wTemp;
        m_iChapter = (int)wTemp;
    }
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumbNumEdit diagnostics

#ifdef _DEBUG
void PLFNNumbNumEdit::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNNumbNumEdit::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// PLFNStringHistory construction/destruction

PLFNStringHistory::PLFNStringHistory()
{
}
PLFNStringHistory::PLFNStringHistory(const PLFNStringHistory &right)
{
      *this = right;
}

const PLFNStringHistory & PLFNStringHistory::operator=(const PLFNStringHistory *right)
{
    this->PLFNString::operator=( (inherited*)right );
    m_Str = right->m_Str;
    return *this;
}

const PLFNStringHistory & PLFNStringHistory::operator=(const PLFNStringHistory &right)
{
    this->PLFNString::operator=( (inherited&)right );
    m_Str = right.m_Str;
    return *this;
}

PlanFinObject* PLFNStringHistory::Clone()
{
    PLFNStringHistory*    pObject = new PLFNStringHistory( *this );
    return pObject;
}

void PLFNStringHistory::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNStringHistory*)this)->PLFNStringHistory::operator=( (PLFNStringHistory*)pSrc );
}

PLFNStringHistory::~PLFNStringHistory()
{
}

BOOL     PLFNStringHistory::IsSelected( const CPoint& point ) const
{
    return( m_rctObject.PtInRect( point ) );
}

/*
CStringArray&    PLFNStringHistory::GetInitialChoice()
{
    return PlanFinObject::GetHistoricValues();
}
*/



// GetContains --------------------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    19/12/1994
// Description    :    This function scan the line and retreive the object
//                    contains.
// Parameters    :    strLine            the string that contains the line.
//
// Return        :    Nothing.
//
//----------------------------------------------------------------------------
void    PLFNStringHistory::GetContains( CString& strLine )
{
    PLFNString::GetContains( strLine );
}


/////////////////////////////////////////////////////////////////////////////
// PLFNStringHistory serialization

void PLFNStringHistory::Serialize(CArchive& ar)
{
    PLFNString::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// PLFNStringHistory diagnostics

#ifdef _DEBUG
void PLFNStringHistory::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNStringHistory::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG







/////////////////////////////////////////////////////////////////////////////
// PLFNCalculated construction/destruction

PLFNCalculated::PLFNCalculated()
{
}
PLFNCalculated::PLFNCalculated(const PLFNCalculated &right)
{
      *this = right;
}

const PLFNCalculated & PLFNCalculated::operator=(const PLFNCalculated *right)
{
    this->PLFNLong::operator=( (inherited*)right );
    m_Long = right->m_Long;
    return *this;
}

const PLFNCalculated & PLFNCalculated::operator=(const PLFNCalculated &right)
{
    this->PLFNLong::operator=( (inherited&)right );
    m_Long = right.m_Long;
    return *this;
}


PlanFinObject* PLFNCalculated::Clone()
{
    PLFNCalculated*    pObject = new PLFNCalculated( *this );
    return pObject;
}

void PLFNCalculated::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNCalculated*)this)->PLFNCalculated::operator=( (PLFNCalculated*)pSrc );
}

PLFNCalculated::~PLFNCalculated()
{
}

// This function recalculate is own
// value
void     PLFNCalculated::Recalculate(ZDDocument* pDoc)
{
    // Find in the document the right formula for the
    // current field
    if (pDoc)
    {

        ZAFormula*    Formula = pDoc->GetFormula( GetObjectName() );
        if (Formula)
        {    
            Parser            prs;
            m_Long = prs.StringParser( (const char *)Formula->m_sExtractedFormula, &(pDoc->GetObjectList()) );
    //        if( ZAApp::ZAGetApp()->GetiRounded() && ApplyRounded() )
            // Function floor first integer less than
            // Function ceil first integer greater than
    //            m_Long = ceil( m_Long / (double)ZAApp::ZAGetApp()->GetiRounded() ) * (double)ZAApp::ZAGetApp()->GetiRounded();
        }
    }
}


// This function return the string
// represented the object formated 
// with the current format type
// Format with the time value
CString     PLFNCalculated::GetFormatedObject( )
{
    if ( IsEmpty() )
        FormatObject( (double)0 );
    else
        FormatObject( m_Long );
    CString        sValue( GetFormatedBuffer() );

    return sValue;
}



/////////////////////////////////////////////////////////////////////////////
// PLFNCalculated serialization

void PLFNCalculated::Serialize(CArchive& ar)
{
    PLFNLong::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// PLFNCalculated diagnostics

#ifdef _DEBUG
void PLFNCalculated::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNCalculated::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// PLFNNumHistory construction/destruction

PLFNNumHistory::PLFNNumHistory()
{
}
PLFNNumHistory::PLFNNumHistory(const PLFNNumHistory &right)
{
      *this = right;
}

const PLFNNumHistory & PLFNNumHistory::operator=(const PLFNNumHistory *right)
{
    this->PLFNLong::operator=( (inherited*)right );
    return *this;
}

const PLFNNumHistory & PLFNNumHistory::operator=(const PLFNNumHistory &right)
{
    this->PLFNLong::operator=( (inherited&)right );
    return *this;
}

PlanFinObject* PLFNNumHistory::Clone()
{
    PLFNNumHistory*    pObject = new PLFNNumHistory( *this );
    return pObject;
}

void PLFNNumHistory::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNNumHistory*)this)->PLFNNumHistory::operator=( (PLFNNumHistory*)pSrc );
}

PLFNNumHistory::~PLFNNumHistory()
{
}

BOOL     PLFNNumHistory::IsSelected( const CPoint& point ) const
{
    return( m_rctObject.PtInRect( point ) );
}

/*
CStringArray&    PLFNNumHistory::GetInitialChoice()
{
    return PlanFinObject::GetHistoricValues();
}
*/





// GetContains --------------------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    19/12/1994
// Description    :    This function scan the line and retreive the object
//                    contains.
// Parameters    :    strLine            the string that contains the line.
//
// Return        :    Nothing.
//
//----------------------------------------------------------------------------
void    PLFNNumHistory::GetContains( CString& strLine )
{
    PLFNLong::GetContains( strLine );
}


/////////////////////////////////////////////////////////////////////////////
// PLFNNumHistory serialization

void PLFNNumHistory::Serialize(CArchive& ar)
{
    PLFNLong::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// PLFNNumHistory diagnostics

#ifdef _DEBUG
void PLFNNumHistory::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNNumHistory::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG




