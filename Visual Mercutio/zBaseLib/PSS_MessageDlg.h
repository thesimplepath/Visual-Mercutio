/****************************************************************************
 * ==> PSS_MessageDlg ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a message dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/
 
#ifndef PSS_MessageDlgH
#define PSS_MessageDlgH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_FlatButton.h"
#include "PSS_Dialog.h"

extern AFX_EXTENSION_MODULE g_zBaseLibDLL;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define ID_TIMERMESSAGE      16
#define M_Message_Icon_Count 16
//---------------------------------------------------------------------------

/**
* Message dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MessageDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pWnd - parent window, can be NULL
        */
        PSS_MessageDlg(CWnd* pWnd = NULL);

        virtual ~PSS_MessageDlg();

        /**
        * Shows the message
        *@param textID - text to show
        *@param titleID - title to show
        *@param bitmapID - bitmap identifier to show in resources
        */
        void ShowMessage(const CString& text, const CString& title = "", UINT bitmapID = 0);

        /**
        * Shows the message
        *@param textID - text identifier to show in resources
        *@param titleID - title identifier to show in resources
        *@param bitmapID - bitmap identifier to show in resources
        */
        void ShowMessage(UINT IDText, UINT IDTitle = 0, UINT IDBitmap = 0);

    protected:
        /**
        * DDX/DDV support
        *@param pDX- DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_MessageDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnTimer(UINT nIDEvent);
        afx_msg void OnPaint();
        afx_msg void OnCloseWindow();
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_MESSAGEDLG
        };

        HINSTANCE      m_hInst;
        PSS_FlatButton m_CloseButton;
        CStatic        m_AppIcon;
        HCURSOR        m_Cursor;
        CFont          m_TitleFont;
        CFont          m_TextFont;
        CString        m_Title;
        CString        m_Text;
        int            m_Icon;
        UINT           m_BitmapID;
        UINT           m_TimerID;
        HICON          m_pIcon[M_Message_Icon_Count];

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MessageDlg(const PSS_MessageDlg& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_MessageDlg& operator=(const PSS_MessageDlg& other);

        /**
        * Closes the window
        */
        void CloseWindow();
};

#endif
