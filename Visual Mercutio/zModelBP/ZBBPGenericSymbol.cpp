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

IMPLEMENT_SERIAL(ZBBPGenericSymbol, PSS_Symbol, g_DefVersion)

ZBBPGenericSymbol::ZBBPGenericSymbol(const CString Name /*= _T( "" )*/)
{
    PSS_Symbol::SetSymbolName(Name);
}

ZBBPGenericSymbol::~ZBBPGenericSymbol()
{}

ZBBPGenericSymbol::ZBBPGenericSymbol(const ZBBPGenericSymbol& src)
{
    *this = src;
}

ZBBPGenericSymbol& ZBBPGenericSymbol::operator=(const ZBBPGenericSymbol& src)
{
    // Call the base class assignement operator
    PSS_Symbol::operator=((const PSS_Symbol&)src);
    return *this;
}

CODComponent* ZBBPGenericSymbol::Dup() const
{
    return (new ZBBPGenericSymbol(*this));
}

BOOL ZBBPGenericSymbol::Create(UINT nID, const CString Name /*= _T( "" )*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = PSS_Symbol::Create(nID,
                                       AfxFindResourceHandle(MAKEINTRESOURCE(nID), _T("Symbol")),
                                       Name);

    m_IsInCreationProcess = false;

    return RetValue;
}

void ZBBPGenericSymbol::Serialize(CArchive& ar)
{
    TRACE(_T("ZBBPGenericSymbol::Serialize : Start\n"));

    // Serialize the canvas model.
    PSS_Symbol::Serialize(ar);

    TRACE(_T("ZBBPGenericSymbol::Serialize : End\n"));
}
