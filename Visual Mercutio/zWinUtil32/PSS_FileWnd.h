/****************************************************************************
 * ==> PSS_FileWnd ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file window                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileWndH
#define PSS_FileWndH

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
#include "PSS_DirTreeCtrl.h"
#include "PSS_SearchEdit.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"
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
* File window button toolbar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FileWndButtonToolBar : public CStatic, public PSS_Subject
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_FileWndButtonToolBar(CWnd* pParent = NULL);

        virtual ~PSS_FileWndButtonToolBar();

        /**
        * Sets the parent window
        *@param pParent - parent window
        */
        virtual void SetParent(CWnd* pParent);

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FileWndButtonToolBar)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_FileWndButtonToolBar)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnStopFileButton();
        afx_msg void OnRefreshFileButton();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd*         m_pParent;
        CImageList    m_ImageList;
        CCJFlatButton m_StopWebButton;
        CCJFlatButton m_RefreshWebButton;
        CToolTipCtrl  m_ToolTip;
};

/**
* File window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileWnd : public CWnd, public PSS_Subject, public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_FileWnd)

    public:
        PSS_FileWnd();
        virtual ~PSS_FileWnd();

        /**
        * Called when window is updated
        *@param pSubject - subject
        *@param pMSg - message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    private:
        PSS_SearchEdit           m_FileName;
        PSS_DirTreeCtrl          m_DirTreeCtrl;
        PSS_FileWndButtonToolBar m_FlatToolBar;
        COLORREF                 m_clrBtnFace;

        /// Generated message map functions
        //{{AFX_MSG(PSS_FileWnd)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Reflects the directory changes
        */
        void ReflectChangedDirectory();

        /**
        * Called when stop button is clicked
        */
        void OnStopFileButton();

        /**
        * Called when refresh button is clicked
        */
        void OnRefreshButton();
};

#endif
