/****************************************************************************
 * ==> PSS_AnimateDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an animate dialog                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AnimateDialogH
#define PSS_AnimateDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifndef _WIN32
    // 16 bit only
    extern "C" extern void WINAPI InitZWinUtilDLL();
    extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
    #define    AFX_EXT_CLASS
#else
    // 32 bit only
    extern AFX_EXTENSION_MODULE g_zWinUtil32DLL;
#endif

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
* Animate dialog
*@author Dominique Aigroz, Jean-Milost Reymond
¨*/
class AFX_EXT_CLASS PSS_AnimateDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_AnimateDialog(CWnd* pParent = NULL);

        /**
        * Shows next animation
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ShowNext();

        /**
        * Closes the animation
        */
        virtual void CloseAnimation();

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(ZIAnimateDlg)
        virtual BOOL OnInitDialog();
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        virtual void OnCancel();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CRect m_ImageRect;
        UINT  m_ID;
        BOOL  m_Stop;
};

#endif
