// **********************************************************************************************************
// *                                      Classe ZBBPGenericSymbol                                            *
// **********************************************************************************************************
// * JMR-MODIF - Le 19 octobre 2005 - Ajout de la classe ZBBPGenericSymbol.                                    *
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage de n'importe quel type de symbole. On initialise la        *
// * classe avec un pointeur vers la ressource du symbole, et celui-ci est entièrement pris en charge.        *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZBBPGenericSymbol.h"

IMPLEMENT_SERIAL(ZBBPGenericSymbol, ZBSymbol, g_DefVersion)

ZBBPGenericSymbol::ZBBPGenericSymbol( const CString Name /*= _T( "" )*/ )
{
    ZBSymbol::SetSymbolName( Name );
}

ZBBPGenericSymbol::~ZBBPGenericSymbol()
{
}

ZBBPGenericSymbol::ZBBPGenericSymbol( const ZBBPGenericSymbol& src )
{
    *this = src;
}

ZBBPGenericSymbol& ZBBPGenericSymbol::operator=( const ZBBPGenericSymbol& src )
{
    // Call the base class assignement operator
    ZBSymbol::operator=( (const ZBSymbol&)src );
    return *this;
}

CODComponent* ZBBPGenericSymbol::Dup() const
{
    return ( new ZBBPGenericSymbol( *this ) );
}

BOOL ZBBPGenericSymbol::Create( UINT nID, const CString Name /*= _T( "" )*/ )
{
    m_IsInCreationProcess = true;

    BOOL RetValue = ZBSymbol::Create( nID,
                                      AfxFindResourceHandle( MAKEINTRESOURCE( nID ), _T( "Symbol" ) ),
                                      Name );

    m_IsInCreationProcess = false;

    return RetValue;
}

void ZBBPGenericSymbol::Serialize( CArchive& ar )
{
    TRACE( _T( "ZBBPGenericSymbol::Serialize : Start\n" ) );

    // Serialize the canvas model.
    ZBSymbol::Serialize( ar );

    TRACE( _T( "ZBBPGenericSymbol::Serialize : End\n" ) );
}
