// ZBExtFilePropertyMgr.h: interface for the ZBExtFilePropertyMgr class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEXTFILEPROPERTYMGR_H__9FDFA8A5_FD6C_453B_9A4D_8B0425568139__INCLUDED_)
#define AFX_ZBEXTFILEPROPERTYMGR_H__9FDFA8A5_FD6C_453B_9A4D_8B0425568139__INCLUDED_

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

#include "ZBExtFiles.h"
#include "ZBExtFileProp.h"
#include "zProperty\ZIProperties.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 4 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBExtFilePropertyMgr
{
public:

	ZBExtFilePropertyMgr();
	virtual ~ZBExtFilePropertyMgr();

	/* Copy constructor. */
	ZBExtFilePropertyMgr( const ZBExtFilePropertyMgr& src );

	/* Assignment operator. */
	ZBExtFilePropertyMgr& operator=( const ZBExtFilePropertyMgr& src );

	/////////////////////////////////////////////////////////////////////////////
	// External Files methods

	// Returns the external file object reference
	ZBExtFiles& GetExtFiles()
	{
		return m_ExternalFiles;
	}

	// Return the counter of combinations
	size_t GetExtFileCount() const
	{
		return m_ExternalFiles.GetExtFileCount();
	}

	// Add a new extfile,
	// and return the index of the new added extfile
	// Return -1 if the function fails
	int AddNewExtFile()
	{
		return m_ExternalFiles.AddNewExtFile();
	}

	// Add a new extfile,
	// and return the index of the new added extfile
	// Return -1 if the function fails
	int AddExtFile( ZBExtFileProperties* pProperty )
	{
		return m_ExternalFiles.AddExtFile(pProperty);
	}

	// Delete an extfile
	bool DeleteExtFile( size_t Index )
	{
		return m_ExternalFiles.DeleteExtFile( Index );
	}

	bool DeleteExtFile( const CString Filename )
	{
		return m_ExternalFiles.DeleteExtFile( Filename );
	}

	bool DeleteExtFile( ZBExtFileProperties* pProperty )
	{
		return m_ExternalFiles.DeleteExtFile( pProperty );
	}

	// Return true if the extfile already exists
	bool ExtFileExist( const CString Filename ) const
	{
		return m_ExternalFiles.ExtFileExist( Filename );
	}

	// Retreive the right extfile properties base on the extfile filename
	ZBExtFileProperties* LocateExtFile( const CString Filename ) const
	{
		return m_ExternalFiles.LocateExtFile( Filename );
	}

	ZBExtFileProperties* GetExtFileProperty( size_t Index ) const
	{
		return m_ExternalFiles.GetProperty( Index );
	}

	// Returns the index of the first empty element if there is,
	// otherwise, return -1
	int LocateFirstEmptyExtFile() const
	{
		return m_ExternalFiles.LocateFirstEmptyExtFile();
	}

	// Remove only empty elements
	void RemoveAllEmptyExtFiles()
	{
		m_ExternalFiles.RemoveAllEmptyExtFiles();
	}

	// Remove all elements
	void RemoveAllExtFiles()
	{
		m_ExternalFiles.RemoveAllExtFiles();
	}

	/* Gets the file title at the specific Index. */
	CString GetFileTitle( size_t Index ) const
	{
		return m_ExternalFiles.GetFileTitle( Index );
	}

	//@cmember
	/* Sets the file title at the specific Index. */
	void SetFileTitle( size_t Index, CString Value )
	{
		m_ExternalFiles.SetFileTitle( Index, Value );
	}

	//@cmember
	/* Gets the filename at the specific Index. */
	CString GetFilename( size_t Index ) const
	{
		return m_ExternalFiles.GetFilename( Index );
	}

	//@cmember
	/* Sets the filename at the specific Index. */
	void SetFilename( size_t Index, CString Value )
	{
		m_ExternalFiles.SetFilename( Index, Value );
	}

	//@cmember
	/* Gets the insertion type at the specific Index. */
	int GetInsertionType( size_t Index ) const
	{
		return m_ExternalFiles.GetInsertionType( Index );
	}

	//@cmember
	/* Sets the insertion type at the specific Index. */
	void SetInsertionType( size_t Index, const int value )
	{
		m_ExternalFiles.SetInsertionType( Index, value );
	}

	//@cmember
	/* Gets the activation type at the specific Index. */
	int GetActivationType( size_t Index ) const
	{
		return m_ExternalFiles.GetActivationType( Index );
	}

	//@cmember
	/* Sets the activation type at the specific Index. */
	void SetActivationType( size_t Index, const int value )
	{
		m_ExternalFiles.SetActivationType( Index, value );
	}

	virtual void OnAddNewExtFile( ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh )
	{
		// Sets the refresh flag to true
		Refresh = DoInsertExtFile( false );

		if ( Refresh )
		{
			value = GetFileTitle( GetExtFileCount() - 1 );
		}
	}

	virtual void OnDelCurrentExtFile( ZBProperty&		Property,
									  CString&			value,
									  ZBPropertySet&	Properties,
									  bool&				Refresh )
	{
		// Delete the current selected external file
		int Index = Property.GetCategoryID() - ZS_BP_PROP_EXTFILE;

		if ( DeleteExtFile( Index ) )
		{
			// Sets the refresh flag to true
			Refresh = true;
		}
	}

	// Do a standard ext app insertion.
	virtual bool DoInsertExtFile( bool DisplayDialog = true );

	// Drag and drop methods
	virtual bool AcceptDropItem( CObject* pObj, CPoint pt );
	virtual bool DropItem( CObject* pObj, CPoint pt );

	// Call when a new symbol is created
	virtual bool CreateSymbolProperties()
	{
		// Creates the initial properties for extfiles and extapps
		m_ExternalFiles.CreateInitialProperties();
		return true;
	}

	// Call to retreive properties for the object
	virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false );

	// RS-MODIF 11.12.04 fill properties for segregation
	virtual bool FillPropertiesMessenger( ZBPropertySet&	PropSet,
										  bool				NumericValue	= false,
										  bool				GroupValue		= false );

	// Call to save new changes to object's properties
	virtual bool SaveProperties( ZBPropertySet& PropSet );

	// Called to retreive a property for the object
	virtual bool FillProperty( ZBProperty& Property )
	{
		return true;
	}

	// Called to save a property for the object
	virtual bool SaveProperty( ZBProperty& Property );

	// Called to check the property value
	virtual bool CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties )
	{
		return true;
	}

	// Called to process the extended input for the property value
	virtual bool ProcessExtendedInput( ZBProperty&		Property,
									   CString&			value,
									   ZBPropertySet&	Properties,
									   bool&			Refresh );

	// Called to process the a menu command for the property value
	virtual bool ProcessMenuCommand( int			MenuCommand,
									 ZBProperty&	Property,
									 CString&		value,
									 ZBPropertySet&	Properties,
									 bool&			Refresh );

	// Called after the property changed
	virtual bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh )
	{
		// Nothing has changed
		return false;
	}

	// Called before the property changed
	virtual bool OnPrePropertyChanged( CString NewValue, ZBProperty& Property, ZBPropertySet& Properties )
	{
		// No error
		return true;
	}

	/* Serializes the external applications and files. */
	virtual void Serialize( CArchive& ar );

protected:

	ZBExtFiles			m_ExternalFiles;

	// RS-MODIF 11.12.04 we need symbols
	CODSymbolComponent*	m_pSymbol;
};

#endif // !defined(AFX_ZBEXTFILEPROPERTYMGR_H__9FDFA8A5_FD6C_453B_9A4D_8B0425568139__INCLUDED_)