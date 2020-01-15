/****************************************************************************************************************
 *                                            classe ZVDynamicAttributesDuplication                                *
 ****************************************************************************************************************
 * JMR-MODIF - Le 18 août 2005 - Ajout de la classe ZVDynamicAttributesDuplication.                                *
 * Cette classe représente la boîte de dialogue permettant de paramétrer la copie d'attributs dynamiques. Elle    *
 * s'occupe de la validité des données, et mets ces dernières à disposition pour l'opération de copie.            *
 ****************************************************************************************************************/

#if !defined(AFX_ZVDYNAMICATTRIBUTESDUPLICATION_H__7CD0522A_A41A_456A_A5A9_52FB2F9B6BA1__INCLUDED_)
#define AFX_ZVDYNAMICATTRIBUTESDUPLICATION_H__7CD0522A_A41A_456A_A5A9_52FB2F9B6BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

 // Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_WizardDialog.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\zModelRes.h"

#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zProperty\ZBProperty.h"

#include "afxwin.h"
#include "PSS_DynamicAttributesManipulator.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// **************************************************************************************************************
// *                                      Classe ZVDynamicAttributesDuplication                                    *
// **************************************************************************************************************
class ZVDynamicAttributesDuplication : public PSS_WizardDialog
{
    DECLARE_DYNAMIC(ZVDynamicAttributesDuplication)

public:

    ZVDynamicAttributesDuplication(PSS_ProcessGraphModelDoc* pModelDoc, bool SymbolSelected);
    virtual ~ZVDynamicAttributesDuplication();

    // Données de boîte de dialogue
    enum
    {
        IDD = IDD_WZ_DYNAMICATTR_S3
    };

protected:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVDynamicAttributesCreationS1)
    virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV
    //}}AFX_VIRTUAL

    // Generated message map functions
    //{{AFX_MSG(ZVDynamicAttributesCreationS1)
    virtual BOOL OnInitDialog();
    afx_msg void OnLbnSelchangeAttribCategoryList();
    afx_msg void OnBnClickedOk();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:

    CString                    m_Name;
    CString                    m_Category;

    BOOL                    m_bDupValuesIsChecked;

private:

    PSS_ProcessGraphModelDoc*    m_pModelDoc;

    CStringArray            m_StaticAttribArray;
    CStringArray            m_DynamicAttribArray;

    CListBox                m_CategoryList;

    bool                    m_InternalNameChange;

    CEdit                    m_AttribNameTxtBox;
    CButton                    m_cbDuplicateValues;
};

#endif
