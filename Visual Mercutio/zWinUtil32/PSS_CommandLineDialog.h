/****************************************************************************
 * ==> PSS_CommandLineDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a command line dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CommandLineDialogH
#define PSS_CommandLineDialogH

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

// processsoft
#include "PSS_SearchEdit.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
* Command line dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CommandLineDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param jobName - job name
        *@param commandLine - command line
        *@param parameters - parameters
        *@param startupDir - startup directory
        *@param priority - priority
        *@param windowMode - window mode
        *@param pParent - parent window, can be NULL
        */
        PSS_CommandLineDialog(const CString& jobName     = "",
                              const CString& commandLine = "",
                              const CString& parameters  = "",
                              const CString& startupDir  = "",
                              int            priority    = 0,
                              int            windowMode  = 0,
                              CWnd*          pParent     = NULL);

        /**
        * Gets the job name
        *@return the job name
        */
        virtual inline CString GetJobName() const;

        /**
        * Gets the command line
        *@return the comand line
        */
        virtual inline CString GetCommandLine() const;

        /**
        * Gets the parameters
        *@return the parameters
        */
        virtual inline CString GetParameters() const;

        /**
        * Gets the startup directory
        *@return the startup directory
        */
        virtual inline CString GetStartupDir() const;

        /**
        * Gets the priority
        *@return the priority
        */
        virtual inline int GetPriority() const;

        /**
        * Gets the window mode
        *@return the window mode
        */
        virtual inline int GetWindowMode() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_CommandLineDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_CommandLineDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        afx_msg void OnFileArg();
        afx_msg void OnDirArg();
        afx_msg void OnSysVarArg();
        afx_msg void OnChangeJobName();
        afx_msg void OnChangeApplication();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_COMMANDLINE
        };

        PSS_SearchEdit m_Arguments;
        CComboBox      m_PriorityList;
        CComboBox      m_WindowModeList;
        PSS_SearchEdit m_StartupDirectory;
        PSS_SearchEdit m_Application;
        CString        m_JobName;
        CString        m_CommandLine;
        CString        m_Parameters;
        CString        m_StartupDir;
        int            m_Priority;
        int            m_WindowMode;
        bool           m_JobNameHasChanged;

        /**
        * Check if command line is OK
        *@return TRUE if command line is OK, otherwise FALSE
        */
        BOOL IsOK();

        /**
        * Saves the values to the object
        */
        void SaveValuesToObject();

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_NewFormPropertySheet
//---------------------------------------------------------------------------
CString PSS_CommandLineDialog::GetJobName() const
{
    return m_JobName;
}
//---------------------------------------------------------------------------
CString PSS_CommandLineDialog::GetCommandLine() const
{
    return m_CommandLine;
}
//---------------------------------------------------------------------------
CString PSS_CommandLineDialog::GetParameters() const
{
    return m_Parameters;
}
//---------------------------------------------------------------------------
CString PSS_CommandLineDialog::GetStartupDir() const
{
    return m_StartupDir;
}
//---------------------------------------------------------------------------
int PSS_CommandLineDialog::GetPriority() const
{
    return m_Priority;
}
//---------------------------------------------------------------------------
int PSS_CommandLineDialog::GetWindowMode() const
{
    return m_WindowMode;
}
//---------------------------------------------------------------------------

#endif
