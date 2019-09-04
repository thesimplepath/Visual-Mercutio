/****************************************************************************
 * ==> PSS_Border ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a border component                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BorderH
#define PSS_BorderH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Border
    #define PSS_Border ZABorder
#endif

// mfc
#include "Mfc.h"

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
* Border component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Border : public CObject
{
    DECLARE_SERIAL(PSS_Border)

    public:
        typedef CObject inherited;

        PSS_Border();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Border(const PSS_Border& other);

        virtual ~PSS_Border();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Border& operator = (const PSS_Border& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_Border* Clone() const;

        /**
        * Draws the border rectangle
        *@param pDC - device context to draw to
        *@param rect - rectangle
        */
        virtual void DrawBorderRect(CDC* pDC, const CRect& rect);

        /**
        * Draws the top border rectangle
        *@param pDC - device context to draw to
        *@param startPoint - start point
        *@param endPoint - end point
        */
        virtual void DrawBorderTopLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint);

        /**
        * Draws the bottom border rectangle
        *@param pDC - device context to draw to
        *@param startPoint - start point
        *@param endPoint - end point
        */
        virtual void DrawBorderBottomLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint);

        /**
        * Draws the left border rectangle
        *@param pDC - device context to draw to
        *@param startPoint - start point
        *@param endPoint - end point
        */
        virtual void DrawBorderLeftLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint);

        /**
        * Draws the right border rectangle
        *@param pDC - device context to draw to
        *@param startPoint - start point
        *@param endPoint - end point
        */
        virtual void DrawBorderRightLine(CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint);

        /**
        * Gets the left border width
        *@return the left border width
        */
        virtual inline const WORD GetLeftWidth() const;

        /**
        * Sets the left border width
        *@param value - the left border width
        */
        virtual inline void SetLeftWidth(WORD value);

        /**
        * Gets the top border width
        *@return the top border width
        */
        virtual inline const WORD GetTopWidth() const;

        /**
        * Sets the top border width
        *@param value - the top border width
        */
        virtual inline void SetTopWidth(WORD value);

        /**
        * Gets the right border width
        *@return the right border width
        */
        virtual inline const WORD GetRightWidth() const;

        /**
        * Sets the right border width
        *@param value - the right border width
        */
        virtual inline void SetRightWidth(WORD value);

        /**
        * Gets the bottom border width
        *@return the bottom border width
        */
        virtual inline const WORD GetBottomWidth() const;

        /**
        * Sets the bottom border width
        *@param value - the bottom border width
        */
        virtual inline void SetBottomWidth(WORD value);

        /**
        * Gets the left border line type
        *@return the left border line type
        */
        virtual inline const ELineType GetLeftType() const;

        /**
        * Sets the left border line type
        *@param value - the left border line type
        */
        virtual inline void SetLeftType(ELineType value);

        /**
        * Gets the right border line type
        *@return the right border line type
        */
        virtual inline const ELineType GetRightType() const;

        /**
        * Sets the right border line type
        *@param value - the right border line type
        */
        virtual inline void SetRightType(ELineType value);

        /**
        * Gets the top border line type
        *@return the top border line type
        */
        virtual inline const ELineType GetTopType() const;

        /**
        * Sets the top border line type
        *@param value - the top border line type
        */
        virtual inline void SetTopType(ELineType value);

        /**
        * Gets the bottom border line type
        *@return the bottom border line type
        */
        virtual inline const ELineType GetBottomType() const;

        /**
        * Sets the bottom border line type
        *@param value - the bottom border line type
        */
        virtual inline void SetBottomType(ELineType value);

        /**
        * Gets the shadow state
        *@return the shadow state
        */
        virtual inline const BOOL GetShadow() const;

        /**
        * Sets the shadow state
        *@param value - the shadow state
        */
        virtual inline void SetShadow(BOOL value);

        /**
        * Gets the top border color
        *@return the top border color
        */
        virtual inline const COLORREF GetTopColor() const;

        /**
        * Sets the top border color
        *@param value - the top border color
        */
        virtual inline void SetTopColor(COLORREF value);

        /**
        * Gets the bottom border color
        *@return the bottom border color
        */
        virtual inline const COLORREF GetBottomColor() const;

        /**
        * Sets the bottom border color
        *@param value - the bottom border color
        */
        virtual inline void SetBottomColor(COLORREF value);

        /**
        * Gets the left border color
        *@return the left border color
        */
        virtual inline const COLORREF GetLeftColor() const;

        /**
        * Sets the left border color
        *@param value - the left border color
        */
        virtual inline void SetLeftColor(COLORREF value);

        /**
        * Gets the right border color
        *@return the right border color
        */
        virtual inline const COLORREF GetRightColor() const;

        /**
        * Sets the right border color
        *@param value - the right border color
        */
        virtual inline void SetRightColor(COLORREF value);

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

    private:
        ELineType m_LeftType;
        ELineType m_TopType;
        ELineType m_RightType;
        ELineType m_BottomType;
        COLORREF  m_LeftColor;
        COLORREF  m_TopColor;
        COLORREF  m_RightColor;
        COLORREF  m_BottomColor;
        WORD      m_LeftWidth;
        WORD      m_TopWidth;
        WORD      m_RightWidth;
        WORD      m_BottomWidth;
        BOOL      m_Shadow;

        /**
        * Draws a horizontal line on a border rectangle
        *@param pDC - device context
        *@param startPoint - start point
        *@param endPoint - end point
        *@param type - line type
        */
        void DrawBorderHorizontalLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint, ELineType Type);

        /**
        * Draws a vertical line on a border rectangle
        *@param pDC - device context
        *@param startPoint - start point
        *@param endPoint - end point
        *@param type - line type
        */
        void DrawBorderVerticalLine(CDC* pDC, const CPoint& startPoint, const CPoint& endPoint, ELineType Type);
};

