/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtFileProperties
//@module ZBExtFileProp.cpp | Implementation of the <c ZBExtFileProperties> class.
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

#include "ZBExtFileProp.h"

// Resources
#include "zModelRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 4 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

using namespace sfl;

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties construction/destruction

IMPLEMENT_SERIAL( ZBExtFileProperties, CObject, def_Version )

//@mfunc | ZBExtFileProperties | ZBExtFileProperties | Constructor.
//
//@syntax ZBExtFileProperties::ZBExtFileProperties(int nId);
//@syntax ZBExtFileProperties::ZBExtFileProperties(const ZBExtFileProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBExtFileProperties& | propProcess | The fill property to copy.
ZBExtFileProperties::ZBExtFileProperties()
{
    m_FileTitle            = _T( "" );
    m_Filename            = _T( "" );
    m_InsertionType        = 0;
    m_ActivationType    = 0;
}

ZBExtFileProperties::ZBExtFileProperties( const ZBExtFileProperties& propProcess )
{
    m_FileTitle            = propProcess.GetFileTitle();
    m_Filename            = propProcess.GetFilename();
    m_InsertionType        = propProcess.GetInsertionType();
    m_ActivationType    = propProcess.GetActivationType();
}

//@mfunc Destructor.
ZBExtFileProperties::~ZBExtFileProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties attributes

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBExtFileProperties::SetFileTitle( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_FileTitle = lpszValue;
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
void ZBExtFileProperties::SetFileTitleEx( const CString value )
{
    SetFileTitle( value );
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtFileProperties::SetFilename( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_Filename = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Decision List pointer!\n" ) );
        ASSERT( FALSE );
    }
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBExtFileProperties::SetFilenameEx( const CString value )
{
    SetFilename( value );
}

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties operations

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBExtFileProperties& ZBExtFileProperties::operator=( const ZBExtFileProperties& propProcess )
{
    SetFileTitle        ( propProcess.GetFileTitle() );
    SetFilename            ( propProcess.GetFilename() );
    SetInsertionType    ( propProcess.GetInsertionType() );
    SetActivationType    ( propProcess.GetActivationType() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBExtFileProperties::operator==( const ZBExtFileProperties propProcess ) const
{
    return ( GetFileTitle()            == propProcess.GetFileTitle()        &&
             GetFilename()            == propProcess.GetFilename()        &&
             GetInsertionType()        == propProcess.GetInsertionType()    &&
             GetActivationType()    == propProcess.GetActivationType() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBExtFileProperties::Merge( ZBExtFileProperties* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_FILE_TITLE )
        {
            m_FileTitle = pProperty->GetFileTitle();
        }

        if ( dwChangeFlags & Z_CHANGE_FILE_NAME )
        {
            m_Filename = pProperty->GetFilename();
        }

        if ( dwChangeFlags & Z_CHANGE_INSERTION_TYPE )
        {
            m_InsertionType = pProperty->GetInsertionType();
        }

        if ( dwChangeFlags & Z_CHANGE_ACTIVATION_TYPE )
        {
            m_ActivationType = pProperty->GetActivationType();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBExtFileProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBExtFileProperties::IsEqual( ZBExtFileProperties* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBExtFileProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBExtFileProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBExtFileProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBExtFileProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBExtFileProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBExtFileProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBExtFileProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        {
            strValue = m_FileTitle;
            break;
        }

        case Z_FILE_NAME:
        {
            strValue = m_Filename;
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

BOOL ZBExtFileProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        {
            throw new CODPropertyConversionException();
            break;
        }

        case Z_INSERTION_TYPE:
        {
            nValue = m_InsertionType;
            break;
        }

        case Z_ACTIVATION_TYPE:
        {
            nValue = m_ActivationType;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBExtFileProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        {
            throw new CODPropertyConversionException();
            break;
        }

        case Z_INSERTION_TYPE:
        {
            nValue = (UINT)m_InsertionType;
            break;
        }

        case Z_ACTIVATION_TYPE:
        {
            nValue = (UINT)m_ActivationType;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBExtFileProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        case Z_INSERTION_TYPE:
        case Z_ACTIVATION_TYPE:
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

BOOL ZBExtFileProperties::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        case Z_INSERTION_TYPE:
        case Z_ACTIVATION_TYPE:
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

//@mfunc | ZBExtFileProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBExtFileProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBExtFileProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBExtFileProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBExtFileProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBExtFileProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBExtFileProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        {
            m_FileTitle = lpszValue;
            break;
        }

        case Z_FILE_NAME:
        {
            m_Filename = lpszValue;
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

BOOL ZBExtFileProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        {
            throw new CODPropertyConversionException();
            break;
        }

        case Z_INSERTION_TYPE:
        {
            m_InsertionType = nValue;
            break;
        }

        case Z_ACTIVATION_TYPE:
        {
            m_ActivationType = nValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBExtFileProperties::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        {
            throw new CODPropertyConversionException();
            break;
        }

        case Z_INSERTION_TYPE:
        {
            m_InsertionType = (int)nValue;
            break;
        }

        case Z_ACTIVATION_TYPE:
        {
            m_ActivationType = (int)nValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBExtFileProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        case Z_INSERTION_TYPE:
        case Z_ACTIVATION_TYPE:
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

BOOL ZBExtFileProperties::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_FILE_TITLE:
        case Z_FILE_NAME:
        case Z_INSERTION_TYPE:
        case Z_ACTIVATION_TYPE:
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
// ZBExtFileProperties Property meta-data 

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties diagnostics

#ifdef _DEBUG
void ZBExtFileProperties::AssertValid() const
{
    CObject::AssertValid();
}

void ZBExtFileProperties::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );

    dc << _T( "Name = " )                << m_FileTitle        << _T( "\n" );
    dc << _T( "Deliverables = " )        << m_Filename        << _T( "\n" );
    dc << _T( "Insertion Type = " )        << m_InsertionType    << _T( "\n" );
    dc << _T( "Activation Type = " )    << m_ActivationType    << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBExtFileProperties::Serialize( CArchive& ar )
{
    if (ar.IsStoring())
    {
        ar << m_FileTitle;
        ar << m_Filename;
        ar << m_InsertionType;
        ar << m_ActivationType;
    }
    else
    {
        ar >> m_FileTitle;
        ar >> m_Filename;
        ar >> m_InsertionType;
        ar >> m_ActivationType;
    }
}
