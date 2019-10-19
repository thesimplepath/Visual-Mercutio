#if !defined(AFX_ZVFindSymbolExtDlg_H__A4CA0373_BC42_46A5_8106_AF4418EDAC5B__INCLUDED_)
#define AFX_ZVFindSymbolExtDlg_H__A4CA0373_BC42_46A5_8106_AF4418EDAC5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVFindSymbolExtDlg.h : header file
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



#include "zBaseLib\PSS_Dialog.h"
#include "zModelRes.h"

// ZCSymbolAttributesTreeCtrl
#include "ZCSymbolAttributesTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBPropertyAttributes;


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
// ZVFindSymbolExtDlg dialog

class AFX_EXT_CLASS ZVFindSymbolExtDlg : public PSS_Dialog
{
// Construction
public:
    ZVFindSymbolExtDlg(ZBPropertyAttributes* pPropAttributes = NULL, 
                       ZBPropertySet* pPropSet = NULL,
                       CWnd* pParent = NULL);   // standard constructor

    BOOL GetInAllModels() const
    {
        return m_InAllModels;
    };
    BOOL GetCaseSensitive() const
    {
        return m_CaseSensitive;
    };
    BOOL GetPartialSearch() const
    {
        return m_PartialSearch;
    };
    CString GetWhat() const
    {
        return m_What;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVFindSymbolExtDlg)
    enum { IDD = IDD_FIND_SYMBOL_EXT };
    ZCSymbolAttributesTreeCtrl    m_AttributeText;
    BOOL                        m_InAllModels;
    BOOL                        m_CaseSensitive;
    BOOL                        m_PartialSearch;
    CString                        m_What;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVFindSymbolExtDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVFindSymbolExtDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeSymbolName();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void    CheckControlState();

private:
    ZBPropertyAttributes* m_pPropAttributes;
    ZBPropertySet* m_pPropSet;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVFindSymbolExtDlg_H__A4CA0373_BC42_46A5_8106_AF4418EDAC5B__INCLUDED_)
