// **************************************************************************************************************
// *                                             Classe ZVRiskModifyDlg                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 25 juin 2007 - Ajout de la classe ZVRiskModifyDlg.                                            *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de modifier un élément dans les listes déroulantes utilisées par les    *
// * risques.                                                                                                    *
// **************************************************************************************************************

#if !defined(AFX_ZVRISKMODIFYDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVRISKMODIFYDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

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
// ZVRiskModifyDlg dialog

class AFX_EXT_CLASS ZVRiskModifyDlg : public CDialog
{
private:

    ZVRiskModifyDlg();

// Construction / Destruction
public:

    // Standard constructor
    ZVRiskModifyDlg( CString    fileName,
                     CString    Extension,
                     CWnd*        pParent        = NULL );

public:

    CString GetFileName();

private:

    // Dialog Data
    //{{AFX_DATA(ZVRiskModifyDlg)
    enum { IDD = IDD_MODIFY_RISK };
    CString        m_Element;
    CEdit        m_ElementCtrl;
    CListBox    m_ElementsListCtrl;
    CButton        m_Add;
    CButton        m_Del;
    CButton        m_OK;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVRiskModifyDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVRiskModifyDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangeNewElement();
    afx_msg void OnLbnSelchangeElementsList();
    afx_msg void OnBnClickedAddElement();
    afx_msg void OnBnClickedDelElement();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedNewFile();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    CString m_FileName;
    CString m_Extension;
};

#endif
