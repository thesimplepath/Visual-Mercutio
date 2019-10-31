/****************************************************************************
 * ==> PSS_PointerWnd ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a pointer window                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PointerWndH
#define PSS_PointerWndH

// processsoft
#include "PSS_Messages.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifndef _WIN32
    // 16 bit only
    extern "C" extern void WINAPI InitZWinUtilDLL();
    extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
    #define AFX_EXT_CLASS
#else
    // 32 bit only
    extern AFX_EXTENSION_MODULE g_zWinUtil32DLL;
#endif

/**
* Pointer window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PointerWnd : public CWnd
{
    DECLARE_DYNAMIC(PSS_PointerWnd)

    public:
        PSS_PointerWnd();
        virtual ~PSS_PointerWnd();

        /**
        * Creates a pointer window
        *@param pWndMessage - window message
        *@param rect - window rectangle
        *@param pParent - parent window, can be NULL
        */
        virtual void Create(CWnd* pWndMessage, CRect& rect, CWnd* pParent);

        /**
        * Assigns the message window
        *@param pWndMessage - window message
        */
        virtual void AssignMessageWnd(CWnd* pWndMessage);
    
    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_PointerWnd)
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        HCURSOR m_hCurPointer;
        CWnd*   m_pWndMessage;
        UINT    m_ID;
        BOOL    m_StartPointer;
};

#endif
