/****************************************************************************
 * ==> PSS_ScanInformationDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan information dialog box                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ScanInformationDialogH
#define PSS_ScanInformationDialogH

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
#include "zBaseLib\PSS_WizardDialog.h"

// resources
#ifndef _WIN32
    #include "ZWinUtilRes.h"
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
* Scan information dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ScanInformationDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param name - name
        *@param description - description
        *@param pParent - parent window, can be NULL
        */
        PSS_ScanInformationDialog(const CString& name = "", const CString& description = "", CWnd* pParent = NULL);

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ScanInformationDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ScanInformationDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZSCANNING_INFODOC
        };

        CString m_Name;
        CString m_Description;
};

//---------------------------------------------------------------------------
// PSS_ScanInformationDialog
//---------------------------------------------------------------------------
CString PSS_ScanInformationDialog::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
CString PSS_ScanInformationDialog::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------

#endif
