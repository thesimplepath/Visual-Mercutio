/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtApps
//@module ZBExtApps.h | Interface of the <c ZBExtApps> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         07/2001
// <nl>Description:  ZBExtApps external application manager
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBExtApps_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZBExtApps_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 8 juillet 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration

class ZBExtAppProperties;

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library

using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBExtAppPropertiesSet | An array of ZBSymbolEntity pointers.
//@iex typedef CCArray_T<ZBExtAppProperties*,ZBExtAppProperties*> ZBExtAppPropertiesSet;
typedef CCArray_T<ZBExtAppProperties*,ZBExtAppProperties*> ZBExtAppPropertiesSet;

//@type ZBExtAppPropertiesIterator | An iterator for ZBExtAppPropertiesSet collections.
//@iex typedef Iterator_T<ZBExtAppProperties*> ZBExtAppPropertiesIterator;
typedef Iterator_T<ZBExtAppProperties*> ZBExtAppPropertiesIterator;

/////////////////////////////////////////////////////////////////////////////
// ZBExtApps class

class AFX_EXT_CLASS ZBExtApps : public CObject
{
    DECLARE_SERIAL( ZBExtApps )

public:

    ZBExtApps( CODSymbolComponent* pParent = NULL );
    virtual ~ZBExtApps();

    /* Copy constructor. */
    ZBExtApps( const ZBExtApps& src );

    /* Assignment operator. */
    ZBExtApps& operator=( const ZBExtApps& src );

    /* Create a duplicate copy of this object. */
    virtual ZBExtApps* Dup() const;

    // Sets the parent symbol object
    void SetParent( CODSymbolComponent* pParent );

    // Create the initial properties
    bool CreateInitialProperties();

    // Add a new ExtApp,
    // and return the index of the new added ExtApp
    // Return -1 if the function fails
    int AddNewExtApp();

    // Add a new ExtApp,
    // and return the index of the new added ExtApp
    // Return -1 if the function fails
    int AddExtApp( ZBExtAppProperties* pProperty );

    // Delete an ExtApp
    bool DeleteExtApp( size_t Index );
    bool DeleteExtApp( const CString CommandTitle );
    bool DeleteExtApp( ZBExtAppProperties* pProperty );

    // Return true if the ExtApp already exists
    bool ExtAppExist( const CString CommandTitle ) const;

    // Retrieve the right ExtApp properties base on the ExtApp file name
    ZBExtAppProperties* LocateExtApp( const CString CommandTitle ) const;

    ZBExtAppPropertiesSet& GetExtAppSet()
    {
        return m_Set;
    }

    // Return the counter of ExtApps
    size_t GetExtAppCount() const
    {
        return m_Set.GetSize();
    }

    ZBExtAppProperties* GetProperty( size_t Index ) const
    {
        if ( Index < GetExtAppCount() )
        {
            return m_Set.GetAt( Index );
        }

        return NULL;
    }

    // Returns the index of the first empty element if there is,
    // otherwise, return -1
    int LocateFirstEmptyExtApp() const;

    // Remove only empty elements
    void RemoveAllEmptyExtApps();

    // Remove all elements
    void RemoveAllExtApps();

    /* Gets the file title at the specific Index. */
    CString GetCommandTitle( size_t Index ) const;

    //@cmember
    /* Sets the file title at the specific Index. */
    void SetCommandTitle( size_t Index, CString Value );

    //@cmember
    /* Gets the file name at the specific Index. */
    CString GetCommandLine( size_t Index ) const;

    //@cmember
    /* Sets the file name at the specific Index. */
    void SetCommandLine( size_t Index, CString Value );

    //@cmember
    /* Gets the file name at the specific Index. */
    CString GetCommandParameters( size_t Index ) const;

    //@cmember
    /* Sets the file name at the specific Index. */
    void SetCommandParameters( size_t Index, CString Value );

    //@cmember
    /* Gets the file name at the specific Index. */
    CString GetCommandStartupDirectory( size_t Index ) const;

    //@cmember
    /* Sets the file name at the specific Index. */
    void SetCommandStartupDirectory( size_t Index, CString Value );

    //@cmember
    /* Gets the insertion type at the specific Index. */
    int GetPriorityLevel( size_t Index ) const;

    //@cmember
    /* Sets the insertion type at the specific Index. */
    void SetPriorityLevel( size_t Index, const int value );

    //@cmember
    /* Gets the activation type at the specific Index. */
    int GetWindowStartMode( size_t Index ) const;

    //@cmember
    /* Sets the activation type at the specific Index. */
    void SetWindowStartMode( size_t Index, const int value );

    /* Serializes the combinations. */
    virtual void Serialize( CArchive& ar );

private:

    CODSymbolComponent*        m_pParent;
    ZBExtAppPropertiesSet    m_Set;
};

#endif // !defined(AFX_ZBExtApps_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)