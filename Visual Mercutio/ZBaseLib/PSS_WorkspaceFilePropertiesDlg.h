/****************************************************************************
 * ==> PSS_WorkspaceFilePropertiesDlg --------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace file properties dialog box            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceFilePropertiesDlgH
#define PSS_WorkspaceFilePropertiesDlgH

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

// resources
#include "zBaseLibRes.h"

// forward class declaration
class ZBWorkspaceGroupEntity;

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
* Workspace file properties dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WorkspaceFilePropertiesDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pRootGroup - root group, can be NULL
        *@param title - title
        *@param completeFileName - complete file name
        *@param pParent - parent window, can be NULL
        */
        PSS_WorkspaceFilePropertiesDlg(ZBWorkspaceGroupEntity* pRootGroup       = NULL,
                                       const CString&          title            = "",
                                       const CString&          completeFileName = "",
                                       CWnd*                   pParent          = NULL);

        /**
        * Gets the file title
        *@return the file title
        */
        virtual inline CString GetFileTitle() const;
    
        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;
 
    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WorkspaceFilePropertiesDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceFilePropertiesDlg)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WKS_FILEPROP
        };

        CString m_FileTitle;
        CString m_FileName;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceFilePropertiesDlg
//---------------------------------------------------------------------------
CString PSS_WorkspaceFilePropertiesDlg::GetFileTitle() const
{
    return m_FileTitle;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceFilePropertiesDlg::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------

#endif
