// ZBSymbolEntity.h: interface for the ZBSymbolEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSYMBOLENTITY_H__CCE095E4_6B7D_426B_928B_9F990EBB2B95__INCLUDED_)
#define AFX_ZBSYMBOLENTITY_H__CCE095E4_6B7D_426B_928B_9F990EBB2B95__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// stingray studio
#include "Foundation/Image/MFC/SECJPEG.H"

// processsoft
#include "ZBSymbolStamp.h"

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif

// forward class declaration
class PSS_Symbol;

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

// forward reference
class ZBSymbolEntity;    

using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBSymbolEntitySet | An array of ZBSymbolEntity pointers.
//@iex typedef CCArray_T<ZBSymbolEntity*,ZBSymbolEntity*> CODComponentSet;
typedef CCArray_T<ZBSymbolEntity*,ZBSymbolEntity*> ZBSymbolEntitySet;

//@type ZBSymbolEntityIterator | An iterator for ZBSymbolEntitySet collections.
//@iex typedef Iterator_T<ZBSymbolEntity*> ZBSymbolEntityIterator;
typedef Iterator_T<ZBSymbolEntity*> ZBSymbolEntityIterator;



class AFX_EXT_CLASS ZBSymbolEntity : public CObject  
{
    DECLARE_SERIAL(ZBSymbolEntity)

public:
    // Contruction operations --------------------------------
    ZBSymbolEntity();

    // Copy constructor
    ZBSymbolEntity(const ZBSymbolEntity &right);
    // Assignment operator
    const ZBSymbolEntity & operator=(const ZBSymbolEntity &right);

    ZBSymbolEntity* Clone ();

    virtual ~ZBSymbolEntity();


    // Get Set operations ------------------------------------
    DWORD    GetInternalFileVersion() const;

    CString    GetName() const;
    void SetName( CString value );

    CString GetDescription() const;
    void SetDescription( CString value );

    DWORD    GetSymbolVersion() const;
    void SetSymbolVersion( DWORD value );

    CString GetCategory() const;
    void SetCategory( CString value );

    CString GetAuthor() const;
    void SetAuthor( CString value );

    PSS_Date    GetCreationDate() const;
    void SetCreationDate(PSS_Date value );

    PSS_Date    GetModificationDate() const;
    void SetModificationDate(PSS_Date value );

    ZBSymbolStamp&    GetSymbolStamp();
    const ZBSymbolStamp&    GetSymbolStampConst() const;
    PSS_Symbol*        GetSymbolPtr();
    const PSS_Symbol*        GetSymbolPtrConst() const;

    // Archiving operations ----------------------------------

    virtual void Serialize(CArchive& ar);

    // Read the stamp from a given file name
    virtual BOOL ReadFromFile (CString fileName);

    // Write the stamp to a given file name
    virtual BOOL WriteToFile (CString fileName);

    // Versioning operations ---------------------------------

    DWORD IncrementPublishVersionOfFile (const CString fileName);
    DWORD DecrementPublishVersionOfFile (const CString fileName);
    BOOL  SetPublishVersionOfFile (const CString fileName, DWORD Version);
    DWORD GetPublishVersionOfFile (const CString fileName);

protected:
    ZBSymbolStamp    m_SymbolStamp;
    PSS_Symbol*      m_pSymbol;
private:
    SECJpeg m_Image;
};

inline DWORD    ZBSymbolEntity::GetInternalFileVersion() const
{
    return m_SymbolStamp.GetInternalFileVersion();
}

inline CString    ZBSymbolEntity::GetName() const
{
    return m_SymbolStamp.GetName();
}
inline void ZBSymbolEntity::SetName( CString value )
{
    m_SymbolStamp.SetName( value );
}

inline CString ZBSymbolEntity::GetDescription() const
{
    return m_SymbolStamp.GetDescription();
}
inline void ZBSymbolEntity::SetDescription( CString value )
{
    m_SymbolStamp.SetDescription( value );
}

inline DWORD ZBSymbolEntity::GetSymbolVersion() const
{
    return m_SymbolStamp.GetSymbolVersion();
}
inline void ZBSymbolEntity::SetSymbolVersion( DWORD value )
{
    m_SymbolStamp.SetSymbolVersion( value );
}

inline CString ZBSymbolEntity::GetCategory() const
{
    return m_SymbolStamp.GetCategory();
}
inline void ZBSymbolEntity::SetCategory( CString value )
{
    m_SymbolStamp.SetCategory( value );
}

inline CString ZBSymbolEntity::GetAuthor() const
{
    return m_SymbolStamp.GetAuthor();
}
inline void ZBSymbolEntity::SetAuthor( CString value )
{
    m_SymbolStamp.SetAuthor( value );
}

inline PSS_Date    ZBSymbolEntity::GetCreationDate() const
{
    return m_SymbolStamp.GetCreationDate();
}
inline void ZBSymbolEntity::SetCreationDate(PSS_Date value )
{
    m_SymbolStamp.SetCreationDate( value );
}

inline PSS_Date    ZBSymbolEntity::GetModificationDate() const
{
    return m_SymbolStamp.GetModificationDate();
}
inline void ZBSymbolEntity::SetModificationDate(PSS_Date value )
{
    m_SymbolStamp.SetModificationDate( value );
}

inline DWORD ZBSymbolEntity::IncrementPublishVersionOfFile (const CString fileName)
{
    return m_SymbolStamp.IncrementPublishVersionOfFile(fileName);
}
inline DWORD ZBSymbolEntity::DecrementPublishVersionOfFile (const CString fileName)
{
    return m_SymbolStamp.DecrementPublishVersionOfFile(fileName);
}
inline BOOL  ZBSymbolEntity::SetPublishVersionOfFile (const CString fileName, DWORD Version)
{
    return m_SymbolStamp.SetPublishVersionOfFile(fileName, Version);
}
inline DWORD ZBSymbolEntity::GetPublishVersionOfFile (const CString fileName)
{
    return m_SymbolStamp.GetPublishVersionOfFile(fileName);
}

inline ZBSymbolStamp& ZBSymbolEntity::GetSymbolStamp()
{
    return m_SymbolStamp;
}
inline const ZBSymbolStamp& ZBSymbolEntity::GetSymbolStampConst() const
{
    return m_SymbolStamp;
}

inline PSS_Symbol* ZBSymbolEntity::GetSymbolPtr()
{
    return m_pSymbol;
}

inline const PSS_Symbol* ZBSymbolEntity::GetSymbolPtrConst() const
{
    return m_pSymbol;
}

#endif
