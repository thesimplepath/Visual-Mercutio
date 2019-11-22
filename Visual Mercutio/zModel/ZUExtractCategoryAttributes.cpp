// ZUExtractCategoryAttributes.cpp: implementation of the ZUExtractCategoryAttributes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUExtractCategoryAttributes.h"

#include "zModel\ProcGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 1er mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUExtractCategoryAttributes::ZUExtractCategoryAttributes(ZDProcessGraphModelMdl*    pModel            /*= NULL*/,
                                                         CStringArray*                pStaticArray    /*= NULL*/,
                                                         CStringArray*                pDynamicArray    /*= NULL*/,
                                                         void*                        pClass            /*= NULL*/)
    : ZUModelNavigation(pModel, pClass),
    m_pStaticArray(pStaticArray),
    m_pDynamicArray(pDynamicArray)
{}

ZUExtractCategoryAttributes::~ZUExtractCategoryAttributes()
{}

bool ZUExtractCategoryAttributes::OnStart()
{
    // Reset the array of categories
    ResetStringsArray();

    if (m_pDynamicArray)
    {
        m_pDynamicArray->RemoveAll();
    }

    if (m_pStaticArray)
    {
        m_pStaticArray->RemoveAll();
    }

    // Nothing more to do
    return true;
}

bool ZUExtractCategoryAttributes::OnFinish()
{
    // Send it to the soap server
    return true;
}

bool ZUExtractCategoryAttributes::OnSymbol(ZBSymbol* pSymbol)
{
    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties(PropSet, true);

    // Add the attributes to the pPublishAttribDef class
    FillAttribCategory(PropSet);

    // Remove all properties
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

bool ZUExtractCategoryAttributes::OnLink(PSS_LinkSymbol* pLink)
{
    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pLink->FillProperties(PropSet, true);

    // Add the attributes to the pPublishAttribDef class
    FillAttribCategory(PropSet);

    // Remove all properties
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

void ZUExtractCategoryAttributes::FillAttribCategory(ZBPropertySet& PropSet)
{
    // Remove all properties
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // Check if the category has already been generated
        if (!StringAlreadyGenerated(pProp->GetCategory()))
        {
            if (pProp->IsDynamic() && m_pDynamicArray)
            {
                m_pDynamicArray->Add(pProp->GetCategory());
            }
            else if (m_pStaticArray)
            {
                m_pStaticArray->Add(pProp->GetCategory());
            }
        }
    }
}
