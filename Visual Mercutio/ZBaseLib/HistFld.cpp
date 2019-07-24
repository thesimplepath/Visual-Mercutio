//## begin module%363481990180.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%363481990180.cm

//## begin module%363481990180.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%363481990180.cp

//## Module: HistFld%363481990180; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\HistFld.cpp

//## begin module%363481990180.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%363481990180.additionalIncludes

//## begin module%363481990180.includes preserve=yes
//## end module%363481990180.includes

// HistFld
#include "HistFld.h"
//## begin module%363481990180.declarations preserve=no
//## end module%363481990180.declarations

//## begin module%363481990180.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAHistoryField, CObject, g_DefVersion)
//## end module%363481990180.additionalDeclarations


// Class ZAHistoryField 




ZAHistoryField::ZAHistoryField()
  //## begin ZAHistoryField::ZAHistoryField%.hasinit preserve=no
      : m_ReadOnly(FALSE)
  //## end ZAHistoryField::ZAHistoryField%.hasinit
  //## begin ZAHistoryField::ZAHistoryField%.initialization preserve=yes
  //## end ZAHistoryField::ZAHistoryField%.initialization
{
  //## begin ZAHistoryField::ZAHistoryField%.body preserve=yes
  //## end ZAHistoryField::ZAHistoryField%.body
}

ZAHistoryField::ZAHistoryField(const ZAHistoryField &right)
  //## begin ZAHistoryField::ZAHistoryField%copy.hasinit preserve=no
      : m_ReadOnly(FALSE)
  //## end ZAHistoryField::ZAHistoryField%copy.hasinit
  //## begin ZAHistoryField::ZAHistoryField%copy.initialization preserve=yes
  //## end ZAHistoryField::ZAHistoryField%copy.initialization
{
  //## begin ZAHistoryField::ZAHistoryField%copy.body preserve=yes
    *this = right;
  //## end ZAHistoryField::ZAHistoryField%copy.body
}


ZAHistoryField::~ZAHistoryField()
{
  //## begin ZAHistoryField::~ZAHistoryField%.body preserve=yes
  //## end ZAHistoryField::~ZAHistoryField%.body
}


const ZAHistoryField & ZAHistoryField::operator=(const ZAHistoryField &right)
{
  //## begin ZAHistoryField::operator=%.body preserve=yes
      // copy the values
      for (int i = 0; i < right.m_FieldValueHistoryArray.GetSize(); ++i)
          m_FieldValueHistoryArray.Add( right.m_FieldValueHistoryArray[i] );
    m_ReadOnly = right.m_ReadOnly;
    m_FieldName = right.m_FieldName;
    return *this;
  //## end ZAHistoryField::operator=%.body
}



//## Other Operations (implementation)
void ZAHistoryField::Serialize (CArchive& ar)
{
  //## begin ZAHistoryField::Serialize%909410992.body preserve=yes
    m_FieldValueHistoryArray.Serialize( ar );
    if (ar.IsStoring())
    {    // Write the elements
          ar << (WORD)m_ReadOnly;
          ar << m_FieldName;
    }
    else
    {    // Read the elements
        WORD    wTemp;
        ar >> wTemp;
        m_ReadOnly = wTemp;
          ar >> m_FieldName;
    }
  //## end ZAHistoryField::Serialize%909410992.body
}

void ZAHistoryField::AddFieldValue (const CString& Value)
{
  //## begin ZAHistoryField::AddFieldValue%909410994.body preserve=yes
      // Tests if the value already exists
      for (int i = 0; i < m_FieldValueHistoryArray.GetSize(); ++i)
          if (m_FieldValueHistoryArray[i] == Value)
              return;
      m_FieldValueHistoryArray.Add( Value );
  //## end ZAHistoryField::AddFieldValue%909410994.body
}

BOOL ZAHistoryField::RemoveFieldValue (const CString& Value)
{
  //## begin ZAHistoryField::RemoveFieldValue%909410995.body preserve=yes
      // Tests if the value already exists
      for (int i = 0; i < m_FieldValueHistoryArray.GetSize(); ++i)
          if (m_FieldValueHistoryArray[i] == Value)
          {
              m_FieldValueHistoryArray.RemoveAt( i );
              return TRUE;
          }
      return FALSE;
  //## end ZAHistoryField::RemoveFieldValue%909410995.body
}

void ZAHistoryField::FreeList ()
{
  //## begin ZAHistoryField::FreeList%909411006.body preserve=yes
      m_FieldValueHistoryArray.RemoveAll();
  //## end ZAHistoryField::FreeList%909411006.body
}

ZAHistoryField* ZAHistoryField::Clone ()
{
  //## begin ZAHistoryField::Clone%939069934.body preserve=yes
    ZAHistoryField*    pObject = new ZAHistoryField( *this );
    return pObject;
  //## end ZAHistoryField::Clone%939069934.body
}

// Additional Declarations
  //## begin ZAHistoryField%36347E3600E3.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAHistoryField diagnostics

#ifdef _DEBUG
void ZAHistoryField::AssertValid() const
{
    CObject::AssertValid();
}

void ZAHistoryField::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZAHistoryField%36347E3600E3.declarations
//## begin module%363481990180.epilog preserve=yes
//## end module%363481990180.epilog
