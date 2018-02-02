/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPRuleListProperties
//@module ZBBPRuleListProp.cpp | Implementation of the <c ZBBPRuleListProperties> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 04/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ZBBPRuleListProp.h"

// Resources
#include "zRMdlBP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 22 novembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

using namespace sfl;

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties construction/destruction

IMPLEMENT_SERIAL( ZBBPRuleListProperties, CODIntProperty, def_Version )

//@mfunc | ZBBPRuleListProperties | ZBBPRuleListProperties | Constructor.
//
//@syntax ZBBPRuleListProperties::ZBBPRuleListProperties(int nId);
//@syntax ZBBPRuleListProperties::ZBBPRuleListProperties(const ZBBPRuleListProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPRuleListProperties& | propProcess | The fill property to copy.
ZBBPRuleListProperties::ZBBPRuleListProperties( int nId )
	: CODIntProperty( nId )
{
	m_RuleList = _T( "" );

	RegisterProperties();
}

ZBBPRuleListProperties::ZBBPRuleListProperties( const ZBBPRuleListProperties& propProcess )
	: CODIntProperty( propProcess.GetId() )
{
	m_RuleList = propProcess.GetRuleList();

	RegisterProperties();
}

//@mfunc Destructor.
ZBBPRuleListProperties::~ZBBPRuleListProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties attributes

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPRuleListProperties::SetRuleList( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_RuleList = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid Task List pointer!\n" ) );
		ASSERT( FALSE );
	}
}

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPRuleListProperties::SetRuleListEx( const CString value )
{
	SetRuleList( value );
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties operations

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPRuleListProperties::CompareId( const int nId ) const
{
	int nIdMin = m_nId;
	int nIdMax = m_nId + Z_RULE_LIST;

	return ( nId >= nIdMin && nId <= nIdMax );
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPRuleListProperties& ZBBPRuleListProperties::operator=( const ZBBPRuleListProperties& propProcess )
{
	SetId( propProcess.GetId() );
	SetRuleList( propProcess.GetRuleList() );

	return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPRuleListProperties::operator==( const ZBBPRuleListProperties propProcess ) const
{
	return ( GetRuleList() == propProcess.GetRuleList() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPRuleListProperties::Merge( CODProperty* pProperty, DWORD dwChangeFlags )
{
	ZBBPRuleListProperties* pProcessProps = (ZBBPRuleListProperties*)pProperty;

	if ( pProcessProps )
	{
		if ( dwChangeFlags & Z_CHANGE_RULE_LIST )
		{
			m_RuleList = pProcessProps->GetRuleList();
		}
	}
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPRuleListProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPRuleListProperties::IsEqual( CODProperty* pProp )
{
	if ( GetId() == pProp->GetId() )
	{
		ZBBPRuleListProperties* pProcessProp = (ZBBPRuleListProperties*)pProp;

		if ( pProcessProp )
		{
			return ( *this == *pProcessProp );
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPRuleListProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPRuleListProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPRuleListProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPRuleListProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPRuleListProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPRuleListProperties::GetValue(const int nPropId, float& fValue) const
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to retrieve.
//@parm CString& | strValue | Variable to assign return value to.
//@parm int& | nValue | Variable to assign return value to.
//@parm UINT& | nValue | Variable to assign return value to.
//@parm DWORD& | dwValue | Variable to assign return value to.
//@parm float& | fValue | Variable to assign return value to.
//
//@comm See <t Fill Property Identifiers> for a list property IDs supported.
// This function will throw a <c CODPropertyConversionException> exception
// if the data type of the argument passed in is not compatible with the
// given property identifier.

BOOL ZBBPRuleListProperties::GetValue( const int nPropId, CString& strValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			strValue = m_RuleList;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::GetValue( const int nPropId, int& nValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::GetValue( const int nPropId, UINT& nValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::GetValue( const int nPropId, float& fValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

//@mfunc | ZBBPRuleListProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPRuleListProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPRuleListProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPRuleListProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPRuleListProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPRuleListProperties::SetValue(const int nPropId, const float fValue)
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to set.
//@parm LPCTSTR | lpszValue | Input value to assign to the specified property.
//@parm const int | nValue | Input value to assign to the specified property.
//@parm const UINT | nValue | Input value to assign to the specified property.
//@parm const DWORD | dwValue | Input value to assign to the specified property.
//@parm const float | fValue | Input value to assign to the specified property.
//
//@comm See <t Fill Property Identifiers> for a list property IDs supported.
// This function will throw a <c CODPropertyConversionException> exception
// if the data type of the argument passed in is not compatible with the
// given property identifier.

BOOL ZBBPRuleListProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			m_RuleList = lpszValue;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::SetValue( const int nPropId, const int nValue )
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::SetValue( const int nPropId, const UINT nValue )
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::SetValue( const int nPropId, const DWORD dwValue )
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBBPRuleListProperties::SetValue( const int nPropId, const float fValue )
{
	switch ( nPropId )
	{
		case Z_RULE_LIST:
		{
			throw new CODPropertyConversionException();
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties Property meta-data 

bool ZBBPRuleListProperties::RegisterProperties()
{
	static bool propsRegistered = false;

	if ( !propsRegistered )
	{
		bool success = true;

		if ( success )
		{
			success = RegisterProperty( Z_RULE_LIST,
										IDS_Z_RULE_LIST_NAME,
										IDS_Z_RULE_LIST_DESC,
										_PropertyAccessor( &ZBBPRuleListProperties::GetRuleList,
														   &ZBBPRuleListProperties::SetRuleListEx ),
										VT_BSTR,
										PROP_DIRECT );
		}

		if ( !success )
		{
			ZBBPRuleListProperties::GetPropertyMap().DeleteAll();
		}

		propsRegistered = success;
	}

	return propsRegistered;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties diagnostics

#ifdef _DEBUG
void ZBBPRuleListProperties::AssertValid() const
{
	CODIntProperty::AssertValid();
}

void ZBBPRuleListProperties::Dump( CDumpContext& dc ) const
{
	CODIntProperty::Dump( dc );

	dc << _T( "Rule list = " ) << m_RuleList << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPRuleListProperties::Serialize( CArchive& ar )
{
	CODIntProperty::Serialize( ar );

	if ( ar.IsStoring() )
	{
		TRACE( _T( "ZBBPRuleListProperties::Serialize : Start Save\n" ) );

		PUT_SCHEMA( ar, ZBBPRuleListProperties );

		ar << m_RuleList;

		TRACE( _T( "ZBBPRuleListProperties::Serialize : End Save\n" ) );
	}
	else
	{
		TRACE( _T( "ZBBPRuleListProperties::Serialize : Start Read\n" ) );

		UINT nSchema;
		GET_SCHEMA( ar, nSchema );

		ar >> m_RuleList;

		TRACE( _T( "ZBBPRuleListProperties::Serialize : End Read\n" ) );
	}
}
