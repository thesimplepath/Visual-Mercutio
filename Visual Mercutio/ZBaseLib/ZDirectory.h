// ZDirectory.h: interface for the ZDirectory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDIRECTORY_H__56375D80_6793_11D3_9869_00C04FB4D0D7__INCLUDED_)
#define AFX_ZDIRECTORY_H__56375D80_6793_11D3_9869_00C04FB4D0D7__INCLUDED_

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




#ifdef _ZBASELIBEXPORT
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

class AFX_EXT_CLASS ZDirectory  
{
public:
	ZDirectory();
	virtual ~ZDirectory();

	static CString	NormalizeDirectory( const CString Directory, bool CheckFullPath = false );

	static CString	GetUpperDirectory( const CString Directory );
	static CString	GetShortDirectoryName( const CString Directory );

	static BOOL		DeleteFile( const CString File );
	static int		FindFile( const CString Filter, CStringArray& FileArray );
	static int		FindFile( const CString Filter, const CString Directory, CStringArray& FileArray, bool IncludeSubDir = false );
	static BOOL		CreateDirectory( const CString Directory );
	static BOOL		DeleteDirectory( const CString Directory, BOOL IncludeContents = FALSE, BOOL IncludeSubDirectory = FALSE );
	static BOOL		Exist( const CString Directory );
	static BOOL		ChangeCurrentDirectory( const CString Directory );
	static CString	GetCurrentDirectory();
	static BOOL		DeleteFileFromDirectory(  const CString Directory );
	static BOOL		CopyFileFromToDirectory(  const CString SrcDirectory, const CString DstDirectory, const CString Filename, BOOL Overwrite = TRUE );
	static BOOL		CopyFile( const CString SrcFile, const CString DstFile, BOOL Overwrite = TRUE );
	static BOOL		CopyAllFileFromToDirectory(  const CString SrcDirectory, const CString DstDirectory, BOOL Overwrite = TRUE, BOOL IncludeSubDirectory = FALSE, BOOL CreateDir = FALSE );
	static BOOL		MoveFileFromToDirectory(  const CString SrcDirectory, const CString DstDirectory, const CString Filename, BOOL Overwrite = TRUE );
	static BOOL		MoveAllFileFromToDirectory(  const CString SrcDirectory, const CString DstDirectory, BOOL Overwrite = TRUE, BOOL IncludeSubDirectory = FALSE, BOOL CreateDir = FALSE );
	static BOOL		MoveFile( const CString SrcFile, const CString DstFile, BOOL Overwrite = TRUE );

};

#endif // !defined(AFX_ZDIRECTORY_H__56375D80_6793_11D3_9869_00C04FB4D0D7__INCLUDED_)
