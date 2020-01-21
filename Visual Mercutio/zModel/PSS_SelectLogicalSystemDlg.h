/****************************************************************************
 * ==> PSS_SelectLogicalSystemDlg ------------------------------------------*
 ****************************************************************************
 * Description : Provides a select logical system dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectLogicalSystemDlgH
#define PSS_SelectLogicalSystemDlgH

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
#include "PSS_LogicalSystemTreeCtrl.h"

// resources
#include "zModelRes.h"

// old class name mapping
#ifndef PSS_SystemEntity
    #define PSS_SystemEntity ZBSystemEntity
#endif
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// forward class declaration
class PSS_SystemEntity;
class PSS_LogicalSystemEntity;

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
* Select logical system dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectLogicalSystemDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param title - the title
        *@param pMainLogicalSystemGroup - the main logical system group
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectLogicalSystemDlg(const CString&           title                   = _T(""),
                                   PSS_LogicalSystemEntity* pMainLogicalSystemGroup = NULL,
                                   CWnd*                    pParent                 = NULL);

        /**
        * Constructor
        *@param title - the title identifier in resources
        *@param pMainLogicalSystemGroup - the main logical system group
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectLogicalSystemDlg(UINT                     titleID,
                                   PSS_LogicalSystemEntity* pMainLogicalSystemGroup,
                                   CWnd*                    pParent = NULL);

        virtual ~PSS_SelectLogicalSystemDlg();

        /**
        * Release the dialog box content
        */
        virtual void Release();

        /**
        * Gets the selected system entity
        *@return the selected system entity
        */
        virtual inline PSS_SystemEntity* GetSelectedSystemEntity() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectLogicalSystemDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectLogicalSystemDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedLogicalSystemTree(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_LOGICALSYSTEM_SELECTION
        };

        PSS_LogicalSystemEntity*  m_pMainLogicalSystemGroup;
        PSS_SystemEntity*         m_pSystemEntity;
        PSS_LogicalSystemTreeCtrl m_Ctrl;
        CString                   m_Title;
};

//---------------------------------------------------------------------------
// PSS_SelectLogicalSystemDlg
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_SelectLogicalSystemDlg::GetSelectedSystemEntity() const
{
    return m_pSystemEntity;
}
//---------------------------------------------------------------------------

#endif
