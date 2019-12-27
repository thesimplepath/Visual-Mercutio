/****************************************************************************
 * ==> PSS_UserGroupEntity -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group entity                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_ZBUserGroupEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)
#define AFX_ZBUserGroupEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_UserEntity.h"

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserRoleEntity;

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBUserEntitySet | An array of ZBUserEntity pointers.
//@iex typedef CCArray_T<ZBUserEntity*,ZBUserEntity*> ZBUserEntitySet;
typedef CCArray_T<PSS_UserEntity*, PSS_UserEntity*> ZBUserEntitySet;

//@type ZBUserEntityIterator | An iterator for ZBUserEntitySet collections.
//@iex typedef Iterator_T<ZBUserEntity*> ZBUserEntityIterator;
typedef Iterator_T<PSS_UserEntity*> ZBUserEntityIterator;

/**
* User group entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBUserGroupEntity : public PSS_UserEntity
{
    DECLARE_SERIAL(ZBUserGroupEntity)

public:

    ZBUserGroupEntity(const CString Name = _T(""),
                      const CString Description = _T(""),
                      const float Cost = 0,
                      PSS_UserEntity* pParent = NULL);

    virtual ~ZBUserGroupEntity();

    /* Copy constructor. */
    ZBUserGroupEntity(const ZBUserGroupEntity& src);

    /* Assignment operator. */
    ZBUserGroupEntity& operator=(const ZBUserGroupEntity& src);

    /* Create a duplicate copy of this object. */
    virtual PSS_UserEntity* Clone() const;

    void RemoveAllUserEntities();

    size_t FillGroupNameArray(CStringArray& NameArray);

    virtual bool ContainEntity() const
    {
        return true;
    }

    virtual size_t GetEntityCount() const
    {
        return m_EntitySet.GetSize();
    }

    virtual PSS_UserEntity* GetEntityAt(size_t Index)
    {
        return (Index < GetEntityCount()) ? m_EntitySet.GetAt(Index) : NULL;
    }

    virtual ZBUserEntitySet* GetEntitySet()
    {
        return &m_EntitySet;
    }

    virtual const ZBUserEntitySet* GetEntitySetConst() const
    {
        return &m_EntitySet;
    }

    virtual bool ContainThisRole(const CString Role);

    // Modified flag functions
    virtual BOOL IsModified()
    {
        return m_bModified;
    }

    virtual void SetModifiedFlag(BOOL bModified = TRUE)
    {
        m_bModified = bModified;
    }

    ////////////////////////////////////////////////////////////////
    // Group management functions
    ZBUserGroupEntity* AddGroup(const CString Name, const CString Description, const float Cost);

    ZBUserGroupEntity* AddGroup(const CString    Name,
                                const CString    Description,
                                const float    Cost,
                                const CString    InGroupName);

    ZBUserGroupEntity* AddGroup(const CString        Name,
                                const CString        Description,
                                const float        Cost,
                                ZBUserGroupEntity*    pInGroup);

    bool RemoveGroup(const CString Name, bool Deeper = false);
    bool RemoveGroup(const CString Name, const CString InGroupName);
    bool RemoveGroup(const CString Name, ZBUserGroupEntity* pInGroup);
    bool RemoveGroup(ZBUserGroupEntity* pGroup);

    bool MoveEntity(PSS_UserEntity* pEntity);

    PSS_UserEntity* FindGroupByGUID(const CString GUID, bool Deeper = false);

    ZBUserEntitySet* FindGroup(const CString Name, bool Deeper = false);
    ZBUserEntitySet* FindGroup(const CString Name, const CString InGroupName);
    ZBUserEntitySet* FindGroup(const CString Name, ZBUserGroupEntity* pInGroup);

    ZBUserGroupEntity* FindFirstGroup(const CString Name, bool Deeper = false)
    {
        return _FindFirstGroup(Name, Deeper);
    }

    bool GroupExist(const CString Name, bool Deeper = false);
    bool GroupExist(const CString Name, const CString InGroupName);
    bool GroupExist(const CString Name, ZBUserGroupEntity* pInGroup);

    ////////////////////////////////////////////////////////////////
    // Role management functions
    ZBUserRoleEntity* AddRole(const CString Rolename, const CString Description);
    ZBUserRoleEntity* AddRole(const CString Rolename, const CString Description, const CString InGroupName);
    ZBUserRoleEntity* AddRole(const CString Rolename, const CString Description, ZBUserGroupEntity* pInGroup);
    bool RemoveRole(ZBUserRoleEntity* pRole);
    bool RemoveRole(const CString Rolename);
    bool RemoveRole(const CString Rolename, const CString InGroupName);
    bool RemoveRole(const CString Rolename, ZBUserGroupEntity* pInGroup);

    PSS_UserEntity* FindRoleByGUID(const CString GUID, bool Deeper = false);

    // Serialization mechanism
    virtual void Serialize(CArchive& ar);    // Overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    bool AddEntity(PSS_UserEntity* pEntity)
    {
        m_EntitySet.Add(pEntity);
        return true;
    }

    bool RemoveEntityFromSet(PSS_UserEntity* pEntity);

    ////////////////////////////////////////////////////////////////
    // Group management functions
    PSS_UserEntity* _FindGroupByGUID(const CString GUID, bool Deeper = false);
    void _FindGroup(const CString Name, ZBUserGroupEntity* pInGroup);
    void _FindGroup(const CString Name, bool Deeper = false);
    ZBUserGroupEntity* _FindFirstGroup(const CString Name, ZBUserGroupEntity* pInGroup);
    ZBUserGroupEntity* _FindFirstGroup(const CString Name, bool Deeper = false);
    bool _RemoveGroups(ZBUserEntitySet& Set);

    ////////////////////////////////////////////////////////////////
    // Role management functions
    PSS_UserEntity* _FindRoleByGUID(const CString GUID, bool Deeper = false);

    void RecalculateParent();

    // Members are protected, since they need to be access directly by sub-class
protected:

    ZBUserEntitySet            m_EntitySet;

    static ZBUserEntitySet    m_FindSet;
    static BOOL                m_bModified;
};

#endif
