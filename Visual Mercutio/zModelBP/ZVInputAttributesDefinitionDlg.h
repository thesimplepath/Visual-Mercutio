#if !defined(AFX_ZVINPUTATTRIBUTESDEFINITIONDLG_H__91FA06A9_8E2F_44DF_9AE7_A6F954422CD9__INCLUDED_)
#define AFX_ZVINPUTATTRIBUTESDEFINITIONDLG_H__91FA06A9_8E2F_44DF_9AE7_A6F954422CD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInputAttributesDefinitionDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zModelBP\zModelBPRes.h"
#include "zProperty\ZIProperties.h"

// class name mapping
#ifndef PSS_InputAttribute
    #define PSS_InputAttribute ZBInputAttribute
#endif

// forward class declaration
class ZBDynamicPropertiesManager;
class PSS_InputAttribute;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributesDefinitionDlg dialog

class AFX_EXT_CLASS ZVInputAttributesDefinitionDlg : public CDialog
{
// Construction
public:
    ZVInputAttributesDefinitionDlg(ZBDynamicPropertiesManager* pPropManager, ZBPropertySet* pSet, PSS_InputAttribute* pInputAttr = NULL, CWnd* pParent = NULL);   // standard constructor

    int GetCategoryID() const
    {
        return m_CategoryID;
    };
    int GetItemID() const
    {
        return m_ItemID;
    };
    CString    GetDefaultValue() const
    {
        return m_DefaultValue;
    };
    int GetVisibility() const
    {
        return m_Visibility;
    };
    int GetFlag() const
    {
        return m_Flag;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVInputAttributesDefinitionDlg)
    enum { IDD = IDD_INPUTATTRIBUTES_DEF };
    CComboBox    m_VisibilityList;
    CComboBox    m_FlagList;
    CString    m_DefaultValue;
    CString    m_DynamicAttributeName;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVInputAttributesDefinitionDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVInputAttributesDefinitionDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChooseDynAttr();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZBDynamicPropertiesManager* m_pPropManager;
    ZBPropertySet* m_pSet;
    PSS_InputAttribute* m_pInputAttr;

    int m_CategoryID;
    int m_ItemID;
    int m_Visibility;
    int m_Flag;

};

#endif
