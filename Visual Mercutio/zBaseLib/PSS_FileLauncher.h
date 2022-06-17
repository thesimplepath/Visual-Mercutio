/****************************************************************************
 * ==> PSS_FileLauncher ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file launcher                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileLauncherH
#define PSS_FileLauncherH

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
* File launcher
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileLauncher
{
    public:
        /**
        * File mode
        *@note Values are:
        *      - IE_FM_Edit    -> Opens an editor. If lpFile is not a document file, the function will fail
        *      - IE_FM_Explore -> The function explores the folder specified by lpFile
        *      - IE_FM_Open    -> The function opens the file specified by the lpFile parameter. The file can be an executable file or a document file. It can also be a folder
        *      - IE_FM_Print   -> The function prints the document file specified by lpFile. If lpFile is not a document file, the function will fail
        *      - IE_FM_Properties
        */
        enum class IEMode
        {
            IE_FM_Edit,
            IE_FM_Explore,
            IE_FM_Open,
            IE_FM_Print,
            IE_FM_Properties
        };

        /**
        * Constructor
        *@param fileName - file name to launch
        *@param mode - open mode
        *@param parameters - additional parameters to send to application
        *@param directory - directory
        */
        PSS_FileLauncher(const CString& fileName   = "",
                         IEMode         mode       = IEMode::IE_FM_Open,
                         const CString& parameters = "",
                         const CString& directory  = "");

        virtual ~PSS_FileLauncher();

        /**
        * Initializes the class
        *@param fileName - file name to launch
        *@param mode - open mode
        *@param parameters - additional parameters to send to application
        *@param directory - directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Initialize(const CString& fileName,
                                IEMode         mode       = IEMode::IE_FM_Open,
                                const CString& parameters = "",
                                const CString& directory  = "");

        /**
        * Launches a file
        *@param fileName - file name to launch
        *@param mode - open mode
        *@param parameters - additional parameters to send to application
        *@param directory - directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Launch(const CString& fileName,
                            IEMode         mode       = IEMode::IE_FM_Open,
                            const CString& parameters = "",
                            const CString& directory  = "");

        /**
        * Launches the file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Launch();

        /**
        * Closes the launched file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Close();

        /**
        * Activates the target application
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ActivateApplication();

        /**
        * Checks if the file was launched successfully
        *@return TRUE if the file was launched successfully, otherwise FALSE
        */
        virtual BOOL HasBeenLaunched() const;

        /**
        * Gets the error string
        *@return the error string
        */
        virtual CString GetErrorString() const;

        /**
        * Checks if the last result was an error
        *@return TRUE if the last result was an error, otherwise FALSE
        */
        virtual inline BOOL IsError() const;

        /**
        * Gets the target application handle
        *@return the target application handle
        */
        virtual inline HANDLE GetApplicationHandle() const;

        /**
        * Gets the target application process handle
        *@return the target application process handle
        */
        virtual inline HANDLE GetApplicationProcessHandle() const;

    private:
        CString          m_FileName;
        IEMode           m_Mode;
        CString          m_Parameters;
        CString          m_Directory;
        SHELLEXECUTEINFO m_ShellInfoExecute;
        HANDLE           m_ErrorCode;

        /**
        * Gets the mode verb string
        *@return the mode verb string
        */
        CString GetModeVerbString() const;
};

//---------------------------------------------------------------------------
// PSS_FileLauncher
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::IsError() const
{
    return (int(m_ErrorCode) <= 32);
}
//---------------------------------------------------------------------------
HANDLE PSS_FileLauncher::GetApplicationHandle() const
{
    return m_ShellInfoExecute.hInstApp;
}
//---------------------------------------------------------------------------
HANDLE PSS_FileLauncher::GetApplicationProcessHandle() const
{
    return m_ShellInfoExecute.hProcess;
}
//---------------------------------------------------------------------------

#endif
