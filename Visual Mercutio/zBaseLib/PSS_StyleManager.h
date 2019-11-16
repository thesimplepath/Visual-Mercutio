/****************************************************************************
 * ==> PSS_StyleManager ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a style manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef ZAStylMg_h
#define ZAStylMg_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_StyleManager
    #define PSS_StyleManager ZAStyleManager
#endif

// processsoft
#include "PSS_Style.h"
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
* Style manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StyleManager : public CObject
{
    DECLARE_SERIAL(PSS_StyleManager)

    public:
        typedef CObject inherited;

        PSS_StyleManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_StyleManager(const PSS_StyleManager& other);

        virtual ~PSS_StyleManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_StyleManager& operator = (const PSS_StyleManager& other);

        /**
        * Adds a new style
        *@param pStyle - the style to add
        *@return the added style handle
        */
        virtual PSS_Style::Handle AddStyle(PSS_Style* pStyle);

        /**
        * Removes a specific style from the manager
        *@param hStyle - style handle to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveStyle(PSS_Style::Handle hStyle);

        /**
        * Searches a specific font from its name
        *@param name - font name to search
        *@return font handle, g_NoStyleDefined if not found or on error
        */
        virtual PSS_Style::Handle SearchStyle(const CString& name);

        /**
        * Get the style
        *@param hStyle - style handle to search
        *@return the style, NULL if not found or on error
        */
        virtual inline PSS_Style* GetStyle(PSS_Style::Handle hStyle);

        /**
        * Get the style at index
        *@param index - style index
        *@return the style, NULL if not found or on error
        */
        virtual inline PSS_Style* GetStyleAt(int index);

        /**
        * Gets the style count
        *@return the style count
        */
        virtual inline std::size_t GetCount();

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
        CObArray m_StyleArray;
};

//---------------------------------------------------------------------------
// PSS_StyleManager
//---------------------------------------------------------------------------
PSS_Style* PSS_StyleManager::GetStyle(PSS_Style::Handle hStyle)
{
    return (hStyle == g_NoStyleDefined || hStyle >= m_StyleArray.GetSize() ? NULL : (PSS_Style*)m_StyleArray[int(hStyle)]);
}
//---------------------------------------------------------------------------
PSS_Style* PSS_StyleManager::GetStyleAt(int index)
{
    return (index == g_NoStyleDefined || index >= m_StyleArray.GetSize() ? NULL : (PSS_Style*)m_StyleArray[int(index)]);
}
//---------------------------------------------------------------------------
std::size_t PSS_StyleManager::GetCount()
{
    return m_StyleArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
