// PLFNBackImage.h: interface for the PLFNBackImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLFNBACKIMAGE_H__9E7EF5E5_0BDA_4534_8016_BDC9AD35F5C0__INCLUDED_)
#define AFX_PLFNBACKIMAGE_H__9E7EF5E5_0BDA_4534_8016_BDC9AD35F5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "ZABitmap.h"


//## begin module%3378993C0104.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS PLFNBackImage : public PLFNBitmap  
{
public:
// Inherited feature
    typedef PLFNBitmap inherited;
    virtual UINT GetRightSubMenu() const { return g_ObjectRightSubMenu; };

public:
    PLFNBackImage();
    virtual ~PLFNBackImage();

    PLFNBackImage(const PLFNBackImage &right);

    const PLFNBackImage & operator=(const PLFNBackImage &right);
    //    A copy constructor with a pointer.
    const PLFNBackImage& operator = (const PLFNBackImage* right);

    //    Make a clone of the object.
    virtual PlanFinObject* Clone ();

    virtual void CopyObject (PlanFinObject* pSrc);

    virtual BOOL IsHint(CPoint& point) const;

// Implementation
protected:
    DECLARE_SERIAL(PLFNBackImage)

};


// Can't be selected
inline BOOL PLFNBackImage::IsHint(CPoint& point) const
{
    return FALSE;
}

#endif // !defined(AFX_PLFNBACKIMAGE_H__9E7EF5E5_0BDA_4534_8016_BDC9AD35F5C0__INCLUDED_)
