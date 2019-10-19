/****************************************************************************
 * ==> PSS_SysVarDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system variables converter dialog box           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SysVarDialogH
#define PSS_SysVarDialogH

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
* System variables dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SysVarDialog : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_SysVarDialog(CWnd* pParent = NULL);

        /**
        * Gets the keyword
        *@return the keyword
        */
        virtual inline const CString GetKeyword() const;

    protected:
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SysVarDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_SysVarDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangeSystemVarlist();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_SYSTEMVAR
        };

        CListBox m_SysVarList;
        CString  m_Keyword;
};

//---------------------------------------------------------------------------
// PSS_SysVarDialog
//---------------------------------------------------------------------------
const CString PSS_SysVarDialog::GetKeyword() const
{
    return m_Keyword;
}
//---------------------------------------------------------------------------

#endif
