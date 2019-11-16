/****************************************************************************
 * ==> PSS_MsgBox ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a message box                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MsgBoxH
#define PSS_MsgBoxH

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

extern AFX_EXTENSION_MODULE g_zBaseLibDLL;

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_AnimIconNb  7
#define M_AnimIcon2Nb 9
//---------------------------------------------------------------------------

/**
* Message box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MsgBox : public CDialog
{
    DECLARE_DYNCREATE(PSS_MsgBox)

    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DIALOG_FORSAVE
        };

        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_MsgBox(CWnd* pParent = NULL);

        virtual ~PSS_MsgBox();

        /**
        * Shows the message box
        *@param message - message
        *@param style - style
        *@return dialog modal result
        */
        virtual int Show(LPCSTR pMessage, UINT style = MB_YESNOCANCEL);

        /**
        * Shows the message box
        *@param messageID - message identifier
        *@param style - style
        *@param hInstance - instance
        *@return dialog modal result
        */
        virtual int Show(UINT messageID, UINT style = MB_YESNOCANCEL, HINSTANCE hInstance = NULL);

        /**
        * Switches the 3rd button label between cancel or unlock
        *@param value - if TRUE, the 3rd button text will show unlock instead of cancel
        */
        virtual void DoChangeCancelBtnToUnlockBtn(BOOL Value = TRUE);

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_MsgBox)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        virtual BOOL OnInitDialog();
        afx_msg void OnTimer(UINT nIDEvent);
        afx_msg void OnPaint();
        afx_msg void OnYes();
        afx_msg void OnNo();
        afx_msg void OnCancelBtn();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CStatic m_Icon;
        HICON   m_pAnimIcons [M_AnimIconNb];
        HICON   m_pAnimIcons2[M_AnimIcon2Nb];
        CString m_Text;
        UINT    m_TimerID;
        UINT    m_Style;
        int     m_IconIndex;
        BOOL    m_DoShowUnlockButton;

        /**
        * Releases the dialog resources
        */
        void ReleaseDialog();

        /**
        * Adjusts the dialog size
        */
        void AdjustSize();
};

#endif
