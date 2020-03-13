/****************************************************************************
 * ==> PSS_FindSymbolExtDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a find symbol dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FindSymbolExtDlgH
#define PSS_FindSymbolExtDlgH

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
#include "PSS_SymbolAttributesTreeCtrl.h"

// resources
#include "zModelRes.h"

// forward class declaration
class PSS_PropertyAttributes;

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
* Find symbol dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FindSymbolExtDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pPropAttributes - the property attributes, can be NULL
        *@param pPropSet - the properties set, can be NULL
        *@param pParent - the parent window, can be NULL
        */
        PSS_FindSymbolExtDlg(PSS_PropertyAttributes*       pPropAttributes = NULL,
                             PSS_Properties::IPropertySet* pPropSet        = NULL,
                             CWnd*                         pParent         = NULL);

        virtual ~PSS_FindSymbolExtDlg();

        /**
        * Gets if the search should be extended to all models
        *@return TRUE if the search should be extended to all models, otherwise FALSE
        */
        virtual inline BOOL GetInAllModels() const;

        /**
        * Gets if the search is case sensitive
        *@return TRUE if the search is case sensitive, otherwise FALSE
        */
        virtual inline BOOL GetCaseSensitive() const;

        /**
        * Gets if the search should be partial
        *@return TRUE if the search should be partial, otherwise FALSE
        */
        virtual inline BOOL GetPartialSearch() const;

        /**
        * Gets the search argument
        *@return the search argument
        */
        virtual inline CString GetSearchArgument() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FindSymbolExtDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FindSymbolExtDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnChangeSymbolName();
        virtual void OnOK();
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
            IDD = IDD_FIND_SYMBOL_EXT
        };

        PSS_PropertyAttributes*       m_pPropAttributes;
        PSS_Properties::IPropertySet* m_pPropSet;
        PSS_SymbolAttributesTreeCtrl  m_AttributeText;
        CString                       m_SearchArgument;
        BOOL                          m_InAllModels;
        BOOL                          m_CaseSensitive;
        BOOL                          m_PartialSearch;
};

//---------------------------------------------------------------------------
// PSS_FindSymbolExtDlg
//---------------------------------------------------------------------------
BOOL PSS_FindSymbolExtDlg::GetInAllModels() const
{
    return m_InAllModels;
}
//---------------------------------------------------------------------------
BOOL PSS_FindSymbolExtDlg::GetCaseSensitive() const
{
    return m_CaseSensitive;
}
//---------------------------------------------------------------------------
BOOL PSS_FindSymbolExtDlg::GetPartialSearch() const
{
    return m_PartialSearch;
}
//---------------------------------------------------------------------------
CString PSS_FindSymbolExtDlg::GetSearchArgument() const
{
    return m_SearchArgument;
}
//---------------------------------------------------------------------------

#endif
