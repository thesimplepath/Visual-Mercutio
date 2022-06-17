/****************************************************************************
 * ==> PSS_PrestationsInfoDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an prestations info dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PrestationsInfoDlgH
#define PSS_PrestationsInfoDlgH

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
#include "zBaseLib/PSS_FilteredDialogBox.h"

// resources
#include "zModelRes.h"

// old class name mapping
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// forward class declaration
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
* Prestations info dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PrestationsInfoDlg : public PSS_FilteredDialogBox
{
    public:
        /**
        * Constructor
        *@param titleID - the title identifier
        *@param pLogicalPrestation - the logical prestations
        *@param name - the name
        *@param description - the description
        *@param modifyMode - if true, the modify mode will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_PrestationsInfoDlg(UINT                          titleID            = -1,
                               PSS_LogicalPrestationsEntity* pLogicalPrestation = NULL,
                               const CString&                name               = _T(""),
                               const CString&                description        = _T(""),
                               bool                          modifyMode         = false,
                               CWnd*                         pParent            = NULL);

        virtual ~PSS_PrestationsInfoDlg();

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PrestationsInfoDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PrestationsInfoDlg)
        afx_msg virtual BOOL OnInitDialog();
        afx_msg virtual void OnEnKillfocusPrestationName();
        afx_msg virtual void OnEnSetfocusPrestationName();
        afx_msg virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_PRESTATIONS_INFO
        };

        PSS_LogicalPrestationsEntity* m_pPrestation;
        CString                       m_Title;
        CString                       m_Name;
        CString                       m_Description;
        bool                          m_ModifyMode;
};

//---------------------------------------------------------------------------
// PSS_PrestationsInfoDlg
//---------------------------------------------------------------------------
CString PSS_PrestationsInfoDlg::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
CString PSS_PrestationsInfoDlg::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------

#endif
