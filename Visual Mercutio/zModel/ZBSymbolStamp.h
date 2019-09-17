// ZBSymbolStamp.h: interface for the ZBSymbolStamp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSymbolStamp_H__94F5F0FA_6E0F_4610_A385_D361D5B1F2B8__INCLUDED_)
#define AFX_ZBSymbolStamp_H__94F5F0FA_6E0F_4610_A385_D361D5B1F2B8__INCLUDED_

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

#include "zBaseLib\ZBDate.h"



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



class AFX_EXT_CLASS ZBSymbolStamp : public CObject  
{
    DECLARE_SERIAL(ZBSymbolStamp)
public:
    // Contruction operations --------------------------------
    ZBSymbolStamp();
    // Copy constructor
    ZBSymbolStamp(const ZBSymbolStamp &right);
    // Assignment operator
    const ZBSymbolStamp & operator=(const ZBSymbolStamp &right);

    ZBSymbolStamp* Clone ();

    virtual ~ZBSymbolStamp();

    // Get Set operations ------------------------------------
    DWORD    GetInternalFileVersion() const;
    void SetInternalFileVersion( DWORD value );

    CString    GetName() const;
    void SetName( CString value );

    CString GetDescription() const;
    void SetDescription( CString value );

    CString GetClassName() const;
    void SetClassName( CString value );

    CString GetCategory() const;
    void SetCategory( CString value );

    DWORD    GetSymbolVersion() const;
    void SetSymbolVersion( DWORD value );

    CString GetAuthor() const;
    void SetAuthor( CString value );

    PSS_Date    GetCreationDate() const;
    void SetCreationDate(PSS_Date value );

    PSS_Date    GetModificationDate() const;
    void SetModificationDate(PSS_Date value );

    // Archiving operations ----------------------------------

    virtual void Serialize(CArchive& ar);

    // Store from the archive to the object Stamp.
    AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZBSymbolStamp& Stamp);

    // Store the object Stamp to the archive.
    AFX_EXT_API friend CArchive& operator << (CArchive& ar, const ZBSymbolStamp& Stamp);

    // Read the stamp from a given filename.
    virtual BOOL ReadFromFile (CString Filename);

    // Write the stamp to a given filename.
    virtual BOOL WriteToFile (CString Filename);


    // Versioning operations ---------------------------------

    DWORD IncrementPublishVersionOfFile (const CString Filename);
    DWORD DecrementPublishVersionOfFile (const CString Filename);
    BOOL  SetPublishVersionOfFile (const CString Filename, DWORD Version);
    DWORD GetPublishVersionOfFile (const CString Filename);


private:
    DWORD    m_InternalFileVersion;
    CString    m_Name;
    CString m_Description;
    CString m_ClassName;
    CString m_Category;
    DWORD    m_SymbolVersion;
    CString m_Author;
    PSS_Date    m_CreationDate;
    PSS_Date    m_ModificationDate;
};

inline DWORD    ZBSymbolStamp::GetInternalFileVersion() const
{
    return m_InternalFileVersion;
}
inline void ZBSymbolStamp::SetInternalFileVersion( DWORD value )
{
    m_InternalFileVersion = value;
}

inline CString    ZBSymbolStamp::GetName() const
{
    return m_Name;
}
inline void ZBSymbolStamp::SetName( CString value )
{
    m_Name = value;
}

inline CString ZBSymbolStamp::GetDescription() const
{
    return m_Description;
}
inline void ZBSymbolStamp::SetDescription( CString value )
{
    m_Description = value;
}

inline CString ZBSymbolStamp::GetClassName() const
{
    return m_ClassName;
}
inline void ZBSymbolStamp::SetClassName( CString value )
{
    m_ClassName = value;
}

inline CString ZBSymbolStamp::GetCategory() const
{
    return m_Category;
}
inline void ZBSymbolStamp::SetCategory( CString value )
{
    m_Category = value;
}

inline DWORD    ZBSymbolStamp::GetSymbolVersion() const
{
    return m_SymbolVersion;
}
inline void ZBSymbolStamp::SetSymbolVersion( DWORD value )
{
    m_SymbolVersion = value;
}

inline CString ZBSymbolStamp::GetAuthor() const
{
    return m_Author;
}
inline void ZBSymbolStamp::SetAuthor( CString value )
{
    m_Author = value;
}

inline PSS_Date    ZBSymbolStamp::GetCreationDate() const
{
    return m_CreationDate;
}
inline void ZBSymbolStamp::SetCreationDate(PSS_Date value )
{
    m_CreationDate = value;
}

inline PSS_Date    ZBSymbolStamp::GetModificationDate() const
{
    return m_ModificationDate;
}
inline void ZBSymbolStamp::SetModificationDate(PSS_Date value )
{
    m_ModificationDate = value;
}

#endif // !defined(AFX_ZBSymbolStamp_H__94F5F0FA_6E0F_4610_A385_D361D5B1F2B8__INCLUDED_)
