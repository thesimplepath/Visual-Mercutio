/****************************************************************************
 * ==> PSS_SelectModelSymbolDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a select model symbol dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectModelSymbolDlgH
#define PSS_SelectModelSymbolDlgH

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
#include "PSS_SelectableDefs.h"

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
* Select model symbol dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectModelSymbolDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param title - the title
        *@param selectableItem - the selectable item
        *@param pSet - the runtime class set
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                 const CString&            title          = _T(""),
                                 int                       selectableItem = g_Selectable_All,
                                 PSS_RuntimeClassSet*      pSet           = NULL,
                                 CWnd*                     pParent        = NULL);

        /**
        * Constructor
        *@param pModel - the model
        *@param title - the title
        *@param selectableClass - the selectable runtime class
        *@param pSet - the runtime class set
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                 const CString&            title,
                                 CRuntimeClass*            pSelectableClass,
                                 PSS_RuntimeClassSet*      pSet    = NULL,
                                 CWnd*                     pParent = NULL);

        /**
        * Constructor
        *@param pModel - the model
        *@param titleResID - the title resource identifier
        *@param selectableItem - the selectable item
        *@param pSet - the runtime class set
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                 UINT                      titleResID,
                                 int                       selectableItem = g_Selectable_All,
                                 PSS_RuntimeClassSet*      pSet           = NULL,
                                 CWnd*                     pParent        = NULL);

        /**
        * Constructor
        *@param pModel - the model
        *@param titleResID - the title resource identifier
        *@param selectableItem - the selectable item
        *@param pSet - the runtime class set
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                 UINT                      titleResID,
                                 CRuntimeClass*            pSelectableClass,
                                 PSS_RuntimeClassSet*      pSet    = NULL,
                                 CWnd*                     pParent = NULL);

        virtual ~PSS_SelectModelSymbolDlg();

        /**
        * Gets the selected model
        *@return the selected model
        */
        virtual inline CODModel* GetSelectedModel();

        /**
        * Gets the selected symbol
        *@return the selected symbol
        */
        virtual inline CODSymbolComponent* GetSelectedSymbol();

        /**
        * Gets the selected page
        *@return the selected page
        */
        virtual inline PSS_ProcessGraphPage* GetSelectedPage();

        /**
        * Gets the symbol name
        *@return the symbol name
        */
        virtual inline CString GetSymbolName() const;

        /**
        * Gets the symbol path
        *@return the symbol path
        */
        virtual inline CString GetSymbolPath() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectModelSymbolDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectModelSymbolDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_SELECTSYMBOL
        };

        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_ProcessGraphPage*     m_pSelectedPage;
        CODModel*                 m_pSelectedModel;
        CODSymbolComponent*       m_pSelectedSymbol;
        CRuntimeClass*            m_pSelectableClass;
        PSS_RuntimeClassSet*      m_pSet;
        PSS_ProcessModelTree      m_SymbolTree;
        CString                   m_SymbolName;
        CString                   m_SymbolPath;
        CString                   m_Title;
        int                       m_SelectableItem;
};

//---------------------------------------------------------------------------
// PSS_SelectModelSymbolDlg
//---------------------------------------------------------------------------
CODModel* PSS_SelectModelSymbolDlg::GetSelectedModel()
{
    return m_pSelectedModel;
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_SelectModelSymbolDlg::GetSelectedSymbol()
{
    return m_pSelectedSymbol;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_SelectModelSymbolDlg::GetSelectedPage()
{
    return m_pSelectedPage;
}
//---------------------------------------------------------------------------
CString PSS_SelectModelSymbolDlg::GetSymbolName() const
{
    return m_SymbolName;
}
//---------------------------------------------------------------------------
CString PSS_SelectModelSymbolDlg::GetSymbolPath() const
{
    return m_SymbolPath;
}
//---------------------------------------------------------------------------

#endif
