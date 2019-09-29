/****************************************************************************
 * ==> PSS_WorkspaceEntity -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace entity                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkspaceEntity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_WorkspaceEntity
//---------------------------------------------------------------------------
PSS_WorkspaceEntity::PSS_WorkspaceEntity(const CString& name, PSS_WorkspaceEntity* pParent) :
    CObject(),
    m_pParent(pParent),
    m_EntityName(name)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity::~PSS_WorkspaceEntity()
{}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEntity::ContainEntity() const
{
    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_WorkspaceEntity::GetEntityCount() const
{
    return 0;
}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceEntity::GetEntityAt(std::size_t index)
{
    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceEntity::GetEntityName() const
{
    return m_EntityName;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::SetEntityName(const CString& value)
{
    m_EntityName = value;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceEntity::GetEntityDescription() const
{
    return m_EntityName;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::SetEntityDescription(const CString& value)
{
    m_EntityDescription = value;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::ClearExtensionList()
{}
//---------------------------------------------------------------------------
CStringArray* PSS_WorkspaceEntity::GetExtensionList()
{
    return NULL;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::GetExtensionList(CString& Extensions)
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::SetExtensionList(CStringArray& extensionArray)
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::SetExtensionList(const CString Extensions)
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::AddElementToExtensionList(CStringArray& extensionArray)
{}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEntity::ContainThisExtension(const CString& extension)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEntity::HasFileName() const
{
    return false;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceEntity::GetFileName() const
{
    return _T("");
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::SetFileName(const CString& value)
{}
//---------------------------------------------------------------------------
CString PSS_WorkspaceEntity::GetFileTitle() const
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceEntity::GetFilePath() const
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceEntity::GetFileExt() const
{
    return _T("");
}
//---------------------------------------------------------------------------
HICON PSS_WorkspaceEntity::GetFileNameIcon() const
{
    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEntity::PropertiesVisible()
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_EntityName;
        ar << m_EntityDescription;
    }
    else
    {
        // read the elements
        ar >> m_EntityName;
        ar >> m_EntityDescription;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceEntity::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceEntity::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
