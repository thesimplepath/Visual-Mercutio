/****************************************************************************
 * ==> PSS_GenericSymbolBP -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic symbol for banking process              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GenericSymbolBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_GenericSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_GenericSymbolBP
//---------------------------------------------------------------------------
PSS_GenericSymbolBP::PSS_GenericSymbolBP(const CString& name) :
    PSS_Symbol()
{
    PSS_Symbol::SetSymbolName(name);
}
//---------------------------------------------------------------------------
PSS_GenericSymbolBP::PSS_GenericSymbolBP(const PSS_GenericSymbolBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_GenericSymbolBP::~PSS_GenericSymbolBP()
{}
//---------------------------------------------------------------------------
PSS_GenericSymbolBP& PSS_GenericSymbolBP::operator = (const PSS_GenericSymbolBP& other)
{
    PSS_Symbol::operator = ((const PSS_Symbol&)other);
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_GenericSymbolBP::Create(UINT nID, const CString& name)
{
    BOOL result;

    try
    {
        m_IsInCreationProcess = true;
        result                = PSS_Symbol::Create(nID, AfxFindResourceHandle(MAKEINTRESOURCE(nID), _T("Symbol")), name);
    }
    catch (...)
    {
        m_IsInCreationProcess = false;
        throw;
    }

    m_IsInCreationProcess = false;
    return result;
}
//---------------------------------------------------------------------------
CODComponent* PSS_GenericSymbolBP::Dup() const
{
    return new PSS_GenericSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_GenericSymbolBP::Serialize(CArchive& ar)
{
    TRACE(_T("PSS_GenericSymbolBP::Serialize - Start\n"));

    PSS_Symbol::Serialize(ar);

    TRACE(_T("PSS_GenericSymbolBP::Serialize - End\n"));
}
//---------------------------------------------------------------------------
