/****************************************************************************
 * ==> PSS_SelectPropertyDlg -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog box to select a property                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectPropertyDlgH
#define PSS_SelectPropertyDlgH

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
#include "zPtyMgr\zPtyMgrRes.h"
#include "PSS_PropertyListCtrl.h"

// class name mapping
#ifndef PSS_DynamicPropertiesManager
    #define PSS_DynamicPropertiesManager ZBDynamicPropertiesManager
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_DynamicPropertiesManager;
class PSS_ProcessGraphModelMdl;

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Select a property dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectPropertyDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pProps - the properties
        *@param showType - the view type to show
        *@param selection - if true, the selection is allowed
        *@param allowItemSelection - if true, the item selection is allowed
        *@param allowCategorySelection - if true, the category selection is allowed
        *@param pPropManager - the property manager
        *@param pModel - the model
        *@param pParent - the parent window, can be NULL
        */
        PSS_SelectPropertyDlg(PSS_Properties*               pProps,
                              int                           showType               = 0,
                              bool                          selection              = true,
                              bool                          allowItemSelection     = true,
                              bool                          allowCategorySelection = false,
                              PSS_DynamicPropertiesManager* pPropManager           = NULL,
                              PSS_ProcessGraphModelMdl*     pModel                 = NULL,
                              CWnd*                         pParent                = NULL);

        /**
        * Constructor
        *@param pPropSet - the property set
        *@param showType - the view type to show
        *@param selection - if true, the selection is allowed
        *@param allowItemSelection - if true, the item selection is allowed
        *@param allowCategorySelection - if true, the category selection is allowed
        *@param pPropManager - the property manager
        *@param pModel - the model
        *@param pParent - the parent window, can be NULL
        */
        PSS_SelectPropertyDlg(PSS_Properties::IPropertySet* pPropSet,
                              int                           showType               = 0,
                              bool                          selection              = true,
                              bool                          allowItemSelection     = true,
                              bool                          allowCategorySelection = false,
                              PSS_DynamicPropertiesManager* pPropManager           = NULL,
                              PSS_ProcessGraphModelMdl*     pModel                 = NULL,
                              CWnd*                         pParent                = NULL);

        /**
        * Gets the selected property
        *@return the selected property
        */
        virtual inline PSS_Property* GetSelectedProperty();

        /**
        * Gets the selected property item
        *@return the selected property item
        */
        virtual inline PSS_PropertyItem* GetSelectedPropertyItem() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectPropertyDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_SelectPropertyDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnProptype();
        afx_msg void OnRenameAttribute();
        afx_msg void OnDeleteAttribute();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_ALL_PROPERTIES
        };

        PSS_PropertyListCtrl          m_PropertyList;
        PSS_Properties*               m_pProperties;
        PSS_Properties::IPropertySet* m_pPropSet;
        PSS_PropertyItem*             m_pSelectedProperty;
        PSS_DynamicPropertiesManager* m_pPropManager;
        PSS_ProcessGraphModelMdl*     m_pModel;
        int                           m_PropType;
        bool                          m_AllowItemSelection;
        bool                          m_AllowCategorySelection;
        bool                          m_Selection;

        /**
        * Checks the control state
        */
        void CheckControlStates();
};

//---------------------------------------------------------------------------
// PSS_SelectPropertyDlg
//---------------------------------------------------------------------------
PSS_Property* PSS_SelectPropertyDlg::GetSelectedProperty()
{
    if (m_pSelectedProperty)
        return m_PropertyList.GetMatchingProperty(m_pSelectedProperty);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItem* PSS_SelectPropertyDlg::GetSelectedPropertyItem() const
{
    return m_pSelectedProperty;
}
//---------------------------------------------------------------------------

#endif
