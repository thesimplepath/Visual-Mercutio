/****************************************************************************
 * ==> PSS_InsertLinkModelPageDlg ------------------------------------------*
 ****************************************************************************
 * Description : Provides an insert link model page dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InsertLinkModelPageDlgH
#define PSS_InsertLinkModelPageDlgH

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

//processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "PSS_ObjectCollections.h"
#include "PSS_ProcessModelTree.h"

// resources
#include "zModelRes.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;

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
* Insert link model page dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InsertLinkModelPageDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param newPageName - the new page name
        *@param pPageNameArray - the page name array
        *@param pSet - the runtime class set
        *@param pParent - the parent window, can be NULL
        */
        PSS_InsertLinkModelPageDlg(PSS_ProcessGraphModelMdl* pModel,
                                   const CString&            newPageName    = "",
                                   CStringArray*             pPageNameArray = NULL,
                                   PSS_RuntimeClassSet*      pSet           = NULL,
                                   CWnd*                     pParent        = NULL);

        virtual ~PSS_InsertLinkModelPageDlg();

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline CString GetPageName() const;

        /**
        * Gets if the insert new page checkbox is selected
        *@return true if the insert new page checkbox is selected, otherwise false
        */
        virtual inline bool SelectInsertNewPage() const;

        /**
        * Gets the parent model
        *@return the parent model
        */
        virtual inline PSS_ProcessGraphModelMdl* GetParentModel() const;

        /**
        * Gets the parent model full name
        *@return the parent model full name
        */
        virtual inline CString GetParentModelFullName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InsertLinkModelPageDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_InsertLinkModelPageDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnSelchangedExistingPagetree(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnInsLink();
        afx_msg void OnInsLink2();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INSERTORLINK_MODELPAGE
        };

        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_ProcessGraphModelMdl* m_pParentModel;
        PSS_RuntimeClassSet*      m_pSet;
        PSS_ProcessModelTree      m_ExistingPages;
        PSS_ProcessModelTree      m_SymbolTree;
        CStringArray*             m_pArrayPageName;
        CString                   m_NewPageName;
        CString                   m_ParentModelFullName;
        CString                   m_PageName;
        int                       m_InsertOrLink;

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_InsertLinkModelPageDlg
//---------------------------------------------------------------------------
CString PSS_InsertLinkModelPageDlg::GetPageName() const
{
    return m_PageName;
}
//---------------------------------------------------------------------------
bool PSS_InsertLinkModelPageDlg::SelectInsertNewPage() const
{
    return !m_InsertOrLink;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_InsertLinkModelPageDlg::GetParentModel() const
{
    return m_pParentModel;
}
//---------------------------------------------------------------------------
CString PSS_InsertLinkModelPageDlg::GetParentModelFullName() const
{
    return m_ParentModelFullName;
}
//---------------------------------------------------------------------------

#endif
