/****************************************************************************
 * ==> PSS_FontManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a font manager                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FontManagerH
#define PSS_FontManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_FontManager
    #define PSS_FontManager ZAFontManager
#endif

// processsoft
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

/**
* User created font manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FontManager : public CObject
{
    DECLARE_SERIAL(PSS_FontManager)

    public:
        typedef CObject inherited;

        PSS_FontManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FontManager(const PSS_FontManager& other);

        virtual ~PSS_FontManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FontManager& operator = (const PSS_FontManager& other);

        /**
        * Adds a font
        *@param pFont - font to add
        *@return the newly added font handle, g_NoFontDefined on error
        */
        virtual inline PSS_Font::FontHandle AddFont(PSS_Font* pFont);

        /**
        * Removes a font
        *@param hFont - font handle to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFont(PSS_Font::FontHandle hFont);

        /**
        * Searches a font
        *@param pLogFont - logical font
        *@param color - color
        *@return the font handle, g_NoFontDefined if not found or on error
        */
        virtual PSS_Font::FontHandle SearchFont(LOGFONT* pLogFont, COLORREF color);

        /**
        * Searches a font
        *@param pFont - font to search
        *@return the font handle, g_NoFontDefined if not found or on error
        */
        virtual PSS_Font::FontHandle SearchFont(PSS_Font* pFont);

        /**
        * Gets a font matching with a handle
        *@param hFont - font handle
        *@return the font, NULL if not found or on error
        */
        virtual inline PSS_Font* GetFont(PSS_Font::FontHandle hFont);

        /**
        * Gets the font count
        *@return the font count
        */
        virtual inline std::size_t GetCount();

        /**
        * Takes an initial font and rotate it by the specified angle
        *@param hFont - font handle
        *@param angle - rotation angle in degrees
        *@return the rotated font handle, g_NoFontDefined on error
        */
        virtual PSS_Font::FontHandle RotateFont(PSS_Font::FontHandle hFont, int angle);

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
        CObArray m_FontArray;
};

//---------------------------------------------------------------------------
// PSS_FontManager
//---------------------------------------------------------------------------
PSS_Font::FontHandle PSS_FontManager::AddFont(PSS_Font* pFont)
{
    if (!pFont)
        return g_NoFontDefined;

    pFont->SetFontHandle(m_FontArray.Add(pFont));
    
    return pFont->GetFontHandle();
}
//---------------------------------------------------------------------------
PSS_Font* PSS_FontManager::GetFont(PSS_Font::FontHandle hFont)
{
    return (hFont == g_NoFontDefined || hFont >= m_FontArray.GetSize() ? NULL : (PSS_Font*)(m_FontArray[int(hFont)]));
}
//---------------------------------------------------------------------------
std::size_t PSS_FontManager::GetCount()
{
    return m_FontArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
