#if !defined(AFX_ZVDeleteModelPageDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
#define AFX_ZVDeleteModelPageDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVDeleteModelPageDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "ObjectCollections.h"
#include "ZCProcessModelTree.h"

// resources
#include "zModelRes.h"

// Forward declaration
class ZDProcessGraphModelMdl;


#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS



/////////////////////////////////////////////////////////////////////////////
// ZVDeleteModelPageDlg dialog

class AFX_EXT_CLASS ZVDeleteModelPageDlg : public PSS_Dialog
{
// Construction
public:
    ZVDeleteModelPageDlg(ZDProcessGraphModelMdl* pModel, ZBRuntimeClassSet* pSet = NULL, CWnd* pParent = NULL);   // standard constructor

    CString    GetPageName() const;
    ZDProcessGraphPage* GetSelectedPage()
    {
        return m_pSelectedPage;
    };

// Dialog Data
    //{{AFX_DATA(ZVDeleteModelPageDlg)
    enum { IDD = IDD_DELETE_MODELPAGE };
    ZCProcessModelTree    m_SymbolTree;
    CString    m_PageName;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVDeleteModelPageDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVDeleteModelPageDlg)
    virtual void OnOK();
    afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZDProcessGraphModelMdl* m_pModel;

// Implementation
private:
    ZDProcessGraphPage* m_pSelectedPage;
    ZDProcessGraphPage* m_pRootPage;
    // Set of elements that can be displayed in the tree
    ZBRuntimeClassSet* m_pSet;
};

inline CString    ZVDeleteModelPageDlg::GetPageName() const
{
    return m_PageName;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVDeleteModelPageDlg_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
