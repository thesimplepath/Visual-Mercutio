/****************************************************************************
 * ==> PSS_ResourceManager -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a resource manager                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ResourceManagerH
#define PSS_ResourceManagerH

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

// resources
#include "PSS_LanguageDefs.h"

// forward classes definition
class PSS_ResourceInfo;

#ifdef _ZRESMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// stingray studio namespace
using namespace sfl;

/**
* PSS_ResourceInfo collection
*/
typedef CCArray_T<PSS_ResourceInfo*, PSS_ResourceInfo*> PSS_ResourceInfoSet;

/**
* PSS_ResourceInfo collection iterator
*/
typedef Iterator_T<PSS_ResourceInfo*> PSS_ResourceIterator;

/**
* Resource info
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ResourceInfo
{
    public:
        /**
        * Constructor
        *@param fileName - file name, may be empty
        *@param language - language, may be unknown
        */
        PSS_ResourceInfo(const CString& fileName = _T(""), ELanguage language = E_LN_Unknown);

        virtual ~PSS_ResourceInfo();

        /**
        * Gets the module instance
        *@return the module instance
        */
        virtual inline HMODULE    GetModule() const;

        /**
        * Sets the module instance
        *@param hModule - the module instance
        */
        virtual inline void SetModule(HMODULE hModule);

        /**
        * Gets the language
        *@return the language
        */
        virtual inline ELanguage GetLanguage() const;

        /**
        * Sets the language
        *@param language - the language
        */
        virtual inline void SetLanguage(ELanguage language);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Sets the file name
        *@param fileName - the file name
        */
        virtual inline void SetFileName(const CString& fileName);

    private:
        HMODULE   m_Module;
        ELanguage m_Language;
        CString   m_FileName;
};

//---------------------------------------------------------------------------
// PSS_ModuleVersion
//---------------------------------------------------------------------------
HMODULE PSS_ResourceInfo::GetModule() const
{
    return m_Module;
}
//---------------------------------------------------------------------------
void PSS_ResourceInfo::SetModule(HMODULE hModule)
{
    m_Module = hModule;
}
//---------------------------------------------------------------------------
ELanguage PSS_ResourceInfo::GetLanguage() const
{
    return m_Language;
}
//---------------------------------------------------------------------------
void PSS_ResourceInfo::SetLanguage(ELanguage value)
{
    m_Language = value;
}
//---------------------------------------------------------------------------
CString PSS_ResourceInfo::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_ResourceInfo::SetFileName(const CString& fileName)
{
    m_FileName = fileName;
}
//---------------------------------------------------------------------------

/**
* Resources manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ResourceManager
{
    public:
        PSS_ResourceManager();
        virtual ~PSS_ResourceManager();

        /**
        * Releases the resources manager
        */
        static void Release();

        /**
        * Loads all the resource dlls contained inside a directory
        *@param dir - directory containing the resource dlls to load
        *@return true on sucess, otherwise false
        */
        static bool LoadFromDirectory(const CString& dir);

        /**
        * Changes the language
        *@param language - new language to set
        *@return true on sucess, otherwise false
        */
        static bool ChangeLanguage(ELanguage language);

    private:
        static PSS_ResourceInfoSet m_TableResources;
        static PSS_ResourceInfoSet m_TableResourcesLoaded;
        static ELanguage           m_CurrentLanguage;

        /**
        * Unloads the resource manager
        */
        static void Unload();
};

#endif
