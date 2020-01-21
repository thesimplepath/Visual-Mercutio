/****************************************************************************
 * ==> PSS_SelectSymbolAttributeDlg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a select symbol attribute dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectSymbolAttributeDlgH
#define PSS_SelectSymbolAttributeDlgH

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
#include "zProperty\ZIProperties.h"
#include "PSS_SymbolAttributesTreeCtrl.h"

// resources
#include "zModelRes.h"

// forward class declaration
class ZBPropertyAttributes;

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
* Select symbol attribute dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SelectSymbolAttributeDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pPropAttributes - the property attributes
        *@param pPropSet - the properties set
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectSymbolAttributeDlg(ZBPropertyAttributes* pPropAttributes = NULL,
                                     ZBPropertySet*        pPropSet        = NULL,
                                     CWnd*                 pParent         = NULL);

        virtual ~PSS_SelectSymbolAttributeDlg();

        /**
        * Checks if the attributes should be set as default for all properties
        *@return TRUE if the attributes should be set as default for all properties, otherwise FALSE
        */
        virtual inline BOOL MustSetAsDefaultToAll() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectSymbolAttributeDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectSymbolAttributeDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnApplyToAll();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_SYMBOLATTRIBUTE_SELECTION
        };

        ZBPropertyAttributes*        m_pPropAttributes;
        ZBPropertySet*               m_pPropSet;
        PSS_SymbolAttributesTreeCtrl m_AttributeTree;
        BOOL                         m_SetAsDefaultToAll;
        BOOL                         m_ShowLabel;
};

//---------------------------------------------------------------------------
// PSS_SelectSymbolAttributeDlg
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolAttributeDlg::MustSetAsDefaultToAll() const
{
    return m_SetAsDefaultToAll;
}
//---------------------------------------------------------------------------

#endif
