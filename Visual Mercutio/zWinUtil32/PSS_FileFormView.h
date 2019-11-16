/****************************************************************************
 * ==> PSS_FileFormView ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file form view                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileFormViewH
#define PSS_FileFormViewH

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
#include "PSS_DirTreeCtrl.h"
#include "PSS_SearchEdit.h"

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
* File form view button toolbar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FileFormViewButtonToolBar : public CStatic
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_FileFormViewButtonToolBar(CWnd* pParent = NULL);
        virtual ~PSS_FileFormViewButtonToolBar();

        /**
        * Sets the parent
        *@param pParent - parent window
        */
        void SetParent(CWnd* pParent);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FileFormViewButtonToolBar)
        virtual void PreSubclassWindow();
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FileFormViewButtonToolBar)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnStopFileButton();
        afx_msg void OnRefreshFileButton();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd*         m_pParent;
        CCJFlatButton m_StopWebButton;
        CCJFlatButton m_RefreshWebButton;
        CImageList    m_ImageList;
        CToolTipCtrl  m_ToolTip;
};

/**
* File form view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileFormView : public CFormView
{
    DECLARE_DYNCREATE(PSS_FileFormView)

    public:
        PSS_FileFormView();
        virtual ~PSS_FileFormView();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FileFormView)
        virtual void OnInitialUpdate( );
        virtual void DoDataExchange(CDataExchange* pDX);
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
            IDD = IDD_FILEWINDOW
        };

        PSS_SearchEdit                m_FileName;
        PSS_DirTreeCtrl               m_DirTreeCtrl;
        PSS_FileFormViewButtonToolBar m_FlatToolBar;

        /// Generated message map functions
        //{{AFX_MSG(ZVFileFormView)
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg LRESULT OnStopFileButton(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRefreshWebButton(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Sizes the control
        */
        void SizeControl();

        /**
        * Reflects the directory changes
        */
        void ReflectChangedDirectory();
};

#endif
