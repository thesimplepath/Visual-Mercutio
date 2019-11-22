// ZVSelectModelSymbolDlg.h : header file

#if !defined(AFX_ZVSELECTMODELSYMBOLDLG_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_)
#define AFX_ZVSELECTMODELSYMBOLDLG_H__5CD7AD82_AB75_4CDC_9B1B_0F0808494530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
#include "ZDefinitionSelectable.h"
#include "ZCProcessModelTree.h"

// resources
#include "zModelRes.h"

// forward class declaration
class ZDProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVSelectModelSymbolDlg dialog

class AFX_EXT_CLASS ZVSelectModelSymbolDlg : public PSS_Dialog
{
// Construction
public:

    // Standard constructor
    ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*        pModel,
                            const CString                Title                = _T( "" ),
                            int                            SelectableItem        = Selectable_All,
                            PSS_RuntimeClassSet*          pSet                = NULL,
                            CWnd*                        pParent                = NULL);

    ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*        pModel,
                            const CString                Title,
                            CRuntimeClass*                pSelectableClass,
                            PSS_RuntimeClassSet*          pSet                = NULL,
                            CWnd*                        pParent                = NULL );

    ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*        pModel,
                            UINT                        nIDResTitle,
                            int                            SelectableItem        = Selectable_All,
                            PSS_RuntimeClassSet*          pSet                = NULL,
                            CWnd*                        pParent                = NULL );

    ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*        pModel,
                            UINT                        nIDResTitle,
                            CRuntimeClass*                pSelectableClass,
                            PSS_RuntimeClassSet*          pSet                = NULL,
                            CWnd*                        pParent                = NULL );

    CODModel* GetSelectedModel()
    {
        return m_pSelectedModel;
    };

    CODSymbolComponent* GetSelectedSymbol()
    {
        return m_pSelectedSymbol;
    };

    ZDProcessGraphPage* GetSelectedPage()
    {
        return m_pSelectedPage;
    };

    CString GetSymbolPath() const
    {
        return m_SymbolPath;
    };

    CString GetSymbolName() const
    {
        return m_SymbolName;
    };

    // Dialog Data
    //{{AFX_DATA(ZVSelectModelSymbolDlg)
    enum { IDD = IDD_SELECTSYMBOL };
    ZCProcessModelTree    m_SymbolTree;
    CString    m_SymbolPath;
    CString    m_SymbolName;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVSelectModelSymbolDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Implementation
    // Generated message map functions
    //{{AFX_MSG(ZVSelectModelSymbolDlg)
    virtual void OnOK();
    afx_msg void OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    ZDProcessGraphModelMdl*    m_pModel;
    CRuntimeClass*            m_pSelectableClass;
    CODModel*                m_pSelectedModel;
    CODSymbolComponent*        m_pSelectedSymbol;
    ZDProcessGraphPage*        m_pSelectedPage;
    CString                    m_Title;
    int                        m_SelectableItem;

    // Set of elements that can be displayed in the tree
    PSS_RuntimeClassSet*        m_pSet;
};

#endif
