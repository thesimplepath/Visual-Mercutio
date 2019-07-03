// CrtFldW.h: interface for the ZICreateFolderWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRTFLDW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_CRTFLDW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

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

#include "zWinUtil32\ZWinUtil32.h"


#ifdef _ZWINUTIL32EXPORT
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


class AFX_EXT_CLASS ZICreateFolderWizard  
{
public:
    ZICreateFolderWizard( BOOL UseFolderNameAsFilename, CString FileDirectory, CString FileExtension = "", CString FolderName = "", CString FolderDescription = "" );
    
    // Start the wizard
    BOOL    PlayWizard();
    
    // Get information, if successful
    CString    GetFolderFilename() const { return m_CompleteFilename; };
    CString    GetFolderName() const { return m_FolderName; };
    CString    GetFolderDescription() const { return m_FolderDescription; };


    virtual ~ZICreateFolderWizard();


private:
    CString m_FileDirectory;
    CString m_FolderName;
    CString m_FolderDescription;
    CString m_FileExtension;
    CString m_CompleteFilename;

    BOOL    m_UseFolderNameAsFilename;

private:
    BOOL CheckFolderExist( const CString Filename = "" );

};

#endif // !defined(AFX_CRTFLDW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
