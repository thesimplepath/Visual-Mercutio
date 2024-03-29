/****************************************************************************
 * ==> PSS_ModelGlobal -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides the model global property attributes              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelGlobal.h"

// std
#include <memory>>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_ModelGlobal::IPropertyAttributesSet PSS_ModelGlobal::m_Set;
CString                                 PSS_ModelGlobal::m_FileName;
//---------------------------------------------------------------------------
// PSS_ModelGlobal
//---------------------------------------------------------------------------
PSS_ModelGlobal::PSS_ModelGlobal()
{}
//---------------------------------------------------------------------------
PSS_ModelGlobal::~PSS_ModelGlobal()
{
    Release();
}
//---------------------------------------------------------------------------
bool PSS_ModelGlobal::SaveGlobalPropertyAttributes()
{
    const int count = m_Set.GetSize();

    // iterate through the global attributes
    for (int i = 0; i < count; ++i)
    {
        PSS_PropertyAttributes* pPropAtt = m_Set.GetAt(i);

        if (pPropAtt)
            pPropAtt->SaveStateToIniFile(m_FileName, i);
    }

    return true;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes& PSS_ModelGlobal::GetGlobalPropertyAttributes(int objectID)
{
    PSS_PropertyAttributes* pPropAtt = NULL;

    if (objectID < m_Set.GetSize())
        pPropAtt = m_Set.GetAt(objectID);

    if (!pPropAtt)
    {
        std::unique_ptr<PSS_PropertyAttributes> pNewPropAtt(new PSS_PropertyAttributes());
        pNewPropAtt->LoadStateFromIniFile(m_FileName, objectID);
        m_Set.SetAtGrow(objectID, pNewPropAtt.get());
        pPropAtt = pNewPropAtt.release();
    }

    PSS_Assert(pPropAtt);
    return *pPropAtt;
}
//---------------------------------------------------------------------------
void PSS_ModelGlobal::Release()
{
    const int count = m_Set.GetSize();

    for (int i = 0; i < count; ++i)
    {
        PSS_PropertyAttributes* pPropAtt = m_Set.GetAt(i);

        if (pPropAtt)
            delete pPropAtt;
    }

    m_Set.RemoveAll();
    m_FileName.Empty();
}
//---------------------------------------------------------------------------
