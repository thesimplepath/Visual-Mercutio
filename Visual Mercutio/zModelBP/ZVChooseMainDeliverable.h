// **************************************************************************************************************
// *                                    Classe ZVChooseMainDeliverable                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 14 février 2006 - Ajout de la classe ZVChooseMainDeliverable.                                *
// **************************************************************************************************************
// * Cette classe représente la boîte de dialogue permettant la sélection d'un nouveau livrable principal.        *
// **************************************************************************************************************

#if !defined(AFX_ZVChooseMainDeliverable_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZVChooseMainDeliverable_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBPRes.h"

class ZVChooseMainDeliverable : public CDialog
{
public:
    ZVChooseMainDeliverable( const CString Deliverables, const CString Main = _T( "" ), CWnd* pParent = NULL );
    ~ZVChooseMainDeliverable();

    CString GetMain() const
    {
        return m_Main;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVChooseMainDeliverable)
    enum { IDD = IDD_CHOOSE_MAINDELIV };
    CListBox    m_ListOfDeliverables;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVChooseMainDeliverable)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVChooseMainDeliverable)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnSelchangeListOfDeliverable();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void StringToListBox( const CString Deliv, CListBox& LB );
    void CheckState();

private:

    CString m_Deliverables;
    CString m_Main;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVChooseMainDeliverable_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
