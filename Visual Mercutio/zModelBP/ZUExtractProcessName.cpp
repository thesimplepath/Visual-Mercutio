/////////////////////////////////////////////////////////////////////////////
//@doc ZUExtractProcessName
//@module ZUExtractProcessName.cpp | Implementation of the <c ZUExtractProcessName> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 07/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUExtractProcessName.h"

//#include "zModel\ProcGraphModelMdl.h"
#include "ZBBPProcessSymbol.h"

// Include files for log
#include "zBaseLib\ZILog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 8 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUExtractProcessName::ZUExtractProcessName( ZDProcessGraphModelMdl* pModel /*= NULL*/, ZILog* pLog /*= NULL*/ )
    : m_pModel    ( pModel ),
      m_pLog    ( pLog ),
      m_pArray    ( NULL )
{
}

ZUExtractProcessName::~ZUExtractProcessName()
{
}

// JMR-MODIF - Le 29 mars 2006 - Ajout du paramètre FirstElementToSort.
bool ZUExtractProcessName::FillProcessNameArray( CStringArray* pArray, int FirstElementToSort /*= 0*/ )
{
    m_pArray = pArray;

    if ( m_pModel && m_pArray )
    {
        m_pModel->AcceptVisitor( *this );

        // JMR-MODIF - Le 8 mars 2006 - Trie la liste par ordre alphabétique croissant avant de rendre la main.
        Sort( FirstElementToSort );

        return true;
    }

    return false;
}

bool ZUExtractProcessName::Visit( CODComponent& Symbol )
{
    CODComponent* pSymbol = &Symbol;

    if ( ISA( pSymbol, ZBBPProcessSymbol ) )
    {
        return AddProcessSymbol( dynamic_cast<ZBBPProcessSymbol*>( &Symbol ) );
    }

    // Nothing to do
    return true;
}

bool ZUExtractProcessName::AddProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
    ASSERT( pSymbol );
    ASSERT( m_pArray );

    if ( !Exist( *m_pArray, pSymbol->GetSymbolName() ) )
    {
        m_pArray->Add( pSymbol->GetSymbolName() );
    }

    return true;
}

bool ZUExtractProcessName::Exist( CStringArray& Array, const CString ProcessName )
{
    size_t Counter = Array.GetSize();

    for ( size_t i = 0; i < Counter; ++i )
    {
        if ( Array.GetAt( i ) == ProcessName )
        {
            return true;
        }
    }

    return false;
}

// JMR-MODIF - Le 8 mars 2006 - Fonction de Tri de la liste de noms, par ordre alphabétique croissant.
// JMR-MODIF - Le 29 mars 2006 - Ajout du paramètre First.
void ZUExtractProcessName::Sort( int First /*= 0*/ )
{
    if ( First >= m_pArray->GetUpperBound() )
    {
        return;
    }

    size_t CurPos    = First;
    size_t NextPos    = First;

    while ( CurPos <= m_pArray->GetUpperBound() )
    {
        NextPos = CurPos + 1;

        if ( NextPos <= m_pArray->GetUpperBound() )
        {
            CString m_CurStr    = m_pArray->GetAt( CurPos );
            CString m_NextStr    = m_pArray->GetAt( NextPos );

            if ( m_CurStr != _T( "" ) && m_NextStr != _T( "" ) )
            {
                if ( m_CurStr.Compare( m_NextStr ) > 0 )
                {
                    m_pArray->SetAt( CurPos, m_NextStr );
                    m_pArray->SetAt( NextPos, m_CurStr );

                    Sort( First );
                    return;
                }
            }
        }

        CurPos += 1;
    }
}
