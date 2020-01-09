#if !defined(AFX_ZVINSERTLINKMODELPAGEDLG_H__BD317299_FA94_4B3D_9AE7_BD95F07744CE__INCLUDED_)
#define AFX_ZVINSERTLINKMODELPAGEDLG_H__BD317299_FA94_4B3D_9AE7_BD95F07744CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInsertLinkModelPageDlg.h : header file
//

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

//processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "PSS_ObjectCollections.h"
#include "PSS_ProcessModelTree.h"

// resources
#include "zModelRes.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
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
    ZVInsertLinkModelPageDlg(PSS_ProcessGraphModelMdl* pModel,
                             const CString NewPageName = "",
                             CStringArray* pArrayPageName = NULL,
                             PSS_RuntimeClassSet* pSet = NULL,
                             CWnd* pParent = NULL);

    CString    GetPageName() const
    {
        return m_PageName;
    };

    bool ChooseInsertNewPage() const
    {
        return (m_InsertOrLink == 0) ? true : false;
    };

    PSS_ProcessGraphModelMdl* GetParentModel() const;
    CString GetParentModelFullName() const
    {
        return m_ParentModelFullName;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVInsertLinkModelPageDlg)
    enum { IDD = IDD_INSERTORLINK_MODELPAGE };
    PSS_ProcessModelTree    m_ExistingPages;
    PSS_ProcessModelTree    m_SymbolTree;
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
    PSS_ProcessGraphModelMdl* m_pModel;
    PSS_ProcessGraphModelMdl* m_pParentModel;

    // Set of elements that can be displayed in the tree
    PSS_RuntimeClassSet* m_pSet;
};

inline PSS_ProcessGraphModelMdl* ZVInsertLinkModelPageDlg::GetParentModel() const
{
    return m_pParentModel;
}

#endif
