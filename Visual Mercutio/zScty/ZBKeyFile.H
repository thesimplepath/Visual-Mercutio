																				   /////////////////////////////////////////////////////////////////////////////
//@doc ZBKeyFile
//@module ZBKeyFile.h | Interface of the <c ZBKeyFile> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:devzone@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zADS library.
// See these sources for detailed information regarding
// zADS libraries.
//
// <nl>Created:		 03/2000
// <nl>Description:  ZBKeyFile implements a file containing keys for licenses.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _ZBKeyFile_h__
#define _ZBKeyFile_h__ 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT






#ifdef _ZSCTYEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



/////////////////////////////////////////////////////////////////////////////
//## Class: ZBKeyEntity


class AFX_EXT_CLASS ZBKeyEntity 
{
  public:
      ZBKeyEntity();

      virtual ~ZBKeyEntity();


      // This function generates a random key.
      CString GenerateRandomEntity();

	  bool IsEqual( ZBKeyEntity& Entity );

      //	The entity
      const CString GetsEntity() const;
      void SetsEntity(const CString value);

      //	Take the key and cript it.
      void CriptEntity();

  private:  //## implementation


      CString m_sEntity;
};



/////////////////////////////////////////////////////////////////////////////
//## Class: ZBKeyFile


class AFX_EXT_CLASS ZBKeyFile 
{
  public:
      ZBKeyFile();
      ZBKeyFile(const CString& sFileName);
      ZBKeyFile(const CString& sFileName, const CString& sClearFileName, int Count);

      virtual ~ZBKeyFile();

      //	Create the security filename with the creation date and
      //	counters.
      BOOL GenerateFile();

	  // Check if the key is a valid key
	  BOOL IsKeyValid( const CString Key );

//	const fstream GetSecurityFile() const;

      const CString GetFilename() const;
      void SetFilename(const CString value);

      const CString GetClearFilename() const;
      void SetClearFilename(const CString value);

  protected:



  private:  //## implementation

      // Write the entity table to disk.
      BOOL WriteEntityTable( CString Filename );
	  // Load the security entities from the file to the table.
      BOOL LoadSecurityTable( CString Filename );


private:
	CStdioFile	m_SecurityFile;
    CString		m_sFilename;
    CString		m_sClearFilename;
	int			m_Count;

	ZBKeyEntity  m_KeyEntityTable[10000];
};



// Class ZBKeyFile 

//## Get and Set Operations for Has Relationships (inline)

// JMR-MODIF - Le 19 mai 2005 - Fonction inline supprimée car incompatible, et apparamment inutilisée.
//inline const fstream ZBKeyFile::GetSecurityFile() const
//{
//	return m_SecurityFile;
//}

inline const CString ZBKeyFile::GetFilename() const
{
  return m_sFilename;
}

inline void ZBKeyFile::SetFilename(const CString value)
{
  m_sFilename = value;
}

inline const CString ZBKeyFile::GetClearFilename() const
{
  return m_sClearFilename;
}

inline void ZBKeyFile::SetClearFilename(const CString value)
{
  m_sClearFilename = value;
}


// Class ZBKeyEntity 

//## Get and Set Operations for Has Relationships (inline)

inline const CString ZBKeyEntity::GetsEntity() const
{
  return m_sEntity;
}

inline void ZBKeyEntity::SetsEntity(const CString value)
{
  m_sEntity = value;
}





#endif	 // _ZBKeyFile_h__


