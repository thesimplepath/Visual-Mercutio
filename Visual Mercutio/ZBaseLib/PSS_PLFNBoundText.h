/****************************************************************************
 * ==> PSS_PLFNBoundText ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan bounding text object             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNBoundTextH
#define PSS_PLFNBoundTextH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNBoundText
    #define PSS_PLFNBoundText PLFNBoundText
#endif

// processsoft
#include "ZAString.h"

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
* Financial plan bounding text object, acts like a financial plan string object
* but let the text be wrapped into a bound
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNBoundText : public PLFNString
{
    DECLARE_SERIAL(PSS_PLFNBoundText)

    public:
        typedef PLFNString inherited;

        /**
        * Constructor
        *@param isStatic - if TRUE the text will be static
        */
        PSS_PLFNBoundText(BOOL isStatic = FALSE);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNBoundText(const PSS_PLFNBoundText& other);

        virtual ~PSS_PLFNBoundText();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNBoundText& operator = (const PSS_PLFNBoundText& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNBoundText& operator = (const PSS_PLFNBoundText* pOther);

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
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

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
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the hanging in centimeters
        *@return the hanging in centimeters
        */
        virtual inline const double GetHanging() const;

        /**
        * Sets the hanging in centimeters
        *@param value - the hanging in centimeters
        */
        virtual inline void SetHanging(double value);

        /**
        * Gets the number of lines that must follow the hanging
        *@return the number of lines that must follow the hanging
        */
        virtual inline const UINT GetHangingLines() const;

        /**
        * Sets the number of lines that must follow the hanging
        *@param value - the number of lines that must follow the hanging
        */
        virtual inline void SetHangingLines(UINT value);

        /**
        * Gets the interline value in centimeters
        *@return the interline value in centimeters
        */
        virtual inline const double GetInterLine() const;

        /**
        * Sets the interline value in centimeters
        *@param value - the interline value in centimeters
        */
        virtual inline void SetInterLine(double value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        double m_Hanging;
        double m_InterLine;
        UINT   m_HangingLines;
};

//---------------------------------------------------------------------------
// PSS_PLFNBoundText
//---------------------------------------------------------------------------
UINT PSS_PLFNBoundText::GetRightSubMenu() const
{
    return g_BoundTextRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNBoundText::GetPropertyTabs() const
{
    return (PropertyGeneralBoundTextPage | PropertySizePage | PropertyBoundTextPage);
}
//---------------------------------------------------------------------------
const double PSS_PLFNBoundText::GetHanging() const
{
    return m_Hanging;
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::SetHanging(double value)
{
    m_Hanging = value;
}
//---------------------------------------------------------------------------
const UINT PSS_PLFNBoundText::GetHangingLines() const
{
    return m_HangingLines;
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::SetHangingLines(UINT value)
{
    m_HangingLines = value;
}
//---------------------------------------------------------------------------
const double PSS_PLFNBoundText::GetInterLine() const
{
    return m_InterLine;
}
//---------------------------------------------------------------------------
void PSS_PLFNBoundText::SetInterLine(double value)
{
    m_InterLine = value;
}
//---------------------------------------------------------------------------

#endif
