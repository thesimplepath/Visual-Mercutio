/****************************************************************************
 * ==> PSS_FilteredDialogBox -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog box which provides input filters         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FilteredDialogBoxH
#define PSS_FilteredDialogBoxH

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
* Dialog box which provides input filters
*@author Jean-Milost Reymond
*/
 class AFX_EXT_CLASS PSS_FilteredDialogBox : public CDialog
{
    public:
        /**
        * Constructor
        *@param IDD - dialog resource identifier
        *@param pParent - parent owning this dialog
        */
        PSS_FilteredDialogBox(UINT IDD, CWnd* pParent = NULL);

        virtual ~PSS_FilteredDialogBox();

        /**
        * Enables or disables the char filtering
        *@param value - if true, the char filtering will be enabled
        */
        void EnableCharFilter(bool value = true);

        /**
        * Pre-translates the Windows messages
        *@param pMsg - message
        */
        BOOL PreTranslateMessage(MSG* pMsg);

    protected:
        // Generated message map functions
        //{{AFX_MSG(ZAFilteredDialogBox)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        bool m_FilterChars;
};

#endif
