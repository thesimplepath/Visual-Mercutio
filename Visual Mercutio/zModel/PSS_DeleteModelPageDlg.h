/****************************************************************************
 * ==> PSS_DeleteModelPageDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a delete model page dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DeleteModelPageDlgH
#define PSS_DeleteModelPageDlgH

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
* Delete model page dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DeleteModelPageDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pSet - the runtime class set
        *@param pParent - the parent window, can be NULL
        */
        PSS_DeleteModelPageDlg(PSS_ProcessGraphModelMdl* pModel, PSS_RuntimeClassSet* pSet = NULL, CWnd* pParent = NULL);

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline CString GetPageName() const;

        /**
        * Gets the selected page
        *@return the selected page, NULL if no selection or on error
        */
        virtual inline PSS_ProcessGraphPage* GetSelectedPage();

    protected:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DELETE_MODELPAGE
        };

        PSS_ProcessModelTree m_SymbolTree;
        CString              m_PageName;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DeleteModelPageDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DeleteModelPageDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_ProcessGraphPage*     m_pRootPage;
        PSS_ProcessGraphPage*     m_pSelectedPage;
        PSS_RuntimeClassSet*      m_pSet;
};

//---------------------------------------------------------------------------
// PSS_DeleteModelPageDlg
//---------------------------------------------------------------------------
CString PSS_DeleteModelPageDlg::GetPageName() const
{
    return m_PageName;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_DeleteModelPageDlg::GetSelectedPage()
{
    return m_pSelectedPage;
}
//---------------------------------------------------------------------------

#endif
