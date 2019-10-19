// **************************************************************************************************************
// *                                          ZVRenameModelPageDlg                                                *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de sélectionner une page, puis de la renommer.                            *
// **************************************************************************************************************

#if !defined(AFX_ZVRenameModelPageDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
#define AFX_ZVRenameModelPageDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_

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

#include "zBaseLib\PSS_Dialog.h"

#include "ObjectCollections.h"
#include "zModelRes.h"
#include "ZCProcessModelTree.h"

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
// ZVRenameModelPageDlg dialog

class AFX_EXT_CLASS ZVRenameModelPageDlg : public PSS_Dialog
{
// Construction
public:

    // Standard constructor
    ZVRenameModelPageDlg( ZDProcessGraphModelMdl*    pModel,
                          CStringArray*                pArrayPageName    = NULL,
                          ZDProcessGraphPage*        pPageToRename    = NULL,
                          ZBRuntimeClassSet*        pSet            = NULL,
                          CWnd*                        pParent            = NULL );

    CString GetPageName() const;

    ZDProcessGraphPage* GetSelectedPage()
    {
        return m_pSelectedPage;
    };

    // Dialog Data
    //{{AFX_DATA(ZVRenameModelPageDlg)
    enum { IDD = IDD_RENAME_MODELPAGE };
    ZCProcessModelTree m_SymbolTree;
    CString m_PageName;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVRenameModelPageDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVRenameModelPageDlg)
    virtual void OnOK();
    afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

// Implementation
private:

    ZDProcessGraphModelMdl*    m_pModel;
    CStringArray*            m_pArrayPageName;

    ZDProcessGraphPage*        m_pSelectedPage;
    ZDProcessGraphPage*        m_pPageToRename;

    // Set of elements that can be displayed in the tree
    ZBRuntimeClassSet*        m_pSet;
};

inline CString ZVRenameModelPageDlg::GetPageName() const
{
    return m_PageName;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRenameModelPageDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
