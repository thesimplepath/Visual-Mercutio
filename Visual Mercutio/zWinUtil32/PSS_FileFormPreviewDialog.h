/****************************************************************************
 * ==> PSS_FileFormPreviewDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a file form preview dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FormFilePreviewDialogH
#define PSS_FormFilePreviewDialogH

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
#include "zBaseLib\PSS_ReadView.h"
#include "zBaseLib\PSS_Document.h"
#include "zBaseLib\PSS_DocTemplateEx.h"

// resources
#include "zWinUtil32Res.h"

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
* File form preview button toolbar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FileFormPreviewButtonToolBar : public CStatic
{
    public:
        PSS_FileFormPreviewButtonToolBar();
        virtual ~PSS_FileFormPreviewButtonToolBar();

        /**
        * Sets the parent window
        *@param pPArent - parent window
        */
        virtual void SetParent(CWnd* pParent);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FileFormPreviewButtonToolBar)
        virtual void PreSubclassWindow();
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FileFormPreviewButtonToolBar)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnPreviousPageButton();
        afx_msg void OnNextPageButton();
        afx_msg void OnRefreshButton();
        afx_msg void OnZoomInButton();
        afx_msg void OnZoomOutButton();
        afx_msg void OnPrevFileButton();
        afx_msg void OnNextFileButton();
        afx_msg void OnCloseButton();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CImageList    m_ImageList;
        CCJFlatButton m_NextPageButton;
        CCJFlatButton m_PreviousPageButton;
        CCJFlatButton m_RefreshButton;
        CCJFlatButton m_ZoomOutButton;
        CCJFlatButton m_ZoomInButton;
        CCJFlatButton m_NextFileButton;
        CCJFlatButton m_PreviousFileButton;
        CCJFlatButton m_CloseFileButton;
        CToolTipCtrl  m_ToolTip;
        CWnd*         m_pParent;
};

/**
* File form preview dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileFormPreviewDialog : public CDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_FORM_FILEPREVIEW
        };

        PSS_FileFormPreviewButtonToolBar m_FlatToolBar;

        /**
        * Constructor
        *@param fileName - file name
        *@param pDocTemplate - document template
        *@param pPArent - parent window, can be NULL
        */
        PSS_FileFormPreviewDialog(const CString& fileName, PSS_DocTemplateEx* pDocTemplate, CWnd* pParent = NULL);
        virtual ~PSS_FileFormPreviewDialog();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FileFormPreviewDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
        virtual void PostNcDestroy();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FileFormPreviewDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnClose();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CCreateContext     m_Context;
        PSS_ReadView*      m_pView;
        CFrameWnd*         m_pFrameWindow;
        PSS_Document*      m_pDocument;
        PSS_DocTemplateEx* m_pDocTemplate;
        CString            m_FileName;

        /**
        * Sizes the control
        */
        void SizeControl();

        /**
        * Closes the document
        */
        void CloseDocument();
};

#endif
