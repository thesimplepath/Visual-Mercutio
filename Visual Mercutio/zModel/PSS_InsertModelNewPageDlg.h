/****************************************************************************
 * ==> PSS_InsertModelNewPageDlg -------------------------------------------*
 ****************************************************************************
 * Description : Provides an insert model new page dialog box               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InsertModelNewPageDlgH
#define PSS_InsertModelNewPageDlgH

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
#include "zBaseLib\PSS_Dialog.h"
#include "PSS_ObjectCollections.h"
#include "PSS_ProcessModelTree.h"

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
* Insert model new page dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InsertModelNewPageDlg : public PSS_Dialog
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
        PSS_InsertModelNewPageDlg(PSS_ProcessGraphModelMdl* pModel,
                                  const CString&            newPageName    = _T(""),
                                  CStringArray*             pArrayPageName = NULL,
                                  PSS_RuntimeClassSet*      pSet           = NULL,
                                  CWnd*                     pParent        = NULL);

        virtual ~PSS_InsertModelNewPageDlg();

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline CString GetPageName() const;

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
        //{{AFX_VIRTUAL(PSS_InsertModelNewPageDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InsertModelNewPageDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INSERT_MODELPAGE
        };

        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_ProcessGraphModelMdl* m_pParentModel;
        PSS_ProcessModelTree      m_SymbolTree;
        PSS_RuntimeClassSet*      m_pSet;
        CStringArray*             m_pPageNameArray;
        CString                   m_ParentModelFullName;
        CString                   m_PageName;

        /**
        * Checks the control state
        */
        void CheckControls();
};

//---------------------------------------------------------------------------
// PSS_InsertModelNewPageDlg
//---------------------------------------------------------------------------
CString PSS_InsertModelNewPageDlg::GetPageName() const
{
    return m_PageName;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_InsertModelNewPageDlg::GetParentModel() const
{
    return m_pParentModel;
}
//---------------------------------------------------------------------------
CString PSS_InsertModelNewPageDlg::GetParentModelFullName() const
{
    return m_ParentModelFullName;
};
//---------------------------------------------------------------------------

#endif
