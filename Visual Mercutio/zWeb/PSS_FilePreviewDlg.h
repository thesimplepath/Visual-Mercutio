/****************************************************************************
 * ==> PSS_FilePreviewDlg --------------------------------------------------*
 ****************************************************************************
 * Description : File preview dialog                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FilePreviewDlgH
#define PSS_FilePreviewDlgH

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
#include "PSS_WebBrowser.h"

// resources
#include "ZWebRes.h"

#ifdef _ZWEBEXPORT
    //put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* File preview dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FilePreviewDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param resID - resource identifier containing the file to show
        *@param parent - parent form, can be NULL
        */
        PSS_FilePreviewDlg(UINT resID, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param pURL - url of the file to show
        *@param isRes - if TRUE, url is a resource path
        *@param parent - parent form, can be NULL
        */
        PSS_FilePreviewDlg(LPCTSTR pURL, BOOL isRes, CWnd* pParent = NULL);

        virtual ~PSS_FilePreviewDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FilePreviewDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_FilePreviewDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSize(UINT type, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_WebBrowser* m_pBrowser;
        CString         m_URL;

        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_BROWSER_FILEPREVIEW
        };

        /**
        * Resizes the control
        */
        void ResizeControl();
};

#endif
