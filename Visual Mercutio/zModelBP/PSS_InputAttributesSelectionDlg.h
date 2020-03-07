/****************************************************************************
 * ==> PSS_InputAttributesSelectionDlg -------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes selection dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputAttributesSelectionDlgH
#define PSS_InputAttributesSelectionDlgH

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
#include "PSS_InputAttributesList.h"

// resources
#include "zModelBP\zModelBPRes.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input attributes selection dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputAttributesSelectionDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pInputManager - the input manager
        *@param pPropManager - the property manager
        *@param pParent - the parent window, can be NULL
        */
        PSS_InputAttributesSelectionDlg(PSS_InputAttributeManager*  pInputManager,
                                        ZBDynamicPropertiesManager* pPropManager,
                                        CWnd*                       pParent = NULL);

        virtual ~PSS_InputAttributesSelectionDlg();

        /**
        * Gets the selected input attribute
        *@return the selected input attribute
        */
        virtual inline PSS_InputAttribute* GetSelectedInputAttribute();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InputAttributesSelectionDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InputAttributesSelectionDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnClickInputattributeList(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkInputattributeList(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INPUTATTRIBUTES
        };

        PSS_InputAttributeManager*  m_pInputManager;
        ZBDynamicPropertiesManager* m_pPropManager;
        PSS_InputAttributesList     m_List;

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_InputAttributesSelectionDlg
//---------------------------------------------------------------------------
PSS_InputAttribute* PSS_InputAttributesSelectionDlg::GetSelectedInputAttribute()
{
    return m_List.GetSelectedInputAttribute();
}
//---------------------------------------------------------------------------

#endif
