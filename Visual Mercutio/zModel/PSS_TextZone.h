/****************************************************************************
 * ==> PSS_TextZone --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a text zone                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TextZoneH
#define PSS_TextZoneH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_TextZone
    #define PSS_TextZone ZBTextZone
#endif

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_TextZoneColor RGB(255, 222, 159)
//---------------------------------------------------------------------------

/**
* Text zone
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TextZone : public CODTextComponent
{
    DECLARE_SERIAL(PSS_TextZone)

    public:
        PSS_TextZone();
        virtual ~PSS_TextZone();

        /**
        * Initializes the style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeStyle();

        /**
        * Sets the line color
        *@param value - the line color
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLineColor(COLORREF value = RGB(0, 0, 0));

        /**
        * Sets if the line is transparent
        *@param value - if TRUE, the line is transparent
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLineTransparent(BOOL value = FALSE);

        /**
        * Sets the line width
        *@param value - the line width
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLineWidth(int value = 1);

        /**
        * Sets the line style
        *@param value - the line style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLineStyle(int value = PS_SOLID);

        /**
        * Sets the fill color
        *@param value - the fill color
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFillColor(COLORREF value = RGB(255, 255, 255));

        /**
        * Sets if fill is transparent
        *@param value - if TRUE, the fill is transparent
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFillTransparent(BOOL value = FALSE);

        /**
        * Sets the fill style
        *@param value - the fill style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFillStyle(int value = BS_SOLID);

        /**
        * Sets the fill hatch
        *@param value - the fill hatch
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFillHatch(int value = HS_BDIAGONAL);

        /**
        * Sets the fill background mode
        *@param value - the fill background mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFillBackgroundMode(int value = TRANSPARENT);

        /**
        * Sets the fill background color
        *@param value - the fill background color
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFillBackgroundColor(COLORREF value = RGB(255, 255, 255));

        /**
        * Sets the font
        *@param value - the font family name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFont(const CString& value = _T("Arial"));

        /**
        * Sets the font color
        *@param value - the font color
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFontColor(COLORREF value = RGB(0, 0, 0));

        /**
        * Sets the font size
        *@param value - the font size
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFontSize(int value = 10);

        /**
        * Sets the font height
        *@param value - the font height
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFontHeight(int value = 10);

        /**
        * Sets the font weight
        *@param value - the font weight
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFontWeight(int value = FW_NORMAL);

        /**
        * Sets if the text should be shown in italic
        *@param value - if TRUE, the text should be shown in italic
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetItalic(BOOL value = FALSE);

        /**
        * Sets if the text should be underlined
        *@param value - if TRUE, the text should underlined
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetUnderline(BOOL value = FALSE);

        /**
        * Sets if the text should be striked out
        *@param value - if TRUE, the text should be striked out
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetStrikeout(BOOL value = FALSE);

        /**
        * Sets if the text may be shown on several lines
        *@param value - if TRUE, the text may be shown on several lines
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetMultiline(BOOL value = FALSE);

        /**
        * Sets if the word break may be used to show the text
        *@param value - if TRUE, the word break may be used to show the text
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetUseWordbreak(BOOL value = FALSE);

        /**
        * Sets the horizontal alignment
        *@param value - the horizontal alignment
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetHorizontalAlignement(int value = DT_CENTER);

        /**
        * Sets the vertical alignment
        *@param value - the vertical alignment
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetVerticalAlignement(int value = DT_VCENTER);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);
};

#endif
