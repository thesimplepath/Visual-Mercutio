// ZNetResourceWrapper.h: interface for the ZNetResourceWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZNetResourceWrapper_H__1CCBD68E_888A_4F9A_BF26_94A6A95935FF__INCLUDED_)
#define AFX_ZNetResourceWrapper_H__1CCBD68E_888A_4F9A_BF26_94A6A95935FF__INCLUDED_

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

class AFX_EXT_CLASS ZNetResourceWrapper : public CObject 
{
    DECLARE_DYNAMIC( ZNetResourceWrapper )

public:

    // Constructors
    ZNetResourceWrapper( const CString Filename, NETRESOURCE* pNetResource = NULL, bool IsDirectory = false );
    virtual ~ZNetResourceWrapper();

    void Initialize( const CString Filename, NETRESOURCE* pNetResource = NULL, bool IsDirectory = false );

    NETRESOURCE* GetNetResource()
    {
        return m_pNetResource;
    };

    CString GetFilename() const
    {
        return m_Filename;
    };

    bool IsDirectory() const
    {
        return m_IsDirectory;
    };

    bool IsFile() const
    {
        return m_IsDirectory == false;
    };

private:

    CString            m_Filename;
    NETRESOURCE*    m_pNetResource;
    bool            m_IsDirectory;
};

#endif // !defined(AFX_ZNetResourceWrapper_H__1CCBD68E_888A_4F9A_BF26_94A6A95935FF__INCLUDED_)