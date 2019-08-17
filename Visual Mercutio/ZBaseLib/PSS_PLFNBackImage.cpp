/****************************************************************************
 * ==> PSS_PLFNBackImage ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan background image                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PLFNBackImage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNBackImage, PLFNBitmap, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNBackImage
//---------------------------------------------------------------------------
PSS_PLFNBackImage::PSS_PLFNBackImage() :
    PLFNBitmap()
{}
//---------------------------------------------------------------------------
PSS_PLFNBackImage::~PSS_PLFNBackImage()
{}
//---------------------------------------------------------------------------
PSS_PLFNBackImage::PSS_PLFNBackImage(const PSS_PLFNBackImage& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
const PSS_PLFNBackImage& PSS_PLFNBackImage::operator = (const PSS_PLFNBackImage& other)
{
    PLFNBitmap::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNBackImage& PSS_PLFNBackImage::operator = (const PSS_PLFNBackImage* pOther)
{
    PLFNBitmap::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNBackImage::Clone() const
{
    std::unique_ptr<PSS_PLFNBackImage> pObject(new PSS_PLFNBackImage(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNBackImage::CopyObject(PlanFinObject* pSrc)
{
    this->PSS_PLFNBackImage::operator = ((PSS_PLFNBackImage*)pSrc);
}
//---------------------------------------------------------------------------
