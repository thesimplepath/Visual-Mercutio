/////////////////////////////////////////////////////////////////////////////
//@doc ZUExtractCategoryAttributes
//@module ZUExtractCategoryAttributes.h | Interface of the <c ZUExtractCategoryAttributes> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         05/2002
// <nl>Description:  ZUExtractCategoryAttributes navigates through the model and
//                     extract unique attributes' categories
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUExtractCategoryAttributes_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUExtractCategoryAttributes_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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


#include "zModel\ZUModelNavigation.h"

#include "zProperty\ZIProperties.h"
#include "zProperty\ZBProperty.h"
#include "zBaseLib\PSS_KeepStringUsage.h"


#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZUExtractCategoryAttributes : public ZUModelNavigation, public PSS_KeepStringUsage
{
public:
    ZUExtractCategoryAttributes(PSS_ProcessGraphModelMdl* pModel = NULL,
                                CStringArray* pStaticArray = NULL,
                                CStringArray* pDynamicArray = NULL,
                                void* pClass = NULL);

    virtual ~ZUExtractCategoryAttributes();


    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();

    virtual bool OnSymbol(ZBSymbol* pSymbol);
    virtual bool OnLink(PSS_LinkSymbol* pLink);

private:
    CStringArray* m_pDynamicArray;
    CStringArray* m_pStaticArray;

    void FillAttribCategory(ZBPropertySet& PropSet);
};

#endif
