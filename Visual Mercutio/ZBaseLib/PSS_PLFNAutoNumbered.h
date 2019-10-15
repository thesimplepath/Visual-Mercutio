/****************************************************************************
 * ==> PSS_PLFNAutoNumbered ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an financial plan auto-numbered object            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNAutoNumberedH
#define PSS_PLFNAutoNumberedH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNAutoNumbered
    #define PSS_PLFNAutoNumbered PLFNAutoNumbered
#endif

// processsoft
#include "PSS_PlanFinObject.h"
#include "PSS_PlanFinObjects.h"

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
* Financial plan auto-numbered object, it's a header with automatic numeration
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNAutoNumbered : public PSS_PlanFinObject
{
    DECLARE_SERIAL(PSS_PLFNAutoNumbered)

    public:
        typedef PSS_PlanFinObject inherited;

        PSS_PLFNAutoNumbered();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNAutoNumbered(const PSS_PLFNAutoNumbered& other);

        virtual ~PSS_PLFNAutoNumbered();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNAutoNumbered& operator = (const PSS_PLFNAutoNumbered& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNAutoNumbered& operator = (const PSS_PLFNAutoNumbered* pOther);

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
        * Checks if a field is empty
        *@return TRUE if the field is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets a formatted string containing the object attributes
        *@return the formatted string, empty string if object is empty or on error
        */
        virtual CString GetFormattedObject();

        /**
        * Converts a formatted object to numeric, date, string, etc.
        *@param value - value
        *@param locateFormat - if TRUE, format will use the locale
        *@param emptyWhenZero - if TRUE, the field will be emptied if the value is empty
        *@return TRUE if the value has changed, otherwise FALSE
        */
        virtual BOOL ConvertFormattedObject(const CString& value, BOOL locateFormat = TRUE, BOOL emptyWhenZero = FALSE);

        /**
        * Checks if the object is selected
        *@param point - hit point in pixels
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

        /**
        * Gets the text level string
        *@return the text level string
        */
        virtual inline const CString& GetStringTextLevel() const;

        /**
        * Sets the text level string
        *@param text - text level string
        */
        virtual inline void SetStringTextLevel(const CString& text);

        /**
        * Called when the object size and/or position has changed
        */
        virtual void SizePositionHasChanged();

        /**
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the object image unformatted string
        *@return the object image unformatted string
        */
        virtual CString GetUnformattedObject();

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
        * Gets the style handle
        *@return the style handle
        */
        virtual inline const PSS_Style::Handle GetStyle() const;

        /**
        * Sets the style handle
        *@param hStyle - style handle
        *@note After having assigned the handle, remove the font handle, the object color
        *      and the object alignement
        */
        virtual void SetStyle(PSS_Style::Handle hStyle);

        /**
        * Gets the text level
        *@return the text level
        *@note Used to contains the section and paragraph number
        */
        virtual inline PSS_PLFNStatic& GetTextLevel();

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
        * Gets the text offset from the section and paragraph number
        *@return the text offset
        */
        virtual inline const int GetTextOffset() const;

        /**
        * Sets the text offset to the section and paragraph number
        *@param value - the text offset
        */
        virtual inline void SetTextOffset(int value);

        /**
        * Gets if the section and paragraph must be automatically calculated
        *@return TRUE if the section and paragraph must be automatically calculated, otherwise FALSE
        */
        virtual inline const BOOL GetAutoCalculate() const;

        /**
        * Sets if the section and paragraph must be automatically calculated
        *@param value - if TRUE, the section and paragraph will be automatically calculated
        */
        virtual inline void SetAutoCalculate(BOOL value);

        /**
        * Gets the section number
        *@return the section number
        */
        virtual inline const int GetSectionNumber() const;

        /**
        * Sets the section number
        *@param value - the section number
        */
        virtual inline void SetSectionNumber(int value);

        /**
        * Gets the level
        *@return the level
        */
        virtual inline const int GetLevel() const;

        /**
        * Sets the level
        *@param value - the level
        */
        virtual inline void SetLevel(int value);

        /**
        * Gets the object fill color
        *@return the object fill color
        */
        virtual const COLORREF GetFillColor() const;

        /**
        * Sets the object fill color
        *@param value - the object fill color
        */
        virtual void SetFillColor(COLORREF value);

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
        PSS_PLFNStatic     m_TextLevel;
        PSS_PlanFinObject* m_pObject;
        int                m_TextOffset;
        int                m_SectionNumber;
        int                m_Level;
        BOOL               m_AutoCalculate;
};

//---------------------------------------------------------------------------
// PSS_PLFNAutoNumbered
//---------------------------------------------------------------------------
BOOL PSS_PLFNAutoNumbered::IsEmpty() const
{
    if (m_pObject)
        return m_pObject->IsEmpty();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNAutoNumbered::IsSelected(const CPoint& point) const
{
    return(m_ObjectRect.PtInRect(point));
}
//---------------------------------------------------------------------------
const CString& PSS_PLFNAutoNumbered::GetStringTextLevel() const
{
    return m_TextLevel.GetStr();
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetStringTextLevel(const CString& text)
{
    m_TextLevel.SetStr(text);
}
//---------------------------------------------------------------------------
UINT PSS_PLFNAutoNumbered::GetRightSubMenu() const
{
    return g_AutoNumberedRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNAutoNumbered::GetPropertyTabs() const
{
    return (g_PropertyGeneralPage | g_PropertySizePage | g_PropertyNumberedPage);
}
//---------------------------------------------------------------------------
UINT PSS_PLFNAutoNumbered::GetJustify(PSS_Document* pDoc) const
{
    if (m_pObject)
        return m_pObject->GetJustify(pDoc);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetJustify(UINT value)
{
    if (m_pObject)
        m_pObject->SetJustify(value);
}
//---------------------------------------------------------------------------
const PSS_Style::Handle PSS_PLFNAutoNumbered::GetStyle() const
{
    if (m_pObject)
        return m_pObject->GetStyle();

    return GetStyle();
}
//---------------------------------------------------------------------------
PSS_PLFNStatic& PSS_PLFNAutoNumbered::GetTextLevel()
{
    return m_TextLevel;
}
//---------------------------------------------------------------------------
const PSS_PlanFinObject* PSS_PLFNAutoNumbered::GetObject() const
{
    return m_pObject;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetObject(PSS_PlanFinObject* value)
{
    m_pObject = value;
}
//---------------------------------------------------------------------------
const int PSS_PLFNAutoNumbered::GetTextOffset() const
{
    return m_TextOffset;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetTextOffset(int value)
{
    m_TextOffset = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNAutoNumbered::GetAutoCalculate() const
{
    return m_AutoCalculate;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetAutoCalculate(BOOL value)
{
    m_AutoCalculate = value;
}
//---------------------------------------------------------------------------
const int PSS_PLFNAutoNumbered::GetSectionNumber() const
{
    return m_SectionNumber;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetSectionNumber(int value)
{
    m_SectionNumber = value;
}
//---------------------------------------------------------------------------
const int PSS_PLFNAutoNumbered::GetLevel() const
{
    return m_Level;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetLevel(int value)
{
    m_Level = value;
}
//---------------------------------------------------------------------------
const PSS_Font::Handle PSS_PLFNAutoNumbered::GetFont() const
{
    if (m_pObject)
        return m_pObject->GetFont();

    return GetFont();
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetFont(PSS_Font::Handle hFont)
{
    if (m_pObject)
        m_pObject->SetFont(hFont);
}
//---------------------------------------------------------------------------

#endif
