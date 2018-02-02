// ZNetResource.h: interface for the ZNetResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZNETRESOURCE_H__1CCBD68E_888A_4F9A_BF26_94A6A95935FF__INCLUDED_)
#define AFX_ZNETRESOURCE_H__1CCBD68E_888A_4F9A_BF26_94A6A95935FF__INCLUDED_

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


class AFX_EXT_CLASS ZNetResource : public CObject 
{
	DECLARE_DYNAMIC(ZNetResource)

public:
	// Constructors
	ZNetResource(NETRESOURCE* pNetResource = NULL, bool IsDirectory = false);
	ZNetResource(ZNetResource& NetResource, bool IsDirectory = false);

	virtual ~ZNetResource();

    const ZNetResource & operator=(const ZNetResource &right);
    const ZNetResource & operator=(const NETRESOURCE &right);
	ZNetResource*	Clone();

	void	Initialize( NETRESOURCE& NetResource, bool IsDirectory = false );

	NETRESOURCE*	GetNetResourceObject();

	DWORD	GetScope() const { return m_Scope; };
	void	SetScope( DWORD	value ) { m_Scope = value; };

    DWORD	GetType() const { return m_Type; };
    void	SetType( DWORD	value ) { m_Type = value; };

    DWORD	GetDisplayType() const { return m_DisplayType; };
    void	SetDisplayType( DWORD	value ) { m_DisplayType = value; };

    DWORD	GetUsage() const { return m_Usage; };
    void	SetUsage( DWORD	value ) { m_Usage = value; };

    CString GetLocalName() const { return m_LocalName; };
    void	SetLocalName( CString value ) { m_LocalName = value; };

    CString GetRemoteName() const { return m_RemoteName; };
    void	SetRemoteName( CString value ) { m_RemoteName = value; };

    CString GetComment() const { return m_Comment; };
    void	SetComment( CString value ) { m_Comment = value; };

    CString	GetProvider() const { return m_Provider; };
    void	SetProvider( CString	value ) { m_Provider = value; };

	bool	GetIsDirectory() const { return m_IsDirectory; };
	void	SetIsDirectory( bool value ) { m_IsDirectory = value; };


private:
	DWORD			m_Scope; 
    DWORD			m_Type; 
    DWORD			m_DisplayType; 
    DWORD			m_Usage; 
    CString			m_LocalName; 
    CString			m_RemoteName; 
    CString			m_Comment; 
    CString			m_Provider;
	bool			m_IsDirectory;
};

#endif // !defined(AFX_ZNETRESOURCE_H__1CCBD68E_888A_4F9A_BF26_94A6A95935FF__INCLUDED_)
