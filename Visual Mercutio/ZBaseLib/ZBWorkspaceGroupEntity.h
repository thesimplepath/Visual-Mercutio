// ZBWorkspaceGroupEntity.h: interface for the ZBWorkspaceGroupEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWORKSPACEGROUPENTITY_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)
#define AFX_ZBWORKSPACEGROUPENTITY_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_WorkspaceEntity.h"

// forward class declaration
class ZBWorkspaceFileEntity;

#ifdef _ZBASELIBEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;


///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBWorkspaceEntitySet | An array of ZBWorkspaceEntity pointers.
//@iex typedef CCArray_T<ZBWorkspaceEntity*,ZBWorkspaceEntity*> ZBWorkspaceEntitySet;
typedef CCArray_T<PSS_WorkspaceEntity*, PSS_WorkspaceEntity*> ZBWorkspaceEntitySet;

//@type ZBWorkspaceEntityIterator | An iterator for ZBWorkspaceEntitySet collections.
//@iex typedef Iterator_T<ZBWorkspaceEntity*> ZBWorkspaceEntityIterator;
typedef Iterator_T<PSS_WorkspaceEntity*> ZBWorkspaceEntityIterator;



class AFX_EXT_CLASS ZBWorkspaceGroupEntity : public PSS_WorkspaceEntity
{
    DECLARE_SERIAL(ZBWorkspaceGroupEntity)
public:
    ZBWorkspaceGroupEntity(const CString Name = "", PSS_WorkspaceEntity* pParent = NULL);
    ZBWorkspaceGroupEntity(const CString Name, CStringArray* pExtensionList, PSS_WorkspaceEntity* pParent = NULL);
    virtual ~ZBWorkspaceGroupEntity();

    void RemoveAllEntities();

    virtual bool ContainEntity() const
    {
        return true;
    };
    virtual size_t GetEntityCount() const
    {
        return m_EntitySet.GetSize();
    };
    virtual PSS_WorkspaceEntity* GetEntityAt(size_t Index)
    {
        return (Index < GetEntityCount()) ? m_EntitySet.GetAt(Index) : NULL;
    };
    virtual ZBWorkspaceEntitySet* GetEntitySet()
    {
        return &m_EntitySet;
    };

    virtual void ClearExtensionList()
    {
        m_ExtensionList.RemoveAll();
    };
    virtual void SetExtensionList(CStringArray& ExtensionArray);
    virtual void AddElementToExtensionList(CStringArray& ExtensionArray);
    virtual CStringArray* GetExtensionList()
    {
        return &m_ExtensionList;
    };
    virtual void SetExtensionList(const CString Extensions);
    virtual void GetExtensionList(CString& Extensions);
    virtual bool ContainThisExtension(const CString Extension);

    virtual bool DisplayProperties();


    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBWorkspaceGroupEntity* AddGroup(const CString Name, CStringArray* pExtensionList = NULL);
    ZBWorkspaceGroupEntity* AddGroup(const CString Name, CStringArray* pExtensionList, const CString InGroupName);
    ZBWorkspaceGroupEntity* AddGroup(const CString Name, CStringArray* pExtensionList, ZBWorkspaceGroupEntity* pInGroup);
    ZBWorkspaceGroupEntity* AddGroup(const CString Name, CString& Extensions);
    ZBWorkspaceGroupEntity* AddGroup(const CString Name, CString& Extensions, const CString InGroupName);
    ZBWorkspaceGroupEntity* AddGroup(const CString Name, CString& Extensions, ZBWorkspaceGroupEntity* pInGroup);


    bool RemoveGroup(const CString Name, bool Deeper = false);
    bool RemoveGroup(const CString Name, const CString InGroupName);
    bool RemoveGroup(const CString Name, ZBWorkspaceGroupEntity* pInGroup);
    bool RemoveGroup(ZBWorkspaceGroupEntity* pGroup);

    ZBWorkspaceEntitySet* FindGroup(const CString Name, bool Deeper = false);
    ZBWorkspaceEntitySet* FindGroup(const CString Name, const CString InGroupName);
    ZBWorkspaceEntitySet* FindGroup(const CString Name, ZBWorkspaceGroupEntity* pInGroup);
    bool GroupExist(const CString Name, bool Deeper = false);
    bool GroupExist(const CString Name, const CString InGroupName);
    bool GroupExist(const CString Name, ZBWorkspaceGroupEntity* pInGroup);


    ////////////////////////////////////////////////////////////////
    // File management functions
    ZBWorkspaceFileEntity* AddFile(const CString Filename);
    ZBWorkspaceFileEntity* AddFile(const CString Filename, const CString InGroupName);
    ZBWorkspaceFileEntity* AddFile(const CString Filename, ZBWorkspaceGroupEntity* pInGroup);
    bool RemoveFile(ZBWorkspaceFileEntity* pFile);
    bool RemoveFile(const CString Filename);
    bool RemoveFile(const CString Filename, const CString InGroupName);
    bool RemoveFile(const CString Filename, ZBWorkspaceGroupEntity* pInGroup);

    // Serialization mechanism
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    ////////////////////////////////////////////////////////////////
    // Group management functions
    void _FindGroup(const CString Name, ZBWorkspaceGroupEntity* pInGroup);
    void _FindGroup(const CString Name, bool Deeper = false);
    ZBWorkspaceGroupEntity* _FindFirstGroup(const CString Name, ZBWorkspaceGroupEntity* pInGroup);
    ZBWorkspaceGroupEntity* _FindFirstGroup(const CString Name, bool Deeper = false);
    bool _RemoveGroups(ZBWorkspaceEntitySet& Set);

    void RecalculateParent();
    bool ParseExtension(const CString Extensions, CStringArray& ExtensionArray);

    // Members are protected, since they need to be access directly by sub-class
protected:
    ZBWorkspaceEntitySet m_EntitySet;
    CStringArray m_ExtensionList;

    static ZBWorkspaceEntitySet m_FindSet;


};

#endif
