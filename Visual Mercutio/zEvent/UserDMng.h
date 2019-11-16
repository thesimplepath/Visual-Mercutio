// UserDMng.h: interface for the ZBUserDirectoryManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERDMNG_H__E056C8E0_1AA1_11D3_981B_00C04FB4D0D7__INCLUDED_)
#define AFX_USERDMNG_H__E056C8E0_1AA1_11D3_981B_00C04FB4D0D7__INCLUDED_

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


#ifdef _ZEVENTEXPORT
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


class AFX_EXT_CLASS ZBUserDirectoryManager  
{
public:
    ZBUserDirectoryManager( const CString Directory = "");
    BOOL    SetDirectory( const CString value );
    CString    GetDirectory() const { return m_Directory; };

    BOOL    UserExist( const CString Username );
    BOOL    CreateUser( const CString Username );
    CString    BuildUserDirectory( const CString Username );

    virtual ~ZBUserDirectoryManager();

private:
    ZBUserDirectoryManager(const ZBUserDirectoryManager &right);
    const ZBUserDirectoryManager & operator=(const ZBUserDirectoryManager &right);

    void    SaveCurrentDirectory();
    void    SetLastCurrentDirectory();

private:
    CString        m_Directory;
    // Keep the old directory
    char        m_CurrentDir[MAX_PATH];
    DWORD        m_nBufferLength;
};


//#undef  AFX_DATA
//#define AFX_DATA


inline void    ZBUserDirectoryManager::SaveCurrentDirectory()
{
    // Keep the old directory
    GetCurrentDirectory( m_nBufferLength, m_CurrentDir );
}
inline void    ZBUserDirectoryManager::SetLastCurrentDirectory()
{
    // Sets back the directory
    SetCurrentDirectory( m_CurrentDir );
}


inline CString    ZBUserDirectoryManager::BuildUserDirectory( const CString Username )
{
    return m_Directory + "\\" + Username;
}

#endif // !defined(AFX_USERDMNG_H__E056C8E0_1AA1_11D3_981B_00C04FB4D0D7__INCLUDED_)
