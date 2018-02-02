// findfile.h
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <winver.h>
#include <dos.h>
#include <direct.h>
#include <io.h>

class ZUFindFile
{
public:
	ZUFindFile(CStringArray& FileArray);
	CStringArray&		GetFoundedFile(){ return m_FoundedFile; };
	int					CopyFoundFileArray(CStringArray& FileArray);
	int					FindFile(const CString&  sExeFilename, CString sDefaultDir = "");

private:

	int 				ProcessMainSubDir();
	int 				GetMainSubDir(CStringArray& DirArray);
	int					FindFileInDrive(const CString&  sFilename, int iDrive);
	void			 	FindFileInCurrentDir();
	BOOL 				FirstSubDir(struct _finddata_t* pFileInfo);
	BOOL 				NextSubDir(long hFile, struct _finddata_t* pFileInfo);
	BOOL 				FindFileInSubDir();

private:
	// Find File variable
	CString	m_sFoundedFilename;
	CString	m_sFilenameToSearch;

	CString	m_FullPath;
	
	CStringArray&	m_FoundedFile;	
	static	int		m_iLevel;
	
	BOOL 			m_bTranslateMessage;
};

