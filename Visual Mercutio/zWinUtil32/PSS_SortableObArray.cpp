/****************************************************************************
 * ==> PSS_SortableObArray -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a sortable (and typed sortable) object array      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SortableObArray.h"

 //---------------------------------------------------------------------------
 // Global defines
 //---------------------------------------------------------------------------
#define M_Stride_Factor 3
 //---------------------------------------------------------------------------
 // PSS_SortableObArray
 //---------------------------------------------------------------------------
void PSS_SortableObArray::Sort(int(*CompareFunc)(CObject* pFirst, CObject* pSecond))
{
    ASSERT_VALID(this);

    BOOL     found;
    int      elements             = GetSize();
    int      inner, outer, stride = 1;
    CObject* pTmp;

    while (stride <= elements)
        stride *= M_Stride_Factor + 1;
    
    while (stride > (M_Stride_Factor - 1))
    {
        stride /= M_Stride_Factor;

        for (outer = stride; outer < elements; ++outer)
        {
            found = false;
            inner = outer - stride;

            while ((inner >= 0) && !found)
                if (CompareFunc(m_pData[inner + stride], m_pData[inner]) < 0)
                {
                    pTmp                     = m_pData[inner + stride];
                    m_pData[inner + stride]  = m_pData[inner];
                    m_pData[inner]           = pTmp;
                    inner                   -= stride;
                }
                else
                    found = true;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SortableObArray::Sort(int startPos, int elements, int(*CompareFunc)(CObject* pFirst, CObject* pSecond))
{
    // this variation allows to sort only a portion of the array
    ASSERT_VALID(this);
    PSS_Assert(startPos >= 0 && startPos <= GetUpperBound());
    PSS_Assert(GetSize() - startPos >= elements);

    BOOL      found;
    int       inner, outer, stride = 1;
    CObject*  pTmp;
    CObject** pData = &m_pData[startPos];

    while (stride <= elements)
        stride *= M_Stride_Factor + 1;

    while (stride > (M_Stride_Factor - 1))
    {
        stride /= M_Stride_Factor;

        for (outer = stride; outer < elements; ++outer)
        {
            found = false;
            inner = outer - stride;

            while ((inner >= 0) && !found)
                if (CompareFunc(pData[inner + stride], pData[inner]) < 0)
                {
                    pTmp                   = pData[inner + stride];
                    pData[inner + stride]  = pData[inner];
                    pData[inner]           = pTmp;
                    inner                 -= stride;
                }
                else
                    found = true;
        }
    }
}
//---------------------------------------------------------------------------
