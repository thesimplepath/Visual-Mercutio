/************************************************************************************************************
 *												Classe ZUFileLauncher										*
 ************************************************************************************************************
 * Cette classe permet d'ouvrir un fichier. Si ce n'est pas un fichier associé à l'application Mercutio,	*
 * la classe prend en charge le démarrage de l'application propriétaire du fichier.							*
 ************************************************************************************************************/

#if !defined(AFX_ZUFILELAUNCHER_H__6E3CB810_2560_11D3_9828_00C04FB4D0D7__INCLUDED_)
#define AFX_ZUFILELAUNCHER_H__6E3CB810_2560_11D3_9828_00C04FB4D0D7__INCLUDED_

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

enum FileLauncherMode {	FLMedit,		// Opens an editor. If lpFile is not a document file, the function will fail. 
						FLMexplore,		// The function explores the folder specified by lpFile.  
						FLMopen,		// The function opens the file specified by the lpFile parameter. The file can be an executable file or a document file. It can also be a folder. 
						FLMprint,		// The function prints the document file specified by lpFile. If lpFile is not a document file, the function will fail. 
						FLMproperties };

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

class AFX_EXT_CLASS ZUFileLauncher  
{
public:

	ZUFileLauncher				( const CString		Filename	= "",
								  FileLauncherMode	Mode		= FLMopen,
								  const CString		Parameters	= "",
								  const CString		Directory	= "" );

	virtual ~ZUFileLauncher		();

	BOOL	Initialize			( const CString		Filename,
								  FileLauncherMode	Mode		= FLMopen,
								  const CString		Parameters	= "",
								  const CString		Directory	= "" );

	BOOL	Launch				( const CString		Filename,
								  FileLauncherMode	Mode		= FLMopen,
								  const CString		Parameters	= "",
								  const CString		Directory	= "" );

	BOOL	Launch				();
	BOOL	Close				();
	BOOL	ActivateApplication	();
	BOOL	HasBeenLaunched		();

	CString	GetErrorString		();

//	BOOL	IsError() const { return reinterpret_cast<int>(m_sei.hInstApp) <= 32; };
	BOOL IsError() const
	{
		return ((int)m_ErrorCode) <= 32;//reinterpret_cast<int>( m_ErrorCode ) <= 32;
	};

	HANDLE GetApplicationHandle() const
	{
		return m_sei.hInstApp;
	};

	HANDLE GetApplicationProcessHandle() const
	{
		return m_sei.hProcess;
	};

private:

	CString GetModeVerbString();

private:

	CString				m_Filename;
	FileLauncherMode	m_Mode;
	CString				m_Parameters;
	CString				m_Directory;
	SHELLEXECUTEINFO	m_sei;
	HANDLE				m_ErrorCode;
};

#endif // !defined(AFX_ZUFILELAUNCHER_H__6E3CB810_2560_11D3_9828_00C04FB4D0D7__INCLUDED_)