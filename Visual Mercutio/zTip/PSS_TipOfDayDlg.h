/****************************************************************************
 * ==> PSS_TipOfDayDlg -----------------------------------------------------*
 ****************************************************************************
 * Description : Tip of the day dialog                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TipOfDayDlgH
#define PSS_TipOfDayDlgH

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
#include "zWeb\PSS_WebBrowser.h"

// resources
#include "ZTipRes.h"

#ifdef _ZTIPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Tip of the day dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TipOfDayDlg : public CDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_TIP
        };

        BOOL m_DontShowOnStartup;

        /**
        * Constructor
        *@param parent - parent form, can be NULL
        */
        PSS_TipOfDayDlg(CWnd* pParent = NULL);

        /**
        * Constructor
        *@param resID - resource identifier containing the url to show
        *@param parent - parent form, can be NULL
        */
        PSS_TipOfDayDlg(UINT resID, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param pURL - url to show
        *@param isRes - if TRUE, url is a resource path
        *@param parent - parent form, can be NULL
        */
        PSS_TipOfDayDlg(LPCTSTR pURL, BOOL isRes, CWnd* pParent = NULL);

        virtual ~PSS_TipOfDayDlg();

        /**
        * Checks if dialog shouldn't be shown on startup
        *@return TRUE if dialog shouldn't be shown on startup, otherwise FALSE
        */
        virtual inline BOOL DoNotShowOnStartup() const;

    protected:
        /// generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_TipOfDayDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// generated message map functions
        //{{AFX_MSG(PSS_TipOfDayDlg)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_WebBrowser* m_pBrowser;
        CString         m_strURL;
};

//---------------------------------------------------------------------------
// PSS_TipOfDayDlg
//---------------------------------------------------------------------------
BOOL PSS_TipOfDayDlg::DoNotShowOnStartup() const
{
    return m_DontShowOnStartup;
}
//---------------------------------------------------------------------------

#endif
