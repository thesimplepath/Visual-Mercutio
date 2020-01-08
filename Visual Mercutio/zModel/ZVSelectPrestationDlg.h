// **************************************************************************************************************
// *                                        Classe ZVSelectPrestationDlg                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 27 février 2006 - Ajout de la classe ZVSelectPrestationDlg.                                    *
// **************************************************************************************************************
// * Cette classe représente l'interface de sélection d'une prestation, ou d'un groupe de prestations, dans la    *
// * liste.                                                                                                        *
// **************************************************************************************************************

#if !defined(AFX_ZVSELECTPRESTATIONDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)
#define AFX_ZVSELECTPRESTATIONDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_

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

#include "PSS_PrestationsTreeCtrl.h"
#include "zModelRes.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// old class name mapping
#ifndef PSS_PrestationsEntity
#define PSS_PrestationsEntity ZBPrestationsEntity
#endif
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// forward class declaration
class PSS_PrestationsEntity;
class PSS_LogicalPrestationsEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVSelectPrestationDlg dialog

class AFX_EXT_CLASS ZVSelectPrestationDlg : public CDialog
{
    // Construction
public:

    // Standard constructor
    ZVSelectPrestationDlg(const CString                Title = _T(""),
                          PSS_LogicalPrestationsEntity*    pMainPrestation = NULL,
                          bool                            AllowPrestationSelection = true,
                          CWnd*                        pParent = NULL);

    // Standard constructor
    ZVSelectPrestationDlg(UINT                            nTitle,
                          PSS_LogicalPrestationsEntity*    pMainPrestation,
                          bool                            AllowPrestationSelection = true,
                          CWnd*                        pParent = NULL);

    ~ZVSelectPrestationDlg();

    void Release();

    PSS_PrestationsEntity* GetSelectedPrestationEntity() const
    {
        return m_pPrestationEntity;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVSelectPrestationDlg)
    enum
    {
        IDD = IDD_PRESTATION_SELECTION
    };
    PSS_PrestationsTreeCtrl    m_Ctrl;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVSelectPrestationDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVSelectPrestationDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedPrestationsTree(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_PrestationsEntity*        m_pPrestationEntity;
    PSS_LogicalPrestationsEntity* m_pMainPrestation;
    CString                       m_Title;
    bool                          m_AllowPrestationSelection;
};

#endif
