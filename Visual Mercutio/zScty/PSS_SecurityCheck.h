/****************************************************************************
 * ==> PSS_SecurityCheck ---------------------------------------------------*
 ****************************************************************************
 * Description : Manages the security file for product key                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SecurityCheckH
#define PSS_SecurityCheckH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Security.h"

#ifdef _ZSCTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Manages the security file for product key
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SecurityCheck : public PSS_Security
{
    public:
        PSS_SecurityCheck();

        /**
        * Constructor
        *@param fileName - security file name
        *@param daysMax - number of remaining days
        *@param counterMax - the maximum counter where the app can be opened
        *@param counterMin - the minimum counter where the days can be checked
        *@param appRegistryKey - application registry key
        *@param appPID - application identifier
        */
        PSS_SecurityCheck(const CString& fileName,
                          int            daysMax,
                          int            counterMax,
                          int            counterMin,
                          const CString& appRegistryKey = "",
                          const CString& appPID         = "");

        virtual ~PSS_SecurityCheck();

        /**
        * Checks if the user can use the program or a functionnality
        *@return TRUE if the user can use the program or a functionnality, otherwise FALSE
        */
        virtual BOOL Check();

        /**
        * Finds an old file name on the disk
        *@param exeFileName - old exe file name to find
        *@return found old version file name and path, empty string if not found or on error
        */
        virtual const CString FindOldVersion(const CString& exeFileName);

        /**
        * Creates the security file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateSecurityFile();

        /**
        * Creates a security check
        *@param fileName - security file name
        *@param daysMax - number of remaining days
        *@param counterMax - the maximum counter where the app can be opened
        *@param counterMin - the minimum counter where the days can be checked
        *@param appRegistryKey - application registry key
        *@param appPID - application identifier
        */
        virtual BOOL Create(const CString& fileName,
                            int            daysMax,
                            int            counterMax,
                            int            counterMin,
                            const CString& appRegistryKey = "",
                            const CString& appPID         = "");

        /**
        * Checks the registry to verify if user can use the installed version
        *@return TRUE if usage is allowed by registry, otherwise FALSE
        */
        virtual BOOL CheckRegistry();

        /**
        * Gets the file name to search
        *@return the file name to search
        */
        virtual inline const CString GetFileNameToSearch() const;

        /**
        * Sets the file name to search
        *@value - the file name to search
        */
        virtual inline void SetFileNameToSearch(const CString& value);

        /**
        * Gets the found file name
        *@return the found file name
        */
        virtual inline const CString GetFoundFileName() const;

        /**
        * Sets the found file name
        *@value - the found file name
        */
        virtual inline void SetFoundFileName(const CString& value);

    private:
        CString m_FileNameToSearch;
        CString m_FoundFileName;
        int     m_DaysMax;
        int     m_CounterMax;
        int     m_CounterMin;

        /**
        * Finds a specific file in a specific drive
        *@param fileName - file name to find
        *@param drive - drive index
        *@return found file name, empty string if not found or on error
        */
        const CString& FindFile(const CString& fileName, int drive);

        /**
        * Finds a specific file in the current directory
        *@return TRUE if file was found in the current directory, otherwise FALSE
        */
        BOOL FindFileInCurrentDir();
};

//---------------------------------------------------------------------------
// PSS_SecurityCheck
//---------------------------------------------------------------------------
const CString PSS_SecurityCheck::GetFileNameToSearch() const
{
    return m_FileNameToSearch;
}
//---------------------------------------------------------------------------
void PSS_SecurityCheck::SetFileNameToSearch(const CString& value)
{
    m_FileNameToSearch = value;
}
//---------------------------------------------------------------------------
const CString PSS_SecurityCheck::GetFoundFileName() const
{
    return m_FoundFileName;
}
//---------------------------------------------------------------------------
void PSS_SecurityCheck::SetFoundFileName(const CString& value)
{
    m_FoundFileName = value;
}
//---------------------------------------------------------------------------

#endif
