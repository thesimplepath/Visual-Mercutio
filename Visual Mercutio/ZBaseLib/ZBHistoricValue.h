/////////////////////////////////////////////////////////////////////////////
//@doc ZBHistoricValue
//@module ZBHistoricValue.h | Interface of the <c ZBHistoricValue> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zForms library.
// See these sources for detailed information regarding
// zForms libraries.
//
// Author:       Dom
// <nl>Created:         03/2000
// <nl>Description:  ZBHistoricValue keep historic values for a specific name
//

#ifndef ZBHistoricValue_h
#define ZBHistoricValue_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBHistoricValue
{
public:

    // Default contructor
    ZBHistoricValue( const CString EntityName = "" );

    // Copy constructor
    ZBHistoricValue( const ZBHistoricValue &right );

    // Destructor
    virtual ~ZBHistoricValue();

    // Assignement operator
    const ZBHistoricValue & operator=( const ZBHistoricValue &right );

    // Clone method
    ZBHistoricValue* Clone ();

    // Return the number of values.
    size_t GetCount () const;

    // return the index of an historic value, 
    // if not found return -1
    int FindHistoricValue ( const CString& Value ) const;

    // return true if the historic value already exist
    bool HistoricValueExist ( const CString& Value ) const
    {
        return ( FindHistoricValue( Value ) != -1 ) ? true : false;
    }

    // Add a new historic value into the FieldValueHistoryArray.
    void AddHistoricValue ( const CString Value );

    // Remove a specific historic value from the manager.
    bool RemoveHistoricValue ( const CString& Value );

    CString GetValueAt( size_t Index ) const;

    const CStringArray& GetValueArray () const;

    // remove the history.
    void FreeHistoric ();

    // The field name.
    const CString GetEntityName () const;
    void SetEntityName ( CString value );

private:

    // Contains the history string values.
    CStringArray    m_ValueHistoryArray;
    CString            m_EntityName;
};

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<( CDumpContext& dc, ZBHistoricValue src );
#endif

CArchive& AFXAPI operator<<( CArchive& ar, ZBHistoricValue src );
CArchive& AFXAPI operator>>( CArchive& ar, ZBHistoricValue& src );

// Class ZBHistoricValue 

inline size_t ZBHistoricValue::GetCount () const
{
      return m_ValueHistoryArray.GetSize();
}

inline CString ZBHistoricValue::GetValueAt( size_t Index ) const
{
    return ( Index < GetCount() ) ? m_ValueHistoryArray.GetAt( Index ) : _T( "" );
}

inline const CStringArray& ZBHistoricValue::GetValueArray () const
{
      return m_ValueHistoryArray;
}

inline const CString ZBHistoricValue::GetEntityName () const
{
  return m_EntityName;
}

inline void ZBHistoricValue::SetEntityName ( CString value )
{
  m_EntityName = value;
}

#endif