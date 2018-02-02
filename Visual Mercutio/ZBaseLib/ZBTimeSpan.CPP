// ZBTimeSpan.cpp : implementation of the ZDDocumentReadWrite class

#include <StdAfx.h>

#include "ZBTimeSpan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBTimeSpan construction/destruction
// The default is the zero time.
ZBTimeSpan::ZBTimeSpan()
{
}

ZBTimeSpan::~ZBTimeSpan()
{
}

const ZBTimeSpan & ZBTimeSpan::operator=( const ZBTimeSpan &right )
{
	this->COleDateTimeSpan ::operator=( (COleDateTimeSpan &)right );
	return *this;
}

const ZBTimeSpan & ZBTimeSpan::operator=( const COleDateTimeSpan &right )
{
	this->COleDateTimeSpan ::operator=( (COleDateTimeSpan &)right );
	return *this;
}

const ZBTimeSpan & ZBTimeSpan::operator=( const CTimeSpan &right )
{
	SetDateTimeSpan( (long)right.GetDays(), right.GetHours(), right.GetMinutes(), right.GetSeconds() );
	return *this;
}

void ZBTimeSpan::Clear()
{
	m_span = 0;
}

ZBTimeSpan* ZBTimeSpan::Clone()
{
	ZBTimeSpan*	pObject = new ZBTimeSpan( *this );
	return pObject;
}

CString ZBTimeSpan::GetStandardFormatedTimeSpan()
{
	if ( IsEmpty() )
	{
		return _T( "" );
	}

	return COleDateTimeSpan::Format( _T( "%H:%M:%S" ) );
}

CString ZBTimeSpan::GetFormatedTimeSpan( UINT nFormatID )
{
	if ( IsEmpty() )
	{
		return _T( "" );
	}

	return COleDateTimeSpan::Format( nFormatID );
}

CString ZBTimeSpan::GetFormatedTimeSpan( CString Format )
{
	if ( IsEmpty() )
	{
		return _T( "" );
	}

	return COleDateTimeSpan::Format( (LPCTSTR)Format );
}
