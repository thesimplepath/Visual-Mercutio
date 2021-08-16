/****************************************************************************
 * ==> PSS_MathHelper ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a math helper                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MathHelperH
#define PSS_MathHelperH

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
* Vector 2D
*@author Dominique Aigroz, Jean-Milost Reymond
*/
struct AFX_EXT_CLASS PSS_Vector2D
{
    float m_X;
    float m_Y;

    inline PSS_Vector2D();

    /**
    * Constructror
    *@param x - x coordinate
    *@param y - y coordinate
    */
    inline PSS_Vector2D(float x, float y);

    /**
    * Normalizes the vector
    *@return the normalized vector
    */
    inline PSS_Vector2D Normalize() const;

    /**
    * Gets the dot product
    *@param other - other vector to dot with
    *@return the dot product
    */
    inline float Dot(const PSS_Vector2D& other) const;
};

//---------------------------------------------------------------------------
// PSS_Vector2D
//---------------------------------------------------------------------------
PSS_Vector2D::PSS_Vector2D() :
    m_X(0.0f),
    m_Y(0.0f)
{}
//---------------------------------------------------------------------------
PSS_Vector2D::PSS_Vector2D(float x, float y) :
    m_X(x),
    m_Y(y)
{}
//---------------------------------------------------------------------------
PSS_Vector2D PSS_Vector2D::Normalize() const
{
    const float n = sqrtf((m_X * m_X) + (m_Y * m_Y));

    if (!n)
        return PSS_Vector2D();

    return PSS_Vector2D(m_X / n, m_Y / n);
}
//---------------------------------------------------------------------------
float PSS_Vector2D::Dot(const PSS_Vector2D& other) const
{
    return ((m_X * other.m_X) + (m_Y * other.m_Y));
}
//---------------------------------------------------------------------------

/**
* Geometric triangle
*@author Dominique Aigroz, Jean-Milost Reymond
*/
struct AFX_EXT_CLASS PSS_Triangle
{
    PSS_Vector2D m_Vertices[3];

    inline PSS_Triangle();

    /**
    * Constructor
    *@param v1x - first vertex x coordinate
    *@param v1y - first vertex y coordinate
    *@param v2x - second vertex x coordinate
    *@param v2y - second vertex y coordinate
    *@param v3x - third vertex x coordinate
    *@param v3y - third vertex y coordinate
    */
    inline PSS_Triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);

    /**
    * Constructor
    *@param v1 - first vertex
    *@param v2 - second vertex
    *@param v3 - third vertex
    */
    inline PSS_Triangle(const PSS_Vector2D& v1, const PSS_Vector2D& v2, const PSS_Vector2D& v3);
};

//---------------------------------------------------------------------------
// PSS_Triangle
//---------------------------------------------------------------------------
PSS_Triangle::PSS_Triangle()
{}
//---------------------------------------------------------------------------
PSS_Triangle::PSS_Triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y)
{
    m_Vertices[0] = PSS_Vector2D(v1x, v1y);
    m_Vertices[1] = PSS_Vector2D(v2x, v2y);
    m_Vertices[2] = PSS_Vector2D(v3x, v3y);
}
//---------------------------------------------------------------------------
PSS_Triangle::PSS_Triangle(const PSS_Vector2D& v1, const PSS_Vector2D& v2, const PSS_Vector2D& v3)
{
    m_Vertices[0] = v1;
    m_Vertices[1] = v2;
    m_Vertices[2] = v3;
}
//---------------------------------------------------------------------------

/**
* Math helper
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MathHelper
{
    public:
        PSS_MathHelper();
        virtual ~PSS_MathHelper();

        /**
        * Checks if the point is inside the triangle
        *@param triangle - the triangle to check
        *@param point - the point to check against
        *@return true if the point is inside the triangle, otherwise false
        */
        static bool Inside(const PSS_Triangle& triangle, const PSS_Vector2D& point);

        /**
        * Clamps a value between a min and max range (in a such manner that minVal >= value >= maxVal)
        *@param value - value to clamp
        *@param minVal - min value
        *@param maxVal - max value
        *@return clamped value
        */
        template <class T>
        static T Clamp(T value, T minVal, T maxVal);
};

//---------------------------------------------------------------------------
// PSS_MathHelper
//---------------------------------------------------------------------------
template <class T>
T PSS_MathHelper::Clamp(T value, T minVal, T maxVal)
{
    return min(max(value, minVal), maxVal);
}
//---------------------------------------------------------------------------

#endif
