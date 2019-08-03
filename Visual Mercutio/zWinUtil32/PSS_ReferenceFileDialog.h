/****************************************************************************
 * ==> PSS_ReferenceFileDialog ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a reference file dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_ZVREFERENCEFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVREFERENCEFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

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
#include "PSS_SearchEdit.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Reference file dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ReferenceFileDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param reference - reference
        *@param insertionType - insertion type
        *@param activationType - activation type
        *@param pPArent - parent window, can be NULL
        */
        PSS_ReferenceFileDialog(const CString& reference      = _T(""),
                                int            insertionType  = 0,
                                int            activationType = 0,
                                CWnd*          pParent        = NULL);

        /**
        * Gets the reference
        *@return the reference
        */
        virtual inline CString GetReference() const;

        /**
        * Gets the insertion type
        *@return the insertion type
        */
        virtual inline int GetInsertionType() const;

        /**
        * Gets the activation type
        *@return the activation type
        */
        virtual inline int GetActivationType() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ReferenceFileDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_ReferenceFileDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnAddfile();
        afx_msg void OnAddurl();
        afx_msg void OnScriptor();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_REFERENCE_FILE
        };

        CComboBox m_ActivationTypeCtrl;
        CComboBox m_InsertionTypeCtrl;
        CString   m_Reference;
        int       m_InsertionType;
        int       m_ActivationType;

        /**
        * Saves the values to the object
        */
        void SaveValuesToObject();

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_ReferenceFileDialog
//---------------------------------------------------------------------------
CString PSS_ReferenceFileDialog::GetReference() const
{
    return m_Reference;
}
//---------------------------------------------------------------------------
int PSS_ReferenceFileDialog::GetInsertionType() const
{
    return m_InsertionType;
}
//---------------------------------------------------------------------------
int PSS_ReferenceFileDialog::GetActivationType() const
{
    return m_ActivationType;
}
//---------------------------------------------------------------------------

#endif
