/****************************************************************************
 * ==> PSS_Style -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a style                                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StyleH
#define PSS_StyleH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <cstdint>

// mfc
#include "Mfc.h"

// processsoft
#include "PSS_Border.h"
#include "PSS_Font.h"

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
const std::intptr_t g_NormalStyle    =  0;
const std::intptr_t g_NoStyleDefined = -1;
//---------------------------------------------------------------------------

/**
* Style
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Style : public CObject
{
    DECLARE_SERIAL(PSS_Style)

    public:
        typedef std::intptr_t Handle;
        typedef CObject       inherited;

        PSS_Style();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Style(const PSS_Style &right);

        virtual ~PSS_Style();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Style& operator = (const PSS_Style& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_Style* Clone() const;

        /**
        * Checks if the style has a border
        *@return TRUE if the style has a border, otherwise FALSE
        */
        virtual inline BOOL HasBorder() const;

        /**
        * Gets the font handle
        *@return the font handle
        */
        virtual inline const PSS_Font::Handle GetFontHandle() const;

        /**
        * Sets the font handle
        *@param hFont - the font handle
        */
        virtual inline void SetFontHandle(PSS_Font::Handle hFont);

        /**
        * Gets the back color
        *@return the back color, -1 if none
        */
        virtual inline const COLORREF GetBackColor() const;

        /**
        * Sets the back color
        *@param value - the back color, -1 for none
        */
        virtual inline void SetBackColor(COLORREF value);

        /**
        * Gets the style handle
        *@return the style handle
        */
        virtual inline const Handle GetStyleHandle() const;

        /**
        * Sets the style handle
        *@param hStyle - the style handle
        */
        virtual inline void SetStyleHandle(Handle hStyle);

        /**
        * Gets the style name
        *@return the style name
        */
        virtual inline const CString GetStyleName() const;

        /**
        * Sets the style name
        *@param value - the style name
        */
        virtual inline void SetStyleName(const CString& value);

        /**
        * Gets the field border
        *@return the field border
        */
        virtual inline PSS_Border* GetBorder();

        /**
        * Sets the field border
        *@param pBorder - the field border
        */
        virtual inline void SetBorder(PSS_Border* pBorder);

        /**
        * Gets the justification
        *@return the justification
        */
        virtual inline const UINT GetJustify() const;

        /**
        * Sets the justification
        *@param value - the justification
        */
        virtual inline void SetJustify(UINT value);

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
        Handle           m_hStyle;
        PSS_Font::Handle m_hFont;
        PSS_Border*      m_pBorder;
        COLORREF         m_BackColor;
        CString          m_StyleName;
        UINT             m_Justify;
};

//---------------------------------------------------------------------------
// PSS_Style
//---------------------------------------------------------------------------
BOOL PSS_Style::HasBorder() const
{
    return (m_pBorder != NULL);
}
//---------------------------------------------------------------------------
const PSS_Font::Handle PSS_Style::GetFontHandle() const
{
    return m_hFont;
}
//---------------------------------------------------------------------------
void PSS_Style::SetFontHandle(PSS_Font::Handle value)
{
    m_hFont = value;
}
//---------------------------------------------------------------------------
const COLORREF PSS_Style::GetBackColor() const
{
    return m_BackColor;
}
//---------------------------------------------------------------------------
void PSS_Style::SetBackColor(COLORREF value)
{
    m_BackColor = value;
}
//---------------------------------------------------------------------------
const PSS_Style::Handle PSS_Style::GetStyleHandle() const
{
    return m_hStyle;
}
//---------------------------------------------------------------------------
void PSS_Style::SetStyleHandle(Handle value)
{
    m_hStyle = value;
}
//---------------------------------------------------------------------------
const CString PSS_Style::GetStyleName() const
{
    return m_StyleName;
}
//---------------------------------------------------------------------------
void PSS_Style::SetStyleName(const CString& value)
{
    m_StyleName = value;
}
//---------------------------------------------------------------------------
PSS_Border* PSS_Style::GetBorder()
{
    return m_pBorder;
}
//---------------------------------------------------------------------------
void PSS_Style::SetBorder(PSS_Border* pBorder)
{
    m_pBorder = pBorder;
}
//---------------------------------------------------------------------------
const UINT PSS_Style::GetJustify() const
{
    return m_Justify;
}
//---------------------------------------------------------------------------
void PSS_Style::SetJustify(UINT value)
{
    m_Justify = value;
}
//---------------------------------------------------------------------------

#endif
