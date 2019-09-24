/****************************************************************************
 * ==> PSS_Rect ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rectangle                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Rect.h"

// processsoft
#include "PSS_BaseDocument.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_Rect
//---------------------------------------------------------------------------
PSS_Rect::PSS_Rect() :
    CRect()
{}
//---------------------------------------------------------------------------
PSS_Rect::~PSS_Rect()
{}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_Rect& rect)
{
    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() <= 12)
    {
        WORD wTemp;
        ar >> wTemp;
        rect.left = int(wTemp);

        ar >> wTemp;
        rect.top = int(wTemp);

        ar >> wTemp;
        rect.right = int(wTemp);

        ar >> wTemp;
        rect.bottom = int(wTemp);
    }
    else
    {
        DWORD dwTemp;
        ar >> dwTemp;
        rect.left = int(dwTemp);

        ar >> dwTemp;
        rect.top = int(dwTemp);

        ar >> dwTemp;
        rect.right = int(dwTemp);

        ar >> dwTemp;
        rect.bottom = int(dwTemp);
    }

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_Rect& rect)
{
    ar << DWORD(rect.left);
    ar << DWORD(rect.top);
    ar << DWORD(rect.right);
    ar << DWORD(rect.bottom);

    return ar;
}
//---------------------------------------------------------------------------
void PSS_Rect::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        // write the elements
        ar << *this;
    else
        // read the elements
        ar >> *this;
}
//---------------------------------------------------------------------------
