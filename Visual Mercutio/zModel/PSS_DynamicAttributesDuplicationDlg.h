/****************************************************************************
 * ==> PSS_DynamicAttributesDuplicationDlg ---------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic attributes duplication dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DynamicAttributesDuplicationDlgH
#define PSS_DynamicAttributesDuplicationDlgH

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

// mfc
#include "afxwin.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_WizardDialog.h"
#include "zProperty\PSS_Property.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_DynamicAttributesManipulator.h"

// resources
#include "zModelRes.h"

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
* Dynamic attributes duplication dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DynamicAttributesDuplicationDlg : public PSS_WizardDialog
{
    DECLARE_DYNAMIC(PSS_DynamicAttributesDuplicationDlg)

    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_DYNAMICATTR_S3
        };

        /**
        * Constructor
        *@param pModelDoc - the model document
        *@param symbolSelected - if true, the symbol at which the attribute belongs is selected
        */
        PSS_DynamicAttributesDuplicationDlg(PSS_ProcessGraphModelDoc* pModelDoc, bool symbolSelected);

        virtual ~PSS_DynamicAttributesDuplicationDlg();

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Gets the category
        *@return the category
        */
        virtual inline CString GetCategory() const;

        /**
        * Checks if duplicate values checkbox is checked
        *@return TRUE if duplicate values checkbox is checked, otherwise FALSE
        */
        virtual inline BOOL DupValuesIsChecked() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DynamicAttributesDuplicationDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DynamicAttributesDuplicationDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnLbnSelchangeAttribCategoryList();
        afx_msg void OnBnClickedOk();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ProcessGraphModelDoc* m_pModelDoc;
        CEdit                     m_AttribNameTxtBox;
        CButton                   m_DuplicateValues;
        CListBox                  m_CategoryList;
        CStringArray              m_StaticAttribArray;
        CStringArray              m_DynamicAttribArray;
        CString                   m_Name;
        CString                   m_Category;
        BOOL                      m_DupValuesIsChecked;
        bool                      m_InternalNameChange;
};

//---------------------------------------------------------------------------
// PSS_DynamicAttributesDuplicationDlg
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesDuplicationDlg::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
CString PSS_DynamicAttributesDuplicationDlg::GetCategory() const
{
    return m_Category;
}
//---------------------------------------------------------------------------
BOOL PSS_DynamicAttributesDuplicationDlg::DupValuesIsChecked() const
{
    return m_DupValuesIsChecked;
}
//---------------------------------------------------------------------------

#endif
