/****************************************************************************
 * ==> PSS_PreConditionFormProcDialog --------------------------------------*
 ****************************************************************************
 * Description : Provides a pre-condition form process dialog box           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PreConditionFormProcDialogH
#define PSS_PreConditionFormProcDialogH

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
#include "zBaseLib\ZWizard.h"
#include "ZSearchEdit.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

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
* Pre-condition form process dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PreConditionFormProcDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPREACT_FORMPROC
        };

        ZCSearchEdit m_FileName;
        CString      m_ActivityName;
        CString      m_FormName;

        /**
        * Constructor
        *@param activityName - activity name
        *@param formNameArray - form name array
        *@param fileRequired - file required
        *@param isLast - is last
        *@param isProcess - is process
        *@param fileArray - file array
        *@param pParent - parent window, can be NULL
        */
        PSS_PreConditionFormProcDialog(const CString& activityName,
                                       CStringArray&  formNameArray,
                                       BOOL           fileRequired,
                                       BOOL           isLast,
                                       BOOL           isProcess,
                                       CStringArray&  fileArray,
                                       CWnd*          pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PreConditionFormProcDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PreConditionFormProcDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        afx_msg void OnNext();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CStringArray& m_FormNameArray;
        CStringArray& m_FileArray;
        int           m_CurrentFormIndex;
        BOOL          m_FileRequired;
        BOOL          m_IsLast;
        BOOL          m_IsProcess;

        /**
        * Builds the text
        *@param formIndex - form index
        */
        void BuildText(int formIndex);

        /**
        * Checks the states
        */
        void CheckStates();

        /**
        * Checks the files
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CheckFiles();
};

#endif
