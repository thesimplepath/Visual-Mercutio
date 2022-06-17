/****************************************************************************
 * ==> PSS_RenameModelPageInTreeDlg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a rename model page in tree dialog box            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RenameModelPageInTreeDlgH
#define PSS_RenameModelPageInTreeDlgH

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
#include "zBaseLib\PSS_FilteredDialog.h"

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
* Rename model page in tree dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RenameModelPageInTreeDlg : public PSS_FilteredDialog
{
    public:
        /**
        * Constructor
        *@param proposedName - the proposed name
        *@param pPageNameArray - the page name array
        *@param pParent - parent window, can be NULL
        */
        PSS_RenameModelPageInTreeDlg(const CString& proposedName   = _T(""),
                                     CStringArray*  pPageNameArray = NULL,
                                     CWnd*          pParent        = NULL);

        virtual ~PSS_RenameModelPageInTreeDlg();

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline CString GetPageName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RenameModelPageInTreeDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RenameModelPageInTreeDlg)
        afx_msg virtual BOOL OnInitDialog();
        afx_msg void OnChangePageName();
        afx_msg virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_RENAME_MODELPAGE_IN_TREE
        };

        CStringArray* m_pPageNameArray;
        CString       m_PageName;
};

//---------------------------------------------------------------------------
// PSS_RenameModelPageInTreeDlg
//---------------------------------------------------------------------------
CString PSS_RenameModelPageInTreeDlg::GetPageName() const
{
    return m_PageName;
}
//---------------------------------------------------------------------------

#endif
