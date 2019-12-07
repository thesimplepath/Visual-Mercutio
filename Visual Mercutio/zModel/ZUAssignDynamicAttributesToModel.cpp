// ZUAssignDynamicAttributesToModel.cpp: implementation of the ZUAssignDynamicAttributesToModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUAssignDynamicAttributesToModel.h"

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

ZUAssignDynamicAttributesToModel::ZUAssignDynamicAttributesToModel(PSS_ProcessGraphModelMdl* pModel /*= NULL*/,
                                                                   ZBProperty* pProperty /*= NULL*/,
                                                                   CRuntimeClass* pRTClass /*= NULL*/,
                                                                   void* pClass /*= NULL*/)
    : ZUModelNavigation(pModel, pClass),
    m_pProperty(pProperty),
    m_pRTClass(pRTClass)
{}

ZUAssignDynamicAttributesToModel::~ZUAssignDynamicAttributesToModel()
{

}

bool ZUAssignDynamicAttributesToModel::OnStart()
{
    if (!m_pProperty)
        return false;

    // Nothing more to do
    return true;
}

bool ZUAssignDynamicAttributesToModel::OnFinish()
{
    // Send it to the soap server
    return true;
}

bool ZUAssignDynamicAttributesToModel::OnSymbol(ZBSymbol* pSymbol)
{
    // If for the whole model
    // or for a specific class name
    if (!m_pRTClass ||
        (m_pRTClass &&
         m_pRTClass->m_lpszClassName == pSymbol->GetRuntimeClass()->m_lpszClassName))
        pSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(m_pProperty->Dup());

    return true;
}
bool ZUAssignDynamicAttributesToModel::OnLink(PSS_LinkSymbol* pLink)
{
    // If for the whole model
    // or for a specific class name
    if (!m_pRTClass ||
        (m_pRTClass &&
         m_pRTClass->m_lpszClassName == pLink->GetRuntimeClass()->m_lpszClassName))
        pLink->GetDynamicPropertiesManager()->AddDynamicProperty(m_pProperty->Dup());

    return true;
}
