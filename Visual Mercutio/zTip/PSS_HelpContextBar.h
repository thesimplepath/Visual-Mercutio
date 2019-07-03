/****************************************************************************
 * ==> PSS_HelpContextBar --------------------------------------------------*
 ****************************************************************************
 * Description : Contextual help bar component                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HelpBarH
#define PSS_HelpBarH

#if _MSC_VER >= 1000
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
#include "zWeb\ZWebBrowser.h"

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
* Contextual help bar component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HelpContextBar : public SECControlBar
{
    public:
        PSS_HelpContextBar();
        virtual ~PSS_HelpContextBar();

        /**
        * Sets the url
        *@param resID - resource identifier
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void SetURL(UINT resID, HINSTANCE hInstance = NULL);

        /**
        * Sets the url
        *@param url - url
        *@param isRes - if TRUE url is a resource name
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void SetURL(LPCTSTR url, BOOL isRes, HINSTANCE hInstance = NULL);

        /**
        * Sets the url
        *@param resID - resource identifier
        *@param param - parameters
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void SetURL(UINT resID, LPCTSTR param, HINSTANCE hInstance = NULL);

        /**
        * Sets the url
        *@param url - url
        *@param isRes - if TRUE url is a resource name
        *@param param - parameters
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void SetURL(LPCTSTR url, BOOL isRes, LPCTSTR param, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        */
        virtual inline void Navigate();

        /**
        * Navigates to url
        *@param resID - resource identifier
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void Navigate(UINT resID, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        *@param url - url
        *@param isRes - if TRUE url is a resource name
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void Navigate(LPCTSTR url, BOOL isRes, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        *@param resID - resource identifier
        *@param param - parameters
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void Navigate(UINT resID, LPCTSTR param, HINSTANCE hInstance = NULL);

        /**
        * Navigates to url
        *@param url - url
        *@param isRes - if TRUE url is a resource name
        *@param param - parameters
        *@param hInstance - instance handle, can be NULL
        */
        virtual inline void Navigate(LPCTSTR url, BOOL isRes, LPCTSTR param, HINSTANCE hInstance = NULL);

    protected:
        /// generated message map functions
        //{{AFX_MSG(PSS_HelpContextBar)
        afx_msg int OnCreate(LPCREATESTRUCT pCreateStruct);
        afx_msg void OnSize(UINT type, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZWebBrowser* m_pBrowser;
};

//---------------------------------------------------------------------------
// PSS_HelpContextBar
//---------------------------------------------------------------------------
void PSS_HelpContextBar::SetURL(UINT resID, HINSTANCE hInstance)
{ 
    if (m_pBrowser)
        m_pBrowser->SetURL(resID, hInstance); 
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::SetURL(LPCTSTR url, BOOL isRes, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->SetURL(url, isRes, hInstance); 
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::SetURL(UINT resID, LPCTSTR param, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->SetURL(resID, param, hInstance);
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::SetURL(LPCTSTR url, BOOL isRes, LPCTSTR param, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->SetURL(url, isRes, param, hInstance);
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::Navigate()
{
    if (m_pBrowser)
        m_pBrowser->Navigate();
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::Navigate(UINT resID, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->Navigate(resID, hInstance);
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::Navigate(LPCTSTR url, BOOL isRes, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->Navigate(url, isRes, hInstance);
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::Navigate(UINT resID, LPCTSTR param, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->Navigate(resID, param, hInstance);
}
//---------------------------------------------------------------------------
void PSS_HelpContextBar::Navigate(LPCTSTR url, BOOL isRes, LPCTSTR param, HINSTANCE hInstance)
{
    if (m_pBrowser)
        m_pBrowser->Navigate(url, isRes, param, hInstance);
}
//---------------------------------------------------------------------------

#endif
