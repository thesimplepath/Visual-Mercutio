/****************************************************************************
 * ==> PSS_MathHelper ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a math helper                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MathHelper.h"

//---------------------------------------------------------------------------
// PSS_MathHelper
//---------------------------------------------------------------------------
PSS_MathHelper::PSS_MathHelper()
{}
//---------------------------------------------------------------------------
PSS_MathHelper::~PSS_MathHelper()
{}
//---------------------------------------------------------------------------
bool PSS_MathHelper::Inside(const PSS_Triangle& triangle, const PSS_Vector2D& point)
{
    // calculate vectors from each triangle vertices to point
    const PSS_Vector2D pToV1(triangle.m_Vertices[0].m_X - point.m_X, triangle.m_Vertices[0].m_Y - point.m_Y);
    const PSS_Vector2D pToV2(triangle.m_Vertices[1].m_X - point.m_X, triangle.m_Vertices[1].m_Y - point.m_Y);
    const PSS_Vector2D pToV3(triangle.m_Vertices[2].m_X - point.m_X, triangle.m_Vertices[2].m_Y - point.m_Y);

    // normalize the point-to-vertex vectors
    const PSS_Vector2D normalizedPToV1 = pToV1.Normalize();
    const PSS_Vector2D normalizedPToV2 = pToV2.Normalize();
    const PSS_Vector2D normalizedPToV3 = pToV3.Normalize();

    // calculate the dot product of each point-to-vertex vectors. Also manage the rounding errors (to avoid to get
    // e.g 1.0000000000000000000001f as result, which may cause the acosf function to fail later)
    const float a1 = Clamp(normalizedPToV1.Dot(normalizedPToV2), -1.0f, 1.0f);
    const float a2 = Clamp(normalizedPToV2.Dot(normalizedPToV3), -1.0f, 1.0f);
    const float a3 = Clamp(normalizedPToV3.Dot(normalizedPToV1), -1.0f, 1.0f);

    // calculate the total angle. If its value is equals to 360°, then the point is inside the triangle
    return ((std::acosf(a1) + std::acosf(a2) + std::acosf(a3)) >= 6.28f);
}
//---------------------------------------------------------------------------
