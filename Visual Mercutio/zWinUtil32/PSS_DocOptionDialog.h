/****************************************************************************
 * ==> PSS_DocOptionDialog -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document options dialog box                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocOptionDialogH
#define PSS_DocOptionDialogH

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
#include "zBaseLib\PSS_DocumentOptions.h"
#include "zRes32\zRes.h"

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
* Document options dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocOptionDialog : public CDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DOCUMENT_OPTIONS
        };

        CStatic m_SmallLineCtrl;
        CStatic m_DashedLineCtrl;
        CStatic m_DottedCtrl;
        CStatic m_LinedCtrl;
        CString m_FLF_FileName;
        int     m_EmptyStyle;
        int     m_SynchronisationYesNo;
        int     m_ShowHiddenFieldYesNoDoc;
        int     m_ShowEmptyLineYesNoDoc;
        int     m_SynchronizationTime;
        int     m_GenerateHeader;
        int     m_SeparatorType;
        int     m_AutomaticFileNameGeneration;
        BOOL    m_PrintEmptyStyleWhenEmpty;

        /**
        * Constructor
        *@param pDocOptions - document options
        *@param pPArent - parent window, can be NULL
        */
        PSS_DocOptionDialog(PSS_DocumentOptions* pDocOptions, CWnd* pParent = NULL);

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_DocOptionDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnPaint();
        afx_msg void OnClicked();
        afx_msg void OnSelectFLF();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_DocumentOptions* m_pDocOptions;

        /**
        * Checks the control state
        */
        void CheckControlState();
};

#endif
