//## begin module%38819AFD0267.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38819AFD0267.cm

//## begin module%38819AFD0267.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%38819AFD0267.cp

//## Module: ZBFldColMg%38819AFD0267; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBFldClM.cpp

//## begin module%38819AFD0267.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%38819AFD0267.additionalIncludes

//## begin module%38819AFD0267.includes preserve=yes
//## end module%38819AFD0267.includes

// ZBFldColMg
#include "ZBFldClM.h"
//## begin module%38819AFD0267.declarations preserve=no
//## end module%38819AFD0267.declarations

//## begin module%38819AFD0267.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZBFieldColumnManager, CObject, g_DefVersion)
//## end module%38819AFD0267.additionalDeclarations


// Class ZBFieldColumnManager 


ZBFieldColumnManager::ZBFieldColumnManager()
  //## begin ZBFieldColumnManager::ZBFieldColumnManager%.hasinit preserve=no
  //## end ZBFieldColumnManager::ZBFieldColumnManager%.hasinit
  //## begin ZBFieldColumnManager::ZBFieldColumnManager%.initialization preserve=yes
  //## end ZBFieldColumnManager::ZBFieldColumnManager%.initialization
{
  //## begin ZBFieldColumnManager::ZBFieldColumnManager%.body preserve=yes
  //## end ZBFieldColumnManager::ZBFieldColumnManager%.body
}

ZBFieldColumnManager::ZBFieldColumnManager(const ZBFieldColumnManager &right)
  //## begin ZBFieldColumnManager::ZBFieldColumnManager%copy.hasinit preserve=no
  //## end ZBFieldColumnManager::ZBFieldColumnManager%copy.hasinit
  //## begin ZBFieldColumnManager::ZBFieldColumnManager%copy.initialization preserve=yes
  //## end ZBFieldColumnManager::ZBFieldColumnManager%copy.initialization
{
  //## begin ZBFieldColumnManager::ZBFieldColumnManager%copy.body preserve=yes
    *this = right;
  //## end ZBFieldColumnManager::ZBFieldColumnManager%copy.body
}


ZBFieldColumnManager::~ZBFieldColumnManager()
{
  //## begin ZBFieldColumnManager::~ZBFieldColumnManager%.body preserve=yes
  //## end ZBFieldColumnManager::~ZBFieldColumnManager%.body
}


const ZBFieldColumnManager & ZBFieldColumnManager::operator=(const ZBFieldColumnManager &right)
{
  //## begin ZBFieldColumnManager::operator=%.body preserve=yes
    for (size_t i = 0; i < right.GetCount(); ++i)
    {
        AddColumn( right.GetColumnAt(i)->Clone() );
    }
    return *this;
  //## end ZBFieldColumnManager::operator=%.body
}



//## Other Operations (implementation)
void ZBFieldColumnManager::Serialize (CArchive& ar)
{
  //## begin ZBFieldColumnManager::Serialize%948017486.body preserve=yes
    m_ColumnArray.Serialize( ar );
  //## end ZBFieldColumnManager::Serialize%948017486.body
}

ZBFieldColumnManager* ZBFieldColumnManager::Clone ()
{
  //## begin ZBFieldColumnManager::Clone%948017488.body preserve=yes
    ZBFieldColumnManager*    pObject = new ZBFieldColumnManager( *this );
    return pObject;
  //## end ZBFieldColumnManager::Clone%948017488.body
}

void ZBFieldColumnManager::AddColumn (ZBFieldColumn* pColumn)
{
  //## begin ZBFieldColumnManager::AddColumn%948017490.body preserve=yes
    m_ColumnArray.Add( (CObject*)pColumn );
  //## end ZBFieldColumnManager::AddColumn%948017490.body
}

void ZBFieldColumnManager::AddColumn (const CString HeaderName, const CStringArray& Values)
{
  //## begin ZBFieldColumnManager::AddColumn%948017508.body preserve=yes
    AddColumn( new ZBFieldColumn( HeaderName, Values ) );
  //## end ZBFieldColumnManager::AddColumn%948017508.body
}

bool ZBFieldColumnManager::RemoveColumn (const CString& HeaderName)
{
  //## begin ZBFieldColumnManager::RemoveColumn%948017491.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i)->GetHeaderName() == HeaderName)
            return RemoveColumnAt( i );
    }
    return false;
  //## end ZBFieldColumnManager::RemoveColumn%948017491.body
}

