/****************************************************************************
 * ==> PSS_UrlWnd ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an url window                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UrlWndH
#define PSS_UrlWndH

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
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_FlatButton.h"
#include "zBaseLib\ZCIntelliEdit.h"
#include "zWeb\PSS_WebBrowser.h"

// resources
#include "zWinUtil32\ZWinUtil32Res.h"
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
* Url window address intellisense edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_UrlWndAddressIntelliEdit : public ZCIntelliEdit, public PSS_Subject
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        *@param pArrayOfValues - array of values, can be NULL
        */
        PSS_UrlWndAddressIntelliEdit(CWnd* pParent = NULL, CStringArray* pArrayOfValues = NULL);

        virtual ~PSS_UrlWndAddressIntelliEdit();

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
        // Generated message map functions
        //{{AFX_MSG(PSS_UrlWndAddressIntelliEdit)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd* m_pParent;
};

/**
* Url window button toolbar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_UrlWndButtonToolBar : public CStatic, public PSS_Subject
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_UrlWndButtonToolBar(CWnd* pParent = NULL);

        virtual ~PSS_UrlWndButtonToolBar();

        /**
        * Sets the parent window
        *@param pParent - parent window
        */
        virtual void SetParent(CWnd* pParent);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UrlWndButtonToolBar)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_UrlWndButtonToolBar)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnStopWebButton();
        afx_msg void OnRefreshWebButton();
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
        CToolTipCtrl  m_ToolTip;
        CImageList    m_ImageList;
};

/**
* Url window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UrlWnd : public CWnd, public PSS_Subject, public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_UrlWnd)

    public:
        PSS_UrlWnd();
        virtual ~PSS_UrlWnd();

    private:
        PSS_WebBrowser*              m_pBrowser;
        PSS_UrlWndAddressIntelliEdit m_URLEdit;
        PSS_UrlWndButtonToolBar      m_FlatToolBar;
        PSS_FlatButton               m_GoButton;
        CStringArray                 m_ValueArray;
        CString                      m_URL;
        COLORREF                     m_ClrBtnFace;

        /// Generated message map functions
        //{{AFX_MSG(ZVURLWnd)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        afx_msg void OnGo();
        void OnStopWebButton();
        void OnRefreshWebButton();
        void OnPrevWebButton();
        void OnNextWebButton();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
