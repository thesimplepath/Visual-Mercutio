/****************************************************************************
 * ==> PSS_PublishModelGenerateDialog --------------------------------------*
 ****************************************************************************
 * Description : Dialog box showing the model publication progression       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelGenerateH
#define PSS_PublishModelGenerateH

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
#include "zBaseLib\ZWizard.h"

// resources
#include "zModelWebRes.h"

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dialog box showing the model publication progression
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishModelGenerateDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPUBMODEL_GENERATE
        };

        PSS_PublishModelGenerateDialog();

        /**
        * Creates the dialog
        *@param pParent - dialog parent, can be NULL
        *@return true on success, otherwise false
        */
        virtual bool Create(CWnd* pParent = NULL);

        /**
        * Sets the destination
        *@param destination - destination
        */
        virtual void SetDestination(const CString& destination);

        /**
        * Checks if cancel was requested
        *@return true if cancel was requested, otherwise false
        */
        virtual inline bool CancelRequested() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishModelGenerate)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

    private:
        bool         m_CancelRequested;
        CAnimateCtrl m_FileMoveAnimation;
        CString      m_Destination;

        /// generated message map functions
        //{{AFX_MSG(PSS_PublishModelGenerate)
        virtual BOOL OnInitDialog();
        virtual void OnCancel();
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT ctlColor);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_PublishModelGenerate
//---------------------------------------------------------------------------
bool PSS_PublishModelGenerateDialog::CancelRequested() const
{
    return m_CancelRequested;
};
//---------------------------------------------------------------------------

#endif
