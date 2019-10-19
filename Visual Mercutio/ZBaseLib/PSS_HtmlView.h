/****************************************************************************
 * ==> PSS_HtmlView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an html view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HtmlViewH
#define PSS_HtmlViewH

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

// mfc
#ifndef __AFXEXT_H__
    #include <afxext.h>
#endif
#include <afxhtml.h>

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
* Html view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HtmlView : public CHtmlView
{
    DECLARE_DYNCREATE(PSS_HtmlView)

    public:
        PSS_HtmlView();

        /**
        * Navigates to an url
        *@param resID - url resource identifier
        *@param flags - flags
        *@param pTargetFrameName - target frame name
        */
        virtual void Navigate(UINT resID, DWORD flags = 0, LPCTSTR pTargetFrameName = NULL);

        /**
        * Navigates to an url
        *@param pURL - url to navigate to
        *@param res - if TRUE, the url points to a resource
        *@param flags - flags
        *@param pTargetFrameName - target frame name
        */
        virtual void Navigate(LPCTSTR pURL, BOOL res, DWORD flags = 0, LPCTSTR pTargetFrameName = NULL);

        /**
        * Gets the current url
        *@return the current url
        */
        virtual inline const CString GetCurrentURL() const;

    protected:
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_HtmlView)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_HtmlView)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        virtual ~PSS_HtmlView();

        /**
        * Gets an url from a resource
        *@param pUrl - url pointing to the resource to get
        */
        virtual void ResourceToURL(LPCTSTR pUrl);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        CString m_URL;
};

//---------------------------------------------------------------------------
// PSS_HtmlView
//---------------------------------------------------------------------------
const CString PSS_HtmlView::GetCurrentURL() const
{
    return m_URL;
}
//---------------------------------------------------------------------------

#endif
