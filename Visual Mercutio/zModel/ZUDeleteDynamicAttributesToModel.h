/////////////////////////////////////////////////////////////////////////////
//@doc ZUDeleteDynamicAttributesToModel
//@module ZUDeleteDynamicAttributesToModel.h | Interface of the <c ZUDeleteDynamicAttributesToModel> class.
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
// <nl>Description:  ZUDeleteDynamicAttributesToModel navigates through the model and
//                     delete the property object to all symbols.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUDeleteDynamicAttributesToModel_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUDeleteDynamicAttributesToModel_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

// processsoft
#include "zProperty\ZIProperties.h"
#include "zProperty\ZBProperty.h"
#include "zModel\ZUModelNavigation.h"

// forward class declaration
class PSS_BasicSymbol;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZUDeleteDynamicAttributesToModel : public ZUModelNavigation
{
public:
    ZUDeleteDynamicAttributesToModel(PSS_ProcessGraphModelMdl* pModel = NULL,
                                     ZBProperty* pProperty = NULL,
                                     void* pClass = NULL);

    virtual ~ZUDeleteDynamicAttributesToModel();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();

    virtual bool OnSymbol(PSS_Symbol* pSymbol);
    virtual bool OnLink(PSS_LinkSymbol* pLink);

private:
    ZBProperty* m_pProperty;
};

#endif
