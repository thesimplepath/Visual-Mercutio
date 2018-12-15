// ZBUnit.cpp: implementation of the ZBUnit class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUnit.h"
#include "ProcGraphModelDoc.h"
#include "zBaseLib\File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_SERIAL( ZBUnit, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUnit::ZBUnit( const CString Name /*= ""*/, const CString Filename /*= ""*/ )
    : m_Name        ( Name ),
      m_Filename    ( Filename ),
      m_pUnitDoc    ( NULL )
{
}

ZBUnit::~ZBUnit()
{
    // Do not delete the document pointer,
    // Unload will do it.
}

bool ZBUnit::Create( const CString Name )
{
    m_Name = Name;
    m_Key = CreateUniqueKey();

    if ( m_Key.IsEmpty() )
    {
        return false;
    }

    return true;
}

bool ZBUnit::Create( const CString Name, const CString Filename )
{
    m_Name        = Name;
    m_Filename    = Filename;
    m_Key        = CreateUniqueKey();

    if ( m_Key.IsEmpty() )
    {
        return false;
    }

    return true;
}

CString    ZBUnit::CreateUniqueKey()
{
    GUID guid;

    HRESULT Result = CoCreateGuid( &guid );

    if ( Result == S_OK )
    {
        CString Key;
        Key.Format( _T( "%d-%d" ), guid.Data1, guid.Data2 );

        return Key;
    }

    // Problem in the creation
    return _T( "" );
}

bool ZBUnit::LoadUnit( ZDProcessModelDocTmpl* pDocTmpl )
{
    // Check if the file exists
    ZFile File( m_Filename );

    if ( !File.Exist() )
    {
        return false;
    }

    if ( m_pUnitDoc )
    {
        if ( !UnloadUnit() )
        {
            return false;
        }
    }

    CDocument* pDoc = pDocTmpl->OpenDocumentFile( m_Filename, FALSE );

    if ( pDoc && ISA( pDoc, ZDProcessGraphModelDoc ) )
    {
        m_pUnitDoc = (ZDProcessGraphModelDoc*)pDoc;

        // Assign the name.
        m_Name = ( (ZDProcessGraphModelDoc*)pDoc )->GetModel()->GetModelName();
    }
    else
    {
        if ( pDoc )
        {
            pDoc->OnCloseDocument();
            delete pDoc;
        }
    }

    return m_pUnitDoc != NULL;
}

bool ZBUnit::UnloadUnit()
{
    if ( m_pUnitDoc )
    {
        m_pUnitDoc->OnCloseDocument();
        delete m_pUnitDoc;
        m_pUnitDoc = NULL;

        return true;
    }

    return false;
}

// Serializes the unit
void ZBUnit::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << m_Key;
        ar << m_Name;
        ar << m_Filename;
    }
    else
    {
        ar >> m_Key;
        ar >> m_Name;
        ar >> m_Filename;
    }
}
