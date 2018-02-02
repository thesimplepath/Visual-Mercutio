/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtAppProperties
//@module ZBExtAppProp.cpp | Implementation of the <c ZBExtAppProperties> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 07/2001
// 
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ZBExtAppProp.h"

// Resources
#include "zModelRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 13 octobre - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

using namespace sfl;

/////////////////////////////////////////////////////////////////////////////
// ZBExtAppProperties construction/destruction

IMPLEMENT_SERIAL( ZBExtAppProperties, CObject, def_Version )

//@mfunc | ZBExtAppProperties | ZBExtAppProperties | Constructor.
//
//@syntax ZBExtAppProperties::ZBExtAppProperties(int nId);
//@syntax ZBExtAppProperties::ZBExtAppProperties(const ZBExtAppProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBExtAppProperties& | propProcess | The fill property to copy.
ZBExtAppProperties::ZBExtAppProperties()
{
	m_CommandTitle				= _T( "" );
	m_CommandLine				= _T( "" );
	m_CommandParameters			= _T( "" );
	m_CommandStartupDirectory	= _T( "" );

	m_PriorityLevel				= 0;
	m_WindowStartMode			= 0;
}

ZBExtAppProperties::ZBExtAppProperties( const ZBExtAppProperties& propProcess )
{
	m_CommandTitle				= propProcess.GetCommandTitle();
	m_CommandLine				= propProcess.GetCommandLine();
	m_CommandParameters			= propProcess.GetCommandParameters();
	m_CommandStartupDirectory	= propProcess.GetCommandStartupDirectory();
	m_PriorityLevel				= propProcess.GetPriorityLevel();
	m_WindowStartMode			= propProcess.GetWindowStartMode();
}

