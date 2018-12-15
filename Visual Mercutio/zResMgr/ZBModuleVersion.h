/////////////////////////////////////////////////////////////////////////////
//@doc ZBModuleVersion
//@module ZBModuleVersion.h | Interface of the <c ZBModuleVersion> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         10/2002
// <nl>Description:  ZBModuleVersion works with file version information
//                     for a module
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MODULEVER_H
#define __MODULEVER_H

// Tell linker to link with version.lib for VerQueryValue, etc.
#pragma comment(linker, "/defaultlib:version.lib")

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZRESMGREXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

// following is from shlwapi.h, in November 1997 release of the Windows SDK
#if WINVER < 0x0400
typedef struct _DllVersionInfo
{
    DWORD cbSize;
    DWORD dwMajorVersion;    // Major version
    DWORD dwMinorVersion;    // Minor version
    DWORD dwBuildNumber;    // Build number
    DWORD dwPlatformID;        // DLLVER_PLATFORM_*
} DLLVERSIONINFO;

// Platform IDs for DLLVERSIONINFO
#define DLLVER_PLATFORM_WINDOWS    0x00000001    // Windows 95
#define DLLVER_PLATFORM_NT        0x00000002    // Windows NT
#endif // WINVER < 0x0400

class AFX_EXT_CLASS ZBModuleVersion : public VS_FIXEDFILEINFO
{
public:

    ZBModuleVersion();
    virtual ~ZBModuleVersion();

    bool        GetFileVersionInfo    ( LPCTSTR modulename );
    CString        GetValue            ( LPCTSTR lpKeyName );
    static bool    DllGetVersion        ( LPCTSTR modulename, DLLVERSIONINFO& dvi );

    WORD GetLangID() const
    {
        return m_translation.langID;
    };

    WORD GetCharset() const
    {
        return m_translation.charset;
    };

protected:

    BYTE* m_pVersionInfo;    // all version info

    struct TRANSLATION
    {
        WORD langID;        // language ID
        WORD charset;        // character set (code page)
    } m_translation;
};

#endif