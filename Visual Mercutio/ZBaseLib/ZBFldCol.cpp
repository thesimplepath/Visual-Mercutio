//## begin module%38819A1401D6.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38819A1401D6.cm

//## begin module%38819A1401D6.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%38819A1401D6.cp

//## Module: ZBFldCol%38819A1401D6; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBFldCol.cpp

//## begin module%38819A1401D6.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%38819A1401D6.additionalIncludes

//## begin module%38819A1401D6.includes preserve=yes
//## end module%38819A1401D6.includes

// ZBFldCol
#include "ZBFldCol.h"
//## begin module%38819A1401D6.declarations preserve=no
//## end module%38819A1401D6.declarations

//## begin module%38819A1401D6.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZBFieldColumn, CObject, g_DefVersion)
//## end module%38819A1401D6.additionalDeclarations


// Class ZBFieldColumn 




ZBFieldColumn::ZBFieldColumn()
  //## begin ZBFieldColumn::ZBFieldColumn%.hasinit preserve=no
  //## end ZBFieldColumn::ZBFieldColumn%.hasinit
  //## begin ZBFieldColumn::ZBFieldColumn%.initialization preserve=yes
  : m_Width(60)
  //## end ZBFieldColumn::ZBFieldColumn%.initialization
{
  //## begin ZBFieldColumn::ZBFieldColumn%.body preserve=yes
  //## end ZBFieldColumn::ZBFieldColumn%.body
}

ZBFieldColumn::ZBFieldColumn(const ZBFieldColumn &right)
  //## begin ZBFieldColumn::ZBFieldColumn%copy.hasinit preserve=no
  //## end ZBFieldColumn::ZBFieldColumn%copy.hasinit
  //## begin ZBFieldColumn::ZBFieldColumn%copy.initialization preserve=yes
  //## end ZBFieldColumn::ZBFieldColumn%copy.initialization
{
  //## begin ZBFieldColumn::ZBFieldColumn%copy.body preserve=yes
    *this = right;
  //## end ZBFieldColumn::ZBFieldColumn%copy.body
}

ZBFieldColumn::ZBFieldColumn (const CString HeaderName, const CStringArray& Values)
  //## begin ZBFieldColumn::ZBFieldColumn%948017507.hasinit preserve=no
  //## end ZBFieldColumn::ZBFieldColumn%948017507.hasinit
  //## begin ZBFieldColumn::ZBFieldColumn%948017507.initialization preserve=yes
  : m_HeaderName(HeaderName), m_Width(60)
  //## end ZBFieldColumn::ZBFieldColumn%948017507.initialization
{
  //## begin ZBFieldColumn::ZBFieldColumn%948017507.body preserve=yes
    // Copy values
    for (size_t i = 0; i < (size_t)Values.GetSize(); ++i)
        AddValue( Values.GetAt(i) );
  //## end ZBFieldColumn::ZBFieldColumn%948017507.body
}

ZBFieldColumn::ZBFieldColumn (const CString HeaderName, size_t Width)
  //## begin ZBFieldColumn::ZBFieldColumn%948222400.hasinit preserve=no
  //## end ZBFieldColumn::ZBFieldColumn%948222400.hasinit
  //## begin ZBFieldColumn::ZBFieldColumn%948222400.initialization preserve=yes
  : m_HeaderName(HeaderName), m_Width(Width)
  //## end ZBFieldColumn::ZBFieldColumn%948222400.initialization
{
  //## begin ZBFieldColumn::ZBFieldColumn%948222400.body preserve=yes
  //## end ZBFieldColumn::ZBFieldColumn%948222400.body
}


ZBFieldColumn::~ZBFieldColumn()
{
  //## begin ZBFieldColumn::~ZBFieldColumn%.body preserve=yes
  //## end ZBFieldColumn::~ZBFieldColumn%.body
}


const ZBFieldColumn & ZBFieldColumn::operator=(const ZBFieldColumn &right)
{
  //## begin ZBFieldColumn::operator=%.body preserve=yes
    m_HeaderName = right.m_HeaderName;
    m_Width = right.m_Width;
    for (size_t i = 0; i < right.GetValueCount(); ++i)
    {
        AddValue( right.GetValueAt(i) );
    }
    return *this;
  //## end ZBFieldColumn::operator=%.body
}



