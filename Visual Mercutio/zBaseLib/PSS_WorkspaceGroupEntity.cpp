/****************************************************************************
 * ==> PSS_WorkspaceGroupEntity --------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace group entity                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceGroupEntity.h"

// processsoft
#include "PSS_WorkspaceFileEntity.h"
#include "PSS_Tokenizer.h"
#include "PSS_WorkspaceGroupNameDlg.h"

// resources
#include "zBaseLibRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkspaceGroupEntity, PSS_WorkspaceEntity, g_DefVersion)
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::IEntitySet PSS_WorkspaceGroupEntity::m_FindSet;
//---------------------------------------------------------------------------
// PSS_WorkspaceGroupEntity
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::PSS_WorkspaceGroupEntity(const CString& name, PSS_WorkspaceEntity* pParent) :
    PSS_WorkspaceEntity(name, pParent)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::PSS_WorkspaceGroupEntity(const CString&       name,
                                                   CStringArray*        pExtensionList,
                                                   PSS_WorkspaceEntity* pParent) :
    PSS_WorkspaceEntity(name, pParent)
{
    if (pExtensionList)
        SetExtensionList(*pExtensionList);
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::~PSS_WorkspaceGroupEntity()
{
    RemoveAllEntities();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::RemoveAllEntities()
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    // iterate through entities
    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        delete pEnv;

    m_EntitySet.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::ContainEntity() const
{
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_WorkspaceGroupEntity::GetEntityCount() const
{
    return m_EntitySet.GetSize();
}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceGroupEntity::GetEntityAt(std::size_t index)
{
    return (index < GetEntityCount() ? m_EntitySet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::IEntitySet* PSS_WorkspaceGroupEntity::GetEntitySet()
{
    return &m_EntitySet;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::ClearExtensionList()
{
    m_ExtensionList.RemoveAll();
}
//---------------------------------------------------------------------------
CStringArray* PSS_WorkspaceGroupEntity::GetExtensionList()
{
    return &m_ExtensionList;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::GetExtensionList(CString& extensions)
{
    extensions.Empty();

    // initialize the token class with the separator char
    PSS_Tokenizer Token(';');

    const int count = m_ExtensionList.GetSize();

    // copy all elements
    for (int i = 0; i < count; ++i)
        Token.AddToken(m_ExtensionList.GetAt(i));

    extensions = Token.GetString();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::SetExtensionList(const CStringArray& extensionArray)
{
    // remove all elements
    m_ExtensionList.RemoveAll();

    // copy all elements
    PSS_WorkspaceGroupEntity::AddElementToExtensionList(extensionArray);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::SetExtensionList(const CString& extensions)
{
    ParseExtension(extensions, m_ExtensionList);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::AddElementToExtensionList(const CStringArray& extensionArray)
{
    const int count = extensionArray.GetSize();

    // add all elements
    for (int i = 0; i < count; ++i)
        m_ExtensionList.Add(extensionArray.GetAt(i));
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::ContainThisExtension(const CString& extension)
{
    const int count = m_ExtensionList.GetSize();

    // iterate through elements
    for (int i = 0; i < count; ++i)
        // is matching?
        if (m_ExtensionList.GetAt(i).CompareNoCase(extension) == 0)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::PropertiesVisible()
{
    CString extensions;
    GetExtensionList(extensions);

    PSS_WorkspaceGroupNameDlg dlg(dynamic_cast<PSS_WorkspaceGroupEntity*>(GetParent()), GetEntityName(), extensions);

    // ask for the name
    if (dlg.DoModal() == IDOK)
    {
        SetExtensionList(dlg.GetExtensions());
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::AddGroup(const CString& name, CStringArray* pExtensionList)
{
    std::unique_ptr<PSS_WorkspaceGroupEntity> pNewGroup(new PSS_WorkspaceGroupEntity(name, pExtensionList, this));
    m_EntitySet.Add(pNewGroup.get());
    return pNewGroup.release();
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::AddGroup(const CString& name,
                                                             CStringArray*  pExtensionList,
                                                             const CString& inGroupName)
{
    PSS_WorkspaceGroupEntity* pGroup = NULL;

    // locate the group in group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return AddGroup(name, pExtensionList, pGroup);
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::AddGroup(const CString&            name,
                                                             CStringArray*             pExtensionList,
                                                             PSS_WorkspaceGroupEntity* pInGroup)
{
    // no group defined?
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->AddGroup(name, pExtensionList);
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::AddGroup(const CString& name, const CString& extensions)
{
    CStringArray extensionArray;

    if (ParseExtension(extensions, extensionArray))
        return AddGroup(name, &extensionArray);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::AddGroup(const CString& name,
                                                             const CString& extensions,
                                                             const CString& inGroupName)
{
    CStringArray extensionArray;

    if (ParseExtension(extensions, extensionArray))
        return AddGroup(name, &extensionArray, inGroupName);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::AddGroup(const CString&            name,
                                                             const CString&            extensions,
                                                             PSS_WorkspaceGroupEntity* pInGroup)
{
    CStringArray extensionArray;

    if (ParseExtension(extensions, extensionArray))
        return AddGroup(name, &extensionArray, pInGroup);

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveGroup(const CString& name, bool deeper)
{
    IEntitySet* pSet = FindGroup(name, deeper);

    if (pSet && pSet->GetSize() > 0)
        return RemoveGroups(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveGroup(const CString& name, const CString& inGroupName)
{
    IEntitySet* pSet = FindGroup(name, inGroupName);

    if (pSet && pSet->GetSize() > 0)
        return RemoveGroups(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveGroup(const CString& name, PSS_WorkspaceGroupEntity* pInGroup)
{
    IEntitySet* pSet = FindGroup(name, pInGroup);

    if (pSet && pSet->GetSize() > 0)
        return RemoveGroups(*pSet);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveGroup(PSS_WorkspaceGroupEntity* pGroup)
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    // iterate through entities
    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
        if (pEnv == pGroup && ISA(pEnv, PSS_WorkspaceGroupEntity))
        {
            // free the memory
            delete pGroup;

            // remove the current element
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::IEntitySet* PSS_WorkspaceGroupEntity::FindGroup(const CString& name, bool deeper)
{
    m_FindSet.RemoveAll();
    FindGroupPvt(name, deeper);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::IEntitySet* PSS_WorkspaceGroupEntity::FindGroup(const CString& name, const CString& inGroupName)
{
    PSS_WorkspaceGroupEntity* pGroup = NULL;

    // locate the group in group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return FindGroup(name, pGroup);
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity::IEntitySet* PSS_WorkspaceGroupEntity::FindGroup(const CString&            name,
                                                                          PSS_WorkspaceGroupEntity* pInGroup)
{
    m_FindSet.RemoveAll();
    FindGroupPvt(name, pInGroup);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::GroupExist(const CString& name, bool deeper)
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    // iterate through entities
    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_WorkspaceGroupEntity* pEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEnv);

        if (pEntity)
        {
            // is matching with the requested name?
            if (pEntity->GetEntityName() == name)
                return true;

            // if the group has entity
            if (deeper && pEntity->ContainEntity())
                if (pEntity->GroupExist(name, deeper))
                    return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::GroupExist(const CString& name, const CString& inGroupName)
{
    PSS_WorkspaceGroupEntity* pGroup = NULL;

    // locate the group in group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return GroupExist(name, pGroup);
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::GroupExist(const CString& name, PSS_WorkspaceGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->GroupExist(name, false);
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity* PSS_WorkspaceGroupEntity::AddFile(const CString& fileName)
{
    PSS_WorkspaceFileEntity* pNewFile = new PSS_WorkspaceFileEntity(fileName, this);
    m_EntitySet.Add(pNewFile);
    return pNewFile;
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity* PSS_WorkspaceGroupEntity::AddFile(const CString& fileName, const CString& inGroupName)
{
    PSS_WorkspaceGroupEntity* pGroup = NULL;

    // locate the group in group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return AddFile(fileName, pGroup);
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity* PSS_WorkspaceGroupEntity::AddFile(const CString& fileName, PSS_WorkspaceGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->AddFile(fileName);
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveFile(PSS_WorkspaceFileEntity* pFile)
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    // iterate through entities
    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_WorkspaceFileEntity* pFileEntity = dynamic_cast<PSS_WorkspaceFileEntity*>(pEnv);

        if (pFileEntity && pFileEntity == pFile)
        {
            // free the memory
            delete pEnv;

            // remove the current element
            it.Remove();
            return true;
        }

        PSS_WorkspaceGroupEntity* pGroupEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEnv);

        // if a group entity was found and contains entities, recalculate it
        if (pGroupEntity && pGroupEntity->ContainEntity())
            if (pGroupEntity->RemoveFile(pFile))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveFile(const CString& fileName)
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    // iterate through entities
    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_WorkspaceFileEntity* pEntity = dynamic_cast<PSS_WorkspaceFileEntity*>(pEnv);

        if (pEntity && pEntity->GetFileName() == fileName)
        {
            // free the memory
            delete pEnv;

            // remove the current element
            it.Remove();
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveFile(const CString& fileName, const CString& inGroupName)
{
    PSS_WorkspaceGroupEntity* pGroup = NULL;

    // locate the group in group name
    if (!inGroupName.IsEmpty())
        pGroup = FindFirstGroup(inGroupName);

    return RemoveFile(fileName, pGroup);
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveFile(const CString& fileName, PSS_WorkspaceGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->RemoveFile(fileName);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::Serialize(CArchive& ar)
{
    PSS_WorkspaceEntity::Serialize(ar);

    if (ar.IsStoring())
    {
        const int count = GetEntityCount();

        // write the elements
        ar << count;

        for (int i = 0; i < count; ++i)
        {
            PSS_WorkspaceEntity* pEntity = GetEntityAt(i);
            ar << pEntity;
        }
    }
    else
    {
        // remove all previous elements
        RemoveAllEntities();

        PSS_WorkspaceEntity* pEntity;
        int                  count;

        ar >> count;

        // read the elements
        for (int i = 0; i < count; ++i)
        {
            ar >> pEntity;
            m_EntitySet.Add(pEntity);
            pEntity->SetParent(this);
        }
    }

    // serialize the extension list
    m_ExtensionList.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceGroupEntity::AssertValid() const
    {
        PSS_WorkspaceEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceGroupEntity::Dump(CDumpContext& dc) const
    {
        PSS_WorkspaceEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::FindGroupPvt(const CString& name, bool deeper)
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        PSS_WorkspaceGroupEntity* pEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEnv);

        if (pEntity)
        {
            // if matching with the requested name, add it to the find set
            if (pEntity->GetEntityName() == name)
                m_FindSet.Add(pEnv);

            // if a group entity was found and contains entities, recalculate it
            if (deeper && pEntity->ContainEntity())
                pEntity->FindGroupPvt(name, deeper);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::FindGroupPvt(const CString& name, PSS_WorkspaceGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    pInGroup->FindGroupPvt(name, false);
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::FindFirstGroup(const CString& name, bool deeper)
{
    IEntityIterator it(&m_EntitySet);

    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv != NULL; pEnv = it.GetNext())
    {
        PSS_WorkspaceGroupEntity* pEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEnv);

        if (pEntity)
        {
            // is matching with the requested name?
            if (pEntity->GetEntityName() == name)
                return pEntity;

            // the group contains entities?
            if (deeper && pEntity->ContainEntity())
            {
                PSS_WorkspaceGroupEntity* pGroup = pEntity->FindFirstGroup(name, deeper);

                if (pGroup)
                    return pGroup;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceGroupEntity* PSS_WorkspaceGroupEntity::FindFirstGroup(const CString& name, PSS_WorkspaceGroupEntity* pInGroup)
{
    if (!pInGroup)
        pInGroup = this;

    return pInGroup->FindFirstGroup(name, false);
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::RemoveGroups(IEntitySet& groupArray)
{
    bool result = false;

    if (groupArray.GetSize() > 0)
    {
        result          = true;
        const int count = groupArray.GetSize();

        // iterate through groups
        for (int i = 0; i < count; ++i)
        {
            PSS_WorkspaceGroupEntity* pGroup = dynamic_cast<PSS_WorkspaceGroupEntity*>(groupArray.GetAt(i));

            if (pGroup && pGroup->GetParent())
            {
                PSS_WorkspaceGroupEntity* pParent = dynamic_cast<PSS_WorkspaceGroupEntity*>(pGroup->GetParent());

                if (!pParent || !pParent->RemoveGroup(pGroup))
                    result = false;
            }
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceGroupEntity::RecalculateParent()
{
    // set the iterator to the right entity set
    IEntityIterator it(&m_EntitySet);

    for (PSS_WorkspaceEntity* pEnv = it.GetFirst(); pEnv; pEnv = it.GetNext())
    {
        pEnv->SetParent(this);

        PSS_WorkspaceGroupEntity* pEntity = dynamic_cast<PSS_WorkspaceGroupEntity*>(pEnv);

        // if a group entity was found and contains entities, recalculate it
        if (pEntity && pEntity->ContainEntity())
            pEntity->RecalculateParent();
    }
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceGroupEntity::ParseExtension(const CString& extensions, CStringArray& extensionArray)
{
    // clear the array
    extensionArray.RemoveAll();

    // initialize the token class with the separator char
    PSS_Tokenizer token(';');

    CString ext = token.GetFirstToken(extensions);

    while (!ext.IsEmpty())
    {
        // add the extension to the array
        extensionArray.Add(ext);

        // get next token
        ext = token.GetNextToken();
    }

    return true;
}
//---------------------------------------------------------------------------
