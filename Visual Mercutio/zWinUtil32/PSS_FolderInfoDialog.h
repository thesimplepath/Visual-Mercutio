/****************************************************************************
 * ==> PSS_FolderInfoDialog ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a folder info dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FolderInfoDialogH
#define PSS_FolderInfoDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIDialog.h"
#include "zBaseLib\FldStamp.h"
#include "PSS_FolderInfoCtrl.h"

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
* Folder info dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FolderInfoDialog : public ZIDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_FOLDER_INFORMATION
        };

        CString m_FolderName;
        CString m_FolderDescription;

        #ifdef _WIN32
            PSS_FolderInfoCtrl m_ListInformation;
        #endif

        /**
        * Constructor
        *@param pFolderStamp - folder stamp, can be NULL
        *@param readOnly - if TRUE, folder is read-only
        *@param pPArent - parent window, can be NULL
        */
        PSS_FolderInfoDialog(ZDFolderStamp* pFolderStamp = NULL, BOOL readOnly = FALSE, CWnd* pParent = NULL);

        /**
        * Gets the folder name
        @return the folder name
        */
        virtual inline CString GetFolderName() const;

        /**
        * Gets the folder description
        @return the folder description
        */
        virtual inline CString GetFolderDescription() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_FolderInfoDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    
    private:
        ZDFolderStamp* m_pFolderStamp;
        BOOL           m_ReadOnly;
};

//---------------------------------------------------------------------------
// PSS_FolderInfoDialog
//---------------------------------------------------------------------------
CString PSS_FolderInfoDialog::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
CString PSS_FolderInfoDialog::GetFolderDescription() const
{
    return m_FolderDescription;
}
//---------------------------------------------------------------------------

#endif
