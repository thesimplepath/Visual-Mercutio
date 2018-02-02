// ZBSymbolLabel.cpp: implementation of the ZBSymbolLabel class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbolLabel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_SERIAL( ZBSymbolLabel, CODLabelComponent, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSymbolLabel::ZBSymbolLabel( bool NotifyParent /*= false*/ )
	: m_NotifyParent( NotifyParent )
{
}

ZBSymbolLabel::ZBSymbolLabel( CODSymbolComponent* pOwner, bool NotifyParent /*= false*/ )
	: CODLabelComponent	( pOwner ),
	  m_NotifyParent	( NotifyParent )
{
}

ZBSymbolLabel::ZBSymbolLabel( const OD_CONTROL_POINT ctlPoint, bool NotifyParent /*= false*/ )
	: CODLabelComponent	( ctlPoint ),
	  m_NotifyParent	( NotifyParent )
{
}

ZBSymbolLabel::~ZBSymbolLabel()
{
}

ZBSymbolLabel::ZBSymbolLabel( const ZBSymbolLabel& src )
{
	*this = src;
}

ZBSymbolLabel& ZBSymbolLabel::operator=( const ZBSymbolLabel& src )
{
	// Call the base class assignement operator
	CODLabelComponent::operator=( (const CODLabelComponent&)src );
	m_NotifyParent = src.m_NotifyParent;

	return *this;
}

CODComponent* ZBSymbolLabel::Dup() const
{
	return ( new ZBSymbolLabel( *this ) );
}

void ZBSymbolLabel::Serialize( CArchive& ar )
{
	// Serialize the label symbol
	CODLabelComponent::Serialize( ar );

	// Only if the object is serialize from and to a document
	if ( ar.m_pDocument )
	{
		if ( ar.IsStoring() )
		{
			ar << (WORD)m_NotifyParent;
		}
		else
		{
			WORD wValue;
			ar >> wValue;
			m_NotifyParent = ( ( wValue == 1 ) ? ( true ) : ( false ) );
		}
	}
}
