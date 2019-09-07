//## begin module%334FC46302ED.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302ED.cm

//## begin module%334FC46302ED.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302ED.cp

//## Module: ZAText%334FC46302ED; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\PLANFIN\ZAText.cpp

//## begin module%334FC46302ED.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302ED.additionalIncludes

//## begin module%334FC46302ED.includes preserve=yes
//## end module%334FC46302ED.includes

// ZAText
#include "ZAText.h"
//## begin module%334FC46302ED.declarations preserve=no
//## end module%334FC46302ED.declarations

//## begin module%334FC46302ED.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNText, PSS_PLFNAscii, g_DefVersion)
//## end module%334FC46302ED.additionalDeclarations


// Class PLFNText 



PLFNText::PLFNText()
  //## begin PLFNText::PLFNText%.hasinit preserve=no
      : m_IsStatic(FALSE)
  //## end PLFNText::PLFNText%.hasinit
  //## begin PLFNText::PLFNText%.initialization preserve=yes
  //## end PLFNText::PLFNText%.initialization
{
  //## begin PLFNText::PLFNText%.body preserve=yes
  //## end PLFNText::PLFNText%.body
}

PLFNText::PLFNText(const PLFNText &right)
  //## begin PLFNText::PLFNText%copy.hasinit preserve=no
      : m_IsStatic(FALSE)
  //## end PLFNText::PLFNText%copy.hasinit
  //## begin PLFNText::PLFNText%copy.initialization preserve=yes
  //## end PLFNText::PLFNText%copy.initialization
{
  //## begin PLFNText::PLFNText%copy.body preserve=yes
  *this = right;
  //## end PLFNText::PLFNText%copy.body
}


PLFNText::~PLFNText()
{
  //## begin PLFNText::~PLFNText%.body preserve=yes
  //## end PLFNText::~PLFNText%.body
}


const PLFNText & PLFNText::operator=(const PLFNText &right)
{
  //## begin PLFNText::operator=%.body preserve=yes
    this->PSS_PLFNAscii::operator=( (inherited&)right );
    m_Str = right.m_Str;
      m_IsStatic = right.m_IsStatic;
    return *this;
  //## end PLFNText::operator=%.body
}



//## Other Operations (implementation)
const PLFNText& PLFNText::operator = (const PLFNText* right)
{
  //## begin PLFNText::operator =%829516133.body preserve=yes
    this->PSS_PLFNAscii::operator=( (inherited*)right );
    m_Str = right->m_Str;
      m_IsStatic = right->m_IsStatic;
    return *this;
  //## end PLFNText::operator =%829516133.body
}

CString PLFNText::GetFormattedObject ()
{
  //## begin PLFNText::GetFormattedObject%829516158.body preserve=yes
    return m_Str;
  //## end PLFNText::GetFormattedObject%829516158.body
}

BOOL PLFNText::ConvertFormattedObject (const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero)
{
  //## begin PLFNText::ConvertFormattedObject%829516157.body preserve=yes
    // Has changed ???
      BOOL    RetValue = (m_Str != sValue) ? TRUE : FALSE;
    // Assign the new string
      m_Str = sValue;
    (m_Str.IsEmpty() == TRUE) ?    EmptyObject() : ClearEmptyObjectFlag();
    return RetValue;
  //## end PLFNText::ConvertFormattedObject%829516157.body
}

void PLFNText::Serialize (CArchive& ar)
{
  //## begin PLFNText::Serialize%829516183.body preserve=yes
    PSS_PLFNAscii::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        // Check if template file but not static element.
        // If static, serialize it.
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetFileType() == PSS_Stamp::IE_FD_TemplateType &&
            !GetIsStatic() && !GetDefaultValue())
        {
            CString str(m_Str);
            m_Str = "";
            ar << m_Str;
            m_Str = str;
        }
        else
            ar << m_Str;
            
        ar << (WORD)m_IsStatic;
    }
    else
    {    // Read the elements
        ar >> m_Str;
          
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            WORD    wTemp;
              ar >> wTemp;
            m_IsStatic = (BOOL)wTemp;
        }
        // Before version 12
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 12)
        {
            m_IsEmpty = m_Str.IsEmpty();
        }
    }
  //## end PLFNText::Serialize%829516183.body
}

void PLFNText::GetContains (const CString& line)
{
  //## begin PLFNText::GetContains%831692953.body preserve=yes
    int            iIndex;
    
    // Extract object Name    
    if( (iIndex=line.ReverseFind(',')) == -1 )
        return;

    // Extract the iX
    int        iPos = line.GetLength()-iIndex-2;
    if( iPos > 0 )
        m_Str = line.Right( iPos );
  //## end PLFNText::GetContains%831692953.body
}

PlanFinObject* PLFNText::Clone ()
{
  //## begin PLFNText::Clone%849755977.body preserve=yes
    PLFNText*    pObject = new PLFNText( *this );
    return pObject;
  //## end PLFNText::Clone%849755977.body
}

void PLFNText::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNText::CopyObject%863615082.body preserve=yes
    ((PLFNText*)this)->PLFNText::operator=( (PLFNText*)pSrc );
  //## end PLFNText::CopyObject%863615082.body
}

CString PLFNText::GetUnformattedObject ()
{
  //## begin PLFNText::GetUnformattedObject%901298463.body preserve=yes
    return m_Str;
  //## end PLFNText::GetUnformattedObject%901298463.body
}

// Additional Declarations
  //## begin PLFNText%334FC46102A4.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNText diagnostics

#ifdef _DEBUG
void PLFNText::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNText::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNText%334FC46102A4.declarations
//## begin module%334FC46302ED.epilog preserve=yes
//## end module%334FC46302ED.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin PLFNText::PLFNText%829516132.initialization preserve=no
    , PLFNAscii( cpIniString )
//## end PLFNText::PLFNText%829516132.initialization

//## begin PLFNText::PLFNText%829516132.body preserve=no
    GetContains( cpIniString );
//## end PLFNText::PLFNText%829516132.body

#endif
