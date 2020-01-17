/****************************************************************************
 * ==> PSS_FindSymbolDlg ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a find a symbol dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FindSymbolDlgH
#define PSS_FindSymbolDlgH

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
#include "PSS_SymbolListCtrl.h"

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
* Find a symbol dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FindSymbolDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param model - the model containing the symbol
        *@param resID - the resource identifier
        *@param pParent - the parent window, can be NULL
        */
        PSS_FindSymbolDlg(PSS_ProcessGraphModelMdl& model, UINT resID, CWnd* pParent = NULL);

        virtual ~PSS_FindSymbolDlg();

        /**
        * Gets the selected symbol
        *@return the selected symbol
        */
        virtual inline CODSymbolComponent* GetSelectedSymbol() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FindSymbolDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FindSymbolDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnFind();
        afx_msg void OnBrowse();
        afx_msg void OnChangeSymbolName();
        afx_msg void OnClickFindResultList(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkFindResultList(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Checks the control state
        */
        virtual void CheckControlState();

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_FIND_SYMBOL
        };

        PSS_ProcessGraphModelMdl& m_Model;
        CODSymbolComponent*       m_pSymbol;
        PSS_SymbolListCtrl        m_ResultList;
        CString                   m_SymbolName;
        UINT                      m_ResID;
        BOOL                      m_InAllModels;
        BOOL                      m_CaseSensitive;
        BOOL                      m_PartialSearch;
};

//---------------------------------------------------------------------------
// PSS_FindSymbolDlg
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_FindSymbolDlg::GetSelectedSymbol() const
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------

#endif
