// PLFNBackImage.cpp: implementation of the PLFNBackImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PLFNBackImage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(PLFNBackImage, PLFNBitmap, def_Version)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLFNBackImage::PLFNBackImage()
{

}

PLFNBackImage::~PLFNBackImage()
{

}


PLFNBackImage::PLFNBackImage(const PLFNBackImage &right)
{
    *this = right;
}


const PLFNBackImage & PLFNBackImage::operator=(const PLFNBackImage &right)
{
    this->PLFNBitmap::operator=( (inherited&)right );
    return *this;
}



const PLFNBackImage& PLFNBackImage::operator = (const PLFNBackImage* right)
{
    this->PLFNBitmap::operator=( (inherited*)right );
    return *this;
}

PlanFinObject* PLFNBackImage::Clone ()
{
    PLFNBackImage*    pObject = new PLFNBackImage( *this );
    return pObject;
}

void PLFNBackImage::CopyObject (PlanFinObject* pSrc)
{
    ((PLFNBackImage*)this)->PLFNBackImage::operator=( (PLFNBackImage*)pSrc );
}
