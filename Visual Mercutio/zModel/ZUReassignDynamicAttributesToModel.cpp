// ZUReassignDynamicAttributesToModel.cpp: implementation of the ZUReassignDynamicAttributesToModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUReassignDynamicAttributesToModel.h"

#include "zModel\ProcGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "zProperty\ZBDynamicProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUReassignDynamicAttributesToModel::ZUReassignDynamicAttributesToModel(ZDProcessGraphModelMdl* pModel /*= NULL*/, 
                                                                   ZBProperty* pProperty /*= NULL*/,
                                                                   void* pClass /*= NULL*/)
: ZUModelNavigation(pModel,pClass),
  m_pProperty(pProperty)
{
}

ZUReassignDynamicAttributesToModel::~ZUReassignDynamicAttributesToModel()
{

}

bool ZUReassignDynamicAttributesToModel::OnStart()
{
    if (!m_pProperty)
        return false;

    // Nothing more to do
    return true;
}

bool ZUReassignDynamicAttributesToModel::OnFinish()
{
    // Send it to the soap server
    return true;
}

bool ZUReassignDynamicAttributesToModel::OnSymbol( ZBSymbol* pSymbol )
{
    // If for the symbol has the same property
    // delete the property and assign the new one
    if (pSymbol->GetDynamicPropertiesManager()->DeleteProperty( m_pProperty ))
        pSymbol->GetDynamicPropertiesManager()->AddDynamicProperty( m_pProperty->Dup() );

    return true;
}
bool ZUReassignDynamicAttributesToModel::OnLink( ZBLinkSymbol* pLink )
{
    // If for the symbol has the same property
    // delete the property and assign the new one
    if (pLink->GetDynamicPropertiesManager()->DeleteProperty( m_pProperty ))
        pLink->GetDynamicPropertiesManager()->AddDynamicProperty( m_pProperty->Dup() );

    return true;
}







