/****************************************************************************
 * ==> PSS_HtmlDialog ------------------------------------------------------*
 ****************************************************************************
 * Description : Dialog to show a html content                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HtmlDialogH
#define PSS_HtmlDialogH

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

#ifdef _ZWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dialog to show a html content
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HtmlDialog
{
    public:
        /**
        * Constructor
        */
        PSS_HtmlDialog();

        /**
        * Constructor
        *@param resID - resource identifier containing the url to show
        *@param pParent - dialog parent, can be NULL
        */
        PSS_HtmlDialog(UINT resID, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param pURL - url to show
        *@param isRes - if TRUE, url is a resource path
        *@param pParent - dialog parent, can be NULL
        */
        PSS_HtmlDialog(LPCTSTR pURL, BOOL isRes = FALSE, CWnd* pParent = NULL);

        virtual ~PSS_HtmlDialog();

        /**
        * Sets options
        *@param pOptions - options to set
        */
        virtual void SetOptions(LPCTSTR pOptions);

        /**
        * Sets size
        *@param width - width in pixels
        *@param height - height in pixels
        */
        virtual void SetSize(int width, int height);

        /**
        * Sets parameters
        *@param pArgs - parameters
        */
        virtual void SetParam(LPCTSTR  pArgs);
        virtual void SetParam(VARIANT* pArgs);

        /**
        * Gets the return variant
        *@return variant
        */
        virtual LPCVARIANT GetReturnVariant();

        /**
        * Gets the return string
        *@return string
        */
        virtual CString GetReturnString();

        /**
        * Shows the form in modal mode
        *@return modal result
        */
        virtual int DoModal();

    protected:
        HWND        m_hParent;
        HINSTANCE   m_hMSHTML;
        COleVariant m_Args;
        COleVariant m_Return;
        CString     m_Options;
        CString     m_URL;

    private:
        /**
        * Converts a url to his matching resource string
        *@param pURL - source url
        */
        inline void ResourceToURL(LPCTSTR pURL);

        /**
        * Initializes the class
        */
        void Init();
};

//---------------------------------------------------------------------------
// PSS_HtmlDialog
//---------------------------------------------------------------------------
void PSS_HtmlDialog::ResourceToURL(LPCTSTR pURL)
{
    HINSTANCE hInstance = ::AfxGetResourceHandle();
    PSS_Assert(hInstance);

    LPTSTR pModule = new TCHAR[_MAX_PATH];

    try
    {
        if (::GetModuleFileName(hInstance, pModule, _MAX_PATH))
            m_URL.Format(_T("res://%s/%s"), pModule, pURL);
    }
    catch (...)
    {
        delete[] pModule;
        throw;
    }

    delete[] pModule;
}
//---------------------------------------------------------------------------

#endif
