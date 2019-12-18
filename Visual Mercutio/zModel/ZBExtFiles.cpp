/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtFiles
//@module ZBExtFiles.cpp | Implementation of the <c ZBExtFiles> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 06/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBExtFiles.h"

#include "ZBExtFileProp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 4 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// constant definition
const int LastExtFileIDProperties = ZS_BP_PROP_EXTFILE + 39;

IMPLEMENT_SERIAL(ZBExtFiles, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBExtFiles::ZBExtFiles( CODSymbolComponent* pParent /*= NULL*/ )
    : m_pParent( pParent )
{
}

ZBExtFiles::~ZBExtFiles()
{
    RemoveAllExtFiles();
}

ZBExtFiles::ZBExtFiles( const ZBExtFiles& src )
{
    *this = src;
}

ZBExtFiles& ZBExtFiles::operator=( const ZBExtFiles& src )
{
    // Copy the members.
    ZBExtFilePropertiesIterator i( &const_cast<ZBExtFiles&>( src ).GetExtFileSet() );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        AddExtFile( pProp->Dup() );
    }

    m_pParent = src.m_pParent;

    return *this;
}

ZBExtFiles* ZBExtFiles::Dup() const
{
    return (new ZBExtFiles(*this));
}

void ZBExtFiles::SetParent( CODSymbolComponent* pParent )
{
    m_pParent = pParent;
}

bool ZBExtFiles::CreateInitialProperties()
{
    if ( GetExtFileCount() > 0 )
    {
        return true;
    }

    ZBExtFileProperties* pProps = new ZBExtFileProperties;

    if ( AddExtFile( pProps ) >= 0 )
    {
        return true;
    }

    return false;
}

int ZBExtFiles::AddNewExtFile()
{
    ZBExtFileProperties* pProps = new ZBExtFileProperties;

    return AddExtFile( pProps );
}

int ZBExtFiles::AddExtFile( ZBExtFileProperties* pProperty )
{
    if ( pProperty )
    {
        m_Set.Add( pProperty );

        // Returns the index
        return GetExtFileCount() - 1;
    }

    return -1;
}

bool ZBExtFiles::DeleteExtFile( size_t Index )
{
    if ( Index < GetExtFileCount() )
    {
        ZBExtFileProperties* pProperty = GetProperty( Index );

        if ( pProperty )
        {
            m_Set.RemoveAt( Index );
            delete pProperty;
            return true;
        }
    }

    return false;
}

bool ZBExtFiles::DeleteExtFile( const CString fileName )
{
    // Run through the set of deliverables and check if found
    ZBExtFilePropertiesIterator it( &m_Set );

    for ( ZBExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext() )
    {
        if ( pProp->GetFileName() == fileName)
        {
            delete pProp;
            it.Remove();
            return true;
        }
    }

    return false;
}

bool ZBExtFiles::DeleteExtFile( ZBExtFileProperties* pProperty )
{
    ZBExtFilePropertiesIterator i( &m_Set );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProperty == pProp )
        {
            i.Remove();
            delete pProp;
            return true;
        }
    }

    return false;
}

int ZBExtFiles::LocateFirstEmptyExtFile() const
{
    int Idx = 0;
    ZBExtFilePropertiesIterator i( &m_Set );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Idx )
    {
        if ( pProp->IsEmpty() )
        {
            return Idx;
        }
    }

    return -1;
}

void ZBExtFiles::RemoveAllEmptyExtFiles()
{
    ZBExtFilePropertiesIterator i( &m_Set );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->IsEmpty() )
        {
            delete pProp;
            i.Remove();
        }
    }
}

void ZBExtFiles::RemoveAllExtFiles()
{
    ZBExtFilePropertiesIterator i( &m_Set );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    // Then, remove all elements
    m_Set.RemoveAll();
}

CString ZBExtFiles::GetFileTitle( size_t Index ) const
{
    if ( Index < GetExtFileCount() )
    {
        return m_Set.GetAt(Index)->GetFileTitle();
    }

    return _T( "" );
}

void ZBExtFiles::SetFileTitle( size_t Index, CString Value )
{
    if ( Index < GetExtFileCount() )
    {
        m_Set.GetAt(Index)->SetFileTitle( Value );
    }
}

CString ZBExtFiles::GetFileName( size_t Index ) const
{
    if ( Index < GetExtFileCount() )
    {
        return m_Set.GetAt( Index )->GetFileName();
    }

    return _T( "" );
}

void ZBExtFiles::SetFileName( size_t Index, CString Value )
{
    if ( Index < GetExtFileCount() )
    {
        m_Set.GetAt( Index )->SetFileName( Value );
    }
}

int ZBExtFiles::GetInsertionType( size_t Index ) const
{
    if ( Index < GetExtFileCount() )
    {
        return m_Set.GetAt( Index )->GetInsertionType();
    }

    return 0;
}

void ZBExtFiles::SetInsertionType( size_t Index, const int value )
{
    if ( Index < GetExtFileCount() )
    {
        m_Set.GetAt( Index )->SetInsertionType( value );
    }
}

int ZBExtFiles::GetActivationType( size_t Index ) const
{
    if ( Index < GetExtFileCount() )
    {
        return m_Set.GetAt( Index )->GetActivationType();
    }

    return 0;
}

void ZBExtFiles::SetActivationType( size_t Index, const int value )
{
    if ( Index < GetExtFileCount() )
    {
        m_Set.GetAt( Index )->SetActivationType( value );
    }
}

bool ZBExtFiles::ExtFileExist( const CString fileName) const
{
    // Run through the set and build the string
    ZBExtFilePropertiesIterator i( &m_Set );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetFileName() == fileName)
        {
            return true;
        }
    }

    return false;
}

ZBExtFileProperties* ZBExtFiles::LocateExtFile( const CString fileName) const
{
    // Run through the set of deliverables and check if found
    ZBExtFilePropertiesIterator i( &m_Set );

    for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetFileName() == fileName)
        {
            return pProp;
        }
    }

    return NULL;
}

void ZBExtFiles::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Serialize the size of the set
        ar << m_Set.GetSize();
        ZBExtFilePropertiesIterator i( &m_Set );

        for ( ZBExtFileProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            ar << pProp;
        }
    }
    else
    {
        RemoveAllExtFiles();

        // Read the size of the set
        int Count;
        ar >> Count;

        ZBExtFileProperties* pProp;

        for ( int i = 0; i < Count; ++i )
        {
            ar >> pProp;
            AddExtFile( pProp );
        }
    }
}
