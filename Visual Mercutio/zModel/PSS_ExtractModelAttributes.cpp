/****************************************************************************
 * ==> PSS_ExtractModelAttributes ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               extract unique symbol                                      *
 *               attributes                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtractModelAttributes.h"

// processsoft
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ExtractModelAttributes
//---------------------------------------------------------------------------
PSS_ExtractModelAttributes::PSS_ExtractModelAttributes(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    ZUModelNavigation(pModel, pClass)
{}
//---------------------------------------------------------------------------
PSS_ExtractModelAttributes::~PSS_ExtractModelAttributes()
{}
//---------------------------------------------------------------------------
bool PSS_ExtractModelAttributes::OnStart()
{
    m_pPropertySet = static_cast<ZBPropertySet*>(m_pClass);

    if (!m_pPropertySet)
        return false;

    // reset the id array
    std::memset(m_IDArray, 0, sizeof(m_IDArray));

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelAttributes::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelAttributes::OnSymbol(PSS_Symbol* pSymbol)
{
    ZBPropertySet propSet;

    // get the property set from object
    pSymbol->FillProperties(propSet, true);

    // add the attributes to the pPublishAttribDef class
    ProcessAttrib(propSet);

    ZBPropertyIterator it(&propSet);

    // remove all properties
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelAttributes::OnLink(PSS_LinkSymbol* pLink)
{
    ZBPropertySet propSet;

    // get the property set from object
    pLink->FillProperties(propSet, true);

    // add the attributes to the pPublishAttribDef class
    ProcessAttrib(propSet);

    ZBPropertyIterator it(&propSet);

    // remove all properties
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
void PSS_ExtractModelAttributes::ProcessAttrib(ZBPropertySet& propSet)
{
    ASSERT(m_pPropertySet);

    ZBPropertyIterator it(&propSet);

    // remove all properties
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const short left  = pProp->GetCategoryID() & 0x0000FFFF;
        const short right = pProp->GetItemID()     & 0x0000FFFF;
        const int   key   = (left << 16) | right;

        // if the key doesn't exist, add it to the final property set
        if (!KeyExist(key))
            m_pPropertySet->Add(pProp->Dup());
    }
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelAttributes::KeyExist(int key)
{
    int index = 0;

    for (int i = 0; i < sizeof(m_IDArray) && m_IDArray[i] != 0; ++i)
    {
        if (m_IDArray[i] == key)
            return true;

        index = i;
    }

    // doesn't exist, check the array size before inserting the element
    if (index < sizeof(m_IDArray) / sizeof(int))
        // add it for the next time
        m_IDArray[index] = key;

    return false;
}
//---------------------------------------------------------------------------
