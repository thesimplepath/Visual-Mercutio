// ZIObjectPath.h: interface for the ZIObjectPath class.

#if !defined(AFX_ZIOBJECTPATH_H__B5847982_B00A_419D_9BDE_669222D2913F__INCLUDED_)
#define AFX_ZIOBJECTPATH_H__B5847982_B00A_419D_9BDE_669222D2913F__INCLUDED_

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

#ifdef _ZBASESYMEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 11 octobre 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

const char ObjectSeparatorChar = _T( ':' );

class AFX_EXT_CLASS ZIObjectPath
{
public:

    ZIObjectPath();
    virtual ~ZIObjectPath();

    virtual CString GetAbsolutePath() const;

    virtual bool    IsEqual( const ZIObjectPath& Path );

    virtual void    SetAbsolutePath( const CString Path );
    virtual void    ClearPath();
    virtual void    ReCalculateAbsolutePath();

    virtual void    CalculateAbsolutePath()
    {
    };

    virtual void    AddMemberToPath( const CString Member );
    virtual CString    GetRootMember();

protected:

    CString m_ObjectPath;
};

inline CString ZIObjectPath::GetAbsolutePath() const
{
    return m_ObjectPath;
}

inline void ZIObjectPath::SetAbsolutePath( const CString Path )
{
    m_ObjectPath = Path;
}

inline void ZIObjectPath::ClearPath()
{
    m_ObjectPath.Empty();
}

inline void ZIObjectPath::ReCalculateAbsolutePath()
{
    ClearPath();
    CalculateAbsolutePath();
}

inline bool ZIObjectPath::IsEqual( const ZIObjectPath& Path )
{
    return ( m_ObjectPath.Compare( (const char*)Path.GetAbsolutePath() ) == 0 ) ? true : false;
}

#endif // !defined(AFX_ZIOBJECTPATH_H__B5847982_B00A_419D_9BDE_669222D2913F__INCLUDED_)