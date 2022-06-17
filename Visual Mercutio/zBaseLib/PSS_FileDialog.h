/****************************************************************************
 * ==> PSS_FileDialog ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file dialog                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileDialogH
#define PSS_FileDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "mfc.h"

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
* File dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileDialog : public CFileDialog
{
    public:
        /**
        * Constructor
        *@param title - dialog title
        *@param filters - file extension filters
        *@param filterCount - filter count
        *@param initialDir - initial dir
        *@param defExtension - default extension
        *@param openStyleBox - if TRUE, the style box will be opened
        */
        PSS_FileDialog(const CString& title        = _T(""),
                       const CString& filters      = _T(""),
                       int            filterCount  = 0,
                       const CString& initialDir   = _T(""),
                       const CString& defExtension = _T(""),
                       BOOL           openStyleBox = TRUE);

        /**
        * Constructor
        *@param titleID - dialog title resource identifier
        *@param filters - file extension filters
        *@param filterCount - filter count
        *@param initialDir - initial dir
        *@param defExtension - default extension
        *@param openStyleBox - if TRUE, the style box will be opened
        */
        PSS_FileDialog(UINT           titleID,
                       const CString& filters      = _T(""),
                       int            filterCount  = 0,
                       const CString& initialDir   = _T(""),
                       const CString& defExtension = _T(""),
                       BOOL           openStyleBox = TRUE);

        virtual ~PSS_FileDialog();

        /**
        * Show dialog in modal mode
        *@return modal result
        */
        virtual int DoModal();

        /**
        * Gets the directory
        *@return the directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Gets the selected file name
        *@return the selected file name
        */
        virtual inline const CString GetFileName() const;

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_FileDialog)
        #ifdef _WIN32
            virtual BOOL OnFileNameOK();
        #endif
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CString m_Title;
        CString m_FileName;
        CString m_InitialDir;
        CString m_PathName;
        CString m_Filters;
        int     m_FilterCount;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FileDialog(const PSS_FileDialog& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FileDialog& operator = (const PSS_FileDialog& other);
};

//---------------------------------------------------------------------------
// PSS_FileDialog
//---------------------------------------------------------------------------
CString PSS_FileDialog::GetDirectory() const
{
    return m_PathName;
}
//---------------------------------------------------------------------------
const CString PSS_FileDialog::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------

#endif
