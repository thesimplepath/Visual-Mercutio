/****************************************************************************
 * ==> PSS_DistributionAttributesDefinitionDlg -----------------------------*
 ****************************************************************************
 * Description : Provides a distribution attributes definition dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionAttributesDefinitionDlgH
#define PSS_DistributionAttributesDefinitionDlgH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zModelBP\PSS_DistributionAttributesList.h"
#include "zModelBP\zModelBPRes.h"
#include "zProperty\ZIProperties.h"

// class name mapping
#ifndef PSS_DistributionAttribute
    #define PSS_DistributionAttribute ZBDistributionAttribute
#endif
#ifndef PSS_DistributionAttributeManager
    #define PSS_DistributionAttributeManager ZBDistributionAttributeManager
#endif
#ifndef PSS_DistributionRulesForRole
    #define PSS_DistributionRulesForRole ZBDistributionRulesForRole
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_DistributionAttribute;
class PSS_DistributionAttributeManager;
class ZBDynamicPropertiesManager;
class PSS_DistributionRulesForRole;
class PSS_UserGroupEntity;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Distribution attributes definition dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionAttributesDefinitionDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pDistributionManager - the distribution manager
        *@param pPropManager -  the property manager
        *@param pSet - the property set
        *@param pMainUserGroup - the main user group
        *@param groupGUID - the user group GUID
        *@param pDistributionAttr - the distribution attribute
        *@param pParent - the parent window, can be NULL
        */
        PSS_DistributionAttributesDefinitionDlg(PSS_DistributionAttributeManager* pDistributionManager,
                                                ZBDynamicPropertiesManager*       pPropManager,
                                                ZBPropertySet*                    pSet,
                                                PSS_UserGroupEntity*              pMainUserGroup,
                                                const CString&                    groupGUID         = "",
                                                PSS_DistributionAttribute*        pDistributionAttr = NULL,
                                                CWnd*                             pParent           = NULL);

        virtual ~PSS_DistributionAttributesDefinitionDlg();

        /**
        * Gets the category identifier
        *@return the category identifier
        */
        virtual inline int GetCategoryID() const;

        /**
        * Gets the item identifier
        *@return the item identifier
        */
        virtual inline int GetItemID() const;

        /**
        * Gets the group unique identifier
        *@return the group unique identifier
        */
        virtual inline CString GetGroupGUID() const;

        /**
        * Gets the distribution attribute
        *@return the distribution attribute
        */
        virtual inline PSS_DistributionAttribute* GetDistributionAttribute();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DistributionAttributesDefinitionDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DistributionAttributesDefinitionDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnChooseDynattr();
        afx_msg void OnChooseUsergroup();
        afx_msg void OnAddruleButton();
        afx_msg void OnDelruleButton();
        afx_msg void OnModruleButton();
        afx_msg void OnClickDistriblist(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkDistriblist(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DISTRIBUTIONATTRIBUTES_DEF
        };

        PSS_DistributionAttributesList    m_List;
        PSS_DistributionAttributeManager* m_pDistributionManager;
        ZBDynamicPropertiesManager*       m_pPropManager;
        PSS_UserGroupEntity*              m_pMainUserGroup;
        PSS_DistributionAttribute*        m_pDistributionAttr;
        ZBPropertySet*                    m_pSet;
        CString                           m_DynamicAttributeName;
        CString                           m_GroupName;
        CString                           m_GroupGUID;
        int                               m_CategoryID;
        int                               m_ItemID;
        bool                              m_Allocated;

        /**
        * Checks the control state
        */
        void CheckControlState();

        /**
        * Gets the selected distribution attribute
        *@return the selected distribution attribute, NULL if no selection or on error
        */
        inline PSS_DistributionAttribute* GetSelectedDistributionAttribute();

        /**
        * Gets the selected distribution rule for role
        *@return the selected distribution rule for role, NULL if no selection or on error
        */
        inline PSS_DistributionRulesForRole* GetSelectedDistributionRuleForRole();

        /**
        * Gets the selected distribution rule
        *@return the selected distribution rule, NULL if no selection or on error
        */
        inline PSS_DistributionRule* GetSelectedDistributionRule();
};

//---------------------------------------------------------------------------
// PSS_DistributionAttributesDefinitionDlg
//---------------------------------------------------------------------------
int PSS_DistributionAttributesDefinitionDlg::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
int PSS_DistributionAttributesDefinitionDlg::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
CString PSS_DistributionAttributesDefinitionDlg::GetGroupGUID() const
{
    return m_GroupGUID;
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttributesDefinitionDlg::GetDistributionAttribute()
{
    return m_pDistributionAttr;
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttributesDefinitionDlg::GetSelectedDistributionAttribute()
{
    return m_List.GetSelectedDistributionAttribute();
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole* PSS_DistributionAttributesDefinitionDlg::GetSelectedDistributionRuleForRole()
{
    return m_List.GetSelectedDistributionRuleForRole();
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionAttributesDefinitionDlg::GetSelectedDistributionRule()
{
    return m_List.GetSelectedDistributionRule();
}
//---------------------------------------------------------------------------

#endif
