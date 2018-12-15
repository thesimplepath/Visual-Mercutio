// ******************************************************************************************************************
// *                                           Classe ZVPrestationsInfoDlg                                            *
// ******************************************************************************************************************
// * JMR-MODIF - Le 11 octobre 2005 - Ajout de la classe ZVPrestationsInfoDlg.                                        *
// ******************************************************************************************************************
// * Cette classe représente une boîte de dialogue personnalisée pour les messages en provenance du gestionnaire de    *
// * données des prestations.                                                                                        *
// ******************************************************************************************************************

#if !defined(AFX_ZVPrestationsInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVPrestationsInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelRes.h"

// forward class declaration
class ZBLogicalPrestationsEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVPrestationsInfoDlg dialog

class ZVPrestationsInfoDlg : public CDialog
{
// Construction
public:

    // Standard constructor
    ZVPrestationsInfoDlg( UINT                            nTitleID            = -1,
                          ZBLogicalPrestationsEntity*    pLogicalPrestation    = NULL,
                          const CString                    Name                = _T( "" ),
                          const CString                    Description            = _T( "" ),
                          bool                            ModifyMode            = false,
                          CWnd*                            pParent                = NULL );

    ~ZVPrestationsInfoDlg();

    CString GetDescription() const
    {
        return m_Description;
    };

    CString GetName() const
    {
        return m_Name;
    };

// Dialog Data
private:

    //{{AFX_DATA(ZVPrestationsInfoDlg)
    enum { IDD = IDD_PRESTATIONS_INFO };
    CString m_Description;
    CString m_Name;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVPrestationsInfoDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVPrestationsInfoDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    ZBLogicalPrestationsEntity*    m_pPrestation;
    CString                        m_Title;
    bool                        m_ModifyMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPrestationsInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)