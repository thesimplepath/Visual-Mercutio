/****************************************************************************
 * ==> PSS_PaintResources --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a paint resources helper class                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PaintResourcesH
#define PSS_PaintResourcesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Paint resources helper class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PaintResources
{
    public:
        PSS_PaintResources();
        virtual ~PSS_PaintResources();

        /**
        * Initializes all the paint resources
        */
        static void Initialize();

        /**
        * Gets the system font
        *@return the system font
        */
        static inline CFont& GetSystemFont();

        /**
        * Gets the small system font
        *@return the small system font
        */
        static inline CFont& GetSmallSystemFont();

        /**
        * Gets the black pen
        *@return the black pen
        */
        static inline CPen& GetBlackPen();

        /**
        * Gets the white pen
        *@return the white pen
        */
        static inline CPen& GetWhitePen();

        /**
        * Gets the blue pen
        *@return the blue pen
        */
        static inline CPen& GetBluePen();

        /**
        * Gets the gray pen
        *@return the gray pen
        */
        static inline CPen& GetGrayPen();

        /**
        * Gets the yellow pen
        *@return the yellow pen
        */
        static inline CPen& GetYellowPen();

        /**
        * Gets the green pen
        *@return the green pen
        */
        static inline CPen& GetGreenPen();

        /**
        * Gets the red pen
        *@return the red pen
        */
        static inline CPen& GetRedPen();

        /**
        * Gets the white brush
        *@return the white brush
        */
        static inline CBrush& GetWhiteBrush();

        /**
        * Gets the light blue brush
        *@return the light blue brush
        */
        static inline CBrush& GetLtBlueBrush();

        /**
        * Gets the red brush
        *@return the red brush
        */
        static inline CBrush& GetRedBrush();

        /**
        * Gets the black brush
        *@return the black brush
        */
        static inline CBrush& GetBlackBrush();

        /**
        * Gets the gray brush
        *@return the gray brush
        */
        static inline CBrush& GetGrayBrush();

        /**
        * Gets the blue brush
        *@return the blue brush
        */
        static inline CBrush& GetBlueBrush();

    private:
        static CFont  m_SystemFont;
        static CFont  m_SmallSystemFont;
        static CPen   m_BlackPen;
        static CPen   m_WhitePen;
        static CPen   m_BluePen;
        static CPen   m_GrayPen;
        static CPen   m_YellowPen;
        static CPen   m_GreenPen;
        static CPen   m_RedPen;
        static CBrush m_WhiteBrush;
        static CBrush m_LtBlueBrush;
        static CBrush m_RedBrush;
        static CBrush m_BlackBrush;
        static CBrush m_GrayBrush;
        static CBrush m_BlueBrush;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PaintResources(const PSS_PaintResources& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PaintResources& operator = (const PSS_PaintResources& other);
};

//---------------------------------------------------------------------------
// PSS_PaintResources
//---------------------------------------------------------------------------
CFont& PSS_PaintResources::GetSystemFont()
{
    return m_SystemFont;
}
//---------------------------------------------------------------------------
CFont& PSS_PaintResources::GetSmallSystemFont()
{
    return m_SmallSystemFont;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetBlackPen()
{
    return m_BlackPen;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetWhitePen()
{
    return m_WhitePen;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetBluePen()
{
    return m_BluePen;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetGrayPen()
{
    return m_GrayPen;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetYellowPen()
{
    return m_YellowPen;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetGreenPen()
{
    return m_GreenPen;
}
//---------------------------------------------------------------------------
CPen& PSS_PaintResources::GetRedPen()
{
    return m_RedPen;
}
//---------------------------------------------------------------------------
CBrush& PSS_PaintResources::GetWhiteBrush()
{
    return m_WhiteBrush;
}
//---------------------------------------------------------------------------
CBrush& PSS_PaintResources::GetLtBlueBrush()
{
    return m_LtBlueBrush;
}
//---------------------------------------------------------------------------
CBrush& PSS_PaintResources::GetRedBrush()
{
    return m_RedBrush;
}
//---------------------------------------------------------------------------
CBrush& PSS_PaintResources::GetBlackBrush()
{
    return m_BlackBrush;
}
//---------------------------------------------------------------------------
CBrush& PSS_PaintResources::GetGrayBrush()
{
    return m_GrayBrush;
}
//---------------------------------------------------------------------------
CBrush& PSS_PaintResources::GetBlueBrush()
{
    return m_BlueBrush;
}
//---------------------------------------------------------------------------

#endif
