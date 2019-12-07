/****************************************************************************
 * ==> ZUExtractModelAttributes --------------------------------------------*
 ****************************************************************************
 * Description : Navigates through the model and extract unique symbol      *
 *               attributes                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef AFX_ZUExtractModelAttributesH
#define AFX_ZUExtractModelAttributesH

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zModel\ZUModelNavigation.h"
#include "zProperty\ZBProperty.h"
#include "PSS_ProcessGraphModelMdl.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigates through the model and extract unique symbol attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZUExtractModelAttributes : public ZUModelNavigation  
{
    public:
        ZUExtractModelAttributes(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
        virtual ~ZUExtractModelAttributes();

        virtual bool OnStart();
        virtual bool OnFinish();

        virtual bool OnSymbol(ZBSymbol* pSymbol);
        virtual bool OnLink(PSS_LinkSymbol* pLink);

    private:
        int            m_IDArray[500];
        ZBPropertySet* m_pPropertySet;

        void ProcessAttrib(ZBPropertySet& PropSet);
        bool KeyExist(int key);
};

#endif
