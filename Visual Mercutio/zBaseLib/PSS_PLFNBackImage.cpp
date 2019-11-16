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
IMPLEMENT_SERIAL(PSS_PLFNBackImage, PSS_PLFNBitmap, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNBackImage
//---------------------------------------------------------------------------
PSS_PLFNBackImage::PSS_PLFNBackImage() :
    PSS_PLFNBitmap()
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
    PSS_PLFNBitmap::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNBackImage& PSS_PLFNBackImage::operator = (const PSS_PLFNBackImage* pOther)
{
    PSS_PLFNBitmap::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNBackImage::Clone() const
{
    return new PSS_PLFNBackImage(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNBackImage::CopyObject(PSS_PlanFinObject* pSrc)
{
    this->PSS_PLFNBackImage::operator = ((PSS_PLFNBackImage*)pSrc);
}
//---------------------------------------------------------------------------