//@mfunc Destructor.
ZBExtAppProperties::~ZBExtAppProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBExtAppProperties attributes

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBExtAppProperties::SetCommandTitle( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_CommandTitle = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid command title pointer!\n" ) );
		ASSERT( FALSE );
	}
}

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBExtAppProperties::SetCommandTitleEx( const CString value )
{
	SetCommandTitle( value );
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtAppProperties::SetCommandLine( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_CommandLine = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid command line pointer!\n" ) );
		ASSERT( FALSE );
	}
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtAppProperties::SetCommandLineEx( const CString value )
{
	SetCommandLine( value );
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtAppProperties::SetCommandParameters( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_CommandParameters = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid command parameters pointer!\n" ) );
		ASSERT( FALSE );
	}
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtAppProperties::SetCommandParametersEx( const CString value )
{
	SetCommandParameters( value );
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtAppProperties::SetCommandStartupDirectory( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_CommandStartupDirectory = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid command startup directory pointer!\n" ) );
		ASSERT( FALSE );
	}
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtAppProperties::SetCommandStartupDirectoryEx( const CString value )
{
	SetCommandStartupDirectory( value );
}

/////////////////////////////////////////////////////////////////////////////
// ZBExtAppProperties operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBExtAppProperties& ZBExtAppProperties::operator=( const ZBExtAppProperties& propProcess )
{
	SetCommandTitle				( propProcess.GetCommandTitle() );
	SetCommandLine				( propProcess.GetCommandLine() );
	SetCommandParameters		( propProcess.GetCommandParameters() );
	SetCommandStartupDirectory	( propProcess.GetCommandStartupDirectory() );
	SetPriorityLevel			( propProcess.GetPriorityLevel() );
	SetWindowStartMode			( propProcess.GetWindowStartMode() );

	return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBExtAppProperties::operator==( const ZBExtAppProperties propProcess ) const
{
	return ( GetCommandTitle()				== propProcess.GetCommandTitle() &&
			 GetCommandLine()				== propProcess.GetCommandLine() &&
			 GetCommandParameters()			== propProcess.GetCommandParameters() &&
			 GetCommandStartupDirectory()	== propProcess.GetCommandStartupDirectory() &&
			 GetPriorityLevel()				== propProcess.GetPriorityLevel() &&
			 GetWindowStartMode()			== propProcess.GetWindowStartMode() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBExtAppProperties::Merge( ZBExtAppProperties* pProperty, DWORD dwChangeFlags )
{
	if ( pProperty )
	{
		if ( dwChangeFlags & Z_CHANGE_COMMAND_TITLE )
		{
			m_CommandTitle = pProperty->GetCommandTitle();
		}

		if ( dwChangeFlags & Z_CHANGE_COMMAND_LINE )
		{
			m_CommandLine = pProperty->GetCommandLine();
		}

		if ( dwChangeFlags & Z_CHANGE_COMMAND_PARAM )
		{
			m_CommandParameters = pProperty->GetCommandParameters();
		}

		if ( dwChangeFlags & Z_CHANGE_COMMAND_STARTUPDIR )
		{
			m_CommandStartupDirectory = pProperty->GetCommandStartupDirectory();
		}

		if ( dwChangeFlags & Z_CHANGE_PRIORITY_LEVEL )
		{
			m_PriorityLevel = pProperty->GetPriorityLevel();
		}

		if ( dwChangeFlags & Z_CHANGE_WINDOW_STARTMODE )
		{
			m_WindowStartMode = pProperty->GetWindowStartMode();
		}
	}
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBExtAppProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBExtAppProperties::IsEqual( ZBExtAppProperties* pProp )
{
	if ( pProp )
	{
		return ( *this == *pProp );
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBExtAppProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBExtAppProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBExtAppProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBExtAppProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBExtAppProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBExtAppProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBExtAppProperties::GetValue( const int nPropId, CString& strValue ) const
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		{
			strValue = m_CommandTitle;
			break;
		}

		case Z_COMMAND_LINE:
		{
			strValue = m_CommandLine;
			break;
		}

		case Z_COMMAND_PARAM:
		{
			strValue = m_CommandParameters;
			break;
		}

		case Z_COMMAND_STARTUPDIR:
		{
			strValue = m_CommandStartupDirectory;
			break;
		}

		default:
		{
			throw new CODPropertyConversionException();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBExtAppProperties::GetValue( const int nPropId, int& nValue ) const
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		{
			throw new CODPropertyConversionException();
			break;
		}

		case Z_PRIORITY_LEVEL:
		{
			nValue = m_PriorityLevel;
			break;
		}

		case Z_WINDOW_STARTMODE:
		{
			nValue = m_WindowStartMode;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBExtAppProperties::GetValue( const int nPropId, UINT& nValue ) const
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		{
			throw new CODPropertyConversionException();
			break;
		}

		case Z_PRIORITY_LEVEL:
		{
			nValue = (UINT)m_PriorityLevel;
			break;
		}

		case Z_WINDOW_STARTMODE:
		{
			nValue = (UINT)m_WindowStartMode;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBExtAppProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		case Z_PRIORITY_LEVEL:
		case Z_WINDOW_STARTMODE:
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

BOOL ZBExtAppProperties::GetValue( const int nPropId, float& fValue ) const
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		case Z_PRIORITY_LEVEL:
		case Z_WINDOW_STARTMODE:
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

//@mfunc | ZBExtAppProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBExtAppProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBExtAppProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBExtAppProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBExtAppProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBExtAppProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBExtAppProperties::SetValue( const int nPropId, LPCTSTR lpszValue	)
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		{
			m_CommandTitle = lpszValue;
			break;
		}

		case Z_COMMAND_LINE:
		{
			m_CommandLine = lpszValue;
			break;
		}

		case Z_COMMAND_PARAM:
		{
			m_CommandParameters = lpszValue;
			break;
		}

		case Z_COMMAND_STARTUPDIR:
		{
			m_CommandStartupDirectory = lpszValue;
			break;
		}

		default:
		{
			throw new CODPropertyConversionException();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBExtAppProperties::SetValue( const int nPropId, const int nValue )
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		{
			throw new CODPropertyConversionException();
			break;
		}

		case Z_PRIORITY_LEVEL:
		{
			m_PriorityLevel = nValue;
			break;
		}

		case Z_WINDOW_STARTMODE:
		{
			m_WindowStartMode = nValue;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBExtAppProperties::SetValue( const int nPropId, const UINT nValue )
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		{
			throw new CODPropertyConversionException();
			break;
		}

		case Z_PRIORITY_LEVEL:
		{
			m_PriorityLevel = (int)nValue;
			break;
		}

		case Z_WINDOW_STARTMODE:
		{
			m_WindowStartMode = (int)nValue;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL ZBExtAppProperties::SetValue( const int nPropId, const DWORD dwValue )
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		case Z_PRIORITY_LEVEL:
		case Z_WINDOW_STARTMODE:
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

BOOL ZBExtAppProperties::SetValue( const int nPropId, const float fValue )
{
	switch ( nPropId )
	{
		case Z_COMMAND_TITLE:
		case Z_COMMAND_LINE:
		case Z_COMMAND_PARAM:
		case Z_COMMAND_STARTUPDIR:
		case Z_PRIORITY_LEVEL:
		case Z_WINDOW_STARTMODE:
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
// ZBExtAppProperties diagnostics

#ifdef _DEBUG
void ZBExtAppProperties::AssertValid() const
{
	CObject::AssertValid();
}

void ZBExtAppProperties::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );

	dc << _T( "Title = " )					<< m_CommandTitle				<< _T( "\n" );
	dc << _T( "Command line = " )			<< m_CommandLine				<< _T( "\n" );
	dc << _T( "Command param = " )			<< m_CommandParameters			<< _T( "\n" );
	dc << _T( "Command startup dir = " )	<< m_CommandStartupDirectory	<< _T( "\n" );
	dc << _T( "Priority = " )				<< m_PriorityLevel				<< _T( "\n" );
	dc << _T( "Window mode = " )			<< m_WindowStartMode			<< _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBExtAppProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBExtAppProperties::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		ar << m_CommandTitle;
		ar << m_CommandLine;
		ar << m_CommandParameters;
		ar << m_CommandStartupDirectory;
		ar << m_PriorityLevel;
		ar << m_WindowStartMode;
	}
	else
	{
		ar >> m_CommandTitle;
		ar >> m_CommandLine;
		ar >> m_CommandParameters;
		ar >> m_CommandStartupDirectory;
		ar >> m_PriorityLevel;
		ar >> m_WindowStartMode;
	}
}
