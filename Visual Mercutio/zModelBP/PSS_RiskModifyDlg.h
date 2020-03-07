/****************************************************************************
 * ==> PSS_RiskModifyDlg ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a modify risk dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskModifyDlgH
#define PSS_RiskModifyDlgH

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
class AFX_EXT_CLASS PSS_RiskModifyDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param fileName - the file name
        *@param extension - the file extension
        *@param pParent - the parent window, can be NULL
        */
        PSS_RiskModifyDlg(const CString& fileName,
                          const CString& extension,
                          CWnd*          pParent = NULL);

        virtual ~PSS_RiskModifyDlg();

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RiskModifyDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RiskModifyDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnEnChangeNewElement();
        afx_msg void OnLbnSelchangeElementsList();
        afx_msg void OnBnClickedAddElement();
        afx_msg void OnBnClickedDelElement();
        afx_msg void OnBnClickedNewFile();
        afx_msg void OnBnClickedOk();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_MODIFY_RISK
        };

        CEdit    m_ElementCtrl;
        CListBox m_ElementsListCtrl;
        CButton  m_Add;
        CButton  m_Del;
        CButton  m_OK;
        CString  m_FileName;
        CString  m_Extension;
        CString  m_Element;

        PSS_RiskModifyDlg();
};

#endif
