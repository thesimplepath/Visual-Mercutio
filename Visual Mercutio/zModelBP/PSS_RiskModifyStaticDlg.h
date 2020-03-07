/****************************************************************************
 * ==> PSS_RiskModifyStaticDlg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify risk static dialog box                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskModifyStaticDlgH
#define PSS_RiskModifyStaticDlgH

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

// stdafx
#include "afxwin.h"

// resources
#include "zModelBPRes.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Modify risk dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskModifyStaticDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param fileName - the file name
        *@param extension - the file extension
        *@param elementCount - the element count
        *@param pParent - the parent window, can be NULL
        */
        PSS_RiskModifyStaticDlg(const CString& fileName,
                                const CString& extension,
                                int            elementCount,
                                CWnd*          pParent = NULL);

        virtual ~PSS_RiskModifyStaticDlg();

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RiskModifyStaticDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RiskModifyStaticDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnEnChangeStaticModifyElement();
        afx_msg void OnLbnSelchangeStaticElementsList();
        afx_msg void OnBnClickedStaticNewFile();
        afx_msg void OnBnClickedOk();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_MODIFY_RISK_STATIC
        };

        CEdit    m_ElementCtrl;
        CListBox m_ElementsListCtrl;
        CButton  m_OK;
        CStatic  m_ElementNbrCtrl;
        CString  m_FileName;
        CString  m_Extension;
        CString  m_Element;
        int      m_ElementCount;

        PSS_RiskModifyStaticDlg();
};

#endif
