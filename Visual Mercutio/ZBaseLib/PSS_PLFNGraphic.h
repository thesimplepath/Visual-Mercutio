/****************************************************************************
 * ==> PSS_PLFNGraphic -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan graphical object                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNGraphicH
#define PSS_PLFNGraphicH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNGraphic
    #define PSS_PLFNGraphic PLFNGraphic
#endif

// processsoft
#include "ZAObject.h"

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
* Financial plan graphical object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNGraphic : public PlanFinObject
{
    DECLARE_SERIAL(PSS_PLFNGraphic)

public:
    typedef PlanFinObject inherited;

    PSS_PLFNGraphic();

    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    PSS_PLFNGraphic(const PSS_PLFNGraphic& other);

    virtual ~PSS_PLFNGraphic();

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    const PSS_PLFNGraphic& operator = (const PSS_PLFNGraphic& other);

    /**
    * Copy operator
    *@param pOther - other object to copy from
    *@return copy of itself
    */
    const PSS_PLFNGraphic& operator = (const PSS_PLFNGraphic* pOther);

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
    * Gets the graphic brush
    *@param[in, out] brush - brush
    *@return the passed brush
    */
    virtual CBrush& GetGraphicBrush(CBrush& brush) const;

    /**
    * Gets the graphic pen
    *@param[in, out] pen - pen
    *@return the passed pen
    */
    virtual CPen& GetGraphicPen(CPen& pen) const;

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
    * Gets the graphic color
    *@return the graphic color
    */
    virtual inline const COLORREF GetGraphicColor() const;

    /**
    * Sets the graphic color
    *@param value - the graphic color
    */
    virtual inline void SetGraphicColor(COLORREF value);

    /**
    * Gets the graphic width
    *@return the graphic width
    */
    virtual inline const WORD GetGraphicWidth() const;

    /**
    * Sets the graphic width
    *@param value - the graphic width
    */
    virtual inline void SetGraphicWidth(WORD value);

    /**
    * Gets if the graphic has a shadow
    *@return TRUE if the graphic has a shadow, otherwise FALSE
    */
    virtual inline const BOOL GetShadow() const;

    /**
    * Sets if the graphic has a shadow
    *@param valie - if TRUE, the graphic has a shadow
    */
    virtual inline void SetShadow(BOOL value);

    /**
    * Gets the graphic style
    *@return the graphic style
    */
    virtual inline const WORD GetGraphicStyle() const;

    /**
    * Sets the graphic style
    *@param value - the graphic style
    */
    virtual inline void SetGraphicStyle(WORD value);

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
    COLORREF m_GraphicColor;
    WORD     m_GraphicStyle;
    WORD     m_GraphicWidth;
    BOOL     m_Shadow;
};

//---------------------------------------------------------------------------
// PSS_PLFNGraphic
//---------------------------------------------------------------------------
UINT PSS_PLFNGraphic::GetRightSubMenu() const
{
    return g_GraphicRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNGraphic::GetPropertyTabs() const
{
    return PropertyGeneralBasicPage | PropertySizePage;
}
//---------------------------------------------------------------------------
const COLORREF PSS_PLFNGraphic::GetGraphicColor() const
{
    return m_GraphicColor;
}
//---------------------------------------------------------------------------
void PSS_PLFNGraphic::SetGraphicColor(COLORREF value)
{
    m_GraphicColor = value;
}
//---------------------------------------------------------------------------
const WORD PSS_PLFNGraphic::GetGraphicWidth() const
{
    return m_GraphicWidth;
}
//---------------------------------------------------------------------------
void PSS_PLFNGraphic::SetGraphicWidth(WORD value)
{
    m_GraphicWidth = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNGraphic::GetShadow() const
{
    return m_Shadow;
}
//---------------------------------------------------------------------------
void PSS_PLFNGraphic::SetShadow(BOOL value)
{
    m_Shadow = value;
}
//---------------------------------------------------------------------------
const WORD PSS_PLFNGraphic::GetGraphicStyle() const
{
    return m_GraphicStyle;
}
//---------------------------------------------------------------------------
void PSS_PLFNGraphic::SetGraphicStyle(WORD value)
{
    m_GraphicStyle = value;
}
//---------------------------------------------------------------------------

#endif
