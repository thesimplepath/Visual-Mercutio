/****************************************************************************
 * ==> PSS_PlanFinObject ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan object                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PlanFinObjectH
#define PSS_PlanFinObjectH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PlanFinObject
    #define PSS_PlanFinObject PlanFinObject
#endif

// std
#include <Float.h>
#include <Math.h>

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif
#ifndef PSS_FieldColumn
    #define PSS_FieldColumn ZBFieldColumn
#endif

class ZIView;
class PSS_Document;
class PSS_FieldColumn;

// processsoft
#include "PSS_MathParser.h"
#include "PSS_Notes.h"
#include "PSS_Rect.h"
#include "PSS_Style.h"
#include "PSS_Font.h"
#include "PSS_Border.h"

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
// Global variables
//---------------------------------------------------------------------------
const UINT        g_PropertyGeneralPage          = 0x00000001;
const UINT        g_PropertySizePage             = 0x00000002;
const UINT        g_PropertyCheckBoxPage         = 0x00000004;
const UINT        g_PropertyRadioPage            = 0x00000008;
const UINT        g_PropertyNumberedPage         = 0x00000010;
const UINT        g_PropertyGeneralTextPage      = 0x00000020;
const UINT        g_PropertySquarePage           = 0x00000040;
const UINT        g_PropertyBoundTextPage        = 0x00000080;
const UINT        g_PropertyLongPage             = 0x00000100;
const UINT        g_PropertyGraphicPage          = 0x00000200;
const UINT        g_PropertyRectPage             = 0x00000400;
const UINT        g_PropertyGeneralBasicPage     = 0x00000800;
const UINT        g_PropertyGeneralDatePage      = 0x00001000;
const UINT        g_PropertyGeneralBoundTextPage = 0x00002000;
const UINT        g_PropertyGeneralStaticPage    = 0x00004000;
const UINT        g_PropertyMaskTextPage         = 0x00008000;
const UINT        g_PropertyMultiColumnPage      = 0x00010000;
const std::size_t g_PropertyTabGeneral           = 0;
const std::size_t g_PropertyTabSize              = 1;
const std::size_t g_PropertyTabCheckBox          = 2;
const std::size_t g_PropertyTabRadio             = 2;
const std::size_t g_PropertyTabNumbered          = 2;
const std::size_t g_PropertyTabSquare            = 2;
const std::size_t g_PropertyTabBoundText         = 2;
const std::size_t g_PropertyTabLong              = 2;
const std::size_t g_PropertyTabGraphic           = 2;
const std::size_t g_PropertyMaskText             = 2;
const std::size_t g_PropertyTabRect              = 3;
const std::size_t g_PropertyMultiColumn          = 3;
//---------------------------------------------------------------------------

/**
* Financial plan object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PlanFinObject : public PSS_FormulaObjectParser
{
    DECLARE_SERIAL(PSS_PlanFinObject)

    public:
        typedef PSS_FormulaObjectParser inherited;

        PSS_PlanFinObject();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PlanFinObject(const PSS_PlanFinObject& other);

        virtual ~PSS_PlanFinObject();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PlanFinObject& operator = (const PSS_PlanFinObject& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PlanFinObject& operator = (const PSS_PlanFinObject* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PSS_PlanFinObject* pSrc);

        /**
        * Gets the object value
        *@return the object value
        */
        virtual double GetRealValue() const;

        /**
        * Gets if the field is static or not
        *@return TRUE if the field is static, otherwise FALSE
        */
        virtual const BOOL GetIsStatic() const;

        /**
        * Sets the field as static
        *@param value - if TRUE, the field is static
        */
        virtual void SetIsStatic(BOOL value);

        /**
        * Checks if the field is empty
        *@return TRUE if the field is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Empties the object
        */
        virtual inline void EmptyObject();

        /**
        * Clears the empty object flag
        */
        virtual inline void ClearEmptyObjectFlag();

        /**
        * Sets the object to selected state
        *@param pWnd - parent window
        *@param pDC - device context
        *@param state - if TRUE, the object is selected
        *@param erase - if TRUE, the object rectangle content will be erased
        */
        virtual void SelectObject(CWnd* pWnd, CDC* pDC, BOOL state, BOOL erase = TRUE);

        /**
        * Checks if the object is selected
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual inline BOOL IsObjectSelected() const;

        /**
        * Gets the object bounding rectangle
        *@return the object bounding rectangle
        */
        virtual inline CRect& GetClientRect();

        /**
        * Sets the client rect
        *@param rect - the client rect
        */
        virtual inline void SetClientRect(const CRect& rect);

        /**
        * Gets the object page
        *@return the object page
        */
        virtual inline int GetObjectPage() const;

        /**
        * Sets the object page
        *@param page - page
        */
        virtual inline void SetObjectPage(int page);

        /**
        * Gets the format type
        *@return the format type
        */
        virtual inline EFormatType GetFormatType() const;

        /**
        * Sets the format type
        *@param type - the format type
        */
        virtual inline void SetFormatType(EFormatType type);

        /**
        * Formats the object with a string
        *@param pStr - string
        */
        virtual void FormatObject(const char* pStr);

        /**
        * Formats the object with a time
        *@param pTime - time
        */
        virtual void FormatObject(CTime* pTime);

        /**
        * Formats the object with a date and time
        *@param pDateTime - date amd time
        */
        virtual void FormatObject(COleDateTime* pDateTime);

        /**
        * Formats the object with a value
        *@param value - value
        */
        virtual void FormatObject(DOUBLE value);

        /**
        * Recalculates the object
        *@param pDoc - document
        */
        virtual inline void Recalculate(PSS_Document* pDoc);

        /**
        * Gets the object value
        *@return the object value
        */
        virtual inline double GetValue() const;

        /**
        * Sets a value
        *@param value - value
        */
        virtual inline void SetValue(double value);

        /**
        * Gets a string containing the object formatted with the current attributes
        /*@return a string containing the object formatted with the current attributes
        */
        virtual CString GetFormattedObject();

        /**
        * Gets an unformatted string of the object image
        *@return an unformatted string of the object image
        */
        virtual CString GetUnformattedObject();

        /**
        * Converts a formatted object to numeric, date, string, etc.
        *@return TRUE if the value has changed, otherwise FALSE
        */
        virtual BOOL ConvertFormattedObject(const CString& value,
                                            BOOL           locateFormat  = TRUE,
                                            BOOL           emptyWhenZero = FALSE);

        /**
        * Gets the object memory adress
        *@return the object memory adress
        */
        virtual inline void* GetObjectAdress() const;

        /**
        * Gets the format choice array
        *@return the format choice array
        */
        virtual inline CStringArray& GetFormatChoice();

        /**
        * Sets an object choice by passing a string containing the object with a certain choice
        *@param value - value
        */
        virtual inline void SetFormatWithChoice(const CString& value);

        /**
        * Changes the object origin
        *@param point - the new origin point
        */
        virtual void SetOrigin(CPoint& point);

        /**
        * Sets a square on the rect top, used for resizing object functionnality
        *@param pRect - rect to fill
        */
        virtual inline void GetRectTop(CRect* pRect) const;

        /**
        * Sets a square on the rect bottom, used for resizing object functionnality
        *@param pRect - rect to fill
        */
        virtual inline void GetRectBottom(CRect* pRect) const;

        /**
        * Sets a square on the rect left, used for resizing object functionnality
        *@param pRect - rect to fill
        */
        virtual inline void GetRectLeft(CRect* pRect) const;

        /**
        * Sets a square on the rect right, used for resizing object functionnality
        *@param pRect - rect to fill
        */
        virtual inline void GetRectRight(CRect* pRect) const;

        /**
        * Checks if the point is on the top square for resizing the object
        *@param point - point
        *@return TRUE if the point is on the top square, otherwise FALSE
        */
        virtual inline BOOL IsRectTop(const CPoint& point) const;

        /**
        * Checks if the point is on the bottom square for resizing the object
        *@param point - point
        *@return TRUE if the point is on the bottom square, otherwise FALSE
        */
        virtual inline BOOL IsRectBottom(const CPoint& point) const;

        /**
        * Checks if the point is on the left square for resizing the object
        *@param point - point
        *@return TRUE if the point is on the left square, otherwise FALSE
        */
        virtual inline BOOL IsRectLeft(const CPoint& point) const;

        /**
        * Checks if the point is on the right square for resizing the object
        *@param point - point
        *@return TRUE if the point is on the right square, otherwise FALSE
        */
        virtual inline BOOL IsRectRight(const CPoint& point) const;

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

        /**
        * Draws an empty object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawEmpty(CDC* pDC, ZIView* pView);

        /**
        * Draws the hidden symbol for the object
        *@param pDC - device context to draw to
        */
        virtual void DrawHiddenSymbol(CDC* pDC);

        /**
        * Draws the hidden print symbol for the object
        *@param pDC - device context to draw to
        */
        virtual void DrawHiddenOnPrintSymbol(CDC* pDC);

        /**
        * Draws the calculated symbol for the object
        *@param pDC - device context to draw to
        */
        virtual void DrawCalculatedSymbol(CDC* pDC);

        /**
        * Draws the note symbol for the object
        *@param pDC - device context to draw to
        */
        virtual void DrawNoteSymbol(CDC* pDC);

        /**
        * Draws the object rectangle
        *@param pDC - device context to draw to
        */
        virtual void DrawObjectRectangle(CDC* pDC);

        /**
        * Draws the tab order number
        *@param pDC - device context to draw to
        */
        virtual void DrawTabOrder(CDC* pDC);

        /**
        * Draws the object bounded rect
        *@param pDC - device context to draw to
        */
        virtual void DrawBoundRect(CDC* pDC);

        /**
        * Fills the object background
        *@param pDC - device context
        *@param pView - view
        */
        virtual void DrawFillObject(CDC* pDC, ZIView* pView);

        /**
        * Checks if object is selected
        *@param point - hit point
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Checks if the point is contained in the object and can be edited
        *@param point - hit point
        *@return TRUE if the point is contained in the object and can be edited, otherwise FALSE
        */
        virtual inline BOOL IsHint(CPoint& point) const;

        /**
        * Gets the formatted buffer where the displayed operations have been made
        *@return the formatted buffer
        */
        virtual inline const char* GetFormattedBuffer() const;

        /**
        * Shows the field code name
        *@param pDC - device context
        *@param pView - view
        *@param show - if TRUE, the field code name should be shown
        *@param pWnd - parent window, can be NULL
        */
        virtual void DisplayCodeName(CDC* pDC, ZIView* pView, BOOL show = TRUE, CWnd* pWnd = NULL);

        /**
        * Invalidates the object area. When the next draw is started, the object's rectangle will be redrawn
        *@param pDC - device context
        *@param pWnd - parent window
        *@param pRect - rectangle to invalidate
        */
        virtual void InvalidateObjectRect(CDC* pDC, CWnd* pWnd, CRect* pRect = NULL);

        /**
        * Gets the document justification
        *@param pDoc - document
        *@return the document justification
        */
        virtual inline UINT GetJustify(PSS_Document* pDoc) const;

        /**
        * Sets the document justification
        *@param value - the document justification
        */
        virtual inline void SetJustify(UINT value);

        /**
        * Shows the object with a specific color and shade
        *@param pDC - device context
        *@param pView - view
        */
        virtual void ShowColorForNumber(CDC* pDC, ZIView* pView);

        /**
        * Selects the object
        *@param state - if TRUE, the object is selected
        */
        virtual inline void SelectObject(BOOL state = TRUE);

        /**
        * Shows the object name
        *@param pDC - device context
        */
        virtual void ShowObjectName(CDC* pDC);

        /**
        * Notifies when the object size and/or position has changed
        */
        virtual void SizePositionHasChanged();

        /**
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Gets the object font, depends on the defined font style
        *@param pView - view
        *@return the object font
        */
        virtual PSS_Font* GetFont(ZIView* pView);

        /**
        * Gets the color to use to draw the object. Can be the object color,
        * the font color or the style color
        *@param pView - view
        *@return the color to use to draw the object
        */
        virtual COLORREF GetColor(ZIView* pView);

        /**
        * Sets the style handle
        *@param hStyle - style handle
        *@not After having assigned the handle, remove the font handle, the object color and the object alignment
        */
        virtual void SetStyle(PSS_Style::Handle hStyle);

        /**
        * Gets the angle, in tenths of degrees, between the object base line and the x-axis. The angle is measured
        * in a counterclockwise direction from the x-axis for left-handed coordinate systems and in a clockwise
        * direction from the x-axis for right-handed coordinate systems (in which the y direction is up)
        *@return the angle, in tenths of degrees
        */
        virtual inline const int GetAngle() const;

        /**
        * Sets the font angle
        *@param angle - angle in degrees
        *@param pDoc - document
        *@note After having set the angle, if it has changed, call the OnAngleChanged function to alert the object
        *      that his angle has changed
        */
        virtual inline void SetAngle(int angle, PSS_Document* pDoc);

        /**
        * Gets the rotated text extents
        *@param pDC - device context
        *@param str - string to measure
        *@param angle - angle
        *@return the measured text extents in pixels
        */
        virtual CSize GetTextExtent(CDC* pDC, const CString& str, int angle = 0);

        /**
        * Gets the rotated text extents and origin
        *@param pDC - device context
        *@param str - string to measure
        *@param[out] size - text extents in pixels
        *@param[out] org - text origin in pixels
        *@param angle - angle
        *@return the measured string size in pixels
        */
        virtual void GetTextExtentOrg(CDC* pDC, const CString& str, CSize& size, CPoint& org, int angle = 0);

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the fill color, depends on the selected style
        *@param pView - view
        *@return the fill color
        */
        virtual COLORREF GetFillColor(ZIView* pView) const;

        /**
        * Moves the object
        *@param movePt - the move position, in point
        *@param relativeMove - if TRUE, the move must be done in relative position, otherwise in absolute position
        */
        virtual void MoveObject(CPoint& MovePt, BOOL RelativeMove = TRUE);

        /**
        * Notifies the main frame about the object has changed
        */
        virtual inline void NotifyObjectHasChanged();

        /**
        * Gets the border
        *@param pView - view
        *@return the border
        */
        virtual const PSS_Border* GetBorder(ZIView* pView) const;

        /**
        * Checks if object has changed
        *@return TRUE if object has changed, otherwise FALSE
        */
        virtual inline BOOL HasBeenChanged() const;

        /**
        * Checks if the document is read-only
        *@return TRUE if the document is read-only, otherwise FALSE
        */
        virtual inline BOOL IsReadOnly() const;

        /**
        * Sets the document as read-only
        *@param value - if TRUE, the document will be read-only
        */
        virtual inline void SetAsReadOnly(BOOL value = TRUE);

        /**
        * Checks if the document data is read-only at runtime
        *@return TRUE if the document data is read-only at runtime
        */
        virtual inline BOOL IsReadOnlyAtRuntime();

        /**
        * Sets the document data as read-only at runtime
        *@param value - if TRUE, the document data will be read-only at runtime
        */
        virtual inline void SetReadOnlyAtRuntime(BOOL value = TRUE);

        /**
        * Clears the field notes
        */
        virtual inline void ClearNotes();

        /**
        * Adds a new note, replaces it if already exists
        *@param comment - comment
        *@param userName - user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddNotes(const CString& comment, const CString& userName = _T(""));

        /**
        * Deletes the notes
        */
        virtual void DeleteNotes();

        /**
        * Gets the notes
        *@return the notes
        */
        virtual inline PSS_Notes* GetNotes() const;

        /**
        * Checks if the field is a member of a multi-column field
        *@return TRUE if the field is a member of a multi-column field, otherwise FALSE
        */
        virtual inline BOOL IsMemberOfMultiColumn() const;

        /**
        * Gets if the object is visible
        *@return TRUE if the object is visible, otherwise FALSE
        */
        virtual inline const BOOL GetIsVisible() const;

        /**
        * Sets the object as visible
        *@param value - if TRUE, the object will be visible
        */
        virtual inline void SetIsVisible(BOOL value);

        /**
        * Gets if the object should be printed
        *@return TRUE if the object should be printed, otherwise FALSE
        */
        virtual inline const BOOL GetMustBePrinted() const;

        /**
        * Sets if the object may be printed
        *@param value - if TRUE, the object may be printed
        */
        virtual inline void SetMustBePrinted(BOOL value);

        /**
        * Gets the object tracker rectangle
        *@return the object tracker rectangle
        */
        virtual inline CRectTracker* GetRectTracker() const;

        /**
        * Sets the object tracker rectangle
        *@param pRect - the object tracker rectangle
        */
        virtual inline void SetRectTracker(CRectTracker* pRect);

        /**
        * Gets the object color
        *@return the object color
        */
        virtual inline const COLORREF GetColor() const;

        /**
        * Sets the object color
        *@param value - the object color
        */
        virtual inline void SetColor(COLORREF value);

        /**
        * Gets the object fill color
        *@return the object fill color
        */
        virtual inline const COLORREF GetFillColor() const;

        /**
        * Sets the object fill color
        *@param value - the object fill color
        */
        virtual inline void SetFillColor(COLORREF value);

        /**
        * Gets the group number
        *@return the group number
        */
        virtual inline const unsigned long GetGroupNumber() const;

        /**
        * Sets the group number
        *@param value - the group number
        */
        virtual inline void SetGroupNumber(unsigned long value);

        /**
        * Gets the font handle
        *@return the font handle
        */
        virtual inline const PSS_Font::Handle GetFont() const;

        /**
        * Sets the font handle
        *@param hFont - the font handle
        */
        virtual inline void SetFont(PSS_Font::Handle hFont);

        /**
        * Gets the style handle
        *@return the style handle
        */
        virtual inline const PSS_Style::Handle GetStyle() const;

        /**
        * Gets the empty style
        *@return the empty style
        */
        virtual inline const ELineType GetEmptyStyle() const;

        /**
        * Sets the empty style
        *@param value - the empty style
        */
        virtual inline void SetEmptyStyle(ELineType value);

        /**
        * Gets the tab order
        *@return the tab order
        */
        virtual inline const double GetTabOrder() const;

        /**
        * Sets the tab order
        *@param value - the tab order
        */
        virtual inline void SetTabOrder(double value);

        /**
        * Gets the line number
        *@return the line number
        */
        virtual inline const DWORD GetLineNumber() const;

        /**
        * Gets the line number
        *@param value - the line number
        */
        virtual inline void SetLineNumber(DWORD value);

        /**
        * Gets the border
        *@return the border, NULL if no border defined
        */
        virtual inline PSS_Border* GetBorder();

        /**
        * Sets the border
        *@param pBorder - the border
        */
        virtual inline void SetBorder(PSS_Border* pBorder);

        /**
        * Gets if the object contains the default value
        *@return TRUE if the object contains the default value, otherwise FALSE
        */
        virtual inline const BOOL GetDefaultValue() const;

        /**
        * Sets if the object contains the default value
        *@param value - if TRUE, the object contains the default value
        */
        virtual inline void SetDefaultValue(BOOL value);

        /**
        * Sets if the object content has changed
        *@param value - if TRUE, the object content has changed
        */
        virtual inline void SetHasBeenChanged(BOOL value);

        /**
        * Gets the owning multi-column field
        *@return the owning multi-columns field, NULL if object isn't a member of a multi-columns field
        */
        virtual inline const PSS_FieldColumn* GetColumn() const;

        /**
        * Sets the owning multi-column field
        *@param pColumn - the owning multi-columns field
        */
        virtual inline void SetColumn(PSS_FieldColumn* pColumn);

        /**
        * Gets the user help
        *@return the user help
        */
        virtual inline CString GetUserHelp() const;

        /**
        * Sets the user help
        *@param value - the user help
        */
        virtual inline void SetUserHelp(const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

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
        static CStringArray m_FormatChoice;
        static char         m_FormatBuffer[300];
        PSS_Notes*          m_pNotes;
        EFormatType         m_FormatType;
        PSS_Rect            m_ObjectRect;
        BOOL                m_IsEmpty;

        /**
        * Called when the angle has changed
        *@param pDoc - document
        */
        virtual void OnAngleChanged(PSS_Document* pDoc);

        /**
        * Rotates the current font
        *@param pDoc - document
        */
        virtual void RotateFont(PSS_Document* pDoc);

        /**
        * Draws the right corner
        *@param pDC - device context to draw to
        */
        virtual void DrawRightCorner(CDC* pDC);

    private:
        PSS_FieldColumn*  m_pColumn;
        CRectTracker*     m_pRectTracker;
        PSS_Border*       m_pBorder;
        PSS_Font::Handle  m_hFont;
        PSS_Style::Handle m_hStyle;
        ELineType         m_EmptyStyle;
        COLORREF          m_Color;
        COLORREF          m_FillColor;
        CString           m_UserHelp;
        DWORD             m_LineNumber;
        unsigned long     m_GroupNumber;
        double            m_TabOrder;
        int               m_Angle;
        int               m_Page;
        BOOL              m_Selected;
        BOOL              m_IsVisible;
        BOOL              m_MustBePrinted;
        BOOL              m_DefaultValue;
        BOOL              m_HasBeenChanged;
        BOOL              m_ReadOnly;
        BOOL              m_ReadOnlyAtRuntime;

        /**
        * Assigns the font
        */
        void AssignFont();

        /**
        * Draws the object
        *@param pDC - device context to draw to
        */
        void DCDrawMoveObject(CDC* pDC);
};

