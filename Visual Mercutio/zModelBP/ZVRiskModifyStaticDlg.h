// **************************************************************************************************************
// *                                          Classe ZVRiskModifyStaticDlg                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 16 juillet 2007 - Ajout de la classe ZVRiskModifyStaticDlg.                                    *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de modifier un élément dans les listes déroulantes utilisées par les    *
// * risques.                                                                                                    *
// **************************************************************************************************************

#if !defined(AFX_ZVRISKMODIFYSTATICDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVRISKMODIFYSTATICDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zModelBPRes.h"
#include "afxwin.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVRiskModifyStaticDlg dialog

class AFX_EXT_CLASS ZVRiskModifyStaticDlg : public CDialog
{
private:

    ZVRiskModifyStaticDlg();

// Construction / Destruction
public:

    // Standard constructor
    ZVRiskModifyStaticDlg( CString    Filename,
                           CString    Extension,
                           int        NbElements,
                           CWnd*    pParent        = NULL );

public:

    CString GetFilename();

private:

    // Dialog Data
    //{{AFX_DATA(ZVRiskModifyStaticDlg)
    enum { IDD = IDD_MODIFY_RISK_STATIC };
    CString        m_Element;
    CEdit        m_ElementCtrl;
    CListBox    m_ElementsListCtrl;
    CButton        m_OK;
    CStatic        m_ElementNbrCtrl;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVRiskModifyStaticDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVRiskModifyStaticDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeStaticModifyElement();
    afx_msg void OnLbnSelchangeStaticElementsList();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedStaticNewFile();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    int        i_NbElements;

    CString    m_Filename;
    CString    m_Extension;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRISKMODIFYSTATICDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
