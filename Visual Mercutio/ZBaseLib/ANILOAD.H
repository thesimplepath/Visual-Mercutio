/****************************************************************************
 * ==> PSS_StatusBar -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a status bar                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StatusBarH
#define PSS_StatusBarH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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

/**
* Status bar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StatusBar : public SECStatusBar
{
    DECLARE_DYNCREATE(PSS_StatusBar)

    public:
        PSS_StatusBar();
        virtual ~PSS_StatusBar();

        /**
        * Pre-creates the window
        *@param cs - create structure
        */
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

        /**
        * Sets the current percentage
        *@param value - percentage value
        */
        virtual void SetCurrentPercentage(int value);

        /**
        * Begins the animated percentage
        */
        virtual void BeginAniPercentage();

        /**
        * Ends the animated percentage
        */
        virtual void EndAniPercentage();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_StatusBar)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        static HBITMAP m_hBtmBack;
        static HBITMAP m_hBtmGreenLight;
        static HBITMAP m_hBtmRedLight;
        CFont          m_Font;
        CBrush         m_LtBlueBrush;
        CPen           m_BlackPen;
        CPen           m_WhitePen;
        CRect          m_ItemRect;
        DWORD          m_TickCount;
        int            m_Percent;
        int            m_Image;
        int            m_BackWidth;
        int            m_LeftStart;
        int            m_Step;
        BOOL           m_SwapLight;
        BOOL           m_IsStarted;
};

#endif
