/****************************************************************************
 * ==> PSS_WebBrowser ------------------------------------------------------*
 ****************************************************************************
 * Description : Web browser dialog                                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WebBrowserH
#define PSS_WebBrowserH

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
#include "PSS_WebBrowserBase.h"

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
* Web browser dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WebBrowser : public PSS_WebBrowserBase
{
    public:
        PSS_WebBrowser();
        virtual ~PSS_WebBrowser();

        /**
        * Sets options
        *@param pOptions - options to set
        */
        void SetOptions(LPCTSTR pOptions);

        /**
        * Sets parameters
        *@param pArgs - parameters
        */
        void SetParam(LPCTSTR  pArgs);
        void SetParam(VARIANT* pArgs);

        /**
        * Sets the url
        *@param resID - resource identifier containing the url
        *@param hInstance - application instance, can be NULL
        */
        void SetURL(UINT resID, HINSTANCE hInstance = NULL);

        /**
        * Sets the url
        *@param pURL - url
        *@param isRes - if TRUE, url is a resource path
        *@param hInstance - application instance, can be NULL
        */
        void SetURL(LPCTSTR pURL, BOOL isRes, HINSTANCE hInstance = NULL);

        /**
        * Sets the url
        *@param resID - resource identifier containing the url
        *@param pParams - web link parameters, e.g. "?language=EN_en"
        *@param hInstance - application instance, can be NULL
        */
        void SetURL(UINT resID, LPCTSTR pParam, HINSTANCE hInstance = NULL);

        /**
        * Sets the url
        *@param pURL - url
        *@param isRes - if TRUE, url is a resource path
        *@param pParams - web link parameters, e.g. "?language=EN_en"
        *@param hInstance - application instance, can be NULL
        */
        void SetURL(LPCTSTR pURL, BOOL isRes, LPCTSTR pParam, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        */
        void Navigate();

        /**
        * Navigates to url
        *@param url - url to navigate to
        */
        void Navigate(const CString& url);

        /**
        * Navigates to url
        *@param resID - resource identifier containing the url
        *@param hInstance - application instance, can be NULL
        */
        void Navigate(UINT resID, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        *@param pURL - url
        *@param isRes - if TRUE, url is a resource path
        *@param hInstance - application instance, can be NULL
        */
        void Navigate(LPCTSTR pURL, BOOL isRes, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        *@param resID - resource identifier containing the url
        *@param pParams - web link parameters, e.g. "?language=EN_en"
        *@param hInstance - application instance, can be NULL
        */
        void Navigate(UINT resID, LPCTSTR pParam, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        *@param pURL - url
        *@param isRes - if TRUE, url is a resource path
        *@param pParams - web link parameters, e.g. "?language=EN_en"
        *@param hInstance - application instance, can be NULL
        */
        void Navigate(LPCTSTR pURL, BOOL isRes, LPCTSTR pParam, HINSTANCE hInstance = NULL);

        /**
        * Converts a url to his matching resource string
        *@param pURL - source url
        *@param hInstance - application instance, can be NULL
        *@return the builded resource url
        */
        static CString BuildResourceToURL(LPCTSTR pURL, HINSTANCE hInstance = NULL);

    private:
        CString     m_URL;
        CString     m_Options;
        COleVariant m_Args;
        COleVariant m_Return;

        /**
        * Converts a url to his matching resource string
        *@param pURL - source url
        *@param hInstance - application instance, can be NULL
        */
        inline void ResourceToURL(LPCTSTR pURL, HINSTANCE hInstance = NULL);
};

//---------------------------------------------------------------------------
// PSS_WebBrowser
//---------------------------------------------------------------------------
void PSS_WebBrowser::ResourceToURL(LPCTSTR pURL, HINSTANCE hInstance)
{
    m_URL = BuildResourceToURL(pURL, hInstance);
}
//---------------------------------------------------------------------------

#endif
