//## begin module%351388810028.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%351388810028.cm

//## begin module%351388810028.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%351388810028.cp

//## Module: ZATwoSts%351388810028; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\PLANFIN\ZATwoSts.cpp

//## begin module%351388810028.additionalIncludes preserve=no
#include "StdAfx.h"
//## end module%351388810028.additionalIncludes

//## begin module%351388810028.includes preserve=yes
//## end module%351388810028.includes

// ZATwoSts
#include "ZATwoSts.h"
//## begin module%351388810028.declarations preserve=no
//## end module%351388810028.declarations

//## begin module%351388810028.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNTwoStates, PLFNGraphic, g_DefVersion)
//## end module%351388810028.additionalDeclarations


// Class PLFNTwoStates 









PLFNTwoStates::PLFNTwoStates()
  //## begin PLFNTwoStates::PLFNTwoStates%.hasinit preserve=no
      : m_CheckType(E_CB_Rounded), m_bCheckState(FALSE), m_bShowText(TRUE), m_bTextIsCtrl(FALSE), m_OffsetText(10), m_bLeftText(FALSE)
  //## end PLFNTwoStates::PLFNTwoStates%.hasinit
  //## begin PLFNTwoStates::PLFNTwoStates%.initialization preserve=yes
  , m_uSize( 10 )
  //## end PLFNTwoStates::PLFNTwoStates%.initialization
{
  //## begin PLFNTwoStates::PLFNTwoStates%.body preserve=yes
  //## end PLFNTwoStates::PLFNTwoStates%.body
}

PLFNTwoStates::PLFNTwoStates(const PLFNTwoStates &right)
  //## begin PLFNTwoStates::PLFNTwoStates%copy.hasinit preserve=no
      : m_CheckType(E_CB_Rounded), m_bCheckState(FALSE), m_bShowText(TRUE), m_bTextIsCtrl(FALSE), m_OffsetText(10), m_bLeftText(FALSE)
  //## end PLFNTwoStates::PLFNTwoStates%copy.hasinit
  //## begin PLFNTwoStates::PLFNTwoStates%copy.initialization preserve=yes
  //## end PLFNTwoStates::PLFNTwoStates%copy.initialization
{
  //## begin PLFNTwoStates::PLFNTwoStates%copy.body preserve=yes
  *this = right;
  //## end PLFNTwoStates::PLFNTwoStates%copy.body
}


PLFNTwoStates::~PLFNTwoStates()
{
  //## begin PLFNTwoStates::~PLFNTwoStates%.body preserve=yes
  //## end PLFNTwoStates::~PLFNTwoStates%.body
}


const PLFNTwoStates & PLFNTwoStates::operator=(const PLFNTwoStates &right)
{
  //## begin PLFNTwoStates::operator=%.body preserve=yes
    this->PLFNGraphic::operator=( (inherited&)right );
    m_CheckType = right.m_CheckType;
    m_uSize = right.m_uSize;
    m_bCheckState = right.m_bCheckState;
      m_bShowText = right.m_bShowText;
      m_bTextIsCtrl = right.m_bTextIsCtrl;
      m_sText = right.m_sText;
    m_OffsetText = right.m_OffsetText;
    m_bLeftText = right.m_bLeftText;
    return *this;
  //## end PLFNTwoStates::operator=%.body
}



//## Other Operations (implementation)
const PLFNTwoStates& PLFNTwoStates::operator = (const PLFNTwoStates* right)
{
  //## begin PLFNTwoStates::operator =%890472640.body preserve=yes
    this->PLFNGraphic::operator=( (inherited*)right );
    m_CheckType = right->m_CheckType;
    m_uSize = right->m_uSize;
    m_bCheckState = right->m_bCheckState;
      m_bShowText = right->m_bShowText;
      m_bTextIsCtrl = right->m_bTextIsCtrl;
      m_sText = right->m_sText;
    m_OffsetText = right->m_OffsetText;
    m_bLeftText = right->m_bLeftText;
    return *this;
  //## end PLFNTwoStates::operator =%890472640.body
}

void PLFNTwoStates::Serialize (CArchive& ar)
{
  //## begin PLFNTwoStates::Serialize%890472641.body preserve=yes
    PLFNGraphic::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << (DWORD)m_CheckType;
        ar << (WORD)m_uSize;
        // Serialize the status if not a template or a default value is required
        if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetFileType() == E_FD_TemplateType && !GetDefaultValue())
        {
            BOOL    bValue = FALSE;
            ar << (WORD)bValue;
        }
        else
            ar << (WORD)m_bCheckState;
            
          ar << (WORD)m_bShowText;
          ar << (WORD)m_bTextIsCtrl;
          ar << m_sText;
          ar << m_OffsetText;
          ar << (WORD)m_bLeftText;
    }
    else
    {    // Read the elements
        DWORD    dwValue;
        ar >> dwValue;
        m_CheckType = ECheckButtonType(dwValue);
        WORD    wValue;
        ar >> wValue;
        m_uSize = wValue;
        ar >> wValue;
        m_bCheckState = wValue;
        if (((ZDDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> wValue;
            m_bShowText = wValue;
            ar >> wValue;
            m_bTextIsCtrl = wValue;
            ar >> m_sText;
              ar >> m_OffsetText;
              ar >> wValue;
              m_bLeftText = (BOOL)wValue;
        }
        else
        {
            m_bShowText = FALSE;
            m_bTextIsCtrl = FALSE;
            m_bLeftText = FALSE;
        }
    }
  //## end PLFNTwoStates::Serialize%890472641.body
}

PlanFinObject* PLFNTwoStates::Clone ()
{
  //## begin PLFNTwoStates::Clone%890472642.body preserve=yes
    PLFNTwoStates*    pObject = new PLFNTwoStates( *this );
    return pObject;
  //## end PLFNTwoStates::Clone%890472642.body
}

void PLFNTwoStates::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNTwoStates::CopyObject%890472643.body preserve=yes
    ((PLFNTwoStates*)this)->PLFNTwoStates::operator=( (PLFNTwoStates*)pSrc );
  //## end PLFNTwoStates::CopyObject%890472643.body
}

CString PLFNTwoStates::GetUnformatedObject ()
{
  //## begin PLFNTwoStates::GetUnformatedObject%917858762.body preserve=yes
      return (GetbCheckState()) ? "1" : "0";
  //## end PLFNTwoStates::GetUnformatedObject%917858762.body
}

BOOL PLFNTwoStates::ConvertFormatedObject (const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero)
{
  //## begin PLFNTwoStates::ConvertFormatedObject%917889603.body preserve=yes
    if (!(sValue.GetLength() > 0))
        return FALSE;
    // Saves the oldvalue to make comparison
    BOOL    OldValue = m_bCheckState;
    m_bCheckState = (sValue[0] == '0') ? FALSE : TRUE;
    // Has changed ???
    return (OldValue != m_bCheckState) ? TRUE : FALSE;
  //## end PLFNTwoStates::ConvertFormatedObject%917889603.body
}

// Additional Declarations
  //## begin PLFNTwoStates%35138727014A.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNRadio diagnostics

#ifdef _DEBUG
void PLFNTwoStates::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNTwoStates::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNTwoStates%35138727014A.declarations
//## begin module%351388810028.epilog preserve=yes
//## end module%351388810028.epilog
