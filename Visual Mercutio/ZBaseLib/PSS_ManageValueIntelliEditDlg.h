/****************************************************************************
 * ==> PSS_ManageValueIntelliEditDlg ---------------------------------------*
 ****************************************************************************
 * Description : Provides a manage intelligent edit value dialog box        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ManageValueIntelliEditDlgH
#define PSS_ManageValueIntelliEditDlgH

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

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Manage intelligent edit value dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ManageValueIntelliEditDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pArrayOfValues - array of values
        *@param pParent - parent window, can be NULL
        */
        PSS_ManageValueIntelliEditDlg(CStringArray* pArrayOfValues, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZVManageValueIntelliEdit)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZVManageValueIntelliEdit)
        afx_msg void OnAddvalue();
        afx_msg void OnDelvalue();
        afx_msg void OnSelchangeValues();
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CStringArray* m_pArrayOfValues;
        CListBox      m_Values;
};

#endif
