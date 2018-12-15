#if !defined(AFX_ZVFINDSYMBOLDLG_H__A4CA0373_BC42_46A5_8106_AF4418EDAC5B__INCLUDED_)
#define AFX_ZVFINDSYMBOLDLG_H__A4CA0373_BC42_46A5_8106_AF4418EDAC5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVFindSymbolDlg.h : header file
//

#ifdef _AFXEXT
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif



#include "zBaseLib\ZIDialog.h"
#include "zModelRes.h"

#include "ZCSymbolList.h"

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
// ZVFindSymbolDlg dialog

class AFX_EXT_CLASS ZVFindSymbolDlg : public ZIDialog
{
// Construction
public:
    ZVFindSymbolDlg(ZDProcessGraphModelMdl& Mdl, UINT nIDRes, CWnd* pParent = NULL);   // standard constructor

    CODSymbolComponent* GetSelectedSymbol() const { return m_pSymbol; };

private:
// Dialog Data
    //{{AFX_DATA(ZVFindSymbolDlg)
    enum { IDD = IDD_FIND_SYMBOL };
    ZCSymbolList    m_ResultList;
    CString    m_SymbolName;
    BOOL    m_InAllModels;
    BOOL    m_CaseSensitive;
    BOOL    m_PartialSearch;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVFindSymbolDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVFindSymbolDlg)
    afx_msg void OnFind();
    afx_msg void OnBrowse();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeSymbolName();
    afx_msg void OnClickFindResultList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkFindResultList(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void    CheckControlState();

private:
    ZDProcessGraphModelMdl&        m_Model;
    CODSymbolComponent*            m_pSymbol;
    UINT m_nIDRes;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVFINDSYMBOLDLG_H__A4CA0373_BC42_46A5_8106_AF4418EDAC5B__INCLUDED_)
