// ZBStringFormat.cpp: implementation of the ZBStringFormat class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBStringFormat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 1er février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBStringFormat, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBStringFormat::ZBStringFormat( FormatType	ft				/*= General*/,
								bool		UseSeparator	/*= false*/,
								int			DecimalPlace	/*= -1*/,
								CString		Currency		/*= ""*/,
								LCID		lcid			/*= 0*/)
	: m_ft			( ft ),
	  m_UseSeparator( UseSeparator ),
	  m_DecimalPlace( DecimalPlace ),
	  m_Currency	( Currency ),
	  m_lcid		( lcid )
{
	m_CustomFormat.Empty();

	if ( m_lcid == 0 )
	{
		m_lcid = ::GetUserDefaultLCID();
	}
}

ZBStringFormat::ZBStringFormat( CString CustomFormat, LCID lcid /*= 0*/ )
	: m_ft			( Custom ),
	  m_CustomFormat( CustomFormat ),
	  m_lcid		( lcid )
{
	m_Currency.Empty();

	if ( m_lcid == 0 )
	{
		m_lcid = ::GetUserDefaultLCID();
	}
}

ZBStringFormat::ZBStringFormat( const ZBStringFormat &right )
{
	*this = right;
}

ZBStringFormat::~ZBStringFormat()
{
	// JMR-MODIF - Le 15 février 2006 - Ajout du code de desctruction de l'objet.
	Release();
}

const ZBStringFormat & ZBStringFormat::operator=( const ZBStringFormat &right )
{
	m_ft			= right.m_ft;
	m_UseSeparator	= right.m_UseSeparator;
	m_DecimalPlace	= right.m_DecimalPlace;
	m_Currency		= right.m_Currency;
	m_CustomFormat	= right.m_CustomFormat;
	m_lcid			= right.m_lcid;

	return *this;
}

// JMR-MODIF - Le 15 février 2006 - Cette fonction permet de libérer les buffers utilisés par les chaînes CString.
void ZBStringFormat::Release()
{
	m_Currency.Empty();
	m_CustomFormat.Empty();
}

/////////////////////////////////////////////////////////////////////////////
// ZBStringFormat diagnostics

#ifdef _DEBUG
void ZBStringFormat::AssertValid() const
{
	CObject::AssertValid();
}

void ZBStringFormat::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialization

void ZBStringFormat::Serialize ( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// Write the elements
		ar << (int)m_ft;
		ar << (int)m_UseSeparator;
		ar << m_DecimalPlace;
		ar << m_Currency;
		ar << m_CustomFormat;
		ar << m_lcid;
	}
	else
	{
		// Read the elements
		int	value;
		ar >> value;
		m_ft = (FormatType)value;

		ar >> value;
		m_UseSeparator = ( value == 0 ) ? false : true;

		ar >> m_DecimalPlace;
		ar >> m_Currency;
		ar >> m_CustomFormat;
		ar >> m_lcid;
	}
}
