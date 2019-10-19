// ZVInsertModelNewPageDlg.h : header file

#if !defined(AFX_ZVINSERTMODELNEWPAGEDLG_H__2AF4D47B_748C_4CBD_B821_8415E5676084__INCLUDED_)
#define AFX_ZVINSERTMODELNEWPAGEDLG_H__2AF4D47B_748C_4CBD_B821_8415E5676084__INCLUDED_

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

#include "ObjectCollections.h"

#include "zBaseLib\PSS_Dialog.h"
#include "zModelRes.h"
#include "ZCProcessModelTree.h"

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
// ZVInsertModelNewPageDlg dialog

class AFX_EXT_CLASS ZVInsertModelNewPageDlg : public PSS_Dialog
{
// Construction
public:

    // Standard constructor
    ZVInsertModelNewPageDlg( ZDProcessGraphModelMdl*    pModel,
                             const CString                NewPageName        = _T( "" ),
                             CStringArray*                pArrayPageName    = NULL,
                             ZBRuntimeClassSet*            pSet            = NULL,
                             CWnd*                        pParent            = NULL);

    CString GetPageName() const;
    ZDProcessGraphModelMdl* GetParentModel() const;

    CString GetParentModelFullName() const
    {
        return m_ParentModelFullName;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVInsertModelNewPageDlg)
    enum { IDD = IDD_INSERT_MODELPAGE };
    ZCProcessModelTree m_SymbolTree;
    CString m_PageName;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVInsertModelNewPageDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVInsertModelNewPageDlg)
    virtual void OnOK();
    afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void CheckControls();

private:

    CStringArray*            m_pArrayPageName;
    CString                    m_ParentModelFullName;
    ZDProcessGraphModelMdl*    m_pModel;
    ZDProcessGraphModelMdl*    m_pParentModel;

    // Set of elements that can be displayed in the tree
    ZBRuntimeClassSet*        m_pSet;
};

inline CString ZVInsertModelNewPageDlg::GetPageName() const
{
    return m_PageName;
}

inline ZDProcessGraphModelMdl* ZVInsertModelNewPageDlg::GetParentModel() const
{
    return m_pParentModel;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVINSERTMODELNEWPAGEDLG_H__2AF4D47B_748C_4CBD_B821_8415E5676084__INCLUDED_)
