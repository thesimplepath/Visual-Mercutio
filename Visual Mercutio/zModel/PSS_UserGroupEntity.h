/****************************************************************************
 * ==> PSS_UserGroupEntity -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group entity                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserGroupEntityH
#define PSS_UserGroupEntityH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// processsoft
#include "PSS_UserEntity.h"

// forward class declaration
class ZBUserRoleEntity;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* User group entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserGroupEntity : public PSS_UserEntity
{
    DECLARE_SERIAL(PSS_UserGroupEntity)

    public:
        typedef CCArray_T <PSS_UserEntity*, PSS_UserEntity*> IEntitySet;
        typedef Iterator_T<PSS_UserEntity*>                  IEntityIterator;

        /**
        * Constructor
        *@param name - the name
        *@param description - the description
        *@param cost - the cost
        *@param pParent - the parent symbol, can be NULL
        */
        PSS_UserGroupEntity(const CString&  name        = _T(""),
                            const CString&  description = _T(""),
                            const float     cost        = 0,
                            PSS_UserEntity* pParent     = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserGroupEntity(const PSS_UserGroupEntity& src);

        virtual ~PSS_UserGroupEntity();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_UserGroupEntity& operator = (const PSS_UserGroupEntity& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_UserEntity* Clone() const;

        /**
        * Checks if this object contains an entity
        *@return true if this object contains an entity, otherwise false
        */
        virtual inline bool ContainEntity() const;

        /**
        * Gets the entity count
        *@return the entity count
        */
        virtual inline std::size_t GetEntityCount() const;

        /**
        * Gets the entity at index
        *@return the entity at index, NULL if not found or on error
        */
        virtual inline PSS_UserEntity* GetEntityAt(std::size_t index);

        /**
        * Gets the entity set
        *@return the entity set
        */
        virtual inline       IEntitySet* GetEntitySet();
        virtual inline const IEntitySet* GetEntitySet() const;

        /**
        * Checks if the entity was modified
        *@return TRUE if the entity was modified, otherwise FALSE
        */
        virtual inline BOOL IsModified();

        /**
        * Sets the entity as modified
        *@param value - if TRUE, the entity was modified
        */
        virtual inline void SetModifiedFlag(BOOL modified = TRUE);

        /**
        * Adds a group entity
        *@param name - the group name
        *@param description - the group description
        *@return the newly added group entity, NULL on error
        */
        virtual PSS_UserGroupEntity* AddGroup(const CString& name, const CString& description, const float cost);

        /**
        * Adds a group entity
        *@param name - the group name
        *@param description - the group description
        *@param inGroupName - the group entity name in which this entity should be added
        *@return the newly added group entity, NULL on error
        */
        virtual PSS_UserGroupEntity* AddGroup(const CString& name,
                                              const CString& description,
                                              const float    cost,
                                              const CString& inGroupName);

        /**
        * Adds a group entity
        *@param name - the group name
        *@param description - the group description
        *@param pInGroup - the group entity in which this entity should be added
        *@return the newly added group entity, NULL on error
        */
        virtual PSS_UserGroupEntity* AddGroup(const CString&       name,
                                              const CString&       description,
                                              const float          cost,
                                              PSS_UserGroupEntity* pInGroup);

        /**
        * Removes a group entity
        *@param name - the group name
        *@param deeper - if true, the group entity will be removed recursively in children
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(const CString& name, bool deeper = false);

        /**
        * Removes a group entity
        *@param name - the group name
        *@param inGroupName - the group entity name in which this entity should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(const CString& name, const CString& inGroupName);

        /**
        * Removes a group entity
        *@param name - the group name
        *@param pInGroup - the group entity in which this entity should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(const CString& name, PSS_UserGroupEntity* pInGroup);

        /**
        * Removes a group entity
        *@param pGroup - the group to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(PSS_UserGroupEntity* pGroup);

        /**
        * Finds a group from its guid
        *@param guid - the group guid to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the group, NULL if not found or on error
        */
        virtual PSS_UserEntity* FindGroupByGUID(const CString& guid, bool deeper = false);

        /**
        * Finds a group
        *@param name - the group name to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the matching group, NULL if not found or on error
        */
        virtual IEntitySet* FindGroup(const CString& name, bool deeper = false);

        /**
        * Finds a group
        *@param name - the group name to find
        *@param inGroupName - the group entity name in which the search should begin
        *@return the matching group, NULL if not found or on error
        */
        virtual IEntitySet* FindGroup(const CString& name, const CString& inGroupName);

        /**
        * Finds a group
        *@param name - the group name to find
        *@param pInGroup - the group entity in which the search should begin
        *@return the matching group, NULL if not found or on error
        */
        virtual IEntitySet* FindGroup(const CString& name, PSS_UserGroupEntity* pInGroup);

        /**
        * Finds the first group matching with the name
        *@param name - the group name to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the matching group, NULL if not found or on error
        */
        virtual inline PSS_UserGroupEntity* FindFirstGroup(const CString& name, bool deeper = false);

        /**
        * Checks if a group exists
        *@param name - the group name to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return true if the group exists, otherwise false
        */
        virtual bool GroupExist(const CString& name, bool deeper = false);

        /**
        * Checks if a group exists
        *@param name - the group name to find
        *@param inGroupName - the group entity name in which the search should begin
        *@return true if the system exists, otherwise false
        */
        virtual bool GroupExist(const CString& name, const CString& inGroupName);

        /**
        * Checks if a group exists
        *@param name - the group name to find
        *@param pInSystem - the group entity in which the search should begin
        *@return true if the group exists, otherwise false
        */
        virtual bool GroupExist(const CString& name, PSS_UserGroupEntity* pInGroup);

        /**
        * Fills the group name array
        *@return nameArray - the name array to fill
        *@return the name array item count
        */
        virtual std::size_t FillGroupNameArray(CStringArray& nameArray);

        /**
        * Adds a role
        *@param name - the role name
        *@param description - the role description
        *@return the newly added role, NULL on error
        */
        virtual ZBUserRoleEntity* AddRole(const CString& name, const CString& description);

        /**
        * Adds a role
        *@param name - the role name
        *@param description - the role description
        *@param inGroupName - the group entity name in which this role should be added
        *@return the newly added role, NULL on error
        */
        virtual ZBUserRoleEntity* AddRole(const CString& name, const CString& description, const CString& inGroupName);

        /**
        * Adds a role
        *@param name - the role name
        *@param description - the role description
        *@param pInGroup - the group entity in which this role should be added
        *@return the newly added role, NULL on error
        */
        virtual ZBUserRoleEntity* AddRole(const CString& name, const CString& description, PSS_UserGroupEntity* pInGroup);

        /**
        * Removes a role
        *@param name - the role name to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveRole(const CString& name);

        /**
        * Removes a role
        *@param name - the role name to remove
        *@param inGroupName - the group entity name from which the role should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemoveRole(const CString& name, const CString& inGroupName);

        /**
        * Removes a role
        *@param name - the role name to remove
        *@param pInGroup - the group entity from which the role should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemoveRole(const CString& name, PSS_UserGroupEntity* pInGroup);

        /**
        * Removes a role
        *@param pRole - the role to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveRole(ZBUserRoleEntity* pRole);

        /**
        * Finds a role from its guid
        *@param guid - the role guid to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the role, NULL if not found or on error
        */
        virtual PSS_UserEntity* FindRoleByGUID(const CString& guid, bool deeper = false);

        /**
        * Checks if the group contains a role
        *@param name - the role name to find
        *@return true if the group contains the role, otherwise false
        */
        virtual bool ContainThisRole(const CString& name);

        /**
        * Moves an entity
        *@param pEntity - the entity to move
        *@return true on success, otherwise false
        */
        virtual bool MoveEntity(PSS_UserEntity* pEntity);

        /**
        * Removes all the user entities
        */
        virtual void RemoveAllUserEntities();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        static IEntitySet m_FindSet;
        static BOOL       m_Modified;
        IEntitySet        m_EntitySet;

        /**
        * Adds an entity
        *@param pEntity - the entity to add
        *@return true on success, otherwise fals
        */
        virtual inline bool AddEntity(PSS_UserEntity* pEntity);

        /**
        * Removes an entity from the entity set
        *@param pEntity - the entity to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveEntityFromSet(PSS_UserEntity* pEntity);

        /**
        * Finds a group from its guid
        *@param guid - the group guid to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the group, NULL if not found or on error
        */
        virtual PSS_UserEntity* FindGroupByGUIDPvt(const CString& guid, bool deeper = false);

        /**
        * Finds a group
        *@param name - the group name to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the matching group, NULL if not found or on error
        */
        virtual void FindGroupPvt(const CString& name, bool deeper = false);

        /**
        * Finds a group
        *@param name - the group name to find
        *@param pInGroup - the group entity in which the search should begin
        *@return the matching group, NULL if not found or on error
        */
        virtual void FindGroupPvt(const CString& name, PSS_UserGroupEntity* pInGroup);

        /**
        * Finds the first group matching with the name
        *@param name - the group name to find
        *@param pInGroup - the group entity in which the search should begin
        *@return the matching group, NULL if not found or on error
        */
        virtual PSS_UserGroupEntity* FindFirstGroup(const CString& name, PSS_UserGroupEntity* pInGroup);

        /**
        * Removes all groups in a set
        *@param set - the group set containing the groups to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroups(IEntitySet& set);

        /**
        * Finds a role from its guid
        *@param guid - the role guid to find
        *@param deeper - if true, the search will continue recursively in group children
        *@return the role, NULL if not found or on error
        */
        virtual PSS_UserEntity* FindRoleByGUIDPvt(const CString& guid, bool deeper = false);

        /**
        * Recalculates the parent
        */
        virtual void RecalculateParent();
};

//---------------------------------------------------------------------------
// PSS_UserGroupEntity
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::ContainEntity() const
{
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_UserGroupEntity::GetEntityCount() const
{
    return m_EntitySet.GetSize();
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserGroupEntity::GetEntityAt(std::size_t index)
{
    return (index < GetEntityCount() ? m_EntitySet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity::IEntitySet* PSS_UserGroupEntity::GetEntitySet()
{
    return &m_EntitySet;
}
//---------------------------------------------------------------------------
const PSS_UserGroupEntity::IEntitySet* PSS_UserGroupEntity::GetEntitySet() const
{
    return &m_EntitySet;
}
//---------------------------------------------------------------------------
BOOL PSS_UserGroupEntity::IsModified()
{
    return m_Modified;
}
//---------------------------------------------------------------------------
void PSS_UserGroupEntity::SetModifiedFlag(BOOL modified)
{
    m_Modified = modified;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupEntity::AddEntity(PSS_UserEntity* pEntity)
{
    m_EntitySet.Add(pEntity);
    return true;
}
//---------------------------------------------------------------------------

#endif
