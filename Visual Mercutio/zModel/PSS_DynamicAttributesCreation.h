/****************************************************************************
 * ==> PSS_DynamicAttributesCreation ---------------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic attributes creation wizard              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DynamicAttributesCreationH
#define PSS_DynamicAttributesCreationH

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
#include "zBaseLib\PSS_WizardDialog.h"
#include "zProperty\ZBProperty.h"
#include "zModel\zModelRes.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dynamic attributes creation wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DynamicAttributesCreation
{
    public:
        /**
        * Constructor
        *@param pModelDoc - the model document
        *@param symbolSelected - if true, the symbol at which the attribute belongs is selected
        */
        PSS_DynamicAttributesCreation(PSS_ProcessGraphModelDoc* pModelDoc, bool symbolSelected);

        virtual ~PSS_DynamicAttributesCreation();

        /**
        * Gets the categoory name
        *@return the category name
        */
        virtual inline CString GetCategoryName() const;

        /**
        * Gets the attribute name
        *@return the attribute name
        */
        virtual inline CString GetAttributeName() const;

        /**
        * Gets the attribute description
        *@return the attribute description
        */
        virtual inline CString GetAttributeDescription() const;

        /**
        * Gets the property type
        *@return the property type
        */
        virtual inline ZBProperty::PropertyType GetPropertyType() const;

        /**
        * Gets the visibility
        *@return the visibility
        */
        virtual inline int GetVisibility() const;

        /**
        * Shows the dialog box in modal mode
        *@return the modal result
        */
        virtual int DoModal();

    private:
        PSS_ProcessGraphModelDoc* m_pModelDoc;
        ZBProperty::PropertyType  m_PropertyType;
        CString                   m_CategoryName;
        CString                   m_AttributeDescription;
        CString                   m_AttributeName;
        int                       m_Visibility;
        bool                      m_SymbolSelected;
};

//---------------------------------------------------------------------------
// PSS_DynamicAttributesCreation
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesCreation::GetCategoryName() const
{
    return m_CategoryName;
}
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesCreation::GetAttributeName() const
{
    return m_AttributeName;
}
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesCreation::GetAttributeDescription() const
{
    return m_AttributeDescription;
}
//---------------------------------------------------------------------------
ZBProperty::PropertyType PSS_DynamicAttributesCreation::GetPropertyType() const
{
    return m_PropertyType;
}
//---------------------------------------------------------------------------
int PSS_DynamicAttributesCreation::GetVisibility() const
{
    return m_Visibility;
}
//---------------------------------------------------------------------------

/**
* Select dynamic attributes category dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DynamicAttributesSelectCategoryDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pModelDoc - the model document
        *@param pParent - the parent window, can be NULL
        */
        PSS_DynamicAttributesSelectCategoryDlg(PSS_ProcessGraphModelDoc* pModelDoc, CWnd* pParent = NULL);

        virtual ~PSS_DynamicAttributesSelectCategoryDlg();

        /**
        * Gets the categoory name
        *@return the category name
        */
        virtual inline CString GetCategoryName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DynamicAttributesSelectCategoryDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DynamicAttributesSelectCategoryDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnChangeCategoryName();
        afx_msg void OnSelchangeCategoryList();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_DYNAMICATTR_S1
        };

        PSS_ProcessGraphModelDoc* m_pModelDoc;
        CListBox                  m_CategoryList;
        CStringArray              m_StaticAttribArray;
        CStringArray              m_DynamicAttribArray;
        CString                   m_CategoryName;
        bool                      m_InternalNameChange;

        /**
        * Checks the data
        *@return true on success, otherwise false
        */
        bool CheckData();
};

//---------------------------------------------------------------------------
// PSS_DynamicAttributesSelectCategoryDlg
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesSelectCategoryDlg::GetCategoryName() const
{
    return m_CategoryName;
}
//---------------------------------------------------------------------------

/**
* Create dynamic attribute dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DynamicAttributesCreateAttributeDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pModelDoc - the model document
        *@param category - the selected category
        *@param symbolSelected - if true, the symbol at which the attribute belongs is selected
        *@param pParent - the parent window, can be NULL
        */
        PSS_DynamicAttributesCreateAttributeDlg(PSS_ProcessGraphModelDoc* pModelDoc,
                                                const CString&            category,
                                                bool                      symbolSelected,
                                                CWnd*                     pParent = NULL);

        virtual ~PSS_DynamicAttributesCreateAttributeDlg();

        /**
        * Gets the attribute name
        *@return the attribute name
        */
        virtual inline CString GetAttributeName() const;

        /**
        * Gets the attribute description
        *@return the attribute description
        */
        virtual inline CString GetAttributeDescription() const;

        /**
        * Gets the property type
        *@return the property type
        */
        virtual inline ZBProperty::PropertyType GetPropertyType() const;

        /**
        * Gets the visibility
        *@return the visibility
        */
        virtual inline int GetVisibility() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DynamicAttributesCreateAttributeDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DynamicAttributesCreateAttributeDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_DYNAMICATTR_S2
        };

        PSS_ProcessGraphModelDoc* m_pModelDoc;
        ZBProperty::PropertyType  m_PropertyType;
        CComboBox                 m_AttributeVisibility;
        CComboBox                 m_AttributeType;
        CString                   m_AttributeDescription;
        CString                   m_AttributeName;
        CString                   m_Category;
        int                       m_Visibility;
        bool                      m_SymbolSelected;

        /**
        * Checks the data
        *@return true on success, otherwise false
        */
        bool CheckData();
};

//---------------------------------------------------------------------------
// PSS_DynamicAttributesCreateAttributeDlg
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesCreateAttributeDlg::GetAttributeName() const
{
    return m_AttributeName;
}
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesCreateAttributeDlg::GetAttributeDescription() const
{
    return m_AttributeDescription;
}
//---------------------------------------------------------------------------
ZBProperty::PropertyType PSS_DynamicAttributesCreateAttributeDlg::GetPropertyType() const
{
    return m_PropertyType;
}
//---------------------------------------------------------------------------
int PSS_DynamicAttributesCreateAttributeDlg::GetVisibility() const
{
    return m_Visibility;
}
//---------------------------------------------------------------------------

#endif
