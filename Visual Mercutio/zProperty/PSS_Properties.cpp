/****************************************************************************
 * ==> PSS_Properties ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the properties interface                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Properties.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
AFX_EXT_API bool SwapInternalPropertyItem(PSS_Property&                 srcProperty,
                                          PSS_Property&                 dstProperty,
                                          bool                          top2Down,
                                          PSS_Properties::IPropertySet& props,
                                          int                           categoryID)
{
    bool result = false;

    // are the source and destination in the same category?
    if (srcProperty.GetCategoryID() == categoryID && dstProperty.GetCategoryID() == categoryID)
    {
        // move properties from source to destination. Save the source property value 
        const CString srcValue = srcProperty.GetValueString();

        PSS_Properties::IPropertyIterator it(&props);
        PSS_Property*                     pFoundSrc = NULL;

        // iterate through the properties and search for the matching source property
        for (PSS_Property* pProp = (top2Down ? it.GetFirst() : it.GetLast());
             pProp;
             pProp = (top2Down ? it.GetNext() : it.GetPrev()))
        {
            // skip the not matching categories
            if (pProp->GetCategoryID() != categoryID)
                continue;

            // was the source property found?
            if (pProp == &srcProperty)
            {
                pFoundSrc = pProp;
                break;
            }
        }

        // no source found?
        if (!pFoundSrc)
            return false;

        PSS_Property* pPreviousProp = pFoundSrc;
        PSS_Property* pFoundDst     = NULL;

        // from the source until the destination, copy the element to the previous
        for (PSS_Property* pProp = (top2Down ? it.GetNext() : it.GetPrev());
             pProp;
             pProp = (top2Down ? it.GetNext() : it.GetPrev()))
        {
            // skip the not matching categories
            if (pProp->GetCategoryID() != categoryID)
                break;

            // copy the current property value to the previous element
            pPreviousProp->SetValueString(pProp->GetValueString());

            if (pProp == &dstProperty)
            {
                pFoundDst = pProp;
                break;
            }

            // update the previous property pointer
            pPreviousProp = pProp;
        }

        // no destination found?
        if (!pFoundDst)
            return false;

        // copy the droped item saved value
        pFoundDst->SetValueString(srcValue);

        result = true;
    }

    return result;
}
//---------------------------------------------------------------------------
// PSS_Properties
//---------------------------------------------------------------------------
PSS_Properties::PSS_Properties()
{}
//---------------------------------------------------------------------------
PSS_Properties::~PSS_Properties()
{}
//---------------------------------------------------------------------------
