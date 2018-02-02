/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtFiles
//@module ZBExtFiles.h | Interface of the <c ZBExtFiles> class.
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
// <nl>Created:		 07/2001
// <nl>Description:  ZBExtFiles procedure combinations
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ZBExtFiles_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZBExtFiles_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBExtFileProperties;


/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;



///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBExtFilePropertiesSet | An array of ZBSymbolEntity pointers.
//@iex typedef CCArray_T<ZBExtFileProperties*,ZBExtFileProperties*> ZBExtFilePropertiesSet;
typedef CCArray_T<ZBExtFileProperties*,ZBExtFileProperties*> ZBExtFilePropertiesSet;

//@type ZBExtFilePropertiesIterator | An iterator for ZBExtFilePropertiesSet collections.
//@iex typedef Iterator_T<ZBExtFileProperties*> ZBExtFilePropertiesIterator;
typedef Iterator_T<ZBExtFileProperties*> ZBExtFilePropertiesIterator;


/////////////////////////////////////////////////////////////////////////////
// ZBExtFiles class

class AFX_EXT_CLASS ZBExtFiles : public CObject  
{
	DECLARE_SERIAL(ZBExtFiles)
public:
	ZBExtFiles(CODSymbolComponent* pParent = NULL);
	virtual ~ZBExtFiles();
	/* Copy constructor. */
	ZBExtFiles(const ZBExtFiles& src);
	/* Assignment operator. */
	ZBExtFiles& operator=(const ZBExtFiles& src);
	/* Create a duplicate copy of this object. */
	virtual ZBExtFiles* Dup() const;

	// Sets the parent symbol object
	void SetParent(CODSymbolComponent* pParent);
	// Create the initial properties
	bool CreateInitialProperties();

	// Add a new extfile, 
	// and return the index of the new added extfile
	// Return -1 if the function fails
	int AddNewExtFile();

	// Add a new extfile, 
	// and return the index of the new added extfile
	// Return -1 if the function fails
	int AddExtFile( ZBExtFileProperties* pProperty );

	// Delete an extfile
	bool DeleteExtFile( size_t Index );
	bool DeleteExtFile( const CString Filename );
	bool DeleteExtFile( ZBExtFileProperties* pProperty );

	// Return true if the extfile already exists
	bool ExtFileExist( const CString Filename ) const;
	// Retreive the right extfile properties base on the extfile filename
	ZBExtFileProperties* LocateExtFile( const CString Filename ) const;

	ZBExtFilePropertiesSet& GetExtFileSet()
	{
		return m_Set;
	};

	// Return the counter of extfiles
	size_t	GetExtFileCount() const 
	{
		return m_Set.GetSize();
	};

	ZBExtFileProperties* GetProperty( size_t Index ) const
	{
		if (Index < GetExtFileCount())
			return m_Set.GetAt(Index);
		return NULL;
	};

	// Returns the index of the first empty element if there is,
	// otherwise, return -1
	int LocateFirstEmptyExtFile() const;
	// Remove only empty elements
	void RemoveAllEmptyExtFiles();
	// Remove all elements
	void RemoveAllExtFiles();

	/* Gets the file title at the specific Index. */
	CString GetFileTitle(size_t Index) const;

	//@cmember
	/* Sets the file title at the specific Index. */
	void SetFileTitle(size_t Index, CString Value);

	//@cmember
	/* Gets the filename at the specific Index. */
	CString GetFilename(size_t Index) const;

	//@cmember
	/* Sets the filename at the specific Index. */
	void SetFilename(size_t Index, CString Value);

	//@cmember
	/* Gets the insertion type at the specific Index. */
	int GetInsertionType(size_t Index) const;

	//@cmember
	/* Sets the insertion type at the specific Index. */
	void SetInsertionType(size_t Index, const int value);

	//@cmember
	/* Gets the activation type at the specific Index. */
	int GetActivationType(size_t Index) const;

	//@cmember
	/* Sets the activation type at the specific Index. */
	void SetActivationType(size_t Index, const int value);

	/* Serializes the combinations. */
	virtual void Serialize(CArchive& ar);

private:
	CODSymbolComponent*	m_pParent;
	ZBExtFilePropertiesSet m_Set;
};



#endif // !defined(AFX_ZBExtFiles_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
