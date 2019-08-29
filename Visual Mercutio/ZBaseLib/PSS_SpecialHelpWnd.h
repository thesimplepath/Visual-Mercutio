/****************************************************************************
 * ==> PSS_SpecialHelpWnd --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a special help window                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SpecialHelpWndH
#define PSS_SpecialHelpWndH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZAObject.h"

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
* Special help window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SpecialHelpWnd : public CWnd
{
    public:
        PSS_SpecialHelpWnd();
        virtual ~PSS_SpecialHelpWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd*          pParentWnd,
                            CRect*         pRect,
                            PlanFinObject* pObj,
                            BOOL           autoCalculateOption = FALSE) = 0;

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param bitmapRes - bitmap resource identifier
        *@param numberOfButton - number of butons
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateSpecialHelp(CWnd*          pParentWnd,
                                       CRect*         pRect,
                                       PlanFinObject* pObj,
                                       UINT           bitmapRes,
                                       std::size_t    numberOfButton,
                                       BOOL           autoCalculateOption = FALSE);

        /**
        * Destroys the window
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DestroyWindow();

        /**
        * Sets the Wizard cursor
        */
        virtual inline void SetWizardCursor();

        /**
        * Sets the empty cursor
        */
        virtual inline void SetEmptyCursor();

        /**
        * Sets the property cursor
        */
        virtual inline void SetPropertyCursor();

        /**
        * Sets the scenario cursor
        */
        virtual inline void SetScenarioCursor();

        /**
        * Sets the number cursor
        */
        virtual inline void SetNumberCursor();

        /**
        * Sets the calendar cursor
        */
        virtual inline void SetCalendarCursor();

        /**
        * Sets the note cursor
        */
        virtual inline void SetNoteCursor();

        /**
        * Gets the financial plan object
        *@return the financial plan object
        */
        virtual inline PlanFinObject* GetObject() const;

        /**
        * Gets the number of buttons
        *@return the number of buttons
        */
        virtual inline std::size_t GetNumberOfButton() const;

        /**
        * Gets the button position
        *@param point - hit point in pixels
        *@return the button position
        */
        virtual inline int GetButtonPosition(const CPoint& point) const;

    protected:
        #ifdef _WIN32
            CMonthCalCtrl* m_pMonthCal;
        #endif

        /**
        * Called when object property is required
        *@param point - hit point in pixels
        */
        virtual void OnObjectProperty(const CPoint& point);

        /**
        * Called when association menu is required
        *@param point - hit point in pixels
        */
        virtual void OnAssociationMenu(const CPoint& point);

        /**
        * Called when Wizard is required
        *@param point - hit point in pixels
        */
        virtual void OnWizard(const CPoint& point);

        /**
        * Called when calendar is required
        *@param point - hit point in pixels
        */
        virtual void OnCalendar(const CPoint& point);

        /**
        * Called when empty field is required
        *@param point - hit point in pixels
        */
        virtual void OnEmpty(const CPoint& point);

        /**
        * Called when note is required
        *@param point - hit point in pixels
        */
        virtual void OnNote(const CPoint& point);

        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point) = 0;

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point) = 0;

        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpWnd)
        afx_msg void OnPaint();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        static CString near m_ClassName;
        PlanFinObject*      m_pObj;
        HCURSOR             m_hCurWizard;
        HCURSOR             m_hCurEmpty;
        HCURSOR             m_hCurProperty;
        HCURSOR             m_hCurScenario;
        HCURSOR             m_hCurNumber;
        HCURSOR             m_hCurCalendar;
        HCURSOR             m_hCurNote;
        CSize               m_BitmapSize;
        UINT                m_BitmapRes;
        std::size_t         m_NumberOfButton;
        BOOL                m_AutoCalculateOption;
};

//---------------------------------------------------------------------------
// PSS_SpecialHelpWnd
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetWizardCursor()
{
    SetCursor(m_hCurWizard);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetEmptyCursor()
{
    SetCursor(m_hCurEmpty);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetPropertyCursor()
{
    SetCursor(m_hCurProperty);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetScenarioCursor()
{
    SetCursor(m_hCurScenario);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetNumberCursor()
{
    SetCursor(m_hCurNumber);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetCalendarCursor()
{
    SetCursor(m_hCurCalendar);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::SetNoteCursor()
{
    SetCursor(m_hCurNote);
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_SpecialHelpWnd::GetObject() const
{
    return m_pObj;
}
//---------------------------------------------------------------------------
std::size_t PSS_SpecialHelpWnd::GetNumberOfButton() const
{
    return m_NumberOfButton;
}
//---------------------------------------------------------------------------
int PSS_SpecialHelpWnd::GetButtonPosition(const CPoint& point) const
{
    return point.x / (m_BitmapSize.cx / GetNumberOfButton());
}
//---------------------------------------------------------------------------

/**
* Special help window for numbers
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpNumberWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpNumberWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpNumberWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help designer window for numbers
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpNumberDesignerWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpNumberDesignerWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpNumberDesignerWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help scenario window for numbers
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpNumberScenarioWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpNumberScenarioWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpNumberScenarioWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help scenario designer window for numbers
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpNumberScenarioDesignerWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpNumberScenarioDesignerWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpNumberScenarioDesignerWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help window for dates
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpDateWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpDateWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpDateWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help designer window for dates
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpDateDesignerWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpDateDesignerWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpDateDesignerWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help default window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpDefaultWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpDefaultWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpDefaultWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Special help default designer window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpecialHelpDefaultDesignerWnd : public PSS_SpecialHelpWnd
{
    public:
        PSS_SpecialHelpDefaultDesignerWnd();

        /**
        * Creates the special help window
        *@param pParentWnd - parent window
        *@param pRect - rect surrounding the window
        *@param pObj - financial plan object
        *@param autoCalculateOption - if TRUE, options will be auto-calculated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParentWnd, CRect* pRect, PlanFinObject* pObj, BOOL autoCalculateOption = FALSE);

    protected:
        /**
        * Called when left mouse button is down
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void LButtonDown(UINT flags, const CPoint& point);

        /**
        * Called when mouse moves above the window
        *@param flags - mouse flags
        *@param point - hit point in pixels
        */
        virtual void MouseMove(UINT flags, const CPoint& point);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SpecialHelpDefaultDesignerWnd)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