bool ZBFieldColumnManager::RemoveColumn (ZBFieldColumn* pColumn)
{
  //## begin ZBFieldColumnManager::RemoveColumn%948017492.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i) == pColumn)
            return RemoveColumnAt( i );
    }
    return false;
  //## end ZBFieldColumnManager::RemoveColumn%948017492.body
}

void ZBFieldColumnManager::RemoveAll ()
{
  //## begin ZBFieldColumnManager::RemoveAll%948017493.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        // Free memory first
        if (GetColumnAt(i))
            delete GetColumnAt( i );
    }
    // And now can remove all elements
    m_ColumnArray.RemoveAll();
  //## end ZBFieldColumnManager::RemoveAll%948017493.body
}

ZBFieldColumn* ZBFieldColumnManager::FindColumn (const CString& HeaderName)
{
  //## begin ZBFieldColumnManager::FindColumn%948017494.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i)->GetHeaderName() == HeaderName)
            return GetColumnAt(i);
    }
    return NULL;
  //## end ZBFieldColumnManager::FindColumn%948017494.body
}

bool ZBFieldColumnManager::FindColumn (ZBFieldColumn* pColumn)
{
  //## begin ZBFieldColumnManager::FindColumn%948017495.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i) == pColumn)
            return true;
    }
    return false;
  //## end ZBFieldColumnManager::FindColumn%948017495.body
}

ZBFieldColumn* ZBFieldColumnManager::GetColumnAt (size_t Index) const
{
  //## begin ZBFieldColumnManager::GetColumnAt%948017496.body preserve=yes
    if (Index < GetCount())
        return (ZBFieldColumn*)m_ColumnArray.GetAt( Index );
    return NULL;
  //## end ZBFieldColumnManager::GetColumnAt%948017496.body
}

void ZBFieldColumnManager::InsertColumnAt (ZBFieldColumn* pColumn, size_t Index)
{
  //## begin ZBFieldColumnManager::InsertColumnAt%948017497.body preserve=yes
    m_ColumnArray.InsertAt( Index, (CObject*)pColumn );
  //## end ZBFieldColumnManager::InsertColumnAt%948017497.body
}

