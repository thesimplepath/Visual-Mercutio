/****************************************************************************
 * ==> PSS_PaletteBar ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a palette bar                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(__PALETTE_H)
#define __PALETTE_H

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifndef _WIN32
    // 16 bit only
    #include "toolbarx.h"
#endif

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
#define ID_PALMENU_PROP WM_USER         + 0x200
#define ID_PALMENU_HIDE ID_PALMENU_PROP + 1
//---------------------------------------------------------------------------

/**
* Palette bar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PaletteBar : public CToolBar
{
    public:
        PSS_PaletteBar();
        virtual ~PSS_PaletteBar();

        /**
        * Creates the component
        *@param pParent - parent window
        *@param x - x position, in pixels
        *@param y - y position, in pixels
        *@return TRUE on success, otherwise FALSE
        */
        #ifndef _WIN32
            virtual BOOL Create(CWnd* pParent, int x, int y);
        #endif

        /**
        * Gets the column count
        *@return the column count
        */
        virtual inline UINT GetColumnCount() const;

        /**
        * Sets the column count
        *@param columns - the column count
        */
        virtual void SetColumnCount(UINT columns);

        /**
        * Sets the sizes
        *@param sizeButton - the button size
        *@param sizeImage - the image size
        *@param columns - the column count
        */
        virtual void SetSizes(const SIZE& sizeButton, const SIZE& sizeImage, UINT columns = 1);

        /**
        * Sets the buttons
        *@param pIDArray - the identifier array
        *@param idCount - the identifier count
        *@param columns - the column count
        */
        virtual BOOL SetButtons(const UINT FAR* pIDArray, int idCount, UINT columns = 1);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        UINT m_Columns;

        #ifndef _WIN32
            CWnd*  m_pParent;
            CPoint m_Mouse;
            CPoint m_Last;
            UINT   m_CxRightBorder;
            BOOL   m_TrackMove;
        #endif

        /**
        * Gets the item rect
        *@param index - item index
        *@param pRect - item rect
        */
        #ifndef _WIN32
            virtual void GetItemRect(int nIndex, LPRECT lpRect) const;
        #endif

        /**
        * Performs a hit test
        *@param point - point to test in pixels, in the client coordinates
        *@return hit test result
        */
        #ifndef _WIN32
            virtual int HitTest(const CPoint& point);
        #endif

        /**
        * Paints the content
        *@param pDC - device context to paint to
        */
        #ifndef _WIN32
            virtual void DoPaint(CDC* pDC);
        #endif

        /**
        * Inverts the tracker
        *@param point - point
        */
        #ifndef _WIN32
            void InvertTracker(const CPoint& point);
        #endif

        /**
        * Recalculates the layout
        *@param buttonCount - button count
        */
        #ifndef _WIN32
            void RecalcLayout(UINT buttonCount);
        #endif

        /// Generated message map functions
        //{{AFX_MSG(PSS_PaletteBar)
        #ifndef _WIN32
            afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
            afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
            afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
            afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
            afx_msg void OnMouseMove(UINT nFlags, CPoint point);
            afx_msg LONG OnPropriety(UINT, LONG);
            afx_msg LONG OnHide(UINT, LONG);
        #endif
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        #ifndef _WIN32
            CMenu m_Menu;
        #endif
};

//---------------------------------------------------------------------------
// PSS_PaletteBar
//---------------------------------------------------------------------------
UINT PSS_PaletteBar::GetColumnCount() const
{
    return m_Columns;
}
//---------------------------------------------------------------------------

#endif
