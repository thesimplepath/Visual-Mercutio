/////////////////////////////////////////////////////////////////////////////
//@doc ZBStateLink
//@module ZBStateLink.cpp | Implementation of the <c ZBStateLink> class.
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
#include "ZBStateLink.h"

#include "zModel\ProcGraphModelMdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL( ZBStateLink, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBStateLink::ZBStateLink( ZBLinkSymbol*                pLinkSymbol    /*= NULL*/,
                          LinkDirection                Direction    /*= EnteringUp*/,
                          ZDProcessGraphModelMdl*    pModel        /*= NULL*/ )
    : m_pLinkSymbol    ( pLinkSymbol ),
      m_Direction    ( Direction ),
      m_pModel        ( pModel )
{
}

ZBStateLink::~ZBStateLink()
{
}

ZBStateLink::ZBStateLink( const ZBStateLink& src )
{
    *this = src;
}

ZBStateLink& ZBStateLink::operator=( const ZBStateLink& src )
{
    m_pLinkSymbol    = src.m_pLinkSymbol;
    m_Direction        = src.m_Direction;
    m_pModel        = src.m_pModel;

    return *this;
}

ZBStateLink* ZBStateLink::Clone() const
{
    return ( new ZBStateLink( *this ) );
}

bool ZBStateLink::IsEqual( const ZBStateLink& Right )
{
    return ( m_pLinkSymbol != NULL && Right.GetpLinkSymbol() &&
             m_pLinkSymbol->GetSymbolReferenceNumber() == Right.GetpLinkSymbol()->GetSymbolReferenceNumber() &&
             GetDirection() == Right.GetDirection() );
}

bool ZBStateLink::IsEqual( const ZBLinkSymbol& LinkSymbol )
{
    return ( m_pLinkSymbol != NULL &&
             m_pLinkSymbol->GetSymbolReferenceNumber() == const_cast<ZBLinkSymbol&>( LinkSymbol ).GetSymbolReferenceNumber() );
}

/////////////////////////////////////////////////////////////////////////////
// ZBStateLink diagnostics

#ifdef _DEBUG
void ZBStateLink::AssertValid() const
{
    CObject::AssertValid();
}

void ZBStateLink::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBStateLink serialization

void ZBStateLink::Serialize ( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Write the elements
        // Serialize the current object reference number
        CString EmptyString;
        EmptyString.Empty();

        if ( m_pLinkSymbol )
        {
            ar << m_pLinkSymbol->GetSymbolReferenceNumberStr();
        }
        else
        {
            ar << EmptyString;
        }
    }
    else
    {
        // Read the elements
        // Retreive the object reference number
        CString ReferenceNumberStr;
        ar >> ReferenceNumberStr;

        // Initialize current object to null
        m_pLinkSymbol = NULL;

        if ( !ReferenceNumberStr.IsEmpty() && m_pModel != NULL )
        {
            // Find back the right symbol pointer
            int RefNumber = atoi( ReferenceNumberStr );
            CODComponentSet* pSet = m_pModel->FindSymbolByRefNumber( RefNumber, true );

            if ( pSet && pSet->GetSize() > 0 && ISA( pSet->GetAt( 0 ), ZBLinkSymbol ) )
            {
                m_pLinkSymbol = dynamic_cast<ZBLinkSymbol*>( pSet->GetAt( 0 ) );
            }
        }
    }
}
