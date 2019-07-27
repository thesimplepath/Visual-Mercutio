/****************************************************************************
 * ==> PSS_RejectActivityInputDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a reject activity input dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RejectActivityInputDialogH
#define PSS_RejectActivityInputDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _WIN32
    // mfc
    #include <afxwin.h>
    #include <afxext.h>
    #include <afxcmn.h>
    #include <afxdtctl.h>
    #include <afxcmn.h>

    // CodeJoke components library
    #include <CJ60Lib.h>
#endif

// processsoft
#include "zBaseLib\ZIDialog.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "ZWinUtil32Res.h"
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
* Reject activity input dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RejectActivityInputDialog : public ZIDialog
{
    public:
        /**
        * Constructor
        *@param pArray - activity array, can be NULL
        *@param pParent - parent window, can be NULL
        */
        PSS_RejectActivityInputDialog(CStringArray* pArray = NULL, CWnd* pParent = NULL);

        /**
        * Gets the reject text
        *@return the reject text
        */
        virtual inline CString GetRejectText() const;
    
    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_RejectActivityInputDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelChangeRejectCategory();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_REJECTACTIVITYINFO
        };

        #ifdef _WIN32
            // 32 bit version
            CCJFlatComboBox m_RejectCategory;
        #else
            // 16 bit version
            CComboBox       m_RejectCategory;
        #endif
        CStringArray*       m_pArray;
        CString             m_RejectText;
        CString             m_OwnerText;

        /**
        * Checks the control states
        */
        void CheckControlStates();
};

//---------------------------------------------------------------------------
// PSS_RejectActivityInputDialog
//---------------------------------------------------------------------------
CString PSS_RejectActivityInputDialog::GetRejectText() const
{
    return m_RejectText;
}
//---------------------------------------------------------------------------

#endif
