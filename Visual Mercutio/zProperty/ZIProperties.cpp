// ZIProperties.cpp: implementation of the ZIProperties class.

#include "stdafx.h"
#include "ZIProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZIProperties::ZIProperties()
{}

ZIProperties::~ZIProperties()
{}

AFX_EXT_API bool SwapInternalPropertyItem(PSS_Property&        SrcProperty,
                                          PSS_Property&        DstProperty,
                                          bool                Top2Down,
                                          ZBPropertySet&    Properties,
                                          int                CategoryID)
{
    bool RetValue = false;

    // Check if the source and the destination are in the same field and for the text item list
    if (SrcProperty.GetCategoryID() == CategoryID &&
        DstProperty.GetCategoryID() == CategoryID)
    {
        // Move properties from src to destination

        // First, save the source property value 
        CString SrcValue = SrcProperty.GetValueString();

        // Run trough the set of properties and changed find the src for the start
        ZBPropertyIterator i(&Properties);
        PSS_Property* pProp;
        bool FoundSrc = false;

        for (pProp = (Top2Down) ? i.GetFirst() : i.GetLast(); pProp; pProp = (Top2Down) ? i.GetNext() : i.GetPrev())
        {
            // Continue if not the right category
            if (pProp->GetCategoryID() != CategoryID)
            {
                continue;
            }

            // If we found the right source property,
            // break the loop and set the flag
            if (pProp == &SrcProperty)
            {
                FoundSrc = true;
                break;
            }
        }

        // If the source hasn't been reached, then error
        if (!FoundSrc)
        {
            return false;
        }

        // Now, from the source till the destination, copy the element to the previous
        bool FoundDst = false;
        PSS_Property* pPreviousProp = pProp;

        for (pProp = (Top2Down) ? i.GetNext() : i.GetPrev(); pProp; pProp = (Top2Down) ? i.GetNext() : i.GetPrev())
        {
            // If we are not still in the same category
            // then break the loop.
            if (pProp->GetCategoryID() != CategoryID)
            {
                break;
            }

            // Copy the current property value to the previous element
            pPreviousProp->SetValueString(pProp->GetValueString());

            if (pProp == &DstProperty)
            {
                FoundDst = true;
                break;
            }

            // Save the previous property pointer
            pPreviousProp = pProp;
        }

        // If the destination hasn't been reached, then error
        if (!FoundDst || !pProp)
        {
            return false;
        }

        // Copy the saved value of the droped item
        pProp->SetValueString(SrcValue);

        RetValue = true;
    }

    return RetValue;
}
