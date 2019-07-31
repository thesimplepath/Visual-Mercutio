/****************************************************************************
 * ==> PSS_ObjectNotesDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an object notes dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObjectNotesDialogH
#define PSS_ObjectNotesDialogH

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
#include "zBaseLib\ZIDialog.h"

// resources
#include "zWinUtil32Res.h"

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
* Object notes dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ObjectNotesDialog : public ZIDialog
{
    public:
        /**
        * Constructor
        *@param comment - comment
        *@param userName - user name
        *@param pParent - parent form, can be NULL
        */
        PSS_ObjectNotesDialog(const CString& comment  = "",
                              const CString& userName = "",
                              CWnd*          pParent  = NULL);

        /**
        * Gets the comment
        *@return the comment
        */
        virtual inline const CString GetComment() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ObjectNotesDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ObjectNotesDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnChangeNotesEdit();
        afx_msg void OnDeleteNotes();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_OBJECTNOTES
        };

        CString m_UserName;
        CString m_Comment;
        CString m_SaveText;
        BOOL    m_TextChanged;
};

//---------------------------------------------------------------------------
// PSS_ObjectNotesDialog
//---------------------------------------------------------------------------
const CString PSS_ObjectNotesDialog::GetComment() const
{
    return m_Comment;
}
//---------------------------------------------------------------------------

#endif
