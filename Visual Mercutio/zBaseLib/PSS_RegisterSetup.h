/****************************************************************************
 * ==> PSS_RegisterSetup ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to create, modify or get a value from a  *
 *               key in the registry                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RegisterSetupH
#define PSS_RegisterSetupH

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

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Helper to create, modify or get a value from a key in the registry
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RegisterSetup
{
    public:
        PSS_RegisterSetup();
        virtual ~PSS_RegisterSetup();

        /**
        * Creates a key in the registry
        *@param hRoot - root key, if NULL the HKEY_LOCAL_MACHINE key will be used
        *@param entityName - entity name (i.e the key path)
        *@param keyName - the key name
        *@param defaultValue - the key value
        *@param silent - if true, error messages will not be shown
        *@return true on success, otherwise false
        */
        virtual bool CreateEntry(HKEY           hRoot,
                                 const CString& entityName,
                                 const CString& keyName,
                                 const CString& defaultValue = _T(""),
                                 bool           silent       = false) const;
 
        /**
        * Updates a key in the registry
        *@param hRoot - root key, if NULL the HKEY_LOCAL_MACHINE key will be used
        *@param entityName - entity name (i.e the key path)
        *@param keyName - the key name
        *@param value - the new key value
        *@param silent - if true, error messages will not be shown
        *@return true on success, otherwise false
        */
        virtual bool UpdateRegValue(HKEY           hRoot,
                                    const CString& entityName,
                                    const CString& keyName,
                                    const CString& value,
                                    bool           silent = false) const;

        /**
        * Gets a value from a registry key
        *@param hRoot - root key, if NULL the HKEY_LOCAL_MACHINE key will be used
        *@param entityName - entity name (i.e the key path)
        *@param keyName - the key name
        *@param[in, out] - the default key value if the key should be created, the key value on function ends
        *@param createEntry - if true, a new entry will be created in the registry if not exists,
        *                     if false, the function will fail if key not exists
        *@param silent - if true, error messages will not be shown
        *@return true on success, otherwise false
        */
        virtual bool GetRegValue(HKEY           hRoot,
                                 const CString& entityName,
                                 const CString& keyName,
                                 CString&       value,
                                 bool           createEntry = false,
                                 bool           silent      = false) const;

    private:
        /**
        * Shows a generic error message
        */
        void ShowGenericError() const;

        /**
        * Shows an error message
        *@param errorCode - error code
        *@param useLocale - if true, the error message will be translated in selected OS locale
        */
        void ShowError(DWORD errorCode, bool useLocale) const;
};

#endif