bool ZBFieldColumnManager::RemoveColumnAt (size_t Index)
{
  //## begin ZBFieldColumnManager::RemoveColumnAt%948017498.body preserve=yes
    if (Index < GetCount())
    {
        // Free memory first
        if (GetColumnAt(Index))
            delete GetColumnAt( Index );
        // Remove element
        m_ColumnArray.RemoveAt( Index );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::RemoveColumnAt%948017498.body
}

bool ZBFieldColumnManager::GetRowValues (CStringArray& RowValues, size_t RowIndex)
{
  //## begin ZBFieldColumnManager::GetRowValues%948017509.body preserve=yes
    RowValues.RemoveAll();
    // No columns, return false
    if (GetCount() == 0)
        return false;
    // Check the row index, if too large, return false
    if (GetColumnAt(0)->GetValueCount() < RowIndex)
        return false;
    // Run through all columns and fill the array with
    // the row value
    for (size_t i = 0; i < GetCount(); ++i)
        RowValues.Add( GetColumnAt(i)->GetValueAt(RowIndex) );
    return true;
  //## end ZBFieldColumnManager::GetRowValues%948017509.body
}

bool ZBFieldColumnManager::GetColumnRowValue (const CString ColumnName, size_t RowIndex, CString& Value)
{
  //## begin ZBFieldColumnManager::GetColumnRowValue%948017510.body preserve=yes
    ZBFieldColumn* pFieldColumn = FindColumn( ColumnName );
    if (pFieldColumn)
    {
        if (!(RowIndex < pFieldColumn->GetValueCount()))
            return false;
        Value = pFieldColumn->GetValueAt( RowIndex );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::GetColumnRowValue%948017510.body
}

bool ZBFieldColumnManager::GetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString& Value)
{
  //## begin ZBFieldColumnManager::GetColumnRowValue%948017511.body preserve=yes
    ZBFieldColumn* pFieldColumn = GetColumnAt( ColumnIndex );
    if (pFieldColumn)
    {
        if (!(RowIndex < pFieldColumn->GetValueCount()))
            return false;
        Value = pFieldColumn->GetValueAt( RowIndex );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::GetColumnRowValue%948017511.body
}

bool ZBFieldColumnManager::SetColumnRowValue (const CString ColumnName, size_t RowIndex, CString Value)
{
  //## begin ZBFieldColumnManager::SetColumnRowValue%948222412.body preserve=yes
    ZBFieldColumn* pFieldColumn = FindColumn( ColumnName );
    if (pFieldColumn)
    {
        if (!(RowIndex < pFieldColumn->GetValueCount()))
            return false;
        pFieldColumn->SetValueAt( Value, RowIndex );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::SetColumnRowValue%948222412.body
}

bool ZBFieldColumnManager::SetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString Value)
{
  //## begin ZBFieldColumnManager::SetColumnRowValue%948222413.body preserve=yes
    ZBFieldColumn* pFieldColumn = GetColumnAt( ColumnIndex );
    if (pFieldColumn)
    {
        if (!(RowIndex < pFieldColumn->GetValueCount()))
            return false;
        pFieldColumn->SetValueAt( Value, RowIndex );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::SetColumnRowValue%948222413.body
}

bool ZBFieldColumnManager::AutoSizeColumn (const CString& HeaderName)
{
  //## begin ZBFieldColumnManager::AutoSizeColumn%948017530.body preserve=yes
    ZBFieldColumn* pFieldColumn = FindColumn( HeaderName );
    if (pFieldColumn)
    {
        pFieldColumn->AutoSizeColumn();
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::AutoSizeColumn%948017530.body
}

bool ZBFieldColumnManager::AutoSizeColumn (ZBFieldColumn* pColumn)
{
  //## begin ZBFieldColumnManager::AutoSizeColumn%948017531.body preserve=yes
    if (pColumn)
    {
        pColumn->AutoSizeColumn();
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::AutoSizeColumn%948017531.body
}

bool ZBFieldColumnManager::AutoSizeColumnAt (size_t Index)
{
  //## begin ZBFieldColumnManager::AutoSizeColumnAt%948017532.body preserve=yes
    ZBFieldColumn* pFieldColumn = GetColumnAt( Index );
    if (pFieldColumn)
    {
        pFieldColumn->AutoSizeColumn();
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::AutoSizeColumnAt%948017532.body
}

bool ZBFieldColumnManager::AutoSizeAllColumns ()
{
  //## begin ZBFieldColumnManager::AutoSizeAllColumns%948017533.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i))
            GetColumnAt(i)->AutoSizeColumn();
    }
    return true;
  //## end ZBFieldColumnManager::AutoSizeAllColumns%948017533.body
}

bool ZBFieldColumnManager::SizeColumn (const CString& HeaderName, size_t Width)
{
  //## begin ZBFieldColumnManager::SizeColumn%948017534.body preserve=yes
    ZBFieldColumn* pFieldColumn = FindColumn( HeaderName );
    if (pFieldColumn)
    {
        pFieldColumn->SetWidth( Width );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::SizeColumn%948017534.body
}

bool ZBFieldColumnManager::SizeColumn (ZBFieldColumn* pColumn, size_t Width)
{
  //## begin ZBFieldColumnManager::SizeColumn%948017535.body preserve=yes
    if (pColumn)
    {
        pColumn->SetWidth( Width );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::SizeColumn%948017535.body
}

bool ZBFieldColumnManager::SizeColumnAt (size_t Index, size_t Width)
{
  //## begin ZBFieldColumnManager::SizeColumnAt%948017536.body preserve=yes
    ZBFieldColumn* pFieldColumn = GetColumnAt( Index );
    if (pFieldColumn)
    {
        pFieldColumn->SetWidth( Width );
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::SizeColumnAt%948017536.body
}

bool ZBFieldColumnManager::SizeAllColumns (size_t Width)
{
  //## begin ZBFieldColumnManager::SizeAllColumns%948017537.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i))
            GetColumnAt(i)->SetWidth( Width );
    }
    return true;
  //## end ZBFieldColumnManager::SizeAllColumns%948017537.body
}

bool ZBFieldColumnManager::GetHeaderNames (CStringArray& HeaderNames)
{
  //## begin ZBFieldColumnManager::GetHeaderNames%948017546.body preserve=yes
    HeaderNames.RemoveAll();
    // No columns, return false
    if (GetCount() == 0)
        return false;
    // Run through all columns and fill the array with
    // the row value
    for (size_t i = 0; i < GetCount(); ++i)
        HeaderNames.Add( GetColumnAt(i)->GetHeaderName() );
    return true;
  //## end ZBFieldColumnManager::GetHeaderNames%948017546.body
}

bool ZBFieldColumnManager::CreateColumnWithHeaderNames (CStringArray& HeaderNames)
{
  //## begin ZBFieldColumnManager::CreateColumnWithHeaderNames%948222394.body preserve=yes
    for (size_t i = 0; i < (size_t)HeaderNames.GetSize(); ++i)
    {
        ZBFieldColumn* pFieldColumn = new ZBFieldColumn( HeaderNames.GetAt(i) );
        if (!pFieldColumn)
            return false;
        AddColumn( pFieldColumn );
    }
    return true;
  //## end ZBFieldColumnManager::CreateColumnWithHeaderNames%948222394.body
}

bool ZBFieldColumnManager::AddRowValues (CStringArray& RowValues)
{
  //## begin ZBFieldColumnManager::AddRowValues%948222395.body preserve=yes
    if (GetCount() == 0)
        return false;
    for (size_t i = 0; i < (size_t)RowValues.GetSize(); ++i)
    {
        if (GetColumnAt(i))
            GetColumnAt(i)->AddValue( RowValues.GetAt(i) );
    }
    return true;

  //## end ZBFieldColumnManager::AddRowValues%948222395.body
}

bool ZBFieldColumnManager::InsertRowValuesAt (CStringArray& RowValues, size_t RowIndex)
{
  //## begin ZBFieldColumnManager::InsertRowValuesAt%948222396.body preserve=yes
    if (!(RowIndex < GetCount()))
        return false;
    for (size_t i = 0; i < (size_t)RowValues.GetSize(); ++i)
    {
        if (GetColumnAt(i))
            GetColumnAt(i)->InsertValueAt( RowValues.GetAt(i), RowIndex );
    }
    return true;
  //## end ZBFieldColumnManager::InsertRowValuesAt%948222396.body
}

bool ZBFieldColumnManager::SetRowValuesAt (CStringArray& RowValues, size_t RowIndex)
{
  //## begin ZBFieldColumnManager::SetRowValuesAt%948222402.body preserve=yes
    if (!(RowIndex < GetCount()))
        return false;
    for (size_t i = 0; i < (size_t)RowValues.GetSize(); ++i)
    {
        if (GetColumnAt(i))
            GetColumnAt(i)->SetValueAt( RowValues.GetAt(i), RowIndex );
    }
    return true;
  //## end ZBFieldColumnManager::SetRowValuesAt%948222402.body
}

bool ZBFieldColumnManager::RemoveColumnValues (const CString& HeaderName)
{
  //## begin ZBFieldColumnManager::RemoveColumnValues%948222403.body preserve=yes
    ZBFieldColumn* pFieldColumn = FindColumn( HeaderName );
    if (pFieldColumn)
    {
        pFieldColumn->FreeValueArray();
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::RemoveColumnValues%948222403.body
}

bool ZBFieldColumnManager::RemoveColumnValues (ZBFieldColumn* pColumn)
{
  //## begin ZBFieldColumnManager::RemoveColumnValues%948222404.body preserve=yes
    if (pColumn)
    {
        pColumn->FreeValueArray();
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::RemoveColumnValues%948222404.body
}

void ZBFieldColumnManager::RemoveAllValues ()
{
  //## begin ZBFieldColumnManager::RemoveAllValues%948222405.body preserve=yes
    for (size_t i = 0; i < GetCount(); ++i)
    {
        if (GetColumnAt(i))
            GetColumnAt(i)->FreeValueArray();
    }
  //## end ZBFieldColumnManager::RemoveAllValues%948222405.body
}

bool ZBFieldColumnManager::RemoveColumnValuesAt (size_t Index)
{
  //## begin ZBFieldColumnManager::RemoveColumnValuesAt%948222406.body preserve=yes
    ZBFieldColumn* pFieldColumn = GetColumnAt( Index );
    if (pFieldColumn)
    {
        pFieldColumn->FreeValueArray();
        return true;
    }
    return false;
  //## end ZBFieldColumnManager::RemoveColumnValuesAt%948222406.body
}

// Additional Declarations
  //## begin ZBFieldColumnManager%38819AA402EB.declarations preserve=yes
  //## end ZBFieldColumnManager%38819AA402EB.declarations

//## begin module%38819AFD0267.epilog preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZBFieldColumnManager diagnostics

#ifdef _DEBUG
void ZBFieldColumnManager::AssertValid() const
{
    CObject::AssertValid();
}

void ZBFieldColumnManager::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG
//## end module%38819AFD0267.epilog