//---------------------------------------------------------------------------
// PSS_PlanFinObject
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsEmpty() const
{
    return m_IsEmpty;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::EmptyObject()
{
    m_IsEmpty = TRUE;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::ClearEmptyObjectFlag()
{
    m_IsEmpty = FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsObjectSelected() const
{
    return m_Selected;
}
//---------------------------------------------------------------------------
CRect& PSS_PlanFinObject::GetClientRect()
{
    return m_ObjectRect;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetClientRect(const CRect& rect)
{
    (CRect&)m_ObjectRect = rect;
}
//---------------------------------------------------------------------------
int PSS_PlanFinObject::GetObjectPage() const
{
    return m_Page;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetObjectPage(int page)
{
    m_Page = page;
}
//---------------------------------------------------------------------------
EFormatType PSS_PlanFinObject::GetFormatType() const
{
    return m_FormatType;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetFormatType(EFormatType type)
{
    m_FormatType = type;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::Recalculate(PSS_Document* pDoc)
{}
//---------------------------------------------------------------------------
double PSS_PlanFinObject::GetValue() const
{
    return 0;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetValue(double value)
{}
//---------------------------------------------------------------------------
void* PSS_PlanFinObject::GetObjectAdress() const
{
    return NULL;
}
//---------------------------------------------------------------------------
CStringArray& PSS_PlanFinObject::GetFormatChoice()
{
    m_FormatChoice.RemoveAll();
    return m_FormatChoice;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetFormatWithChoice(const CString& value)
{}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::GetRectTop(CRect* pRect) const
{
    pRect->left   = m_ObjectRect.left + (m_ObjectRect.right - m_ObjectRect.left) / 2 - 2;
    pRect->top    = m_ObjectRect.top  - 2;
    pRect->right  = m_ObjectRect.left + (m_ObjectRect.right - m_ObjectRect.left) / 2 + 2;
    pRect->bottom = m_ObjectRect.top  + 2;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::GetRectBottom(CRect* pRect) const
{
    pRect->left   = m_ObjectRect.left   + (m_ObjectRect.right - m_ObjectRect.left) / 2 - 2;
    pRect->top    = m_ObjectRect.bottom - 2;
    pRect->right  = m_ObjectRect.left   + (m_ObjectRect.right - m_ObjectRect.left) / 2 + 2;
    pRect->bottom = m_ObjectRect.bottom + 2;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::GetRectLeft(CRect* pRect) const
{
    pRect->left   = m_ObjectRect.left - 2;
    pRect->top    = m_ObjectRect.top  + (m_ObjectRect.bottom - m_ObjectRect.top) / 2 - 2;
    pRect->right  = m_ObjectRect.left + 2;
    pRect->bottom = m_ObjectRect.top  + (m_ObjectRect.bottom - m_ObjectRect.top) / 2 + 2;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::GetRectRight(CRect* pRect) const
{
    pRect->left   = m_ObjectRect.right - 2;
    pRect->top    = m_ObjectRect.top   + (m_ObjectRect.bottom - m_ObjectRect.top) / 2 - 2;
    pRect->right  = m_ObjectRect.right + 2;
    pRect->bottom = m_ObjectRect.top   + (m_ObjectRect.bottom - m_ObjectRect.top) / 2 + 2;
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsRectTop(const CPoint& point) const
{
    CRect rect;
    GetRectTop(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsRectBottom(const CPoint& point) const
{
    CRect rect;
    GetRectBottom(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsRectLeft(const CPoint& point) const
{
    CRect rect;
    GetRectLeft(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsRectRight(const CPoint& point) const
{
    CRect rect;
    GetRectRight(&rect);

    return rect.PtInRect(point);
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsSelected(const CPoint& point) const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsHint(CPoint& point) const
{
    return m_ObjectRect.PtInRect(point);
}
//---------------------------------------------------------------------------
const char* PSS_PlanFinObject::GetFormattedBuffer() const
{
    return m_FormatBuffer;
}
//---------------------------------------------------------------------------
UINT PSS_PlanFinObject::GetJustify(PSS_Document* pDoc) const
{
    return DT_LEFT | DT_BOTTOM | DT_SINGLELINE;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetJustify(UINT nValue)
{}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SelectObject(BOOL state)
{
    m_Selected = state;
}
//---------------------------------------------------------------------------
UINT PSS_PlanFinObject::GetRightSubMenu() const
{
    return g_ObjectRightSubMenu;
}
//---------------------------------------------------------------------------
const int PSS_PlanFinObject::GetAngle() const
{
    return m_Angle;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetAngle(int angle, PSS_Document* pDoc)
{
    if (angle == m_Angle)
        return;

    // set the new angle value
    m_Angle = angle;

    OnAngleChanged(pDoc);
}
//---------------------------------------------------------------------------
UINT PSS_PlanFinObject::GetPropertyTabs() const
{
    // by default, general and size pages
    return (g_PropertyGeneralPage | g_PropertySizePage);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::NotifyObjectHasChanged()
{
    // to notify the view that the field has changed, pass the object address, then the function that process
    // the message can know wich object has changed
    AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(this));
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::HasBeenChanged() const
{
    return m_HasBeenChanged;
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsReadOnly() const
{
    return m_ReadOnly;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetAsReadOnly(BOOL value)
{
    m_ReadOnly = value;
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsReadOnlyAtRuntime()
{
    return (m_ReadOnlyAtRuntime || m_ReadOnly);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetReadOnlyAtRuntime(BOOL value)
{
    m_ReadOnlyAtRuntime = value;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::ClearNotes()
{
    if (m_pNotes)
        m_pNotes->ClearNotes();
}
//---------------------------------------------------------------------------
PSS_Notes* PSS_PlanFinObject::GetNotes() const
{
    return m_pNotes;
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::IsMemberOfMultiColumn() const
{
    return (m_pColumn != NULL);
}
//---------------------------------------------------------------------------
const BOOL PSS_PlanFinObject::GetIsVisible() const
{
    return m_IsVisible;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetIsVisible(BOOL value)
{
    m_IsVisible = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PlanFinObject::GetMustBePrinted() const
{
    return m_MustBePrinted;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetMustBePrinted(BOOL value)
{
    m_MustBePrinted = value;
}
//---------------------------------------------------------------------------
CRectTracker* PSS_PlanFinObject::GetRectTracker() const
{
    return m_pRectTracker;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetRectTracker(CRectTracker* value)
{
    m_pRectTracker = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_PlanFinObject::GetColor() const
{
    return m_Color;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetColor(COLORREF value)
{
    m_Color = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_PlanFinObject::GetFillColor() const
{
    return m_FillColor;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetFillColor(COLORREF value)
{
    m_FillColor = value;
}
//---------------------------------------------------------------------------
const unsigned long PSS_PlanFinObject::GetGroupNumber() const
{
    return m_GroupNumber;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetGroupNumber(unsigned long value)
{
    m_GroupNumber = value;
}
//---------------------------------------------------------------------------
const PSS_Font::Handle PSS_PlanFinObject::GetFont() const
{
    return m_hFont;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetFont(PSS_Font::Handle value)
{
    m_hFont = value;
}
//---------------------------------------------------------------------------
const PSS_Style::Handle PSS_PlanFinObject::GetStyle() const
{
    return m_hStyle;
}
//---------------------------------------------------------------------------
const ELineType PSS_PlanFinObject::GetEmptyStyle() const
{
    return m_EmptyStyle;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetEmptyStyle(ELineType value)
{
    m_EmptyStyle = value;
}
//---------------------------------------------------------------------------
const double PSS_PlanFinObject::GetTabOrder() const
{
    return m_TabOrder;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetTabOrder(double value)
{
    m_TabOrder = value;
}
//---------------------------------------------------------------------------
const DWORD PSS_PlanFinObject::GetLineNumber() const
{
    return m_LineNumber;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetLineNumber(DWORD value)
{
    m_LineNumber = value;
}
//---------------------------------------------------------------------------
PSS_Border* PSS_PlanFinObject::GetBorder()
{
    return m_pBorder;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetBorder(PSS_Border* value)
{
    m_pBorder = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PlanFinObject::GetDefaultValue() const
{
    return m_DefaultValue;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetDefaultValue(BOOL value)
{
    m_DefaultValue = value;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetHasBeenChanged(BOOL value)
{
    m_HasBeenChanged = value;
}
//---------------------------------------------------------------------------
const PSS_FieldColumn* PSS_PlanFinObject::GetColumn() const
{
    return m_pColumn;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetColumn(PSS_FieldColumn* pColumn)
{
    m_pColumn = pColumn;
}
//---------------------------------------------------------------------------
CString PSS_PlanFinObject::GetUserHelp() const
{
    return m_UserHelp;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetUserHelp(const CString& value)
{
    m_UserHelp = value;
}
//---------------------------------------------------------------------------

#endif