//---------------------------------------------------------------------------
// PSS_Border
//---------------------------------------------------------------------------
const WORD PSS_Border::GetLeftWidth() const
{
    return m_LeftWidth;
}
//---------------------------------------------------------------------------
void PSS_Border::SetLeftWidth(WORD value)
{
    m_LeftWidth = value;
}
//---------------------------------------------------------------------------
const WORD PSS_Border::GetTopWidth() const
{
    return m_TopWidth;
}
//---------------------------------------------------------------------------
void PSS_Border::SetTopWidth(WORD value)
{
    m_TopWidth = value;
}
//---------------------------------------------------------------------------
const WORD PSS_Border::GetRightWidth() const
{
    return m_RightWidth;
}
//---------------------------------------------------------------------------
void PSS_Border::SetRightWidth(WORD value)
{
    m_RightWidth = value;
}
//---------------------------------------------------------------------------
const WORD PSS_Border::GetBottomWidth() const
{
    return m_BottomWidth;
}
//---------------------------------------------------------------------------
void PSS_Border::SetBottomWidth(WORD value)
{
    m_BottomWidth = value;
}
//---------------------------------------------------------------------------
const ELineType PSS_Border::GetLeftType() const
{
    return m_LeftType;
}
//---------------------------------------------------------------------------
void PSS_Border::SetLeftType(ELineType value)
{
    m_LeftType = value;
}
//---------------------------------------------------------------------------
const ELineType PSS_Border::GetRightType() const
{
    return m_RightType;
}
//---------------------------------------------------------------------------
void PSS_Border::SetRightType(ELineType value)
{
    m_RightType = value;
}
//---------------------------------------------------------------------------
const ELineType PSS_Border::GetTopType() const
{
    return m_TopType;
}
//---------------------------------------------------------------------------
void PSS_Border::SetTopType(ELineType value)
{
    m_TopType = value;
}
//---------------------------------------------------------------------------
const ELineType PSS_Border::GetBottomType() const
{
    return m_BottomType;
}
//---------------------------------------------------------------------------
void PSS_Border::SetBottomType(ELineType value)
{
    m_BottomType = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Border::GetShadow() const
{
    return m_Shadow;
}
//---------------------------------------------------------------------------
void PSS_Border::SetShadow(BOOL value)
{
    m_Shadow = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_Border::GetTopColor() const
{
    return m_TopColor;
}
//---------------------------------------------------------------------------
void PSS_Border::SetTopColor(COLORREF value)
{
    m_TopColor = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_Border::GetBottomColor() const
{
    return m_BottomColor;
}
//---------------------------------------------------------------------------
void PSS_Border::SetBottomColor(COLORREF value)
{
    m_BottomColor = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_Border::GetLeftColor() const
{
    return m_LeftColor;
}
//---------------------------------------------------------------------------
void PSS_Border::SetLeftColor(COLORREF value)
{
    m_LeftColor = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_Border::GetRightColor() const
{
    return m_RightColor;
}
//---------------------------------------------------------------------------
void PSS_Border::SetRightColor(COLORREF value)
{
    m_RightColor = value;
}
//---------------------------------------------------------------------------

#endif
