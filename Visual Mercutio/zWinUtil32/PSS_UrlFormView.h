/****************************************************************************
 * ==> PSS_UrlFormView -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an url form view                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UrlFormViewH
#define PSS_UrlFormViewH

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

// processsoft
#include "zBaseLib\PSS_FlatButton.h"
#include "zBaseLib\PSS_IntelliEdit.h"
#include "zWeb\PSS_WebBrowser.h"

// resources
#ifdef _WIN32
    #include "zWinUtil32Res.h"
#endif
#include "zFormsRes\zFormsRes.h"

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
* Address intellisense edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_AddressIntelliEdit : public PSS_IntelliEdit
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        *@param pArrayOfValues - array of values, can be NULL
        */
        PSS_AddressIntelliEdit(CWnd* pParent = NULL, CStringArray* pArrayOfValues = NULL);

        virtual ~PSS_AddressIntelliEdit();

        /**
        * Sets the parent window
        *@param pParent - parent window
        */
        virtual void SetParent(CWnd* pParent);

        /**
        * Called when Enter key is pressed
        */
        virtual void OnEnter();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_AddressIntelliEdit)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd* m_pParent;
};

/**
* Url form view button toolbar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_UrlFormViewButtonToolBar : public CStatic
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_UrlFormViewButtonToolBar(CWnd* pParent = NULL);

        virtual ~PSS_UrlFormViewButtonToolBar();

        /**
        * Sets the parent window
        *@param pParent - parent window
        */
        virtual void SetParent(CWnd* pParent);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UrlFormViewButtonToolBar)
        virtual void PreSubclassWindow();
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_UrlFormViewButtonToolBar)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnRefreshWebButton();
        afx_msg void OnStopWebButton();
        afx_msg void OnPrevWebButton();
        afx_msg void OnNextWebButton();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd*         m_pParent;
        CCJFlatButton m_PrevWebButton;
        CCJFlatButton m_NextWebButton;
        CCJFlatButton m_StopWebButton;
        CCJFlatButton m_RefreshWebButton;
        CImageList    m_ImageList;
        CToolTipCtrl  m_ToolTip;
};

/**
* Url form view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UrlFormView : public CFormView
{
    DECLARE_DYNCREATE(PSS_UrlFormView)

    public:
        PSS_UrlFormView();
        virtual ~PSS_UrlFormView();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UrlFormView)
        virtual void DoDataExchange(CDataExchange* pDX);
        virtual void OnInitialUpdate();
        //}}AFX_VIRTUAL

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
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_URLWINDOW
        };

        PSS_WebBrowser*              m_pBrowser;
        PSS_UrlFormViewButtonToolBar m_FlatToolBar;
        PSS_AddressIntelliEdit       m_URLEdit;
        PSS_FlatButton               m_GoButton;
        CStringArray                 m_ValueArray;
        CString                      m_URL;

        /// Generated message map functions
        //{{AFX_MSG(PSS_UrlFormView)
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg LRESULT OnStopWebButton(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRefreshWebButton(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnPrevWebButton(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnNextWebButton(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnGoMessage(WPARAM wParam, LPARAM lParam);
        afx_msg void OnGo();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Sizes the control
        */
        void SizeControl();
};

#endif
