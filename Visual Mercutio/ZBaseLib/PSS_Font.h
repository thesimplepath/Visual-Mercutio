/****************************************************************************
 * ==> PSS_Font ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a font object                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FontH
#define PSS_FontH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Font
    #define PSS_Font ZAFont
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

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const std::intptr_t g_NoFontDefined = -1;
//---------------------------------------------------------------------------

/**
* Font class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Font : public CFont
{
    DECLARE_SERIAL(PSS_Font)

    public:
        typedef std::intptr_t Handle;
        typedef CFont         inherited;

        PSS_Font();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Font(const PSS_Font& other);

        virtual ~PSS_Font();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Font& operator = (const PSS_Font& other);

        /**
        * Creates a font from a LOGFONT and a color
        *@param pLogFont - log font
        *@param col - color
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(LOGFONT* pLogFont, COLORREF col = RGB(0, 0, 0));

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_Font* Clone() const;

        /**
        * Gets the font color
        *@return the font color
        */
        virtual inline COLORREF GetFontColor() const;

        /**
        * Sets the font color
        *@param col - the font color
        */
        virtual inline void SetFontColor(COLORREF col);

        /**
        * Gets the font handle
        *@return the font handle
        */
        virtual inline const Handle GetFontHandle() const;

        /**
        * Sets the font handle
        *@param value - the font handle
        */
        virtual inline void SetFontHandle(Handle value);

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
        Handle   m_hFontNumber;
        COLORREF m_ColFont;
};

//---------------------------------------------------------------------------
// PSS_Font
//---------------------------------------------------------------------------
COLORREF PSS_Font::GetFontColor() const
{
    return m_ColFont;
}
//---------------------------------------------------------------------------
void PSS_Font::SetFontColor(COLORREF col)
{
    m_ColFont = col;
}
//---------------------------------------------------------------------------
const PSS_Font::Handle PSS_Font::GetFontHandle() const
{
    return m_hFontNumber;
}
//---------------------------------------------------------------------------
void PSS_Font::SetFontHandle(Handle value)
{
    m_hFontNumber = value;
}
//---------------------------------------------------------------------------

#endif
