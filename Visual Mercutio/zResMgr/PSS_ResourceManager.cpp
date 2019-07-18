/****************************************************************************
 * ==> PSS_ResourceManager -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a resource manager                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ResourceManager.h"

// processsoft
#include "zBaseLib\zDirectory.h"
#include "PSS_ModuleVersion.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
PSS_ResourceInfoSet PSS_ResourceManager::m_TableResources;
PSS_ResourceInfoSet PSS_ResourceManager::m_TableResourcesLoaded;
ELanguage           PSS_ResourceManager::m_CurrentLanguage = E_LN_Unknown;
//---------------------------------------------------------------------------
// PSS_ModuleVersion
//---------------------------------------------------------------------------
PSS_ResourceInfo::PSS_ResourceInfo(const CString& fileName, ELanguage lang) :
    m_Module(NULL),
    m_Language(lang),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_ResourceInfo::~PSS_ResourceInfo()
{}
//---------------------------------------------------------------------------
// PSS_ResourceManager
//---------------------------------------------------------------------------
PSS_ResourceManager::PSS_ResourceManager()
{}
//---------------------------------------------------------------------------
PSS_ResourceManager::~PSS_ResourceManager()
{
    Release();
}
//---------------------------------------------------------------------------
void PSS_ResourceManager::Release()
{
    // unload language libraries
    Unload();

    PSS_ResourceIterator it(&m_TableResources);

    // delete the resources table
    for (PSS_ResourceInfo* pInfo = it.GetFirst(); pInfo; pInfo = it.GetNext())
        if (pInfo)
            delete pInfo;

    m_TableResources.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_ResourceManager::LoadFromDirectory(const CString& dir)
{
    CStringArray fileArray;

    if (ZDirectory::FindFile(_T("*.dll"), dir, fileArray, false) <= 0)
        return true;

    // iterate through the file array and process each file
    for (int i = 0; i < fileArray.GetSize(); ++i)
    {
        HMODULE           hModule  = NULL;
        PSS_ResourceInfo* pResInfo = NULL;

        try
        {
            // open the dll
            hModule = ::LoadLibrary(fileArray.GetAt(i));

            PSS_ModuleVersion moduleInfo;

            // get dll info
            if (moduleInfo.GetFileVersionInfo(fileArray.GetAt(i)))
            {
                ELanguage language = E_LN_Unknown;

                // search for language
                switch (moduleInfo.GetLangID())
                {
                    case 0x040C: language = E_LN_French;  break;
                    case 0x0409: language = E_LN_English; break;
                    case 0x0407: language = E_LN_German;  break;
                }

                // add the resource dll to the table
                pResInfo = new PSS_ResourceInfo(fileArray.GetAt(i), language);
                m_TableResources.Add(pResInfo);
            }
        }
        catch (...)
        {
            if (pResInfo)
                delete pResInfo;

            if (hModule)
                FreeLibrary(hModule);

            throw;
        }

        if (hModule)
            FreeLibrary(hModule);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ResourceManager::ChangeLanguage(ELanguage language)
{
    if (language == m_CurrentLanguage)
        return true;

    // unload the previously loaded resource dll
    Unload();

    bool found = false;

    PSS_ResourceIterator it(&m_TableResources);

    // iterate through the known resource dlls
    for (PSS_ResourceInfo* pInfo = it.GetFirst(); pInfo; pInfo = it.GetNext())
        // is the right language?
        if (pInfo->GetLanguage() == language)
        {
            // load the library and keep the returned module handle
            pInfo->SetModule(::LoadLibrary(pInfo->GetFileName()));

            // add the resource info to the loaded array
            m_TableResourcesLoaded.Add(pInfo);
        }

    m_CurrentLanguage = language;

    return true;
}
//---------------------------------------------------------------------------
void PSS_ResourceManager::Unload()
{
    PSS_ResourceIterator it(&m_TableResourcesLoaded);

    // iterate through the loaded resources
    for (PSS_ResourceInfo* pInfo = it.GetFirst(); pInfo; pInfo = it.GetNext())
    {
        if (pInfo->GetModule())
            FreeLibrary(pInfo->GetModule());

        pInfo->SetModule(NULL);
    }

    // finally remove all elements from the table, but not delete the element itself
    m_TableResourcesLoaded.RemoveAll();
}
//---------------------------------------------------------------------------
