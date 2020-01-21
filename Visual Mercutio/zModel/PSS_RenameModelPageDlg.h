/****************************************************************************
 * ==> PSS_RenameModelPageDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a rename model page dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RenameModelPageDlgH
#define PSS_RenameModelPageDlgH

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
* Rename model page dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RenameModelPageDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pPageNameArray - the page name array
        *@param pPageToRename - the page to rename
        *@param pSet - the runtime class set
        *@param pParent - parent window, can be NULL
        */
        PSS_RenameModelPageDlg(PSS_ProcessGraphModelMdl* pModel,
                               CStringArray*             pPageNameArray = NULL,
                               PSS_ProcessGraphPage*     pPageToRename  = NULL,
                               PSS_RuntimeClassSet*      pSet           = NULL,
                               CWnd*                     pParent        = NULL);

        virtual ~PSS_RenameModelPageDlg();

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline CString GetPageName() const;

        /**
        * Gets the selected page
        *@return the selected page
        */
        virtual inline PSS_ProcessGraphPage* GetSelectedPage();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RenameModelPageDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RenameModelPageDlg)
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
            IDD = IDD_RENAME_MODELPAGE
        };

        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_ProcessGraphPage*     m_pSelectedPage;
        PSS_ProcessGraphPage*     m_pPageToRename;
        CStringArray*             m_pPageNameArray;
        PSS_RuntimeClassSet*      m_pSet;
        PSS_ProcessModelTree      m_SymbolTree;
        CString                   m_PageName;
};

//---------------------------------------------------------------------------
// PSS_RenameModelPageDlg
//---------------------------------------------------------------------------
CString PSS_RenameModelPageDlg::GetPageName() const
{
    return m_PageName;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_RenameModelPageDlg::GetSelectedPage()
{
    return m_pSelectedPage;
}
//---------------------------------------------------------------------------

#endif
