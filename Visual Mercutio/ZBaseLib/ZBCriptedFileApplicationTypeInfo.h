// ZBCriptedFileApplicationTypeInfo.h: interface for the ZBCriptedFileApplicationTypeInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBCRIPTEDFILEAPPLICATIONTYPEINFO_H__6EAC9B86_3386_11D4_973F_0000B45D7C6F__INCLUDED_)
#define AFX_ZBCRIPTEDFILEAPPLICATIONTYPEINFO_H__6EAC9B86_3386_11D4_973F_0000B45D7C6F__INCLUDED_

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


#include "ZBCriptedFileInfo.H"


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


class AFX_EXT_CLASS ZBCriptedFileApplicationTypeInfo : public ZBCriptedFileInfo  
{
public:
    enum ApplicationInfoType { Unknown, HomeEdition, NetworkEdition, EntrepriseEdition };

public:
    ZBCriptedFileApplicationTypeInfo(const CString Filename = "");
    virtual ~ZBCriptedFileApplicationTypeInfo();

    BOOL    Initialize( const CString Filename );
    BOOL    CreateEmpty( const CString Filename );

    BOOL    CheckProductKey( CString ProductKey );

    ApplicationInfoType    LoadApplicationType();
    BOOL            WriteApplicationType( ApplicationInfoType value );

    CString    LoadProductKey();
    BOOL    WriteProductKey( CString value );

private:
    BOOL    ReadFileInfo();
    BOOL    WriteFileInfo();

    ApplicationInfoType    GetApplicationType() const { return m_ApplicationType; };
    void    SetApplicationType( ApplicationInfoType    value ) { m_ApplicationType = value; };

    CString    GetProductKey() const { return m_ProductKey; };
    void    SetProductKey( CString    value ) { m_ProductKey = value; };

private:
    ApplicationInfoType    m_ApplicationType;
    CString    m_ProductKey;
};

#endif // !defined(AFX_ZBCRIPTEDFILEAPPLICATIONTYPEINFO_H__6EAC9B86_3386_11D4_973F_0000B45D7C6F__INCLUDED_)
