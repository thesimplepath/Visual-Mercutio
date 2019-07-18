/****************************************************************************
 * ==> PSS_ModuleVersion ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to works with file version information   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModuleVersionH
#define PSS_ModuleVersionH

// link with version.lib for VerQueryValue, etc...
#pragma comment(linker, "/defaultlib:version.lib")

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZRESMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// below code was extracted from shlwapi.h, in the Windows SDK November 1997 release
#if WINVER < 0x0400
    typedef struct _DllVersionInfo
    {
        DWORD cbSize;
        DWORD dwMajorVersion; // Major version
        DWORD dwMinorVersion; // Minor version
        DWORD dwBuildNumber;  // Build number
        DWORD dwPlatformID;   // DLLVER_PLATFORM_*
    } DLLVERSIONINFO;

    // platform IDs for DLLVERSIONINFO
    #define DLLVER_PLATFORM_WINDOWS 0x00000001 // Windows 95
    #define DLLVER_PLATFORM_NT      0x00000002 // Windows NT
#endif

/**
* Helper to works with file version information
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModuleVersion : public VS_FIXEDFILEINFO
{
    public:
        PSS_ModuleVersion();
        virtual ~PSS_ModuleVersion();

        /**
        * Gets the file version info for a module
        *@param pModuleName - module name
        *@return true on success, otherwise false
        *@note Allocates storage for all info, fills "this" with VS_FIXEDFILEINFO, and sets codepage
        */
        virtual bool GetFileVersionInfo(LPCTSTR pModuleName);

        /**
        * Gets the value matching with the key
        *@param pKeyName - key name, e.g. "CompanyName"
        *@return matching value, empty string if not found or on error
        */
        virtual CString GetValue(LPCTSTR pKeyName);

        /**
        * Gets the language identifier
        *@return the language identifier
        */
        virtual inline WORD GetLangID() const;

        /**
        * Gets the charset
        *@return the charset
        */
        virtual inline WORD GetCharset() const;

        /**
        * Get version of a DLL
        *@param pModuleName - module name
        *@param[out] dvi - DLL version info
        *@return true on success, otherwise false
        */
        static bool DllGetVersion(LPCTSTR pModuleName, DLLVERSIONINFO& dvi);

    protected:
        /**
        * Translation info
        */
        struct ITranslation
        {
            WORD m_LangID;
            WORD m_Charset;
        } m_Translation;

        BYTE* m_pVersionInfo;
};

//---------------------------------------------------------------------------
// PSS_ModuleVersion
//---------------------------------------------------------------------------
WORD PSS_ModuleVersion::GetLangID() const
{
    return m_Translation.m_LangID;
}
//---------------------------------------------------------------------------
WORD PSS_ModuleVersion::GetCharset() const
{
    return m_Translation.m_Charset;
}
//---------------------------------------------------------------------------

#endif
