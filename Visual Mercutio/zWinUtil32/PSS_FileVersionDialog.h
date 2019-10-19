/****************************************************************************
 * ==> PSS_FileVersionDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a file version dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileVersionDialogH
#define PSS_FileVersionDialogH

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
* File version dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileVersionDialog : public PSS_Dialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_FILEVERSION
        };

        CSpinButtonCtrl m_FileVersionSpin;
        long            m_FileVersion;

        /**
        * Constructor
        *@param fileVersion - file version
        *@param pParent - parent window, can be NULL
        */
        PSS_FileVersionDialog(long fileVersion = 0, CWnd* pParent = NULL);

        /**
        * Gets the file version
        *@return the file version
        */
        virtual inline long GetFileVersion() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FileVersionDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FileVersionDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnDeltaposFileversionSpin(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeFileVersion();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_FileVersionDialog
//---------------------------------------------------------------------------
long PSS_FileVersionDialog::GetFileVersion() const
{
    return m_FileVersion;
}
//---------------------------------------------------------------------------

#endif
