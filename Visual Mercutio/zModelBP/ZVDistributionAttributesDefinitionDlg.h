#if !defined(AFX_ZVDISTRIBUTIONATTRIBUTESDEFINITIONDLG_H__D757EF50_18E9_4D65_A086_707453C89826__INCLUDED_)
#define AFX_ZVDISTRIBUTIONATTRIBUTESDEFINITIONDLG_H__D757EF50_18E9_4D65_A086_707453C89826__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVDistributionAttributesDefinitionDlg.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zModelBP\ZCDistributionAttributesList.h"
#include "zModelBP\zModelBPRes.h"
#include "zProperty\ZIProperties.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class ZBDistributionAttributeManager;
class ZBDynamicPropertiesManager;
class ZBDistributionAttribute;
class ZBDistributionRulesForRole;
class PSS_UserGroupEntity;


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
// ZVDistributionAttributesDefinitionDlg dialog

class AFX_EXT_CLASS ZVDistributionAttributesDefinitionDlg : public CDialog
{
// Construction
public:
    ZVDistributionAttributesDefinitionDlg(ZBDistributionAttributeManager* pDistributionManager, 
                                          ZBDynamicPropertiesManager* pPropManager, 
                                          ZBPropertySet* pSet, 
                                          PSS_UserGroupEntity* pMainUserGroup,
                                          const CString GroupGUID = "",
                                          ZBDistributionAttribute* pDistributionAttr = NULL, 
                                          CWnd* pParent = NULL);   // standard constructor

    virtual ~ZVDistributionAttributesDefinitionDlg();
    
    int GetCategoryID() const
    {
        return m_CategoryID;
    };
    int GetItemID() const
    {
        return m_ItemID;
    };
    CString GetGroupGUID() const
    {
        return m_GroupGUID;
    };
    ZBDistributionAttribute* GetDistributionAttribute()
    {
        return m_pDistributionAttr;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVDistributionAttributesDefinitionDlg)
    enum { IDD = IDD_DISTRIBUTIONATTRIBUTES_DEF };
    ZCDistributionAttributesList    m_List;
    CString    m_DynamicAttributeName;
    CString    m_GroupName;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVDistributionAttributesDefinitionDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVDistributionAttributesDefinitionDlg)
    afx_msg void OnChooseDynattr();
    afx_msg void OnChooseUsergroup();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnAddruleButton();
    afx_msg void OnDelruleButton();
    afx_msg void OnModruleButton();
    afx_msg void OnClickDistriblist(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkDistriblist(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    void CheckControlState();
    ZBDistributionAttribute* GetSelectedDistributionAttribute()
    {
        return m_List.GetSelectedDistributionAttribute();
    };
    ZBDistributionRulesForRole*    GetSelectedDistributionRuleForRole()
    {
        return m_List.GetSelectedDistributionRuleForRole();
    };
    ZBDistributionRule*    GetSelectedDistributionRule()
    {
        return m_List.GetSelectedDistributionRule();
    };

private:
    ZBDistributionAttributeManager* m_pDistributionManager;
    ZBDynamicPropertiesManager* m_pPropManager;
    ZBPropertySet* m_pSet;
    PSS_UserGroupEntity* m_pMainUserGroup;
    ZBDistributionAttribute* m_pDistributionAttr;

    int m_CategoryID;
    int m_ItemID;
    CString m_GroupGUID;

    bool m_Allocated;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVDISTRIBUTIONATTRIBUTESDEFINITIONDLG_H__D757EF50_18E9_4D65_A086_707453C89826__INCLUDED_)
