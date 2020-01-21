/****************************************************************************
 * ==> PSS_SelectPrestationDlg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestation selection dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectPrestationDlgH
#define PSS_SelectPrestationDlgH

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
#include "PSS_PrestationsTreeCtrl.h"

// resources
#include "zModelRes.h"

// old class name mapping
#ifndef PSS_PrestationsEntity
    #define PSS_PrestationsEntity ZBPrestationsEntity
#endif
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// forward class declaration
class PSS_PrestationsEntity;
class PSS_LogicalPrestationsEntity;

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
* Prestation selection dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectPrestationDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param title - the title
        *@param pMainPrestation - the main prestation
        *@param allowPrestationSelection - if true, the prestation selection is allowed
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectPrestationDlg(const CString&                title                    = _T(""),
                                PSS_LogicalPrestationsEntity* pMainPrestation          = NULL,
                                bool                          allowPrestationSelection = true,
                                CWnd*                         pParent                  = NULL);

        /**
        * Constructor
        *@param titleID - the title identifier from resources
        *@param pMainPrestation - the main prestation
        *@param allowPrestationSelection - if true, the prestation selection is allowed
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectPrestationDlg(UINT                          titleID,
                                PSS_LogicalPrestationsEntity* pMainPrestation,
                                bool                          allowPrestationSelection = true,
                                CWnd*                         pParent                  = NULL);

        virtual ~PSS_SelectPrestationDlg();

        /**
        * Release the dialog box content
        */
        virtual void Release();

        /**
        * Gets the selected prestation entity
        *@return the selected prestation entity
        */
        virtual inline PSS_PrestationsEntity* GetSelectedPrestationEntity() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectPrestationDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectPrestationDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedPrestationsTree(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_PRESTATION_SELECTION
        };

        PSS_PrestationsEntity*        m_pPrestationEntity;
        PSS_LogicalPrestationsEntity* m_pMainPrestation;
        PSS_PrestationsTreeCtrl       m_Ctrl;
        CString                       m_Title;
        bool                          m_AllowPrestationSelection;
};

//---------------------------------------------------------------------------
// PSS_SelectPrestationDlg
//---------------------------------------------------------------------------
PSS_PrestationsEntity* PSS_SelectPrestationDlg::GetSelectedPrestationEntity() const
{
    return m_pPrestationEntity;
};
//---------------------------------------------------------------------------

#endif
