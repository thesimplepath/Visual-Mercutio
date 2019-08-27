/****************************************************************************
 * ==> PSS_PlanFinObj ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides financial plan objects                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PlanFinObjH
#define PSS_PlanFinObjH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNRect
    #define PSS_PLFNRect PLFNRect
#endif
#ifndef PSS_PLFNLine
    #define PSS_PLFNLine PLFNLine
#endif
#ifndef PSS_PLFNStatic
    #define PSS_PLFNStatic PLFNStatic
#endif
#ifndef PSS_PLFNTime
    #define PSS_PLFNTime PLFNTime
#endif
#ifndef PSS_PLFNLong
    #define PSS_PLFNLong PLFNLong
#endif

// std
#include <float.h>
#include <math.h>

// processsoft
#include "zaconst.h"
#include "zamath.h"
#include "ZAObject.h"
#include "ZAText.h"
#include "ZAString.h"
#include "ZAGraphc.h"
#include "PSS_Formula.h"
#include "ZBPoint.h"
#include "ZBDate.h"

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
* Financial plan containing a rectangle
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNRect : public PLFNGraphic
{
    DECLARE_SERIAL(PSS_PLFNRect)

    public:
        typedef PLFNGraphic inherited;

        /**
        * Constructor
        *@param round - if TRUE, the rect will be rounded
        */
        PSS_PLFNRect(BOOL round = FALSE);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNRect(const PSS_PLFNRect& other);

        virtual ~PSS_PLFNRect();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNRect& operator = (const PSS_PLFNRect* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNRect& operator = (const PSS_PLFNRect& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the arc offset
        *@return the arc offset
        */
        virtual inline WORD GetArcOffset() const;

        /**
        * Sets the arc offset
        *@param value - the arc offset
        */
        virtual inline void SetArcOffset(const WORD value);

        /**
        * Gets if the rect is rounded
        *@return TRUE if the rect is rounded, otherwise FALSE
        */
        virtual inline BOOL IsRounded() const;

        /**
        * Sets if the rect is rounded
        *@param value - if TRUE, the rect will be rounded
        */
        virtual inline void SetRounded(BOOL value);

        /**
        * Checks if a point hits the rect
        *@param point - point to check in pixels
        *@return TRUE if the rect was hit, otherwise FALSE
        */
        virtual inline BOOL IsHint(CPoint& point) const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

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
        /**
        * Draws the object content
        *@param pDC - device context
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

    private:
        WORD m_ArcOffset;
        BOOL m_Round;
};

//---------------------------------------------------------------------------
// PSS_PLFNRect
//---------------------------------------------------------------------------
WORD PSS_PLFNRect::GetArcOffset() const
{
    return m_ArcOffset;
}
//---------------------------------------------------------------------------
void PSS_PLFNRect::SetArcOffset(const WORD value)
{
    m_ArcOffset = value;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNRect::IsRounded() const
{
    return m_Round;
}
//---------------------------------------------------------------------------
void PSS_PLFNRect::SetRounded(BOOL value)
{
    m_Round = value;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNRect::IsHint(CPoint& point) const
{
    // copy the rectangle object and inflate it by -3, -3. This operation is required to check
    // if the cursor is on the rectangle but not inside
    CRect minRect = m_rctObject;
    CRect maxRect = m_rctObject;
    minRect.InflateRect(-3, -3);
    maxRect.InflateRect(3, 3);

    return (maxRect.PtInRect(point) && !minRect.PtInRect(point));
}
//---------------------------------------------------------------------------
inline UINT PSS_PLFNRect::GetPropertyTabs() const
{
    return (PropertyGeneralBasicPage | PropertySizePage | PropertyGraphicPage | PropertyRectPage);
}
//---------------------------------------------------------------------------

/**
* Financial plan containing a line
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNLine : public PLFNGraphic
{
    DECLARE_SERIAL(PSS_PLFNLine)

    public:
        typedef PLFNGraphic inherited;

        PSS_PLFNLine();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNLine(const PSS_PLFNLine& other);

        virtual ~PSS_PLFNLine();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNLine& operator = (const PSS_PLFNLine* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNLine& operator = (const PSS_PLFNLine& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the start point
        *@return the start point
        */
        virtual inline const CPoint& GetStartPoint() const;

        /**
        * Sets the start point
        *@param value - the start point
        */
        virtual inline void SetStartPoint(const CPoint& value);

        /**
        * Gets the end point
        *@return the end point
        */
        virtual inline const CPoint& GetEndPoint() const;

        /**
        * Sets the end point
        *@param value - the end point
        */
        virtual inline void SetEndPoint(const CPoint& value);

        /**
        * Notifies that the object size and/or position has changed
        */
        virtual void SizePositionHasChanged();

        /**
        * Checks if a line hits the rect
        *@param point - point to check in pixels
        *@return TRUE if the line was hit, otherwise FALSE
        */
        virtual inline BOOL IsHint(CPoint& point) const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

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
        /**
        * Draws the object content
        *@param pDC - device context
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

    private:
        ZBPoint m_StartPoint;
        ZBPoint m_EndPoint;
};

//---------------------------------------------------------------------------
// PSS_PLFNLine
//---------------------------------------------------------------------------
const CPoint& PSS_PLFNLine::GetStartPoint() const
{
    return m_StartPoint;
}
//---------------------------------------------------------------------------
void PSS_PLFNLine::SetStartPoint(const CPoint& value)
{
    m_StartPoint = value;
}
//---------------------------------------------------------------------------
const CPoint& PSS_PLFNLine::GetEndPoint() const
{
    return m_EndPoint;
}
//---------------------------------------------------------------------------
void PSS_PLFNLine::SetEndPoint(const CPoint& value)
{
    m_EndPoint = value;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNLine::IsHint(CPoint& point) const
{
    // copy the object rectangle and inflate it by 3, 3. This operation is required to check
    // if the cursor is on the line because lines are very small
    CRect rect = m_rctObject;
    rect.InflateRect(3, 3);

    return (rect.PtInRect(point));
}
//---------------------------------------------------------------------------
UINT PSS_PLFNLine::GetPropertyTabs() const
{
    return (PropertyGeneralBasicPage | PropertySizePage | PropertyGraphicPage);
}
//---------------------------------------------------------------------------

/**
* Financial plan containing a static object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNStatic : public PLFNText
{
    DECLARE_SERIAL(PSS_PLFNStatic)

    public:
        typedef PLFNText inherited;

        PSS_PLFNStatic();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNStatic(const PSS_PLFNStatic& other);

        virtual ~PSS_PLFNStatic();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNStatic& operator = (const PSS_PLFNStatic* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNStatic& operator = (const PSS_PLFNStatic& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual UINT GetPropertyTabs() const;

        /**
        * Draws the object content
        *@param pDC - device context
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

    protected:
        /**
        * Called When the angle has changed
        *@param pDoc - document
        */
        virtual void OnAngleChanged(ZDDocument* pDoc);
};

//---------------------------------------------------------------------------
// PSS_PLFNStatic
//---------------------------------------------------------------------------
inline UINT PSS_PLFNStatic::GetPropertyTabs() const
{
    return (PropertyGeneralStaticPage | PropertySizePage);
}
//---------------------------------------------------------------------------

/**
* Financial plan containing a time
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNTime : public PLFNAscii
{
    DECLARE_SERIAL(PSS_PLFNTime)

    public:
        typedef PLFNAscii inherited;

        PSS_PLFNTime();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNTime(const PSS_PLFNTime& other);

        virtual ~PSS_PLFNTime();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNTime& operator = (const PSS_PLFNTime* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNTime& operator = (const PSS_PLFNTime& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets if the object is static
        *@return TRUE if the object is static, otherwise FALSE
        */
        virtual inline const BOOL GetIsStatic() const;

        /**
        * Checks if the object is selected
        *@param point - point to check in pixels
        *@return TRUE if object is selected, otherwise FALSE
        */
        virtual BOOL IsSelected(const CPoint& point) const;

        /**
        * Sets the time to today
        */
        #ifdef _WIN32
            virtual inline void SetToday();
        #endif

        /**
        * Gets the time
        *@return the time
        */
        #ifdef _WIN32
            virtual inline ZBDate GetTimeValue() const;
        #endif

        /**
        * Sets the time
        *@param time - time
        */
        #ifdef _WIN32
            virtual inline void SetTimeValue(const ZBDate& time);
        #endif

        /**
        * Gets the time object
        *@return the time object
        */
        virtual inline void* GetObject() const;

        /**
        * Gets the formatted object
        *@return the formatted object
        */
        virtual CString GetFormattedObject();

        /**
        * Gets the unformated string of the object image
        *@return the unformated string of the object image
        */
        virtual CString GetUnformattedObject();

        /**
        * Converts the formatted object
        *@param value - formatted value
        *@param locateFormat - if TRUE, the format will be loacalized
        *@param emptyWhenZero - if TRUE, the object will be emptied if set to zero
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ConvertFormattedObject(const CString& value, BOOL locateFormat = TRUE, BOOL emptyWhenZero = FALSE);

        /**
        * Gets the format choice
        *@return the format choice
        */
        virtual CStringArray& GetFormatChoice() const;

        /**
        * Sets the format choice
        *@param value - the format choice
        */
        virtual void SetFormatWithChoice(const CString& value);

        /**
        * Gets the submenu identifier when the user click the right mouse button
        *@return the submenu identifier when the user click the right mouse button
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the time
        *@return the time
        */
        virtual inline const ZBDate& GetTime() const;

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
        /**
        * Draws the object content
        *@param pDC - device context
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

    private:
        ZBDate m_Time;
};

//---------------------------------------------------------------------------
// PSS_PLFNTime
//---------------------------------------------------------------------------
const BOOL PSS_PLFNTime::GetIsStatic() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_PLFNTime::SetToday()
{
    m_Time = ZBDate::GetToday();
}
//---------------------------------------------------------------------------
ZBDate PSS_PLFNTime::GetTimeValue() const
{
    return m_Time;
};
//---------------------------------------------------------------------------
void PSS_PLFNTime::SetTimeValue(const ZBDate& time)
{
    m_Time = time;
    ClearEmptyObjectFlag();
}
//---------------------------------------------------------------------------
void* PSS_PLFNTime::GetObject() const
{
    return((void*)&m_Time);
}
//---------------------------------------------------------------------------
UINT PSS_PLFNTime::GetRightSubMenu() const
{
    return g_DateRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNTime::GetPropertyTabs() const
{
    return PropertyGeneralDatePage | PropertySizePage;
}
//---------------------------------------------------------------------------
const ZBDate& PSS_PLFNTime::GetTime() const
{
    return m_Time;
}
//---------------------------------------------------------------------------

/**
* Financial plan containing a long value
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNLong : public PLFNAscii
{
    DECLARE_SERIAL(PSS_PLFNLong)

    public:
        /**
        * Incon display type
        */
        enum IEIconDisplayType
        {
            IE_DT_NoIcon,
            IE_DT_AssociationIcon,
        };

        typedef PLFNAscii inherited;

        PSS_PLFNLong();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNLong(const PSS_PLFNLong& other);

        virtual ~PSS_PLFNLong();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNLong& operator = (const PSS_PLFNLong* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNLong& operator = (const PSS_PLFNLong& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets if the object is static
        *@return TRUE if the object is static, otherwise FALSE
        */
        virtual inline const BOOL GetIsStatic() const;

        /**
        * Gets the submenu identifier when the user click the right mouse button
        *@return the submenu identifier when the user click the right mouse button
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the contains from a line
        *@param line - the line containing the object definition
        */
        virtual void GetContains(const CString& line);

        /**
        * Checks if object is selected
        *@paran point - point to check in pixels
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Gets the time object
        *@return the time object
        */
        virtual inline void* GetObject() const;

        /**
        * Gets the value
        *@return the value
        */
        virtual inline double GetValue() const;

        /**
        * Sets the value
        *@param value - the value
        */
        virtual inline void SetValue(double value);

        /**
        * Gets the real value
        *@return the real value
        */
        virtual inline double GetRealValue() const;

        /**
        * Gets the formatted object
        *@return the formatted object
        */
        virtual CString GetFormattedObject();

        /**
        * Gets the unformated string of the object image
        *@return the unformated string of the object image
        */
        virtual CString GetUnformattedObject();

        /**
        * Converts the formatted object
        *@param value - formatted value
        *@param locateFormat - if TRUE, the format will be loacalized
        *@param emptyWhenZero - if TRUE, the object will be emptied if set to zero
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ConvertFormatedObject(const CString& value, BOOL locateFormat = TRUE, BOOL emptyWhenZero = FALSE);

        /**
        * Gets the format choice
        *@return the format choice
        */
        virtual CStringArray& GetFormatChoice();

        /**
        * Sets the format choice
        *@param value - the format choice
        */
        virtual void SetFormatWithChoice(const CString& value);

        /**
        * Recalculates its own value
        *@param pDoc - owning document
        */
        virtual void Recalculate(ZDDocument* pDoc);

        /**
        * Checks if value is rounded
        *@return TRUE if value is rounded, otherwise FALSE
        */
        virtual inline BOOL IsRounded() const;

        /**
        * Sets if the value should be rounded
        *@param value - if TRUE, the value should be rounded
        */
        virtual inline void SetRounded(BOOL value = TRUE);

        /**
        * Gets the rounded value
        *@return the rounded value
        */
        virtual inline double GetRoundedValue() const;

        /**
        * Sets the rounded value
        *@param value - the rounded value
        */
        virtual inline void SetRoundedValue(double value);

        /**
        * Gets if the field was calculated
        *@return TRUE if the field was calculated, otherwise FALSE
        */
        virtual inline BOOL IsCalculatedField() const;

        /**
        * Sets if the field was calculated
        *@param value - if TRUE, the field was calculated
        */
        virtual inline void SetCalculatedField(BOOL value = TRUE);

        /**
        * Gets if the value should be kept
        *@return TRUE if the value should be kept, otherwise FALSE
        */
        virtual inline BOOL KeepTheValue() const;

        /**
        * Sets if the value should be kept
        *@param value - if TRUE, the value should be kept
        */
        virtual inline void SetKeepTheValue(BOOL value = TRUE);

        /**
        * Sets the icon display type
        *@param type - icon display type
        */
        virtual inline void SetIconDisplayType(IEIconDisplayType type = IE_DT_NoIcon);

        /**
        * Gets the associations
        *@return the associations
        */
        virtual inline PSS_FormulaAssociationManager& GetAssociations();

        /**
        * Gets the current association
        *@return the current association
        */
        virtual inline PSS_FormulaAssociation* GetCurrentAssociation();

        /**
        * Sets the current association
        *@param pAssociation - the current association
        */
        virtual inline void SetCurrentAssociation(PSS_FormulaAssociation* pAssociation);

        /**
        * Sets the current association
        *@param name - the current association name
        */
        virtual inline void SetCurrentAssociation(const CString& name);

        /**
        * Clears the current association
        */
        virtual inline void ClearCurrentAssociation();

        /**
        * Draws the calculated symbol for the object
        *@param pDC - device context to draw to
        */
        virtual void DrawCalculatedSymbol(CDC* pDC);

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
        double m_Long;

        /**
        * Draws the object content
        *@param pDC - device context
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

    private:
        IEIconDisplayType             m_IconDisplayType;
        PSS_FormulaAssociationManager m_Associations;
        double                        m_Rounded;
        BOOL                          m_IsCalculatedField;
        BOOL                          m_KeepTheValue;
        BOOL                          m_IsRounded;
};

//---------------------------------------------------------------------------
// PSS_PLFNLong
//---------------------------------------------------------------------------
const BOOL PSS_PLFNLong::GetIsStatic() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNLong::GetRightSubMenu() const
{
    if (IsCalculatedField())
        return g_CalculatedRightSubMenu;

    return g_NumberRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNLong::GetPropertyTabs() const
{
    return (IsCalculatedField() ? PropertyGeneralBasicPage | PropertySizePage | PropertyLongPage :
            PropertyGeneralTextPage | PropertySizePage);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNLong::IsSelected(const CPoint& point) const
{
    return(m_rctObject.PtInRect(point));
}
//---------------------------------------------------------------------------
void* PSS_PLFNLong::GetObject() const
{
    return ((void*)&m_Long);
}
//---------------------------------------------------------------------------
double PSS_PLFNLong::GetValue() const
{
    return m_Long;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetValue(double value)
{
    m_Long = value;

    if (IsCalculatedField())
        SetHasBeenChanged(TRUE);

    ClearEmptyObjectFlag();
}
//---------------------------------------------------------------------------
double PSS_PLFNLong::GetRealValue() const
{
    return m_Long;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNLong::IsRounded() const
{
    return m_IsRounded;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetRounded(BOOL value)
{
    m_IsRounded = value;
}
//---------------------------------------------------------------------------
double PSS_PLFNLong::GetRoundedValue() const
{
    return m_Rounded;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetRoundedValue(double value)
{
    m_Rounded = value;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNLong::IsCalculatedField() const
{
    return m_IsCalculatedField;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetCalculatedField(BOOL value)
{
    m_IsCalculatedField = value;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNLong::KeepTheValue() const
{
    return m_KeepTheValue;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetKeepTheValue(BOOL value)
{
    m_KeepTheValue = value;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetIconDisplayType(IEIconDisplayType type)
{
    m_IconDisplayType = type;
}
//---------------------------------------------------------------------------
PSS_FormulaAssociationManager& PSS_PLFNLong::GetAssociations()
{
    return m_Associations;
}
//---------------------------------------------------------------------------
PSS_FormulaAssociation* PSS_PLFNLong::GetCurrentAssociation()
{
    return m_Associations.GetCurrentAssociation();
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetCurrentAssociation(PSS_FormulaAssociation* pAssociation)
{
    m_Associations.SetCurrentAssociation(pAssociation);
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetCurrentAssociation(const CString& name)
{
    m_Associations.SetCurrentAssociation(name);
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::ClearCurrentAssociation()
{
    m_Associations.ClearCurrentAssociation();
}
//---------------------------------------------------------------------------

#endif