//## Other Operations (implementation)
void ZBFieldColumn::Serialize (CArchive& ar)
{
  //## begin ZBFieldColumn::Serialize%948017485.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_HeaderName;
        ar << (WORD)m_Width;
    }
    else
    {    // Read the elements
        ar >> m_HeaderName;
        WORD    wValue;
        ar >> wValue;
        m_Width = (size_t)wValue;
    }
    m_ValueArray.Serialize( ar );
  //## end ZBFieldColumn::Serialize%948017485.body
}

ZBFieldColumn* ZBFieldColumn::Clone ()
{
  //## begin ZBFieldColumn::Clone%948017487.body preserve=yes
    ZBFieldColumn*    pObject = new ZBFieldColumn( *this );
    return pObject;
  //## end ZBFieldColumn::Clone%948017487.body
}

CString ZBFieldColumn::GetValueAt (size_t Index) const
{
  //## begin ZBFieldColumn::GetValueAt%948017500.body preserve=yes
    if (Index < GetValueCount())
        return m_ValueArray.GetAt( Index );
    return "";
  //## end ZBFieldColumn::GetValueAt%948017500.body
}

void ZBFieldColumn::AddValue (const CString& Value)
{
  //## begin ZBFieldColumn::AddValue%948017501.body preserve=yes
    m_ValueArray.Add( Value );
  //## end ZBFieldColumn::AddValue%948017501.body
}

void ZBFieldColumn::InsertValueAt (const CString& Value, size_t Index)
{
  //## begin ZBFieldColumn::InsertValueAt%948017502.body preserve=yes
    m_ValueArray.InsertAt( Index, Value );
  //## end ZBFieldColumn::InsertValueAt%948017502.body
}

void ZBFieldColumn::SetValueAt (const CString& Value, size_t Index)
{
  //## begin ZBFieldColumn::SetValueAt%948222401.body preserve=yes
    if (Index < GetValueCount())
    {
        m_ValueArray.SetAt( Index, Value );
    }
  //## end ZBFieldColumn::SetValueAt%948222401.body
}

bool ZBFieldColumn::RemoveValue (const CString& Value)
{
  //## begin ZBFieldColumn::RemoveValue%948017503.body preserve=yes
    for (size_t i = 0; i < GetValueCount(); ++i)
    {
        if (GetValueAt(i) == Value)
        {
            RemoveValueAt( i );
            return true;
        }
    }
    return false;
  //## end ZBFieldColumn::RemoveValue%948017503.body
}

bool ZBFieldColumn::RemoveValueAt (size_t Index)
{
  //## begin ZBFieldColumn::RemoveValueAt%948017504.body preserve=yes
    if (Index < GetValueCount())
    {
        m_ValueArray.RemoveAt( Index );
        return true;
    }
    return false;
  //## end ZBFieldColumn::RemoveValueAt%948017504.body
}

void ZBFieldColumn::FreeValueArray ()
{
  //## begin ZBFieldColumn::FreeValueArray%948017506.body preserve=yes
    m_ValueArray.RemoveAll();
  //## end ZBFieldColumn::FreeValueArray%948017506.body
}

void ZBFieldColumn::AutoSizeColumn ()
{
  //## begin ZBFieldColumn::AutoSizeColumn%948017529.body preserve=yes
    m_Width = 40;
  //## end ZBFieldColumn::AutoSizeColumn%948017529.body
}

int ZBFieldColumn::GetValueRow (const CString& Value)
{
  //## begin ZBFieldColumn::GetValueRow%948400970.body preserve=yes
    for (size_t i = 0; i < GetValueCount(); ++i)
    {
        if (GetValueAt(i) == Value)
            return (int)i;
    }
    return -1;
  //## end ZBFieldColumn::GetValueRow%948400970.body
}

// Additional Declarations
  //## begin ZBFieldColumn%3881998D038A.declarations preserve=yes
  //## end ZBFieldColumn%3881998D038A.declarations

//## begin module%38819A1401D6.epilog preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZBFieldColumn diagnostics

#ifdef _DEBUG
void ZBFieldColumn::AssertValid() const
{
    CObject::AssertValid();
}

void ZBFieldColumn::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG
//## end module%38819A1401D6.epilog
