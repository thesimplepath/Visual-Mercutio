/****************************************************************************
 * ==> PSS_UrlInputDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an url input dialog box                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UrlInputDialogH
#define PSS_UrlInputDialogH

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
* Url input dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UrlInputDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param url - url
        *@param pParent - parent window, can be NULL
        */
        PSS_UrlInputDialog(const CString& url = "", CWnd* pParent = NULL);

        /**
        * Gets the url
        *@return the url
        */
        virtual inline CString GetURL() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UrlInputDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_UrlInputDialog)
            // NOTE: the ClassWizard will add member functions here
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INPUT_URL
        };

        CString m_URL;
};

//---------------------------------------------------------------------------
// PSS_UrlInputDialog
//---------------------------------------------------------------------------
CString PSS_UrlInputDialog::GetURL() const
{
    return m_URL;
};
//---------------------------------------------------------------------------

#endif
