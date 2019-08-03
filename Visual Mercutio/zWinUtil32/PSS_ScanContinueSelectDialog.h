/****************************************************************************
 * ==> PSS_ScanContinueSelectDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a scan continue select dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ScanContinueSelectDialogH
#define PSS_ScanContinueSelectDialogH

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
#include "PSS_SearchEdit.h"

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
* Scan continue select dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ScanContinueSelectDialog : public ZIWizardDialog
{
    public:
        /**
        * Constructor
        *@param firstTime - if true, the dialog is opened for the first time
        *@param pParent - parent window, can be NULL
        */
        PSS_ScanContinueSelectDialog(bool firstTime, CWnd* pParent = NULL);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ScanContinueSelectDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ScanContinueSelectDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnContinue();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZSCANNING_CONTINUESEL
        };

        PSS_SearchEdit m_File;
        CString        m_CompleteFileName;
        int            m_ScanType;
        bool           m_FirstTime;
};

//---------------------------------------------------------------------------
// PSS_ScanContinueSelectDialog
//---------------------------------------------------------------------------
CString PSS_ScanContinueSelectDialog::GetFileName() const
{
    return m_CompleteFileName;
}
//---------------------------------------------------------------------------

#endif
