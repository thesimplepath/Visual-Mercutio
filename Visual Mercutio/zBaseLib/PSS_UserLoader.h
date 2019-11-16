/****************************************************************************
 * ==> PSS_UserLoader ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user loader                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserLoaderH
#define PSS_UserLoaderH

#include "PSS_UserExport.h"
#include "PSS_UserManager.h"

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
* User loader
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserLoader
{
    public:
        /**
        * Constructor
        *@param pUserManager - the user manager
        *@param fileName - file name
        */
        inline PSS_UserLoader(PSS_UserManager* pUserManager = NULL, const CString& fileName = "");

        virtual ~PSS_UserLoader();

        /**
        * Creates the user loader
        *@param pUserManager - the user manager
        *@param fileName - file name
        */
        virtual inline void Create(PSS_UserManager* pUserManager, const CString& fileName);

        /**
        * Loads all users in memory from a database or a file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadAllUsers();

        /**
        * Saves all users to a database or a file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveAllUsers();

        /**
        * Assigns the user manager to work with
        *@param pUserManager - user manager
        */
        virtual void AssignUserManager(PSS_UserManager* pUserManager);

        /**
        * Assigns the file name
        *@param fileName - file name
        */
        virtual void AssignFileName(CString FileName);

    private:
        PSS_UserManager* m_pUserManager;
        PSS_UserExport   m_UserImport;
        CString          m_FileName;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserLoader(const PSS_UserLoader& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserLoader& operator = (const PSS_UserLoader& other);
};

//---------------------------------------------------------------------------
// PSS_UserLoader
//---------------------------------------------------------------------------
PSS_UserLoader::PSS_UserLoader(PSS_UserManager* pUserManager, const CString& fileName) :
    m_pUserManager(pUserManager),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
void PSS_UserLoader::Create(PSS_UserManager* pUserManager, const CString& fileName)
{
    m_pUserManager = pUserManager;
    m_FileName     = fileName;
}
//---------------------------------------------------------------------------

#endif
