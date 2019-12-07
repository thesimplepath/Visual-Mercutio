// **************************************************************************************************************
// *                                      Classe ZUBuildSymbolNewName                                            *
// **************************************************************************************************************
// * Cette classe permet la création d'un nom valide et unique pour les symboles.                                *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZUBuildSymbolNewName.h"

#include "ProcGraphModelMdl.h"

#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 22 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUBuildSymbolNewName::ZUBuildSymbolNewName(const CString BaseName /*= ""*/)
    : m_BaseName(BaseName)
{}

ZUBuildSymbolNewName::~ZUBuildSymbolNewName()
{}

// JMR-MODIF - Le 23 mai 2006 - Ajout du paramètre RefNumber.
CString ZUBuildSymbolNewName::GetNextAvailableSymbolName(CODModel& Model, int RefNumber)
{
    // **********************************************************************************************************
    // JMR-MODIF - Le 23 mai 2006 - Suppression de l'ancien code de la fonction GetNextAvailableSymbolName.

/*    for ( int p = 1; p < 10000000; ++p )
    {
        if ( m_BaseName.IsEmpty() )
        {
            m_SymbolName.Format( _T( "sym%d" ), p );
        }
        else
        {
            m_SymbolName.Format( _T( "%s%d" ), (const char*)m_BaseName, p );
        }

        m_Found = false;

        // Try the name
        _GetNextAvailableSymbolName( Model );

        // If did found the same symbol name, return it
        if ( m_Found == false )
        {
            return m_SymbolName;
        }
    }

    // If no page available, return empty string
    return _T( "" );
*/
// **********************************************************************************************************

// **********************************************************************************************************
// JMR-MODIF - Le 23 mai 2006 - Nouveau code pour la fonction GetNextAvailableSymbolName.

    if (m_BaseName.IsEmpty())
    {
        m_SymbolName.Format(_T("sym%d"), RefNumber);
    }
    else
    {
        m_SymbolName.Format(_T("%s%d"), (const char*)m_BaseName, RefNumber);
    }

    m_Found = false;

    // Try the name
    _GetNextAvailableSymbolName(Model);

    // If did found the same symbol name, return it
    if (m_Found == false)
    {
        return m_SymbolName;
    }

    // If no page available, return empty string
    return _T("");
    // **********************************************************************************************************
}

void ZUBuildSymbolNewName::_GetNextAvailableSymbolName(CODModel& Model)
{
    CODModel* pModel = &Model;

    if (ISA(pModel, PSS_ProcessGraphModelMdl))
    {
        dynamic_cast<PSS_ProcessGraphModelMdl&>(Model).AcceptVisitor(*this);
    }
}

bool ZUBuildSymbolNewName::Visit(CODComponent& Symbol)
{
    CODComponent* pSymbol = &Symbol;

    if (ISA(pSymbol, ZBSymbol) && dynamic_cast<ZBSymbol*>(&Symbol)->GetSymbolName() == m_SymbolName)
    {
        m_Found = true;
    }
    else if (ISA(pSymbol, PSS_LinkSymbol) &&
             dynamic_cast<PSS_LinkSymbol*>(&Symbol)->GetSymbolName() == m_SymbolName)
    {
        m_Found = true;
    }

    return false;
}
