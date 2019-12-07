/****************************************************************************
 * ==> ZUExtractModelAttributes --------------------------------------------*
 ****************************************************************************
 * Description : Navigates through the model and extract unique symbol      *
 *               attributes                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

 // mfc
#include "stdafx.h"

// processsoft
#include "ZUExtractModelAttributes.h"
#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// ZUExtractModelAttributes
//---------------------------------------------------------------------------
ZUExtractModelAttributes::ZUExtractModelAttributes(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    ZUModelNavigation(pModel, pClass)
{}
//---------------------------------------------------------------------------
ZUExtractModelAttributes::~ZUExtractModelAttributes()
{}
//---------------------------------------------------------------------------
bool ZUExtractModelAttributes::OnStart()
{
    m_pPropertySet = static_cast<ZBPropertySet*>(m_pClass);

    if (!m_pPropertySet)
        return false;

    // reset the array of ids
    std::memset(m_IDArray, 0, sizeof(m_IDArray));

    // nothing more to do
    return true;
}
//---------------------------------------------------------------------------
bool ZUExtractModelAttributes::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool ZUExtractModelAttributes::OnSymbol(ZBSymbol* pSymbol)
{
    ZBPropertySet propSet;

    // Retrieve the property set from object
    pSymbol->FillProperties(propSet, true);

    // Add the attributes to the pPublishAttribDef class
    ProcessAttrib(propSet);

    // Remove all properties
    ZBPropertyIterator i(&propSet);
    ZBProperty*        pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool ZUExtractModelAttributes::OnLink(PSS_LinkSymbol* pLink)
{
    ZBPropertySet propSet;

    // retrieve the property set from object
    pLink->FillProperties(propSet, true);

    // add the attributes to the pPublishAttribDef class
    ProcessAttrib(propSet);

    // remove all properties
    ZBPropertyIterator i(&propSet);
    ZBProperty*        pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
void ZUExtractModelAttributes::ProcessAttrib(ZBPropertySet& propSet)
{
    ASSERT(m_pPropertySet);

    // remove all properties
    ZBPropertyIterator i(&propSet);
    ZBProperty*        pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        const short left  = pProp->GetCategoryID() & 0x0000FFFF;
        const short right = pProp->GetItemID()     & 0x0000FFFF;
        const int   key   = (left << 16) | right;

        // if the key doesn't exist yet, add it to the final property set
        if (!KeyExist(key))
            m_pPropertySet->Add(pProp->Dup());
    }
}
//---------------------------------------------------------------------------
bool ZUExtractModelAttributes::KeyExist(int key)
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
