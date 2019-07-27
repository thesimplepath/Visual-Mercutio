/****************************************************************************
 * ==> PSS_SelectServerWizard ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a select a server Wizard                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectServerWizardH
#define PSS_SelectServerWizardH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Select a server Wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectServerWizard
{
    public:
        PSS_SelectServerWizard();

        /**
        * Constructor
        *@param file - file
        *@param local - if TRUE, server is local
        */
        PSS_SelectServerWizard(const CString& file, BOOL local);

        virtual ~PSS_SelectServerWizard();

        /**
        * Gets the complete ini file with its path
        *@return the complete ini file with its path, empty string if not found or on error
        */
        virtual inline CString GetIniFile() const;

        /**
        * Gets the server directory
        *@return the server directory, empty string if not found or on error
        */
        static inline const CString GetServerDirectory();

        /**
        * Executes the Wizard
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Execute();

        /**
        * Executes the Wizard
        *@param file - file
        *@param local - if TRUE, server is local
        *@return the server directory, empty string if no server selected or on error
        */
        static CString Execute(const CString& file, BOOL local);

    private:
        static CString m_File;
        static CString m_CompleteFile;
        static CString m_ServerDirectory;
        static BOOL    m_Local;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SelectServerWizard(const PSS_SelectServerWizard& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SelectServerWizard& operator = (const PSS_SelectServerWizard& other);

        /**
        * Processes the selection
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ProcessSelection();
};

//---------------------------------------------------------------------------
// PSS_SelectServerWizard
//---------------------------------------------------------------------------
CString PSS_SelectServerWizard::GetIniFile() const
{
    return m_CompleteFile;
}
//---------------------------------------------------------------------------
const CString PSS_SelectServerWizard::GetServerDirectory()
{
    return m_ServerDirectory;
}
//---------------------------------------------------------------------------

#endif
