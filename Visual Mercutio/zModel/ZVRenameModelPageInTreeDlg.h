// **************************************************************************************************************
// *                                      ZVRenameModelPageInTreeDlg                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 3 avril 2006 - Ajout de la classe ZVRenameModelPageInTreeDlg.                                *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de renommer une page sélectionnée dans l'arbre à l'aide du menu        *
// * contextuel.                                                                                                *
// **************************************************************************************************************

#if !defined(AFX_ZVRenameModelPageInTreeDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
#define AFX_ZVRenameModelPageInTreeDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_

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

#include "zBaseLib\ZIDialog.h"

#include "zModelRes.h"

// Forward declaration
class ZDProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 3 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVRenameModelPageInTreeDlg dialog

class AFX_EXT_CLASS ZVRenameModelPageInTreeDlg : public ZIDialog
{
// Construction
public:

    // Standard constructor
    ZVRenameModelPageInTreeDlg( CString                    ProposedName    = _T( "" ),
                                CStringArray*            pArrayPageName    = NULL,
                                CWnd*                    pParent            = NULL );

    CString GetPageName() const;

    // Dialog Data
    //{{AFX_DATA(ZVRenameModelPageInTreeDlg)
    enum { IDD = IDD_RENAME_MODELPAGE_IN_TREE };
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVRenameModelPageInTreeDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVRenameModelPageInTreeDlg)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnEnChangePagename();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

// Implementation
private:

    CStringArray*            m_pArrayPageName;
    CString                    m_PageName;
};

inline CString ZVRenameModelPageInTreeDlg::GetPageName() const
{
    return m_PageName;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRenameModelPageInTreeDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
