/****************************************************************************
 * ==> PSS_VisualTool ------------------------------------------------------*
 ****************************************************************************
 * Description : Visual tools base class. These tools can be selected,      *
 *               edited, add a new rectangle, line, text, etc...            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_VisualToolH
#define PSS_VisualToolH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZIView.h"

#ifndef _WIN32
    #include "ToolBarx.h"
#endif

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic visual tool
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_VisualTool
{
    public:
        /**
        * Tooltypes
        */
        enum IEToolType
        {
            IE_TT_VToolSelect,
            IE_TT_VToolEdit,
            IE_TT_VToolLine,
            IE_TT_VToolRect,
            IE_TT_VToolRoundRect,
            IE_TT_VToolBoundEdit,
            IE_TT_VToolDate,
            IE_TT_VToolNumber,
            IE_TT_VToolSquareText,
            IE_TT_VToolCheckBox,
            IE_TT_VToolRadioButton,
            IE_TT_VToolStaticText,
            IE_TT_VToolText,
            IE_TT_VToolCircle,
            IE_TT_VToolBitmap,
            IE_TT_VToolNumbered,
            IE_TT_VToolDesignEdit,
            IE_TT_VToolDesignEditFieldName,
            IE_TT_VToolMaskText,
            IE_TT_VToolTabOrder,
            IE_TT_VToolMultiColumn,
        };

        /**
        * Visual tool modes
        */
        enum IEVisualToolModes
        {
            IE_TM_Normal,
            IE_TM_NoCreate,
        };

        static IEToolType        m_CurrentToolType;
        static IEVisualToolModes m_ToolMode;
        static CRect             m_Rect;
        static CPoint            m_DownPoint;
        static CPoint            m_LastPoint;

        /**
        * Constructor
        *@param objectToolType - object tool type
        */
        PSS_VisualTool(IEToolType objectToolType);

        virtual ~PSS_VisualTool();

        /**
        * Called when the left button is down
        *@param pView - view
        *@param flags - mouse flags
        *@param point - clicked point in pixels
        */
        virtual void OnLButtonDown(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the left button is double clicked
        *@param pView - view
        *@param flags - mouse flags
        *@param point - clicked point in pixels
        */
        virtual void OnLButtonDblClk(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the left button is up
        *@param pView - view
        *@param flags - mouse flags
        *@param point - mouse position in pixels
        */
        virtual void OnLButtonUp(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the mouse moves
        *@param pView - view
        *@param flags - mouse flags
        *@param point - mouse position in pixels
        */
        virtual void OnMouseMove(ZIView* pView, UINT nFlags, const CPoint& point);

        /**
        * Called when the current action is canceled
        */
        virtual void OnCancel();

        /**
        * Searches the object matching with the object tool type
        *@param objectToolType - object tool type
        *@return the matching object tool type, NULL if not found or on error
        */
        static PSS_VisualTool* FindTool(IEToolType objectToolType);

        /**
        * Gets the tool type
        *@return the tool type
        */
        virtual inline IEToolType GetObjectToolType() const;

    protected:
        HCURSOR m_hCurNormal;

    private:
        static CPtrList m_ToolsList;
        static UINT     m_DownFlags;
        IEToolType      m_ObjectToolType;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_VisualTool(const PSS_VisualTool& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_VisualTool& operator = (const PSS_VisualTool& other);
};

//---------------------------------------------------------------------------
// PSS_VisualTool
//---------------------------------------------------------------------------
PSS_VisualTool::IEToolType PSS_VisualTool::GetObjectToolType() const
{
    return m_ObjectToolType;
}
//---------------------------------------------------------------------------

/**
* Editable object visual tools
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_VisualToolEdit : public PSS_VisualTool
{
    public:
        typedef PSS_VisualTool inherited;

        PSS_VisualToolEdit();
        virtual ~PSS_VisualToolEdit();

        /**
        * Called when the left button is down
        *@param pView - view
        *@param flags - mouse flags
        *@param point - clicked point in pixels
        */
        virtual void OnLButtonDown(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the left button is up
        *@param pView - view
        *@param flags - mouse flags
        *@param point - clicked point in pixels
        */
        virtual void OnLButtonUp(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the mouse moves
        *@param pView - view
        *@param flags - mouse flags
        *@param point - mouse position in pixels
        */
        virtual void OnMouseMove(ZIView* pView, UINT flags, const CPoint& point);

    private:
        HCURSOR m_hCurEdit;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_VisualToolEdit(const PSS_VisualToolEdit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_VisualToolEdit& operator = (const PSS_VisualToolEdit& other);
};

/**
* Object creator visual tools
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_VisualToolObjectCreator : public PSS_VisualTool
{
    public:
        typedef PSS_VisualTool inherited;

        /**
        * Constructor
        *@param objectToolType - object tool type
        */
        PSS_VisualToolObjectCreator(IEToolType objectToolType);

        virtual ~PSS_VisualToolObjectCreator();

        /**
        * Called when the left button is down
        *@param pView - view
        *@param flags - mouse flags
        *@param point - clicked point in pixels
        */
        virtual void OnLButtonDown(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the left button is up
        *@param pView - view
        *@param flags - mouse flags
        *@param point - clicked point in pixels
        */
        virtual void OnLButtonUp(ZIView* pView, UINT flags, const CPoint& point);

        /**
        * Called when the mouse moves
        *@param pView - view
        *@param flags - mouse flags
        *@param point - mouse position in pixels
        */
        virtual void OnMouseMove(ZIView* pView, UINT flags, const CPoint& point);

    protected:
        HCURSOR m_hCurCreation;
        BOOL    m_CreationStarted;

        /**
        * Creates an object
        *@param rect - rect
        *@note This function is called when the left mouse button is up, after using this tool
        */
        virtual void CreateObject(CRect& rect) = 0;

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_VisualToolObjectCreator(const PSS_VisualToolObjectCreator& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_VisualToolObjectCreator& operator = (const PSS_VisualToolObjectCreator& other);
};

#endif
