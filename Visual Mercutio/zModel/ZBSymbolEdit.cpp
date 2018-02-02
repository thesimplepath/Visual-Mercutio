// ZBSymbolEdit.cpp: implementation of the ZBSymbolEdit class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbolEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_SERIAL( ZBSymbolEdit, CODTextComponent, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSymbolEdit::ZBSymbolEdit()
	: m_AutoSizeProp( TRUE )
{
}

ZBSymbolEdit::~ZBSymbolEdit()
{
}

BOOL ZBSymbolEdit::GetValue( const int nPropId, CString& strValue ) const
{
	return CODTextComponent::GetValue( nPropId, strValue );
}

BOOL ZBSymbolEdit::GetValue( const int nPropId, int& nValue ) const
{
	switch ( nPropId )
	{
		case OD_PROP_AUTOSIZE:
		{
			nValue = m_AutoSizeProp;
		}

		default:
		{
			return CODTextComponent::GetValue( nPropId, nValue );
		}
	}

	return TRUE;
}

BOOL ZBSymbolEdit::GetValue( const int nPropId, UINT& nValue ) const
{
	switch ( nPropId )
	{
		case OD_PROP_AUTOSIZE:
		{
			nValue = m_AutoSizeProp;
		}

		default:
		{
			return CODTextComponent::GetValue( nPropId, nValue );
		}
	}

	return TRUE;
}

BOOL ZBSymbolEdit::GetValue( const int nPropId, DWORD& dwValue ) const
{
	switch ( nPropId )
	{
		case OD_PROP_AUTOSIZE:
		{
			dwValue = m_AutoSizeProp;
		}

		default:
		{
			return CODTextComponent::GetValue( nPropId, dwValue );
		}
	}

	return TRUE;
}

BOOL ZBSymbolEdit::GetValue( const int nPropId, float& fValue ) const
{
	return CODTextComponent::GetValue( nPropId, fValue );
}

BOOL ZBSymbolEdit::SetValue( const int nPropId, LPCTSTR lpszValue )
{
	return CODTextComponent::SetValue( nPropId, lpszValue );
}

BOOL ZBSymbolEdit::SetValue( const int nPropId, const int nValue )
{
	switch ( nPropId )
	{
		case OD_PROP_AUTOSIZE:
		{
			m_AutoSizeProp = nValue;
		}

		default:
		{
			return CODTextComponent::SetValue( nPropId, nValue );
		}
	}

	return TRUE;
}

BOOL ZBSymbolEdit::SetValue( const int nPropId, const UINT nValue )
{
	switch ( nPropId )
	{
		case OD_PROP_AUTOSIZE:
		{
			m_AutoSizeProp = nValue;
		}

		default:
		{
			return CODTextComponent::SetValue( nPropId, nValue );
		}
	}

	return TRUE;
}

BOOL ZBSymbolEdit::SetValue( const int nPropId, const DWORD dwValue )
{
	switch ( nPropId )
	{
		case OD_PROP_AUTOSIZE:
		{
			m_AutoSizeProp = dwValue;
		}

		default:
		{
			return CODTextComponent::SetValue( nPropId, dwValue );
		}
	}

	return TRUE;
}

BOOL ZBSymbolEdit::SetValue( const int nPropId, const float fValue )
{
	return CODTextComponent::SetValue( nPropId, fValue );
}
