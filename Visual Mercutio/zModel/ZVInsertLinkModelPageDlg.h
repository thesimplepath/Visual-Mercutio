#if !defined(AFX_ZVINSERTLINKMODELPAGEDLG_H__BD317299_FA94_4B3D_9AE7_BD95F07744CE__INCLUDED_)
#define AFX_ZVINSERTLINKMODELPAGEDLG_H__BD317299_FA94_4B3D_9AE7_BD95F07744CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInsertLinkModelPageDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

//processsoft
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
// ZVInsertLinkModelPageDlg dialog

class AFX_EXT_CLASS ZVInsertLinkModelPageDlg : public PSS_Dialog
{
// Construction
public:
    ZVInsertLinkModelPageDlg(ZDProcessGraphModelMdl* pModel, const CString NewPageName = "", CStringArray* pArrayPageName = NULL, ZBRuntimeClassSet* pSet = NULL, CWnd* pParent = NULL);   // standard constructor

    CString    GetPageName() const
    {
        return m_PageName;
    };

    bool ChooseInsertNewPage() const
    {
        return (m_InsertOrLink == 0) ? true : false;
    };

    ZDProcessGraphModelMdl*    GetParentModel() const;
    CString GetParentModelFullName() const
    {
        return m_ParentModelFullName;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVInsertLinkModelPageDlg)
    enum { IDD = IDD_INSERTORLINK_MODELPAGE };
    ZCProcessModelTree    m_ExistingPages;
    ZCProcessModelTree    m_SymbolTree;
    CString            m_NewPageName;
    int                m_InsertOrLink;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVInsertLinkModelPageDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVInsertLinkModelPageDlg)
    virtual void OnOK();
    afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchangedExistingPagetree(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnInsLink();
    afx_msg void OnInsLink2();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    void CheckControlState();

private:
    CStringArray* m_pArrayPageName;
    CString m_ParentModelFullName;
    CString m_PageName;
    ZDProcessGraphModelMdl* m_pModel;
    ZDProcessGraphModelMdl* m_pParentModel;

    // Set of elements that can be displayed in the tree
    ZBRuntimeClassSet* m_pSet;
};

inline ZDProcessGraphModelMdl*    ZVInsertLinkModelPageDlg::GetParentModel() const
{
    return m_pParentModel;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVINSERTLINKMODELPAGEDLG_H__BD317299_FA94_4B3D_9AE7_BD95F07744CE__INCLUDED_)
