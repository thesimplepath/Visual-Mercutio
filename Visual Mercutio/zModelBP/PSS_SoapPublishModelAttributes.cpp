/****************************************************************************
 * ==> PSS_SoapPublishModelAttributes --------------------------------------*
 ****************************************************************************
 * Description : Publish the model attributes to Messenger through a SOAP   *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublishModelAttributes.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zSOAP\PSS_SoapData_Settings.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SoapPublishModelAttributes
//---------------------------------------------------------------------------
PSS_SoapPublishModelAttributes::PSS_SoapPublishModelAttributes(PSS_PublishMessengerModelInformation* pInfo,
                                                               PSS_ProcessGraphModelMdl*             pModel,
                                                               void*                                 pClass) :
    PSS_ModelNavigation(pModel, pClass),
    m_pInfo(pInfo)
{
    std::memset(&m_IDArray, 0x0, 500);
}
//---------------------------------------------------------------------------
PSS_SoapPublishModelAttributes::~PSS_SoapPublishModelAttributes()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelAttributes::OnStart()
{
    // copy the publication address from source info
    m_MessengerAddress           = static_cast<const char*>(m_pClass);
    PSS_SoapData_Settings::m_Url = (const char*)m_MessengerAddress;

    // reset the IDs array
    std::memset(m_IDArray, 0, sizeof(m_IDArray));

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelAttributes::OnFinish()
{
    if (!m_pModel)
        return false;

    // get the model main document
    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(m_pModel->GetDocument());

    // found it?
    if (!pDoc)
        return false;

    // get the dynamic properties
    PSS_DynamicPropertiesManager* pDynPropMgr = pDoc->GetDynamicPropertiesManager();

    if (!pDynPropMgr)
        return false;

    PSS_Properties::IPropertySet                                 propSet;
    PSS_DynamicPropertiesManager::IDynamicPropertiesInfoIterator it(&pDynPropMgr->GetDynamicPropertiesInfoSet());

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        propSet.Add(pProp->m_pProperty);

    // publish the properties
    Publish(propSet);

    // remove all properties, but don't delete the pointer itself
    propSet.RemoveAll();

    // send it to the soap server
    return m_PubMdlAttr.Send();
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelAttributes::OnSymbol(PSS_Symbol* pSymbol)
{
    if (!pSymbol)
        return false;

    PSS_Properties::IPropertySet propSet;

    // get the object properties
    pSymbol->FillProperties(propSet, true, true);

    // publish the properties
    Publish(propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelAttributes::OnLink(PSS_LinkSymbol* pLink)
{
    if (!pLink)
        return false;

    PSS_Properties::IPropertySet propSet;

    // get the object properties
    pLink->FillProperties(propSet, true, true);

    // publish the properties
    Publish(propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
void PSS_SoapPublishModelAttributes::Publish(const PSS_Properties::IPropertySet& propSet)
{
    PSS_Properties::IPropertyIterator it(&propSet);

    // iterate through properties to publish
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // build the property key (to find it in properties array)
        const short left  = pProp->GetCategoryID() & 0x0000FFFF;
        const short right = pProp->GetItemID()     & 0x0000FFFF;
        const int   key   = (left << 16) | right;

        int type;

        // search for property value type
        switch (pProp->GetValueType())
        {
            case PSS_Property::IEValueType::IE_VT_Double:
            case PSS_Property::IEValueType::IE_VT_Float:    type = 2; break;
            case PSS_Property::IEValueType::IE_VT_Date:
            case PSS_Property::IEValueType::IE_VT_TimeSpan:
            case PSS_Property::IEValueType::IE_VT_Duration: type = 3; break;
            default:                                        type = 1; break;
        }

        // check if property already exists in array, add it if not
        if (!KeyExist(key))
        {
            // log the newly added property content
            if (m_pLog && m_pLog->IsInDebugMode())
            {
                CString message;
                message.Format(IDS_AL_PUBLISHMODELATTRIBUTE,
                               pProp->GetItemID(),
                               (const char*)pProp->GetLabel(),
                               pProp->GetValueType());

                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            // publish the property
            m_PubMdlAttr.Add
                    (PSS_SoapData_ModelAttributes(key,                             // attrib ID
                                                  pProp->GetItemID(),              // group ID
                                                  PSS_String16(pProp->GetLabel()), // text
                                                  type,                            // type (1 = string)
                                                  1));                             // 1 = mandatory (always set to 1)
            m_PubMdlAttr.AddAlias(m_pInfo->m_MessengerAlias);

            #ifdef _DEBUG
                CString s;
                s.Format(_T(" Attributes = %s Key =%d SubKey =%d\n"),
                         (const char*)pProp->GetLabel(),
                         key,
                         pProp->GetItemID());

                TRACE(s);
            #endif
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelAttributes::KeyExist(int key)
{
    int index;

    for (index = 0; index < sizeof(m_IDArray) && m_IDArray[index] != 0; ++index)
        if (m_IDArray[index] == key)
            return true;

    // doesn't exist, check the array size before inserting the element
    if (index < sizeof(m_IDArray) / sizeof(int))
        // add it for the next time
        m_IDArray[index] = key;

    return false;
}
//---------------------------------------------------------------------------
