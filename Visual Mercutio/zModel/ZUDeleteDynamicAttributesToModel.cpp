// ZUDeleteDynamicAttributesToModel.cpp: implementation of the ZUDeleteDynamicAttributesToModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUDeleteDynamicAttributesToModel.h"

#include "zModel\PSS_ProcessGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "zProperty\ZBDynamicProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUDeleteDynamicAttributesToModel::ZUDeleteDynamicAttributesToModel(PSS_ProcessGraphModelMdl* pModel /*= NULL*/,
                                                                   ZBProperty* pProperty /*= NULL*/,
                                                                   void* pClass /*= NULL*/)
    : ZUModelNavigation(pModel, pClass),
    m_pProperty(pProperty)
{}

ZUDeleteDynamicAttributesToModel::~ZUDeleteDynamicAttributesToModel()
{

}

bool ZUDeleteDynamicAttributesToModel::OnStart()
{
    if (!m_pProperty)
        return false;

    // Nothing more to do
    return true;
}

bool ZUDeleteDynamicAttributesToModel::OnFinish()
{
    // Send it to the soap server
    return true;
}

bool ZUDeleteDynamicAttributesToModel::OnSymbol(ZBSymbol* pSymbol)
{
    // If for the symbol has the same property
    // delete the property and assign the new one
    pSymbol->GetDynamicPropertiesManager()->DeleteProperty(m_pProperty);

    return true;
}
bool ZUDeleteDynamicAttributesToModel::OnLink(PSS_LinkSymbol* pLink)
{
    // If for the symbol has the same property
    // delete the property and assign the new one
    pLink->GetDynamicPropertiesManager()->DeleteProperty(m_pProperty);

    return true;
}
