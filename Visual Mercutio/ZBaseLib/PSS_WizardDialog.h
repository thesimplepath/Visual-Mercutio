/****************************************************************************
 * ==> PSS_WizardDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic Wizard dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WizardDialogH
#define PSS_WizardDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Dialog.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
* Wizard dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WizardDialog : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindow - window title
        *@param titleWizard - wizard title
        *@param textWizard - text wizard
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        */
        PSS_WizardDialog(UINT           id          = 0,
                         UINT           bitmapID    = 0,
                         UINT           iconID      = 0,
                         const CString& titleWindow = _T(""),
                         const CString& titleWizard = _T(""),
                         const CString& textWizard  = _T(""),
                         BOOL           autoCenter  = TRUE,
                         BOOL           standalone  = FALSE,
                         CWnd*          pParent     = NULL);

        /**
        * Constructor
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindowID - window title resource identifier
        *@param titleWizardID - wizard title resource identifier
        *@param textWizardID - text wizard resource identifier
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        */
        PSS_WizardDialog(UINT  id,
                         UINT  bitmapID,
                         UINT  iconID,
                         UINT  titleWindowID,
                         UINT  titleWizardID,
                         UINT  textWizardID,
                         BOOL  autoCenter = TRUE,
                         BOOL  standalone = FALSE,
                         CWnd* pParent    = NULL);

        /**
        * Constructor
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindow - window title
        *@param titleWizard - wizard title
        *@param textWizard - text wizard
        *@param backCol - back color
        *@param staticCol - static color
        *@param editCol - edit color
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        */
        PSS_WizardDialog(UINT           id,
                         UINT           bitmapID,
                         UINT           iconID,
                         const CString& titleWindow,
                         const CString& titleWizard,
                         const CString& textWizard,
                         COLORREF       backCol,
                         COLORREF       staticCol,
                         COLORREF       editCol,
                         BOOL           autoCenter = TRUE,
                         BOOL           standalone = FALSE,
                         CWnd*          pParent    = NULL);

        /**
        * Constructor
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindowID - window title resource identifier
        *@param titleWizardID - wizard title resource identifier
        *@param textWizardID - text wizard resource identifier
        *@param backCol - back color
        *@param staticCol - static color
        *@param editCol - edit color
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        */
        PSS_WizardDialog(UINT     id,
                         UINT     bitmapID,
                         UINT     iconID,
                         UINT     titleWindowID,
                         UINT     titleWizardID,
                         UINT     textWizardID,
                         COLORREF backCol,
                         COLORREF staticCol,
                         COLORREF editCol,
                         BOOL     autoCenter = TRUE,
                         BOOL     standalone = FALSE,
                         CWnd*    pParent = NULL);

        /**
        * Creates the Wizard dialog box
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindow - window title
        *@param titleWizard - wizard title
        *@param textWizard - text wizard
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Create(UINT           id          = 0,
                    UINT           bitmapID    = 0,
                    UINT           iconID      = 0,
                    const CString& titleWindow = _T(""),
                    const CString& titleWizard = _T(""),
                    const CString& textWizard  = _T(""),
                    BOOL           autoCenter  = TRUE,
                    BOOL           standalone  = FALSE,
                    CWnd*          pParent     = NULL);

        /**
        * Creates the Wizard dialog box
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindowID - window title resource identifier
        *@param titleWizardID - wizard title resource identifier
        *@param textWizardID - text wizard resource identifier
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Create(UINT  id,
                    UINT  bitmapID,
                    UINT  iconID,
                    UINT  titleWindowID,
                    UINT  titleWizardID,
                    UINT  textWizardID,
                    BOOL  autoCenter = TRUE,
                    BOOL  standalone = FALSE,
                    CWnd* pParent    = NULL);

        /**
        * Creates the Wizard dialog box
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindow - window title
        *@param titleWizard - wizard title
        *@param textWizard - text wizard
        *@param backCol - back color
        *@param staticCol - static color
        *@param editCol - edit color
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Create(UINT           id,
                    UINT           bitmapID,
                    UINT           iconID,
                    const CString& titleWindow,
                    const CString& titleWizard,
                    const CString& textWizard,
                    COLORREF       backCol,
                    COLORREF       staticCol,
                    COLORREF       editCol,
                    BOOL           autoCenter = TRUE,
                    BOOL           standalone = FALSE,
                    CWnd*          pParent    = NULL);

        /**
        * Creates the Wizard dialog box
        *@param id - resource identifier
        *@param bitmapID - bitmap resource identifier
        *@param iconID - icon resource identifier
        *@param titleWindowID - window title resource identifier
        *@param titleWizardID - wizard title resource identifier
        *@param textWizardID - text wizard resource identifier
        *@param backCol - back color
        *@param staticCol - static color
        *@param editCol - edit color
        *@param autoCenter - if TRUE, the wizard will be auto-centered in parent
        *@param standalone - if TRUE, the wizard is a standalone wizard
        *@param pParent - parent window, can be NULL
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Create(UINT     id,
                    UINT     bitmapID,
                    UINT     iconID,
                    UINT     titleWindowID,
                    UINT     titleWizardID,
                    UINT     textWizardID,
                    COLORREF backCol,
                    COLORREF staticCol,
                    COLORREF editCol,
                    BOOL     autoCenter = TRUE,
                    BOOL     standalone = FALSE,
                    CWnd*    pParent    = NULL);

        /**
        * Sets the wizard window title
        *@param id - title resource identifier
        */
        virtual void SetWizardWindowTitle(UINT id);

        /**
        * Sets the wizard subject text
        *@param id - subject text resource identifier
        */
        virtual void SetWizardSubjectText(UINT id);

        /**
        * Sets the wizard body text
        *@param id - body text resource identifier
        */
        virtual void SetWizardBodyText(UINT id);

        /**
        * Sets the wizard window title
        *@param value - title
        */
        virtual inline void SetWizardWindowTitle(const CString& value);

        /**
        * Sets the wizard subject text
        *@param id - subject text
        */
        virtual inline void SetWizardSubjectText(const CString& value);

        /**
        * Sets the wizard body text
        *@param id - body text
        */
        virtual inline void SetWizardBodyText(const CString& value);

    protected:
        CBitmapButton m_BtnHelp;
        HINSTANCE     m_hInst;
        HICON         m_hIcon;
        CRect         m_DialogRect;
        CString       m_TitleWindow;
        CString       m_TitleWizard;
        CString       m_TextWizard;
        UINT          m_ID;
        UINT          m_BitmapID;
        UINT          m_IconID;
        BOOL          m_Standalone;

        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /**
        * Paints the wizard
        *@param dc - device context to paint to
        */
        virtual void Paint(CDC& dc);

        /// Generated message map functions
        //{{AFX_MSG(PSS_WizardDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnPaint();
        afx_msg void OnNext();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CFont m_TitleFont;
        CFont m_TextFont;

        /**
        * Creates the font
        */
        void CreateFont();
};

//---------------------------------------------------------------------------
// PSS_WizardDialog
//---------------------------------------------------------------------------
void PSS_WizardDialog::SetWizardWindowTitle(const CString& value)
{
    m_TitleWindow = value;
    SetWindowText(m_TitleWindow);
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::SetWizardSubjectText(const CString& value)
{
    m_TitleWizard = value;
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::SetWizardBodyText(const CString& value)
{
    m_TextWizard = value;
}
//---------------------------------------------------------------------------

#endif
