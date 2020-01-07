/****************************************************************************
 * ==> PSS_LogicalSystemEntity ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system entity                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalSystemEntityH
#define PSS_LogicalSystemEntityH

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
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// processsoft
#include "PSS_SystemEntity.h"

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

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const CString g_LogicalSystemKey = _T("$LS=");
//---------------------------------------------------------------------------

/**
* Logical system entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalSystemEntity : public PSS_SystemEntity
{
    DECLARE_SERIAL(PSS_LogicalSystemEntity)

    public:
        typedef CCArray_T <PSS_SystemEntity*, PSS_SystemEntity*> IEntitySet;
        typedef Iterator_T<PSS_SystemEntity*>                    IEntityIterator;

        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param pParent - the parent
        */
        PSS_LogicalSystemEntity(const CString&    name        = _T(""),
                                const CString&    description = _T(""),
                                PSS_SystemEntity* pParent     = NULL);

        virtual ~PSS_LogicalSystemEntity();

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
        virtual inline PSS_SystemEntity* GetEntityAt(std::size_t index);

        /**
        * Gets the entity set
        *@return the entity set
        */
        virtual inline IEntitySet* GetEntitySet();

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
        * Adds a system entity
        *@param name - the system name
        *@param description - the system description
        *@return the newly added system entity, NULL on error
        */
        virtual PSS_LogicalSystemEntity* AddSystem(const CString& name, const CString& description);

        /**
        * Adds a system entity
        *@param name - the system name
        *@param description - the system description
        *@param inSystemName - the system entity name in which this entity should be added
        *@return the newly added system entity, NULL on error
        */
        virtual PSS_LogicalSystemEntity* AddSystem(const CString& name,
                                                   const CString& description,
                                                   const CString& inSystemName);

        /**
        * Adds a system entity
        *@param name - the system name
        *@param description - the system description
        *@param pInSystem - the system entity in which this entity should be added
        *@return the newly added system entity, NULL on error
        */
        virtual PSS_LogicalSystemEntity* AddSystem(const CString&           name,
                                                   const CString&           description,
                                                   PSS_LogicalSystemEntity* pInSystem);

        /**
        * Removes a system entity
        *@param name - the system name
        *@param deeper - if true, the system entity will be removed recursively in children
        *@return true on success, otherwise false
        */
        virtual bool RemoveSystem(const CString& name, bool deeper = false);

        /**
        * Removes a system entity
        *@param name - the system name
        *@param inSystemName - the system entity name in which this entity should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemoveSystem(const CString& name, const CString& inSystemName);

        /**
        * Removes a system entity
        *@param name - the system name
        *@param pInSystem - the system entity in which this entity should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemoveSystem(const CString& name, PSS_LogicalSystemEntity* pInSystem);

        /**
        * Removes a system entity
        *@param pSystem - the system to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveSystem(PSS_LogicalSystemEntity* pSystem);

        /**
        * Removes all the system entities
        */
        virtual void RemoveAllSystemEntities();

        /**
        * Finds a system from its guid
        *@param guid - the system guid to find
        *@param deeper - if true, the search will continue recursively in system children
        *@return the system, NULL if not found or on error
        */
        virtual PSS_SystemEntity* FindSystemByGUID(const CString& guid, bool deeper = false);

        /**
        * Finds a system
        *@param name - the system name to find
        *@param deeper - if true, the search will continue recursively in system children
        *@return the matching system, NULL if not found or on error
        */
        virtual IEntitySet* FindSystem(const CString& name, bool deeper = false);

        /**
        * Finds a system
        *@param name - the system name to find
        *@param inSystemName - the system entity name in which the search should begin
        *@return the matching system, NULL if not found or on error
        */
        virtual IEntitySet* FindSystem(const CString& name, const CString& inSystemName);

        /**
        * Finds a system
        *@param name - the system name to find
        *@param pInSystem - the system entity in which the search should begin
        *@return the matching system, NULL if not found or on error
        */
        virtual IEntitySet* FindSystem(const CString& name, PSS_LogicalSystemEntity* pInSystem);

        /**
        * Checks if a system exists
        *@param name - the system name to find
        *@param deeper - if true, the search will continue recursively in system children
        *@return true if the system exists, otherwise false
        */
        virtual bool SystemExist(const CString& name, bool deeper = false);

        /**
        * Checks if a system exists
        *@param name - the system name to find
        *@param inSystemName - the system entity name in which the search should begin
        *@return true if the system exists, otherwise false
        */
        virtual bool SystemExist(const CString& name, const CString& inSystemName);

        /**
        * Checks if a system exists
        *@param name - the system name to find
        *@param pInSystem - the system entity in which the search should begin
        *@return true if the system exists, otherwise false
        */
        virtual bool SystemExist(const CString& name, PSS_LogicalSystemEntity* pInSystem);

        /**
        * Moves a system
        *@param pSystem - the system to move
        *@return true on success, otherwise false
        */
        virtual bool MoveSystem(PSS_SystemEntity* pSystem);

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
        * Adds a system
        *@param pSystem - the system to add
        *@return true on success, otherwise false
        */
        virtual inline bool AddSystem(PSS_SystemEntity* pSystem);

        /**
        * Removes a system from the system set
        *@param pSystem - the system to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveSystemFromSet(PSS_SystemEntity* pSystem);

        /**
        * Finds a system from its guid
        *@param guid - the system guid to find
        *@param deeper - if true, the search will continue recursively in system children
        *@return the system, NULL if not found or on error
        */
        virtual PSS_SystemEntity* FindSystemByGUIDPvt(const CString& guid, bool deeper = false);

        /**
        * Finds a system
        *@param name - the system name to find
        *@param deeper - if true, the search will continue recursively in system children
        *@return the matching system, NULL if not found or on error
        */
        virtual void FindSystemPvt(const CString& name, bool deeper = false);

        /**
        * Finds a system
        *@param name - the system name to find
        *@param inSystemName - the system entity name in which the search should begin
        *@return true if the system exists, otherwise false
        */
        virtual void FindSystemPvt(const CString& name, PSS_LogicalSystemEntity* pInSystem);

        /**
        * Finds the first system matching with the name
        *@param name - the system name to find
        *@param deeper - if true, the search will continue recursively in system children
        *@return the matching system, NULL if not found or on error
        */
        virtual PSS_LogicalSystemEntity* FindFirstSystem(const CString& name, bool deeper = false);

        /**
        * Finds the first system matching with the name
        *@param name - the system name to find
        *@param inSystemName - the system entity name in which the search should begin
        *@return true if the system exists, otherwise false
        */
        virtual PSS_LogicalSystemEntity* FindFirstSystem(const CString& name, PSS_LogicalSystemEntity* pInSystem);

        /**
        * Removes all system in a set
        *@param set - the system set containing the system to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveSystems(IEntitySet& Set);

        /**
        * Recalculates the parent
        */
        virtual void RecalculateParent();
};

//---------------------------------------------------------------------------
// PSS_LogicalSystemEntity
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::ContainEntity() const
{
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_LogicalSystemEntity::GetEntityCount() const
{
    return m_EntitySet.GetSize();
}
//---------------------------------------------------------------------------
PSS_SystemEntity* PSS_LogicalSystemEntity::GetEntityAt(std::size_t index)
{
    return (index < GetEntityCount() ? m_EntitySet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity::IEntitySet* PSS_LogicalSystemEntity::GetEntitySet()
{
    return &m_EntitySet;
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalSystemEntity::IsModified()
{
    return m_Modified;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemEntity::SetModifiedFlag(BOOL modified)
{
    m_Modified = modified;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemEntity::AddSystem(PSS_SystemEntity* pSystem)
{
    m_EntitySet.Add(pSystem);
    return true;
}
//---------------------------------------------------------------------------

#endif
