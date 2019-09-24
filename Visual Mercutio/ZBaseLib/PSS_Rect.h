/****************************************************************************
 * ==> PSS_Rect ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rectangle                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RectH
#define PSS_RectH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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

/**
* Rectangle
*@note This class is used to provide a compatibility between 16 bit and 32 bit generated serialized files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Rect : public CRect
{
    public:
        typedef CRect inherited;

        PSS_Rect();

        /**
        * Constructor
        *@param l - left
        *@param t - top
        *@param r - right
        *@param b - bottom
        */
        inline PSS_Rect(int l, int t, int r, int b);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Rect(CRect& other);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Rect(PSS_Rect& other);

        virtual ~PSS_Rect();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline const PSS_Rect& operator = (const CRect& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline const PSS_Rect& operator = (const PSS_Rect& other);

        /**
        * Stores from the archive to the rect
        *@param ar - archive
        *@param rect - rect
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_Rect& rect);

        /**
        * Stores the rect to the archive
        *@param ar - archive
        *@param rect - rect
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_Rect& rect);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);
};

//---------------------------------------------------------------------------
// PSS_Rect
//---------------------------------------------------------------------------
inline PSS_Rect::PSS_Rect(int l, int t, int r, int b) :
    CRect(l, t, r, b)
{}
//---------------------------------------------------------------------------
PSS_Rect::PSS_Rect(CRect& other) :
    CRect(other.left, other.top, other.right, other.bottom)
{}
//---------------------------------------------------------------------------
PSS_Rect::PSS_Rect(PSS_Rect& other) :
    CRect(other.left, other.top, other.right, other.bottom)
{}
//---------------------------------------------------------------------------
const PSS_Rect& PSS_Rect::operator = (const CRect& other)
{
    CRect::operator = ((CRect&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_Rect& PSS_Rect::operator = (const PSS_Rect& other)
{
    CRect::operator = ((CRect&)other);
    return *this;
}
//---------------------------------------------------------------------------

#endif
