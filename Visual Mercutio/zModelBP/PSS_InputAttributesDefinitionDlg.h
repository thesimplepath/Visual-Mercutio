/****************************************************************************
 * ==> PSS_InputAttributesDefinitionDlg ------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes definition dialog box         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputAttributesDefinitionDlgH
#define PSS_InputAttributesDefinitionDlgH

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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input attributes definition dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputAttributesDefinitionDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pPropManager - the property manager
        *@param pSet - the property set
        *@param pInputAttr - the input attributes
        *@param pParent - the parent window, can be NULL
        */
        PSS_InputAttributesDefinitionDlg(ZBDynamicPropertiesManager* pPropManager,
                                         ZBPropertySet*              pSet,
                                         PSS_InputAttribute*         pInputAttr = NULL,
                                         CWnd*                       pParent    = NULL);

        virtual ~PSS_InputAttributesDefinitionDlg();

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
        * Gets the default value
        *@return the default value
        */
        virtual inline CString GetDefaultValue() const;

        /**
        * Gets the visibility
        *@return the visibility
        */
        virtual inline int GetVisibility() const;

        /**
        * Gets the flags
        *@return the flags
        */
        virtual inline int GetFlag() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InputAttributesDefinitionDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InputAttributesDefinitionDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnChooseDynAttr();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INPUTATTRIBUTES_DEF
        };

        ZBDynamicPropertiesManager* m_pPropManager;
        ZBPropertySet*              m_pSet;
        PSS_InputAttribute*         m_pInputAttr;
        CComboBox                   m_VisibilityList;
        CComboBox                   m_FlagList;
        CString                     m_DefaultValue;
        CString                     m_DynamicAttributeName;
        int                         m_CategoryID;
        int                         m_ItemID;
        int                         m_Visibility;
        int                         m_Flag;
};

//---------------------------------------------------------------------------
// PSS_InputAttributesDefinitionDlg
//---------------------------------------------------------------------------
int PSS_InputAttributesDefinitionDlg::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
int PSS_InputAttributesDefinitionDlg::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
CString PSS_InputAttributesDefinitionDlg::GetDefaultValue() const
{
    return m_DefaultValue;
}
//---------------------------------------------------------------------------
int PSS_InputAttributesDefinitionDlg::GetVisibility() const
{
    return m_Visibility;
}
//---------------------------------------------------------------------------
int PSS_InputAttributesDefinitionDlg::GetFlag() const
{
    return m_Flag;
}
//---------------------------------------------------------------------------

#endif
