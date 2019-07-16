/****************************************************************************
 * ==> PSS_CodeInputDialog -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an code input dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CodeInputDialogH
#define PSS_CodeInputDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZSCTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Code input dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CodeInputDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param pParent - parent window
        */
        PSS_CodeInputDialog(CWnd* pParent = NULL);

        /**
        * Gets the entered code
        *@return the entered code
        */
        virtual inline CString GetCode() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_CodeInputDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CString m_Code;
        int     m_Counter;
};

//---------------------------------------------------------------------------
// PSS_CodeInputDialog
//---------------------------------------------------------------------------
CString PSS_CodeInputDialog::GetCode() const
{
    return m_Code;
}
//---------------------------------------------------------------------------

#endif
