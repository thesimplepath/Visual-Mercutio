/****************************************************************************
 * ==> PSS_PLFNSquare ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan form square object               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNSquareH
#define PSS_PLFNSquareH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNSquare
    #define PSS_PLFNSquare PLFNSquare
#endif

// processsoft
#include "PSS_PlanFinObject.h"

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
* Financial plan form square object. A square may only contain one char
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNSquare : public PSS_PlanFinObject
{
    DECLARE_SERIAL(PSS_PLFNSquare)

    public:
        typedef PSS_PlanFinObject inherited;

        PSS_PLFNSquare();

        /**
        * Constructor
        *@param squareSize - square size
        *@param maxLength - maximum length
        */
        PSS_PLFNSquare(const CSize& squareSize, int maxLength);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNSquare(const PSS_PLFNSquare& other);

        virtual ~PSS_PLFNSquare();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNSquare& operator = (const PSS_PLFNSquare& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNSquare& operator = (const PSS_PLFNSquare* pOther);

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
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, PSS_View* pView);

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Checks if the object is empty
        *@return TRUE if the object is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets the formatted object
        *@return the formatted object
        */
        virtual CString GetFormattedObject();

        /**
        * Gets the unformatted string of the object image
        *@return the unformatted string of the object image
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
        * Checks if the object is selected
        *@param point - point to check in pixels
        *@return TRUE if object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Gets the size of each square
        *@return the size of each square
        */
        virtual const inline CSize GetSquareSize() const;

        /**
        * Sets the size of each square
        *@param value - the size
        */
        virtual void inline SetSquareSize(const CSize& value);

        /**
        * Gets the maximum text length included within the squares
        *@return the maximum text length included within the squares
        */
        virtual inline const int GetSquareMaxLength() const;

        /**
        * Sets the maximum text length included within the squares
        *@param value - the maximum text length included within the squares, -1 for infinite
        */
        virtual inline void SetSquareMaxLength(int value);

        /**
        * Gets if the square should be auto-sized
        *@return TRUE if the square should be auto-sized, otherwise FALSE
        */
        virtual inline const BOOL GetAutoAdjustSize() const;

        /**
        * Sets if the square should be auto-sized
        *@param value - if TRUE, the square should be auto-sized
        */
        virtual inline void SetAutoAdjustSize(BOOL value);

        /**
        * Gets the number of char per square
        *@return the number of char per square
        */
        virtual inline const unsigned GetCharPerSquare() const;

        /**
        * Sets the number of char per square
        *@param value - the number of char per square
        */
        virtual inline void SetCharPerSquare(unsigned value);

        /**
        * Gets the object
        *@return the object
        */
        virtual inline const PSS_PlanFinObject* GetObject() const;

        /**
        * Sets the object
        *@param pObject - the object
        */
        virtual inline void SetObject(PSS_PlanFinObject* pObject);

        /**
        * Gets the way the square should be shown
        *@return the way the square should be shown
        */
        virtual inline const ESquareType GetSquareType() const;

        /**
        * Sets the way the square should be shown
        *@param value - the way the square should be shown
        */
        virtual inline void SetSquareType(ESquareType value);

        /**
        * Gets the way the parsing should be done
        *@return the way the parsing should be done
        */
        virtual inline const EParsingModeType GetParsingMode() const;

        /**
        * Sets the way the parsing should be done
        *@param value - the way the parsing should be done
        */
        virtual inline void SetParsingMode(EParsingModeType value);

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
        PSS_PlanFinObject* m_pObject;
        ESquareType        m_SquareType;
        EParsingModeType   m_ParsingMode;
        CSize              m_SquareSize;
        int                m_SquareMaxLength;
        unsigned           m_CharPerSquare;
        BOOL               m_AutoAdjustSize;

        /**
        * Draws all the squares
        *@param pDC - device context
        */
        void DrawSquares(CDC* pDC);
};

//---------------------------------------------------------------------------
// PSS_PLFNSquare
//---------------------------------------------------------------------------
UINT PSS_PLFNSquare::GetRightSubMenu() const
{
    if (m_pObject)
        return m_pObject->GetRightSubMenu();

    return g_ObjectRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNSquare::GetPropertyTabs() const
{
    return (g_PropertyGeneralPage | g_PropertySizePage | g_PropertySquarePage);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNSquare::IsEmpty() const
{
    if (m_pObject)
        return m_pObject->IsEmpty();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNSquare::IsSelected(const CPoint& point) const
{
    if (m_pObject)
        return m_pObject->IsSelected(point);

    return FALSE;
}
//---------------------------------------------------------------------------
const CSize PSS_PLFNSquare::GetSquareSize() const
{
    return m_SquareSize;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetSquareSize(const CSize& value)
{
    m_SquareSize = value;
}
//---------------------------------------------------------------------------
const int PSS_PLFNSquare::GetSquareMaxLength() const
{
    return m_SquareMaxLength;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetSquareMaxLength(int value)
{
    m_SquareMaxLength = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNSquare::GetAutoAdjustSize() const
{
    return m_AutoAdjustSize;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetAutoAdjustSize(BOOL value)
{
    m_AutoAdjustSize = value;
}
//---------------------------------------------------------------------------
const unsigned PSS_PLFNSquare::GetCharPerSquare() const
{
    return m_CharPerSquare;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetCharPerSquare(unsigned value)
{
    m_CharPerSquare = value;
}
//---------------------------------------------------------------------------
const PSS_PlanFinObject* PSS_PLFNSquare::GetObject() const
{
    return m_pObject;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetObject(PSS_PlanFinObject* pObject)
{
    m_pObject = pObject;
}
//---------------------------------------------------------------------------
const ESquareType PSS_PLFNSquare::GetSquareType() const
{
    return m_SquareType;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetSquareType(ESquareType value)
{
    m_SquareType = value;
}
//---------------------------------------------------------------------------
const EParsingModeType PSS_PLFNSquare::GetParsingMode() const
{
    return m_ParsingMode;
}
//---------------------------------------------------------------------------
void PSS_PLFNSquare::SetParsingMode(EParsingModeType value)
{
    m_ParsingMode = value;
}
//---------------------------------------------------------------------------

#endif
