/****************************************************************************
 * ==> PSS_Point -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a point                                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef ZBPoint_h
#define ZBPoint_h 1

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
* Point
*@author Dominique Aigroz, Jean-Milost Reymond
*@note This class is used to provide a compatibility between 16 bit and 32 bit generated serialized files
*/
class AFX_EXT_CLASS PSS_Point : public CPoint
{
    public:
        typedef CPoint inherited;

        PSS_Point();

        /**
        * Constructor
        *@param x - x coordinate
        *@param y - y coordinate
        */
        inline PSS_Point(int x, int y);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Point(CPoint& other);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Point(PSS_Point& other);

        virtual ~PSS_Point();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline const PSS_Point& operator = (const CPoint& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline const PSS_Point& operator = (const PSS_Point& other);

        /**
        * Stores from the archive to the point
        *@param ar - archive
        *@param point - point
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_Point& point);

        /**
        * Stores the point to the archive
        *@param ar - archive
        *@param point - point
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_Point& point);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);
};

//---------------------------------------------------------------------------
// PSS_Point
//---------------------------------------------------------------------------
PSS_Point::PSS_Point(int x, int y) :
    CPoint(x, y)
{}
//---------------------------------------------------------------------------
PSS_Point::PSS_Point(CPoint& other) :
    CPoint(other.x, other.y)
{}
//---------------------------------------------------------------------------
PSS_Point::PSS_Point(PSS_Point& other) :
    CPoint(other.x, other.y)
{}
//---------------------------------------------------------------------------
const PSS_Point& PSS_Point::operator = (const CPoint& other)
{
    CPoint::operator = ((CPoint&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_Point & PSS_Point::operator = (const PSS_Point &other)
{
    CPoint::operator = ((CPoint&)other);
    return *this;
}
//---------------------------------------------------------------------------

#endif
