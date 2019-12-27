/****************************************************************************
 * ==> PSS_ModelSet --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a model set                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelSet.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ModelSet, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ModelSet
//---------------------------------------------------------------------------
PSS_ModelSet::PSS_ModelSet() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_ModelSet::~PSS_ModelSet()
{}
//---------------------------------------------------------------------------
PSS_ModelSet* PSS_ModelSet::Clone()
{
    std::unique_ptr<PSS_ModelSet> pNewSet(new PSS_ModelSet());

    const std::size_t modelCount = GetModelCount();

    for (std::size_t i = 0; i < modelCount; ++i)
    {
        PSS_ProcessGraphModelMdl* pMdl = GetModelAt(i);

        if (pMdl)
            pNewSet->AddModel(pMdl);
    }

    return pNewSet.release();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelSet::GetModelAt(std::size_t index)
{
    if (index < GetModelCount())
        return static_cast<PSS_ProcessGraphModelMdl*>(m_Set.GetAt(index));

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelSet::FindModel(const CString& name)
{
    const std::size_t modelCount = GetModelCount();

    for (std::size_t i = 0; i < modelCount; ++i)
    {
        PSS_ProcessGraphModelMdl* pMdl = GetModelAt(i);

        if (pMdl->GetModelName() == name)
            return pMdl;
    }

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_ModelSet::FindModelIndex(PSS_ProcessGraphModelMdl* pModel)
{
    const std::size_t modelCount = GetModelCount();

    for (std::size_t i = 0; i < modelCount; ++i)
    {
        PSS_ProcessGraphModelMdl* pMdl = GetModelAt(i);

        if (pMdl == pModel)
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ModelSet::AddModel(PSS_ProcessGraphModelMdl* pModel)
{
    const std::size_t prevCount = GetModelCount();
    m_Set.Add(pModel);
    return GetModelCount() > prevCount;
}
//---------------------------------------------------------------------------
bool PSS_ModelSet::RemoveModel(PSS_ProcessGraphModelMdl* pModel)
{
    const std::size_t modelCount = GetModelCount();

    for (std::size_t i = 0; i < modelCount; ++i)
    {
        PSS_ProcessGraphModelMdl* pMdl = GetModelAt(i);

        if (pMdl == pModel)
        {
            RemoveModelAt(i);
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelSet::RemoveModelAt(std::size_t index)
{
    if (index < GetModelCount())
    {
        m_Set.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ModelSet::RemoveAllModel()
{
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ModelSet::DeleteAllModel()
{
    const std::size_t modelCount = GetModelCount();

    for (std::size_t i = 0; i < modelCount; ++i)
    {
        PSS_ProcessGraphModelMdl* pMdl = GetModelAt(i);

        if (pMdl)
            delete pMdl;
    }

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ModelSet::Serialize(CArchive& ar)
{
    m_Set.Serialize(ar);
}
//---------------------------------------------------------------------------
